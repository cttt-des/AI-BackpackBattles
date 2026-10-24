extends Node2D

onready var unrankedLabel = $Unranked
onready var rankingLabel = $Ranking
onready var emblem = $LeagueEmblem
onready var surviveLabel = $Survive
onready var survivalSkull = $SurvivalSkull
onready var lobbyNode = $Lobby
onready var lobbyRoundsLabel = $Lobby / LobbyRounds
onready var roundNode = $Round
onready var winsNode = $Wins
onready var triesNode = $Tries
onready var customRulesIcon = $CustomRulesIcon

func _ready() -> void :
	Game.connect("switch_to_shop", self, "updateLabels")
	add_to_group("Localized")
	
func updateLabels():
	if Game.curMode != Game.Mode.Lobbies:
		triesNode.show()
		roundNode.position = Vector2( - 44, 114)
		winsNode.position = Vector2( - 64, 155)
		customRulesIcon.rect_position = Vector2(200, 78)
		
		if Game.isSurvivalMode():
			survivalSkull.show()
			surviveLabel.show()
			var roundsToSurvive = Game.getRoundsToSurvive()
			if roundsToSurvive == 1:
				surviveLabel.text = Util.tra("UI_SURVIVE_ONEROUND")
			else:
				surviveLabel.text = Util.tra("UI_SURVIVE").format({"rounds": roundsToSurvive})
		else:
			survivalSkull.hide()
			surviveLabel.hide()
		
		if Game.curMode == Game.Mode.Ranked or Game.isRankedSwitchMode():
			lobbyNode.hide()
			unrankedLabel.hide()
			rankingLabel.show()
			emblem.show()
			
			var league = Game.getLeague(Game.curClass)
			rankingLabel.text = String(Game.getRanking(Game.curClass))
			emblem.setLeague(league)
		else:
			lobbyNode.hide()
			unrankedLabel.show()
			rankingLabel.hide()
			emblem.hide()
	else:
		
		survivalSkull.hide()
		surviveLabel.hide()
		unrankedLabel.hide()
		rankingLabel.hide()
		emblem.hide()




		triesNode.hide()
		roundNode.position = Vector2(127, 128)
		winsNode.position = Vector2(107, 176)
		customRulesIcon.rect_position = Vector2( - 15, 93)
	
	if CustomRules.areCustomRulesActive():
		customRulesIcon.show()
		customRulesIcon.lobbyMode = (Game.curMode == Game.Mode.Lobbies)
	else:
		customRulesIcon.hide()
	
func updateLocale():
	if Game.isSurvivalMode():
		var roundsToSurvive = Game.getRoundsToSurvive()
		if roundsToSurvive == 1:
			surviveLabel.text = Util.tra("UI_SURVIVE_ONEROUND")
		else:
			surviveLabel.text = Util.tra("UI_SURVIVE").format({"rounds": roundsToSurvive})
