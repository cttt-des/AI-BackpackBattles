extends Node2D

const colors = {
	Item.Affected.Primary: Color(1, 0.969516, 0.219608), 
	Item.Affected.Secondary: Color(0.219608, 1, 0.442142), 
	Item.Affected.Tertiary: Color(0.949219, 0.413429, 0.771319), 
	Item.Affected.Lightning: Color(0.949219, 0.752484, 0.413429)
}

const starTextures = {
	Item.Affected.Primary: preload("res://Interface/AffectsArrowPrimary.png"), 
	Item.Affected.Secondary: preload("res://Interface/AffectsArrowSecondary.png"), 
	Item.Affected.Tertiary: preload("res://Interface/AffectsArrowTertiary.png"), 
	Item.Affected.Lightning: preload("res://Interface/AffectsArrowLightning.png")
}

var poolingHandle
var line
var sortLength
var star

func preset():
	line = $Line2D
	star = $Star


func setPositions(item, end: Vector2):
	var start: Vector2 = item.global_position
	
	var minDist = 99999.9
	for cellPos in item.getCollisionPoints():
		var dist = cellPos.distance_to(end)
		if dist < minDist:
			start = cellPos
			minDist = dist
	
	
	
	var dif = start - end
	var dir = dif.normalized()
	sortLength = dif.length()
	
	
	end = start - dir * (40 + sortLength / 7)
	
	position = end
	line.points[0] = dir * 0.0
	line.points[1] = (start - end) - dir * 30.0
	
	star.position = line.points[0]
	star.look_at(star.global_position + dif)
	


func setColor(color: int):
	modulate = colors[color]
	star.texture = starTextures[color]

func getLength() -> float:
	return sortLength

func moveBy(vec: Vector2):
	position += vec
