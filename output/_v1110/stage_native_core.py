"""Build an isolated 1.1.10 kernel candidate; leave the running v1 audit intact."""
from pathlib import Path
import json
import re
import shutil

repo = Path.cwd()
stage = repo / "output/_v1110"
src = stage / "sim"
dest = stage / "sim_native"
if not dest.exists():
    shutil.copytree(src, dest, ignore=shutil.ignore_patterns(
        "output", "__pycache__", "*.pyd", "*.dll", "build", ".git"))
    runtime = dest / "output/godot36"
    runtime.mkdir(parents=True, exist_ok=True)
    shutil.copy2(src / "output/godot36/Godot_v3.6-stable_win64.exe", runtime)

def function(text, name, replacement):
    found = re.search(rf"(?m)^(?:static )?func {re.escape(name)}\(", text)
    assert found is not None, name
    following = re.search(r"(?m)^(?:static )?func ", text[found.end():])
    end = found.end() + following.start() if following else len(text)
    return text[:found.start()] + replacement.rstrip() + "\n\n\n" + text[end:]

def load(name):
    return (src / "gd_core" / name).read_text("utf8")

def save(name, text):
    for area in (dest, dest / "gd_core_test", dest / "native_sim_cpp"):
        (area / "gd_core" / name).write_text(text, encoding="utf8", newline="\n")

context = load("CoreContext.gd").replace("const PHYSICS_DELTA := 1.0 / 60.0", "const PHYSICS_DELTA := 0.01666666753590107")
context += '''

# Shared initial replay state, observed before activation. Never read event truth.
var activation_rng_state = null
var idle_timer_initial: Array = []
var timer_pass_epoch := 0
var in_physics_timer_pass := false

func setReplayInitial(activation_state, idle_left: Array, flickers = null) -> void:
	activation_rng_state = activation_state
	idle_timer_initial = idle_left
	flicker_initial = flickers
'''
context += (stage / "native_motion_queue.gd.inc").read_text("utf8")
context += "\n\n" + (stage / "native_flicker_model.gd.inc").read_text("utf8")
save("CoreContext.gd", context)

character = load("CoreCharacter.gd")
start = character.index("# ── 表现层链状态")
end = character.index("# 职业音效文件数", start)
character = character[:start] + (stage / "native_tween_model.gd.inc").read_text("utf8") + "\n\n" + character[end:]
character = function(character, "playActivateAnimation", '''func playActivateAnimation() -> void:
	if attack_moving_forward:
		return
	var forward = _f32eng(-40.0 - _visual_y) / 300.0 * ctx.rng.randf_range(0.9, 1.1)
	var back = 40.0 / 300.0 * ctx.rng.randf_range(0.9, 1.1)
	_beginVisualMotion(2, _visual_x, -40.0, forward, back)
''')
character = function(character, "attackMovingForward_reset", '''func attackMovingForward_reset() -> void:
	attack_moving_forward = false
	_visual_kind = 0
	_visual_x = 0.0
	_visual_y = 0.0
''')
character = function(character, "_setRageTimer", '''func _setRageTimer(t: float) -> void:
	_rage_eng = _f32eng(t)
	_rage_left = _rage_eng
	_rage_seen = _rage_eng
	_rage_active = true
''')
# Physical timer activity is snapshotted before any callbacks in that pass.
character += '''
var _physics_timer_mask := 0

func snapshotPhysicsTimers() -> void:
	_physics_timer_mask = (1 if _tick_timer_active else 0) + (2 if _rage_active else 0) + (4 if _invul_active else 0) + (8 if _autoRage_active else 0)
'''
for flag, bit in (("_tick_timer_active", 1), ("_rage_active", 2), ("_invul_active", 4), ("_autoRage_active", 8)):
    begin = character.index("func tickPhysicsTimers(")
    end_match = re.search(r"(?m)^func ", character[begin+5:])
    end = begin+5+end_match.start() if end_match else len(character)
    body = character[begin:end]
    # Only the outer conditional gets the snapshot mask; callback rearm stays intact.
    body = body.replace(f"\tif {flag}:\n", f"\tif {flag} and (_physics_timer_mask & {bit}) != 0:\n", 1)
    character = character[:begin] + body + character[end:]
begin = character.index("func tickPhysicsTimers(")
next_match = re.search(r"(?m)^func ", character[begin+5:])
end = begin+5+next_match.start()
body = character[begin:end]
body = body.replace("_rage_left = _rage_eng    #", "_rage_left = _rage_eng - delta    #")
body = body.replace("_invul_left = _invul_eng\n", "_invul_left = _invul_eng - delta\n")
body = body.replace("\telse:\n\t\t# ★ np34", "\telif not _invul_active:\n\t\t# ★ np34")
character = character[:begin] + body + character[end:]
save("CoreCharacter.gd", character)

