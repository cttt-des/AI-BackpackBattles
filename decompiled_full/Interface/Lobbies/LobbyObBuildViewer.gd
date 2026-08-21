extends Node2D

onready var LOBBIES = RunDatabase.lobbies
onready var itemsNode = $Items
onready var itemScale = itemsNode.scale
onready var inventory = $Items / Inventory
onready var nameLabel = $PlayerName
onready var roundLabel = $RoundNum
onready var animation = $AnimationPlayer
onready var clickOutside = $ClickOutside
var curOpponentIndex = 0
var roundNum = 0
var opponentSteamIds = []

const memberEntryScene = preload("res://Interface/Lobbies/LobbyResultEntry.tscn")
onready var memberContainer = $ScrollContainer / VBoxContainer
var memberEntries: Dictionary
onready var cursor = $ScrollContainer / VBoxContainer / Cursor

func _ready():
	for entry in memberContainer.get_children():
		if entry != cursor:
			entry.queue_free()
	LOBBIES.connect("score_changed", self, "updateMember")
	Util.addFallbackFonts(nameLabel.get("custom_fonts/font"))
	opponentSteamIds = LOBBIES.memberList.duplicate()
	for steamId in opponentSteamIds:
		var memberEntry = memberEntryScene.instance()
		memberContainer.add_child(memberEntry)
		memberEntry.setPlayerId(steamId)
		memberEntry.buildViewer = self
		memberEntries[steamId] = memberEntry
	clickOutside.viewer = self
	InputBlocker.activate(InputBlocker.Source.PopupAnimation, false)
	InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.shopSceneNode)
	InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.playerNode)
	animation.play("Appear")

func opened():
	InputBlocker.deactivate(InputBlocker.Source.PopupAnimation, false)

func nextMember():
	curOpponentIndex += 1
	curOpponentIndex %= LOBBIES.getNumMembers()
	updateBuild()

func previousMember():
	curOpponentIndex += LOBBIES.getNumMembers()
	curOpponentIndex -= 1
	curOpponentIndex %= LOBBIES.getNumMembers()
	updateBuild()

func nextRound():
	roundNum += 1
	roundNum %= Game.MAX_ROUNDS_LOBBIES
	updateBuild()

func previousRound():
	roundNum += Game.MAX_ROUNDS_LOBBIES
	roundNum -= 1
	roundNum %= Game.MAX_ROUNDS_LOBBIES
	updateBuild()

func updateBuild():
	var steamId = opponentSteamIds[curOpponentIndex]
	if not steamId in LOBBIES.memberData:
		print("ERR: Member ", steamId, " not in lobby anymore")
		return
	var entry = memberEntries[steamId]
	var roundButton = entry.roundButtons[roundNum]
	var memberData: LobbyMemberData = LOBBIES.getMemberData(steamId)
	nameLabel.text = memberData.playerName
	roundLabel.formatParams = {
		"cur": roundNum + 1, 
		"max": Game.MAX_ROUNDS_LOBBIES}
	roundLabel.updateLocale()
	var roundData: String = memberData.getRoundData(roundNum + 1)
	if roundData == null:
		print("ERR: Round missing ", roundNum + 1)
	var itemDict = RunData.deserializeItems(roundData, Game.VERSION)
	itemsNode.scale = Vector2.ONE
	inventory.createFromItemTuples(itemDict["items"], Item.Owner.BuildViewer)
	itemsNode.scale = itemScale
	for item in inventory.getItemsAndGems():
		item.initBuildViewer()
	cursor.global_position = roundButton.rect_global_position - Vector2(3, 7)

func onRoundButtonPressed(roundButton, steamId, roundNum):
	if animation.current_animation == "":
		setSpecificBuild(steamId, roundNum)

func setSpecificBuild(steamId, _roundNum):
	roundNum = _roundNum
	curOpponentIndex = opponentSteamIds.find(steamId)
	updateBuild()

func updateMember(steamId = null):
	if steamId == null:
		for member in memberEntries:
			memberEntries[member].onFightFinished()
	else:
		memberEntries[steamId].onFightFinished()
	for member in memberEntries:
		memberEntries[member].updateRanking()

func close():
	InputBlocker.activate(InputBlocker.Source.PopupAnimation, false)
	animation.play("Hide")

func closed():
	InputBlocker.deactivate(InputBlocker.Source.PopupAnimation, false)
	InputBlocker.restoreAllControls(InputBlocker.Source.Popup)
	LOBBIES.onObBuildViewerClosed()
	queue_free()

func close_from_click_outside():
	if animation.is_playing():
		return
	close()
