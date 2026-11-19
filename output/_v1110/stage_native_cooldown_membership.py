"""Match Godot's snapshot of the ordinary physics-process group."""
from stage_native_mega_clover_rng import SIM, replace_one


def main():
    changes = {}
    for root in (SIM, SIM / "native_sim_cpp"):
        context = root / "gd_core/CoreContext.gd"
        anchor = "var in_physics_timer_pass := false\n"
        changes[context] = replace_one(context.read_text("utf8"), anchor,
                                       anchor + "var in_item_physics_pass := false\n")

        combat = root / "gd_core/CoreCombat.gd"
        anchor = "\tctx.advancePhysicsFrame(delta)\n"
        source = replace_one(combat.read_text("utf8"), anchor,
                             anchor + "\tctx.in_item_physics_pass = true\n")
        anchor = """\tfor item in player.inventory.getItems():
\t\titem.physicsTick(delta)
\t\tfor gem in item.gems:
\t\t\tif gem != null:
\t\t\t\tgem.physicsTick(delta)
"""
        changes[combat] = replace_one(source, anchor, anchor + "\tctx.in_item_physics_pass = false\n")

        item = root / "gd_core/CoreItem.gd"
        anchor = "var _cooldown_active := false\n"
        source = replace_one(item.read_text("utf8"), anchor, anchor +
                             "var _cooldown_changed_epoch := -1\nvar _cooldown_blocked_epoch := -1\n")
        anchor = """func setCooldownActive(active: bool) -> void :
\t_cooldown_active = active


func activateCooldown() -> void :
\t_cooldown_active = true


func deactivateCooldown() -> void :
\t_cooldown_active = false
"""
        source = replace_one(source, anchor, """func setCooldownActive(active: bool) -> void :
	if _cooldown_active != active and ctx.in_item_physics_pass:
		var epoch: int = ctx.timer_pass_epoch
		if _cooldown_changed_epoch != epoch:
			# Only nodes enabled at the start of this pass are in its snapshot.
			_cooldown_changed_epoch = epoch
			if active:
				_cooldown_blocked_epoch = epoch
	_cooldown_active = active


func activateCooldown() -> void :
	setCooldownActive(true)


func deactivateCooldown() -> void :
	setCooldownActive(false)
""")
        anchor = "\tif not _cooldown_active:\n\t\treturn\n\tif not character().isStunned():\n"
        changes[item] = replace_one(source, anchor, """\tif not _cooldown_active:
\t\treturn
\tif _cooldown_blocked_epoch >= 0 and _cooldown_blocked_epoch == ctx.timer_pass_epoch:
\t\treturn
\tif not character().isStunned():
""")
    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()
