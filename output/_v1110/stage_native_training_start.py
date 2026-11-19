"""Enable the shipping frame scheduler for seeded fights without a recording."""
from stage_native_mega_clover_rng import SIM, replace_one


def stage_core(root):
    context_path = root / "gd_core/CoreContext.gd"
    context = context_path.read_text("utf8")
    anchor = "var replay_engine_rng = null\n"
    context = replace_one(context, anchor, anchor + '''var native_frame_rng := false
var native_label_mode := 0
var training_start := false
''')
    anchor = "\treplay_engine_rng = engine_rng\n"
    context = replace_one(context, anchor, anchor + '''\tnative_frame_rng = engine_rng != null
\tif native_frame_rng:
\t\tnative_label_mode = int(engine_rng[4])
''')
    context = replace_one(context, '''\tvar mode := int(replay_engine_rng[4])
\tif mode == 0 or mode == 1:
\t\tcollectCriticalShake(false)
\tif has_item and (mode == 0 or mode == 2):
''', '''\tif native_label_mode == 0 or native_label_mode == 1:
\t\tcollectCriticalShake(false)
\tif has_item and (native_label_mode == 0 or native_label_mode == 2):
''')
    anchor = "func scheduleParticleDraws(schedule: Array) -> void:\n"
    context = replace_one(context, anchor + "\tif replay_engine_rng == null:\n", anchor + "\tif not native_frame_rng:\n")
    anchor = "func restoreFlickers() -> void:\n"
    context = replace_one(context, anchor, '''func addTrainingFlicker(item, delay: float) -> void:
\tvar flicker = NativeFlicker.new()
\tflicker.ctx = self
\tvar descr = item.descriptor
\tflicker.limits = [descr.flickerMinDist, descr.flickerMaxDist, descr.flickerMinSpeed, descr.flickerMaxSpeed]
\t# Each 1.1.10 FlickerAnimation uses a 0.3-second one-shot. Only Magic Torch autoplays it.
\tflicker.length = _nativeF32(0.3)
\tflicker.playing = descr.identifier == "Magic Torch"
\tif item.character().playerId == CoreConst.CharID.OPPONENT:
\t\t_opponent_flickers.append(flicker)
\telse:
\t\t_flickers.append(flicker)
\tcallDelayed(flicker, "playAni", delay)


''' + anchor)

    combat_path = root / "gd_core/CoreCombat.gd"
    combat = combat_path.read_text("utf8").replace("ctx.replay_engine_rng != null", "ctx.native_frame_rng")
    anchor = "\t_track_hidden_log = ctx.combat_log.prepareHiddenLog(ordered_items)\n"
    combat = replace_one(combat, anchor, anchor + '''\tif ctx.training_start:
\t\tctx.callDelayed(self, "clashTrainingSwords", 1.0)
\t\tctx.callDelayed(self, "activateTraining", CoreContext.COMBAT_DELAY)
''')
    anchor = "func physicsTick(delta: float) -> void :\n"
    combat = replace_one(combat, anchor, '''func clashTrainingSwords() -> void:
\tctx.rng.randf_range(0.9, 1.0)


func activateTraining() -> void:
\tactivateItems(ordered_items)


''' + anchor)
    anchor = "\t\t_activate_countdown -= delta\n"
    combat = replace_one(combat, anchor, '''\t\tif ctx.training_start:
\t\t\tctx.advancePhysicsFrame(delta)
\t\t\tctx.beginCriticalShakeFrame()
\t\t\tstepCharacterIdle(delta)
\t\t\tctx.flushDeferred()
\t\t\tctx._flushTimed()
\t\t\tctx.tickMotion(delta)
\t\t\tctx.flushDeferred()
\t\t\treturn
''' + anchor)
    idle = '''\topponent.tickIdleAnimation(delta)
\tctx.tickOpponentFlickers(delta)
\tplayer.tickIdleAnimation(delta)
\tctx.tickFlickers(delta)
\tif ctx.native_frame_rng:
\t\tctx.stepCriticalShake()
'''
    combat = replace_one(combat, idle, "\tstepCharacterIdle(delta)\n")
    combat += "\n\nfunc stepCharacterIdle(delta: float) -> void:\n" + idle

    item_path = root / "gd_core/CoreItem.gd"
    item = replace_one(item_path.read_text("utf8"),
                       '\t\tctx.callDelayed(self, "flickerPlayAni", float(flicker_delay))\n', '''\t\tif ctx.training_start and character() != null:
\t\t\tctx.addTrainingFlicker(self, float(flicker_delay))
\t\telse:
\t\t\tctx.callDelayed(self, "flickerPlayAni", float(flicker_delay))
''')
    changes = {context_path: context, combat_path: combat, item_path: item}
    for relative in ("gd_core/CoreCharacter.gd", "gd_core_items/TheLovers.gd"):
        file = root / relative
        changes[file] = file.read_text("utf8").replace("ctx.replay_engine_rng != null", "ctx.native_frame_rng")
    return changes


