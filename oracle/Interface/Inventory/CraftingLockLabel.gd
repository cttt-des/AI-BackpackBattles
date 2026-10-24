extends Node2D

signal returned_to_pool

var poolingHandle
var animation
var label

func preset():
	animation = $AnimationPlayer
	label = $Label
	Util.localizeFonts(label)

func lock():
	label.text = Util.tra("LABEL_LockCombining")
	animation.play("Lock")

func unlock():
	label.text = Util.tra("LABEL_UnlockCombining")
	animation.play("Unlock")

func returnToObjectPool():
	emit_signal("returned_to_pool")
	ObjectPool.returnInstance(self)
