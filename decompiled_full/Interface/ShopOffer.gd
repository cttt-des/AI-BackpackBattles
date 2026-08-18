extends Node2D

onready var index = int(name) - 1
var item
var price: int
var free = false
var onSale = false
var wasOnSale = false
var bought = false
var reserved = false
var normalPrice
var salePrice
var saleMode = Game.SaleMode.Roll

const saleSound = preload("res://Assets/Sound/Sale.ogg")
const reserveSound = preload("res://Assets/Sound/Reserve.wav")
const treasureAnimation = preload("res://Items/Animations/TreasurePulse.tscn")

const treasureSound = preload("res://Assets/Sound/Glitter.wav")

const neutralBannerMaterial = preload("res://Shader/SkillBanner_Neutral.material")
const classBannerMaterial = preload("res://Shader/ClassBanner.material")
const craftingPulse = preload("res://Items/Animations/CraftingShopPulse.tscn")
const specialShopParticles = preload("res://Shader/SpecialShopParticles.tscn")

const tooPoorColor = Color(0.765625, 0.098694, 0.098694)
const throwOutDur = 0.6

onready var priceLabel = $PriceLabel
onready var salePriceLabel = $Sale / SalePrice
onready var animation = $AnimationPlayer
onready var light = $Light
onready var reserveButton = $ReserveButton
onready var reserveHint = $ReserveHint / ReserveHintLabel
onready var reservedTag = $ReservedTag
onready var reserveAnimation = $ReservedTag / AnimationPlayer
onready var saleAnimation = $Sale / AnimationPlayer
onready var uniqueParticles = $UniqueParticles
onready var subclassLabel = $Subclass
onready var banner = $Subclass / SubclassBanner
onready var subclassAnimation = $Subclass / AnimationPlayer

onready var bannerTexture_singleLine = banner.texture
const bannerTexture_doubleLine = preload("res://Interface/SkillBanner.png")
onready var bannerMargins = [banner.margin_left, banner.margin_top, banner.margin_right, banner.margin_bottom]

func _input(event: InputEvent) -> void :
	if InputBlocker.isActive(): return
	
	if (Util.isActionPressed_event(event, "reserve") and 
		canPlayerReserve() and 
		Game.hasHoverFocus(item)):
			setReserved( not reserved)
			if reserved:
				Game.onItemReserved()

func _ready() -> void :
	Game.connect("gold_changed", self, "checkMoney")
	priceLabel.self_modulate = Color.transparent
	priceLabel.text = ""
	light.self_modulate = Color.transparent
	Util.localizeFonts(subclassLabel)
	add_to_group("Localized")
	
	reserveButton.connect("mouse_entered", self, "onReserveButtonHover")
	reserveButton.connect("mouse_exited", self, "onReserveButtonHoverEnd")
	reserveButton.connect("pressed", self, "onReserveButtonPressed")

func setItem(_item, _saleMode = Game.SaleMode.Roll):
	saleMode = _saleMode
	
	animation.stop()
	
	if bought or not item:
		animation.play("AppearFromNothing")
	else:
		animation.play("AppearFromItem")
	item = _item
	
	bought = false
	
	item.ownerType = Item.Owner.Shop
	Game.shopItemYSort.add_child(item)
	
	
	
	item.position = global_position - item.getBottomCenter() - Game.shopItemYSort.global_position
	item.connect("dropped", self, "dropped")
	
	light.modulate = item.rarityColors[item.getRarity()]
	
	if item.getRarity() == Item.Rarity.Unique:
		uniqueParticles.emitting = true
		
		if item.descriptor.startsSubclass != "":
			setBannerText(Game.getTranslatedSubclassName(item.descriptor.startsSubclass))
			var mat = classBannerMaterial.duplicate()
			banner.set_material(mat)
			mat.set_shader_param("gradient", Util.bannerGradients[item.descriptor.classes])
			mat.set_shader_param("gradient2", null)
			mat.set_shader_param("use2ndGradient", false)
			
			subclassAnimation.play("Show")
			addSpecialShopParticles()
		
		elif item.hasType(Item.Type.Skill):
			setBannerText(item.getTranslatedName())
			if item.descriptor.classes == ItemDescriptor.StuffedClasses.Neutral:
				banner.set_material(neutralBannerMaterial)
			else:
				var mat = classBannerMaterial.duplicate()
				
				banner.set_material(mat)
				var classesAsArr = item.descriptor.getClassesAsArray()
				mat.set_shader_param("gradient", Util.bannerGradients[classesAsArr[0]])
				
				if classesAsArr.size() == 1:
					mat.set_shader_param("gradient2", null)
					mat.set_shader_param("use2ndGradient", false)
					
				else:
					mat.set_shader_param("gradient2", Util.bannerGradients[classesAsArr[1]])
					mat.set_shader_param("use2ndGradient", true)
					
					var xPos = banner.rect_global_position.x + banner.rect_size.x * 0.5
					xPos -= Game.shopSceneNode.position.x
					xPos /= 1920
					mat.set_shader_param("xPos", xPos)
			
			subclassAnimation.play("Show")
			addSpecialShopParticles()
		
		elif item.descriptor.randomUniquePool:
			var ani = ObjectPool.instance(treasureAnimation)
			ani.hide()
			add_child(ani)
			ani.get_node("AnimationPlayer").play("Activate")
			ani.global_position = item.global_position
			Sound.playSound(treasureSound, 6)
	else:
		uniqueParticles.emitting = false
	
	calcPrice()
	call_deferred("checkCrafting")

