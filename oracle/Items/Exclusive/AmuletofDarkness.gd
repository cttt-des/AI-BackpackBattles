extends Item

const amuletColor = Color(0.580392, 0.266667, 0.960784)
const activationParticles = preload("res://Items/Exclusive/Particles/AmuletofDarknessParticles.tscn")

onready var damageThreshold: = int(getP("damt"))
var damageAcc: int

func _ready():
	damageSource = DamageSource.new().setItem(self)
	specificDragParticles[0].self_modulate = amuletColor

func canAffect(item):
	return item.canActivate()

func onPrepare():
	damageAcc = 0
	connectForCombat(opponent(), "character_attacked", "onOpponentDamaged")
	
	for item in getAffectedItems():
		# ★ np51㊳终⑭ 触发面探针（ORACLE_AODPROBE 门控，零 rng 消耗）
		if OS.get_environment("ORACLE_AODPROBE") != "":
			print("[AOD-prep] affected=", item.descriptor.identifier)
		connectForCombat(item, "activated", "onItemActivated")

func onItemActivated(event):
	# ★ np51㊳终⑭ 触发面探针（ORACLE_AODPROBE 门控，零 rng 消耗）
	if OS.get_environment("ORACLE_AODPROBE") != "":
		print("[AOD-trig] t=", Util.time)
	if OS.get_environment("ORACLE_CHUPROBE") != "":
		Util.debug_flip_tag = "AOD t=" + str(Util.time)
	if rollChance():
		var dam = descriptor.minDam
		var res = dealEffectDamage(dam)
		activate()
		var particles = ObjectPool.particleOneShot(activationParticles, self)
		move_child(particles, 0)

func onOpponentDamaged(damageRes: DamageResult):
	if damageRes.hasHit() and damageRes.damageSource.isEffectDamage():
		if OS.get_environment("ORACLE_PROC_DEBUG") != "":
			var _src = damageRes.damageSource.origin
			print("[AoDhit] dmg=", damageRes.damage,
					" src=", (_src.descriptor.identifier if _src != null and _src.descriptor != null else "null"),
					" acc=", damageAcc + damageRes.damage, " damt=", damageThreshold)
		damageAcc += damageRes.damage

		var proccs = damageAcc / damageThreshold
		if proccs > 0:
			damageAcc %= damageThreshold
			inflictRandomDebuffs(proccs)
			miniActivate()