def stage_wrapper(native):
    wrapper = native / "engine_wrapper.cpp"
    source = wrapper.read_text("utf8")
    source = replace_one(source, "    ReplayHostRng* host = nullptr\n",
                         "    ReplayHostRng* host = nullptr,\n    bool training_start = false\n")
    anchor = "    ctx_obj->f_show_cooldown_progress = gd::GdVal::from_bool(false);\n"
    source = replace_one(source, anchor, anchor + '''    if (training_start) {
        ctx_obj->f_training_start = gd::GdVal::from_bool(true);
        ctx_obj->f_native_frame_rng = gd::GdVal::from_bool(true);
        ctx_obj->f_replay_native_scene_delays = gd::GdVal::from_bool(true);
        ctx_obj->f_native_label_mode = gd::GdVal::from_int(opts.label_rng_enabled ? 0 : 3);
    }
''')
    anchor = "    } else if (opts.native_activation_order) {\n"
    start = source.index(anchor)
    stop = source.index("        gd::shuffle_array(battle, p_items);\n", start)
    source = source[:start] + '''    } else if (opts.native_activation_order || training_start) {
        if (!training_start) battle.bind_battle(opts.seed);
        std::unordered_map<const gd::GdObj*, int32_t> dbg_idx_p, dbg_idx_o;
        const bool dbg = g_dbg_enabled.load(std::memory_order_relaxed) != 0;
        if (dbg) {
            for (uint32_t i = 0; i < p_items->len; ++i)
                if (p_items->data[i].kind == gd::GdVal::Kind::Obj && p_items->data[i].obj)
                    dbg_idx_p.emplace(p_items->data[i].obj, static_cast<int32_t>(i));
            for (uint32_t i = 0; i < o_items->len; ++i)
                if (o_items->data[i].kind == gd::GdVal::Kind::Obj && o_items->data[i].obj)
                    dbg_idx_o.emplace(o_items->data[i].obj, static_cast<int32_t>(i));
        }
''' + source[stop:]
    anchor = "void gd_sim_run_one_replay_v2(\n"
    source = replace_one(source, anchor, '''void gd_sim_run_one_training(
    const PackedSide* player, const PackedSide* opponent,
    const BattleOptions* opts, BattleResult* out
) {
    gd_sim_init();
    run_one_internal(tl_battle_ctx, *player, *opponent, *opts, *out, nullptr, nullptr, nullptr,
                     false, 0.0, nullptr, true);
}

''' + anchor)
    batch_start = source.index("void gd_sim_run_batch(\n")
    batch_end = source.index('}  // extern "C"', batch_start)
    batch = source[batch_start:batch_end]
    batch = replace_one(batch, "void gd_sim_run_batch(\n", "static void run_batch_internal(\n")
    batch = replace_one(batch, "    int32_t n_threads\n", "    int32_t n_threads,\n    bool training_start\n")
    batch = replace_one(batch, "    if (n_threads <= 1 || n_fights == 1) {\n",
                        "    if (n_threads <= 1 || n_fights == 1 || g_dbg_enabled.load(std::memory_order_relaxed)) {\n")
    for ctx in ("tl_battle_ctx", "local_ctx"):
        anchor = f"run_one_internal({ctx}, players[i], opponents[i], opts[i], outs[i]);"
        batch = replace_one(batch, anchor,
                            f"run_one_internal({ctx}, players[i], opponents[i], opts[i], outs[i], "
                            "nullptr, nullptr, nullptr, false, 0.0, nullptr, training_start);")
    for suffix, training in (("", "false"), ("_training", "true")):
        batch += f'''void gd_sim_run_batch{suffix}(
    int32_t n_fights, const PackedSide* players, const PackedSide* opponents,
    const BattleOptions* opts, BattleResult* outs, int32_t n_threads
) {{
    run_batch_internal(n_fights, players, opponents, opts, outs, n_threads, {training});
}}

'''
    return {wrapper: source[:batch_start] + batch + source[batch_end:]}


