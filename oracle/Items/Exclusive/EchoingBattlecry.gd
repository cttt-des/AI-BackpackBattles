extends Item

const activationParticles = preload("res://Items/Exclusive/Particles/EchoingBattlecryActivationParticles.tscn")

var affectedItems: Array

onready var speedPerItem: = getP("speed") / 100.0

func canAffect(item):
	return item.hasStartofBattle()

func onPrepare():
	affectedItems = getAffectedItems()
	if OS.get_environment("B2_SHUF_DBG") != "":
		_b2_dump("ECHO PRE", affectedItems)
	affectedItems.shuffle()
	if OS.get_environment("B2_SHUF_DBG") != "":
		_b2_dump("ECHO POST", affectedItems)
	
	addSpeed(speedPerItem * affectedItems.size())

# ★ b1_c2 取证桩（B2_SHUF_DBG 门控，只读旁路）：洗牌前后数组序 dump。
func _b2_dump(tag: String, arr: Array) -> void :
	var path = ProjectSettings.globalize_path("res://..") + "/output/_round_patches/b1_c2/oracle_shuf_dump.log"
	var f = File.new()
	if f.file_exists(path):
		f.open(path, File.READ_WRITE)
		f.seek_end()
	else:
		f.open(path, File.WRITE)
	f.store_line("%s t=%.4f n=%d" % [tag, Util.time, arr.size()])
	for it in arr:
		f.store_line("  %s iid=%d tl=%s" % [it.getName(), it.get_instance_id(), str(it.get("top_left"))])
	f.close()

func doCooldownEffect():
	if not affectedItems.empty():
		var item = affectedItems.pop_back()
		item.repeatCombatStart()
		var particles = ObjectPool.particleOneShot(activationParticles, get_parent())
		particles.global_position = item.global_position
		if affectedItems.empty():
			onAfterEffectFinished()
		else:
			activate()
