extends Area2D

func _ready():
	onTitleEntered()
	Game.connect("title_to_shop", self, "onTitleLeft")
	Game.connect("returned_to_title", self, "onTitleEntered")

func onTitleEntered():
	Util.tryConnect(self, "body_entered", self, "onBodyEntered")
	set_physics_process(true)

func onTitleLeft():
	Util.tryDisconnect(self, "body_entered", self, "onBodyEntered")
	set_physics_process(false)

func _physics_process(delta):
	global_position = Util.getMousePosInWindow() + Vector2(8, 15)

func onBodyEntered(body):
	
	if body is Item:
		var dif = (body.global_position - global_position).normalized()
		
		
		body.linear_velocity = (body.linear_velocity.limit_length(200) + dif * 300.3 + Util.mouseVelocity * 50.0).limit_length(500)
		body.angular_velocity += Util.rng.randf_range( - 4, 4)
		body.lastCollisionPos = global_position
