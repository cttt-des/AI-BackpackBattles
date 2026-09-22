extends SceneTree

# Probe.gd — 逐帧取证：物品触发时刻 vs combat_time vs 事件时间戳
# 用法: godot --no-window --path gd_core_test --script Probe.gd

class WeaponBehavior extends Reference:
	func hasBehavior(item, methodName: String) -> bool:
		return methodName == "doCooldownEffect"
	func callBehavior(item, methodName: String, args: Array):
		if methodName == "doCooldownEffect":
			if item.useStamina() == CoreCharacter.StaminaResult.Sufficient:
				item.activate(item.dealDamage())
	func doCooldownEffect(item) -> void:
		pass

const STEP := 1.0 / 60.0
var _weapon = WeaponBehavior.new()
var _report: Array = []


func say(line: String) -> void:
	print(line)
	_report.push_back(line)
	var fh = File.new()
	if fh.open("res://probe_result.txt", File.WRITE) == OK:
		fh.store_string(PoolStringArray(_report).join("\n") + "\n")
		fh.close()


func new_character(ctx, pid: int, hp: int) -> CoreCharacter:
	var c = CoreCharacter.new(ctx, pid)
	c.setMaxHealth(hp)
	c.setCurrentHealth(hp)
	c.maxStamina = 50.0
	c.baseMaxStamina = 50.0
	c.baseStaminaRegen = 20.0
	c.fillUpStamina()
	return c


func new_weapon(ctx, character, item_name: String, dmg: int, cd: float) -> CoreItem:
	var data = {
		"name": item_name, "minDam": dmg, "maxDam": dmg, "cd": cd,
		"staminaCost": 0.0, "accuracy": 100.0, "block": 0,
		"types": [CoreConst.Type.Weapon, CoreConst.Type.Melee],
	}
	var it = CoreItem.new(ctx, CoreItemData.new().fromDict(data), character)
	it._behavior = _weapon
	it.buildDamageSource()
	return it


func _init() -> void:
	say("=== PROBE: 触发时刻取证 ===")
	var ctx = CoreContext.new(20260922, null)
	var p = new_character(ctx, CoreCharacter.ID.PLAYER, 100)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT, 20)
	
	# 只放玩家 1 把武器，排除对手武器干扰
	var items: Array = [new_weapon(ctx, p, "W", 5, 1.0)]
	
	var combat = CoreCombat.new(ctx)
	combat.setup(p, o)
	combat.startBattle(items, [])
	
	var prev: Array = [1.0]
	var frame := 0
	while not combat.fight_ended and frame < 60 * 10:
		var ct_before = combat.combat_time
		combat.physicsTick(STEP)
		frame += 1
		# 触发判定：triggerTime 出现向上跳变（+= iterationCooldown）
		var it = items[0]
		if not combat.activated:
			continue
		if it.triggerTime > prev[0] + 0.001:
			say("  frame=%3d  combat_time_before=%.4f  after=%.4f  trigTime %.4f -> %.4f  oppHP=%.1f" % [
				frame, ct_before, combat.combat_time, prev[0], it.triggerTime, 
				combat.opponent.curHealth])
		prev[0] = it.triggerTime
	
	say("  结束: combat_time=%.4f  oppHP=%.1f  playerHP=%.1f" % [
		combat.combat_time, combat.opponent.curHealth, combat.player.curHealth])
	quit(0)
