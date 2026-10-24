extends Node2D

signal returned_to_pool

var poolingHandle
var animation
var label

func preset():
	animation = $AnimationPlayer
	label = $Label
	
	Util.localizeFonts(label)
	
func showProgress(itemName: String, num: int, outOf: int, 
	ingredientCounter: Array) -> void :
	updateLabel(itemName, num, outOf, ingredientCounter)
	
	if num == 1:
		animation.play("ShowFast")
	else:
		var speed = 1.0 if ingredientCounter.empty() else 0.8
		animation.play("Show", - 1, speed)

func updateProgress(itemName: String, num: int, outOf: int, 
	ingredientCounter: Array) -> void :
	
	updateLabel(itemName, num, outOf, ingredientCounter)
	animation.play("Change")

const green = Color(0.535913, 0.982422, 0.443241)
const yellow = Color(1, 0.890196, 0)
const labelFormat = "[center][color=#{col}]{name}\n{num}/{outOf}[/color]{bonded}{missing}"
const bondedFormat = "\n[color=#{col}]{icon} {name} {num}/{outOf}"

const missingMark = preload("res://Interface/HookArrow.png")

func updateLabel(itemName: String, num: int, outOf: int, 
	ingredientCounter: Array):
	
	var color
	if num == outOf:
		color = green.to_html()
	else:
		color = Color.white.to_html()
	
	var bondedStr = ""
	var missingStr = ""
	













	
	for arr in ingredientCounter:
		missingStr += bondedFormat.format({
			"name": arr[0].getTranslatedName(), 
			"col": yellow.to_html(), 
			"num": arr[1], 
			"outOf": arr[2], 
			"icon": Util.imageToBbcode(missingMark.get_path(), 30)
		})
	
	label.bbcode_text = labelFormat.format({
		"col": color, 
		"name": itemName, 
		"num": num, 
		"outOf": outOf, 
		"bonded": bondedStr, 
		"missing": missingStr})
	
	animation.stop()
	label.rect_size.y = 0
	
func fade():
	if (animation.current_animation == "" or 
		Util.getRemainingAnimationTime(animation) > 0.3):
		animation.stop()
		animation.play("Fade")

func returnToObjectPool():
	emit_signal("returned_to_pool")
	ObjectPool.returnInstance(self)
