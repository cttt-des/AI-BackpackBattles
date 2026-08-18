extends Node2D
class_name Character

signal class_changed
signal health_changed_ui
signal max_health_changed_ui
signal max_stamina_changed_ui
signal stamina_regen_changed_ui
signal gained_stamina_ui
signal used_stamina_ui
signal character_died
signal character_insufficient_stamina

enum ID{
	PLAYER = 0, 
	OPPONENT = 1
}

enum Stat{
	Health, 
	MaxHealth, 
	Stamina, 
	MaxStamina, 
	Invulnerable, 
	Stunned, 
	BattleRage, 
	
	ReflectStacks, 
	DebuffResistStacks, 
	CritStacks, 
	DodgeStacks, 
	CritResistStacks, 
	CritResistance, 
	StunResistance, 
	HealEfficiency, 
	DamageResistance, 
	MeleeDmgFactor, 
	RangedDmgFactor, 
	EffectDmgFactor, 
	Unhealing, 
	StaminaRegen, 
	MaxHealthGain
}

const inventoryScene = preload("res://Core/Inventory.tscn")
const AUTO_RAGE_DELAY = 5.0
const AUTO_RAGE_DUR = 4.0

var INVENTORY
var playerId: int
var characterClass = Game.Classes.Ranger
var characterName: String
var chibi = false
var opponent = null
var isDead: bool
var buffs: Dictionary
var maxHealth: float = 30.0
var curHealth: float
var temporaryMaxHealth: float = 0.0
var temporaryMaxHealthGain: float = 1.0
var baseMaxStamina: float
var maxStamina: float = 5.0
var curStamina: float
var temporaryMaxStamina: float = 0.0
var baseStaminaRegen: float = 1.0
var staminaRegen: float = baseStaminaRegen
var allowStaminaOverflow: bool = false
var stunnedDuration: float
var invulnerable: bool = false
var invulnerabilityItem = null
var unhealingAmount: float = 0.0
var healingEfficiency: float = 1.0
var damageResistance: float = 0.0
var damageReduction: int
var dodgeStacks: int = 0
var critResistance: float = 0.0
var critResistStacks: int = 0
var stunResistance: float = 0.0
var debuffResistStacks: int = 0

var debuffReflectStacks: int = 0
var buffProtectStacks: int = 0
var critTokens: int = 0
var battleRageBonusDur: float = 0.0
var bonusFatigueDamage: = 0
var meleeSpikesLimit: = 1.0
var rangedSpikesLimit: = 0.0
var effectSpikesLimit: = 0.0
var meleeVampirismLimit: = 1.0
var rangedVampirismLimit: = 0.0
var empowerDamage: = 1.0
var typedDamageFactors = {}

var accuracyRng = BalancedRng.new()
var critRng = BalancedRng.new()
var critResistanceRng = BalancedRng.new()
var stunResistanceRng = BalancedRng.new()
var spikeDamageSource
var poisonDamageSource
var spriteAnimation
var idleAnimation
var idleAniDefaultSpeed
var attackTween
var combatDefaultPos: Vector2
var invulBubbleVisible: = false
var blindingLightActive: = false
var attackMovingForward: bool
var attackSoundReadyTime: = 0.0
var tickCounter: int
var autoRageItem = null

onready var animation = $AnimationPlayer
onready var combatAnimation = $CombatAnimation
onready var spriteNode = $Mirroring / Sprite
onready var tickTimer = $TickTimer
onready var sprite = $Mirroring / Sprite / Sprite
onready var idleAniSpeedTimer = $Mirroring / Sprite / AnimationSpeedTimer
onready var damageAnimation = $HitAnimation
onready var audioPlayer = $AudioStreamPlayer
onready var invuBubbleAni = $Mirroring / Sprite / InvulnerabilityBubble / AnimationPlayer
onready var invulnerabilityTimer = $InvulnerabilityTimer
onready var battleRageTimer = $BattleRageTimer
onready var autoRageTimer = $AutoRageTimer
onready var battleRageAnimation = $Mirroring / Sprite / BattleRageAura / AnimationPlayer
onready var battleRageParticles = $Mirroring / Sprite / BattleRageParticles
onready var battleRageAura = $Mirroring / Sprite / BattleRageAura
onready var statsDisplay = $CombatUI / StatsDisplay
onready var loseParticles = $Mirroring / LoseParticles
onready var winParticles = $Mirroring / WinParticles
onready var nameBanner = $CombatUI / Sheet / NameBanner
onready var randomClassParticles = get_node_or_null("Mirroring/Sprite/RandomClassParticles")

onready var nameLineEdit = get_node_or_null("ShopUI/NameLineEdit")
onready var nameLabel = $CombatUI / Name
onready var goldPos = get_node_or_null("ShopUI/GoldPos")
onready var damNumberPos = $Mirroring / Sprite / DamageNumberPosition
onready var clickArea = $Mirroring / Sprite / Button
onready var levelUpParticles = get_node_or_null("Mirroring/Sprite/LevelUpParticles")

func _ready() -> void :
	Util.localizeFonts(self)
	
	Util.addFallbackFonts(nameLabel.get("custom_fonts/font"))
	
	INVENTORY = inventoryScene.instance()
	get_parent().add_child(INVENTORY)
	INVENTORY.character = self
	
	if playerId == ID.OPPONENT:
		animation.play("OpponentInit")
		animation.advance(0.01)
		INVENTORY.position = Vector2(position.x - 450, 60)
		
	elif playerId == ID.PLAYER:
		animation.play("StartOnTitle")
		INVENTORY.position = Vector2(position.x - 300, 60)
		Util.addFallbackFonts(nameLineEdit.get("custom_fonts/font"))
	
	spikeDamageSource = DamageSource.new().init(self, DamageSource.Type.Spikes, 1)
	spikeDamageSource.flags = DamageSource.chipDamageFlags + DamageSource.Flags.CanCrit
	
	poisonDamageSource = DamageSource.new().init(self, DamageSource.Type.Poison, 1)
	poisonDamageSource.flags = DamageSource.chipDamageFlags + DamageSource.Flags.CanCrit
	
	for buffType in range(Game.EventType.Block, Game.EventType.Cold + 1):
		buffs[buffType] = Buff.new().init(buffType, self, 
		get_node("CombatUI/" + Game.eventTypeKeys[buffType]), 
		"character_" + Game.eventTypeKeys[buffType].to_lower() + "_changed")
	
	for damageType in DamageSource.Type.values():
		typedDamageFactors[damageType] = 0.0
	
func isPlayer():
	return playerId == ID.PLAYER

func setOpponent(_opponent):
	opponent = _opponent

func setCharacterName(_name: String):
	characterName = _name
	if playerId == ID.PLAYER:
		nameLineEdit.text = characterName
	nameLabel.text = characterName


func showCharacterName():
	nameLabel.text = characterName

func hideCharacterName():
	nameLabel.text = Util.tra("OPPONENT_HIDDEN")

func getClass() -> int:
	return characterClass

func isChibi() -> int:
	return chibi

