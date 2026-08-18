extends Node

var instances: Dictionary

func insertInstance(instance, scene: PackedScene):
	var existingInstances = instances.get(scene, null)
	if existingInstances != null:
		existingInstances.push_back(instance)
	else:
		instances[scene] = [instance]

func prepare(scene: PackedScene, number: int):
	var existingInstances = instances.get(scene, null)
	
	for i in number:
		var instance = scene.instance()
		instance.preset()
		if "poolingHandle" in instance:
			instance.poolingHandle = scene
		
		if existingInstances != null:
			existingInstances.push_back(instance)
		else:
			instances[scene] = [instance]

func instance(scene: PackedScene):
	var existingInstances = instances.get(scene, null)
	if existingInstances != null:
		var instance = existingInstances.pop_back()
		if existingInstances.empty():
			instances.erase(scene)
		instance.request_ready()
		return instance
	else:
		
		var instance = scene.instance()
		instance.preset()
		if "poolingHandle" in instance:
			instance.poolingHandle = scene
		return instance

func returnInstance(instance: Node, scene: PackedScene = null):
	if not is_instance_valid(instance): return
	



	
	if not scene:
		scene = instance.poolingHandle
	
	instance.get_parent().remove_child(instance)
	var existingInstances = instances.get(scene, null)
	if existingInstances != null:
		existingInstances.push_back(instance)
	else:
		instances[scene] = [instance]

func clear():
	for arr in instances:
		for instance in arr:
			instance.queue_free()
	
	instances.clear()


func returnAfter(delay: float, instance: Node, scene: PackedScene = null):
	Util.callDelayed_process(self, "returnInstance", delay, [instance, scene])

func particleOneShot(particleScene, parent, globalPos = null):
	
	var particles = instance(particleScene)
	parent.add_child(particles)
	particles.restart()
	var spawnTime = particles.lifetime * (1.0 - particles.explosiveness)
	var lifeTime = particles.lifetime
	var extraTime = 0.0
	returnAfter(extraTime + (spawnTime + lifeTime) / particles.speed_scale, particles)
	if globalPos != null:
		particles.global_position = globalPos
	return particles

func playAnimation(animationScene, animationName, parent, belowNode = null):
	var ani = instance(animationScene)
	if belowNode != null:
		parent.add_child_below_node(belowNode, ani)
	else:
		parent.add_child(ani)
	ani.get_node("AnimationPlayer").play(animationName)
	return ani

