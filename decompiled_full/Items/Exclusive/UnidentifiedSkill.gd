extends Item

const revealPulseScene = preload("res://Items/Animations/SkillRevealPulse.tscn")
const revealSound = preload("res://Assets/Sound/Reveal.ogg")

var skillPool

func _ready():
	connect("dropped", self, "onDropped")
	if ownerType == Owner.Shop:
		call_deferred("getSkillPool")

func getSkillPool():
	skillPool = ItemBook.getSkillPool()



func onDropped(dropRes):
	if (wasAddedToInventory(dropRes) or 
		dropRes == DropResult.AddedToStorageBox):
		
		prepareReplacement()
		var skill = skillPool.pick_random()
		call_deferred("identifySkill", dropRes, skill)

func identifySkill(dropResult, skillDescriptor):
	
	var skill = ItemBook.generateItem(skillDescriptor)
	if wasAddedToInventory(dropResult):
		inventory.replaceItem(self, skill)
	else:
		Game.STORAGEBOX.removeItem(self)
		collisionShape.disabled = true
		discard()
		Game.playerNode.add_child(skill)
		
		skill.global_position = global_position
		skill.addToStorageBox(true, true, true, global_position)
	
	Sound.playSound(revealSound, 6)
	var pulse = ObjectPool.instance(revealPulseScene)
	Game.playerNode.add_child(pulse)
	pulse.global_position = global_position
	pulse.get_node("AnimationPlayer").play("RevealSkill")
	Game.saveRunState()
	
	skill.onBought()
	finishReplacement()


func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	var string
	if wrapInColor:
		string = Util.tr("TOOLTIP_Always Offered2").format(
			{"round1": Util.highlight(descriptor.appearRounds[0]), 
				"round2": Util.highlight(descriptor.appearRounds[1])})
	else:
		string = Util.tr("TOOLTIP_Always Offered2").format(
			{"round1": descriptor.appearRounds[0], 
				"round2": descriptor.appearRounds[1]})
	descr += "\n\n" + string
	return descr

func getRelatedItems():
	if ownerType == Owner.Shop:
		return skillPool
	else:
		return ItemBook.getFullSkillPool()

func getRelatedItemColumns() -> int:
	return 6

func getRelatedItemHeight() -> int:
	return 80