func setClass(_class: int, _chibi: bool):
	characterClass = _class
	chibi = _chibi
	var classResource = Game.classResources[characterClass]
	if playerId == ID.PLAYER:
		setClassResource(classResource)
	else:
		setSprite(classResource, chibi)
	
	nameBanner.texture = Game.classNameBanners[characterClass]
	
	emit_signal("class_changed")

func setClassResource(classResource: CharacterClass):
	setMaxHealth(classResource.health)
	baseMaxStamina = classResource.stamina
	setMaxStamina(baseMaxStamina)
	setSprite(classResource, chibi)
	
func setSprite(classResource, _chibi: bool):
	chibi = _chibi
	
	
	var spriteScene
	if Game.isClassUnlocked():
		
		if not chibi or not classResource.chibiSprite:
			spriteScene = classResource.sprite
		else:
			spriteScene = classResource.chibiSprite
	else:
		spriteScene = classResource.notUnlockedSprite
		
	if not spriteScene: return
	
	sprite.queue_free()
	sprite = spriteScene.instance()
	spriteNode.add_child(sprite)
	spriteAnimation = sprite.get_node("SpriteAnimationPlayer")
	idleAnimation = sprite.get_node("IdleAnimationPlayer")
	idleAniDefaultSpeed = idleAnimation.playback_speed

func titleToShop():
	animation.play("EnterShopFromTitle")
	playSound(Game.classResources[characterClass].getRunStartSound())
	randomClassParticles.deactivate()

func shopEntered():
	opponent = null
	

func shopToCombat():
	animation.advance(100)
	animation.play("RESET")
	animation.advance(100)
	animation.play("EnterCombatFromShop")
	
func combatToShop():
	if playerId == ID.PLAYER:
		call_deferred("cleanse")
		animation.play("EnterShopFromCombat")
	else:
		animation.play("OpponentLeaveCombat")

func combatToTitle():
	if playerId == ID.PLAYER:
		call_deferred("cleanse")
		animation.play("CombatToTitle")
		animation.queue("StartOnTitle")
	else:
		animation.play("OpponentLeaveCombat")

func shopToTitle():
	animation.play("StartOnTitle")

func finishAnimations():
	animation.advance(100)
	call_deferred("finishAnimations_deferred")

func finishAnimations_deferred():
	invuBubbleAni.advance(100)
	battleRageAnimation.advance(100)
	battleRageParticles.restart()
	battleRageParticles.emitting = false

func playSound(stream, volume = 0, pitch = 1.0, force = false):
	if force:
		audioPlayer.stop()
	
	if not audioPlayer.playing:
		audioPlayer.stream = stream
		audioPlayer.volume_db = volume - 3
		audioPlayer.pitch_scale = pitch + 0.1
		audioPlayer.play()


func prepare():
	staminaRegen = baseStaminaRegen
	var bonusHealth = getMaxHealth() * ((CustomRules.getHealthMultiplier() - 100.0) / 100.0)
	changeMaxHealthTemporary(bonusHealth)
	
	accuracyRng.reset()
	critRng.reset()
	critResistanceRng.reset()
	stunResistanceRng.reset()
	
	if Game.isBelowLeague(Game.Leagues.Master) or Game.curMode == Game.Mode.Lobbies:
		if playerId == ID.PLAYER:
			accuracyRng.setBias( - 0.2)
			critRng.setBias( - 0.2)
		else:
			accuracyRng.setBias(0.2)
			critRng.setBias(0.2)
	
	autoRageItem = null
	var hasBattleRageStarter = false
	for item in INVENTORY.getItems():
		if item.hasTag(Item.Tag.BattleRage):
			hasBattleRageStarter = true
			break
	
	if not hasBattleRageStarter:
		var battleRageItems = []
		for item in INVENTORY.getItemsAndGems():
			if item.isBattleRageItem():
				battleRageItems.push_back(item)
		
		if not battleRageItems.empty():
			autoRageItem = battleRageItems.pick_random()

func combatStart():
	stunnedDuration = 0.0
	set_physics_process(true)
	combatDefaultPos = spriteNode.position
	tickCounter = 0
	tickTimer.start()
	
	if autoRageItem != null:
		autoRageTimer.start(AUTO_RAGE_DELAY)

func combatEnd():
	set_physics_process(false)
	tickTimer.stop()
	attackMovingForward = false
	
	for buff in buffs:
		buffs[buff].combatEnd()
	battleRageTimer.stop()
	autoRageTimer.stop()
	invulnerabilityTimer.stop()

func cleanse():
	isDead = false
	temporaryMaxHealth = 0
	temporaryMaxHealthGain = 1.0
	staminaRegen = baseStaminaRegen
	healToFull()
	emit_signal("max_health_changed_ui")
	setTemporaryMaxStamina(0)
	fillUpStamina()
	endStun()
	setBlock(0)

	for buffType in buffs:
		buffs[buffType].reset()
	
	if invulBubbleVisible:
		playInvulnerableAnimation(false)
	
	invulnerable = false
	invulnerabilityItem = null
	
	damageResistance = 0.0
	damageReduction = 0
	dodgeStacks = 0
	critResistance = 0.0
	critResistStacks = 0
	stunResistance = 0.0
	unhealingAmount = 0.0
	healingEfficiency = 1.0
	critTokens = 0
	debuffResistStacks = 0
	debuffReflectStacks = 0
	buffProtectStacks = 0
	Util.killTween(attackTween)
	if battleRageAura.visible:
		battleRageAnimation.play("BattleRageEnded")
	battleRageParticles.deactivate()
	battleRageBonusDur = 0.0
	bonusFatigueDamage = 0
	blindingLightActive = false
	meleeSpikesLimit = 1.0
	rangedSpikesLimit = 0.0
	effectSpikesLimit = 0.0
	meleeVampirismLimit = 1.0
	rangedVampirismLimit = 0.0
	empowerDamage = 1.0
	for damageType in DamageSource.Type.values():
		typedDamageFactors[damageType] = 0.0
	
	poisonDamageSource.critChancePercent = 0
	spikeDamageSource.critChancePercent = 0

func onTick():
	if tickCounter % 2 == 0:
		var regen = getRegeneration()
		if regen > 0:
			heal(regen, Game.EventType.Regeneration)
			buffs[Game.EventType.Regeneration].counter.activate()
	else:
		var poison = getPoison()
		if poison > 0:
			poisonDamageSource.setDamage(poison)
			takeDamage(poisonDamageSource)
			buffs[Game.EventType.Poison].counter.activate()
		
	tickCounter += 1

func replayEvent(event):
	var origin = event.getOrigin()
	if origin == Game.EventType.Regeneration:
		buffs[Game.EventType.Regeneration].counter.activate()
		spawnLabel(Game.EventType.Health, event.getAmount(), Game.EventType.Regeneration, randHealNumberPos())
	
	elif origin == Game.EventType.Poison:
		buffs[Game.EventType.Poison].counter.activate()
		spawnLabel(Game.EventType.Poison, event.getParam("damage", 0))
	
	elif origin == Game.EventType.Fatigue:
		spawnLabel(Game.EventType.Fatigue, event.getParam("damage", 0))
	
	elif origin == Game.EventType.Spikes:
		spawnLabel(Game.EventType.Spikes, event.getParam("damage", 0))

