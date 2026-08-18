extends LocalizedControl

onready var icon = $StaminaUsage
onready var animation = $AnimationPlayer
onready var tooltipArea = $TooltipArea

var updateQueued: = false

const colors = [
	Color(0.664886, 1, 0.457031), 
	Color(0.893951, 1, 0.457031), 
	Color(1, 0.97879, 0.457031), 
	Color(1, 0.686096, 0.457031), 
	Color(1, 0.390625, 0.390625)
]

func _ready() -> void :
	add_to_group("Localized")
	Game.connect("inventory_changed", self, "updateCounter")

func updateCounter():
	if not updateQueued:
		updateQueued = true
		call_deferred("updateLocale")

func updateLocale():
	updateQueued = false
	var previousState = icon.frame
	var totalStaminaUse = Game.PLAYER.getTotalStaminaUsage()
	var key = "STAMINA_"
	if totalStaminaUse < 0.5:
		icon.frame = 0
		key += "VeryLow"
	elif totalStaminaUse < 1.2:
		icon.frame = 1
		key += "Low"
	elif totalStaminaUse < 1.5:
		icon.frame = 2
		key += "Medium"
	elif totalStaminaUse < 2.0:
		icon.frame = 3
		key += "High"
	else:
		icon.frame = 4
		key += "VeryHigh"
	
	setTranslationKey(key)
	
	if previousState != icon.frame:
		if icon.frame == 4:
			
			animation.play("VeryHighStart")
			animation.queue("VeryHighUsage")
		else:
			animation.play("RESET")
		
		set("custom_colors/font_color", colors[icon.frame])
		
	tooltipArea.params = {
		"staminaGain": Util.wrapInColor("1", Util.paramColor), 
		"staminaUsage": Util.wrapInColor(String(stepify(totalStaminaUse, 0.1)), Util.paramColor)
	}
	
