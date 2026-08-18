extends ToolTip
class_name ItemToolTip

enum TextEffect{
	None = 0, 
	Water = 1, 
	Spooky = 2, 
	Shaky = 3, 
	Ice = 4, 
	Fire = 5, 
	Rainbow = 6, 
	Vampiric = 7, 
	Gold = 8, 
	Light = 9, 
	Nature = 10, 
	Magic = 11, 
	Lightning = 12, 
	Stompy = 13, 
	Mercury = 14, 
	Steel = 15, 
	Dog = 16, 
	Dog2 = 17, 
	Spring = 18, 
	Hyper = 19, 
	Stone = 20, 
	Poison = 21, 
	NotSet = - 1
}

const propertyScene = preload("res://Interface/Tooltips/TooltipProperty.tscn")

const descriptionScene = preload("res://Interface/Tooltips/Description.tscn")
const dividerScene = preload("res://Interface/Tooltips/TooltipDivider.tscn")
const typeIconScene = preload("res://Interface/Tooltips/TypeIcon.tscn")
const classIconScene = preload("res://Interface/Tooltips/ClassIcon.tscn")

const MAX_MOUSE_SPEED = 15.0

var poolingHandle

var animation
var propertyContainer
var hboxContainer
var marginContainer
var descrLabel
var rarityLabel
var typeLabel
var typesContainer
var extraTypesLabel
var spacer2
var divider1
var divider2

var item
var properties: Dictionary
var references = []
var sizeChanged: bool
var toReturn = []
var stackDescriptionNodes = []
onready var framesUntilVisible: = 0


onready var subDescriptionPosition = marginContainer
onready var propPosition = nameLabel

static func highlight(text: String, _wave = false, _bold = false):
	var paramColor = Color(1, 0.890196, 0.219608)
	return Util.wrapInColor_fixed(text, paramColor)

func preset():
	vboxcontainer = $VBoxContainer
	marginContainer = $VBoxContainer / MarginContainer
	descrLabel = $VBoxContainer / MarginContainer / Description
	animation = $AnimationPlayer
	propertyContainer = $VBoxContainer / PropertyContainer
	hboxContainer = $VBoxContainer / HBoxContainer
	rarityLabel = $VBoxContainer / HBoxContainer / Rarity
	typeLabel = $VBoxContainer / HBoxContainer / HBoxContainer / Type
	extraTypesLabel = $VBoxContainer / ExtraTypes
	typesContainer = $VBoxContainer / HBoxContainer / HBoxContainer
	divider1 = $VBoxContainer / Divider1
	divider2 = $VBoxContainer / Divider2
	spacer2 = $VBoxContainer / HBoxContainer / Spacer2
	











const bagEffectIcon = "[i][img=0x28]res://Interface/Tooltips/AffectsInside.png[/img][/i]"

