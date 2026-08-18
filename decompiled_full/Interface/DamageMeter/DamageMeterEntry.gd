extends FocusGrabbingControl

const stylebox_normal = preload("res://Interface/DamageMeter/DamageMeterEntryStylebox.tres")
const stylebox_connected = preload("res://Interface/DamageMeter/DamageMeterEntryStylebox_connected.tres")
const defaultColorProp: = "custom_colors/default_color"
const fontColorProp = "custom_colors/font_color"
const textActiveColor: = Color(1, 0.92549, 0.831373)
const textInactiveColor: = Color(0.697266, 0.684629, 0.668667)

var nameLabel
var progressBar
var relDamageLabel
var absDamageLabel
var panel
var plotButton
var progressBarStylebox: StyleBoxFlat
var player
var source
var absDamage
var dps
var plot = null
var damageMeter

var plotButtonActiveColor: Color
const plotButtonInactiveColor: = Color(0.652344, 0.606742, 0.549141)
var plotButtonActive: bool

func preset():
	nameLabel = $Name
	progressBar = $ProgressBar
	relDamageLabel = $RelDamage
	absDamageLabel = $AbsoluteDamage
	panel = $Panel
	plotButton = $PlotButton
	
	add_to_group("Localized")
	Util.localizeFonts(self)
	nameLabel.set_message_translation(false)
	
	progressBarStylebox = progressBar.get("custom_styles/fg")


func init(_player: bool, _source, _absValue, _dps: float, 
	relValue: float, relToLargest: float, _plot, _damageMeter):
	
	player = _player
	source = _source
	plot = _plot
	damageMeter = _damageMeter
	dps = _dps
	absDamage = _absValue
	plotButton.visible = plot != null
	if plot != null:
		setPlotButtonStyle(plot.getColor(source), 
			plot.getSymbol(source), plot.isActive(source))
	else:
		progressBarStylebox.bg_color = Color(2, 1.78, 0.44, 0.37)
	
	progressBar.value = relToLargest * 100.0
	
	relDamageLabel.text = String(round(100.0 * relValue)) + "%"
	
	Util.localizeFonts(self)
	updateLocale()
	unhighlight()

func updateLocale():
	absDamageLabel.text = Util.tra("UI_DamageMeter_Format").format({
		"absDmg": stepify(absDamage, 0.1), 
		"dps": stepify(dps, 0.1)})
		
	var sourceName = ""
	if typeof(source) == TYPE_INT:
		var icon = Util.getIcon(Game.typeToKeyword(source))
		if icon:
			sourceName += icon + " "
		sourceName += Util.tra(Game.typeToKeyword(source) + "_NAME")
	else:
		sourceName = source.getTranslatedName()
	
	nameLabel.bbcode_text = sourceName

func highlight():
	panel.set("custom_styles/panel", stylebox_connected)

func unhighlight():
	panel.set("custom_styles/panel", stylebox_normal)

func onHover():
	.onHover()
	if typeof(source) == TYPE_INT:
		
		Game.combatLog.highlightSource(source, player)
	else:
		Game.combatLog.highlightItem(source)

func onHoverEnd():
	.onHoverEnd()
	Game.combatLog.unhighlightItem()

func setPlotButtonStyle(color: Color, symbol: Texture, active: bool = true):
	plotButton.texture = symbol
	plotButtonActiveColor = color
	plotButtonActive = active
	
	if active:
		onShowPlotLine()
	else:
		onHidePlotLine()

func onPlotButtonToggled():
	setPlotButtonActive( not plotButtonActive)

func setPlotButtonActive(active):
	plotButtonActive = active
	
	if plotButtonActive:
		plot.showLine(source)
		onShowPlotLine()
	else:
		plot.hideLine(source)
		onHidePlotLine()

func onShowPlotLine():
	progressBarStylebox.bg_color = plotButtonActiveColor
	plotButton.modulate = plotButtonActiveColor
	nameLabel.set(defaultColorProp, textActiveColor)
	nameLabel.set(defaultColorProp, textActiveColor)
	relDamageLabel.set(fontColorProp, textActiveColor)
	absDamageLabel.set(fontColorProp, textActiveColor)

func onHidePlotLine():
	progressBarStylebox.bg_color = plotButtonInactiveColor
	plotButton.modulate = plotButtonInactiveColor
	nameLabel.set(defaultColorProp, textInactiveColor)
	relDamageLabel.set(fontColorProp, textInactiveColor)
	absDamageLabel.set(fontColorProp, textInactiveColor)

func _gui_input(event):
	if plot != null and not Game.combatLog.movedDuringDrag:
		if Util.isClickReleaseEvent(event):
			Game.onClickButton()
			onPlotButtonToggled()
		
		elif Util.isRightClickReleaseEvent(event):
			Game.onClickButton()
			var isIsolated: = true
			for entry in damageMeter.plotToEntry[plot]:
				if entry == self:
					if not plotButtonActive:
						isIsolated = false
						break
				elif entry.plotButtonActive:
					isIsolated = false
					break
			
			for entry in damageMeter.plotToEntry[plot]:
				if entry == self:
					setPlotButtonActive( not isIsolated)
				else:
					entry.setPlotButtonActive(isIsolated)
