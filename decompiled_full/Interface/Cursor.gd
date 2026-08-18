extends Node2D

onready var sprite = $Sprite

func _ready():
	hide()
	Util.callNextFrame(self, "show")

func _process(_delta: float) -> void :
	var texIndex = Game.CursorTypes.DEFAULT
	
	if Game.hoveredItems.empty() and not Game.draggedItem:
		if Input.get_current_cursor_shape() == Input.CURSOR_POINTING_HAND:
			if Game.left_click:
				texIndex = Game.CursorTypes.CLICKABLE_CLICKED
			else:
				texIndex = Game.CursorTypes.CLICKABLE
		else:
			if Game.left_click:
				texIndex = Game.CursorTypes.CLICKED
			else:
				texIndex = Game.CursorTypes.DEFAULT
			
	else:
		if Game.left_click:
			texIndex = Game.CursorTypes.GRABBED
		else:
			texIndex = Game.CursorTypes.GRABBABLE
	
	sprite.position = - Game.getCursorOffset(texIndex)
	sprite.texture = Game.scaledCursors[texIndex]
	
	sprite.scale.y = sprite.scale.x
	position = get_global_mouse_position()
