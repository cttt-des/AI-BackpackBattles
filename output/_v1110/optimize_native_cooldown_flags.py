"""Specialize boolean cooldown checks while retaining truth conversion for other types."""
import argparse
from pathlib import Path


def optimize(native):
    runtime = (native / "gd_rt.cpp").read_text("utf8")
    if "case GdVal::Kind::Bool: return v.b;" not in runtime:
        raise ValueError("The runtime boolean truth conversion changed")
    updates = {}
    for shard, receiver, expected in (("shard_00", "this", 1),
                                      ("shard_03", "cooldown_item", 2),
                                      ("shard_03", "cooldown_gem", 2)):
        path = native / "gen/shards" / (shard + ".cpp")
        source = updates.get(path, path.read_text("utf8"))
        field = receiver + "->f__cooldown_active"
        original = "gd::gd_truth(" + field + ")"
        if source.count(original) != expected:
            raise ValueError(f"Expected {expected} cooldown checks for {receiver}")
        fast = ("([&] { const auto& active = " + field + "; "
                "if (active.kind == gd::GdVal::Kind::Bool) [[likely]] return active.b; "
                "return gd::gd_truth(active); }())")
        updates[path] = source.replace(original, fast)
    for path, source in updates.items():
        path.write_text(source, encoding="utf8", newline="\n")
    print("Specialized five cooldown flag checks with the original non-boolean fallback", flush=True)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    optimize(parser.parse_args().native)
