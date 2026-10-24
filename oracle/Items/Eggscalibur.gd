extends "res://Items/Pan.gd"

const activationParticles = preload("res://Items/Particles/EggscaliburActivationParticles.tscn")

func onDealtDamage(damageRes: DamageResult):
	var event = tryUseMana(getP2(), damageRes.event)
	if event:
		var affected = getAffectedItems()
		if OS.get_environment("B2_SHUF_DBG") != "":
			_b2_dump("EGG PRE", affected)
			_b2_dump_cells("EGG CELLS", getAffectedCellsInInventory())
		affected.shuffle()
		if OS.get_environment("B2_SHUF_DBG") != "":
			_b2_dump("EGG POST", affected)
		for food in affected:
			food.doCooldownEffect()
		
		ObjectPool.particleOneShot(activationParticles, sprite)

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

# ★ b1_c2 取证桩：受影响格序列（含顺序）dump。
func _b2_dump_cells(tag: String, cells: Array) -> void :
	var path = ProjectSettings.globalize_path("res://..") + "/output/_round_patches/b1_c2/oracle_shuf_dump.log"
	var f = File.new()
	if f.file_exists(path):
		f.open(path, File.READ_WRITE)
		f.seek_end()
	else:
		f.open(path, File.WRITE)
	f.store_line("%s t=%.4f n=%d" % [tag, Util.time, cells.size()])
	for c in cells:
		f.store_line("  %s" % str(c))
	f.close()
