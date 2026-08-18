extends Weapon

const stunParticles = preload("res://Items/Particles/StunParticles.tscn")

onready var manaNeeded: = int(getP("manat"))
onready var blind: = int(getP("blind"))
onready var numDebuffs: = int(getP("cleanse"))
onready var dmgReductionTimer = $DmgReductionTimer
onready var healthThreshold: = getP("healtht") / 100.0 - 0.0001
onready var bonusSpeed: = getP("speed") / 100.0
onready var damReduction: = getP("dmgreduction")

var hasActivated: bool

func _ready():
	sprite.offset = Vector2.ZERO

func canAffect(item):
	return item.hasCooldown() or item.gainsStack(Stack.Mana)

func onPrepare():
	updateShaderRotation()
	hasActivated = false
	connectForCombat(character(), "character_damaged", "onDamaged")

func onDealtDamage(damageRes: DamageResult):
	if (damageRes.hasHit() and 
		character().getMana() >= manaNeeded):
		
		var event = useMana(manaNeeded, damageRes.event)
		var duration = getP_m("dur_blind")
		giveStacksTemporary(opponent(), Game.EventType.Blind, 
			blind, duration, event)
		
		if rollChance():
			stun(getP_m("dur_stun"), event)
			var particles = ObjectPool.particleOneShot(stunParticles, sprite)
			particles.position = Vector2(175, - 144)
		
		cleanseRandomDebuffs(numDebuffs, event)

func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		
		for item in getAffectedItems():
			item.addSpeed(bonusSpeed)
			item.changeAmplificiationChancePercent(Game.EventType.Mana, getChance2())
		
		dmgReductionTimer.start(getP_m("dur_dmgreduction"))
		character().changeDamageResistance(damReduction)
		
		giveBlock(getBlock(), true, event)
		

func getTriggerPriority() -> int:
	return Priority.High + 2

func onDmgReductionTimerTimeout():
	character().changeDamageResistance( - damReduction)

func onCombatEnd():
	dmgReductionTimer.stop()

func showCooldown(progress: float):

	nonRotatedProgress = progress
	progress = rotateProgress(progress * 1.0 + 0.05)
	for sprite in spritesWithShadows:
		sprite.material.set_shader_param("progress", progress)

func clearSpriteMaterial():
	pass

func giveProgressMaterial():
	pass

func updateShaderRotation():
	var dir = Vector2.DOWN.rotated( - global_rotation)
	for i in range(0, spritesWithShadows.size()):
		spritesWithShadows[i].material.set_shader_param("direction", dir)
	.updateShaderRotation()
	
	if nonRotatedProgress == 0:
		showCooldown(0)

func getTextureSize() -> Vector2:
	return sprite.texture.get_size() * Vector2(1.5, 2.0) * sprite.global_scale
