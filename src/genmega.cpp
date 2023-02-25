#include <napi.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "devices/barcode-scanner.hpp"
#include "devices/bill-validator.hpp"
#include "devices/result.hpp"


Napi::Object mapToNapiObject (operationResult result, Napi::Env env) {
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("iRet", result.iRet);
    obj.Set("data", result.data);

    return obj;
}

Napi::Object BarcodeScan(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];
    int presentationMode = 0, mobilePhoneMode = 0; // presentation mode enables getting barcode data continuously, not interesting for our use case
    
    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    // mobile mode
    mobilePhoneMode = info[1].ToNumber();

    return mapToNapiObject(BCS_Scan(szPortName, mobilePhoneMode, presentationMode), env);
}

Napi::Object BarcodeCancelScan(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BCS_CancelScan(), env);
}


// BAU new v2

Napi::Object BAUGetLastErrorV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    
    return mapToNapiObject(BAUGetLastError(), env);
}

Napi::Object BAUOpenV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szPortName[128];

    // serial port name
    std::string serialPortName = (std::string)info[0].ToString();
    strcpy(szPortName, serialPortName.c_str());

    return mapToNapiObject(BAUOpen(szPortName), env);
}

Napi::Object BAUResetV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUReset(), env);
}

Napi::Object BAUCloseV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUClose(), env);
}

Napi::Object BAUStatusV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUStatus(), env);
}

Napi::Object BAUSetEnableDenomV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    char szSetData[512];

    // currency and denomination data
    std::string denominationData = (std::string)info[0].ToString();
    strcpy(szSetData, denominationData.c_str());

    return mapToNapiObject(BAUSetEnableDenom(szSetData), env);
}

Napi::Object BAUAcceptBillV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int acceptMode = info[0].ToNumber();

    return mapToNapiObject(BAUAcceptBill(acceptMode), env);
}

Napi::Object BAUCancelV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUCancel(), env);
}

Napi::Object BAUReturnBillV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUReturnBill(), env);
}

Napi::Object BAUStackBillV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUStackBill(), env);
}

Napi::Object BAUGetSupportCurrencyV2(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return mapToNapiObject(BAUGetSupportCurrency(), env);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // set keys on `exports` object
    exports.Set(Napi::String::New(env, "BarcodeScan"), Napi::Function::New(env, BarcodeScan));
    exports.Set(Napi::String::New(env, "BarcodeCancelScan"), Napi::Function::New(env, BarcodeCancelScan));
    exports.Set(Napi::String::New(env, "BAUGetLastErrorV2"), Napi::Function::New(env, BAUGetLastErrorV2));
    exports.Set(Napi::String::New(env, "BAUOpenV2"), Napi::Function::New(env, BAUOpenV2));
    exports.Set(Napi::String::New(env, "BAUResetV2"), Napi::Function::New(env, BAUResetV2));
    exports.Set(Napi::String::New(env, "BAUCloseV2"), Napi::Function::New(env, BAUCloseV2));
    exports.Set(Napi::String::New(env, "BAUStatusV2"), Napi::Function::New(env, BAUStatusV2));
    exports.Set(Napi::String::New(env, "BAUSetEnableDenomV2"), Napi::Function::New(env, BAUSetEnableDenomV2));
    exports.Set(Napi::String::New(env, "BAUAcceptBillV2"), Napi::Function::New(env, BAUAcceptBillV2));
    exports.Set(Napi::String::New(env, "BAUCancelV2"), Napi::Function::New(env, BAUCancelV2));
    exports.Set(Napi::String::New(env, "BAUReturnBillV2"), Napi::Function::New(env, BAUReturnBillV2));
    exports.Set(Napi::String::New(env, "BAUStackBillV2"), Napi::Function::New(env, BAUStackBillV2));
    exports.Set(Napi::String::New(env, "BAUGetSupportCurrencyV2"), Napi::Function::New(env, BAUGetSupportCurrencyV2));

    // return `exports` object
    return exports;
}

NODE_API_MODULE(genmega, Init);
