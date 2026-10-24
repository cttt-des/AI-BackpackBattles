extends Node2D


export (int, 200) var numShards = 20
export (float) var threshhold = 10.0
export (float) var min_impulse = 50.0
export (float) var max_impulse = 200.0
export (float) var lifetime = 5.0
export var display_triangles = false

const SHARD = preload("res://Utility/Shard.tscn")

var triangles = []
var shards = []

func _ready() -> void :
	if get_parent() is Sprite:
		var _rect = get_parent().get_rect()
		var points = []
		
		points.append(_rect.position)
		points.append(_rect.position + Vector2(_rect.size.x, 0))
		points.append(_rect.position + Vector2(0, _rect.size.y))
		points.append(_rect.end)

		
		for i in numShards:
			var p = _rect.position + Vector2(rand_range(0, _rect.size.x), rand_range(0, _rect.size.y))
			
			if p.x < _rect.position.x + threshhold:
				p.x = _rect.position.x
			elif p.x > _rect.end.x - threshhold:
				p.x = _rect.end.x
			if p.y < _rect.position.y + threshhold:
				p.y = _rect.position.y
			elif p.y > _rect.end.y - threshhold:
				p.y = _rect.end.y
			points.append(p)

		
		var delaunay = Geometry.triangulate_delaunay_2d(points)
		for i in range(0, delaunay.size(), 3):
			triangles.append([points[delaunay[i + 2]], points[delaunay[i + 1]], points[delaunay[i]]])
		
		print(triangles.size())
		
		
		var texture = get_parent().texture
		for t in triangles:
			var center = Vector2((t[0].x + t[1].x + t[2].x) / 3.0, (t[0].y + t[1].y + t[2].y) / 3.0)

			var shard = SHARD.instance()
			shard.position = center
			shard.hide()
			shards.append(shard)

			
			shard.get_node("Polygon2D").texture = texture
			shard.get_node("Polygon2D").polygon = t
			shard.get_node("Polygon2D").position = - center

			







		update()
		call_deferred("add_shards")


func add_shards() -> void :
	for s in shards:
		get_parent().add_child(s)


func shatter() -> void :
	
	
	for s in shards:
		var direction = Vector2.UP.rotated(rand_range(0, 2 * PI))
		var impulse = rand_range(min_impulse, max_impulse)
		s.apply_central_impulse(direction * impulse)
		s.sleeping = false
		
		s.show()
	$DeleteTimer.start(lifetime)


func _on_DeleteTimer_timeout() -> void :
	queue_free()


func _draw() -> void :
	if display_triangles:
		for i in triangles:
			draw_line(i[0], i[1], Color.white, 1)
			draw_line(i[1], i[2], Color.white, 1)
			draw_line(i[2], i[0], Color.white, 1)