const attackForwardSpeed = 2600.0
const attackBackwardSpeed = 1000.0
const jumpSpeed = 300.0
const activateJumpHeight = 40.0

const attackSounds = [
	preload("res://Assets/Sound/Swing1.wav"), 
	preload("res://Assets/Sound/Swing2.wav"), 
	preload("res://Assets/Sound/Swing3.wav")
]

const invuSound = preload("res://Assets/Sound/Invu.wav")
const stunnedSound = preload("res://Assets/Sound/Stun.ogg")

func playAttackAnimation(distance = Util.rng.randf_range(100, 160)):
	if attackMovingForward: return
	
	var curPos = spriteNode.position
	var targetPos = combatDefaultPos + Vector2(distance, 0)
	var duration = (targetPos.x - curPos.x) / attackForwardSpeed * Util.rng.randf_range(0.9, 1.1)
	var backDuration = distance / attackBackwardSpeed * Util.rng.randf_range(0.9, 1.1)
	Util.killTween(attackTween)
	attackTween = create_tween()
	attackTween.tween_property(spriteNode, "position", targetPos, duration)
	attackTween.tween_callback(self, "attackMovingBack")
	attackTween.tween_property(spriteNode, "position", combatDefaultPos, backDuration)
	attackMovingForward = true
	Sound.playSound(Util.pickRandomElement(attackSounds), 0, Util.rng.randf_range(0.8, 1.2))
	if Util.clockTime > attackSoundReadyTime:
		playSound(Game.classResources[characterClass].getAttackSound(), - 3)
		attackSoundReadyTime = Util.clockTime + 0.1

func attackMovingBack():
	attackMovingForward = false

func playActivateAnimation():
	if attackMovingForward: return
	
	var curHeight = spriteNode.position.y
	var targetHeight = combatDefaultPos.y - activateJumpHeight
	
	var duration = (targetHeight - curHeight) / jumpSpeed * Util.rng.randf_range(0.9, 1.1)
	var backDuration = activateJumpHeight / jumpSpeed * Util.rng.randf_range(0.9, 1.1)
	Util.killTween(attackTween)
	attackTween = create_tween()
	attackTween.tween_property(spriteNode, "position:y", targetHeight, duration)
	attackTween.tween_callback(self, "attackMovingBack")
	attackTween.tween_property(spriteNode, "position:y", combatDefaultPos.y, backDuration)
	attackMovingForward = true

func dealDamage(damageSource: DamageSource, triggerEvent = null) -> DamageResult:
	
	playAttackAnimation()
	var res = opponent.takeDamage(damageSource, triggerEvent)
	applyVampirism(res)
	return res

func getName():
	return ["Player", "Opponent"][playerId]

func getCenter():
	return global_position - Vector2(0, 100)

func takeDamage(damageSource: DamageSource, triggerEvent = null) -> DamageResult:
	
	var damageRes = DamageResult.new()
	
	
	damageSource = DamageSource.new().fromDamageSource(damageSource)
	damageRes.damageSource = damageSource
	damageRes.reset()
	
	if isDead:
		return damageRes
	
	var item = null
	if damageSource.origin is Item:
		item = damageSource.origin
	
	var attackEffectCount: = 1
	
	if item != null:
		attackEffectCount += item.rollDoubleAttackEffect()
	
	if damageSource.canMiss():
		var accuracy = damageSource.accuracy
		damageRes.hit = accuracyRng.rollPercent(accuracy)
		if damageRes.hit and dodgeStacks > 0:
			changeDodgeStacks( - 1)
			damageRes.hit = false
	else:
		damageRes.hit = true
	
	
	var pos = randDmgNumberPos()
	var direction = randDmgNumberDir()
	
	
	if item != null and damageSource.isAttack():
		item.preDealDamage_early(damageRes)
		if item.hasPreDealDamageEarlyEffect:
			for i in attackEffectCount:
				item.onPreDealDamage_early(damageRes)
	
	if damageRes.hit:
		damageRes.damage += damageSource.randDamage()
		
		if damageSource.hasType(DamageSource.Type.Fatigue):
			damageRes.damage += bonusFatigueDamage
		
		if damageSource.canCrit():
			var critical = false
			
			var critChancePercent = damageSource.getCritChancePercent()
			if critChancePercent > 0 and critRng.rollPercent(critChancePercent):
				critical = true
			
			if not damageRes.critical and item != null and item.getCritTokens() > 0:
				item.useCritToken()
				critical = true
			
			if not damageRes.critical and opponent.getCritTokens() > 0:
				opponent.useCritToken()
				critical = true
			
			if critical:
				if critResisted():
					Util.spawnBuffLabel(Game.EventType.CriticalResisted, randBuffLabelPos())
				else:
					damageRes.makeCritical()
		
		var activeDmgResi = clamp(damageResistance / 100, - 10, 1)
		damageRes.damage = round(damageRes.damage * (1.0 - activeDmgResi))
		
		
		if damageRes.damageSource.isAttack():
			
			damageRes.damage -= damageReduction
		
		if invulnerable:
			damageRes.damage = 0
		
		EventBus.emitSignal(self, "pre_take_damage", [damageRes])
		
		damageRes.damage -= damageRes.damageReduction
		
		damageRes.damage = max(0, damageRes.damage)
		
		if item != null and damageSource.isAttack():
			item.preDealDamage_late(damageRes)
			if item.hasPreDealDamageLateEffect:
				for i in attackEffectCount:
					item.onPreDealDamage_late(damageRes)
		
		EventBus.emitSignal(self, "pre_take_damage_late", [damageRes])
		damageRes.healthDamage = damageRes.damage
		
		if damageSource.canBeBlocked():
			var curBlock = getBlock()
			if damageRes.damage > curBlock:
				damageRes.healthDamage -= curBlock
				loseBlock(curBlock)
			else:
				loseBlock(damageRes.damage)
				damageRes.healthDamage = 0
				
			
		curHealth -= damageRes.healthDamage
		
		if damageRes.wasCriticalHit():
			spawnLabel(Game.EventType.CriticalDamage, damageRes.damage, item, pos, direction)
		elif damageSource.hasType(DamageSource.Type.Fatigue):
			spawnLabel(Game.EventType.Fatigue, damageRes.damage, item, pos, direction)
		elif damageSource.hasType(DamageSource.Type.Poison):
			spawnLabel(Game.EventType.Poison, damageRes.damage, item, pos, direction)
		elif damageSource.hasType(DamageSource.Type.Spikes):
			spawnLabel(Game.EventType.Spikes, damageRes.damage, item, pos, direction)
		else:
			spawnLabel(Game.EventType.DealDamage, damageRes.damage, item, pos, direction)
		
		
		if playerId == ID.OPPONENT and damageRes.wasCriticalHit() and damageRes.damage > 300:
			SteamHelper.unlockAchievement("BigCrit")
		
		if damageAnimation.current_animation != "Poison":
			damageAnimation.stop()
			if damageRes.healthDamage == 0:
				damageAnimation.play("Block")
			elif damageSource.hasType(DamageSource.Type.Fatigue):
				damageAnimation.play("Fatigue")
			else:
				damageAnimation.play("Hit")
				
			damageAnimation.playback_speed = Util.rng.randf_range(0.9, 1.1)
	else:
		spawnLabel(Game.EventType.MissedAttack, 0, item, pos, direction)
	
	var event
	if item != null:
		event = Game.combatLog.createEvent_Attack(damageRes, triggerEvent)
		item.dealtDamage(damageRes)
	else:
		event = Game.combatLog.createEvent_Damage(damageRes, opponent.playerId, triggerEvent)
	
	damageRes.event = event
	EventBus.emitEvent(self, "character_attacked", event, [damageRes])
	EventBus.emitSignal(self, "character_damaged", [damageRes.healthDamage, damageRes.event])
	
	emit_signal("health_changed_ui")
	
	if (item != null and 
		damageSource.isAttack() and 
		item.hasDealtDamageEffect):
		for i in attackEffectCount:
			item.onDealtDamage(damageRes)
	
	if curHealth <= 0:
		death()
	
	applySpikes(damageRes)
	
	return damageRes

