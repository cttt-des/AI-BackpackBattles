extends Node2D

const normalFont = preload("res://Interface/Lobbies/LobbyTimerFont_normal.tres")
const hurryFont = preload("res://Interface/Lobbies/LobbyTimerFont_hurry.tres")
const countdownSound = preload("res://Assets/Sound/Countdown1.ogg")
const forceSpeedAni = preload("res://Interface/Lobbies/ForceSpeedAnimation.tscn")

const FRAMETIME: = 1.0 / 60.0
const FORCE_LOSE_TIME: = 10.0
const FORCE_TRANSITION_TIME: = 8.0
const FORCE_SPEED_TIME: = 45.0
const BASETIME = 1734611782
const PROGRESS_MODULATE_END = Color(2, 1.6, 0.8)

onready var LOBBIES = RunDatabase.lobbies

onready var minutesLabel_shop = $Minutes
onready var secondsLabel_shop = $Seconds
onready var colonLabel = $Label
onready var waitingLabel = $Waiting
onready var readyButton = $ReadyButton
onready var checkMark = $Checkmark
onready var readyCounter = $ReadyCounter
onready var particles = $Particles2D

onready var combatNode = $Combat
onready var minutesLabel_combat = $Combat / Minutes
onready var secondsLabel_combat = $Combat / Seconds
onready var colonLabel_combat = $Combat / Label

onready var animation = $Combat / AnimationPlayer
onready var shockwaveAni = $Shockwave / AnimationPlayer
onready var progressSprite = $Progress

var remainingRoundTime: float
var preciseTime: float = 0
var serverTime: int
var nextFightTime: float
var timerActive: = false
var curFont = normalFont
var shockwaveStarted = false
var displayTime: = - 1000
var progressTween

func _ready():
	
	LOBBIES.connect("update_ready_counter", self, "updateReadyCounter")
	LOBBIES.connect("all_end_results_received", self, "allEndResultsReceived")
	remove_child(combatNode)
	Game.combatSceneNode.aboveUINode.add_child(combatNode)
	
	Game.connect("shop_closed", self, "showCombatTimer")
	Game.connect("switch_to_shop", self, "hideCombatTimer")

func initTimer():
	if preciseTime == 0:
		preciseTime = Steam.getServerRealTime()


	
	

func showCombatTimer():
	animation.play("ShowTimer")
	

func hideCombatTimer():
	animation.play("HideTimer")
	showWaitLabel(false)

func updateTimer(timestamp: float):
	
	
	nextFightTime = timestamp + BASETIME
	
	
	
	var timeDif = nextFightTime - preciseTime
	setTimer(timeDif)
	print("update timer with diff ", timeDif)

func forwardTo(_remainingRoundTime: float):
	particles.activate()
	progressTween = Util.refreshTween(progressTween).set_parallel(true)
	if not progressSprite.visible:
		startProgressAni()
	animateProgress(_remainingRoundTime)
	
	if _remainingRoundTime < remainingRoundTime:
		nextFightTime = Steam.getServerRealTime() + _remainingRoundTime
		setTimer(_remainingRoundTime)

func setTimer(_remainingRoundTime: float):
	
	remainingRoundTime = _remainingRoundTime
	if remainingRoundTime < 0:
		
		showWaitLabel(true)


	
	timerActive = true
	updateTime()

