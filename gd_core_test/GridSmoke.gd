# =============================================================================
# GridSmoke.gd — gd_core 网格子系统专项验证（Godot 3.6 宿主）
# =============================================================================
# 里程碑 1 里新落地的 CoreGrid + CoreItem 邻接/受影响格 API 需要独立验证：
# 它们是 176 项战斗缺口里最大的一块（约 65 项），且物品联动（Whetstone / Banana /
# Exclusive 系列）全部建立在它上面。
#
# 覆盖的契约：
#   1. 受影响格来源：affectedTileCells + getAffectedCellsAfterRotate 覆写
#   2. 判定闸门：命中格 ≠ 受影响，还要过 canAffect（行为覆写）才计入
#   3. 快照语义：currentAffectedItems 在「加入背包」时增量建立，
#      prepare 时定版为 cachedAffectedItems（战斗期间只读）
#   4. 取首项次序：getFirstAffectedItem 的顺序 = 加入背包的次序
#      （原版靠 onAffectedItemAdded 的键插入顺序，本测试固定该契约）
#   5. 邻接：getNeighborItemsAndGems 的四邻域去重与「排除自身占格」
#   6. 计数族：getNumAffectedItems / getNumAffected_type / getNumAffectedCells /
#      countItemsInAffectedCells_cached / getNumEmptyAffectedCells
#   7. 确定性：同装配次序 → 结果逐位一致
#   8. 朝向：faceDirection 是战斗判定输入（SpintoWin 按方向分流 Heat/Lucky/Regen/Mana），
#      放置写入 → 行为读到同值，且 rotation = fd×90°
#
# 运行：
#   Godot_v3.6-stable_win64.exe --no-window --path gd_core_test --script GridSmoke.gd
# =============================================================================
extends SceneTree


# ── 假联动行为：只覆写 canAffect（对应 Food.gd / Whetstone.gd 的角色） ──
# 语义：只影响「武器」。
class LinkBehavior extends Reference:
	
	func hasBehavior(item, methodName: String) -> bool:
		return methodName == "canAffect"
	
	func callBehavior(item, methodName: String, args: Array):
		match methodName:
			"canAffect":
				return canAffect(item, args[0])
	
	func canAffect(item, other) -> bool:
		return other != null and other.isWeapon()


var failures: Array = []
var _report: Array = []


func say(line: String) -> void:
	print(line)
	_report.push_back(line)
	var fh = File.new()
	if fh.open("res://grid_result.txt", File.WRITE) == OK:
		fh.store_string(PoolStringArray(_report).join("\n") + "\n")
		fh.close()


func check(cond: bool, what: String) -> void:
	if not cond:
		failures.push_back(what)


func _init() -> void:
	say("")
	say("=== gd_core grid smoke test ===")
	print("GRID: start")
	test_affected_pipeline()
	print("GRID: test1 done")
	test_adjacency()
	print("GRID: test2 done")
	test_determinism()
	print("GRID: test3 done")
	test_face_direction()
	print("GRID: test4 done")
	
	say("")
	if failures.empty():
		say("GRID: PASS")
	else:
		for f in failures:
			say("GRID: FAIL  " + f)
		say("GRID: FAIL (%d 项)" % failures.size())
	
	quit(0 if failures.empty() else 1)


# ─────────────────────────── 装配辅助 ───────────────────────────

func new_character(ctx, pid: int) -> CoreCharacter:
	var c = CoreCharacter.new(ctx, pid)
	c.setMaxHealth(100)
	c.setCurrentHealth(100)
	c.maxStamina = 50.0
	c.baseMaxStamina = 50.0
	c.fillUpStamina()
	return c


func new_item(ctx, character, item_name: String, types: Array) -> CoreItem:
	var data = {
		"name": item_name,
		"identifier": item_name,
		"cd": 1.0,
		"staminaCost": 0.0,
		"accuracy": 100.0,
		"types": types,
	}
	return CoreItem.new(ctx, CoreItemData.new().fromDict(data), character)