func isVulnerable():
	return not invulnerable

const DMG_NUM_OFFSET = Vector2(50, 70)
const DMG_NUM_CENTER = [Vector2( - 100, - 40), Vector2(100, - 40)]
const HEAL_NUM_CENTER = [Vector2(0, - 40), Vector2(0, - 40)]

const BUFFLABEL_CENTER = [Vector2( - 100, 100), Vector2(100, 100)]
const BUFFLABEL_OFFSET = Vector2(60, 40)

func randDmgNumberPos():
	return global_position + DMG_NUM_CENTER[playerId] + Vector2(
		Util.rng.randf_range( - DMG_NUM_OFFSET.x, DMG_NUM_OFFSET.x), 
		Util.rng.randf_range( - DMG_NUM_OFFSET.y, DMG_NUM_OFFSET.y))

func randHealNumberPos():
	return global_position + HEAL_NUM_CENTER[playerId] + Vector2(
		Util.rng.randf_range( - DMG_NUM_OFFSET.x, DMG_NUM_OFFSET.x), 
		Util.rng.randf_range( - DMG_NUM_OFFSET.y, DMG_NUM_OFFSET.y))

const dmgNumBaseDir: = Vector2(0, - 660)
const dmgNumMinAngle: = deg2rad( - 21)
const dmgNumMaxAngle: = deg2rad( - 3)

func randDmgNumberDir():
	var direction = dmgNumBaseDir
	direction = direction.rotated(Util.rng.randf_range(
		dmgNumMinAngle, dmgNumMaxAngle))
	if playerId == ID.OPPONENT:
		direction.x *= - 1
		
	return direction

func randBuffLabelPos():
	return global_position + BUFFLABEL_CENTER[playerId] + Vector2(
		Util.rng.randf_range( - BUFFLABEL_OFFSET.x, BUFFLABEL_OFFSET.x), 
		Util.rng.randf_range( - BUFFLABEL_OFFSET.y, BUFFLABEL_OFFSET.y))

func spawnLabel(type: int, damage: int, item = null, 
	pos: Vector2 = randDmgNumberPos(), 
	direction: Vector2 = randDmgNumberDir()):
	
	var setting = Settings.getVal(Settings.Setting.damage_numbers)
	
	if setting == Settings.DMG_NR_ALL or setting == Settings.DMG_NR_CHAR:
		if type == Game.EventType.MissedAttack:
			Util.spawnMissLabel(pos, direction * 0.8)
		else:
			Util.spawnNumberLabel(type, pos, direction, damage)
	
	
	if item != null and item is Item:
		item.spawnLabel(type, damage)

func applySpikes(damageRes: DamageResult):
	if getSpikes() > 0 and damageRes.canTriggerSpikes():
		var spikesLimit: float
		if damageRes.damageSource.hasType(DamageSource.Type.Ranged):
			spikesLimit = rangedSpikesLimit
		else:
			spikesLimit = meleeSpikesLimit
		
		if damageRes.damageSource.hasType(DamageSource.Type.Effect):
			spikesLimit = max(effectSpikesLimit, spikesLimit)
		
		var spikeDam = min(getSpikes(), round(damageRes.damage * spikesLimit))
		if spikeDam > 0:
			spikeDamageSource.setDamage(spikeDam)
			opponent.takeDamage(spikeDamageSource, damageRes.event)
			buffs[Game.EventType.Spikes].counter.activate()
	
func applyVampirism(damageRes: DamageResult):
	if getVampirism() > 0 and damageRes.canTriggerVampirism():
		var vampLimit: float
		if damageRes.damageSource.hasType(DamageSource.Type.Ranged):
			vampLimit = rangedVampirismLimit
		else:
			vampLimit = meleeVampirismLimit
		
		var healAmount = min(getVampirism(), round(damageRes.damage * vampLimit))
		if healAmount > 0:
			heal(healAmount, Game.EventType.Vampirism, damageRes.event)
			buffs[Game.EventType.Vampirism].counter.activate()

func heal(amount, origin = null, triggerEvent = null):
	amount *= getHealingEfficiency()
	amount = round(amount)


	
	var missingHealth = getMaxHealth() - curHealth
	var overheal = max(0, amount - missingHealth)
	curHealth += amount
	curHealth = min(curHealth, getMaxHealth())
	
	emit_signal("health_changed_ui")
	spawnLabel(Game.EventType.Health, amount, origin, randHealNumberPos())
	
	var event = Game.combatLog.createEvent_Heal(amount, playerId, origin, triggerEvent)
	
	if origin:
		if origin is Item:
			origin.addMetric(Game.ItemMetrics.Heal, amount)
			origin.addMetric(Game.ItemMetrics.Overheal, overheal)
		else:
			Game.combatLog.snapshotMetric(playerId, Game.ItemMetrics.Heal, origin, amount)
			Game.combatLog.snapshotMetric(playerId, Game.ItemMetrics.Overheal, origin, overheal)
	
	EventBus.emitEvent(self, "character_healed", event, [event.getAmount(), event])
	if overheal > 0:
		EventBus.emitSignal(self, "character_overhealed", [overheal, event])
	
	if getUnhealing() > 0:
		
		var unhealing = ceil(amount * getUnhealing() * (1 + typedDamageFactors[DamageSource.Type.Unhealing]))
		if unhealing > 0:
			Game.unhealingDamageSource.setDamage(unhealing)
			opponent.takeDamage(Game.unhealingDamageSource, event)


func healToFull():
	curHealth = getMaxHealth()
	emit_signal("health_changed_ui")

