"""Keep battle character idle callbacks in the original signal order."""
from stage_native_mega_clover_rng import SIM, replace_one


def main():
    for root in (SIM, SIM / "gd_core_test", SIM / "native_sim_cpp"):
        context = root / "gd_core/CoreContext.gd"
        source = context.read_text("utf8")
        old = '''\tfor call in _idle_frame_calls:
\t\tif call[0] == obj and call[1] == methodName:
\t\t\treturn
\t_idle_frame_calls.push_back([obj, methodName, args])
'''
        new = '''\tvar position := _idle_frame_calls.size()
\tfor i in range(_idle_frame_calls.size()):
\t\tvar call = _idle_frame_calls[i]
\t\tif call[0] == obj and call[1] == methodName:
\t\t\treturn
\t\t# Godot idle_frame emits in receiver ObjectID order, then by method.
\t\t# Game creates the persistent Player before instancing the Opponent.
\t\tif position == _idle_frame_calls.size() and (obj == player or obj == opponent):
\t\t\tif (obj == player and call[0] == opponent) or (call[0] == obj and methodName < call[1]):
\t\t\t\tposition = i
\t_idle_frame_calls.insert(position, [obj, methodName, args])
'''
        context.write_text(replace_one(source, old, new), encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()
