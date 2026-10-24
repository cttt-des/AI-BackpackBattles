extends FocusGrabbingButton

const activateTime = 0.5
const hoveredTexture = preload("res://Assets/Shop/Sign1_hovered.png")
const clickSound = preload("res://Assets/Sound/Thud5.wav")

export var progress: float

onready var animation = $AnimationPlayer
onready var normalTexture = icon
onready var progressMat = $Progress.material
onready var pathFollow = $Path / PathFollow2D
onready var pathParticles = $Path / PathFollow2D / PathParticles
onready var storageHint = get_parent().get_node("Hints/StorageHint")
onready var storageHintAni = storageHint.get_node("AnimationPlayer")
onready var lampButton = get_parent().get_node("Lamp/Button")

var isPressed = false
var hovered = false
var enabled = true
var willFaceNoConnectionDarkReflection: bool

func _ready() -> void :
	Game.connect("run_started", self, "onRunStarted")
	Game.connect("switch_to_shop", self, "reset")
	Game.connect("warp_cursor_shop", self, "onCursorWarp")
	set_process(false)

func onRunStarted():
	visible = (Game.curMode != Game.Mode.Lobbies)

func reset():
	set_pressed_no_signal(false)
	isPressed = false
	onHoverEnd()
	

func onHover():
	.onHover()
	if not hovered:
		hovered = true
		if enabled:
			Game.onHoverInteractable(self)
			icon = hoveredTexture

func onHoverEnd():
	.onHoverEnd()
	if hovered:
		hovered = false
		if enabled:
			icon = normalTexture
			Game.onHoverInteractableEnd(self)

func onButtonDown():
	if enabled:
		isPressed = true

func onButtonUp():
	isPressed = false

func _unhandled_input(event):
	if InputBlocker.isActive(): return
	
	if Util.isActionPressed_event(event, "start_battle"):
		activateButton()

func onPressed():
	if enabled and hovered:
		if Util.time > Game.lastItemDropTime + 0.5:
			activateButton()

func _gui_input(event):
	if event is InputEventScreenTouch and event.pressed:
		isPressed = true


func activateButton():
	if Game.isSwitchToCombatPossible():
		
		var pullButtons = get_tree().get_nodes_in_group("PullButton")
		for button in pullButtons:
			if button.isGrabbed():
				return
		
		if Game.canCancelSwitch:
			Game.cancelSwitch()
		else:
			willFaceNoConnectionDarkReflection = false
			
			if RunDatabase.getParsedRuns().empty():
				
				if not RunDatabase.hasConnected():
					willFaceNoConnectionDarkReflection = true
					if Game.curMode == Game.Mode.Ranked:
						Game.showWarning("HINT_NoConnection_Ranked", 
							null, 
							"BUTTON_Cancel")
					else:
						Game.showWarning("HINT_NoConnection", 
							"BUTTON_FaceDarkReflection", 
							"BUTTON_Cancel")
				else:
					
					Game.showWarning("HINT_NoOpponents", 
							"BUTTON_FaceDarkReflection", 
							"BUTTON_Cancel")
			elif ( not Game.wasRunContinued() and 
				Game.shopSceneNode.itemsBoughtThisRound == 0 and 
				Game.shopSceneNode.rerollsThisRound == 0 and 
				Game.getGold() >= 5 and 
				not ItemBook.isItemOwned(ItemBook.presentDescriptor) and 
				not ItemBook.isItemOwned(ItemBook.bagOfGivingDescriptor)):
					Game.showWarning("HINT_BoughtNothing", 
						"BUTTON_Confirm", 
						"BUTTON_Cancel")
			else:
				Game.switchToCombat()
				Sound.playSound(clickSound, 6)
				showStorageHint()
				if animation.current_animation_position > 0.61:
					activateParticles()

func playSwitchSound():
	Sound.playSound(Game.shopSceneNode.shopOpenSound, 0, 0.8)

func cancelSwitch():
	pathParticles.deactivate()
	set_process(false)

func finishSwitchingToCombat():
	pathParticles.deactivate()
	
	if willFaceNoConnectionDarkReflection:
		RunDatabase.facedNoConnectionDarkReflection += 1
	
	if OS.has_feature("crazygames"):
		CrazySDK.connect("ad_done", self, "onAdFinished", [], CONNECT_ONESHOT)
		InputBlocker.activate(InputBlocker.Source.SceneSwitch)
		Game.pause(Game.PauseSource.Ad)
		CrazySDK.midgameAd()
	else:
		Game.finishSwitchingToCombat()

func onAdFinished():
	Game.unpause(Game.PauseSource.Ad)
	Game.finishSwitchingToCombat()
	
func activateParticles():
	if Game.canCancelSwitch:
		set_process(true)
		pathParticles.activate()

func _process(delta: float) -> void :
	
	pathFollow.unit_offset = progress






func disable():
	onHoverEnd()
	
	if Game.canCancelSwitch:
		Game.cancelSwitch()
	enabled = false
	InputBlocker.setMouseFilter(self, Control.MOUSE_FILTER_IGNORE)
	InputBlocker.setMouseFilter(lampButton, Control.MOUSE_FILTER_IGNORE)



func enable():
	enabled = true
	InputBlocker.setMouseFilter(self, Control.MOUSE_FILTER_STOP)
	InputBlocker.setMouseFilter(lampButton, Control.MOUSE_FILTER_STOP)


	if hovered:
		onHover()

func showStorageHint():
	storageHint.bbcode_text = "[center]"
	var itemsInStorage = Game.STORAGEBOX.getItems().size()
	if itemsInStorage > 0:
		var key = "HINT_Storage"
		if itemsInStorage == 1:
			key = "HINT_Storage_Single"

		storageHint.bbcode_text += Util.tra(key).format({
			"num": "[b]" + Util.wrapInColor(str(itemsInStorage), Util.paramColor) + "[/b]"
		})
		storageHintAni.play("Show")
		
	if CustomRules.isSwitchMode():
		if itemsInStorage > 0:
			var switchModeHint1 = Util.tra("HINT_SwitchModeStorage")
			storageHint.bbcode_text += "\n" + Util.wrapInColor(switchModeHint1, Util.red)
		
		if Game.getGold() > 0:
			var switchModeHint2 = Util.tra("HINT_SwitchModeGold").replace("$gold", Util.getIcon("gold"))
			storageHint.bbcode_text += "\n" + Util.wrapInColor(switchModeHint2, Util.red)
			storageHintAni.play("Show")
			
		
func onCursorWarp():
	Game.addPointOfInterest(rect_global_position + rect_pivot_offset)
