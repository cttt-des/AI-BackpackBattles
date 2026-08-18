extends Node2D

onready var wantItemNode = $Node2D / Item1
onready var giveItemNode = $Node2D / Item2
onready var bubble = $Node2D / ThinkBubble1
onready var animation = $AnimationPlayer
onready var idleAnimations = [
	$Node2D / IdleAnimation, 
	$ThinkBubble2 / IdleAnimation, 
	$ThinkBubble3 / IdleAnimation]

var wantItem = null
var giveItem = null
var active: = false


onready var tradeExcludeItems = {
	ItemBook.chessboardDescriptor: true, 
	ItemBook.deckOfCardsDescriptor: true
}

func _ready():
	Game.connect("return_to_title", self, "onReturnToTitle")
	Game.connect("shop_opened", self, "onShopOpened")
	Game.connect("shop_closed", self, "onShopClosed")
	Game.connect("warp_cursor_shop", self, "onCursorWarp")

func onReturnToTitle():
	z_index = 4
	call_deferred("endTrade")

func onShopOpened():
	z_index = 35

func onShopClosed():
	endTrade()

func isTradeActive() -> bool:
	return active

func isTradable(item) -> bool:
	return isTradeActive() and item.isA(wantItem.descriptor)


func setTrade(wantItemIndex, giveItemIndex, giveData):
	active = true
	animation.play("ShowTrade")
	for ani in idleAnimations:
		ani.play("Idle")
	
	wantItem = initItem(ItemBook.getDescriptorFromIndex(wantItemIndex), wantItemNode)
	giveItem = initItem(ItemBook.getDescriptorFromIndex(giveItemIndex), giveItemNode)
	
	if giveData != null:
		giveItem.setData(giveData)

func startTrade(bonusValue: int):
	var tradeWasActive = isTradeActive()
	
	if wantItem != null:
		clearItem(wantItem, false)
		wantItem = null
	
	if giveItem != null:
		clearItem(giveItem, false)
		giveItem = null
	
	active = false
	
	var wantCandidates = []
	for item in ItemBook.getOwnedItems():
		if (item.getRarity() != Item.Rarity.Unique and 
			not item.isBag() and 
			not item.descriptor in tradeExcludeItems):
			wantCandidates.push_back(item.descriptor)
			
	
	if wantCandidates.empty():
		return
	
	wantCandidates = Util.filterDuplicates(wantCandidates)
	wantCandidates.shuffle()
	
	
	var itemPool = ItemPool.new()
	var filters = ItemBook.Filter.Gems + ItemBook.Filter.Amulets + ItemBook.Filter.Crafted
	for descriptor in ItemBook.items.values():
		if ItemBook.canBeGenerated(descriptor, filters):
			itemPool.addItem(descriptor)
	itemPool.sortItems()
	
	for wantDescriptor in wantCandidates:
		var giveCandidates = []
		var price = wantDescriptor.getPrice() + bonusValue



		for descriptor in itemPool.pool:
			if descriptor != wantDescriptor:
				var priceDif = descriptor.price - price
				if priceDif == 2 or priceDif == 1:
					giveCandidates.push_back(descriptor)
		
		if not giveCandidates.empty():
			active = true


			
			if tradeWasActive:
				animation.play("NewTrade")
			else:
				animation.play("ShowTrade")
				for ani in idleAnimations:
					ani.play("Idle")
			
			var giveDescriptor = giveCandidates.pick_random()
			
			wantItem = initItem(wantDescriptor, wantItemNode)
			giveItem = initItem(giveDescriptor, giveItemNode)
			
			if ItemBook.isRing(giveItem):
				giveItem.randEffects(false)
			
			Game.saveRunState()
			
			
			return
	
	if tradeWasActive:
		endTrade()
	
	print("cannot find give item.")

func initItem(descriptor, parent):
	var item = descriptor.instantiate_pooled()
	item.ownerType = item.Owner.BuildViewerIcon
	parent.add_child(item)
	item.initBuildViewerIcon()
	
	item.scaleToFit_local(Vector2(90, 100), 0.7)
	item.position = item.getSpriteOffset_local()
	item.popIn()
	var hoverArea = parent.get_node("HoverArea")
	hoverArea.connect("mouse_entered", self, "onItemHovered", [item])
	hoverArea.connect("mouse_exited", self, "onItemHoverEnd", [item])
	hoverArea.show()
	return item

func clearItem(item, instant: bool):
	item.hoverEnd()
	var parent = item.get_parent()
	var hoverArea = parent.get_node("HoverArea")
	hoverArea.disconnect("mouse_entered", self, "onItemHovered")
	hoverArea.disconnect("mouse_exited", self, "onItemHoverEnd")
	hoverArea.hide()
	if instant:
		item.discard()
	else:
		item.disappear()

func getTradeGiveData():
	if not isTradeActive(): return null
	
	if ItemBook.isRing(giveItem):
		return giveItem.getData()
	
	return null

func onItemHovered(item):
	item.hover()

func onItemHoverEnd(item):
	item.hoverEnd()

func endTrade():
	if active:
		active = false
		animation.play("EndTrade")
		for ani in idleAnimations:
			ani.stop()


func reset():
	animation.play("RESET")
	for ani in idleAnimations:
		ani.stop()
	
	if wantItem != null:
		clearItem(wantItem, true)
		wantItem = null
	
	if giveItem != null:
		clearItem(giveItem, true)
		giveItem = null

const darkColor = Color(0.880859, 0.860786, 0.830967)

func updateColor(item = null):
	modulate = Color.white
	if item == null:
		bubble.self_modulate = darkColor
	elif not isTradable(item):
		if Game.SELLBOX.hovered:
			modulate = Color(0.78, 0.78, 0.96)
			bubble.self_modulate = darkColor
		else:
			bubble.self_modulate = darkColor
			
	else:
		if Game.SELLBOX.hovered:
			bubble.self_modulate = Color(1.05, 1.05, 0.9)
		else:
			bubble.self_modulate = Color(1, 1, 1)


func onCursorWarp():
	if active:
		Game.addPointOfInterest(wantItem.global_position)
		Game.addPointOfInterest(giveItem.global_position)
