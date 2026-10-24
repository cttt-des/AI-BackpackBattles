extends Node2D

const destructReactionScene = preload("res://Assets/Shop/Shopkeeper/DestructReaction.tscn")

const numTips = 12
var curTip = 0
var craftingTipShown = false
var craftNextRound = false
var showCraftFlavorText: = false

onready var hint = $ShopKeeperHint
onready var head = $Shopkeeper / ShopkeeperHead

func _ready() -> void :
	Game.connect("shop_opened", self, "onShopOpened")
	Game.connect("item_bought", self, "onBuy")
	Game.connect("item_sold", self, "onSell")
	Game.connect("return_to_title", self, "onReturnToTitle")
	Game.connect("returned_to_title", self, "onReturnedToTitle")
	Game.connect("crafting_ready", self, "onCraftingReady")
	Game.connect("item_crafted", self, "onCraft")
	Game.connect("combat_start_pressed", self, "onStartPressed")
	add_to_group("Localized")
	updateLocale()
	
	if Util.isChristmas():
		var christmasHead = Sprite.new()
		christmasHead.texture = load("res://Assets/Shop/Shopkeeper/Shopkeeper_Head_Christmas.png")
		head.add_child(christmasHead)
		christmasHead.position = Vector2(12, - 70)
		head.self_modulate.a = 0

func updateLocale():
	hint.bbcode_text = "[center]" + ToolTip.highlight(Util.tr_nbs("HINT_Shopkeeper"), true)

func onReturnToTitle():
	Game.speechBubble.z_index = 10

func onReturnedToTitle():
	Game.speechBubble.shutUp()

func onHover():
	
	if Game.draggedItem == null:
		hint.show()

func onHoverEnd():
	hint.hide()

func onShopkeeperClicked():
	if Game.speechBubble.isSpeaking(): return
	
	Game.speechBubble.say(Util.tr_nbs("TIP" + str(curTip)))
	curTip = (curTip + 1) % numTips
	

func onShopOpened():
	Game.speechBubble.z_index = 33
	
	showCraftFlavorText = Util.flip(0.15)
	
	if Game.runWasJustContinued:
		Game.speechBubble.say(Util.tr_nbs("CONTINUE" + randNum(5)))
	else:
		if Game.curRound == 1:
			if Game.getNumStartedRuns() == 1:
				tutorial()
			else:
				if Game.runsStartedThisSession == 1:
					hello()
				else:
					helloAgain()
		
		elif Game.curRound == Game.SUBCLASS_ROUND:
			if ( not Game.isTutorialDone(Game.TutorialSteps.Subclass)):
				Game.speechBubble.say(Util.tr_nbs("TUTORIAL_Subclass"), 10)
				Game.setTutorialDone(Game.TutorialSteps.Subclass)
				
			else:
				Game.speechBubble.say(Util.tr_nbs("SUBCLASS" + randNum(3)), 10)
		
		elif (Game.curRound == Game.SKILL_ROUND1 or 
					Game.curRound == Game.SKILL_ROUND2):
			
			if not Game.isTutorialDone(Game.TutorialSteps.Skill):
				Game.speechBubble.say(Util.tr_nbs("TUTORIAL_Skill"), 10)
				Game.setTutorialDone(Game.TutorialSteps.Skill)
			else:
				Game.speechBubble.say(Util.tr_nbs("SKILL" + randNum(6)), 12)
		
		elif Game.shopSceneNode.rolledUnique:
			var itemName = Game.shopSceneNode.rolledUnique.getTranslatedName(true)
			Game.speechBubble.say(Util.tr_nbs("UNIQUE_ITEM" + randNum(2)
				).replace("$item", itemName), 8)
		





		
		elif Game.numTimesOutOfStamina >= 4 and Game.PLAYER.getTotalStaminaUsage() >= 2:
			Game.speechBubble.say(Util.tr_nbs("OUTOFSTAMINA" + randNum(3)))
		
		else:


			if (Game.itemsAreFusing and 
				not Game.isTutorialDone(Game.TutorialSteps.Lock) and 
				Game.getNumCraftedItems() % 4 == 0):
				
				pass
			else:
				var t = Game.getNextTutorialText()
				
				if t != null:
					Game.speechBubble.say(t[0], 10, t[1])
					
				else:
					if Game.curRound == Game.MAX_ROUNDS:
						Game.speechBubble.say(Util.tr_nbs("LASTROUND" + randNum(3)))
					
					elif Game.justStartedSurvivalMode:
						Game.speechBubble.say(Util.tr_nbs("SURVIVAL" + randNum(4)))
					
					else:
						match Game.getLastRoundResult():
							Game.RoundResult.Win:
								if ( not Game.isTutorialDone(Game.TutorialSteps.Wins) and 
									Game.wins == 1):
									Game.speechBubble.say(Util.tr_nbs("TUTORIAL_Wins"), 10)
									Game.setTutorialDone(Game.TutorialSteps.Wins)
								else:
									onWin()
							Game.RoundResult.Loss:
								if ( not Game.isTutorialDone(Game.TutorialSteps.Tries) and 
									Game.tries == 4):
									Game.speechBubble.say(Util.tr_nbs("TUTORIAL_Tries"), 10)
									Game.setTutorialDone(Game.TutorialSteps.Tries)
								else:
									onLoss()


func tutorial():
	Game.speechBubble.say(Util.tr_nbs("TUTORIAL_BUY"), 30)
	Game.connect("item_bought", self, "onBuy_tutorial", 
		[Game.speechBubble.getSequenceNumber()], CONNECT_ONESHOT)

