extends Control

var poolingHandle
var absDamageLabel
var totalLabel
var player

func preset():
	absDamageLabel = $AbsoluteDamage
	totalLabel = $Name
	Util.localizeFonts(absDamageLabel)

func init(absValue, dps: float):
	absDamageLabel.text = Util.tra("UI_DamageMeter_Format").format({
		"absDmg": stepify(absValue, 0.1), 
		"dps": stepify(dps, 0.1)})
	
	Util.localizeFonts(self)
	totalLabel.updateLocale()
