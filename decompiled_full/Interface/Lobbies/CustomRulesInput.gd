extends VBoxContainer

signal rules_changed

var labels: Dictionary
var sliders: Dictionary
var suffixes: = {
	CustomRules.Rules.HealthMultiplier: "%", 
	CustomRules.Rules.SalesChance: "%", 
	CustomRules.Rules.TradeChance: "%", 
	CustomRules.Rules.BonusTreasures: "%"
}
onready var cannotPickBagsCheckbox = $CannotPickBags / Checkbox

func _ready():
	for entry in get_children():
		var rule: int = CustomRules.Rules[entry.name]
		for child in entry.get_children():
			if child.name == "Value":
				labels[rule] = child
			if child.name == "Control" and child.visible:
				var slider = child.get_node("Slider")
				sliders[rule] = slider
				slider.min_value = CustomRules.MIN[rule]
				slider.max_value = CustomRules.MAX[rule]
				slider.step = CustomRules.STEP[rule]
				slider.connect("value_changed", self, "onValueChanged", [rule])
	
	cannotPickBagsCheckbox.connect("toggled", self, "onCannotPickBagsToggled")
	cannotPickBagsCheckbox.set_pressed_no_signal(CustomRules.getCannotPickBags())

func onCannotPickBagsToggled(state):
	CustomRules.setCannotPickBags(state)
	emit_signal("rules_changed")

func onOpen():
	for rule in sliders:
		sliders[rule].set_value_no_signal(CustomRules.getRuleValue(rule))
	for rule in labels:
		updateLabel(rule)

func updateLabel(rule: int):
	var valStr: String
	if rule == CustomRules.Rules.HealthMultiplier:
		valStr = str(CustomRules.getRuleValue(rule))
	else:
		valStr = Util.addPlus(CustomRules.getRuleValue(rule))
	labels[rule].text = valStr + suffixes.get(rule, "")

func onValueChanged(value, rule: int):
	CustomRules.setRuleValue(rule, value)
	var _value = CustomRules.getRuleValue(rule)
	updateLabel(rule)
	emit_signal("rules_changed")
