extends SceneTree

class Observer extends Node:
	var frame := 0
	func _ready():
		var timer = Timer.new()
		timer.one_shot = true
		add_child(timer)
		timer.connect("timeout", self, "mark", ["idle Timer"])
		timer.start(0.001)
		get_tree().create_timer(0.001, false).connect("timeout", self, "mark", ["SceneTreeTimer"])
		var tween = create_tween()
		tween.tween_interval(0.001)
		tween.tween_callback(self, "mark", ["SceneTreeTween"])
	func mark(label):
		print("[ORDER] ", label, " process_count=", frame)
	func _process(_delta):
		frame += 1
		mark("Node._process")
		if frame == 3:
			get_tree().call_deferred("quit")

func _initialize():
	root.add_child(Observer.new())