item = load("CoreItem.gd")
begin = item.index("# 电荷体：ElectricalCharge")
end = item.index("func sendCharge(", begin)
item = item[:begin] + '''# ElectricalCharge's path and occupancy state; no scene or particles.
class CoreElectricalCharge:
	var lastChargedItem = null
	var curChargedItem = null
	var inventoryCells: Array = []
	var callbackDelays: Array = []
	var elapsed := 0.0
	var nextCell := 2
	var active := true


''' + item[end:]
anchor = "\t_chargeEnterCell(CoreElectricalCharge.new(), 1, inv_cells)\n"
assert item.count(anchor) == 1
item = item.replace(anchor, '''	var charge = CoreElectricalCharge.new()
	charge.inventoryCells = inv_cells
	var half_cell_duration = 0.5 * (chargeDuration / speedFactor) / (cells.size() - 1)
	var delay := 0.0
	for i in cells.size() - 1:
		delay += half_cell_duration
		delay += half_cell_duration
		charge.callbackDelays.append(_f32eng(delay))
	# Registration precedes synchronous entry: a receiver may emit another charge.
	ctx.registerMotion(1, self, charge)
	_chargeEnterCell(charge, 1, inv_cells)
''')
item += '''
static func _f32eng(value: float) -> float:
	var packed := PoolRealArray()
	packed.append(value)
	return packed[0]

func _tickChargePath(charge, delta: float) -> void:
	charge.elapsed = _f32eng(charge.elapsed + delta)
	while charge.nextCell <= charge.inventoryCells.size():
		if charge.elapsed < charge.callbackDelays[charge.nextCell - 2]:
			return
		_chargeEnterCell(charge, charge.nextCell, charge.inventoryCells)
		charge.nextCell += 1
	charge.active = false
	charge.lastChargedItem = null
	charge.curChargedItem = null
'''
save("CoreItem.gd", item)
# The Python source intentionally calls generator-provided cache helpers. Native
# GD/C++ mirrors use the original dispatch body; preserve both existing paths.
for area in (dest / "gd_core_test", dest / "native_sim_cpp"):
    mirror_source = (src / area.name / "gd_core/CoreItem.gd").read_text("utf8")
    start = mirror_source.index("func _hasBehaviorMethod(")
    stop = mirror_source.index("func _behavior_call(", start)
    dispatch = mirror_source[start:stop].rstrip()
    target = area / "gd_core/CoreItem.gd"
    target.write_text(function(item, "_hasBehaviorMethod", dispatch), encoding="utf8", newline="\n")

combat = load("CoreCombat.gd")
anchor = "func activateItems(items: Array) -> void :\n"
assert combat.count(anchor) == 1
combat = combat.replace(anchor, anchor + '''	if ctx.activation_rng_state != null:
		ctx.set_state(int(ctx.activation_rng_state))
	if ctx.idle_timer_initial.size() == 2:
		player._idle_animation_left = float(ctx.idle_timer_initial[0])
		opponent._idle_animation_left = float(ctx.idle_timer_initial[1])
	if ctx.flicker_initial != null:
		ctx.restoreFlickers()
''')
begin = combat.index("\tfor character in [opponent, player]:\n", combat.index("func physicsTick("))
end = combat.index("\t# ⑧ 空闲型 Timer", begin)
combat = combat[:begin] + combat[end:]
anchor = "\tctx.advancePhysicsFrame(delta)\n"
assert combat.count(anchor) == 1
combat = combat.replace(anchor, '''	ctx.timer_pass_epoch += 1
	ctx.in_physics_timer_pass = true
	opponent.snapshotPhysicsTimers()
	player.snapshotPhysicsTimers()
	_tickCharacterTimers(opponent, delta)
	_fatigueTick()
	_tickCharacterTimers(player, delta)
	ctx.in_physics_timer_pass = false
''' + anchor)
combat = combat.replace("\t_fatigueTick()\n\tctx.flushDeferred()\n", "\topponent.tickIdleAnimation(delta)\n\tplayer.tickIdleAnimation(delta)\n\tctx.tickFlickers(delta)\n\tctx.flushDeferred()\n")
anchor = "\t\tctx._flushTimed()\n"
assert combat.count(anchor) == 1
combat = combat.replace(anchor, anchor + "\t\tctx.tickMotion(delta)\n")
anchor = "\t\t\tactivateItems(ordered_items)\n"
assert combat.count(anchor) == 1
combat = combat.replace(anchor, anchor + "\t\t\tctx.tickMotion(delta)\n")
combat += '''
func _tickCharacterTimers(character, delta: float) -> void:
	character.tickPhysicsTimers(delta)
	character.tickBuffs(delta)
	for item in character.inventory.getItems():
		item.tickTimersPass(delta)
'''
save("CoreCombat.gd", combat)

# Carry the shared initial context through the existing replay entry points.
fixture_path = dest / "tools/gen_fixture_from_lineup.py"
fixture = (src / "tools/gen_fixture_from_lineup.py").read_text("utf8")
anchor = '            "below_master": controls.get("below_master", True),\n'
assert fixture.count(anchor) == 1
fixture = fixture.replace(anchor, anchor + '''            "replay_initial": controls.get("replay_initial"),
            "native_activation_order": controls.get("native_activation_order"),
''')
fixture_path.write_text(fixture, encoding="utf8", newline="\n")

