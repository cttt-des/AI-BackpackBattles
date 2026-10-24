extends Node2D

onready var sprite = $Tag
onready var label = $Cost
onready var animation = $Cost / AnimationPlayer

const tagTextures = [
	preload("res://Assets/Shop/RerollRopeLabel1.png"), 
	preload("res://Assets/Shop/RerollRopeLabel3.png"), 
	preload("res://Assets/Shop/RerollRopeLabel3.png")
]

func getColor(cost):
	var color
	if Game.getGold() < cost:
		color = Color(0.957031, 0.29989, 0.284119)
	else:
		if cost == 1:
			color = Color(1, 1, 1)
		elif cost == 2:
			color = Color(0.996094, 0.838942, 0.336571)
		else:
			color = Color(1, 0.639969, 0.291016)
	return color

func onGoldChanged():
	var cost = Game.shopSceneNode.getRerollCost()
	var color = getColor(cost)
	
	
	label.set("custom_colors/font_color", color)

func onCostChanged(cost, increased):
	label.set("custom_colors/font_color", getColor(cost))
	label.text = String(cost)
	sprite.texture = tagTextures[cost - 1]
	sprite.material.set_shader_param("progress", 0.0)
	sprite.material.set_shader_param("overlayTexture", tagTextures[min(cost, tagTextures.size() - 1)])
	animation.play("RESET")
	if increased:
		animation.play("PriceChanged")
