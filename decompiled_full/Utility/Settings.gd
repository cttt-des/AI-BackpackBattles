extends Node

var windowModes = [
	"windowed", 
	"fullscreen", 
	"borderless", 
	"borderless_maximized"
]

var resolutions = [
	"1280x1024", 
	"1920x1080", 
	"2560x1440", 
	"3840x2160"
]

const DMG_NR_ALL = 0
const DMG_NR_CHAR = 1
const DMG_NR_ITEMS = 2
const DMG_NR_NONE = 3

const PICK_OFFSET = 100.0



enum Setting{
	
	language, 
	opponent_chibis, 
	hide_names, 
	combat_speed, 
	highlight_slots, 
	bag_hotswapping, 
	damage_numbers, 
	stat_icons, 
	buff_labels, 
	text_effects, 
	pick_offset, 
	
	
	window_mode, 
	vsync, 
	resolution, 
	fps_limit, 
	reduce_fps_unfocused, 
	software_cursor, 
	cursor_size, 
	cursor_speed, 
	
	bgm_muted, 
	sfx_muted, 
	voice_muted, 
	bgm_volume, 
	sfx_volume, 
	voice_volume, 
	mute_unfocused
}

var settingKeys = Setting.keys()

var settings: Array
var defaults: Array
var initializing = true

func _init():
	settings.resize(Setting.size())
	initDefaults()

func initDefaults():
	defaults.resize(Setting.size())
	defaults[Setting.language] = "en"
	defaults[Setting.opponent_chibis] = false
	defaults[Setting.hide_names] = false
	defaults[Setting.combat_speed] = 1.0
	defaults[Setting.highlight_slots] = true
	defaults[Setting.bag_hotswapping] = false
	defaults[Setting.damage_numbers] = DMG_NR_ALL
	defaults[Setting.stat_icons] = true
	defaults[Setting.buff_labels] = true
	defaults[Setting.text_effects] = true
	
	if OS.has_feature("mobile"):
		defaults[Setting.pick_offset] = 1.0
	else:
		defaults[Setting.pick_offset] = 0.0
	
	
	defaults[Setting.window_mode] = "fullscreen"
	defaults[Setting.vsync] = true
	defaults[Setting.resolution] = "1920x1080"
	defaults[Setting.fps_limit] = 144
	defaults[Setting.reduce_fps_unfocused] = true
	defaults[Setting.software_cursor] = false
	defaults[Setting.cursor_size] = 0.5
	defaults[Setting.cursor_speed] = 1.0
	defaults[Setting.bgm_muted] = false
	defaults[Setting.sfx_muted] = false
	defaults[Setting.voice_muted] = false
	defaults[Setting.bgm_volume] = 0.3
	defaults[Setting.sfx_volume] = 0.3
	defaults[Setting.voice_volume] = 0.3
	defaults[Setting.mute_unfocused] = false

func _ready():
	loadConfig()
	call_deferred("ready_deferred")

func loadConfig():
	for setting in Setting:
		var index = Setting[setting]
		settings[index] = Game.getConfigValue("Options", setting, defaults[index])

func ready_deferred():
	call_deferred("initAll")

func initAll():
	for i in settings.size():
		initVal(i)
	
	initializing = false
	




func initVal(setting: int) -> void :
	var methodName = "init_" + settingKeys[setting]
	if has_method(methodName):
		call(methodName)
	else:
		setVal(setting, settings[setting])

func setValStr(setting: String, value) -> void :
	setVal(Setting[setting], value)

func setVal(setting: int, value) -> void :
	var methodName = "set_" + settingKeys[setting]
	if has_method(methodName):
		value = call(methodName, value)
	
		
	settings[setting] = value
	if value != defaults[setting] or setting == Setting.language:
		Game.setConfigValue("Options", settingKeys[setting], value)
	else:
		Game.eraseConfigValue("Options", settingKeys[setting])

