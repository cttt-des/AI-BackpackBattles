"""Build a C++ A/B DLL with only the headless cooldown display block removed."""
from pathlib import Path
import argparse
import re
import runpy
import shutil
import subprocess
import tempfile


stage = Path(__file__).resolve().parent
native = stage / "sim_native/native_sim_cpp/native_sim"
parser = argparse.ArgumentParser()
parser.add_argument("--objects", type=Path, required=True, help="Object directory of the current clean candidate build")
parser.add_argument("--out", type=Path, required=True)
args = parser.parse_args()
build = runpy.run_path(str(native / "build_windows.py"))
baseline = args.objects / "libgdcore.dll"
assert baseline.read_bytes() == (native / "libgdcore.dll").read_bytes(), "Object cache and candidate DLL differ"
assert "showCooldown" not in (native / "engine_wrapper.cpp").read_text("utf8"), "C++ display hooks changed"
shard = native / "gen/shards/shard_00.cpp"
source = shard.read_text("utf8")
start = source.index("gd::GdVal Gd__gd_core__CoreItem::fn_physicsTick(")
end = source.index("\n}", start)
block = re.compile(r"(?m)^        if \(gd::gd_truth\(gd::get_prop\(gd_ctx, this->f_ctx, SYM_GEN_show_cooldown_progress_\d+\)\)\) \{\n"
                   r"            \(void\)\(\[&\]\(\) \{ gd::GdVal _ca\[\] = \{gd::GdVal::from_obj\(this\), "
                   r"gd::gd_sub\(gd::GdVal::from_float\(1.0\), gd::gd_div\(gd_ctx, this->f_triggerTime, this->f_iterationCooldown\)\)\}; "
                   r"return gd::call_method\(gd_ctx, gd::get_prop\(gd_ctx, this->f_ctx, SYM_GEN_hooks_\d+\), "
                   r"SYM_GEN_showCooldown_\d+, _ca, 2\); \}\)\(\);\n        \}\n")
method, substitutions = block.subn("", source[start:end])
assert substitutions == 1, "Generated display block changed"
objects = sorted(args.objects.glob("*.o"))
assert len(objects) == 20 and sum(path.name == "shard_00.o" for path in objects) == 1
with tempfile.TemporaryDirectory(prefix="bpb_cooldown_") as temp:
    temp = Path(temp)
    rewritten = temp / shard.name
    rewritten.write_text(source[:start] + method + source[end:], encoding="utf8", newline="\n")
    unit = temp / "shard_00.o"
    flags = [build["CXX"], *build["COMMON"]]
    subprocess.run([*flags, "-I", str(shard.parent), "-c", str(rewritten), "-o", str(unit)], check=True)
    dll = temp / "libgdcore.dll"
    subprocess.run([*flags, "-shared", "-static", "-o", str(dll),
                    *(str(unit if path.name == unit.name else path) for path in objects)], check=True)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(dll, args.out)
