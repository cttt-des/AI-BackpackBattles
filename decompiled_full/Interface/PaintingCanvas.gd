extends TextureButton

export var paintColor = Color(1.2, 1.6, 1.7)

var grabbed = false

var image = Image.new()
var imageTexture = ImageTexture.new()

var bounds = Rect2(0, 0, 630, 350)
var lastPos: Vector2

func _ready():
	connect("button_down", self, "_button_down")
	connect("button_up", self, "_button_up")
	image.create(bounds.size.x, bounds.size.y, false, Image.FORMAT_RGBA8)
	imageTexture.create_from_image(image)
	texture_normal = imageTexture
	
func _button_down():
	if not Game.draggedItem:
		lastPos = get_global_mouse_position() - rect_global_position
		lastPos /= rect_scale
		grabbed = true

func _button_up():
	grabbed = false

func _physics_process(delta):
	if grabbed:
		var localPos = get_global_mouse_position() - rect_global_position
		localPos /= rect_scale
		image.lock()
		
		for i in 5:
			var point = localPos + Util.randInCircle(1)
			if bounds.has_point(point):
				image.set_pixelv(point, paintColor)
		
		var distToLastPoint = (localPos - lastPos).length()
		for i in int(distToLastPoint):
			var point = lerp(lastPos, localPos, i / distToLastPoint)
			if bounds.has_point(point):
				image.set_pixelv(point, paintColor)
		
		image.unlock()
		imageTexture.set_data(image)
		texture_normal = imageTexture
		lastPos = localPos
