"""Advance the motion snapshot in place and keep callback order."""
from pathlib import Path


sim = Path(__file__).resolve().parent / "sim_native"
relative = Path("gd_core/CoreContext.gd")
source = (sim / relative).read_text("utf8")
start = source.index("func tickMotion(delta: float) -> void:\n")
end = source.index("# FlickerAnimation's only", start)
source = source[:start] + '''func tickMotion(delta: float) -> void:
	# Snapshot length keeps motions appended by callbacks for the next pass.
	var limit := _motion_queue.size()
	var read := 0
	var write := 0
	while read < limit:
		var entry = _motion_queue[read]
		var keep := false
		if entry[0] == 0:
			var character = entry[1]
			if character._visual_generation == entry[2] and character._visual_kind != 0:
				character.tickVisualMotion(delta)
				keep = character._visual_kind != 0
		else:
			var charge = entry[2]
			entry[1]._tickChargePath(charge, delta)
			keep = charge.active
		if keep:
			if write != read:
				_motion_queue[write] = entry
			write += 1
		read += 1
	if write != limit:
		# Append the new entries after the surviving snapshot entries.
		var end := _motion_queue.size()
		while read < end:
			_motion_queue[write] = _motion_queue[read]
			write += 1
			read += 1
		_motion_queue.resize(write)


''' + source[end:]
for root in (sim, sim / "gd_core_test", sim / "native_sim_cpp"):
    (root / relative).write_text(source, encoding="utf8", newline="\n")