func setItem(_item):





	set_physics_process(false)
	spacer2.rect_min_size.x = 15
	vboxcontainer.rect_size.x = 470
	divider2.texture = divider1.texture
	divider2.material = divider1.material
	
	
	var lastTooltipDuration = Game.lastHideItemTooltipFrame - Game.lastShowItemTooltipFrame
	var timeSinceLastHide = Util.getFrameCounter_process() - Game.lastHideItemTooltipFrame
	
	item = _item
	
	
	
	Game.lastShowItemTooltipFrame = - 1
	
	if _item.spotlight or item.ownerType == item.Owner.Shop:
		Game.lastBagTooltipWasDelayed = false
		setVisible()
	else:
		if lastTooltipDuration > 5 or Game.lastBagTooltipWasDelayed or timeSinceLastHide > 10:
			if _item.isBag() and _item.placed and ( not Game.lastTooltipWasBag or timeSinceLastHide > 10):
				
				Game.lastBagTooltipWasDelayed = true
				
				setVisibleIn(3)
			else:
				Game.lastBagTooltipWasDelayed = false
				setVisible()
		else:
			if _item.isBag() and _item.placed:
				Game.lastBagTooltipWasDelayed = true
			else:
				Game.lastBagTooltipWasDelayed = false
				
			setVisibleIn(6)
	
	Game.lastTooltipWasBag = _item.isBag() and _item.placed
	
	
	nameLabel.bbcode_text = ""
	
	nameLabel.push_align(RichTextLabel.ALIGN_CENTER)
	
	if Settings.getVal(Settings.Setting.text_effects):
		if item.getTextEffect() != TextEffect.None:
			nameLabel.append_bbcode(str("[item s=", item.getTextEffect(), "]"))
	
	nameLabel.add_text(item.getTranslatedName())
	
	updateTooltip(true)
	
	
	if item.descriptor.isNeutral():
		var classIcon = ObjectPool.instance(classIconScene)
		toReturn.push_back(classIcon)
		classIcon.setClass( - 1)
		
		hboxContainer.add_child(classIcon)
		hboxContainer.move_child(classIcon, 1)
	else:
		var pos = 1
		for classI in Game.getNumClasses():
			if item.descriptor.isAvailableFor(classI):
				var classIcon = ObjectPool.instance(classIconScene)
				toReturn.push_back(classIcon)
				classIcon.setClass(classI)
				
				hboxContainer.add_child(classIcon)
				hboxContainer.move_child(classIcon, pos)
				pos += 1
	
	extraTypesLabel.text = ""
	extraTypesLabel.hide()
	
	rarityLabel.text = item.getTranslatedRarity()
	rarityLabel.set("custom_colors/font_color", Game.rarityColors[item.getRarity()].lightened(0.6))
	
	
	var types = item.getTypes()
	var numStaticTypes = item.getNumStaticTypes()
	var numDynamicTypes = types.size() - numStaticTypes
	typeLabel.show()
	
	if Game.USE_ICONS:
		for i in range(types.size() - 1, - 1, - 1):
			
			
			var iconName = item.descriptor.getTypeName(types[i]).to_lower()
			
			if iconName in Util.iconTextures:
				var typeIcon = ObjectPool.instance(typeIconScene)
				toReturn.push_back(typeIcon)
				typeIcon.texture = Util.iconTextures[iconName]
				typesContainer.add_child(typeIcon)
				typesContainer.move_child(typeIcon, 0)
				var ani = typeIcon.get_node("AnimationPlayer")
				ani.stop()
				if i < numDynamicTypes:
					ani.play("Dynamic")
				else:
					
					ani.play("RESET")
					
			else:
				if i == numDynamicTypes:
					typeLabel.text = item.getTranslatedTypeName(types[i])
				else:
					extraTypesLabel.show()
					if extraTypesLabel.text != "":
						extraTypesLabel.text += "  "
					extraTypesLabel.text += item.getTranslatedTypeName(types[i])
			
		if item.descriptor.isTreasure():
			var typeIcon = ObjectPool.instance(typeIconScene)
			typeIcon.texture = Util.iconTextures["treasure"]
			typesContainer.add_child(typeIcon)
			typesContainer.move_child(typeIcon, 0)
			toReturn.push_back(typeIcon)
	else:
		typeLabel.text = item.getTranslatedTypeName(types[0])
		
		if types.size() > 1:
			extraTypesLabel.show()
			extraTypesLabel.text = ""
			for i in range(1, types.size()):
				if i != 1:
					extraTypesLabel.text += "  "
				extraTypesLabel.text += item.getTranslatedTypeName(types[i])
	
	addReferenceExplanations(references)
	
	
	var bags = item.getTouchedBagsCounted()
	if bags != null:
		for bag in bags:
			var number = bags[bag]
			var bagEffect = bag.getBagEffect(number)
			if bagEffect != "" and bag.canApplyEffect(item):
				var replacement = bag.getTranslatedName()
				if number > 1:
						replacement += " x" + String(number)
				bagEffect = bagEffect.replace("$bag", highlight(replacement))
				addSubDescription(bagEffectIcon + bagEffect, true)
	
	updateSize()
	
	Util.localizeFonts(self)
	
	call_deferred("fixSpillingTypes")
	call_deferred("removeStackDescriptions")
	
	ItemBook.pausePrepare()


func fixSpillingTypes():
	if hboxContainer.rect_size.x > 470:
		typeLabel.hide()
		extraTypesLabel.show()
		extraTypesLabel.text = typeLabel.text + " " + extraTypesLabel.text


