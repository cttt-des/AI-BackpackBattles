extends "res://Interface/Lobbies/CustomUnrankedUI.gd"

const localeMargins = {
	"en": 1522, 
	"pt": 1576, 
	"es": 1576, 
}

func startGame():
	CustomRules.setSwitchMode(CustomRules.SwitchModeState.Unranked)
	.startGame()

func _ready():
	$Hint.formatParams = {"gold": Util.getIcon("gold")}
	add_to_group("Localized")

func open():
	.open()
	updateLocale()

func updateLocale():
	var enMargin = localeMargins["en"]
	var margin = localeMargins.get(TranslationServer.get_locale(), enMargin)
	var rules = $Rules
	rules.margin_right = margin
	for rule in rules.get_children():
		var label = rule.get_node_or_null("Property")
		if label != null:
			label.setMaxSize(224 + margin - enMargin)
