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
onready var teamSwitchModeCheckbox = $TeamSwitchMode / Checkbox

func _ready():
	for entry in get_children():
		
		if not entry.name in CustomRules.Rules:
			continue
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
	
	
	
	
	
	teamSwitchModeCheckbox.connect("toggled", self, "onTeamSwitchModeToggled")
	teamSwitchModeCheckbox.set_pressed_no_signal(CustomRules.isTeamSwitchMode())
	
	
	

func onCannotPickBagsToggled(state):
	CustomRules.setCannotPickBags(state)
	emit_signal("rules_changed")

func onTeamSwitchModeToggled(state):
	print("[CustomRulesInput] onTeamSwitchModeToggled state=", state)
	CustomRules.setTeamSwitchMode(CustomRules.TeamSwitchModeState.On if state else CustomRules.TeamSwitchModeState.Off)
	emit_signal("rules_changed")

func onOpen():
	for rule in sliders:
		sliders[rule].set_value_no_signal(CustomRules.getRuleValue(rule))
	for rule in labels:
		updateLabel(rule)
	
	
	teamSwitchModeCheckbox.set_pressed_no_signal(CustomRules.isTeamSwitchMode())

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