func reincarnate(healAmount: int, isHeal: bool, item, triggerEvent):
	setCurrentHealth(0)



	healAmount = min(getMaxHealth(), healAmount)
	setCurrentHealth(healAmount)
	var event = Game.combatLog.createEvent_Reincarnate(item, healAmount, triggerEvent)
	item.addMetric(Game.ItemMetrics.Heal, healAmount)
	EventBus.emitEvent(self, "reincarnated", event, [event])
	return event

func getMaxStamina():
	return maxStamina + temporaryMaxStamina

func gainStamina(amount, item = null, triggerEvent = null):
	
	curStamina += amount
	
	if not allowStaminaOverflow:
		clampStamina()
	
	if item != null:
		var event = Game.combatLog.createEvent_Stamina(amount, item, playerId, triggerEvent)
		EventBus.logEvent(event)
		item.staminaChanged(amount, Item.StackChangeType.Added_Player)
		Util.spawnLabelOnItem(Game.EventType.Stamina, item, amount)
		
	


func addStamina(amount):
	curStamina += amount
	clampStamina()

func clampStamina():
	curStamina = clamp(curStamina, 0, getMaxStamina())

func fillUpStamina():
	addStamina(maxStamina)

enum StaminaResult{
	Sufficient, 
	Insufficient
}

func useStamina(amount):
	allowStaminaOverflow = true
	EventBus.emitSignal(self, "character_pre_use_stamina", [amount])
	allowStaminaOverflow = false
	
	if curStamina >= amount:
		curStamina = max(curStamina - amount, 0)
		clampStamina()
		EventBus.emitSignal(self, "character_used_stamina", [amount])
		
		return StaminaResult.Sufficient
	else:
		clampStamina()
		
		return StaminaResult.Insufficient


func drainStamina(amount, item, triggerEvent = null):
	var drained = min(curStamina, amount)
	curStamina -= drained
	var event = Game.combatLog.createEvent_DrainStamina(drained, item, playerId, triggerEvent)
	EventBus.logEvent(event)
	item.staminaChanged(drained, Item.StackChangeType.Removed_Opponent)
	return event

func setCurrentHealth(_curHealth):
	curHealth = _curHealth
	emit_signal("health_changed_ui")

func loseHealth(amount, item = null, triggerEvent = null):
	curHealth -= amount
	var pos = randDmgNumberPos()
	var direction = randDmgNumberDir()
	Util.spawnNumberLabel(Game.EventType.LoseHealth, pos, direction, amount)
	var event = null
	if item:
		event = Game.combatLog.createEvent_LoseHealth( - amount, playerId, item, triggerEvent)
		EventBus.emitEvent(self, "character_damaged", event, [event.getAmount(), event])
		
	emit_signal("health_changed_ui")
	
	if curHealth <= 0:
		death()
	
	return event

func setMaxHealth(_maxHealth):
	maxHealth = _maxHealth
	curHealth = maxHealth
	emit_signal("health_changed_ui")

func giveMaxHealth(amount):
	maxHealth += amount
	curHealth += amount
	emit_signal("health_changed_ui")

func getBaseMaxHealth():
	return maxHealth

func getMaxHealth():
	return maxHealth + temporaryMaxHealth

func applyTemporaryMaxHealthGain(amount):
	return round(amount * temporaryMaxHealthGain)



func changeMaxHealthTemporary(amount, item = null, triggerEvent = null):
	if amount != 0:
		temporaryMaxHealth += amount
		
		assert (item == null or amount > 0)
		curHealth += amount
		if item != null:
			var event = Game.combatLog.createEvent_TemporaryMaxHealth(item, amount, triggerEvent)
			EventBus.logEvent(event)
		emit_signal("health_changed_ui")

func changeMaxHealthGain(amount):
	temporaryMaxHealthGain += amount
	Game.combatLog.snapshotCharacterStat(self, Stat.MaxHealthGain, true)

func getTemporaryMaxHealth():
	return temporaryMaxHealth
	
func setTemporaryMaxHealth(tempHealth):
	temporaryMaxHealth = tempHealth
	emit_signal("health_changed_ui")

func getCurrentHealth():
	return curHealth

func getRelativeHealth() -> float:
	return getCurrentHealth() / getMaxHealth()

func getMissingHealth() -> int:
	return int(ceil(getMaxHealth() - getCurrentHealth()))

func reduceMaxHealth(amount):
	maxHealth = max(1, maxHealth - amount)
	curHealth = min(maxHealth, curHealth)
	emit_signal("health_changed_ui")

func getCurrentStamina() -> float:
	return curStamina

func setCurrentStamina(stamina: float):
	curStamina = stamina


func getBaseMaxStamina() -> float:
	return baseMaxStamina


func getMaxBaseStamina() -> float:
	return maxStamina

func getMissingStamina() -> float:
	return getMaxStamina() - getCurrentStamina()

func isFullStamina() -> bool:
	return getMissingStamina() <= 0

func setMaxStamina(_maxStamina):
	maxStamina = _maxStamina
	curStamina = maxStamina
	emit_signal("max_stamina_changed_ui")

func giveMaxStamina(amount):
	maxStamina += amount
	curStamina += amount
	emit_signal("max_stamina_changed_ui")

func reduceMaxStamina(amount):
	maxStamina = max(1, maxStamina - amount)
	curStamina = min(maxStamina, curStamina)
	emit_signal("max_stamina_changed_ui")

func changeBaseMaxStamina():
	if playerId == ID.PLAYER and not staminaUpdateQueued:
		staminaUpdateQueued = true
		call_deferred("recalculateMaxStamina")

var staminaUpdateQueued = false

func recalculateMaxStamina():
	staminaUpdateQueued = false
	maxStamina = getBaseMaxStamina()
	for item in INVENTORY.getItems():
		if item.descriptor == ItemBook.staminaSackDescriptor:
			maxStamina += 1
	curStamina = maxStamina
	emit_signal("max_stamina_changed_ui")

func gainMaxStaminaTemporary(amount, item, triggerEvent, filled: bool = true):
	if amount != 0:
		temporaryMaxStamina += amount
		if filled and amount > 0:
			curStamina += amount
		if item != null:
			var event = Game.combatLog.createEvent_TemporaryMaxStamina(item, amount, triggerEvent)
			EventBus.logEvent(event)
			if filled:
				item.staminaChanged(amount, Item.StackChangeType.Added_Player)
			Util.spawnLabelOnItem(Game.EventType.TemporaryMaxStamina, item, amount)
			
		emit_signal("max_stamina_changed_ui")

func setTemporaryMaxStamina(amount):
	temporaryMaxStamina = amount
	emit_signal("max_stamina_changed_ui")

func death():
	isDead = true
	emit_signal("character_died")
	

func lose():
	loseParticles.activate()
	damageAnimation.play("Lose")

func win():
	winParticles.activate()
	damageAnimation.play("Win")
	spriteAnimation.stop()
	spriteAnimation.playback_speed = 1.0
	spriteAnimation.play("Jump")

func levelUp():
	var color = Game.classResources[Game.curClass].color
	
	if Game.curRound == Game.SUBCLASS_ROUND:
		levelUpParticles.amount = 50
	else:
		levelUpParticles.amount = 35
	
	levelUpParticles.self_modulate = color
	levelUpParticles.activate()
	
	damageAnimation.play("LevelUp")
	spriteAnimation.stop()
	spriteAnimation.playback_speed = 1.0
	spriteAnimation.play("Jump")

