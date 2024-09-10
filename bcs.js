const genmega = require('./build/Release/genmega.node')
const return_codes = require('./return_codes')
const return_messages = require('./return_messages')

exports.scan = (serialPortName, mobilePhoneMode) => {
  return new Promise(resolve => {
    /* There's a timeout at ~30s, but we never learn of it... */
    const timeout = setTimeout(() => {
      exports.cancelScan()
      const decoded = null
      const return_int = -9
      const return_code = return_codes[return_int]
      const return_message = return_messages[return_int]
      return resolve({ decoded, return_int, return_code, return_message })
    }, 31000)

    genmega._BCSScan(
      serialPortName,
      mobilePhoneMode,
      (return_int, decoded) => {
        clearTimeout(timeout)
        console.log("BCSScan resolving with return_int", return_int, "and decoded", decoded)
        const return_code = return_codes[return_int]
        const return_message = return_messages[return_int]
        return resolve({ decoded, return_int, return_code, return_message })
      }
    )
  })
}

exports.cancelScan = () => genmega._BCSCancelScan()