func v2(x: int, y: int) -> Vector2:
	return Vector2(x, y)


# 搭一套固定阵容。add_order 决定「加入背包」的次序，进而决定受影响集的键次序。
#   布局（x 向右，y 向下）：
#       A("Linker") 占 (-2,0)(-1,0)，受影响格 (0,0)(1,0)(0,1)
#       "SwordA"  占 (0,0)  武器      → 被 A 影响
#       "SwordB"  占 (1,0)  武器      → 被 A 影响
#       "StoneA"  占 (0,1)  非武器    → 落在受影响格，但 canAffect 不过 → 不计入
#       "SwordC"  占 (-1,1) 武器      → 不在受影响格 → 不计入
func build(ctx, add_order: Array) -> Dictionary:
	var p = new_character(ctx, CoreCharacter.ID.PLAYER)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT)
	var combat = CoreCombat.new(ctx)
	combat.setup(p, o)
	
	var linker = new_item(ctx, p, "Linker", [CoreConst.Type.Accessory])
	linker._behavior = LinkBehavior.new()
	linker.occupiedCells = [v2(-2, 0), v2(-1, 0)]
	linker.collisionCells = [v2(0, 0), v2(1, 0)]
	linker.affectedTileCells = {CoreConst.Affected.Primary: [v2(0, 0), v2(1, 0), v2(0, 1)]}
	
	var sword_a = new_item(ctx, p, "SwordA", [CoreConst.Type.Weapon, CoreConst.Type.Melee])
	sword_a.occupiedCells = [v2(0, 0)]
	sword_a.collisionCells = [v2(0, 0)]
	
	var sword_b = new_item(ctx, p, "SwordB", [CoreConst.Type.Weapon, CoreConst.Type.Melee])
	sword_b.occupiedCells = [v2(1, 0)]
	sword_b.collisionCells = [v2(0, 0)]
	
	var stone_a = new_item(ctx, p, "StoneA", [CoreConst.Type.Accessory])
	stone_a.occupiedCells = [v2(0, 1)]
	stone_a.collisionCells = [v2(0, 0)]
	
	var sword_c = new_item(ctx, p, "SwordC", [CoreConst.Type.Weapon, CoreConst.Type.Melee])
	sword_c.occupiedCells = [v2(-1, 1)]
	sword_c.collisionCells = [v2(0, 0)]
	
	var all = {
		"Linker": linker,
		"SwordA": sword_a, 
		"SwordB": sword_b, 
		"StoneA": stone_a, 
		"SwordC": sword_c, 
	}
	
	# 逐件加入（次序即原版 Inventory.addItem → emit item_added 的次序）
	var items: Array = []
	for key in add_order:
		var it = all[key]
		items.push_back(it)
		p.inventory.addItem(it, it.occupiedCells)
	
	# 对齐 Game.gd:3257-3262：prepare 前先定版受影响集
	for it in items:
		it.prepare()
	
	return {"combat": combat, "p": p, "items": all}


func names_of(items: Array) -> String:
	var out = []
	for it in items:
		out.push_back(it.getName())
	return "[" + ", ".join(out) + "]"


# ─────────────────────────── 1. 受影响格判定链 ───────────────────────────

