extends Node2D

signal closed

const bubbles = [
	preload("res://Assets/Shop/Shopkeeper/Speechbubble4.png"), 
	preload("res://Assets/Shop/Shopkeeper/Speechbubble3.png"), 
	preload("res://Assets/Shop/Shopkeeper/Speechbubble2.png"), 
	preload("res://Assets/Shop/Shopkeeper/Speechbubble1.png"), 
	preload("res://Assets/Shop/Shopkeeper/Speechbubble5.png"), 
	preload("res://Assets/Shop/Shopkeeper/Speechbubble6.png")
]

const tutorialDoneSound = preload("res://Assets/Sound/Chime2.mp3")

var speaking = false
var sequenceNumber = 0
var curTutorialStep
onready var speechBubble = $Speechbubble
onready var textbox = $RichTextLabel
onready var font = textbox.get("custom_fonts/normal_font")
onready var animation = $AnimationPlayer

onready var tutorialAnimation = $Tutorial / AnimationPlayer

func _ready() -> void :
	get_viewport().connect("size_changed", self, "resizeTextbox")

func say(text, presentTime = textbox.basePresentTime, tutorialStep = null):
	if animation.current_animation == "" and not isSpeaking():
		
		curTutorialStep = tutorialStep
		showTextbox(text, presentTime)
	else:
		Util.callDelayed(self, "say", 0.5, [text, presentTime, tutorialStep])

func getSequenceNumber():
	return sequenceNumber
	
func showTextbox(text, presentTime):
	textbox.show()
	speaking = true
	sequenceNumber += 1
	textbox.set_end(Vector2(textbox.get_end().x, textbox.rect_position.y))
	textbox.showText("[riseup]" + text, presentTime)
	Util.callNextFrame(self, "actuallyShowTextbox", [sequenceNumber])
	

func actuallyShowTextbox(forSequenceNumber):
	if sequenceNumber != forSequenceNumber: return
	Util.callNextFrame(self, "resizeTextbox")
	animation.play("Show")
	if curTutorialStep != null:
		tutorialAnimation.play("Idle")
		Game.connect("tutorial_done", self, "onTutorialDone")
		

func resizeTextbox():
	var numLines = round(textbox.rect_size.y / 34.0)
	Util.eassert(numLines - 1 < bubbles.size())
	numLines = clamp(numLines, 1, bubbles.size())
	
	speechBubble.texture = bubbles[numLines - 1]

func onTextFinished():
	animation.play("Hide")

func onAnimationFinished(aniName):
	if aniName == "Hide":
		speaking = false
		tutorialAnimation.play("RESET")
		curTutorialStep = null
		emit_signal("closed")
		Util.tryDisconnect(Game, "tutorial_done", self, "onTutorialDone")
		textbox.hide()
		
		

func isSpeaking() -> bool:
	return speaking

func shutUp():
	textbox.stop()
	onTextFinished()

func onTutorialDone(stepDone):
	if stepDone == curTutorialStep:
		tutorialAnimation.play("Check", 0.3)
		Sound.playSound(tutorialDoneSound)
		curTutorialStep = null

func isGivingTutorial() -> bool:
	return curTutorialStep != null
