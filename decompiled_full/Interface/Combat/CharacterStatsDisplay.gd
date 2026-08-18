extends Node2D

const ICONS_PER_COLUMN = 6
const TOTAL_ICON_SIZE = Vector2(60, 60)
const iconScene = preload("res://Interface/Combat/CharacterStatIcon.tscn")

var icons = {}

var activeIcons = []
var positionTween = null

onready var isPlayer = (get_parent().get_parent().playerId == Character.ID.PLAYER)

func _ready():
	for stat in range(Character.Stat.ReflectStacks, Character.Stat.size()):
		var icon = ObjectPool.instance(iconScene)
		icons[stat] = icon
		add_child(icon)
		icon.setStat(stat)
	
	Game.connect("combat_start", self, "activateIcons")


func onStatChanged(stat: int, value):
	if not Game.STAT_DISPLAY_ENABLED: return
	if not stat in icons: return
	
	var icon = icons[stat]
	var wasActive = icon.active
	icon.setStatValue(value)
	if not wasActive and icon.active:
		icon.position = getGridPosition(activeIcons.size())
		activeIcons.push_back(icon)
	elif wasActive and not icon.active:
		var index = activeIcons.find(icon)
		Util.eassert(index != - 1)
		activeIcons.remove(index)
		repositionIcons(index)

func activateIcons():
	for icon in activeIcons:
		icon.appear()

func repositionIcons(fromIndex: int):
	if fromIndex >= activeIcons.size(): return
	
	positionTween = Util.refreshTween(positionTween).set_parallel(true)
	for iconI in range(fromIndex, activeIcons.size()):
		positionTween.tween_property(activeIcons[iconI], "position", 
			getGridPosition(iconI), 0.2)
	positionTween.set_speed_scale(0)

func getGridPosition(iconIndex: int) -> Vector2:
	var column = iconIndex / ICONS_PER_COLUMN
	var row = iconIndex % ICONS_PER_COLUMN
	if isPlayer:
		column *= - 1
	return Vector2(column, row) * TOTAL_ICON_SIZE

func reset():
	Util.killTween(positionTween)
	positionTween = null
	for icon in activeIcons:
		icon.disappear()
	activeIcons.clear()

func _physics_process(delta):
	if Util.isTweenRunning(positionTween):
		positionTween.set_speed_scale(1)
		positionTween.custom_step(1 / 60.0)
		positionTween.set_speed_scale(0)
