"""Match Godot's double round near half-integer boundaries."""
from stage_native_mega_clover_rng import SIM, replace_one


def main():
    source = SIM / "native_sim_cpp/native_sim/gd_rt.cpp"
    body = source.read_text("utf8")
    old = """GdVal gd_round(const GdVal& x) {
    double v = x.as_float();
    return GdVal::from_float(v >= 0.0 ? std::floor(v + 0.5) : -std::floor(-v + 0.5));
}"""
    new = """GdVal gd_round(const GdVal& x) {
    return GdVal::from_float(std::round(x.as_float()));
}"""
    updated_cpp = replace_one(body, old, new)

    python = SIM / "gd_core_py/_rt.py"
    body = python.read_text("utf8")
    start = body.index("def round(x):\n")
    end = body.index("\n\n# ", start)
    updated_python = body[:start] + """def round(x):
    \"\"\"Round like Godot's C double round, with halfway values away from zero.\"\"\"
    fraction, whole = math.modf(x)
    return whole + math.copysign(1.0, fraction) if abs(fraction) >= 0.5 else whole
""" + body[end:]

    source.write_text(updated_cpp, encoding="utf8", newline="\n")
    python.write_text(updated_python, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()
