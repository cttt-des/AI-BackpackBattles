extends ScrollContainer

const entryScene = preload("res://Interface/Lobbies/LobbyMemberEntry.tscn")

onready var vboxContainer = $VBoxContainer
var memberEntries: Dictionary

func _ready():
	clear()
	RunDatabase.lobbies.connect("member_added", self, "addMember")
	RunDatabase.lobbies.connect("member_removed", self, "removeMember")
	RunDatabase.lobbies.connect("lobby_left", self, "clear")
	get_v_scrollbar().connect("visibility_changed", self, "onScrollbarVisibilityChanged")

func addMember(steamId):
	var entry = entryScene.instance()
	vboxContainer.add_child(entry)
	entry.setSteamId(steamId)
	memberEntries[steamId] = entry

func removeMember(steamId):
	var entry = memberEntries[steamId]
	entry.queue_free()
	memberEntries.erase(entry)

func clear():
	for entry in vboxContainer.get_children():
		entry.queue_free()
	
	memberEntries.clear()

func onScrollbarVisibilityChanged():
	if get_v_scrollbar().visible:
		rect_size.x = 400
	else:
		rect_size.x = 335
