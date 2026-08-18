extends FocusGrabbingTextureButton

onready var combat = Game.combatSceneNode
onready var hideUILabel = $HideLabel
onready var animation = $AnimationPlayer

const closedEye = preload("res://Interface/Combat/Eye_closed.png")
const closedEyeHovered = preload("res://Interface/Combat/Eye_closed_hovered.png")
const openEye = preload("res://Interface/Combat/Eye_open.png")
const openEyeHovered = preload("res://Interface/Combat/Eye_open_hovered.png")

func _ready():
	set_process_input(false)

func showButton():
	set_process_input(true)
	disabled = false
	
	if (Game.getNumStartedRuns() >= 3 and 
		Game.getNumStartedRuns() < 10 and 
		not Game.isTutorialDone(Game.TutorialSteps.ViewCombat)):
		
		animation.play("Tutorial")

func hideButton():
	set_process_input(false)

func _input(event):
	if InputBlocker.isActive(): return
	if not has_focus():
		if event.is_action_pressed("ui_accept"):
			combat.skipIfPossible()

func toggleUI() -> void :
	if combat.UI.visible:
		combat.hideUI()
		Game.setTutorialDone(Game.TutorialSteps.ViewCombat)
		animation.play("RESET")
	else:
		combat.showUI()
	
	if combat.UI.visible:
		texture_normal = openEye
		texture_hover = openEyeHovered
		
		hideUILabel.translationKey = "BUTTON_HideUI"
		hideUILabel.updateText()
		
	else:
		texture_normal = closedEye
		texture_hover = closedEyeHovered
		
		hideUILabel.translationKey = "BUTTON_ShowUI"
		hideUILabel.updateText()
		
		