func _physics_process(delta: float) -> void :
	if stunnedDuration > 0:
		stunnedDuration -= delta
		if stunnedDuration <= 0:
			endStun()
	
	addStamina(getStaminaRegeneration() * delta)

func makeInvulnerable(invuDur, item, triggerEvent = null):
	invulnerabilityItem = item
	
	if not invulnerable:
		invulnerabilityTimer.start(invuDur)
		invulnerable = true
		playInvulnerableAnimation(true)
		Sound.playSound(invuSound, 4, Util.randPitch(0.1))
	else:
		Util.changeTimer(invulnerabilityTimer, invuDur)
	
	var event = Game.combatLog.createEvent_InvulnerableStart(item, invuDur, playerId, triggerEvent)
	EventBus.emitEvent(self, "character_invulnerable_start", event, [event])
	Game.combatLog.snapshotCharacterStat(self, Stat.Invulnerable, false, event)
	return event

func makeVulnerable(item, triggerEvent = null):
	pass

func invulnerabilityEnded():
	invulnerable = false
	var event = Game.combatLog.createEvent_InvulnerableEnd(invulnerabilityItem, playerId)
	EventBus.emitEvent(self, "character_invulnerable_end", event, [event])
	Game.combatLog.snapshotCharacterStat(self, Stat.Invulnerable, false, event)
	playInvulnerableAnimation(false)
	
func playInvulnerableAnimation(invu):
	if invu:
		invuBubbleAni.play("Invulnerable")
		invulBubbleVisible = true
	else:
		invuBubbleAni.play("Vulnerable")
		invulBubbleVisible = false

func stun(duration, item = null, triggerEvent = null):
	
	if stunResisted():
		Util.spawnBuffLabel(Game.EventType.StunResisted, randBuffLabelPos(), duration)
		var event = Game.combatLog.createEvent_StunResist(item, playerId, triggerEvent)
		EventBus.logEvent(event)
	else:
		stunnedDuration = max(stunnedDuration, duration)
		var event = Game.combatLog.createEvent_Stun(item, duration, playerId, triggerEvent)
		EventBus.emitEvent(self, "character_stunned", event, [event])
		Game.combatLog.snapshotCharacterStat(self, Stat.Stunned, false, event)
		playStunAnimation()
		Sound.playSound(stunnedSound)

func endStun():
	stunnedDuration = 0.0
	Game.combatLog.snapshotCharacterStat(self, Stat.Stunned, true)
	playStunAnimation()

func playStunAnimation(duration = stunnedDuration):
	if duration > 0:
		combatAnimation.play("StunStart")
		Util.spawnBuffLabel(Game.EventType.Stun, randBuffLabelPos(), duration)
	else:
		combatAnimation.play("StunEnd")

func isStunned():
	return stunnedDuration > 0

func getStaminaRegeneration():
	return staminaRegen

func giveStaminaRegeneration(amount):
	staminaRegen += amount
	Game.combatLog.snapshotCharacterStat(self, Stat.StaminaRegen)

func getTotalStaminaUsage():
	var totalStaminaUse = 0.0
	for item in INVENTORY.getItems():
		var staminaUse = item.getStaminaCost()
		if item.getCooldown() > 0:
			staminaUse /= item.getCooldown()
		totalStaminaUse += staminaUse
	return totalStaminaUse







func getStacks(buffType) -> int:
	return buffs[buffType].getStacks()

func getBuffStacks() -> int:
	var stacks = 0
	for buff in Game.getBuffs():
		stacks += getStacks(buff)
	return stacks

func getDebuffStacks() -> int:
	var stacks = 0
	for debuff in Game.getDebuffs():
		stacks += getStacks(debuff)
		
	return stacks

func setStacks(buffType, amount: int):
	buffs[buffType].setStacks(amount)

func setStacksLogged(buffType, amount: int, item = null, triggerEvent = null):
	var curStacks = getStacks(buffType)
	if amount < curStacks:
		loseStacks(buffType, curStacks - amount, item, triggerEvent)
	elif amount > curStacks:
		gainStacks(buffType, amount - curStacks, item, triggerEvent)


func gainStacks(buffType, amount: int, item = null, triggerEvent = null, 
	reflect: bool = false):
	
	return buffs[buffType].gainStacks(amount, item, triggerEvent)

func gainStacksTemporary(buffType, amount: int, duration, item = null, 
	triggerEvent = null, reflect: bool = false):
	
	return buffs[buffType].gainTemporary(amount, duration, item, triggerEvent, reflect)


func loseStacks(buffType, amount: int, item = null, triggerEvent = null):
	return buffs[buffType].loseStacks(amount, item, triggerEvent)

func useStacks(buffType, amount: int, item = null, triggerEvent = null):
	return buffs[buffType].loseStacks(amount, item, triggerEvent, true)

func changeResistChance(buffType, chance):
	buffs[buffType].changeResistChance(chance)


func changeDebuffResistChances(chance):
	for debuff in Game.getDebuffs():
		changeResistChance(debuff, chance)


func changeBuffNullifyChances(chance):
	for buff in Game.getBuffs():
		changeResistChance(buff, chance)

func getBlock():
	return getStacks(Game.EventType.Block)

func setBlock(amount: int):
	setStacks(Game.EventType.Spikes, amount)

func gainBlock(amount: int, item = null, triggerEvent = null):
	return gainStacks(Game.EventType.Block, amount, item, triggerEvent)

func loseBlock(amount, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Block, amount, item, triggerEvent)

func getSpikes():
	return getStacks(Game.EventType.Spikes)

func setSpikes(amount: int):
	setStacks(Game.EventType.Spikes, amount)

func gainSpikes(amount: int, item = null, triggerEvent = null):
	return gainStacks(Game.EventType.Spikes, amount, item, triggerEvent)

func loseSpikes(amount: int, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Spikes, amount, item, triggerEvent)

func getVampirism():
	return getStacks(Game.EventType.Vampirism)

func setVampirism(amount: int):
	setStacks(Game.EventType.Vampirism, amount)

func gainVampirism(amount: int, item = null, triggerEvent = null):
	return gainStacks(Game.EventType.Vampirism, amount, item, triggerEvent)
	
func loseVampirism(amount, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Vampirism, amount, item, triggerEvent)

func getPoison():
	return getStacks(Game.EventType.Poison)

func setPoison(amount: int):
	setStacks(Game.EventType.Poison, amount)

func gainPoison(amount: int, item = null, triggerEvent = null):
	var event = gainStacks(Game.EventType.Poison, amount, item, triggerEvent)
	if amount > 0:
		damageAnimation.stop()
		damageAnimation.play("Poison")
	return event

func losePoison(amount: int, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Poison, amount, item, triggerEvent)

func changePoisonCritChancePercent(amount):
	poisonDamageSource.addCritChancePercent(amount)

