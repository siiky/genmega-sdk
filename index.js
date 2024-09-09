exports.bau = require('./bau')
exports.bcs = require('./bcs')
const cdu = require('./cdu')
const rpu = require('./rpu')
const siu = require('./siu')

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
