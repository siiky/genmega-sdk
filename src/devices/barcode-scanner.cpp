#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

static std::atomic<bool> _bcs_stop = false;
static std::mutex _bcs_m;
static std::condition_variable _bcs_scan_con;
static std::string _bcs_data;
static int _bcs_return_int = 0;

static std::atomic<bool> _bcs_opened = false;

static size_t now (void)
{
	return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

static void _log (const char * file, unsigned line, const char * msg)
{
	fprintf(stderr, "%zu [BCS] %s:%u\t%s\n", now(), file, line, msg);
}

#define log(msg) _log(__FILE__, __LINE__, msg)

#define trace(expr) \
do { \
	log(#expr); \
	expr; \
} while (0)


static bool _bcs_stop_pred ()
{
	return _bcs_stop;
}

void ScannedBarcodeDataCallBack (int iId, int iKind, BCSScanData * BcsScanData)
{
	log("ScannedBarcodeDataCallBack()");
	std::unique_lock<std::mutex> lock(_bcs_m);

	char * data = new char [BcsScanData->wSize + 1];
	std::memcpy(data, BcsScanData->szCode, BcsScanData->wSize);
	data[BcsScanData->wSize] = '\0';
	_bcs_data = std::string(reinterpret_cast<char const *>(data));
	delete[] data;

	_bcs_stop = true;
	_bcs_scan_con.notify_all();
}

bool StartScan (std::string serialPortName, int mobilePhoneMode, char presentationMode)
{
	_bcs_data = std::string("");
	_bcs_return_int = 0;
	const char * where = "";

	trace(BCS_CallBackRegister(ScannedBarcodeDataCallBack));

	// This conditional is true if _bcs_opened is false. Inside the block
	// _bcs_opened has already been set to true. We need to change it back to
	// false only if an error occured.
	bool expected = false;
	if (std::atomic_compare_exchange_strong(&_bcs_opened, &expected, true)) {
		trace(_bcs_return_int = BCS_Open(serialPortName.c_str(), mobilePhoneMode));
		if (_bcs_return_int != HM_DEV_OK) {
			_bcs_opened = false;
			where = "BCS_Open";
			goto error;
		}
	}

	trace(_bcs_return_int = BCS_Reset());
	if (_bcs_return_int != HM_DEV_OK) {
		where = "BCS_Reset";
		goto error;
	}

	trace(_bcs_return_int = BCS_AcceptScanCode(presentationMode));
	if (_bcs_return_int != HM_DEV_OK) {
		where = "BCS_AcceptScanCode";
		goto error;
	}

	return true;

error:
	unsigned char errmsg[6] = {0};
	BCS_GetLastError(errmsg);
	fprintf(stderr, "%zu [BCS] %s failed with %d: %s\n", now(), where, _bcs_return_int, errmsg);
	return false;
}

struct _BCS_ScanWorker : public Napi::AsyncWorker
{
public:
	_BCS_ScanWorker(Napi::Function& callback, std::string serialPortName, int mobilePhoneMode, char presentationMode)
		: Napi::AsyncWorker(callback), serialPortName(serialPortName), mobilePhoneMode(mobilePhoneMode), presentationMode(presentationMode) {}
	~_BCS_ScanWorker() {}

	void Execute() override
	{
		log("ScanWorker: Executing");
		std::unique_lock<std::mutex> lock(_bcs_m);

		log("ScanWorker: Starting scan");
		if (!StartScan(serialPortName, mobilePhoneMode, presentationMode))
			return;

		/*
		 * "pred can be optionally provided to detect spurious wakeup."
		 * https://en.cppreference.com/w/cpp/thread/condition_variable/wait
		 */
		log("ScanWorker: Waiting");
		_bcs_scan_con.wait(lock, _bcs_stop_pred);
	}

	void OnOK()
	{
		Callback().Call({Napi::Number::New(Env(), _bcs_return_int), Napi::String::New(Env(), _bcs_data)});
	}

private:
	std::string serialPortName;
	int mobilePhoneMode;
	int presentationMode;
};

void BCSCancelScan ()
{
	trace(BCS_CancelScanCode());
	_bcs_stop = true;
	_bcs_return_int = HM_DEV_CANCEL;
	_bcs_data = std::string("");
	_bcs_scan_con.notify_all();
}

void BCSScan (std::string serialPortName, int mobilePhoneMode, char presentationMode, Napi::Function callback)
{
	_bcs_stop = false;
	_BCS_ScanWorker * _bcs_scanWorker = new _BCS_ScanWorker(callback, serialPortName, mobilePhoneMode, presentationMode);
	_bcs_scanWorker->Queue();
}
