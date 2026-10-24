extends Node2D

var poolingHandle
var label
var animation
var timer
var duration: float

func preset():
	label = $Label
	animation = $AnimationPlayer
	timer = $Timer

func setText(key: String):
	Util.localizeFonts(label)
	label.setTranslationKey(key)
	print("MSG: ", label.text)
	animation.play("Show")
	timer.start(duration)

func setParams(params):
	label.formatParams = params

func close():
	timer.stop()
	if animation.current_animation == "":
		animation.play("Hide")

func onClosed():
	animation.stop()
	ObjectPool.returnInstance(self)