func test_affected_pipeline() -> void:
	say("")
	say("[1] 受影响格判定链：命中格 → canAffect 闸门 → 快照 → 取首项")
	
	var ctx = CoreContext.new(20260922, null)
	var w = build(ctx, ["Linker", "SwordA", "SwordB", "StoneA", "SwordC"])
	var linker = w["items"]["Linker"]
	var p = w["p"]
	
	# ① 受影响格缓存 = tscn 受影响格 + getAffectedCellsAfterRotate 覆写（此处无覆写）
	var aCached = linker.getAffectedCellsInInventory_cached(CoreConst.Affected.Primary)
	say("    A 受影响格缓存 = %s（期望 3 格）" % str(aCached.size()))
	check(aCached.size() == 3, "受影响格缓存应为 3（actual %d）" % aCached.size())
	
	# ② 命中格里的物品（不看 canAffect）
	var inCells = linker.getItemsInAffectedCells_cached(CoreConst.Affected.Primary)
	say("    落在受影响格的物品 = %s（期望 SwordA/SwordB/StoneA）" % names_of(inCells))
	check(inCells.size() == 3, "命中格物品应为 3（actual %d）" % inCells.size())
	
	# ③ 过 canAffect 闸门后的受影响物品
	var affected = linker.getAffectedItems(CoreConst.Affected.Primary)
	say("    受影响物品（过 canAffect）= %s（期望 SwordA/SwordB）" % names_of(affected))
	check(affected.size() == 2, "受影响物品应为 2（actual %d）" % affected.size())
	
	# ④ 快照独立性：战斗期间读的是 cachedAffectedItems
	check(affected == linker.cachedAffectedItems[CoreConst.Affected.Primary], 
			"getAffectedItems 应读缓存快照")
	check(not linker.cachedAffectedItems.empty(), "cachedAffectedItems 应已定版")
	
	# ⑤ 取首项次序 = 加入背包次序（先 SwordA 后 SwordB）
	check(linker.getFirstAffectedItem() == w["items"]["SwordA"], 
			"getFirstAffectedItem 应取最先加入的 SwordA（actual %s）" 
			% (linker.getFirstAffectedItem().getName() if linker.getFirstAffectedItem() != null else "null"))
	
	# ⑥ 计数族
	say("    numAffectedItems=%d  numAffected_type(Weapon)=%d  numAffectedCells=%d" % [
		linker.getNumAffectedItems(), 
		linker.getNumAffected_type(CoreConst.Type.Weapon), 
		linker.getNumAffectedCells()])
	check(linker.getNumAffectedItems() == 2, "numAffectedItems 应为 2")
	check(linker.getNumAffected_type(CoreConst.Type.Weapon) == 2, 
			"numAffected_type(Weapon) 应为 2")
	check(linker.getNumAffectedCells() == 3, "numAffectedCells 应为 3")
	# 无 bagCells → isCellEmpty 恒 false
	check(linker.getNumEmptyAffectedCells() == 0, "numEmptyAffectedCells 应为 0（无袋格）")
	
	# ⑦ countItemsInAffectedCells_cached 记「物品 → 命中格数」
	var counts = linker.countItemsInAffectedCells_cached(CoreConst.Affected.Primary)
	check(counts.size() == 3, "countItemsInAffectedCells_cached 应含 3 个物品")
	check(counts.get(w["items"]["SwordA"], 0) == 1, "SwordA 应命中 1 格")
	
	# ⑧ 无受影响格的物品不应反向影响
	check(w["items"]["SwordA"].getAffectedItems().empty(), 
			"SwordA 无受影响格来源 → 受影响物品应为空")
	
	# ⑨ 方向性：反向不成立（SwordA 不反向影响 Linker）
	check(not w["items"]["SwordA"].isItemAffected(linker), "相邻关系应是有向的")
	
	# ⑩ 不被影响的物品确实不被影响
	check(not w["items"]["SwordC"] in affected, "SwordC 不在受影响格 → 不应被计入")
	check(not w["items"]["StoneA"] in affected, "StoneA 是命中格但 canAffect 不过 → 不应计入")
	
	# ⑪ 快照次序随加入次序变化（验证 getFirstAffectedItem 的次序契约）
	var ctx2 = CoreContext.new(20260922, null)
	var w2 = build(ctx2, ["Linker", "SwordB", "SwordA", "StoneA", "SwordC"])
	var linker2 = w2["items"]["Linker"]
	var first2 = linker2.getFirstAffectedItem()
	say("    调换加入次序后 getFirstAffectedItem = %s（期望 SwordB）" 
		% (first2.getName() if first2 != null else "null"))
	check(linker2.getFirstAffectedItem() == w2["items"]["SwordB"], 
			"调换加入次序后应取最先加入的 SwordB")


