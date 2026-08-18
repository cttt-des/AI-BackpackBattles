extends Label

func _ready():
	RunDatabase.lobbies.connect("config_changed", self, "updateMemberCounter")
	RunDatabase.lobbies.connect("member_added", self, "updateMemberCounter")
	RunDatabase.lobbies.connect("member_removed", self, "updateMemberCounter")
	RunDatabase.lobbies.connect("lobby_joined", self, "show")
	RunDatabase.lobbies.connect("lobby_left", self, "hide")
	hide()

func updateMemberCounter(_steamId = null):
	text = String(RunDatabase.lobbies.getNumMembers())
	text += "/"
	text += String(RunDatabase.lobbies.getLobbySize())
