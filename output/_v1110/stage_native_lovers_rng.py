"""Preserve the engine RNG consumption of The Lovers' single particle burst."""
import json

from stage_native_mega_clover_rng import SIM, replace_one


BURSTS = """# Births observed at 60 Hz. The first ten draws can occur before the next physics pass.
const MEGA_CLOVER_PARTICLE_DRAWS := [20, 10, 10, 10, 10, 10, 0, 10, 10]
const LOVERS_PARTICLE_DRAWS := [20, 10, 10, 10, 10, 10, 10, 10, 10, 0, 10, 10, 10, 10]
const LOVERS_PARTICLE_RESTART_DRAWS := [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 10, 10, 10, 10]
var _particle_draws := []
var particle_draw_frame := 0
var _particle_pending_draws := 0
var _particle_before_physics := 0

func scheduleParticleDraws(schedule: Array) -> void:
	if replay_engine_rng == null:
		return
	var phase := 2 if _critical_shake_after_idle else 1
	changeParticleDraws(schedule, particle_draw_frame, phase, 1)

# phase 0: already visible; 1: redraw during idle; 2: redraw before physics.
func changeParticleDraws(schedule: Array, start: int, phase: int, direction: int) -> void:
	if _particle_draws.empty():
		_particle_draws.resize(LOVERS_PARTICLE_RESTART_DRAWS.size())
		for i in range(_particle_draws.size()):
			_particle_draws[i] = 0
	if phase == 2 and start == particle_draw_frame and _critical_shake_after_idle:
		_particle_before_physics += direction * 10
	for i in range(particle_draw_frame - start, schedule.size()):
		var index: int = (start + i) % _particle_draws.size()
		var count: int = schedule[i]
		if i == 0 and phase == 2:
			count -= 10
		_particle_draws[index] += direction * count
		_particle_pending_draws += direction * count

func restartLoversParticleDraws(previous_frame: int, previous_phase: int, visible: bool) -> int:
	# Joker can call the same card repeatedly. The original restarts its emitter.
	var redraw_phase := 2 if _critical_shake_after_idle else 1
	var pending_redraw := previous_frame == particle_draw_frame and previous_phase == redraw_phase
	if previous_frame >= 0:
		var previous := LOVERS_PARTICLE_RESTART_DRAWS if previous_phase == 0 else LOVERS_PARTICLE_DRAWS
		changeParticleDraws(previous, previous_frame, previous_phase, -1)
	if visible and not pending_redraw:
		changeParticleDraws(LOVERS_PARTICLE_RESTART_DRAWS, particle_draw_frame, 0, 1)
		return 0
	changeParticleDraws(LOVERS_PARTICLE_DRAWS, particle_draw_frame, redraw_phase, 1)
	return redraw_phase

func stepParticleDraws() -> void:
	var index: int = particle_draw_frame % _particle_draws.size()
	var count: int = _particle_draws[index]
	_particle_draws[index] = 0
	particle_draw_frame += 1
	_particle_pending_draws -= count
	for _i in range(count):
		randi()

"""


def main():
    observed = json.loads((SIM.parent / "native_lovers_particles_probe_result.json").read_bytes())["shipping"]
    normal = observed["physics"]
    scheduled = normal[:max(i for i, count in enumerate(normal) if count) + 1]
    assert sum(scheduled) == 140 and str(scheduled) in BURSTS
    idle = observed["idle_end"]
    restart_schedule = idle[:max(i for i, count in enumerate(idle) if count) + 1]
    assert idle == [10, normal[0] - 10] + normal[1:-1]
    assert str(restart_schedule) in BURSTS
    assert observed["same_physics_restart"] == normal
    assert observed["same_idle_restart"] == idle
    for name, initial, frame, visible in (
        ("mid_burst_restart", normal, 3, True),
        ("idle_burst_physics_restart", idle, 1, True),
        ("restart_before_hide", normal, 75, True),
        ("restart_at_hide", normal, 76, False),
        ("idle_restart_at_hide", idle, 76, True),
        ("idle_restart_after_hide", idle, 77, False),
    ):
        actual = observed[name]
        expected = (initial + [0] * frame)[:frame] + (idle if visible else normal)
        assert observed["restart_state"][name]["visible"] == visible, name
        assert actual == expected[:len(actual)], name

    changes = {}
    for root in (SIM, SIM / "native_sim_cpp"):
        context = root / "gd_core/CoreContext.gd"
        source = context.read_text("utf8")
        training = "var native_frame_rng" in source
        bursts = BURSTS.replace("if replay_engine_rng == null:", "if not native_frame_rng:") if training else BURSTS
        particle_enabled = "ctx.native_frame_rng" if training else "ctx.replay_engine_rng != null"
        if "# Births observed at 60 Hz." in source:
            start = source.index("# Births observed at 60 Hz.")
        else:
            start = source.index("# CPU particle births measured at fixed 60 Hz")
        end = source.index("func resetCriticalShake()", start)
        suffix = (source[end:].replace("_mega_clover_draw_cursor", "particle_draw_frame")
                  .replace("_mega_clover_", "_particle_").replace("stepMegaCloverParticleDraws()", "stepParticleDraws()"))
        changes[context] = source[:start] + bursts + suffix

        clover = root / "gd_core_items/Exclusive/MegaClover.gd"
        clover_text = clover.read_text("utf8")
        if "ctx.scheduleMegaCloverParticleDraws()" in clover_text:
            clover_text = replace_one(clover_text, "ctx.scheduleMegaCloverParticleDraws()",
                                      "ctx.scheduleParticleDraws(ctx.MEGA_CLOVER_PARTICLE_DRAWS)")
        changes[clover] = clover_text
        lovers = root / "gd_core_items/TheLovers.gd"
        source = lovers.read_text("utf8")
        if "var heartParticles\n" not in source:
            source = source[:source.index("var particle_draw_frame")] + "var heartParticles\n" + source[source.index("var healAmp"):]
            start = source.index(f"\t\tif {particle_enabled}")
            end = source.index("\n\tactivate()", start)
            source = source[:start] + source[end:]
            start = source.index("func prepare():")
            source = source[:start] + source[source.index("func _readyInit():", start):]
        source = replace_one(source, "var heartParticles\n", """var particle_draw_frame := -1
var particle_start_phase := 0
var particle_hidden_at := 0
""")
        source = replace_one(source, "func _readyInit():", """func prepare():
	.prepare()
	particle_draw_frame = -1
	particle_hidden_at = 0


func _readyInit():""")
        anchor = "\t\tgiveRegeneration(regen)\n"
        changes[lovers] = replace_one(source, anchor, anchor + f"""\t\tif {particle_enabled}:
\t\t\tvar next_idle: int = ctx.frame_counter + (1 if ctx._critical_shake_after_idle else 0)
\t\t\tparticle_start_phase = ctx.restartLoversParticleDraws(particle_draw_frame, particle_start_phase,
\t\t\t\t\tnext_idle < particle_hidden_at)
\t\t\tparticle_draw_frame = ctx.particle_draw_frame
\t\t\t# 76 idle passes until the original emitter's AutoHide timer expires at 60 Hz.
\t\t\tparticle_hidden_at = next_idle + 76
""")

    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()
