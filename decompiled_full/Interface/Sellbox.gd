extends Area2D

signal calc_trade_chance

const openSound = preload("res://Assets/Sound/ChestOpening1.wav")
const burpSound = preload("res://Assets/Sound/ChestOpening2.wav")
const closeSound = preload("res://Assets/Sound/ChestClosing2.wav")
const chompSound = preload("res://Assets/Sound/ChestClosing1.wav")
const coinEatSound_single = preload("res://Assets/Sound/Coins3.wav")
const coinEatSound_many = preload("res://Assets/Sound/Coins1.wav")
const coinSpitSound = preload("res://Assets/Sound/Coins2.wav")
const jumpSound = preload("res://Assets/Sound/Thud3.wav")

const angleCurve = preload("res://Assets/Chestnut/ChestnutOpenCurve.tres")
const closedDist = 1000.0
const maxAnglePerSecond = 180.0
const closedAngle = 0.0
const coinSpritePath = "res://Assets/GoldCoin2.png"

onready var box = $CollisionShape2D
onready var shape = $CollisionShape2D.shape
onready var chestnut = $Chestnut
onready var label = $Chestnut / RichTextLabel
onready var rect = Rect2(box.global_position - shape.extents, shape.extents * 2)
onready var chestnutTop = $Chestnut / Top
onready var animation = $AnimationPlayer
onready var goldPos = $GoldPos
onready var hintArea = $HintArea
onready var hint = $Chestnut / SellHint
onready var chompParticles = $ChompDust
onready var tradeNode = $Trade
onready var tradeAnimation = $TradeAnimation
onready var bottomPos = $Chestnut / BottomPos
onready var light = $Chestnut / Light
onready var hoverParticles = $Chestnut / Particles
onready var pupil = $Chestnut / Top / Eye / Pupil
onready var tongueAnimation = $Chestnut / Tongue / TongueAnimation

onready var littleMimicDescriptor = ItemBook.getDescriptor("Little Mimic")
onready var scaleDescriptor = ItemBook.getDescriptor("Scale")
onready var employeeUniformDescriptor = ItemBook.getDescriptor("Employee Uniform")

var hovered = false
var angleTween
var lightTween
var hoveredLastFrame = false
var tradeChance: = 0.0
var tradeBonusValue: = 0
var soldRoll: Dictionary

func _ready() -> void :
	Game.SELLBOX = self
	label.hide()
	Game.connect("item_picked_up", self, "onItemPickedUp")
	Game.connect("item_dropped", self, "onItemDropped")
	Game.connect("switch_to_shop", self, "onSwitchingToShop")
	Game.connect("returned_to_title", self, "onShopLeft")
	Game.connect("combat_scene_entered", self, "onShopLeft")
	Game.connect("run_over", self, "onRunOver")
	Game.shopSceneNode.connect("shop_refreshed", self, "onShopRefreshed")
	set_process(false)
	hintArea.show()
	hint.hide()

func onRunOver():
	soldRoll.clear()

func getGoldPos():
	return goldPos.global_position

func onItemPickedUp():
	if Game.state != Game.State.Shop: return
	
	if Game.draggedItem.canBeSold():
		set_process(true)
		hintArea.hide()
		label.show()
		animation.stop()
		updateText()
		tradeNode.updateColor(Game.draggedItem)
		chompParticles.emitting = false
	
func onItemDropped(item, dropResult):
	
	if Item.wasHotSwap(dropResult):
		tradeNode.updateColor(Game.draggedItem)
		return
	
	hovered = false
	set_process(false)
	label.hide()
	hintArea.show()
	tradeNode.updateColor(null)
	lightTween = Util.refreshTween(lightTween)
	lightTween.tween_property(light, "modulate:a", 0.0, 0.2)
	hoverParticles.deactivate()
	modulate = Color.white
	
	if dropResult != Item.DropResult.Sold:
		angleTween = Util.refreshTween(angleTween)
		angleTween.tween_property(chestnutTop, "rotation_degrees", closedAngle, 0.2)
	else:
		animation.play("Sell")
		soldRoll[item.descriptor] = Game.shopSceneNode.rollsThisRun