func addSpecialShopParticles():
	var particles = ObjectPool.particleOneShot(specialShopParticles, self)
	particles.rotation = deg2rad( - 8)
	particles.speed_scale = Util.rng.randf_range(1.8, 2.2)

func checkCrafting():
	if item.hasShopItemCraftCandidates():
		var pulse = ObjectPool.instance(craftingPulse)
		add_child(pulse)
		var ani = pulse.get_node("RevealPulse/AnimationPlayer")
		pulse.global_position = item.global_position
		var speedFactor = Util.rng.randf_range(0.9, 1.1)
		ani.playback_speed = 0.7 * speedFactor
		ani.play("Activate")
		var scaling = 0.2 + (0.4 * sqrt(item.getNumOccupiedCells()))
		pulse.scale = Vector2(scaling, scaling)
		item.animation.play("ShopCraft", - 1, speedFactor)

func updateLocale():
	if item != null:
		if item.descriptor.startsSubclass != "":
			setBannerText(Game.getTranslatedSubclassName(item.descriptor.startsSubclass))
		if item.hasType(Item.Type.Skill):
			setBannerText(item.getTranslatedName())

const BANNER_WIDTH = 230.0

func setBannerText(text: String):
	
	subclassLabel.autowrap = false
	subclassLabel.text = text




	
	var font = subclassLabel.get("custom_fonts/font")
	var textWidth = font.get_string_size(subclassLabel.text).x
	if textWidth > BANNER_WIDTH:
		subclassLabel.autowrap = true
		
		
		var spacePos = - 1
		
		var firstLineWidth = BANNER_WIDTH
		while true:
			spacePos = text.find(" ", spacePos + 1)
			if spacePos == - 1:
				break
			
			var s = font.get_string_size(text.substr(0, spacePos + 1)).x
			if s > BANNER_WIDTH:
				break
			else:
				firstLineWidth = s
		
		var secondLineWidth = textWidth - firstLineWidth + 10
		textWidth = max(firstLineWidth, secondLineWidth)
		
		banner.texture = bannerTexture_doubleLine
		banner.rect_position.y = - 12
	else:
		banner.texture = bannerTexture_singleLine
		banner.rect_position.y = - 4
	
	banner.margin_right = bannerMargins[2]
	
	subclassLabel.rect_position.x = - 0.5 * textWidth
	
	subclassLabel.show()
	subclassLabel.set_end(subclassLabel.rect_position + Vector2(textWidth, 55))
	Util.callNextFrame(self, "shrinkBanner", [textWidth])
	

func shrinkBanner(textWidth):
	subclassLabel.set_end(subclassLabel.rect_position + Vector2(textWidth, 55))

func calcPrice():
	if not item: return
	
	wasOnSale = onSale
	
	if saleMode == Game.SaleMode.Free:
		free = true
		onSale = false
	else:
		free = false
		var normalPrice_decoded = item.getPrice()
		var salePrice_decoded = item.getSalePrice()
		normalPrice = Game.encode(normalPrice_decoded)
		salePrice = Game.encode(salePrice_decoded)
		
		if saleMode == Game.SaleMode.Roll:
			onSale = salePrice_decoded < normalPrice_decoded and Game.shopSceneNode.rollSale(self)
		elif saleMode == Game.SaleMode.NoSale:
			onSale = false
		else:
			onSale = true
	
	
	
func updatePrice():
	if onSale:
		price = salePrice
		salePriceLabel.text = String(Game.decode(salePrice))
		if wasOnSale:
			saleAnimation.play("OnSale")
			saleAnimation.advance(2)
			saleAnimation.play("SaleFromSale")
		else:
			saleAnimation.play("OnSale")
		
		Util.callDelayed(self, "playSaleSound", 0.65)
		
	else:
		if free:
			normalPrice = Game.encode(0)
		
		price = normalPrice
		
		if wasOnSale:
			saleAnimation.play("RemoveSale")
	
	priceLabel.text = String(Game.decode(normalPrice))
	
	checkMoney()


