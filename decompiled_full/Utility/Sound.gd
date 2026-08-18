extends Node2D

onready var soundPlayers = $SoundPlayers

onready var bgmPlayer1 = $BGMPlayer1
onready var bgmPlayer2 = $BGMPlayer2
onready var itemMovePlayer = $ItemMoveAudio

onready var MASTER_BUS = AudioServer.get_bus_index("Master")
onready var BGM_BUS = AudioServer.get_bus_index("BGM")
onready var SFX_BUS = AudioServer.get_bus_index("SFX")
onready var VOICE_BUS = AudioServer.get_bus_index("Voice")

var availableSoundPlayers: Array
var availableSoundPlayers_process: Array
var soundsPlayedThisFrame: Dictionary
var risingPitchSounds: Dictionary
var hoverSoundReadyTime = 0.0

var bgmTracks: Dictionary

var castSoundCounter: int = 0
var tween

const MIN_DB = - 60

func _ready():
	for i in range(30):
		var player = AudioStreamPlayer.new()
		player.name = "SoundPlayer" + String(i)
		soundPlayers.add_child(player)
		player.bus = "SFX"
		player.connect("finished", self, "returnPlayer", [player])
		player.pause_mode = Node.PAUSE_MODE_STOP
		availableSoundPlayers.append(player)
	for i in range(5):
		var player = AudioStreamPlayer.new()
		player.name = "SoundPlayer_process" + String(i)
		soundPlayers.add_child(player)
		player.bus = "SFX"
		player.pause_mode = Node.PAUSE_MODE_PROCESS
		player.connect("finished", self, "returnPlayer", [player])
		availableSoundPlayers_process.append(player)
		
	loadBGM()

func returnPlayer(player: AudioStreamPlayer):
	if player.pause_mode == PAUSE_MODE_PROCESS:
		availableSoundPlayers_process.insert(0, player)
	else:
		availableSoundPlayers.insert(0, player)



func getBGMVolume():
	return db2linear(AudioServer.get_bus_volume_db(BGM_BUS))

func setBGMVolume(vol: float):
	AudioServer.set_bus_volume_db(BGM_BUS, linear2db(vol))

func isBGMmuted():
	return AudioServer.is_bus_mute(BGM_BUS)

func muteBGM(mute: bool):
	AudioServer.set_bus_mute(BGM_BUS, mute)


func getSFXVolume():
	return db2linear(AudioServer.get_bus_volume_db(SFX_BUS))

func setSFXVolume(vol: float):
	AudioServer.set_bus_volume_db(SFX_BUS, linear2db(vol))

func isSFXmuted():
	return AudioServer.is_bus_mute(SFX_BUS)

func muteSFX(mute: bool):
	AudioServer.set_bus_mute(SFX_BUS, mute)


func getVoiceVolume():
	return db2linear(AudioServer.get_bus_volume_db(VOICE_BUS))
	
func setVoiceVolume(vol: float):
	AudioServer.set_bus_volume_db(VOICE_BUS, linear2db(vol))

func muteVoice(mute: bool):
	AudioServer.set_bus_mute(VOICE_BUS, mute)

func isVoiceMuted():
	return AudioServer.is_bus_mute(VOICE_BUS)
	

func fadeOutBGM(fadeOutTime: float = 0.5):
	
	Util.killTween(tween)
	tween = get_tree().create_tween().set_pause_mode(SceneTreeTween.TWEEN_PAUSE_PROCESS)
	tween.tween_method(self, "setLinearVolume", db2linear(bgmPlayer2.volume_db), 0.0, fadeOutTime, [bgmPlayer2])
	tween.parallel().tween_method(self, "setLinearVolume", db2linear(bgmPlayer1.volume_db), 0.0, fadeOutTime, [bgmPlayer1])
	
const crossFadeTime = 2.0

func playBGM(stream, volume = 0.0, fadeOutTime: float = 0.5):
	Util.killTween(tween)
	if fadeOutTime == 0:
		setStream(stream, bgmPlayer1, volume)
		setLinearVolume(db2linear(volume), bgmPlayer1)
	else:
		tween = create_tween()
		
		if bgmPlayer1.playing and bgmPlayer1.volume_db > - 30:
			tween.tween_method(self, "setLinearVolume", db2linear(bgmPlayer1.volume_db), 0.0, fadeOutTime, [bgmPlayer1])
			
		
		tween.tween_callback(self, "setStream", [stream, bgmPlayer1, db2linear(0)])
		var linearVolume = db2linear(volume)
		tween.tween_method(self, "setLinearVolume", 0.0, linearVolume, crossFadeTime, [bgmPlayer1])

func playBGM_loop(loop, intro, volume = 0.0, delay = 3.0):
	Util.killTween(tween)
	tween = create_tween().set_parallel(true)
	
	
	setStream(loop, bgmPlayer1, linear2db(0))
	setStream(intro, bgmPlayer2, volume)
	
	tween.tween_method(self, "setLinearVolume", 0.0, db2linear(volume), 2, [bgmPlayer1]).set_delay(delay)
	tween.tween_method(self, "setLinearVolume", db2linear(volume), 0.0, 2, [bgmPlayer2]).set_delay(delay)

func playSurvivalBGM(volume = 0.0):
	playBGM_loop(survivalBGM_loop, survivalBGM_intro, volume)

func playLobbyBGM(volume = 0.0):
	playBGM_loop(lobbyBGM_loop, lobbyBGM_intro, volume)

