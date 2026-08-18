extends AudioStreamPlayer
class_name LoanAudioStreamPlayer

var curOwner: Node2D

func _ready():
	connect("finished", self, "_finishedPlaying")
	curOwner = Sound.soundPlayers
	bus = "SFX"

func playSound(_stream: AudioStream, _volume: float = 0, 
						_pitch: float = 1) -> void :
	stream = _stream
	volume_db = _volume
	pitch_scale = _pitch
	playing = true

func _finishedPlaying() -> void :
	stream = null
	Sound.returnPlayer(self)