func getLastSellRoll(item: ItemDescriptor):
	return soldRoll.get(item, ItemBook.NOT_SOLD)

func onHoverHintArea():
	hint.show()

func onHoverHintAreaEnd():
	hint.hide()

func isHovered():
	return hovered




func eatGold(amount):
	animation.stop()
	Sound.playSound(chompSound, - 4 + Util.randRange( - 1, 1), Util.randPitch(0.2))
	if amount == 1:
		animation.play("EatCoin")
		Util.callDelayed(Sound, "playSound", 0.5, 
			[coinEatSound_single, - 4, Util.randPitch(0.2)])
	else:
		animation.play("EatGold")
		Util.callDelayed(Sound, "playSound", 0.5, 
			[coinEatSound_many, - 4, Util.randPitch(0.2)])

func burp():
	Sound.playSound(burpSound, Util.randRange( - 5, 0), Util.randPitch(0.3) - 0.2)

func chomp():
	Sound.playSound(chompSound, - 10 + Util.randRange( - 3, 1), Util.randPitch(0.2))
	Util.callDelayed(Sound, "playSound", 0.2, 
		[closeSound, - 2, Util.randPitch(0.2)])

func close(volume = - 10):
	Sound.playSound(closeSound, volume + Util.randRange( - 1, 1), Util.randPitch(0.2) - 0.1)












func _process(delta: float) -> void :
	var mousePos = Util.getMousePosInWindow()
	var dist = (mousePos - box.global_position).length()
	var angle = angleCurve.interpolate(dist / closedDist)
	var dif = angle - chestnutTop.rotation_degrees
	chestnutTop.rotation_degrees += sign(dif) * min(abs(dif), maxAnglePerSecond * delta)
	
	hovered = rect.has_point(mousePos)
	if hovered != hoveredLastFrame:
		lightTween = Util.refreshTween(lightTween)
		if hovered:
			lightTween.tween_property(light, "modulate:a", 1.0, 0.05)
			modulate = Color(1.2, 1.2, 1.0)
			hoverParticles.activate()
		else:
			lightTween.tween_property(light, "modulate:a", 0.0, 0.05)
			modulate = Color.white
			hoverParticles.deactivate()
		updateText()
		tradeNode.updateColor(Game.draggedItem)
	hoveredLastFrame = hovered
	
func updateText():
	var rawText
	if tradeNode.isTradeActive() and Game.draggedItem.isA(tradeNode.wantItem.descriptor):
		if hovered:
			label.translationKey = "HINT_Trade2"
		else:
			label.translationKey = "HINT_Trade1"
	else:
		if hovered:
			label.translationKey = "HINT_Sell3"
			
			
			
		else:
			label.translationKey = "HINT_Sell2"
			
			
			
		
		var baseSellPrice = Game.draggedItem.getBaseSellPrice()
		var sellPrice = Game.draggedItem.getSellPrice()
		
		var priceStr: String
		if baseSellPrice > sellPrice:
			priceStr = Util.wrapInColor(str(sellPrice), Util.red)
		else:
			priceStr = Util.wrapInColor(str(sellPrice), Util.paramColor)
		
		label.formatParams = {"price": priceStr + Util.imageToBbcode(coinSpritePath, 44)}
	
	label.updateLocale()
	
	

