extends Node2D

onready var timeLeftLabel = $Open / TimeLeft
onready var linkButton = $Open / LinkButton
onready var openButton = $Closed / OpenButton
onready var closeButton = $Open / CloseButton
onready var openNode = $Open
onready var closedNode = $Closed
onready var sprite = $Open / RangerPlushie
onready var baseScale = sprite.scale
const hoverScale = Vector2(1.05, 1.05)

func _ready():
	var releaseTime = Time.get_unix_time_from_datetime_string("2024-09-06 03:00:00.000")
	
	var curTime = Time.get_unix_time_from_system()
	var timeDif = releaseTime - curTime
	if timeDif < 0:
		queue_free()
		return
	
	var timeInDays: float = timeDif / (60 * 60 * 24)
	var daysToRelease: = int(timeInDays)
	var hoursToRelease: = int((timeInDays - daysToRelease) * 24)
	
	var format = "[center]{days}d {hours}h"
	timeLeftLabel.bbcode_text = format.format({"days": daysToRelease, "hours": hoursToRelease})
	
	linkButton.connect("mouse_entered", self, "onHover")
	linkButton.connect("mouse_exited", self, "onHoverEnd")
	openButton.connect("pressed", self, "open")
	closeButton.connect("pressed", self, "close")
	if Game.getConfigValue("Options", "hide_ranger_plushie", false):
		close(false)
	else:
		open(false)

func open(saveConfig = true):
	openNode.show()
	closedNode.hide()
	if saveConfig:
		Game.setConfigValue("Options", "hide_ranger_plushie", false)

func close(saveConfig = true):
	openNode.hide()
	closedNode.show()
	if saveConfig:
		Game.setConfigValue("Options", "hide_ranger_plushie", true)

func onHover():
	sprite.scale = hoverScale

func onHoverEnd():
	sprite.scale = baseScale
