extends Node2D

signal finished_loading_materials

const pixel_tex = preload("res://Assets/Pixel.png")

func _ready():
	

	var counter = 0
	var dir = Directory.new()
	var directories = []
	var files = []
	if dir.open("res://") == OK:
		dir.list_dir_begin(true, false)
		Util.addDirectoryContents(dir, files, directories)
		
		for fileName in files:
			if fileName.ends_with("Particles.material"):
				
				var sprite = Sprite.new()
				sprite.texture = pixel_tex
				add_child(sprite)
				
				sprite.position = Vector2(500, 500)
				sprite.set_material(load(fileName))
				counter += 1
				
			elif fileName.ends_with(".material"):
				
				var particles = Particles2D.new()
				particles.texture = pixel_tex
				particles.position = Vector2(1000, 500)
				add_child(particles)
				particles.set_process_material(load(fileName))
				counter += 1
			
			if counter > 10:
				counter = 0
				
				
				
				
			
	yield(get_tree(), "idle_frame")
	yield(get_tree(), "idle_frame")
	yield(get_tree(), "idle_frame")
	yield(get_tree(), "idle_frame")
	yield(get_tree(), "idle_frame")
	yield(get_tree(), "idle_frame")
	yield(get_tree(), "idle_frame")
	yield(get_tree(), "idle_frame")
	queue_free()
	emit_signal("finished_loading_materials")
	
	