func updateTime():
	
	
	var clamped = max(0, remainingRoundTime)
	var clampedFloored = int(clamped)
	
	
	if clampedFloored == displayTime + 1:
		return
	displayTime = clampedFloored
	
	var minutes = int(clamped / 60)
	var seconds = int(fmod(clamped, 60.0))
	
	minutesLabel_shop.text = String(minutes)
	secondsLabel_shop.text = "%02d" % seconds
	
	if clamped <= 10:
		setFont(hurryFont, Game.SOFTWHITE)
	else:
		setFont(normalFont, Game.BROWN)
	
	if clampedFloored == 10:
		if not shockwaveStarted:
			shockwaveStarted = true
			Util.callDelayed(self, "shockwave", 0.65)
	elif clampedFloored <= 9:
		if not progressSprite.visible:
			startProgressAni()
			progressTween = create_tween().set_parallel(true)
			animateProgress(clampedFloored)
			
	
	
	var combatTimerReady = (remainingRoundTime >= 0)
	minutesLabel_combat.visible = combatTimerReady
	secondsLabel_combat.visible = combatTimerReady
	colonLabel_combat.visible = combatTimerReady
	minutesLabel_combat.text = minutesLabel_shop.text
	secondsLabel_combat.text = secondsLabel_shop.text
	
	var forceLoseTime = FORCE_LOSE_TIME
	if Game.curRound == Game.MAX_ROUNDS_LOBBIES:
		forceLoseTime = 0
	
	
	if (remainingRoundTime <= FORCE_SPEED_TIME and 
		not Game.fightEnded and 
		not Game.combatTimer.isMaxSpeedForced()):
		print("force max speed")
		
		forceSpeedAnimation()
		Game.combatTimer.forceMaxSpeed()
	
	if (remainingRoundTime <= forceLoseTime and 
		not Game.fightEnded):
		print("force lose combat")
		Game.forceLoseCombat()
	
	elif (remainingRoundTime <= FORCE_TRANSITION_TIME and 
		Game.state == Game.State.Combat and 
		Game.fightEnded and 
		Game.curRound <= Game.MAX_ROUNDS_LOBBIES):
		
		print("force switch to shop")
		Game.combatSceneNode.forceSwitchToShop()
	
	elif (remainingRoundTime <= 0 and 
		Game.state == Game.State.Shop):
		
		timerActive = false
		Game.forceSwitchToCombat()
		showWaitLabel(true)

func shockwave():
	shockwaveAni.play("Tick")
	Sound.playSound(countdownSound)

func forceSpeedAnimation():
	if Game.combatTimer.getSpeed() != Game.combatTimer.MAX_SPEED:
		ObjectPool.playAnimation(forceSpeedAni, "ForceSpeed", Game.combatUINode)

func setFont(font, color):
	if font != curFont:
		curFont = font
		minutesLabel_shop.set("custom_fonts/font", font)
		minutesLabel_shop.set("custom_colors/font_color", color)
		secondsLabel_shop.set("custom_fonts/font", font)
		secondsLabel_shop.set("custom_colors/font_color", color)
		colonLabel.set("custom_fonts/font", font)
		colonLabel.set("custom_colors/font_color", color)

func startProgressAni():
	progressSprite.show()
	progressSprite.modulate = Color(1, 0.890196, 0.215686, 1.0)
	progressSprite.material.set_shader_param("revealState", 0.0)

func animateProgress(duration: float):
	progressTween.tween_property(progressSprite.material, 
		"shader_param/revealState", 1.0, duration)
	progressTween.tween_property(progressSprite, 
		"modulate", PROGRESS_MODULATE_END, duration)
	progressTween.tween_property(progressSprite, 
		"modulate", Color.transparent, 3).from(PROGRESS_MODULATE_END).set_delay(duration)

func showWaitLabel(showWait: bool):
	waitingLabel.visible = showWait
	minutesLabel_shop.visible = not showWait
	secondsLabel_shop.visible = not showWait
	colonLabel.visible = not showWait
	
	if showWait:
		checkMark.hide()
		readyButton.disable()
		readyCounter.hide()
	else:
		readyButton.enable()
		progressSprite.hide()
		shockwaveStarted = false

func _physics_process(delta):
	var previous = serverTime
	serverTime = Steam.getServerRealTime()
	if previous != serverTime:
		
		preciseTime = serverTime
	else:
		preciseTime += FRAMETIME
	
	
	
	
	if timerActive:
		var before = int(remainingRoundTime)
		remainingRoundTime = nextFightTime - preciseTime
		if before != int(remainingRoundTime):
			updateTime()

func allEndResultsReceived():
	timerActive = false
	animation.play("HideTimer")



func _notification(what):
	if what == NOTIFICATION_PREDELETE:
		combatNode.queue_free()
	
func disable():
	Util.disconnectAll(self)
	timerActive = false
	animation.play("HideTimer")
	Util.callDelayed_process(self, "queue_free", 1)


func onReadyPressed():
	if (Game.state == Game.State.Shop and 
		Game.canSwitchToCombat and 
		Game.draggedItem == null):
		
		checkMark.show()
		LOBBIES.setReady()
		readyButton.disable()

func updateReadyCounter():
	var numReady = LOBBIES.countReadyMembers()
	if numReady > 0:
		readyCounter.show()
		readyCounter.text = String(numReady) + "/" + String(LOBBIES.getNumMembers())

func getCurTime() -> float:
	return stepify(preciseTime - BASETIME, 0.01)