def stage_binding(native):
    binding = native / "sim.py"
    source = binding.read_text("utf8")
    source = replace_one(source, '''    def __init__(self, lib_path: Path | str = _DEFAULT_LIB_PATH) -> None:
        self.lib = ctypes.CDLL(str(lib_path))
        self._bind_signatures()
        self.data = runtime_data()
''', '''    def __init__(self, lib_path: Path | str = _DEFAULT_LIB_PATH, *, runtime_path: Path | None = None) -> None:
        self.lib = ctypes.CDLL(str(lib_path))
        self._bind_signatures()
        self.data = runtime_data() if runtime_path is None else json.loads(Path(runtime_path).read_bytes())
''')
    anchor = "        lib.gd_sim_run_batch.restype = None\n"
    source = replace_one(source, anchor, anchor + '''        if hasattr(lib, "gd_sim_run_one_training"):
            lib.gd_sim_run_one_training.argtypes = lib.gd_sim_run_one.argtypes
            lib.gd_sim_run_one_training.restype = None
            lib.gd_sim_run_batch_training.argtypes = lib.gd_sim_run_batch.argtypes
            lib.gd_sim_run_batch_training.restype = None
''')
    source = replace_one(source, "    def pack_side(self, side: dict, gem_lens=None, activation_order=None) -> PackedSideHandle:\n",
                         "    def pack_side(self, side: dict, gem_lens=None, activation_order=None, *, strict=False) -> PackedSideHandle:\n")
    anchor = "            pi.item_id = self.item_ids.get(key, -1)\n"
    source = replace_one(source, anchor, anchor + '''            if strict and pi.item_id < 0:
                raise ValueError(f"Unknown item in native training input: {key}")
''')
    anchor = "                    pi.gems[gi] = self.item_ids.get(gk, -1)\n"
    source = replace_one(source, anchor, anchor + '''                    if strict and pi.gems[gi] < 0:
                        raise ValueError(f"Unknown gem in native training input: {gk}")
''')
    anchor = '        initial = opt_kwargs.pop("replay_initial", None)\n'
    source = replace_one(source, anchor, anchor + '        training = opt_kwargs.pop("training", False)\n')
    anchor = "        if initial is None:\n            self.lib.gd_sim_run_one(*arguments)\n"
    source = replace_one(source, anchor, '''        if training:
            if initial is not None:
                raise ValueError("Training initialization and recorded replay are mutually exclusive")
            self.lib.gd_sim_run_one_training(*arguments)
        elif initial is None:
            self.lib.gd_sim_run_one(*arguments)
''')
    anchor = "        n_threads: int = 8,\n"
    source = replace_one(source, anchor, anchor + "        training: bool = False,\n")
    anchor = "        self.lib.gd_sim_run_batch(n, p_arr, o_arr, opt_arr, out_arr, int(n_threads))\n"
    source = replace_one(source, anchor, '''        run = self.lib.gd_sim_run_batch_training if training else self.lib.gd_sim_run_batch
        run(n, p_arr, o_arr, opt_arr, out_arr, int(n_threads))
''')
    return {binding: source}


def main():
    native = SIM / "native_sim_cpp/native_sim"
    changes = stage_wrapper(native) | stage_binding(native)
    for root in (SIM, SIM / "native_sim_cpp"):
        changes.update(stage_core(root))
    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()
