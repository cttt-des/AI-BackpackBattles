extends Node2D

signal finished_loading_materials

const pixel_tex = preload("res://Assets/Pixel.png")

func _ready():
	# [ORACLE PATCH 记录 #7] 原版此脚本预编译粒子材质后延迟 8 帧发
	# finished_loading_materials（_ready 尾部）；Game.ready_deferred 在该信号上
	# yield，恢复后会走 loadArenaRunAndStartOnTitle → instanceCharacter →
	# PLAYER.INVENTORY.reset()，实测在神谕战斗进行中把玩家重置成默认开局。
	# 神谕直接发信号并终止函数（不再预编译材质、不再二次发信号）——
	# ready_deferred 的 yield 在信号已过后注册，从此永久挂起。
	emit_signal("finished_loading_materials")


func original_ready_disabled():
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
	
	
