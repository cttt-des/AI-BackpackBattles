extends FocusGrabbingTextureButton

onready var iconMember_normal = texture_normal
onready var iconMember_hovered = texture_hover
onready var iconHost_normal = preload("res://Interface/Lobbies/LobbyIcon_Host.png")
onready var iconHost_hovered = preload("res://Interface/Lobbies/LobbyIcon_Host_hovered.png")

onready var LOBBIES = RunDatabase.lobbies

func _ready():
	if LOBBIES.isHost():
		texture_normal = iconHost_normal
		texture_hover = iconHost_hovered
	else:
		texture_normal = iconMember_normal
		texture_hover = iconMember_hovered

func onPressed():
	if not Game.draggedItem and not Game.options.isOpen:
		.onPressed()
		if LOBBIES.scoreboard.isOpen:
			LOBBIES.scoreboard.close()
		else:
			LOBBIES.scoreboard.open()
	
func onHover():
	if not Game.options.isOpen:
		.onHover()
