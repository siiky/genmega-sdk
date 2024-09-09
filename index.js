const bau = require('./bau')
const cdu = require('./cdu')
const rpu = require('./rpu')
const siu = require('./siu')
const bcs = require('./bcs')

exports.BCSScan = bcs.BCSScan
exports.BCSCancelScan = bcs.BCSCancelScan
exports.BAUGetLastError = bau.BAUGetLastError
exports.BAUOpen = bau.BAUOpen
exports.BAUReset = bau.BAUReset
exports.BAUClose = bau.BAUClose
exports.BAUStatus = bau.BAUStatus
exports.BAUSetCapabilities = bau.BAUSetCapabilities
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
exports.CDURetract = cdu.CDURetract
exports.RPUGetLastError = rpu.RPUGetLastError
exports.RPUOpen = rpu.RPUOpen
exports.RPUClose = rpu.RPUClose
exports.RPUStatus = rpu.RPUStatus
exports.RPUCutPaper = rpu.RPUCutPaper
exports.RPUPrintText = rpu.RPUPrintText
exports.SIULightUp = siu.SIULightUp
exports.SIULightDown = siu.SIULightDown
