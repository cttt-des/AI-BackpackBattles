"""Track generated class headers when reusing MinGW object files."""
import argparse
from pathlib import Path


ANCHOR = '        ROOT / "gen" / "class_metas.hpp",\n'
DEPENDENCY = '        *sorted((ROOT / "gen" / "hdrs").glob("*.hpp")),\n'


def optimize(native):
    path = native / "build_windows.py"
    source = path.read_text("utf8")
    if source.count(ANCHOR) != 1:
        raise ValueError("The build header dependency list changed")
    if DEPENDENCY in source:
        print("Generated class headers are already tracked", flush=True)
        return
    path.write_text(source.replace(ANCHOR, ANCHOR + DEPENDENCY), encoding="utf8", newline="\n")
    print("Added generated class headers to object-cache invalidation", flush=True)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    optimize(parser.parse_args().native)
