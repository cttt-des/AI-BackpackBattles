"""Allow replay of the original ring effects present during item placement."""
import argparse

from stage_native_mega_clover_rng import SIM, replace_one


def main():
    native = SIM / "native_sim_cpp/native_sim"
    wrapper = native / "engine_wrapper.cpp"
    source = wrapper.read_text("utf8")
    source = replace_one(source, "    int16_t _pad0;\n", "    uint16_t n_placement_effects;\n")
    anchor = "static void build_side_items(\n"
    source = replace_one(source, anchor, '''static void apply_ring_effects(gd::BattleCtx& battle, gd::GdVal item,
                               const PackedEffect* effects, uint16_t count) {
    auto* entries = gd::GdArr::create(battle.arena, count);
    for (uint16_t i = 0; i < count; ++i) {
        auto* effect = gd::GdDict::create(battle.arena, 2);
        effect->set(battle.arena, gd::GdVal::from_str(gd::make_static_str("triggerType")),
                    gd::GdVal::from_int(effects[i].trigger_type));
        effect->set(battle.arena, gd::GdVal::from_str(gd::make_static_str("stackType")),
                    gd::GdVal::from_int(effects[i].stack_type));
        entries->push_back(battle.arena, gd::GdVal::from_dict(effect));
    }
    auto argument = gd::GdVal::from_arr(entries);
    gd::call_method(battle, item, g_syms.setCraftedEffects, &argument, 1);
}

''' + anchor)
    anchor = "        gd::GdVal add_args[2] = {iv, gd::GdVal::from_arr(occ)};\n"
    source = replace_one(source, anchor, '''        // Match the ring's _ready -> addItem -> setData sequence. Placement
        // can grant a dynamic type that survives when the saved rolls load.
        if (pi.n_placement_effects && pi.n_effects + pi.n_placement_effects <= 8)
            apply_ring_effects(battle, iv, pi.effects + pi.n_effects, pi.n_placement_effects);

''' + anchor)
    start = source.index("        if (pi.n_effects > 0) {\n")
    stop = source.index("        for (uint8_t gi", start)
    source = source[:start] + source[stop:]
    anchor = "        out_items->push_back(battle.arena, iv);\n"
    changes = {wrapper: replace_one(source, anchor, '''        if (pi.n_effects > 0 && pi.n_effects <= 8)
            apply_ring_effects(battle, iv, pi.effects, pi.n_effects);

''' + anchor)}

    binding = native / "sim.py"
    source = binding.read_text("utf8")
    source = replace_one(source, '        ("_pad0", ctypes.c_int16),\n',
                         '        ("n_placement_effects", ctypes.c_uint16),\n')
    anchor = '                    "effects": node.get("effects"),\n'
    source = replace_one(source, anchor, anchor + '                    "placement_effects": node.get("placement_effects"),\n')
    old = '''            for ei in range(pi.n_effects):
                e = effs[ei]
                pi.effects[ei].trigger_type = int(e["triggerType"])
                pi.effects[ei].stack_type = int(e["stackType"])
'''
    new = '''            placement = it.get("placement_effects")
            if placement:
                if len(placement) != len(effs) or len(effs) + len(placement) > 8:
                    raise ValueError(f"Invalid placement effects for {it['key']}")
                pi.n_placement_effects = len(placement)
                effs = [*effs, *placement]
            for index in range(pi.n_effects + pi.n_placement_effects):
                effect = effs[index]
                pi.effects[index].trigger_type = int(effect["triggerType"])
                pi.effects[index].stack_type = int(effect["stackType"])
'''
    changes[binding] = replace_one(source, old, new)

    fixtures = SIM / "tools/gen_fixture_from_lineup.py"
    source = fixtures.read_text("utf8")
    anchor = '            ] if it.get("effects") else None),\n'
    source = replace_one(source, anchor, anchor + '            "placement_effects": it.get("placement_effects"),\n')
    for indent in (20, 32):
        anchor = " " * indent + '"effects": e["effects"],\n'
        start = source.index("\n" + anchor) + 1
        stop = start + len(anchor)
        source = source[:stop] + " " * indent + '"placement_effects": e["placement_effects"],\n' + source[stop:]
    changes[fixtures] = source

    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


def stage_verifier():
    verifier = SIM / "tools/_cpp_verify_events.py"
    source = verifier.read_text("utf8")
    anchor = "def compare_native_case(sim, gem_origin, item_origin, args, fx, cid):\n"
    source = replace_one(source, anchor, '''def match_ring_inputs(lineup, fixture, path):
    expected = [item.get("placement_effects") for item in lineup["items"]]
    assembled = json.loads(path.read_bytes())["backpack"]["items"]
    return all([item.get("placement_effects") for item in items] == expected
               for items in (fixture["items"], assembled))


''' + anchor)
    anchor = '    lineup = json.loads(lineup_path.read_bytes())\n'
    source = replace_one(source, anchor, anchor + '''    if args.ring_placement_observations:
        observed = args.ring_placement_observations / cid
        if observed.is_dir():
            sys.path.insert(0, str(ROOT.parent))
            from native_ring_placement_input import read_placement_input

            lineup, placement_hash = read_placement_input(original, observed)
            if not all(match_ring_inputs(lineup[side], fx[side], path)
                       for side, path in (("player", player_path), ("opponent", opponent_path))):
                rec["category"] = "input_mismatch"
                rec["notes"].append("Packed fixture disagrees with the observed ring placement input")
                return rec
            rec["ring_placement_lineups_sha256"] = placement_hash
''')
    anchor = "    ap.add_argument('--original-dir', type=Path,\n"
    source = replace_one(source, anchor, '''    ap.add_argument('--ring-placement-observations', type=Path,
                    help='Exact original reruns with pre-placement ring observations')
''' + anchor)

    verifier.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--verifier-only", action="store_true")
    if not parser.parse_args().verifier_only:
        main()
    stage_verifier()
