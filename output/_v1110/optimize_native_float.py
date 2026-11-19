"""Lower proven one-element PoolRealArray float conversions to scalar casts.

Only generated methods with the exact conversion-only body are eligible.
Run after gd_to_cpp.py and before build_windows.py. No RNG or event changes.
"""
from pathlib import Path
import re

stage = Path(__file__).resolve().parent
generated = stage / "sim_native/native_sim_cpp/native_sim/gen/shards"
# The generated lambda in call_method contains braces, so match the complete
# known function ending, not an arbitrary C++ block.
pattern = re.compile(r"gd::GdVal (Gd__\w+::sf__(?:f32eng|nativeF32))\(gd::BattleCtx& gd_ctx, const gd::GdVal\* _args, int _argc\) \{\n(.*?)\n\}", re.S)
changed = []
for path in generated.glob("*.cpp"):
    text = path.read_text("utf8")
    def lower(match):
        body = match[2]
        if "static_cast<double>(static_cast<float>(value.as_float()))" in body:
            changed.append(match[1])
            return match[0]
        assert body.count("create_pool_real") == 1 and body.count("gd::SYM_append") == 1, match[1]
        assert body.count("gd::get_index") == 1 and "from_int(0LL)" in body, match[1]
        assert body.count("gd_coerce_float") == 1 and body.count("_args[0]") == 1, match[1]
        assert body.count("return ") == 3, match[1]  # lambda, index, unreachable fallback
        changed.append(match[1])
        return ("gd::GdVal " + match[1] + "(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {\n"
                "    (void)gd_ctx;\n"
                "    const auto value = gd::gd_coerce_float(_argc > 0 ? _args[0] : gd::GdVal::null());\n"
                "    return gd::GdVal::from_float(static_cast<double>(static_cast<float>(value.as_float())));\n}")
    updated = pattern.sub(lower, text)
    if updated != text:
        path.write_text(updated, encoding="utf8", newline="\n")
assert len(changed) == 5, changed
print("Scalar float conversions:", changed)