func changeSpikesCritChancePercent(amount):
	spikeDamageSource.addCritChancePercent(amount)

func getRegeneration():
	return getStacks(Game.EventType.Regeneration)

func setRegeneration(amount: int):
	setStacks(Game.EventType.Regeneration, amount)

func gainRegeneration(amount: int, item = null, triggerEvent = null):
	return gainStacks(Game.EventType.Regeneration, amount, item, triggerEvent)

func loseRegeneration(amount: int, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Regeneration, amount, item, triggerEvent)

func getLucky():
	return getStacks(Game.EventType.Lucky)

func setLucky(amount: int):
	setStacks(Game.EventType.Lucky, amount)

func gainLucky(amount: int, item = null, triggerEvent = null):
	return gainStacks(Game.EventType.Lucky, amount, item, triggerEvent)

func loseLucky(amount: int, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Lucky, amount, item, triggerEvent)

func getBlind():
	return getStacks(Game.EventType.Blind)

func setBlind(amount: int):
	setStacks(Game.EventType.Blind, amount)

func gainBlind(amount: int, item = null, triggerEvent = null):
	return gainStacks(Game.EventType.Blind, amount, item, triggerEvent)

func loseBlind(amount: int, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Blind, amount, item, triggerEvent)

func getMana():
	return getStacks(Game.EventType.Mana)

func setMana(amount: int):
	setStacks(Game.EventType.Mana, amount)

func gainMana(amount: int, item = null, triggerEvent = null):
	return gainStacks(Game.EventType.Mana, amount, item, triggerEvent)

func useMana(amount: int, item = null, triggerEvent = null):
	var event = useStacks(Game.EventType.Mana, amount, item, triggerEvent)
	
	return event

func loseMana(amount: int, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Mana, amount, item, triggerEvent)

func getEmpower():
	return getStacks(Game.EventType.Empower)

func setEmpower(amount: int):
	setStacks(Game.EventType.Empower, amount)

func gainEmpower(amount: int, item = null, triggerEvent = null):
	return gainStacks(Game.EventType.Empower, amount, item, triggerEvent)

func loseEmpower(amount: int, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Empower, amount, item, triggerEvent)

func getHeat():
	return getStacks(Game.EventType.Heat)

func setHeat(amount: int):
	setStacks(Game.EventType.Heat, amount)

func gainHeat(amount: int, item = null, triggerEvent = null):
	return gainStacks(Game.EventType.Heat, amount, item, triggerEvent)

func loseHeat(amount: int, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Heat, amount, item, triggerEvent)

























func getCold():
	return getStacks(Game.EventType.Cold)

func setCold(amount: int):
	setStacks(Game.EventType.Cold, amount)

func gainCold(amount: int, item = null, triggerEvent = null):
	return gainStacks(Game.EventType.Cold, amount, item, triggerEvent)

func loseCold(amount: int, item = null, triggerEvent = null):
	return loseStacks(Game.EventType.Cold, amount, item, triggerEvent)

func getBuffDamageMod():
	return getEmpower() * empowerDamage

func getBuffAccuracyMod():
	return (getLucky() - getBlind()) * 5














func changeDamageResistance(amount: float, item = null, duration = null, 
	triggerEvent = null):
	
	damageResistance += amount
	Game.combatLog.snapshotCharacterStat(self, Stat.DamageResistance)
	if item != null:
		var event = Game.combatLog.createEvent_DamChange(item, - amount, 
			true, duration, null, triggerEvent)
		EventBus.logEvent(event)

func changeDamageReduction(amount: int):
	damageReduction += amount

func changeDodgeStacks(amount: int):
	dodgeStacks = int(max(0, dodgeStacks + amount))
	Game.combatLog.snapshotCharacterStat(self, Stat.DodgeStacks)

func changeCritResistance(amount: float):
	critResistance += amount
	Game.combatLog.snapshotCharacterStat(self, Stat.CritResistance, true)

func critResisted() -> bool:
	var resisted = critResistanceRng.rollPercent(critResistance)
	if not resisted:
		if critResistStacks > 0:
			critResistStacks -= 1
			Game.combatLog.snapshotCharacterStat(self, Stat.CritResistStacks, true)
			return true
	return resisted

func gainCritResistStacks(num: int):
	critResistStacks += num
	Game.combatLog.snapshotCharacterStat(self, Stat.CritResistStacks, true)

func changeStunResistance(amount: float):
	stunResistance += amount
	Game.combatLog.snapshotCharacterStat(self, Stat.StunResistance, true)

func stunResisted() -> bool:
	return stunResistanceRng.rollPercent(stunResistance)

func giveUnhealing(amount: float):
	unhealingAmount += amount
	Game.combatLog.snapshotCharacterStat(self, Stat.Unhealing)

func reduceUnhealing(amount: float):
	unhealingAmount = max(0.0, unhealingAmount - amount)
	Game.combatLog.snapshotCharacterStat(self, Stat.Unhealing)

func getUnhealing():
	return unhealingAmount

func getHealingEfficiency():
	return max(0.0, healingEfficiency)

func addHealingEfficiency(amount: float):
	healingEfficiency += amount
	Game.combatLog.snapshotCharacterStat(self, Stat.HealEfficiency)

func reduceHealingEfficiency(amount: float):
	healingEfficiency -= amount
	Game.combatLog.snapshotCharacterStat(self, Stat.HealEfficiency)

func getCritTokens():
	return critTokens

func gainCritTokens(amount):
	critTokens += amount
	Game.combatLog.snapshotCharacterStat(self, Stat.CritStacks)

func useCritToken():
	critTokens -= 1
	Game.combatLog.snapshotCharacterStat(self, Stat.CritStacks)

func changeResistStacks(buffType, amount):
	buffs[buffType].changeResistStacks(amount)

func changeDebuffProtectionChance(chance):
	for debuff in Game.getDebuffs():
		buffs[debuff].changeCleanseProtectionChance(chance)

func changeProtectionChance(buffType, chance):
	buffs[buffType].changeCleanseProtectionChance(chance)

func changeBuffProtectionChance(chance):
	for buff in Game.getBuffs():
		buffs[buff].changeCleanseProtectionChance(chance)

func changeDebuffResistStacks(amount):
	debuffResistStacks += amount
	Game.combatLog.snapshotCharacterStat(self, Stat.DebuffResistStacks, true)

func changeDebuffReflectStacks(amount):
	debuffReflectStacks += amount
	Game.combatLog.snapshotCharacterStat(self, Stat.ReflectStacks, true)

func changeBuffProtectStacks(amount):
	buffProtectStacks += amount

func changeReflectChance(debuff, amount):
	buffs[debuff].changeReflectChance(amount)

func changeAllDebuffsReflectChance(amount):
	for debuff in Game.getDebuffs():
		changeReflectChance(debuff, amount)

func changeMeleeSpikesLimit(amount):
	meleeSpikesLimit += amount

func changeRangedSpikesLimit(amount):
	rangedSpikesLimit += amount

func changeEffectSpikesLimit(amount):
	effectSpikesLimit += amount