func onBuy_tutorial(item, onSale, sequenceNum):
	if Game.speechBubble.getSequenceNumber() == sequenceNum:
		Game.speechBubble.shutUp()
	
	if Game.usingController:
		var text = Util.tr_nbs("TUTORIAL_ROTATE_CONTROLLER")
		var icon1 = ControllerIcons.getIconFromAction("rotate_left_button_controller")
		var icon2 = ControllerIcons.getIconFromAction("rotate_right_button_controller")
		text = text.format({
			"button1": Util.imageToBbcode(icon1, 40), 
			"button2": Util.imageToBbcode(icon2, 40)})
		Game.speechBubble.say(text, 5, Game.TutorialSteps.Rotate)
	else:
		Game.speechBubble.say(Util.tr_nbs("TUTORIAL_ROTATE"), 5, 
			Game.TutorialSteps.Rotate)

func onLoss():
	if Game.getTries() == 1:
		Game.speechBubble.say(Util.tr_nbs("LASTTRY" + randNum(3)))
		
	else:
		var n: String
		if Game.getTries() > 1:
			n = randNum(14)
		else:
			n = randNum(13)
		
		var t = Util.tr_nbs("LOST" + n)
		
		if n == "14":
			t = t.replace("$tries", str(Game.getTries()))
		
		Game.speechBubble.say(t)

func onWin():
	var n = randNum(15)
	var t = Util.tr_nbs("WON" + n)
	
	if n == "15":
		t = t.replace("$wins", str(Game.getNumWins()))
	
	Game.speechBubble.say(t)

func hello():
	Game.speechBubble.say(Util.tr_nbs("HELLO" + randNum(4)))

func helloAgain():
	Game.speechBubble.say(Util.tr_nbs("HELLO_AGAIN" + randNum(5)))

func onBuy(item, onSale):
	if (item.isSubclassItem() and 
		item.isGateItem() and 
		item.ownerType == Item.Owner.PlayerStorageBox):
			
			Game.speechBubble.shutUp()
			Game.speechBubble.say(Util.tr_nbs("STORAGE_HINT").replace("$item", 
				item.getTranslatedName(true)), 6, true)
			return
	
	if Game.speechBubble.isSpeaking(): return
	
	if ( not Game.isTutorialDone(Game.TutorialSteps.Stars) and 
		item.getNumAffectedCells() > 0):
			var t = Util.tr_nbs("TUTORIAL_Stars")
			t = t.replace("$star", Util.getIcon("affected"))
			Game.speechBubble.say(t, 10)
			Game.setTutorialDone(Game.TutorialSteps.Stars)
	else:
		var rng = Util.rng.randf()
		if rng < 0.15:
			var flavor = item.getFlavorText()
			if flavor != "" and rng < 0.07:
				Game.speechBubble.say(flavor)
			elif onSale:
				Game.speechBubble.say(Util.tr_nbs("BUY_SALE" + randNum(7)).replace("$item", item.getTranslatedName(true)))
			elif item.getRarity() >= Item.Rarity.Legendary:
				Game.speechBubble.say(Util.tr_nbs("BUY_RARE" + randNum(6)).replace("$item", item.getTranslatedName(true)))
			else:
				Game.speechBubble.say(Util.tr_nbs("BUY_NORMAL" + randNum(12)).replace("$item", item.getTranslatedName(true)))
		
func onSell(item):
	if Game.speechBubble.isSpeaking(): return
	var rng = Util.rng.randf()
	if rng < 0.25:
		Game.speechBubble.say(Util.tr_nbs("SELL" + randNum(5)).replace("$item", item.getTranslatedName(true)))

func onStartHovered():
	pass

func onStartPressed():
	say("START", 4)

func onCraftingReady():
	if not craftingTipShown and Game.getNumCraftedItems() == 0:
		Game.speechBubble.shutUp()
		Game.speechBubble.say(Util.tr_nbs("CRAFTING1"), 8)
		craftingTipShown = true

func onCraft(_itemDescriptor):
	
	if ( not Game.isTutorialDone(Game.TutorialSteps.Lock) and 
		Game.getNumCraftedItems() % 4 == 1 and 
		not Game.speechBubble.isGivingTutorial()):
			giveLockHint()
	elif not Game.speechBubble.isGivingTutorial() and showCraftFlavorText:
		var flavor = _itemDescriptor.getFlavorText()
		if flavor != "":
			Game.speechBubble.say(flavor)
			showCraftFlavorText = false











func giveLockHint():
	Game.speechBubble.shutUp()
	if Game.usingController:
		var text = Util.tr_nbs("TUTORIAL_Lock_CONTROLLER")
		text = text.format({"button": Util.getControllerIconBbcode("lock_combining_controller")})
		Game.speechBubble.say(text, 8, Game.TutorialSteps.Lock)
	else:
		Game.speechBubble.say(Util.tr_nbs("TUTORIAL_Lock"), 8, Game.TutorialSteps.Lock)

func randNum(numVariants: int) -> String:
	return String(Util.rng.randi_range(1, numVariants))

func say(code, numVariants):
	if Game.speechBubble.isSpeaking(): return
	Game.speechBubble.say(tr(code + randNum(numVariants)))

func onSpeechbubbleClosed():
	pass

var reaction = null
const reactionFormat = "[center][shake level={level}]{exclamation}"
const exclamations = ["?", "!", "?!", "??", "!!", "!?"]

func onDecorationDestructed():
	if Game.speechBubble.isSpeaking(): return
	
	
	if reaction == null or not reaction.is_inside_tree():
		reaction = ObjectPool.instance(destructReactionScene)
		add_child(reaction)
		reaction.bbcode_text = reactionFormat.format({
			"level": Util.rng.randi_range(0, 3) * 10, 
			"exclamation": Util.pickRandomElement(exclamations)
		})
		reaction.get_node("AnimationPlayer").play("React")