func playSaleSound():
	Sound.playSound(saleSound, - 16, Util.randPitch() - 0.1)



func checkMoney(_goldChange = 0):
	if price == 0:
		return
	if item and not bought:
		if Game.getGold() >= Game.decode(price):
			item.affordable = true
			item.enablePicking()
			Game.setItemEditMode(item)
			priceLabel.modulate = Color.white
			salePriceLabel.modulate = Color.white
		else:
			item.affordable = false
			item.disablePicking()
			priceLabel.modulate = tooPoorColor
			salePriceLabel.modulate = tooPoorColor

func dropped(result: int):
	if Item.wasBought(result):
		buy()









func buy():
	if bought:
		print("Item bought twice")
		return
	
	setReserved(false)
	bought = true
	
	item.disconnect("dropped", self, "dropped")
	var price_decoded = Game.decode(price)
	Game.spendGold(price_decoded)
	Game.onItemBought(item, onSale)
	item.onBought()
	
	var coinParticles = Game.shootGold(Game.PLAYER.getGoldPos(), 
		Game.SELLBOX.getGoldPos(), price_decoded)
	coinParticles.z_index = Game.getCoinPlayerLayer()
	Util.setDelayed(coinParticles, "z_index", Game.getCoinSellboxLayer(), 0.5)
	Util.callDelayed(Game.SELLBOX, "eatGold", 0.3, [price_decoded])
	animation.play("Bought")
	
	if onSale:
		saleAnimation.play("RemoveSale")
	
	onSale = false
	free = false
	
	if subclassLabel.visible:
		subclassAnimation.play("Hide")
	
	Sound.playSound(Game.shopSceneNode.rerollSound, 4, 0.8)
	Util.callDelayed(Sound, "playSound", 0.1, [Game.shopSceneNode.rerollSound, 10, 1.2])
	uniqueParticles.emitting = false
	Game.shopSceneNode.onItemBought(item, self)

func reset():
	if reserved: return
	
	
	if item != null and not bought:
		item.discard()
	bought = false
	item = null
	saleAnimation.play("RESET")
	saleAnimation.advance(1)
	subclassAnimation.play("RESET")
	subclassAnimation.advance(1)
	subclassLabel.text = ""
	subclassLabel.rect_size.x = 0
	animation.play("RESET")
	animation.advance(1)
	onSale = false
	free = false
	saleMode = Game.SaleMode.Roll
	uniqueParticles.emitting = false

func resetFull():
	
	setReserved(false)
	reset()
	priceLabel.self_modulate = Color.transparent

func canThrowOut():
	return item != null and not bought and not reserved

func throwOut():
	if canThrowOut():
		if subclassLabel.visible:
			subclassAnimation.play("Hide")
		
		item.disablePicking()
		ItemBook.onOwnableItemRemoved(item)
		
		
		var dur = throwOutDur * Util.rng.randf_range(0.8, 1.2) + 0.25
		
		item.z_index += 2
		var tween = create_tween().set_parallel(true)
		Util.moveParable(tween, item, Util.rng.randf_range(700, 900), 
			Util.rng.randf_range( - 400, - 100), dur)
		






		tween.tween_property(item, "rotation", Util.rng.randf_range( - 2 * PI, 2 * PI), dur)
		tween.tween_callback(item, "discard").set_delay(dur)

func onReserveButtonHover():
	if canPlayerReserve():
		reserveHint.show()

func onReserveButtonHoverEnd():
	reserveHint.hide()

func onReserveButtonPressed():
	if canPlayerReserve():
		setReserved( not reserved)
		if reserved:
			Game.onItemReserved()


func setReserved(state):
	if state == reserved: return
	if not canChangeReserveState(): return
	
	reserved = state
	
	
	Game.cancelSwitch()
	
	if animation.current_animation != "":
		animation.advance(1)
	
	if reserved:
		animation.play("Reserve")
		reserveAnimation.play("Reserve")
		
		reserveHint.translationKey = "HINT_Unreserve"
		reserveHint.updateText()
		Sound.playSound(reserveSound)
	else:
		animation.play("Unreserve")
		reserveAnimation.play("Unreserve")
		
		reserveHint.translationKey = "HINT_Reserve"
		reserveHint.updateText()
		Sound.playSound(reserveSound, 0, 0.8)
	
func setSaleMode(_mode):
	saleMode = _mode

func canChangeReserveState() -> bool:
	if item == null: return false
	if bought: return false
	
	if Game.draggedItem != null and Util.time > Game.lastItemDropTime: return false
	
	return true

func canPlayerReserve() -> bool:
	if not canChangeReserveState(): return false
	if Game.shopSceneNode.chooseOneShop: return false
	return true
