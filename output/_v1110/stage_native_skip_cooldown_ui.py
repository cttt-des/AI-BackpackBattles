"""Skip per-tick formatting and dispatch of unused cooldown display updates."""
from pathlib import Path


sim = Path(__file__).resolve().parent / "sim_native"


def replace(path, old, new):
    source = path.read_text("utf8")
    assert source.count(old) == 1, path
    path.write_text(source.replace(old, new), encoding="utf8", newline="\n")


for root in (sim, sim / "gd_core_test", sim / "native_sim_cpp"):
    replace(root / "gd_core/CoreContext.gd", "var warn_unknown_api := true\n",
            "var warn_unknown_api := true\nvar show_cooldown_progress := false\n")
    replace(root / "gd_core/CoreContext.gd", "\thooks = _hooks if _hooks != null else CoreHooks.new()\n",
            "\thooks = _hooks if _hooks != null else CoreHooks.new()\n\tshow_cooldown_progress = _hooks != null\n")
    replace(root / "gd_core/CoreItem.gd", "\t\tctx.hooks.showCooldown(self, 1.0 - (triggerTime / iterationCooldown))\n",
            "\t\tif ctx.show_cooldown_progress:\n\t\t\tctx.hooks.showCooldown(self, 1.0 - (triggerTime / iterationCooldown))\n")

wrapper = sim / "native_sim_cpp/native_sim/engine_wrapper.cpp"
# All C++ runs use NativeBattleHooks, which exports events and leaves display hooks as no-ops.
source = wrapper.read_text("utf8")
assert "showCooldown" not in source
anchor = "    auto* ctx_obj = static_cast<Gd__gd_core__CoreContext*>(ctx_val.obj);\n"
replace(wrapper, anchor, anchor + "    ctx_obj->f_show_cooldown_progress = gd::GdVal::from_bool(false);\n")

# Python already strips this no-op call. Strip its new guard along with it.
generator = sim / "tools/gd_to_py.py"
old = '    old = ("\\t\\t\\tself.ctx.hooks.showCooldown(self, 1.0 - _div(self.triggerTime, self.iterationCooldown))\\n")'
new = ('    old = ("\\t\\t\\tif self.ctx.show_cooldown_progress:\\n"\n'
       '           "\\t\\t\\t\\tself.ctx.hooks.showCooldown(self, 1.0 - _div(self.triggerTime, self.iterationCooldown))\\n")')
replace(generator, old, new)
