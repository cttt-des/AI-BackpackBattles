extends ResizableControl

const memberLine = preload("res://Interface/Lobbies/LobbyScoreboardEntry.tscn")
onready var memberContainer = $ScrollContainer / VBoxContainer
onready var scrollContainer = $ScrollContainer
var memberEntries: Dictionary
var isOpen: = false

onready var LOBBIES = RunDatabase.lobbies

func open():
	if not is_inside_tree():
		LOBBIES.scoreboardNode.add_child(self)
	isOpen = true
	show()

func close():
	
	LOBBIES.scoreboardNode.remove_child(self)
	isOpen = false

func _ready():
	
	clear()
	Game.connect("menu_opened", self, "onMenuOpened")
	Game.connect("menu_close", self, "onMenuClose")
	LOBBIES.connect("member_removed", self, "removeMember")
	for memberId in LOBBIES.memberList:
		addMember(memberId)
	LOBBIES.connect("score_changed", self, "updateMember")
	LOBBIES.scoreboardNode.call_deferred("remove_child", self)
	scrollContainer.get_v_scrollbar().connect("visibility_changed", self, "onScrollbarVisibilityChanged")
	onScrollbarVisibilityChanged()
	
func clear():
	for child in memberContainer.get_children():
		child.queue_free()
	memberEntries.clear()

func addMember(steamId):
	var line = memberLine.instance()
	memberContainer.add_child(line)
	memberEntries[steamId] = line
	line.setPlayerId(steamId)

func removeMember(steamId):
	var entry = memberEntries[steamId]
	entry.queue_free()
	memberEntries.erase(steamId)

func updateMember(memberId = null):
	if memberId == null:
		for member in memberEntries:
			memberEntries[member].onFightFinished()
	else:
		memberEntries[memberId].onFightFinished()
	updateRankings()

func updateRankings():
	for memberId in memberEntries:
		memberEntries[memberId].setRanking(RunDatabase.lobbies.getMemberRanking(memberId))

func onMenuOpened():
	if isOpen:
		hide()
	

func onMenuClose():
	if isOpen:
		show()
	

func onScrollbarVisibilityChanged():
	if LOBBIES.isHost():
		if scrollContainer.get_v_scrollbar().visible:
			rect_min_size.x = 568
		else:
			rect_min_size.x = 496
	else:
		if scrollContainer.get_v_scrollbar().visible:
			rect_min_size.x = 538
		else:
			rect_min_size.x = 466

func canDrag():
	return .canDrag() and not scrollContainer.scrollbarHovered
