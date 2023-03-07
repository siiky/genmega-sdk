const genmega = require('./build/Release/genmega.node')
const bau = require('./bau')
const cdu = require('./cdu')
const rpu = require('./rpu')

exports.BarcodeScan = genmega.BarcodeScan
exports.BarcodeCancelScan = genmega.BarcodeCancelScan
exports.BAUGetLastError = bau.BAUGetLastError
exports.BAUOpen = bau.BAUOpen
exports.BAUReset = bau.BAUReset
exports.BAUClose = bau.BAUClose
exports.BAUStatus = bau.BAUStatus
exports.BAUSetEnableDenom = bau.BAUSetEnableDenom
exports.BAUAcceptBill = bau.BAUAcceptBill
exports.BAUCancel = bau.BAUCancel
exports.BAUReject = bau.BAUReject
exports.BAUStack = bau.BAUStack
exports.BAUGetSupportCurrency = bau.BAUGetSupportCurrency
exports.CDUGetLastError = cdu.CDUGetLastError
exports.CDUOpen = cdu.CDUOpen
exports.CDUClose = cdu.CDUClose
exports.CDUStatus = cdu.CDUStatus
exports.CDUVerifyLicenseKey = cdu.CDUVerifyLicenseKey
exports.CDUReset = cdu.CDUReset
exports.CDUSetCassetteNumber = cdu.CDUSetCassetteNumber
exports.CDUDispense = cdu.CDUDispense
exports.CDUPresent = cdu.CDUPresent
exports.CDUForceEject = cdu.CDUForceEject
exports.CDUShutterAction = cdu.CDUShutterAction
exports.RPUGetLastError = rpu.RPUGetLastError
exports.RPUOpen = rpu.RPUOpen
exports.RPUClose = rpu.RPUClose
exports.RPUStatus = rpu.RPUStatus
exports.RPUCutPaper = rpu.RPUCutPaper
exports.RPUPrintText = rpu.RPUPrintText

