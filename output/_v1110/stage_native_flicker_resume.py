"""Keep AnimationPlayer's position when a second timer plays the same clip."""
from stage_native_mega_clover_rng import SIM, replace_one


def main():
    changes = {}
    for root in (SIM, SIM / "native_sim_cpp"):
        context = root / "gd_core/CoreContext.gd"
        source = context.read_text("utf8")
        changes[context] = replace_one(
            source,
            "\t\tposition = 0.0\n\t\tplaying = true\n",
            "\t\t# AnimationPlayer.play of the same clip resumes until it reaches the end.\n"
            "\t\tif position == length:\n"
            "\t\t\tposition = 0.0\n"
            "\t\tplaying = true\n",
        )
    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()
