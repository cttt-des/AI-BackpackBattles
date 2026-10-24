extends Control

const SCALE = Vector2(1, 1)

onready var progressLabel: Label = $Progress
var hasData: bool = false

func _ready() -> void :
	mouse_filter = Control.MOUSE_FILTER_IGNORE
	rect_scale = SCALE
	_connectSignals()
	_setupProgressLabel()
	_updateFromLast()
	_updateVisibility()

func _setupProgressLabel():
	progressLabel.align = Label.ALIGN_RIGHT
	progressLabel.valign = Label.VALIGN_CENTER
	progressLabel.rect_min_size = Vector2.ZERO
	progressLabel.rect_position = Vector2.ZERO
	progressLabel.rect_scale = Vector2.ONE
	progressLabel.add_color_override("font_color", Color.white)
	progressLabel.add_color_override("font_color_shadow", Color(0, 0, 0, 0))

func _connectSignals():
	if not Game.is_connected("combat_scene_entered", self, "_onCombatEntered"):
		Game.connect("combat_scene_entered", self, "_onCombatEntered")
	if not Game.is_connected("switch_to_shop", self, "_onSwitchToShop"):
		Game.connect("switch_to_shop", self, "_onSwitchToShop")
	if not Game.is_connected("combat_scene_left", self, "_onCombatLeft"):
		Game.connect("combat_scene_left", self, "_onCombatLeft")

func _onCombatEntered():
	_updateFromLast()
	_updateVisibility()

func _onSwitchToShop():
	_clearInfo()
	_updateVisibility()

func _onCombatLeft():
	_clearInfo()
	hide()

func _updateVisibility():
	if Game.state == Game.State.Combat and hasData and Game.opponentRankDisplayEnabled:
		show()
	else:
		hide()

func _updateFromLast():
	if not RunDatabase.recentOpponentRuns.empty():
		_setInfo(RunDatabase.recentOpponentRuns[ - 1])
	else:
		_clearInfo()

func refreshVisibility():
	_updateVisibility()

func _clearInfo():
	hasData = false
	progressLabel.text = ""
	hide()

func _setInfo(run):
	if run == null:
		_clearInfo()
		return
	var rating = run.rating
	if rating == RunDatabase.UNRANKED_RATING:
		progressLabel.text = "Unranked"
		progressLabel.add_color_override("font_color", Color(1, 1, 1))
	else:
		var leagueExact = Game.getLeague_exact(rating)
		var league = clamp(int(leagueExact), 0, Game.Leagues.size() - 1)
		var progress = int(fmod(leagueExact, 1.0) * 100)
		var leagueName = Game.getLeagueName(league)
		progressLabel.text = "%s %d" % [leagueName, progress]
		progressLabel.add_color_override("font_color", Game.leagueColors[league])
	hasData = true
	if Game.state == Game.State.Combat:
		show()