func changeMeleeVampirismLimit(amount):
	meleeVampirismLimit += amount

func changeRangedVampirismLimit(amount):
	rangedVampirismLimit += amount

func changeEmpowerDamage(amount):
	empowerDamage += amount


func changeTypedDamageFactor(damageType: int, amount):
	typedDamageFactors[damageType] += amount
	for item in INVENTORY.getItems():
		if item.damageSource != null and item.damageSource.hasType(damageType):
			Game.combatLog.snapshotItemTooltipStat(item, Item.Stat.MinDamage)
			Game.combatLog.snapshotItemTooltipStat(item, Item.Stat.MaxDamage)
	
	match damageType:
		DamageSource.Type.Melee:
			Game.combatLog.snapshotCharacterStat(self, Stat.MeleeDmgFactor)
		DamageSource.Type.Ranged:
			Game.combatLog.snapshotCharacterStat(self, Stat.RangedDmgFactor)
		DamageSource.Type.Effect:
			Game.combatLog.snapshotCharacterStat(self, Stat.EffectDmgFactor)

func changeEffectDamageFactor(amount):
	typedDamageFactors[DamageSource.Type.Effect] += amount
	typedDamageFactors[DamageSource.Type.Unhealing] += amount
	for item in INVENTORY.getItems():
		if item.damageSource != null and item.damageSource.hasType(DamageSource.Type.Effect):
			Game.combatLog.snapshotItemTooltipStat(item, Item.Stat.MinDamage)
			Game.combatLog.snapshotItemTooltipStat(item, Item.Stat.MaxDamage)
	Game.combatLog.snapshotCharacterStat(self, Stat.EffectDmgFactor)

func getGoldPos():
	return goldPos.global_position

func _onNameChanged(new_text: String) -> void :
	Game.setPlayerName(new_text)
	nameLabel.text = Game.getPlayerName()

func onSpriteClicked():
	if animation.current_animation != "" and Util.isTweenRunning(attackTween): return
	
	var remainingTime = Util.getRemainingAnimationTime(spriteAnimation)
	if remainingTime > 0.2: return
	
	spriteAnimation.stop()
	spriteAnimation.playback_speed = Util.rng.randf_range(0.8, 1.4)
	spriteAnimation.play("Jump")
	
	if not OS.has_feature("crazygames"):
		playSound(Game.classResources[characterClass].getClickedSound(), 0, Util.rng.randf_range(0.9, 1.0))

func disableClicking():
	clickArea.mouse_filter = Control.MOUSE_FILTER_IGNORE

func enableClicking():
	clickArea.mouse_filter = Control.MOUSE_FILTER_STOP
	
func randAnimationSpeed() -> void :
	idleAnimation.playback_speed = idleAniDefaultSpeed * Util.rng.randf_range(0.8, 1.2)
	
	idleAniSpeedTimer.start(Util.rng.randf_range(2, 5))
	
	sprite.syncIdleAnis()

func isBattleRaging():
	return not battleRageTimer.is_stopped()

func startBattleRage(item, duration, triggerEvent = null, applyBonus = true):
	
	
	var fullDur = duration
	if applyBonus:
		fullDur += battleRageBonusDur
	battleRageTimer.start(fullDur)
	
	var event = Game.combatLog.createEvent_BattleRageStart(item, fullDur, triggerEvent)
	EventBus.emitEvent(self, "battle_rage_started", event, [event])
	Game.combatLog.snapshotCharacterStat(self, Stat.BattleRage, false, event)
	playBattleRageAnimation(true)

func endBattleRage():
	battleRageTimer.stop()
	var event = Game.combatLog.createEvent_BattleRageEnd(playerId)
	EventBus.emitEvent(self, "battle_rage_ended", event, [event])
	Game.combatLog.snapshotCharacterStat(self, Stat.BattleRage, false, event)
	playBattleRageAnimation(false)

func playBattleRageAnimation(rageStart):
	if rageStart:
		battleRageParticles.activate()
		battleRageAnimation.stop()
		battleRageAnimation.play("BattleRage")
		if Game.classResources[characterClass].battleRageSound:
			playSound(Game.classResources[characterClass].battleRageSound, 3)
	else:
		battleRageParticles.deactivate()
		battleRageAnimation.play("BattleRageEnded")

func addBattleRageDuration(dur):
	battleRageBonusDur += dur

func startAutoRage():
	startBattleRage(autoRageItem, AUTO_RAGE_DUR)

func getBonusFatigueDamage():
	return bonusFatigueDamage

func addFatigueDamage(amount):
	bonusFatigueDamage += amount
	EventBus.emitSignal(self, "fatigue_damage_changed")

func takeFatigueDamage(item = null):
	
	takeDamage(Game.fatigueDamageSource)

func startBlindingLight():
	blindingLightActive = true

func endBlindingLight(event = null):
	blindingLightActive = false
	EventBus.emitSignal(self, "blinding_light_ended", [event])

func setStat(stat, value):
	match stat:
		Stat.Health:
			setCurrentHealth(value)
		Stat.MaxHealth:
			setTemporaryMaxHealth(value)
		Stat.Stamina:
			setCurrentStamina(value)
		Stat.MaxStamina:
			setTemporaryMaxStamina(value - maxStamina)
		Stat.Stunned:
			playStunAnimation(value)
		Stat.Invulnerable:
			playInvulnerableAnimation(value)
		Stat.BattleRage:
			playBattleRageAnimation(value)
		
























func getStat(stat):
	match stat:
		Stat.StaminaRegen:
			return (getStaminaRegeneration() - 1) * 100.0
		Stat.Health:
			return getCurrentHealth()
		Stat.MaxHealth:
			return getTemporaryMaxHealth()
		Stat.Stamina:
			return getCurrentStamina()
		Stat.MaxStamina:
			return getMaxStamina()
		Stat.Stunned:
			return stunnedDuration
		Stat.Invulnerable:
			return invulnerable
		Stat.BattleRage:
			return isBattleRaging()
		
		Stat.ReflectStacks:
			return debuffReflectStacks
		Stat.DebuffResistStacks:
			return debuffResistStacks
		Stat.CritStacks:
			return getCritTokens()
		Stat.DodgeStacks:
			return dodgeStacks
		Stat.CritResistStacks:
			return critResistStacks
		Stat.CritResistance:
			return critResistance
		Stat.StunResistance:
			return stunResistance
		Stat.HealEfficiency:
			return (getHealingEfficiency() - 1) * 100
		Stat.DamageResistance:
			return damageResistance
		Stat.MeleeDmgFactor:
			return typedDamageFactors[DamageSource.Type.Melee] * 100
		Stat.RangedDmgFactor:
			return typedDamageFactors[DamageSource.Type.Ranged] * 100
		Stat.EffectDmgFactor:
			return typedDamageFactors[DamageSource.Type.Effect] * 100
		Stat.Unhealing:
			return getUnhealing() * 100
		Stat.MaxHealthGain:
			return (temporaryMaxHealthGain - 1.0) * 100

func queue_free():
	Util.removeLocalizedNode(nameLabel)
	.queue_free()
