# =============================================================================
# CoreHooks.gd — 无头战斗内核：外部副作用钩子（解耦用）
# =============================================================================
# 这是本次「精简 + 解耦」的核心手法：
#   原版把 视觉/动画/粒子/tween/shader/z_index、音效、UI 悬停/拖拽/预览、
#   战斗日志快照 直接内联写在战斗判定函数里，导致战斗逻辑无法脱离场景树运行。
#   gd_core 把这些调用一律改为对本钩子对象的调用，默认实现全部为空，
#   因此判定路径不再触碰任何渲染/音频/UI/节点 API。
#
# 保真约束：
#   · 钩子**不在任何 if 条件里**参与判定（全部为纯尾部副作用调用）；
#   · 因此空实现与真实实现的判定结果完全一致 —— 这是本方案可证明保真的前提。
#   · 若某处原版把副作用写进了条件（例如 `if animation.current_animation != "Poison"`），
#     该行不会进入钩子，而是整体删除并在真值表里记为「纯表现分支」，因为它不影响
#     任何被判定读取的量。
#
# 需要真实视觉效果时（例如注入回游戏进程内运行），继承本类并覆写即可。
# =============================================================================
extends Reference
class_name CoreHooks


# ── 物品层表现 ──

func showCooldown(item, progress: float) -> void :
	pass


func resetZ(item) -> void :
	pass


func playActivationAnimation(item, aniType, consume: bool) -> void :
	pass


func playActivationSound(item) -> void :
	pass


func playDropSound(item, volume) -> void :
	pass


func spawnLabel(item, type, damage) -> void :
	pass


func queueTooltipUpdate(item) -> void :
	pass


func activateBuffCounter(character, type) -> void :
	pass


func playOutOfStaminaAnimation(item) -> void :
	pass


func playStunAnimation(character, duration) -> void :
	pass


# ── 战斗计时器（CombatTimer）表现 ──

func playFatigueAnimation(name: String) -> void :
	pass


func playFatigueSound() -> void :
	pass


# ── 角色层表现 ──

func playAttackAnimation(character, distance = null) -> void :
	pass


func playActivateAnimation(character) -> void :
	pass


func spawnLabel_character(character, type, damage, item = null) -> void :
	pass


func spawnReflectLabel(type, pos, reflected) -> void :
	pass


func spawnResistedLabel(type, pos, resisted) -> void :
	pass


func spawnProtectedLabel(type, pos, protected) -> void :
	pass


func spawnBuffLabel_item(type, item, amount, appliedToOpponent) -> void :
	pass


func spawnBuffLabel(type, pos) -> void :
	pass


func spawnNumberLabel(type, pos, direction, damage) -> void :
	pass


func spawnMissLabel(pos, direction) -> void :
	pass


func damageAnimation(character, kind: String, speed: float = 1.0) -> void :
	pass


func playCharacterSound(character, stream, volume = 0, pitch = 1.0, force = false) -> void :
	pass


func onHealthChangedUI(character) -> void :
	pass


func applyImpulse(item, offset, impulse) -> void :
	pass


# ── 统计埋点（数值型，可选实现） ──

func addMetric(item, metricIndex: int, amount) -> void :
	pass


func snapshotItemTooltipStat(item, statType, playerId = null, withNextEvent = false, event = null) -> void :
	pass


func snapshotItemState(item, state, withNextEvent: bool, event) -> void :
	pass


func snapshotItemMetric(item, metricIndex: int, playerId = null, withNextEvent = false) -> void :
	pass


func snapshotCharacterStat(character, statType) -> void :
	pass


func snapshotStack(character, type) -> void :
	pass


func snapshotDamageDealt(playerId, type, damage) -> void :
	pass


func snapshotGlobalStat(stat: int, newValue) -> void :
	pass


func snapshotMetric(playerId, metric, eventType, value) -> void :
	pass


func updateDamageMeter(playerId, event) -> void :
	pass


# ── 战斗日志 ──

func logEvent(event) -> void :
	pass
