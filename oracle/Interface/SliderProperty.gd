extends HBoxContainer

export var translationKey = ""
onready var propertyLabel = $Property

func _ready():
	if translationKey == "UI_BonusGold":
		propertyLabel.formatParams = {"gold": Util.getIcon("gold")}
		
	elif translationKey == "UI_BonusTreasure" or translationKey == "UI_TreasureLimit":
		propertyLabel.formatParams = {"treasure": Util.getIcon("treasure")}
		
	propertyLabel.setTranslationKey(translationKey)

func hideSlider():
	$Control.hide()
