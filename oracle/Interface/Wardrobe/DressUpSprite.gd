extends Node2D

onready var character = get_parent().get_parent().get_parent()

var idleAnimationPlayers = []

func _ready():
	findIdleAnis(self)

func findIdleAnis(node):
	if node is AnimationPlayer and node.name.ends_with("Idle"):
		if is_instance_valid(node) and not node.is_queued_for_deletion():
			idleAnimationPlayers.push_back(node)
	for child in node.get_children():
		findIdleAnis(child)


func setSkin(slot: int, skinId: int):
	
	
	
	var aniTime = character.idleAnimation.current_animation_position
	
	var style = int(character.isChibi())
	var skin = SkinBook.getSkinFromId(character.getClass(), style, skinId)
	var skinInstance = skin.scene.instance()
	skinInstance.hide()
	Game.add_child(skinInstance)
	var skinSlotNodes = searchNodes(slot, skinInstance)
	var oldSlotNodes = searchNodes(slot, self)
	
	for node in skinSlotNodes:
		var pathToParent = skinInstance.get_path_to(node.get_parent())
		var path = skinInstance.get_path_to(node)
		
		
		var replacement = Node2D.new()
		replacement.name = node.name
		node.replace_by(replacement)
		var toReplace = get_node_or_null(path)
		
		if toReplace:
			toReplace.replace_by(node)
			oldSlotNodes.erase(toReplace)
			toReplace.queue_free()
		else:
			
			var newParent = get_node(pathToParent)
			newParent.add_child(node)
		
	
	skinInstance.queue_free()
	for leftOverNode in oldSlotNodes:
		leftOverNode.queue_free()
	
	idleAnimationPlayers.clear()
	findIdleAnis(self)
	
	character.idleAnimation.stop()
	character.idleAnimation.play("Idle")
	character.idleAnimation.seek(aniTime)
	syncIdleAnis()
	
func syncIdleAnis():
	if character.idleAnimation.current_animation == "Idle":
		var aniTime = character.idleAnimation.current_animation_position
		for player in idleAnimationPlayers:
			
			player.playback_speed = character.idleAnimation.playback_speed
			player.play("Idle")
			player.seek(aniTime)
	
var slotNodes = []

func searchNodes(slot, rootNode):
	slotNodes.clear()
	visitNode(slot, rootNode)
	return slotNodes.duplicate()
	
func visitNode(slot, node):
	if node.is_in_group(Game.slotNames[slot]):
		slotNodes.push_back(node)
	for child in node.get_children():
		visitNode(slot, child)
	






		


