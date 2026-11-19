"""Retain the engine RNG advances of Mega Clover's CPU particle burst."""
from pathlib import Path


SIM = Path(__file__).resolve().parent / "sim_native"
BURST = '''# CPU particle births measured at fixed 60 Hz using the original emitter settings.
const MEGA_CLOVER_PARTICLE_DRAWS := [20, 10, 10, 10, 10, 10, 0, 10, 10]
var _mega_clover_draws := []
var _mega_clover_draw_cursor := 0
var _mega_clover_pending_draws := 0
var _mega_clover_before_physics := 0

func scheduleMegaCloverParticleDraws() -> void:
	if replay_engine_rng == null:
		return
	if _mega_clover_draws.empty():
		_mega_clover_draws.resize(MEGA_CLOVER_PARTICLE_DRAWS.size())
		for i in range(_mega_clover_draws.size()):
			_mega_clover_draws[i] = 0
	var first: int = MEGA_CLOVER_PARTICLE_DRAWS[0]
	if _critical_shake_after_idle:
		# The first redraw can emit a particle before the next physics pass.
		_mega_clover_before_physics += 10
		first -= 10
	for i in range(MEGA_CLOVER_PARTICLE_DRAWS.size()):
		var index: int = (_mega_clover_draw_cursor + i) % _mega_clover_draws.size()
		var count: int = first if i == 0 else MEGA_CLOVER_PARTICLE_DRAWS[i]
		_mega_clover_draws[index] += count
		_mega_clover_pending_draws += count

func stepMegaCloverParticleDraws() -> void:
	var count: int = _mega_clover_draws[_mega_clover_draw_cursor]
	_mega_clover_draws[_mega_clover_draw_cursor] = 0
	_mega_clover_draw_cursor = (_mega_clover_draw_cursor + 1) % _mega_clover_draws.size()
	_mega_clover_pending_draws -= count
	for _i in range(count):
		randi()

'''


def replace_one(source, anchor, replacement):
    assert source.count(anchor) == 1, anchor
    return source.replace(anchor, replacement)


def main():
    changes = {}
    for root in (SIM, SIM / "native_sim_cpp"):
        context = root / "gd_core/CoreContext.gd"
        source = context.read_text("utf8")
        anchor = "func resetCriticalShake() -> void:\n"
        source = replace_one(source, anchor, BURST + anchor + "\t_mega_clover_draws.clear()\n"
                             "\t_mega_clover_draw_cursor = 0\n\t_mega_clover_pending_draws = 0\n"
                             "\t_mega_clover_before_physics = 0\n")
        anchor = "func beginCriticalShakeFrame() -> void:\n"
        source = replace_one(source, anchor, anchor + "\tif _mega_clover_before_physics > 0:\n"
                             "\t\tfor _i in range(_mega_clover_before_physics):\n"
                             "\t\t\trandi()\n\t\t_mega_clover_before_physics = 0\n")
        anchor = "func stepCriticalShake() -> void:\n"
        changes[context] = replace_one(source, anchor, anchor + "\tif _mega_clover_pending_draws > 0:\n"
                                       "\t\tstepMegaCloverParticleDraws()\n")
        item = root / "gd_core_items/Exclusive/MegaClover.gd"
        source = item.read_text("utf8")
        anchor = "\t\tgiveRandomBuffs(numBuffs, event, stackTypes)\n\t\tactivate()\n"
        changes[item] = replace_one(source, anchor, anchor + "\t\tctx.scheduleMegaCloverParticleDraws()\n")
    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()
