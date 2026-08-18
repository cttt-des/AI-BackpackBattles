extends ToolTip

var lobbyMode: bool

onready var entries = {
	CustomRules.Rules.BonusGold: $VBoxContainer / Gold, 
	CustomRules.Rules.BonusTreasures: $VBoxContainer / Uniques, 
	CustomRules.Rules.HealthMultiplier: $VBoxContainer / Health, 
	CustomRules.Rules.SalesChance: $VBoxContainer / Sales, 
	CustomRules.Rules.TradeChance: $VBoxContainer / Trade, 
	CustomRules.Rules.TreasureLimit: $VBoxContainer / TreasureLimit, 
	CustomRules.Rules.CannotPickBags: $VBoxContainer / CannotPickBags, 
	CustomRules.Rules.LeagueToMatch: get_node_or_null("VBoxContainer/League"), 
	CustomRules.Rules.SwitchMode: get_node_or_null("VBoxContainer/SwitchMode")
}

onready var bonusGoldLabel = $VBoxContainer / Gold / Value
onready var bonusTreasuresLabel = $VBoxContainer / Uniques / Value
onready var treasureLimitLabel = $VBoxContainer / TreasureLimit / Value
onready var saleChanceLabel = $VBoxContainer / Sales / Value
onready var tradeChanceLabel = $VBoxContainer / Trade / Value
onready var healthMultiplierLabel = $VBoxContainer / Health / Value
onready var cannotPickBagsCheckbox = $VBoxContainer / CannotPickBags / Checkbox

onready var leagueToMatchNode = get_node_or_null("VBoxContainer/League")
onready var leagueToMatchRect = get_node_or_null("VBoxContainer/League/TextureRect")

func setRules(_customRules = CustomRules, _lobbyMode: bool = false):
	lobbyMode = _lobbyMode
	if lobbyMode:
		leagueToMatchNode.hide()
	updateRules(_customRules)

func updateRules(_customRules = CustomRules):
	for rule in CustomRules.Rules.values():
		if _customRules.isRuleDefault(rule):
			entries[rule].hide()
		else:
			entries[rule].show()
	
	bonusGoldLabel.text = Util.addPlus(_customRules.getBonusGold())
	treasureLimitLabel.text = Util.addPlus(_customRules.getRuleValue(CustomRules.Rules.TreasureLimit))
	bonusTreasuresLabel.text = Util.addPlus(_customRules.getBonusUniqueChance()) + "%"
	saleChanceLabel.text = Util.addPlus(_customRules.getRuleValue(CustomRules.Rules.SalesChance)) + "%"
	tradeChanceLabel.text = Util.addPlus(_customRules.getRuleValue(CustomRules.Rules.TradeChance)) + "%"
	healthMultiplierLabel.text = str(_customRules.getHealthMultiplier()) + "%"
	cannotPickBagsCheckbox.set_pressed_no_signal(_customRules.getCannotPickBags())
	
	if not lobbyMode:
		var leagueToMatch = _customRules.getLeagueToMatch()
		if leagueToMatch != _customRules.UNRANKED:
			leagueToMatchRect.texture = Game.leagueIcons[leagueToMatch]


	vboxcontainer.rect_size.y = 0

