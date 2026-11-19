extends SceneTree

class Probe extends Node:
	var driver
	var id: String
	func _physics_process(_delta):
		driver.visit(id)

var nodes := {}
var visits := []


func _initialize():
	call_deferred("prepare")


func prepare():
	for id in ["controller", "late", "stopped", "toggled", "internal"]:
		var node := Probe.new()
		node.id = id
		node.driver = self
		root.add_child(node)
		node.set_physics_process(id != "late" and id != "internal")
		nodes[id] = node
	var timer := Timer.new()
	timer.one_shot = true
	timer.process_mode = Timer.TIMER_PROCESS_PHYSICS
	timer.connect("timeout", self, "enable_from_internal")
	root.add_child(timer)
	timer.start(0.001)


func enable_from_internal():
	nodes["internal"].set_physics_process(true)


func visit(id):
	visits.append(id)
	if id != "controller":
		return
	if visits.size() == 1:
		nodes["late"].set_physics_process(true)
		nodes["stopped"].set_physics_process(false)
		nodes["toggled"].set_physics_process(false)
		nodes["toggled"].set_physics_process(true)
		return
	var expected := ["controller", "toggled", "internal", "controller"]
	if visits != expected:
		printerr("Physics membership mismatch: ", visits)
		quit(1)
		return
	print("Physics membership contract: ", visits)
	quit()
