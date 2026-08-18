extends RichTextLabel

export (Array, AudioStream) var sounds
export (float) var volume = - 6.0
export (float) var basePresentTime = 1.8

signal text_finished

enum DollarCommand{
	Pause = 0, 
	Speed = 1, 
	Highlight = 2
}

const BASE_LETTERDURATION = 0.07
const TEXT_SPEED = 1
const textSpeedFactors = [0.8, 1.5, 1.2]
var letterDuration: float
var soundQueued = false
var charactersPrintedLastFrame = 0
var tween
var dollarCommands = []
var audioPlayer = null

func ensureAudioPlayer():
	if audioPlayer == null:
		audioPlayer = AudioStreamPlayer.new()
		add_child(audioPlayer)
		audioPlayer.connect("finished", self, "onSoundFinished")
		audioPlayer.bus = "Voice"
	audioPlayer.stream = sounds[0]
	audioPlayer.volume_db = volume

func _ready() -> void :
	set_physics_process(false)
	if not sounds.empty():
		ensureAudioPlayer()






const highlightStart = "[b]"
const highlightEnd = "[/b]"

func showText(_text: String, presentTime = basePresentTime):
	
	_text = ToolTip.highlight(_text, false, true)
	
	
	bbcode_text = _text
	var text_without_bb = text
	
	
	
	handleDollarCommands(text_without_bb)
	
	bbcode_text = stripDollarCommands(_text)
	_text = text
	
	letterDuration = 1.0
	visible_characters = 0
	
	tween = create_tween()
	tween.set_pause_mode(SceneTreeTween.TWEEN_PAUSE_BOUND)

	var segmentStart = 0
	
	for command in dollarCommands:
		var segmentEnd = command[1]
		var numChars = segmentEnd - segmentStart
		segmentStart = segmentEnd
		
		if command[0] == DollarCommand.Pause:
			var talkTime = getTalkTime(numChars, letterDuration)
			tween.tween_property(self, "visible_characters", segmentEnd, 
				talkTime)
			tween.tween_property(self, "visible_characters", segmentEnd, 
				command[2])
			
		elif command[0] == DollarCommand.Speed:
			letterDuration = command[2]
			var talkTime = getTalkTime(numChars, letterDuration)
			tween.tween_property(self, "visible_characters", segmentEnd, 
				talkTime)
	
	
	var totalChars = text.length() + bbcode_text.countn("[img")
	
	var numChars = totalChars - segmentStart
	var talkTime = getTalkTime(numChars, letterDuration)
	tween.tween_property(self, "visible_characters", totalChars, talkTime)
	
	tween.tween_callback(self, "finished").set_delay((0.05 * talkTime + presentTime) / textSpeedFactors[TEXT_SPEED])
	charactersPrintedLastFrame = 0
	
	if audioPlayer:
		set_physics_process(true)


func getTalkTime(numChars, letterDur):
		return (numChars * BASE_LETTERDURATION) / (letterDuration * textSpeedFactors[TEXT_SPEED])

func _physics_process(delta: float) -> void :
	if visible_characters > charactersPrintedLastFrame:
		charactersPrintedLastFrame = visible_characters
		if audioPlayer.playing:
			soundQueued = true
		else:
			playSound()

func onSoundFinished():
	if soundQueued:
		playSound()
		soundQueued = false

func playSound():
	audioPlayer.stream = Util.pickRandomElement(sounds)
	audioPlayer.pitch_scale = Util.rng.randf_range(1.0, 1.3)
	audioPlayer.play()
	

func finished():
	stop()
	emit_signal("text_finished")

func stop():
	set_physics_process(false)
	Util.killTween(tween)
	tween = null
	if audioPlayer:
		audioPlayer.stop()

func handleDollarCommands(_text):
	dollarCommands.clear()
	var dollarPos = 0
	while true:
		dollarPos = _text.find("$", dollarPos)
		if dollarPos == - 1:
			break
		
		var refEndPos = _text.find(" ", dollarPos)
		var command = _text.substr(dollarPos + 1, refEndPos - dollarPos - 1)
		if command[0] == "p":
			
			var pauseLength = float(command.substr(1))
			dollarCommands.push_back([DollarCommand.Pause, dollarPos, pauseLength])
		elif command[0] == "s":
			
			var speed = float(command.substr(1))
			dollarCommands.push_back([DollarCommand.Speed, dollarPos, speed])
		
		_text = _text.substr(0, dollarPos) + _text.substr(refEndPos + 1, _text.length() - refEndPos)

func stripDollarCommands(_text):
	var dollarPos = 0
	while true:
		dollarPos = _text.find("$", dollarPos)
		if dollarPos == - 1:
			break
		
		var refEndPos = _text.find(" ", dollarPos)
		_text = _text.substr(0, dollarPos) + _text.substr(refEndPos + 1, _text.length() - refEndPos)
	return _text