# ─────────────────────────── 2. 邻接 ───────────────────────────

func test_adjacency() -> void:
	say("")
	say("[2] 邻接：四邻域去重 + 排除自身占格 + 袋格查询")
	
	var ctx = CoreContext.new(31337, null)
	var w = build(ctx, ["Linker", "SwordA", "SwordB", "StoneA", "SwordC"])
	var linker = w["items"]["Linker"]
	
	# A 占 (-2,0)(-1,0) → 邻格按 RIGHT/LEFT/UP/DOWN 逐格展开并去重
	var cells = CoreGrid.getAdjacentCells(linker.occupiedCells)
	say("    A 的邻格 = %s（%d 格）" % [str(cells), cells.size()])
	check(not v2(-2, 0) in cells and not v2(-1, 0) in cells, "邻格应排除自身占格")
	check(cells.size() == 6, "A 的邻格应为 6（actual %d）" % cells.size())
	
	# 邻接物品 = 邻格里的物品（含非武器，邻接不看 canAffect）
	var neighbors = w["p"].inventory.getAdjacentItems(linker)
	say("    邻接物品 = %s（期望 SwordA/SwordC）" % names_of(neighbors))
	check(neighbors.size() == 2, "邻接物品应为 2（actual %d）" % neighbors.size())
	check(w["items"]["SwordA"] in neighbors, "SwordA 与 A 相邻")
	check(w["items"]["SwordC"] in neighbors, "SwordC 与 A 相邻")
	
	# getNeighborItemsAndGems = 邻接物品 + 自身宝石 + 邻接物品的宝石（本测试无宝石）
	var nig = linker.getNeighborItemsAndGems()
	check(nig.size() == 2, "getNeighborItemsAndGems 应为 2（无宝石）")
	
	# 未登记袋格 → getTouchedBags 为空
	check(linker.getTouchedBags().empty(), "无袋格 → getTouchedBags 应为空")
	# 制作系统已剥离 → isBusy / isAvailableForCrafting 恒 false
	check(not linker.isBusy(), "制作剥离后 isBusy 恒 false")
	check(linker.getBusyNeighbors().empty(), "制作剥离后 getBusyNeighbors 恒空")
	check(linker.getCraftableNeighbors().empty(), "制作剥离后 getCraftableNeighbors 恒空")
	
	# 尺寸/左上角
	check(linker.getSizeInCells() == Vector2(2, 1), 
			"Linker 占格尺寸应为 (2,1)（actual %s）" % str(linker.getSizeInCells()))
	check(linker.getTopLeftCell() == v2(-2, 0), 
			"Linker 左上角应为 (-2,0)（actual %s）" % str(linker.getTopLeftCell()))
	check(linker.getNumOccupiedCells() == 2 and linker.getNumCells() == 2, "占格数应为 2")


# ─────────────────────────── 3. 确定性 ───────────────────────────

func test_determinism() -> void:
	say("")
	say("[3] 确定性：同装配次序 + 同种子 → 结果逐位一致")
	
	var a = _snapshot(CoreContext.new(999, null))
	var b = _snapshot(CoreContext.new(999, null))
	say("    run A = " + a)
	say("    run B = " + b)
	check(a == b, "同装配两轮结果应完全一致")


# ─────────────────────── 4. 朝向（faceDirection）契约 ───────────────────────
# 动机：SpintoWin.gd:33-52 的 doCooldownEffect/gainsStack 按 faceDirection 分流战斗效果
# （UP→Heat / RIGHT→Lucky / DOWN→Regeneration / LEFT→Mana）；
# LongSpear.gd:6-7、RainbowPotion.gd:17/96/98 同样按方向分流。
# 故 faceDirection 是**战斗判定输入**，必须可由放置层写入、且行为脚本读到的值与写入值一致。