func playSwitchModeBGM(volume = 0.0):
	playBGM_loop(switchModeBGM_loop, switchModeBGM_intro, volume)

func playSubclassBGM(volume = 0.0):
	playBGM_loop(subclassBGM_loop, subclassBGM_intro, volume)

func playLastTryBGM(volume = 0.0):
	playBGM_loop(lastTryBGM_loop, lastTryBGM_intro, volume)


func setLinearVolume(vol: float, player: AudioStreamPlayer):
	player.volume_db = linear2db(vol)

func setStream(stream, bgmPlayer, volume):
	bgmPlayer.stream = stream
	bgmPlayer.volume_db = volume
	bgmPlayer.play()
	

func setMuffledSound(muffled: bool):
	AudioServer.set_bus_effect_enabled(BGM_BUS, 1, muffled)

func playRising(stream: AudioStream, volume: float = 0, pitch: float = 1, process_when_paused = false):
	
	var pitchData
	if risingPitchSounds.has(stream):
		pitchData = risingPitchSounds[stream]
	else:
		pitchData = PitchData.new()
		risingPitchSounds[stream] = pitchData
	
	var stackedPitch = pitchData.play()
	
	if process_when_paused:
		return playSound_process(stream, volume, stackedPitch * pitch)
	else:
		return playSound(stream, volume, stackedPitch * pitch)

func playSound(stream: AudioStream, volume: float = 0, pitch: float = 1):
	if availableSoundPlayers.size() > 0:
		if not soundsPlayedThisFrame.has(stream):
			var player = availableSoundPlayers.pop_back()
			player.stream = stream
			player.volume_db = volume
			player.pitch_scale = pitch
			player.playing = true
			soundsPlayedThisFrame[stream] = player
			return player
	return null
	
const loopFadeInTime = 0.1
const loopFadeOutTime = 0.2

func playLooping(stream: AudioStream, duration: float, volume: float = 0, pitch: float = 1):
	var player = playSound(stream, volume, pitch)
	if player:
		var tween2 = get_tree().create_tween().set_pause_mode(SceneTreeTween.TWEEN_PAUSE_STOP)
		tween2.tween_method(self, "setLinearVolume", 0.0, db2linear(volume), loopFadeInTime, [player])
		var delay = duration - loopFadeInTime - loopFadeOutTime
		tween2.tween_method(self, "setLinearVolume", db2linear(volume), 0.0, loopFadeOutTime, [player]).set_delay(delay)
		tween2.tween_callback(self, "returnPlayer", [player]).set_delay(duration)

	return player
	

func playSound_process(stream: AudioStream, volume: float = 0, pitch: float = 1):
	if availableSoundPlayers_process.size() > 0:
		if not soundsPlayedThisFrame.has(stream):
			var player = availableSoundPlayers_process.pop_back()
			player.stream = stream
			player.volume_db = volume
			player.pitch_scale = pitch
			player.playing = true
			soundsPlayedThisFrame[stream] = player
			return player
	return null
	
func _physics_process(_delta):
	soundsPlayedThisFrame.clear()


const titleBGM = preload("res://Assets/Sound/BGM/Medieval Vol. 2 6.mp3")
const shopBGM = preload("res://Assets/Sound/BGM/Song_of_Heroes.ogg")
const battleBGM = preload("res://Assets/Sound/BGM/Action 4 (Loop).mp3")
const battleBGM_survival = preload("res://Assets/Sound/BGM/Action 1 Loop.ogg")
const survivalBGM_intro = preload("res://Assets/Sound/BGM/Jolly Tavern of Vicious Folkalore - Start.ogg")
const survivalBGM_loop = preload("res://Assets/Sound/BGM/Jolly Tavern of Vicious Folkalore - Loop.ogg")
const postFightBGM = preload("res://Assets/Sound/BGM/Medieval 6.ogg")
const postFightBGM_survival = preload("res://Assets/Sound/BGM/Ambient 6.ogg")
const lobbyBGM_intro = preload("res://Assets/Sound/BGM/Check-In with Drinks and Slices - Start.ogg")
const lobbyBGM_loop = preload("res://Assets/Sound/BGM/Check-In with Drinks and Slices - Loop.ogg")
const switchModeBGM_intro = preload("res://Assets/Sound/BGM/Valhallas Spa and Rubber Ducks - Start.ogg")
const switchModeBGM_loop = preload("res://Assets/Sound/BGM/Valhallas Spa and Rubber Ducks - Loop.ogg")
const subclassBGM_intro = preload("res://Assets/Sound/BGM/This counts as a Victory - Start.ogg")
const subclassBGM_loop = preload("res://Assets/Sound/BGM/This counts as a Victory - Loop.ogg")
const lastTryBGM_intro = preload("res://Assets/Sound/BGM/Who Brought Bananas To A Sword Fight - Start.ogg")
const lastTryBGM_loop = preload("res://Assets/Sound/BGM/Who Brought Bananas To A Sword Fight - Loop.ogg")


func loadBGM():
	pass



class PitchData:
	var lastPlayedTime: float = 0
	var counter = 0
	
	func play():
		if Util.time <= lastPlayedTime + 0.5:
			if Util.time != lastPlayedTime:
				counter += 1
		else:
			counter = 0
		
		lastPlayedTime = Util.time
			
		
		counter = counter % 16
		var activeCounter
		if counter > 8:
				activeCounter = 16 - counter
		else:
			activeCounter = counter
		
		var pitch: float = 1 + activeCounter * 0.0625
		return pitch
