extends Control

const buttonGroup = preload("res://Interface/Lobbies/RoundButtonGroup.tres")
const stylebox_player = preload("res://Interface/Lobbies/MemberStylebox_Player.tres")
const stylebox_opponent = preload("res://Interface/Lobbies/MemberStylebox_Opponent.tres")

const stylebox_win = preload("res://Interface/Lobbies/ResultPanel_Win.tres")
const stylebox_loss = preload("res://Interface/Lobbies/ResultPanel_Loss.tres")


var rankingLabel
var nameLabel
var winLabel
var classIcon
var roundButtons = []

var steamId: int
var memberData: LobbyMemberData
var isPlayer: bool
var buildViewer


func init():
	rankingLabel = $HboxContainer / Ranking
	nameLabel = $HboxContainer / Name
	winLabel = $HboxContainer / Wins
	classIcon = $HboxContainer / ClassIcon / ClassIcon


	Util.addFallbackFonts(nameLabel.get("custom_fonts/font"))
	



	
	for roundI in Game.MAX_ROUNDS_LOBBIES:
		roundButtons.push_back(get_node("HboxContainer/RoundButton" + str(roundI + 1)))
	
	for roundI in roundButtons.size():
		roundButtons[roundI].connect("pressed", self, "onRoundButtonPressed", [roundI])
		
		roundButtons[roundI].group = buttonGroup
	
func setPlayerId(_steamId: int):
	init()
	steamId = _steamId
	memberData = RunDatabase.lobbies.getMemberData(steamId)
	isPlayer = memberData.isSelf()
	nameLabel.text = memberData.playerName
	winLabel.text = str(memberData.getCurrentWins())
	
	classIcon.texture = Game.classIcons[memberData.characterClass]
	
	if isPlayer:
		set("custom_styles/panel", stylebox_player)
	else:
		set("custom_styles/panel", stylebox_opponent)
	
	for roundI in Game.MAX_ROUNDS_LOBBIES:
		setRoundButton(roundI)
	
	updateRanking()

func onFightFinished():
	winLabel.text = str(memberData.getCurrentWins())
	
	
	setRoundButton(RunDatabase.lobbies.getCurRound() - 1)
	
func setRoundButton(roundI):
	var result = memberData.getResultOfRound(roundI + 1)
	roundButtons[roundI].setResult(result)

func onRoundButtonPressed(roundI: int):
	
		
	buildViewer.onRoundButtonPressed(roundButtons[roundI], steamId, roundI)

func updateRanking():
	rankingLabel.text = str(RunDatabase.lobbies.getMemberRanking(steamId))

func onEntryPressed():
	var maxRound = Game.MAX_ROUNDS_LOBBIES - 1
	if not roundButtons[maxRound].visible:
		maxRound -= 1
	if not roundButtons[maxRound].visible:
		return
	buildViewer.onRoundButtonPressed(roundButtons[maxRound], steamId, maxRound)
