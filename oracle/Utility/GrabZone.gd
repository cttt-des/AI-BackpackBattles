extends Area2D

func _process(delta):
	global_position = Vector2(300, 300)

func onAreaEntered(area):
	var item = area.get_parent()
	item.hover()

func onAreaExited(area):
	var item = area.get_parent()
	item.hoverEnd()
