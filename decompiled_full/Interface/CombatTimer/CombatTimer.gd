extends Node2D

const fatigueStartSound = preload("res://Assets/Sound/Fatigue.wav")
const FATIGUE_TIME = 17
const MAX_SPEED = 3.0

onready var fatigueStartTimer = $FatigueStartTimer
onready var timeLabel = $Time
onready var speedLabel = $Speed
onready var speedSlider = $SpeedSlider
onready var pauseButton = $PauseButton
onready var fastButton = $FastButton
onready var animation = $AnimationPlayer
onready var fatigueTickTimer = $FatigueTickTimer
onready var fatigueAnimation = get_parent().get_node("Fatigue/AnimationPlayer")
onready var fatigueLabel = get_parent().get_node("Fatigue/Counter")


var fatigueCounter: int
var speedBeforePause: = 1.0
var combatTime: float
var timeAdvance: float
var startSpeed: float

func _ready() -> void :
	set_physics_process(false)
	Game.connect("combat_scene_entered", self, "onCombatSceneEntered")
	set_process_unhandled_input(false)
	

func initialize():
	pauseButton.disabled = true
	fastButton.disabled = true
	
	if Game.curMode == Game.Mode.Lobbies:
		startSpeed = MAX_SPEED
		
		var lobbyTimer = RunDatabase.lobbies.lobbyTimer
		if lobbyTimer.remainingRoundTime < lobbyTimer.FORCE_SPEED_TIME + 3:
			forceMaxSpeed()
		else:
			initButtons()
			forceSpeed(startSpeed)
	else:
		initButtons()
		startSpeed = Settings.getVal(Settings.Setting.combat_speed)
		forceSpeed(startSpeed)
	
	speedLabel.text = "x" + String(startSpeed)
	Engine.time_scale = 1.0
	VisualServer.set_shader_time_scale(Engine.time_scale)
	timeAdvance = 0
	timeLabel.text = "0.0"

func initButtons():
	pauseButton.show()
	fastButton.show()
	speedSlider.modulate = Color.white

func forceSpeed(speed):
	speedSlider.editable = true
	speedSlider.max_value = MAX_SPEED
	speedSlider.set_value(speed)
	speedSlider.editable = false

func forceMaxSpeed():
	pauseButton.hide()
	fastButton.hide()
	speedSlider.modulate = Color(0.5, 0.5, 0.5)
	forceSpeed(MAX_SPEED)

func isMaxSpeedForced():
	return not pauseButton.visible

func getSpeed() -> float:
	return speedSlider.value

func getEffectiveTime() -> float:
	return Game.COMBAT_DELAY + combatTime + timeAdvance

func onCombatSceneEntered():
	Engine.time_scale = startSpeed
	
	
	if not isMaxSpeedForced():
		speedSlider.editable = true
		pauseButton.disabled = false
		fastButton.disabled = false
	
	VisualServer.set_shader_time_scale(Engine.time_scale)
	combatTime = 0.0
	set_process_unhandled_input(true)


func getName():
	return "Fatigue"

func combatEnd():
	fatigueCounter = 0
	fatigueStartTimer.stop()
	fatigueTickTimer.stop()
	Game.fatigueDamageSource.setDamage(0)
	animation.play("HideTimer")
	speedSlider.editable = false
	pauseButton.disabled = true
	fastButton.disabled = true
	fatigueAnimation.play("Hide")
	Engine.time_scale = 1
	VisualServer.set_shader_time_scale(Engine.time_scale)
	speedLabel.text = "x1"
	set_physics_process(false)
	set_process_unhandled_input(false)

func start():
	
	fatigueStartTimer.stop()
	fatigueTickTimer.stop()
	
	fatigueStartTimer.start(FATIGUE_TIME - 3)
	set_physics_process(true)

func _physics_process(delta: float) -> void :
	combatTime += delta
	updateTimer()

func _unhandled_input(event):
	if InputBlocker.isActive(): return
	
	if not isMaxSpeedForced():
		if event.is_action_pressed("combat_pause"):
			pause()
		elif event.is_action_pressed("combat_play"):
			unpause()
		elif event.is_action_pressed("combat_speed_up"):
			speedUp(0.5)
		elif event.is_action_pressed("combat_speed_down"):
			speedDown(0.5)

func updateTimer():
	timeLabel.text = "%1.1f" % combatTime

func getTimeStamp():
	return combatTime

func startFatigue():
	fatigueAnimation.play("Start")
	
	fatigueCounter = 0
	
	fatigueLabel.text = Util.tra("UI_Fatigue").format({"counter": 1})
	fatigueTickTimer.start(3)

func dealFatigueDamage():
	if fatigueCounter == 0:
		Sound.playSound(fatigueStartSound)
		EventBus.emitSignal(self, "fatigue_start")
	
	if combatTime < 60.0:
		fatigueCounter += 1 + floor(0.1 * fatigueCounter)
	else:
		fatigueCounter += 1 + floor(0.2 * fatigueCounter)
	
	Game.fatigueDamageSource.setDamage(fatigueCounter)
	
	EventBus.emitSignal(self, "fatigue_damage_changed")
	
	Game.OPPONENT.takeFatigueDamage()
	Game.PLAYER.takeFatigueDamage()
	fatigueAnimation.play("Tick")
	
	var counter
	if Game.PLAYER.getBonusFatigueDamage() != 0 or Game.OPPONENT.getBonusFatigueDamage() != 0:
		var playerFatigue = max(0, fatigueCounter + Game.PLAYER.getBonusFatigueDamage())
		var oppoFatigue = max(0, fatigueCounter + Game.OPPONENT.getBonusFatigueDamage())
		counter = String(playerFatigue) + "/" + String(oppoFatigue)
	else:
		counter = fatigueCounter
	fatigueLabel.text = Util.tra("UI_Fatigue").format({"counter": counter})
	fatigueTickTimer.start(1)

func hasFatigueStarted() -> bool:
	return fatigueCounter > 0

func advanceTime(time):
	timeAdvance += time
	
	var timeLeft = fatigueStartTimer.get_time_left()
	var newTime = timeLeft - time
	if newTime > 0:
		fatigueStartTimer.start(newTime)
	else:
		fatigueStartTimer.stop()
		
		startFatigue()
	
	Game.combatLog.snapshotGlobalStat(Game.combatLog.GlobalStat.TimeAdvance, timeAdvance)
	
func onSpeedChanged(value: float) -> void :
	if speedSlider.editable:
		Engine.time_scale = value
		VisualServer.set_shader_time_scale(Engine.time_scale)
		speedLabel.text = "x" + String(Engine.time_scale)
		speedBeforePause = 1.0

func onPauseButtonPressed():
	if Engine.time_scale == 0:
		unpause()
	else:
		pause()
	
	Game.onClickButton()

func pause():
	var speed = Engine.time_scale
	speedSlider.set_value(0)
	speedBeforePause = speed

func unpause():
	speedSlider.set_value(speedBeforePause)

func onFastButtonPressed():
	speedUp(1)
	Game.onClickButton()

func speedUp(amount):
	speedSlider.set_value(speedSlider.value + amount)

func speedDown(amount):
	speedSlider.set_value(speedSlider.value - amount)

func setTime(time):
	updateTimer()
