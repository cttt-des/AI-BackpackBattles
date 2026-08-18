extends Node2D

const openHeight = 110.0
const hiddenHeight = 50.0
const windParticles = preload("res://Interface/WindParticles.tscn")
const windSound = preload("res://Assets/Sound/Swoosh1.wav")

onready var panel = $Panel
onready var toolbarButton = $ToolbarButton
onready var closedY: = position.y
onready var xPos: = position.x


var particleReadyTime = 0.0
var isOpen: = false
var tween: SceneTreeTween
var nodesToHide: Array

onready var buttons = [
	$UndoButton, $RedoButton, $PushToStorageButton, 
	$ToolbarButton, $GridStorageButton, 
	$EditModeButtons / Default, $EditModeButtons / BagLayer, $EditModeButtons / ItemLayer]
onready var tutorialAni = $AnimationPlayer

func _ready():
	set_process(false)
	position.y = closedY + hiddenHeight
	
	toolbarButton.connect("pressed", self, "onToolbarButtonPressed")
	$UndoButton.connect("pressed", self, "onUndoPressed")
	$RedoButton.connect("pressed", self, "onRedoPressed")
	$PushToStorageButton.connect("pressed", self, "onPushToStoragePressed")
	$GridStorageButton.connect("toggled", self, "onGridStoragePressed")
	Game.gridStorage.connect("toggled", self, "onGridStorageToggled")
	Game.undoStack.connect("state_added", self, "checkUndoRedo")
	Game.undoStack.connect("state_changed", self, "checkUndoRedo")
	
	Game.connect("return_to_title", self, "onShopToTitle")
	Game.connect("switching_to_combat", self, "onShopToCombat")
	Game.connect("combat_scene_entered", self, "onCombatEntered")
	Game.connect("title_to_shop", self, "onTitleToShop")
	Game.connect("switch_to_shop", self, "onCombatToShop")
	Game.connect("menu_open", self, "onMenuOpened")
	Game.connect("warp_cursor_shop", self, "onCursorWarp")
	
	for child in get_children():
		if (child is CanvasItem and 
			child != panel and 
			child != toolbarButton):
			nodesToHide.push_back(child)
			child.hide()

func onShopToTitle():
	tween = Util.refreshTween(tween)
	tween.tween_property(self, "position:y", closedY + hiddenHeight, 0.1)

func onShopToCombat():
	show()
	set_process(true)

func onCombatEntered():
	hide()
	set_process(false)

func onTitleToShop():
	unhide()

func unhide():
	show()
	tween = Util.refreshTween(tween)
	var height = closedY
	if isOpen:
		height -= openHeight
	tween.tween_property(self, "position:y", height, 0.15)

func onCombatToShop():
	position.y = closedY + hiddenHeight
	position.x = xPos
	unhide()
	
	if (Game.getNumStartedRuns() > 3 and 
		not Game.isTutorialDone(Game.TutorialSteps.Toolbar)):
		
		tutorialAni.play("Tutorial")

func _process(delta):
	position.x = Game.shopSceneNode.position.x + xPos

func onToolbarButtonPressed():
	if isOpen:
		close()
	else:
		open()

func isInteractable() -> bool:
	return ( not InputBlocker.isActive() and 
			Game.draggedItem == null and 
			Game.isShopActive())

func open():
	if not isInteractable(): return
	
	isOpen = true
	toolbarButton.flip_v = true
	
	for node in nodesToHide:
		node.show()
	
	tween = Util.refreshTween(tween)
	tween.tween_property(self, "position:y", closedY - openHeight, 0.1)
	
	Game.setTutorialDone(Game.TutorialSteps.Toolbar)
	tutorialAni.play("RESET")

func close():
	isOpen = false
	toolbarButton.flip_v = false
	tween = Util.refreshTween(tween)
	tween.tween_property(self, "position:y", closedY, 0.1)
	tween.tween_callback(self, "closeFinished")

func closeFinished():
	for node in nodesToHide:
		node.hide()

func onUndoPressed():
	if not isInteractable(): return
	
	Game.undoStack.undo()

func onRedoPressed():
	if not isInteractable(): return
	
	Game.undoStack.redo()

func onPushToStoragePressed():
	if not isInteractable(): return
	
	Game.cancelSwitch()
	Game.STORAGEBOX.pushAllToStorage()
	Sound.playSound(windSound)
	if Util.time >= particleReadyTime:
		ObjectPool.particleOneShot(windParticles, get_parent())
		particleReadyTime = Util.time + 0.2

func _unhandled_input(event):
	if not isInteractable(): return
	if Util.isActionPressed_event(event, "push_all_to_storage"):
		onPushToStoragePressed()

func checkUndoRedo():
	$UndoButton.disabled = not Game.undoStack.canUndo()
	$RedoButton.disabled = not Game.undoStack.canRedo()

func onMenuOpened():
	
	
	for button in buttons:
		button.onHoverEnd()



	hide()
	show()

func onGridStoragePressed(toggleState):
	if toggleState:
		Game.gridStorage.open()
	else:
		Game.gridStorage.close()

func onGridStorageToggled():
	$GridStorageButton.set_pressed(Game.gridStorage.visible)

func onCursorWarp():
	if isOpen:
		for button in buttons:
			Game.addPointOfInterest(button.rect_global_position + button.rect_size * 0.5)
				
	else:
		Game.addPointOfInterest(toolbarButton.rect_global_position + toolbarButton.rect_size * 0.5)
		
