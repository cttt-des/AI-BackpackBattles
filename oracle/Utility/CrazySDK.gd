extends Node

signal ad_started
signal ad_finished
signal ad_error
signal ad_done

var SDK = null

var adStartedCallback
var adErrorCallback
var adFinishedCallback

var adCallbacks

func hasSDK() -> bool:
	return SDK != null

func _ready() -> void :
	if not OS.has_feature("crazygames"): return
	
	var window = JavaScript.get_interface("window")
	SDK = window.CrazyGames.SDK
	
	adStartedCallback = JavaScript.create_callback(self, "adStarted")
	adErrorCallback = JavaScript.create_callback(self, "adError")
	adFinishedCallback = JavaScript.create_callback(self, "adFinished")
	
	adCallbacks = JavaScript.create_object("Object")
	adCallbacks["adFinished"] = adFinishedCallback
	adCallbacks["adError"] = adErrorCallback
	adCallbacks["adStarted"] = adStartedCallback

func adStarted(args):
	print("[Godot] adStarted callback")
	emit_signal("ad_started")

func adError(error):
	print("[Godot] adError callback")
	emit_signal("ad_error", error)
	emit_signal("ad_done")

func adFinished(args):
	print("[Godot] adFinished callback")
	emit_signal("ad_finished")
	emit_signal("ad_done")

func midgameAd():
	if not SDK: return
	SDK.ad.requestAd("midgame", adCallbacks)

func rewardedAd():
	if not SDK: return
	SDK.ad.requestAd("rewarded", adCallbacks)

func gameplayStart():
	if not SDK: return
	SDK.game.gameplayStart()

func gameplayStop():
	if not SDK: return
	SDK.game.gameplayStop()

func happytime():
	if not SDK: return
	SDK.game.happytime()