func removeStackDescriptions():
	
	if vboxcontainer.rect_size.y > 900:
		for node in stackDescriptionNodes:
			node.hide()
			rect_size.y -= node.rect_size.y

func updateTooltip(init: bool = false):
	sizeChanged = false
	
	
	var description = item.getDescription()
	description = description.replace("\\~", "\n")
	description = description.replace("\\n", "\n")
	description = description.replace(" \n", "\n")
	description = description.replace("\n ", "\n")
	
	if init:
		for keyword in keywords:
			if Game.getNumStartedRuns() > 2 and keyword == "affected":
				continue
			
			var pos = description.find("$" + keyword)
			if pos != - 1 and Util.isNonLatinLetterOrNumber(description[pos + 1 + keyword.length()]):
			
				references.push_back(keyword)
		references = Util.filterDuplicates(references)
	
	description = replaceReferences(description)
	
	if description != "":
		description = scolor_movePunctuation(description)
		descrLabel.bbcode_text = description
		
	else:
		marginContainer.hide()
	
	if item.isWeapon() and item.canDamage():
		var damRange = item.getDamageRange()
		
		addProperty(item.Stat.MaxDamage, Util.tra("TOOLTIP_Damage"), 
			damRange, item.isDamageModified(), 
		String(stepify(item.getDPS(), 0.1)), item.isDPSModified())
	
	var staminaCost = item.getStaminaCost()
	if item.isWeapon():
		var staminaPS = item.getStaminaPerSecond()
		
		addProperty(item.Stat.StaminaCost, Util.tra("TOOLTIP_StaminaCost"), 
			String(stepify(staminaCost, 0.01)), item.isStaminaModified(), 
			String(stepify(staminaPS, 0.1)), item.isStaminaPerSecondModified())

	var baseAccuracy = item.getBaseAccuracy()
	if baseAccuracy != 0:
		var accuracy: String
		if Game.state == Game.State.Combat:
			accuracy = item.getCombatDisplayAccuracy()
		else:
			accuracy = str(item.getAccuracy())
		
		var accuracyStr = accuracy
		if Util.hasSpaceBeforePercent():
			accuracyStr += Util.nonBreakingSpace
		accuracyStr += "%"
		addProperty(item.Stat.Accuracy, Util.tra("TOOLTIP_Accuracy"), 
			accuracyStr, item.isAccuracyModified())
	
	if item.isWeapon() and item.canBeEmpowered():
		var cooldown = item.getModifiedCooldown()
		if cooldown != 0:
			var secondsStr = Util.tra("FORMAT_Second")
			if Util.hasSpaceBeforeSeconds():
				secondsStr = Util.nonBreakingSpace + secondsStr
			addProperty(item.Stat.Cooldown, Util.tra("TOOLTIP_Cooldown"), 
				String(stepify(cooldown, 0.01)) + secondsStr, 
				item.isCooldownModified())
	
	if item.canDamage():
		var critChancePercent = item.getCritChancePercent()
		if critChancePercent != 0:
			addProperty(item.Stat.CritChance, Util.tra("TOOLTIP_CritChance"), 
				item.getDisplayCritChance() + "%", 
				item.StatModified.Positive)
	
	if not init and sizeChanged:
		forceUpdate()
	
func addReferenceExplanations(refs):
	for type in item.getTypes():
		var typeDescr = item.getTypeDescription(type)
		if typeDescr != "":
			var typeName = item.getTranslatedTypeName(type)
			var text = highlight(typeName)
			var cooldown = Util.wrapInColor_fixed(str(stepify(item.getModifiedCooldown(), 0.01)), 
				Util.statColors[item.isCooldownModified()])
			
			typeDescr = typeDescr.format({
				"itemName": highlight(item.getTranslatedName()), 
				"cd": cooldown
				})
			if TranslationServer.get_locale() == "fr":
				text += Util.nonBreakingSpace
			text += ": " + replaceReferences(typeDescr)
			addSubDescription(text, false)
	
	for reference in refs:
		var description = Util.tra(reference + "_DESCR")
		if description == "": continue
		
		var text = ""
		if reference in Util.icons:
			text += Util.getIcon(reference)
		text += highlight(Util.tra(reference + "_NAME"))
		if TranslationServer.get_locale() == "fr":
			text += Util.nonBreakingSpace
		
		if reference == "rage":
			description = description.format({
				"delay": Game.PLAYER.AUTO_RAGE_DELAY, 
				"duration": Game.PLAYER.AUTO_RAGE_DUR
			})
		
		text += ": " + replaceReferences(description)
		addSubDescription(text, true)
		
		stackDescriptionNodes.push_back(toReturn[ - 2])
		stackDescriptionNodes.push_back(toReturn[ - 1])
	
	


