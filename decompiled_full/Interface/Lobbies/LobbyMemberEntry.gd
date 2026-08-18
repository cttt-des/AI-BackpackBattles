extends Control

var nameLabel
var classIcon
var kickButton

var steamId: int
var memberData: LobbyMemberData
var isPlayer: bool
var isHost: bool

func init():
	classIcon = $HboxContainer / ClassIcon
	nameLabel = $HboxContainer / Name
	kickButton = $HboxContainer / KickButton
	Util.addFallbackFonts(nameLabel.get("custom_fonts/font"))

func setSteamId(_steamId: int):
	init()
	steamId = _steamId
	memberData = RunDatabase.lobbies.getMemberData(steamId)
	isPlayer = memberData.isSelf()
	isHost = RunDatabase.lobbies.isMemberHost(steamId)
	kickButton.visible = RunDatabase.lobbies.isHost() and not isHost
	updatePlayer()
	memberData.connect("data_changed", self, "updatePlayer")

func updatePlayer():
	nameLabel.text = memberData.playerName
	if memberData.loadout == Game.Loadout.RandomCharacter:
		classIcon.texture = Game.randomClassIcon
	else:
		classIcon.texture = Game.classIcons[memberData.characterClass]

func onKickButtonPressed():
	RunDatabase.lobbies.kickMember(steamId)