func test_face_direction() -> void:
	say("")
	say("[4] 朝向：放置写入 faceDirection → 行为读到同值（方向即战斗效果）")
	
	var ctx = CoreContext.new(4242, null)
	var p = new_character(ctx, CoreCharacter.ID.PLAYER)
	var orb = new_item(ctx, p, "Spinner", [CoreConst.Type.Accessory])
	orb.collisionCells = [v2(0, 0)]
	orb.occupiedCells = [v2(0, 0)]
	orb._behavior = DirectionBehavior.new()
	p.inventory.addItem(orb, orb.occupiedCells)
	orb.prepare()
	
	# ① 默认朝向 = UP（对齐 Item.gd:387 区间的 faceDirection 声明默认值）
	check(orb.faceDirection == CoreConst.FaceDirection.UP, "默认朝向应为 UP")
	
	# ② 四方向写入 → getFaceDirection 逐位一致（原版由 rotation 量化而来）
	var names = ["UP", "RIGHT", "DOWN", "LEFT"]
	var seen = []
	for fd in [CoreConst.FaceDirection.UP, CoreConst.FaceDirection.RIGHT, 
			CoreConst.FaceDirection.DOWN, CoreConst.FaceDirection.LEFT]:
		orb.setFaceDirectionInstant(fd)
		seen.push_back(orb._behavior_call("getMatch", [orb]))
		check(orb.faceDirection == fd and orb.getFaceDirection() == fd, 
				"写入 %s 后 faceDirection/getFaceDirection 应为同值（actual %d/%d）"
				% [names[fd], orb.faceDirection, orb.getFaceDirection()])
		check(is_equal_approx(orb.rotation, fd * PI * 0.5), 
				"%s 朝向应对应 rotation = fd*PI/2（actual %f）" % [names[fd], orb.rotation])
	
	# ③ 四种朝向必须分流到四种不同效果（若全同则说明方向没进判定）
	say("    四方向分流结果 = %s（期望 4 个互不相同）" % str(seen))
	var uniq = {}
	for s in seen:
		uniq[s] = true
	check(uniq.size() == 4, "四方向应分流到 4 种不同效果（actual %d 种）" % uniq.size())
	
	# ④ rotateLeft/rotateRight 在字段层面等价于朝向 ±1（战斗期不可达，仅锁语义）
	orb.setFaceDirectionInstant(CoreConst.FaceDirection.UP)
	orb.rotateRight()
	check(orb.faceDirection == CoreConst.FaceDirection.RIGHT, "rotateRight 应 +1 方向")
	orb.rotateLeft()
	check(orb.faceDirection == CoreConst.FaceDirection.UP, "rotateLeft 应 -1 方向")
	orb.rotateLeft()
	check(orb.faceDirection == CoreConst.FaceDirection.LEFT, "UP 左转应回绕到 LEFT")


# 假方向行为：覆写一个读 faceDirection 的方法（对应 SpintoWin.doCooldownEffect）
class DirectionBehavior extends Reference:
	
	func hasBehavior(item, methodName: String) -> bool:
		return methodName == "getMatch"
	
	func callBehavior(item, methodName: String, args: Array):
		match methodName:
			"getMatch":
				return _match(item)
	
	func _match(item):
		match item.faceDirection:
			CoreConst.FaceDirection.UP:
				return "Heat"
			CoreConst.FaceDirection.RIGHT:
				return "Lucky"
			CoreConst.FaceDirection.DOWN:
				return "Regeneration"
			CoreConst.FaceDirection.LEFT:
				return "Mana"
		return "None"


func _snapshot(ctx) -> String:
	var w = build(ctx, ["Linker", "SwordA", "SwordB", "StoneA", "SwordC"])
	var linker = w["items"]["Linker"]
	var first = linker.getFirstAffectedItem()
	return "%d|%d|%d|%s" % [
		linker.getNumAffectedItems(), 
		linker.getNumAffected_type(CoreConst.Type.Weapon), 
		linker.getAffectedCellsInInventory_cached(CoreConst.Affected.Primary).size(), 
		(first.getName() if first != null else "null")]