func addSubDescription(text: String, darken: bool):
	var divider = ObjectPool.instance(dividerScene)
	toReturn.push_back(divider)
	divider.texture = divider1.texture
	divider.material = divider1.material
	vboxcontainer.add_child_below_node(subDescriptionPosition, divider)
	subDescriptionPosition = divider
	var descr = ObjectPool.instance(descriptionScene)
	if darken:
		descr.modulate = Color(0.960784, 0.960784, 0.960784)
	else:
		descr.modulate = Color(1.1, 1.1, 1.1)
	
	toReturn.push_back(descr)
	text = text.replace("\\~", "\n")
	text = item.insertParameters(text)
	text = scolor_movePunctuation(text)
	descr.bbcode_text = replaceReferences(text)
	vboxcontainer.add_child_below_node(subDescriptionPosition, descr)
	subDescriptionPosition = descr
	

func addProperty(stat: int, _name, value, modified: int, 
	perSecond = null, perSecondModified = 0):
	



	
	
	var prop = properties.get(stat, null)
	if prop == null:




		
		prop = ObjectPool.instance(propertyScene)
		toReturn.push_back(prop)
		propertyContainer.add_child(prop)
		properties[stat] = prop
		sizeChanged = true
		
		var divider = ObjectPool.instance(dividerScene)
		divider.texture = divider1.texture
		divider.material = divider1.material
		propertyContainer.add_child(divider)
		toReturn.push_back(divider)
	
	var icon = Util.weaponIcons[stat]
	prop.setTuple(_name, value, modified, icon)
	
	if perSecond:
		var perSecondStr = str("(", perSecond, "/", Util.tra("FORMAT_Second"), ")")
		prop.setPerSecond(perSecondStr, perSecondModified)


const latinPunctuationCharacters = [".", ",", ":", ")"]

const punctuationCharacters = {
	"zh_Hans_CN": ["。", "，", "：", "）"], 
	"zh_Hant_TW": ["。", "，", "：", "）"]
}

func scolor_movePunctuation(text):
	var chars = punctuationCharacters.get(TranslationServer.get_locale(), latinPunctuationCharacters)
	for i in 2:
		for character in chars:
			text = text.replace("[/sc]" + character, character + "[/sc]")
	return text

func _physics_process(delta):
	framesUntilVisible -= 1
	if framesUntilVisible <= 0:
		set_physics_process(false)
		setVisible()



func setVisibleIn(frames):
	modulate = Color.transparent
	framesUntilVisible = frames
	set_physics_process(true)

func setVisible():
	modulate = Color.white
	Game.lastShowItemTooltipFrame = Util.getFrameCounter_process()
	

func discard():
	Game.lastHideItemTooltipFrame = Util.getFrameCounter_process()
	if Game.lastShowItemTooltipFrame == - 1:
		Game.lastShowItemTooltipFrame = Game.lastHideItemTooltipFrame
	
	
	
	for node in stackDescriptionNodes:
		node.show()
	
	for node in toReturn:
		ObjectPool.returnInstance(node)
	
	toReturn.clear()
	properties.clear()
	references.clear()
	stackDescriptionNodes.clear()
	Util.tryDisconnect(get_tree(), "idle_frame", self, "updateSize")
	
	nameLabel.bbcode_text = ""
	nameLabel.rect_size.y = 0
	descrLabel.bbcode_text = ""
	descrLabel.rect_size.y = 0
	marginContainer.show()
	
	
	ObjectPool.returnInstance(self)
