extends Button
class_name ItemListButton

signal list_opened
signal list_closed
signal item_selected

export var OPTION = ""
export var translate = false
export var openWithClick = false
export (float, 0.0, 1.0, 0.1) var warpPointXFactor = 0.5

onready var itemList = $ItemList
onready var defaultIcon = icon

var hoverRect: Rect2
const TOPLEFT_MARGIN = Vector2(50, 50)
const BOTTOMRIGHT_MARGIN = Vector2(50, 80)

var rawItems = []
var focusLostFrame: int
var openFrame: int
var icons = {}
var hovered: = false

func _ready() -> void :
	
	itemList.set("custom_fonts/font", get("custom_fonts/font"))
	itemList.hide()
	set_process(false)
	connect("mouse_entered", self, "onHover")
	connect("mouse_exited", self, "onHoverEnd")
	connect("button_down", self, "onClicked")
	itemList.connect("focus_exited", self, "onFocusLost")
	Util.localizeFonts(self)
	
	itemList.set_fixed_icon_size(Vector2(30, 30))
	
	Game.connect("item_list_closed", self, "onListClosed")
	Game.connectToGetRectsSignals(self, "onGetRects")
	Game.connectToWarpCursorSignals(self, "onCursorWarp")

func addItem(itemText, itemIcon = null):
	var index = rawItems.size()
	icons[index] = itemIcon
	rawItems.push_back(itemText)
	itemList.add_item(Util.tr(itemText), itemIcon)
	widen(itemText, itemIcon)
	
	






func selectItemByIndex(index):
	itemList.select(index)
	updateText(index)

func updateLocale():
	if itemList:
		if translate:
			itemList.rect_size.x = 0
			for i in rawItems.size():
				var newText = Util.tra(rawItems[i])
				itemList.set_item_text(i, newText)
				widen(newText, icons[i])
		
		var selected = itemList.get_selected_items()
		if not selected.empty():
			updateText(selected[0])

func widen(toFitText, iconToFit = null):
	var iconSize = 0
	if iconToFit != null:
		iconSize = 30
	itemList.rect_size.x = max(itemList.rect_size.x, 
		itemList.get("custom_fonts/font").get_string_size(toFitText).x + 16 + iconSize)

func updateText(index):
	self.text = ""
	if OPTION != "":
		self.text = Util.tr(OPTION) + ": "



	self.text += itemList.get_item_text(index)
	var _icon = itemList.get_item_icon(index)
	if _icon != null:
		self.icon = _icon
		expand_icon = true
		
	else:
		self.icon = defaultIcon
		expand_icon = false
	


func selectItem(itemText):
	var index = 0
	for i in rawItems.size():
		if rawItems[i] == itemText:
			index = i
			break
	selectItemByIndex(index)

func onHover():
	hovered = true
	if not Game.itemListOpened:
		Util.grabFocus(self)
		if not openWithClick:
			showItemList()

func onListClosed():
	if hovered:
		onHover()

func onClicked():
	if ( not Game.itemListOpened and 
		openWithClick and 
		Util.getFrameCounter_process() > focusLostFrame + 1):
		showItemList()

func showItemList():
	openFrame = Util.getFrameCounter_process()
	itemList.show()
	itemList.grab_focus()
	set_process(true)
	Game.onHoverInteractable(self)
	Util.callNextFrame(self, "calcHoverRect")
	emit_signal("list_opened")
	Game.itemListOpened = true
	
	
func calcHoverRect():
	if not is_inside_tree():
		print(name, " not inside tree")
		return
	hoverRect.position = rect_global_position - TOPLEFT_MARGIN
	var maxSize = Vector2(max(itemList.rect_size.x, rect_size.x), itemList.rect_size.y)
	hoverRect.size = maxSize + TOPLEFT_MARGIN + BOTTOMRIGHT_MARGIN

func onHoverEnd():
	Game.onHoverInteractableEnd(self)
	hovered = false

func clearList():
	itemList.clear()
	itemList.rect_size.x = 0
	rawItems.clear()

func onFocusLost():
	
	if not hoverRect.has_point(get_global_mouse_position()):
		hideItemList()
		focusLostFrame = Util.getFrameCounter_process()

func onItemSelected(index: int):
	emit_signal("item_selected", index, itemList.get_item_text(index))
	updateText(index)
	hideItemList()
	focusLostFrame = Util.getFrameCounter_process()
	Game.onClickButton()
	Game.disableTooltipsFor(12)
	Game.disableHoverResponsesFor(12)

func hideItemList():
	if itemList.visible:
		itemList.hide()
		set_process(false)
		emit_signal("list_closed")
		Game.onItemListClosed()

func _process(_delta: float) -> void :
	if not hoverRect.has_point(get_global_mouse_position()):
		hideItemList()
	
	
	
	if Util.getFrameCounter_process() > openFrame + 1:
		for i in itemList.get_item_count():
			itemList.set_item_custom_bg_color(i, Color.transparent)
			itemList.set_item_custom_fg_color(i, Game.SOFTWHITE)
			
		var localPos = get_global_mouse_position() - itemList.rect_global_position
		var hoveredItem = itemList.get_item_at_position(localPos)
		if hoveredItem >= 0:
			itemList.set_item_custom_bg_color(hoveredItem, Game.SOFTWHITE)
			itemList.set_item_custom_fg_color(hoveredItem, Util.paramColor)
			
			if Util.isActionJustPressed("ui_select", false):
				selectItemByIndex(hoveredItem)
				onItemSelected(hoveredItem)

func _exit_tree():
	hideItemList()

func onGetRects():
	if itemList.visible:
		var size = Vector2(max(itemList.rect_size.x, rect_size.x), itemList.rect_size.y)
		Game.addOcclusion(rect_global_position, size, 1)

func onCursorWarp():
	if itemList.visible:
		var size = Vector2(max(itemList.rect_size.x, rect_size.x), itemList.rect_size.y)
		var step = size.y / rawItems.size()
		for i in rawItems.size():
			var pos = rect_global_position
			pos.x += size.x * warpPointXFactor
			pos.y += rect_size.y + step * (i + 0.5)
			Game.addPointOfInterest(pos, null, null, 2)