func getValStr(setting: String):
	return getVal(Setting[setting])

func getVal(setting: int):
	var methodName = "get_" + settingKeys[setting]
	if has_method(methodName):
		return call(methodName)
	else:
		return settings[setting]





func init_language():
	setVal(Setting.language, Game.getConfigValue("Options", "language", Game.getDefaultLocale()))

func set_language(value):
	Game.setLocale(value)
	return value

func set_opponent_chibis(value):
	Game.call_deferred("setShowChibis", value)
	return value

func set_hide_names(value):
	
	if Game.OPPONENT:
		if value:
			Game.OPPONENT.hideCharacterName()
		else:
			Game.OPPONENT.showCharacterName()
	return value
	







func setWindowMode(fullscreen, borderless):
	if OS.is_window_fullscreen() != fullscreen:
		OS.set_window_fullscreen(fullscreen)
	
	if OS.get_borderless_window() != borderless:
		OS.set_borderless_window(borderless)
	
	if initializing:
		if not fullscreen:
			var screen = Game.getConfigValue("Options", "screen", null)
			if screen != null:
				OS.set_current_screen(screen)
			
			var windowPos = Game.getConfigValue("Options", "window_position", null)
			if windowPos != null:
				OS.set_window_position(windowPos)
			
			var windowSize = Game.getConfigValue("Options", "window_size", null)
			if windowSize != null:
				OS.set_window_size(windowSize)


func clipToScreen():
	
	if OS.current_screen > OS.get_screen_count() - 1:
		print("screen count exceeded - #screens: ", OS.get_screen_count())
		OS.current_screen = 0
	
	var screenSize = OS.get_screen_size()
	var windowSize = OS.get_window_size()
	windowSize.x = clamp(windowSize.x, 800.0, screenSize.x)
	windowSize.y = clamp(windowSize.y, 450.0, screenSize.y)
	OS.set_window_size(windowSize)
	
	var windowPos = OS.get_window_position()
	var screenPos = OS.get_screen_position()
	
	var screenBottomRight = screenPos + screenSize
	var windowBottomRight = windowPos + windowSize
	var overshoot = windowBottomRight - screenBottomRight
	if overshoot.x > 0:
		windowPos.x -= overshoot.x
	if overshoot.y > 0:
		windowPos.y -= overshoot.y
	
	windowPos.x = max(screenPos.x, windowPos.x)
	windowPos.y = max(screenPos.y, windowPos.y)
	OS.set_window_position(windowPos)

func set_window_mode(value):
	if not OS.has_feature("web"):
		
		match value:
			"fullscreen":
				setWindowMode(true, false)
			"borderless":
				setWindowMode(false, true)
				clipToScreen()
			"borderless_maximized":
				setWindowMode(true, true)
			"windowed":
				setWindowMode(false, false)
				clipToScreen()
	return value

func set_vsync(value):
	OS.vsync_enabled = value
	return value

func set_software_cursor(value):
	if value:
		Game.cursor = Game.Cursor.SOFTWARE_SMALL
	else:
		Game.cursor = Game.Cursor.HARDWARE_SMALL
	return value

func set_fps_limit(value):
	if value < 10 and value > 0:
		value = 10
	value = clamp(value, 0, 999)
	Engine.set_target_fps(value)
	return value

func set_resolution(value):



	return value




func set_cursor_size(value):
	Game.call_deferred("changeCursorSize", value)
	return value



func set_bgm_muted(value):
	Sound.muteBGM(value)
	return value

func set_sfx_muted(value):
	Sound.muteSFX(value)
	return value

func set_voice_muted(value):
	Sound.muteVoice(value)
	return value

func set_bgm_volume(value):
	Sound.setBGMVolume(value)
	return value

func set_sfx_volume(value):
	Sound.setSFXVolume(value)
	return value

func set_voice_volume(value):
	Sound.setVoiceVolume(value)
	return value
