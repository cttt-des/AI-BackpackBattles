"""Preserve the RNG used by delayed combat log formatting of Mananana names."""
from stage_native_mega_clover_rng import SIM, replace_one


LOG_REPLAY = '''# The hidden source log formats one pending row on physics frames with no new events.
# Only Mananana's English display name reads the battle RNG. Store its row numbers.
var _mananana_log_rows = null
var _written_log_rows := 0
var _previous_written_log_rows := 0
var _rendered_log_rows := 0
var _next_mananana_log_row := 0

func prepareHiddenLog(items: Array) -> bool:
	_mananana_log_rows = null
	_written_log_rows = 0
	_previous_written_log_rows = 0
	_rendered_log_rows = 0
	_next_mananana_log_row = 0
	for item in items:
		if item.descriptor.identifier == "Mananana":
			_mananana_log_rows = []
			return true
	return false

func replayHiddenLogEvent() -> void:
	if _previous_written_log_rows == _written_log_rows and _rendered_log_rows < _written_log_rows:
		_rendered_log_rows += 1
		if (_next_mananana_log_row < _mananana_log_rows.size()
				and _mananana_log_rows[_next_mananana_log_row] == _rendered_log_rows):
			_next_mananana_log_row += 1
			if _ctx.rng.flip(0.001):
				_ctx.rng.randi_range(0, 3)
	_previous_written_log_rows = _written_log_rows

'''


def main():
    changes = {}
    for root in (SIM, SIM / "native_sim_cpp"):
        event_bus = root / "gd_core/CoreEventBus.gd"
        source = event_bus.read_text("utf8").replace("→ ctx.hooks.logEvent(event)", "→ _ctx.combat_log.logEvent(event)")
        changes[event_bus] = replace_one(source, "\t\t\t_ctx.hooks.logEvent(event)\n",
                                        "\t\t\t_ctx.combat_log.logEvent(event)\n")

        log = root / "gd_core/CoreCombatLog.gd"
        anchor = "func logEvent(event) -> void :\n\t_ctx.hooks.logEvent(event)\n"
        changes[log] = replace_one(log.read_text("utf8"), anchor, LOG_REPLAY + """func logEvent(event) -> void :
	if _mananana_log_rows != null:
		_written_log_rows += 1
		var origin = event.getOrigin()
		if origin is CoreItem and origin.descriptor.identifier == "Mananana":
			_mananana_log_rows.push_back(_written_log_rows)
	_ctx.hooks.logEvent(event)
""")

        combat = root / "gd_core/CoreCombat.gd"
        anchor = "var activated := false\n"
        source = replace_one(combat.read_text("utf8"), anchor, anchor + "var _track_hidden_log := false\n")
        anchor = "\tctx.resetCriticalShake()\n"
        source = replace_one(source, anchor, anchor + "\t_track_hidden_log = ctx.combat_log.prepareHiddenLog(ordered_items)\n")
        anchor = "\tif not activated:\n\t\tctx.flushDeferred()\n"
        source = replace_one(source, anchor, "\tif not activated:\n\t\tif _track_hidden_log:\n"
                             '\t\t\tctx.defer(ctx.combat_log, "replayHiddenLogEvent")\n\t\tctx.flushDeferred()\n')
        anchor = "\tctx.in_item_physics_pass = false\n"
        changes[combat] = replace_one(source, anchor, anchor + "\tif _track_hidden_log:\n"
                                      '\t\tctx.defer(ctx.combat_log, "replayHiddenLogEvent")\n')
    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()
