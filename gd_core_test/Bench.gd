extends SceneTree

# Bench.gd — gd_core 无头内核吞吐基准
# 输出：模拟秒 / 墙钟秒 的加速比（相对 60Hz 实时），以及单帧成本。
# 用法: godot --no-window --path gd_core_test --script Bench.gd

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
	if fh.open("res://bench_result.txt", File.WRITE) == OK:
		fh.store_string(PoolStringArray(_report).join("\n") + "\n")
		fh.close()


func new_character(ctx, pid: int, hp: int) -> CoreCharacter:
	var c = CoreCharacter.new(ctx, pid)
	c.setMaxHealth(hp)
	c.setCurrentHealth(hp)
	c.maxStamina = 100.0
	c.baseMaxStamina = 100.0
	c.baseStaminaRegen = 50.0
	c.fillUpStamina()
	return c


func new_weapon(ctx, character, dmg: int, cd: float) -> CoreItem:
	var data = {
		"name": "W", "minDam": dmg, "maxDam": dmg, "cd": cd,
		"staminaCost": 0.0, "accuracy": 100.0, "block": 0,
		"types": [CoreConst.Type.Weapon, CoreConst.Type.Melee],
	}
	var it = CoreItem.new(ctx, CoreItemData.new().fromDict(data), character)
	it._behavior = _weapon
	it.buildDamageSource()
	return it


# 单场对战：双方各 n 把武器，返回 (模拟秒, 帧数)
# 注：形参不能用 seed —— 与 GDScript 内置 seed() 同名会报
#     "Expected an identifier for an argument"。
func run_one(sd: int, n: int, hp: int, dmg: int, cd: float) -> Array:
	var ctx = CoreContext.new(sd, null)
	var p = new_character(ctx, CoreCharacter.ID.PLAYER, hp)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT, hp)
	var pi: Array = []
	for i in n:
		pi.push_back(new_weapon(ctx, p, dmg, cd))
	var oi: Array = []
	for i in n:
		oi.push_back(new_weapon(ctx, o, dmg, cd))
	
	var combat = CoreCombat.new(ctx)
	combat.setup(p, o)
	combat.startBattle(pi, oi)
	
	var frames := 0
	while not combat.fight_ended and frames < 60 * 200:
		combat.physicsTick(STEP)
		frames += 1
	return [combat.combat_time, frames]


func bench(label: String, n: int, hp: int, dmg: int, cd: float, reps: int) -> void:
	var sim_seconds := 0.0
	var frames := 0
	var t0 = OS.get_ticks_usec()
	for r in reps:
		var res = run_one(1000 + r, n, hp, dmg, cd)
		sim_seconds += res[0]
		frames += res[1]
	var t1 = OS.get_ticks_usec()
	var wall = float(t1 - t0) / 1000000.0
	
	say("  %-30s reps=%-5d 模拟%.1fs 帧数%-7d 墙钟%.3fs  加速比=%.0f×  单帧=%.2fµs" % [
		label, reps, sim_seconds, frames, wall, 
		sim_seconds / wall, wall * 1000000.0 / float(frames)])


func _init() -> void:
	say("=== gd_core 无头内核吞吐基准 ===")
	say("  （加速比 = 模拟秒 / 墙钟秒；60Hz 实时 = 1×）")
	say("")
	bench("双方各 2 武器 3dmg/0.8cd", 2, 60, 3, 0.8, 300)
	bench("双方各 4 武器 3dmg/0.8cd", 4, 60, 3, 0.8, 300)
	bench("双方各 6 武器 5dmg/1.0cd", 6, 100, 5, 1.0, 300)
	bench("双方空手（纯疲劳 24s 场）", 0, 30, 0, 1.0, 200)
	say("")
	quit(0)