func sellItem(item):
	if tradeNode.isTradeActive():
		if item.isA(tradeNode.wantItem.descriptor):
			Sound.playSound(openSound)
			Util.reparent(item, Game.shopItemYSort)
			var itemTween = create_tween()
			itemTween.tween_property(item, "global_position", 
				bottomPos.global_position, 0.5)
			
			var giveItem = ItemBook.generateAndStorageItem(tradeNode.giveItem.descriptor, 
				bottomPos.global_position + Vector2(30, - 30), Game.STORAGEBOX.center - Vector2(0, 150))
			
			if ItemBook.isRing(giveItem):
				giveItem.copyFrom(tradeNode.giveItem)
			
			tradeNode.endTrade()
			tradeAnimation.play("Trade")
			
			giveItem.animation.play("FromTrade")
			return
	
	
	Util.reparent(item, Game.shopItemYSort)
	var price = item.getSellPrice()
	Game.gainGold(price)
	Game.onItemSold(item)
	var itemTween = create_tween()
	itemTween.tween_property(item, "global_position", 
		bottomPos.global_position, 0.5)
	Sound.playSound(openSound)
	
	if price > 0:
		var coinParticles = Game.shootGold(getGoldPos(), 
			Game.PLAYER.getGoldPos(), price)
		coinParticles.z_index = Game.getCoinSellboxLayer()
		Util.setDelayed(coinParticles, "z_index", Game.getCoinPlayerLayer(), 0.5)
		Util.callDelayed(Sound, "playSound", 0.5, [coinSpitSound])


func getTradeChance() -> float:
	tradeChance = 0.0
	tradeBonusValue = 0
	
	emit_signal("calc_trade_chance")
	
	var chance = tradeChance
	








	
	
	if CustomRules.customRulesActive:
		chance += CustomRules.getRuleValue(CustomRules.Rules.TradeChance) / 100.0
	
	return chance

func onShopRefreshed():
	if Game.itemsAreFusing:
		Game.connect("crafting_finished", self, "rollTrades", [], CONNECT_ONESHOT)
	else:
		rollTrades()
	
func rollTrades():
	
	if Util.flip(getTradeChance()):
		tradeNode.startTrade(tradeBonusValue)
	else:
		tradeNode.endTrade()

func onSwitchingToShop():
	pupil.activate()
	tongueAnimation.play("Idle")

func onShopLeft():
	pupil.deactivate()
	tongueAnimation.stop()


const dustParticlesScene = preload("res://Shader/ChestnutLandParticles.tscn")
var clickTween: SceneTreeTween
onready var defaultPos = chestnut.position

func _gui_input(event):
	if (event is InputEventMouseButton and 
		event.is_pressed() and 
		Game.draggedItem == null and 
		not Util.isTweenRunning(clickTween)):
		
		var strength = 1.0
		if event.button_index == BUTTON_RIGHT:
			strength = 2.0
		
		var dur = 0.2 + 0.1 * strength
		var phase1Dur = dur * 0.5
		var jumpPos = defaultPos.y + Util.rng.randf_range( - 15, - 25) * strength
		clickTween = Util.refreshTween(clickTween)
		clickTween.set_parallel()
		clickTween.tween_property(chestnut, "position:y", jumpPos, 
			phase1Dur).set_ease(Tween.EASE_OUT)
		clickTween.tween_property(chestnut, "position:y", 
			defaultPos.y, dur - phase1Dur).from(jumpPos
			).set_delay(phase1Dur).set_ease(Tween.EASE_IN)
		
		var angle = Util.rng.randf_range( - 0.1, 0.2) * strength
		clickTween.tween_property(chestnut, "rotation", angle, 
			phase1Dur).set_ease(Tween.EASE_OUT)
		clickTween.tween_property(chestnut, "rotation", 0.0, 
			dur - phase1Dur).from(angle).set_delay(phase1Dur).set_ease(Tween.EASE_IN)
		
		clickTween.tween_callback(self, "spawnDust", [strength]).set_delay(dur - 0.1)
		
		Sound.playSound(jumpSound, 0 + (strength - 1) * 3, 0.8)

func spawnDust(strength):
	var particles1 = ObjectPool.particleOneShot(dustParticlesScene, self)
	particles1.position = Vector2( - 58, 100)
	particles1.scale.x = 0.4
	particles1.amount = 3 + 2 * strength
	
	var particles2 = ObjectPool.particleOneShot(dustParticlesScene, self)
	particles2.position = Vector2(26, 100)
	particles2.scale.x = - 0.4
	particles2.amount = 3 + 2 * strength
	
	Sound.playSound(jumpSound, 0 + (strength - 1) * 3, 0.3)
