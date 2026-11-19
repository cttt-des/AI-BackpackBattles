"""Remove frozen-Oracle timer mirrors from the isolated native-aligned kernels."""
from pathlib import Path
import re

stage = Path(__file__).resolve().parent
sim = stage / "sim_native"

def function(text, name, body):
    start = re.search(rf"(?m)^(?:static )?func {re.escape(name)}\(", text)
    assert start, name
    signature_end = text.index("\n", start.start())
    following = re.search(r"(?m)^[^ \t\r\n]", text[signature_end + 1:])
    end = signature_end + 1 + following.start() if following else len(text)
    return text[:start.start()] + body.rstrip() + "\n\n" + text[end:]

def save(name, text):
    for root in (sim, sim / "gd_core_test", sim / "native_sim_cpp"):
        (root / "gd_core" / name).write_text(text, encoding="utf8", newline="\n")

timer = (stage / "native_timer_model.gd.inc").read_text("utf8")
timer = timer.replace("extends Reference\n", "extends Reference\nclass_name CoreTimer\n", 1)
save("CoreTimer.gd", timer)

character = (sim / "gd_core/CoreCharacter.gd").read_text("utf8")
start = character.index("# ★ np25 timeout1t：严格三变量模型")
end = character.index("func _init(", start)
character = character[:start] + "var _rage_wait := 1.0\nvar _invul_wait := 1.0\n\n\n" + character[end:]
character = function(character, "_setRageTimer", '''func _setRageTimer(duration: float) -> void:
	if duration > 0.0:
		_rage_wait = _f32eng(duration)
	_rage_left = _rage_wait
	_rage_active = true
''')
character = function(character, "makeInvulnerable", '''func makeInvulnerable(duration, item, triggerEvent = null):
	invulnerabilityItem = item
	if not invulnerable:
		_startInvulnerability(duration)
		invulnerable = true
		ctx.hooks.playInvulnerableAnimation(self, true)
		ctx.rng.randf_range(0.9, 1.1, "randPitch")
	else:
		_startInvulnerability(duration + _f32eng(max(0.0, _invul_left)))
	var event = ctx.combat_log.createEvent_InvulnerableStart(item, duration, playerId, triggerEvent)
	ctx.bus.emitEvent(self, "character_invulnerable_start", event, [event])
	ctx.combat_log.snapshotCharacterStat(self, Stat.Invulnerable)
	return event
''')
character += '''
func _startInvulnerability(duration: float) -> void:
	if duration > 0.0:
		_invul_wait = _f32eng(duration)
	_invul_left = _invul_wait
	_invul_active = true
'''
character = function(character, "tickPhysicsTimers", '''func tickPhysicsTimers(delta: float) -> void:
	if _tick_timer_active and (_physics_timer_mask & 1) != 0:
		_tick_timer_left -= delta
		if _tick_timer_left < 0.0:
			_tick_timer_left += 1.0
			onTick()
	if _rage_active and (_physics_timer_mask & 2) != 0:
		_rage_left -= delta
		if _rage_left < 0.0:
			_rage_active = false
			endBattleRage()
	if _invul_active and (_physics_timer_mask & 4) != 0:
		_invul_left -= delta
		if _invul_left < 0.0:
			_invul_active = false
			_invul_left = -1.0
			invulnerabilityEnded()
	if _autoRage_active and (_physics_timer_mask & 8) != 0:
		_autoRage_left -= delta
		if _autoRage_left < 0.0:
			_autoRage_left = -1.0
			_autoRage_active = false
			startAutoRage()
''')
character = function(character, "rebuildTimerSeen", '''func rebuildTimerSeen() -> void:
	pass
''')
# Former engine-read/seen mirrors are no longer part of the timer state.
character = "\n".join(line for line in character.splitlines()
                       if line.lstrip().startswith("#") or not re.search(r"\b_(?:rage|invul)_(?:eng|seen)\b", line)) + "\n"
character = character.replace("_autoRage_left = AUTO_RAGE_DELAY", "_autoRage_left = _f32eng(AUTO_RAGE_DELAY)")
character = character.replace("return _rage_active\n", "return _rage_active and _rage_left > 0.0\n")
character = character.replace("\tattackMovingForward_reset()\n\t\n\tfor buffType", "\tattackMovingForward_reset()\n\t_tick_timer_active = false\n\t\n\tfor buffType")
save("CoreCharacter.gd", character)

buff = (stage / "sim/gd_core/CoreBuff.gd").read_text("utf8")
start = buff.index("# 内核计时器（替代 Godot Timer")
end = buff.index("\nvar ctx", start)
buff = buff[:start] + '''# Native Timer countdown, allocated only as scalar state.
var _timer_left := -1.0
var _timer_active := false
var _timer_wait := 1.0
var _timer_first_pass := 0
var _timer_member_epoch := -1
''' + buff[end:]
start = buff.index("\t\t\t\t\tvar timerLeft = _timer_left\n")
end = buff.index("\t\t\t\t\tif duration < timerLeft:", start)
buff = buff[:start] + "\t\t\t\t\tvar timerLeft = _f32eng(max(0.0, _timer_left))\n" + buff[end:]
buff = function(buff, "_startTimer", '''func _startTimer(duration: float) -> void:
	if duration > 0.0:
		_timer_wait = _f32eng(duration)
	_timer_left = _timer_wait
	if not _timer_active:
		_timer_first_pass = ctx.timer_pass_epoch + 1
		if ctx.in_physics_timer_pass and _timer_member_epoch == ctx.timer_pass_epoch:
			_timer_first_pass = ctx.timer_pass_epoch
	_timer_active = true
''')
buff = function(buff, "_stopTimer", '''func _stopTimer() -> void:
	_timer_member_epoch = -1
	if ctx.in_physics_timer_pass and _timer_active and _timer_first_pass <= ctx.timer_pass_epoch:
		_timer_member_epoch = ctx.timer_pass_epoch
	_timer_active = false
	_timer_left = -1.0
''')
buff = function(buff, "_tick", '''func _tick(delta: float) -> void:
	if not _timer_active or ctx.timer_pass_epoch < _timer_first_pass:
		return
	_timer_left -= delta
	if _timer_left < 0.0:
		_timer_active = false
		_timer_left = -1.0
		onTimeout()
''')
buff = function(buff, "rebuildTimerSeen", '''func rebuildTimerSeen() -> void:
	pass
''')
buff = re.sub(r' \+ "/e" \+ str\(_timer_eng\) \+ "/s" \+ str\(_timer_seen\)', '', buff)
assert not re.search(r"(?m)^(?!\s*#).*\b_timer_(?:eng|seen)\b", buff)
save("CoreBuff.gd", buff)
print("Staged native Timer/MultiTimer, Buff and character countdowns")