harness_path = dest / "gd_core_test/OracleAlignBattle.gd"
harness = (src / "gd_core_test/OracleAlignBattle.gd").read_text("utf8")
anchor = "\tvar order := activation_order(seed_value, p_items, o_items)\n"
assert harness.count(anchor) == 1
harness = harness.replace(anchor, anchor + '''	if c.get("native_activation_order") != null:
		order = c["native_activation_order"]
	if c.get("replay_initial") != null:
		ctx.setReplayInitial(c["replay_initial"].get("activation_rng_state"), c["replay_initial"].get("idle_left", []), c["replay_initial"].get("flickers"))
''')
anchor = '\t\t"custom_health_multiplier": ctx.custom_health_multiplier,\n'
assert harness.count(anchor) == 1
harness = harness.replace(anchor, anchor + '\t\t"replay_initial": {"activation_rng_state": ctx.activation_rng_state, "idle_left": ctx.idle_timer_initial, "flickers": ctx.flicker_initial} if ctx.activation_rng_state != null else null,\n')
harness_path.write_text(harness, encoding="utf8", newline="\n")

verifier_path = dest / "tools/verify_oracle.py"
verifier = (src / "tools/verify_oracle.py").read_text("utf8")
anchor = '            eng.ctx.lib_fires = [list(map(float, e)) for e in eng_kwargs_lib]\n'
assert verifier.count(anchor) == 1
verifier = verifier.replace(anchor, anchor + '''            native_initial = fixture[case_id].get("replay_initial")
            if native_initial is not None:
                eng.ctx.setReplayInitial(native_initial.get("activation_rng_state"), native_initial.get("idle_left", []), native_initial.get("flickers"))
''')
anchor = '        "custom_health_multiplier": float(eng.ctx.custom_health_multiplier),\n'
assert verifier.count(anchor) == 1
verifier = verifier.replace(anchor, anchor + '''        "replay_initial": {"activation_rng_state": eng.ctx.activation_rng_state,
                           "idle_left": list(eng.ctx.idle_timer_initial), "flickers": eng.ctx.flicker_initial} if eng.ctx.activation_rng_state is not None else None,
''')
verifier_path.write_text(verifier, encoding="utf8", newline="\n")

cpp_verifier = (src / "tools/_cpp_verify_events.py").read_text("utf8")
anchor = '        below_master = gd_doc.get("below_master")\n'
assert cpp_verifier.count(anchor) == 1
cpp_verifier = cpp_verifier.replace(anchor, '''        if fx.get("replay_initial") is not None and any(doc.get("replay_initial") != fx["replay_initial"] for doc in (gd_doc, pyd)):
            rec["category"] = "input_mismatch"
            rec["notes"].append("Initial activation or idle timer state differs from fixture")
''' + anchor)
anchor = "                          label_rng_enabled=bool(fx.get('label_rng', True)))\n"
assert cpp_verifier.count(anchor) == 1
cpp_verifier = cpp_verifier.replace(anchor, "                          label_rng_enabled=bool(fx.get('label_rng', True)),\n                          **({'replay_initial': fx['replay_initial']} if fx.get('replay_initial') is not None else {}))\n")
(dest / "tools/_cpp_verify_events.py").write_text(cpp_verifier, encoding="utf8", newline="\n")

generator = (src / "tools/gd_to_py.py").read_text("utf8")
anchor = '    text += \'_R.reg("%s", %s)\\n\' % (f.res_path, f.py_class)\n'
assert generator.count(anchor) == 1
generator = generator.replace(anchor, '''    _native_float = _T2 + "packed = PoolRealArray()" + chr(10) + _T2 + "packed.append(value)" + chr(10) + _T2 + "return packed[0]"
    n_native_float = text.count(_native_float)
    if n_native_float:
        text = text.replace(_native_float, _T2 + "return f32(value)")
        hit["PoolRealArray→rt.f32"] = hit.get("PoolRealArray→rt.f32", 0) + n_native_float
''' + anchor)
anchor = '        old = "\\t\\t\\t\\titem.tickTimersPass(delta)\\n"\n'
assert generator.count(anchor) == 1
generator = generator.replace(anchor, anchor + '''        helper_call = "\\t\\t\\titem.tickTimersPass(delta)\\n"
        in_helper = cc.count(old) == 0 and cc.count(helper_call) == 1
        if in_helper:
            old = helper_call
''')
anchor = "        cc = cc.replace(old, new, 1)\n"
assert generator.count(anchor) == 1
generator = generator.replace(anchor, '''        if in_helper:
            new = new.replace("\\t\\t\\t\\t", "\\t\\t\\t").replace("_iter__loc", "_iter")
''' + anchor)
(dest / "tools/gd_to_py.py").write_text(generator, encoding="utf8", newline="\n")

# Preserve initial generation inputs for auditing the isolated candidate.
(dest / "native_candidate.json").write_text(json.dumps({
    "version": "1.1.10", "source": str(src),
    "scope": "Native scheduling and minimal character visual RNG state; work in progress"
}, indent=2) + "\n", encoding="utf8")
print(dest)
