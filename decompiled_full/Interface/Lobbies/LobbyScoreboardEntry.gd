extends Control

const checkmark = preload("res://Interface/Checkmark.png")
const transparentCheckmark = preload("res://Interface/Checkmark_transparent.png")
const stylebox_player = preload("res://Interface/Lobbies/MemberStylebox_Player.tres")
const stylebox_opponent = preload("res://Interface/Lobbies/MemberStylebox_Opponent.tres")


var rankingLabel
var nameLabel
var winLabel
var triesLabel
var classIcon
var statusIcon
var hostIcon
var scoreLabel
var kickButton

var steamId: int
var memberData: LobbyMemberData
var isPlayer: bool
var isHost: bool

func init():
	rankingLabel = $HboxContainer / Ranking
	nameLabel = $HboxContainer / Name
	winLabel = $HboxContainer / Wins
	triesLabel = $HboxContainer / Tries
	statusIcon = $HboxContainer / StatusIcon
	classIcon = $HboxContainer / ClassIcon
	hostIcon = $HostIcon
	scoreLabel = $HboxContainer / Score
	kickButton = $HboxContainer / KickButton
	
	Game.connect("combat_scene_entered", self, "onCombatStart")
	Util.addFallbackFonts(nameLabel.get("custom_fonts/font"))

func setPlayerId(_steamId: int):
	init()
	steamId = _steamId
	memberData = RunDatabase.lobbies.getMemberData(steamId)
	isPlayer = memberData.isSelf()
	isHost = RunDatabase.lobbies.isMemberHost(steamId)
	kickButton.visible = RunDatabase.lobbies.isHost() and not isHost
	nameLabel.text = memberData.playerName
	winLabel.text = str(memberData.getCurrentWins())
	
	
	if isPlayer:
		set("custom_styles/panel", stylebox_player)
	else:
		set("custom_styles/panel", stylebox_opponent)
	
	hostIcon.visible = isHost
	statusIcon.texture = null
	memberData.connect("ready", self, "onReady")
	memberData.connect("round_received", self, "onRoundDataReceived")
	
	if RunDatabase.lobbies.isHost():
		rect_min_size.x = 450
	else:
		rect_min_size.x = 409
	
	updatePlayerData()
	
	Util.callDelayed(self, "updatePlayerData", 1.0)

func updatePlayerData():
	classIcon.texture = Game.classIcons[memberData.characterClass]

func onFightFinished():
	winLabel.text = str(memberData.getCurrentWins())
	
	
	
func setStatus(_status):
	pass

func setRanking(rank):
	rankingLabel.text = str(rank)

func onCombatStart():
	statusIcon.texture = null

func onReady():
	statusIcon.texture = transparentCheckmark

func onRoundDataReceived(roundNum):
	if roundNum == Game.curRound:
		statusIcon.texture = checkmark

func onKickButtonPressed():
	RunDatabase.lobbies.kickMember(steamId)
