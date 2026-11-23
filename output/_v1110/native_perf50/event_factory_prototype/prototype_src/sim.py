"""ctypes Python interface to the native_sim shared library (libgdcore.dll on Windows, .dylib elsewhere)."""

from __future__ import annotations

import ctypes
import json
import sys
from pathlib import Path
from typing import Any, Dict, List, Optional, Sequence, Tuple

from simulator.gd_core_engine import _place_of, character_stats, class_id_of, runtime_data

_ROOT = Path(__file__).resolve().parent
_DEFAULT_LIB_PATH = _ROOT / ("libgdcore.dll" if sys.platform == "win32" else "libgdcore.dylib")


class PackedEffect(ctypes.Structure):
    _fields_ = [
        ("trigger_type", ctypes.c_int16),
        ("stack_type", ctypes.c_int16),
    ]


class PackedAffectedGroup(ctypes.Structure):
    _fields_ = [
        ("color", ctypes.c_int32),
        ("count", ctypes.c_uint16),
        ("offset", ctypes.c_uint16),
    ]


class PackedItem(ctypes.Structure):
    _fields_ = [
        ("item_id", ctypes.c_int32),
        ("rotation", ctypes.c_int32),
        ("crafted", ctypes.c_int8),
        ("storage", ctypes.c_int8),
        ("charge_frame_x", ctypes.c_int16),
        ("charge_frame_y", ctypes.c_int16),
        ("n_occupied", ctypes.c_uint16),
        ("occupied_off", ctypes.c_uint16),
        ("n_collision", ctypes.c_uint16),
        ("collision_off", ctypes.c_uint16),
        ("n_affected_groups", ctypes.c_uint16),
        ("affected_group_off", ctypes.c_uint16),
        ("n_gems", ctypes.c_uint8),
        ("n_effects", ctypes.c_uint8),
        ("n_sockets", ctypes.c_int16),
        ("n_placement_effects", ctypes.c_uint16),
        ("gems", ctypes.c_int32 * 8),
        ("effects", PackedEffect * 8),
    ]


class PackedSide(ctypes.Structure):
    _fields_ = [
        ("char_class", ctypes.c_int32),
        ("health", ctypes.c_double),
        ("stamina", ctypes.c_double),
        ("base_max_stamina", ctypes.c_double),
        ("regen", ctypes.c_double),
        ("snapshot_stamina", ctypes.c_double),
        ("n_items", ctypes.c_int32),
        ("items", ctypes.POINTER(PackedItem)),
        ("cells_xy", ctypes.POINTER(ctypes.c_int16)),
        ("affected_groups", ctypes.POINTER(PackedAffectedGroup)),
        ("n_activation_order", ctypes.c_int32),
        ("activation_order", ctypes.POINTER(ctypes.c_int32)),
    ]


class PackedFlicker(ctypes.Structure):
    _fields_ = [(name, ctypes.c_double) for name in
               ("position", "speed", "length", "min_dist", "max_dist", "min_speed", "max_speed")] + [
        (name, ctypes.c_int32) for name in ("playing", "attachment", "loop", "n_pending")] + [
        ("pending", ctypes.POINTER(ctypes.c_double))]


class ReplayInitial(ctypes.Structure):
    _fields_ = [
        ("has_activation_state", ctypes.c_int32),
        ("activation_state", ctypes.c_uint64),
        ("player_idle_left", ctypes.c_double),
        ("opponent_idle_left", ctypes.c_double),
        ("n_flickers", ctypes.c_int32),
        ("flickers", ctypes.POINTER(PackedFlicker)),
    ]


class PackedReplayBuff(ctypes.Structure):
    _fields_ = [(name, ctypes.c_int32) for name in ("side", "type", "current", "permanent")]


class ReplayBuffState(ctypes.Structure):
    _fields_ = [("count", ctypes.c_int32), ("rows", ctypes.POINTER(PackedReplayBuff))]


class ReplayEngineRng(ctypes.Structure):
    _fields_ = [("prepare_seed", ctypes.c_int64), ("activate_seed", ctypes.c_int64),
                ("prepare_offset", ctypes.c_int32), ("activate_offset", ctypes.c_int32),
                ("label_mode", ctypes.c_int32)]


class HostRngReplayMismatch(RuntimeError):
    def __init__(self, draw_index, result):
        super().__init__(f"RNG state disagrees at recorded host draw {draw_index}")
        self.draw_index = draw_index
        self.result = result


class ReplayHostDraw(ctypes.Structure):
    _fields_ = [("tick", ctypes.c_int32), ("phase", ctypes.c_int32),
                ("before", ctypes.c_uint64), ("after", ctypes.c_uint64)]


class BattleOptions(ctypes.Structure):
    _fields_ = [
        ("seed", ctypes.c_uint64),
        ("round_id", ctypes.c_int32),
        ("below_master", ctypes.c_int32),
        ("custom_health_multiplier", ctypes.c_double),
        ("label_rng_enabled", ctypes.c_int32),
        ("native_activation_order", ctypes.c_int32),
        ("reseed_after_player_character", ctypes.c_int32),
        ("formal_ev_gate", ctypes.c_int32),
        ("max_ticks", ctypes.c_int32),
        ("max_time", ctypes.c_double),
        ("record_per_item", ctypes.c_int32),
        ("rng_state", ctypes.c_uint64),
        ("has_rng_state", ctypes.c_int32),
    ]


class BattleResult(ctypes.Structure):
    _fields_ = [
        ("player_wins", ctypes.c_int32),
        ("timed_out", ctypes.c_int32),
        ("formal_ev_capped", ctypes.c_int32),
        ("combat_time", ctypes.c_double),
        ("ticks", ctypes.c_int32),
        ("fatigue_counter", ctypes.c_int32),
        ("player_hp", ctypes.c_double),
        ("player_max_hp", ctypes.c_double),
        ("player_block", ctypes.c_double),
        ("opponent_hp", ctypes.c_double),
        ("opponent_max_hp", ctypes.c_double),
        ("opponent_block", ctypes.c_double),
        ("out_of_stamina_count", ctypes.c_int32),
        ("event_count", ctypes.c_int32),
        ("player_damage_dealt", ctypes.c_double),
        ("opponent_damage_dealt", ctypes.c_double),
        ("player_healing_done", ctypes.c_double),
        ("opponent_healing_done", ctypes.c_double),
        ("player_crits", ctypes.c_int32),
        ("opponent_crits", ctypes.c_int32),
        ("player_misses", ctypes.c_int32),
        ("opponent_misses", ctypes.c_int32),
        ("n_placed_items", ctypes.c_int32),
        ("item_activations", ctypes.c_int32 * 64),
    ]


class PackedSideHandle:
    """Owns ctypes backing arrays for one PackedSide so it can be reused across batches."""

    def __init__(
        self,
        side: PackedSide,
        items_buf: Any,
        cells_buf: Any,
        aff_buf: Any,
        ao_buf: Any = None,
        round_id: int = 1,
    ) -> None:
        self.side = side
        self._items_buf = items_buf
        self._cells_buf = cells_buf
        self._aff_buf = aff_buf
        self._ao_buf = ao_buf
        self.round_id = round_id


def _encode_recipes(recipes: Sequence[dict]) -> bytes:
    if not recipes:
        return b""
    lines: List[str] = []
    for r in recipes:
        base = str(r.get("b", ""))
        ings = "|".join(str(x) for x in (r.get("i") or []))
        cons = "|".join("1" if x else "0" for x in (r.get("c") or []))
        lines.append(f"{base}\t{ings}\t{cons}")
    return "\n".join(lines).encode("utf-8")


def _extract_placed_entries(lineup: dict, data: dict) -> List[dict]:
    """Flatten nested v3/v4 lineup or pass-through pre-flattened items into placement dicts."""
    if "items" in lineup and isinstance(lineup["items"], list):
        raw_items = lineup["items"]
        if not raw_items or "occupied" in raw_items[0]:
            return raw_items

    out: List[dict] = []

    def walk(nodes: Sequence[dict]) -> None:
        for node in nodes:
            if not isinstance(node, dict):
                continue
            key = node.get("id") or node.get("key") or ""
            if key and not node.get("storage"):
                row = int(node.get("row", node["at"][0] if "at" in node else 0))
                col = int(node.get("col", node["at"][1] if "at" in node else 0))
                rot = int(node.get("rotation", node.get("r", 0)) or 0) % 360
                pl = _place_of(data, key, row, col, rot)
                item_entry = {
                    "key": key,
                    "occupied": pl["occupied"],
                    "collision": pl["collision"],
                    "affected": pl["affected"],
                    "rotation": rot,
                    "gems": list(node.get("gems") or []),
                    "effects": node.get("effects"),
                    "placement_effects": node.get("placement_effects"),
                    "crafted": node.get("crafted"),
                    "storage": bool(node.get("storage", False)),
                    "charge_frame": pl.get("charge_frame", (0, 0)),
                }
                out.append(item_entry)
            contents = node.get("contents")
            if contents:
                walk(contents)

    bp_items = (lineup.get("backpack") or {}).get("items")
    if bp_items is not None:
        walk(bp_items)
    elif "items" in lineup:
        walk(lineup["items"])
    return out


class NativeSimulator:
    def __init__(self, lib_path: Path | str = _DEFAULT_LIB_PATH, *, runtime_path: Path | None = None) -> None:
        self.lib = ctypes.CDLL(str(lib_path))
        self._bind_signatures()
        self.data = runtime_data() if runtime_path is None else json.loads(Path(runtime_path).read_bytes())
        self.item_ids: Dict[str, int] = {}
        self.lib.gd_sim_init()
        self._register_runtime()

    def _bind_signatures(self) -> None:
        lib = self.lib
        lib.gd_sim_init.argtypes = []
        lib.gd_sim_init.restype = None
        lib.gd_sim_reset_registry.argtypes = []
        lib.gd_sim_reset_registry.restype = None

        lib.gd_sim_register_character.argtypes = [
            ctypes.c_int32,
            ctypes.c_char_p,
            ctypes.c_double,
            ctypes.c_double,
            ctypes.c_double,
            ctypes.c_int32,
        ]
        lib.gd_sim_register_character.restype = None

        lib.gd_sim_register_item.argtypes = [
            ctypes.c_char_p,  # key
            ctypes.c_char_p,  # script_path
            ctypes.c_int32,   # sockets
            ctypes.c_char_p,  # name
            ctypes.c_char_p,  # identifier
            ctypes.c_int32,   # minDam
            ctypes.c_int32,   # maxDam
            ctypes.c_double,  # staminaCost
            ctypes.c_int32,   # block
            ctypes.c_double,  # cd
            ctypes.c_double,  # accuracy
            ctypes.c_int32,   # canActivate
            ctypes.c_double,  # chance
            ctypes.c_double,  # chance2
            ctypes.c_double,  # shopChance
            ctypes.c_int64,   # tags
            ctypes.c_int64,   # physics
            ctypes.c_int32,   # rarity
            ctypes.c_int32,   # price
            ctypes.c_int64,   # classes
            ctypes.c_int32,   # randomUniquePool
            ctypes.c_int32,   # hasBattleRageEffect
            ctypes.c_char_p,  # startsSubclass
            ctypes.c_char_p,  # gateItem
            ctypes.c_int32,   # animationScene
            ctypes.c_int32,   # flickerAni
            ctypes.c_double,  # flickerMinDist
            ctypes.c_double,  # flickerMaxDist
            ctypes.c_double,  # flickerMinSpeed
            ctypes.c_double,  # flickerMaxSpeed
            ctypes.c_int32,   # connectorReadyRoll
            ctypes.c_int32,   # gemRoll
            ctypes.c_int32,   # sceneDepth
            ctypes.c_int32,   # releaseState
            ctypes.c_int64,   # gainedStacks
            ctypes.c_int64,   # removedStacks
            ctypes.c_int64,   # usedStacks
            ctypes.POINTER(ctypes.c_double),  # params
            ctypes.c_int32,                   # n_params
            ctypes.POINTER(ctypes.c_double),  # extraCds
            ctypes.c_int32,                   # n_extraCds
            ctypes.POINTER(ctypes.c_int64),   # types
            ctypes.c_int32,                   # n_types
            ctypes.POINTER(ctypes.c_char_p),  # np_keys
            ctypes.POINTER(ctypes.c_double),  # np_vals
            ctypes.c_int32,                   # n_np
            ctypes.c_char_p,                  # recipes_encoded
        ]
        lib.gd_sim_register_item.restype = ctypes.c_int32

        lib.gd_sim_run_one.argtypes = [
            ctypes.POINTER(PackedSide),
            ctypes.POINTER(PackedSide),
            ctypes.POINTER(BattleOptions),
            ctypes.POINTER(BattleResult),
        ]
        lib.gd_sim_run_one.restype = None
        if hasattr(lib, "gd_sim_run_one_replay_v2"):
            lib.gd_sim_run_one_replay_v2.argtypes = lib.gd_sim_run_one.argtypes + [ctypes.POINTER(ReplayInitial)]
            lib.gd_sim_run_one_replay_v2.restype = None
        if hasattr(lib, "gd_sim_run_one_replay_buff_state"):
            lib.gd_sim_run_one_replay_buff_state.argtypes = lib.gd_sim_run_one_replay_v2.argtypes + [ctypes.POINTER(ReplayBuffState)]
            lib.gd_sim_run_one_replay_buff_state.restype = None
        if hasattr(lib, "gd_sim_run_one_replay_engine_rng"):
            lib.gd_sim_run_one_replay_engine_rng.argtypes = lib.gd_sim_run_one_replay_buff_state.argtypes + [ctypes.POINTER(ReplayEngineRng)]
            lib.gd_sim_run_one_replay_engine_rng.restype = None
        if hasattr(lib, "gd_sim_run_one_replay_scene_delays"):
            lib.gd_sim_run_one_replay_scene_delays.argtypes = lib.gd_sim_run_one_replay_engine_rng.argtypes
            lib.gd_sim_run_one_replay_scene_delays.restype = None
        if hasattr(lib, "gd_sim_run_one_replay_native_clock"):
            lib.gd_sim_run_one_replay_native_clock.argtypes = lib.gd_sim_run_one_replay_engine_rng.argtypes + [ctypes.c_int32, ctypes.c_double]
            lib.gd_sim_run_one_replay_native_clock.restype = None
        if hasattr(lib, "gd_sim_run_one_replay_host_phases"):
            lib.gd_sim_run_one_replay_host_phases.argtypes = lib.gd_sim_run_one_replay_native_clock.argtypes + [
                ctypes.POINTER(ReplayHostDraw), ctypes.c_int32]
            lib.gd_sim_run_one_replay_host_phases.restype = ctypes.c_int32

        lib.gd_sim_run_batch.argtypes = [
            ctypes.c_int32,
            ctypes.POINTER(PackedSide),
            ctypes.POINTER(PackedSide),
            ctypes.POINTER(BattleOptions),
            ctypes.POINTER(BattleResult),
            ctypes.c_int32,
        ]
        lib.gd_sim_run_batch.restype = None
        if hasattr(lib, "gd_sim_run_one_training"):
            lib.gd_sim_run_one_training.argtypes = lib.gd_sim_run_one.argtypes
            lib.gd_sim_run_one_training.restype = None
            lib.gd_sim_run_batch_training.argtypes = lib.gd_sim_run_batch.argtypes
            lib.gd_sim_run_batch_training.restype = None

    def _register_runtime(self) -> None:
        self.lib.gd_sim_reset_registry()
        classes = self.data["classes"]
        for ckey, cinfo in self.data["characters"].items():
            if ckey not in classes:
                continue
            cid = int(classes[ckey])
            self.lib.gd_sim_register_character(
                cid,
                ckey.encode("utf-8"),
                float(cinfo.get("health", 25.0)),
                float(cinfo.get("stamina", 5.0)),
                float(cinfo.get("regen", 1.0)),
                int(cinfo.get("gold", 13)),
            )

        for key, item_info in self.data["items"].items():
            ds = item_info["descr"]
            params = [float(x) for x in (ds.get("params") or [])]
            extra_cds = [float(x) for x in (ds.get("extraCds") or [])]
            types = [int(x) for x in (ds.get("types") or [])]
            np_dict = ds.get("namedParams") or {}
            np_items = list(np_dict.items())

            params_buf = (ctypes.c_double * max(1, len(params)))(*params) if params else None
            ecd_buf = (ctypes.c_double * max(1, len(extra_cds)))(*extra_cds) if extra_cds else None
            types_buf = (ctypes.c_int64 * max(1, len(types)))(*types) if types else None
            if np_items:
                np_keys_buf = (ctypes.c_char_p * len(np_items))(
                    *[str(k).encode("utf-8") for k, _ in np_items]
                )
                np_vals_buf = (ctypes.c_double * len(np_items))(
                    *[float(v) for _, v in np_items]
                )
            else:
                np_keys_buf = None
                np_vals_buf = None

            item_id = self.lib.gd_sim_register_item(
                key.encode("utf-8"),
                str(item_info.get("script") or "res://gd_core_items/Item.gd").encode("utf-8"),
                int(item_info.get("sockets", ds.get("sockets", 0))),
                str(ds.get("name", key)).encode("utf-8"),
                str(ds.get("identifier", key)).encode("utf-8"),
                int(ds.get("minDam", 0)),
                int(ds.get("maxDam", 0)),
                float(ds.get("staminaCost", 0.0)),
                int(ds.get("block", 0)),
                float(ds.get("cd", 0.0)),
                float(ds.get("accuracy", 100.0)),
                1 if ds.get("canActivate", True) else 0,
                float(ds.get("chance", 0.0)),
                float(ds.get("chance2", 0.0)),
                float(ds.get("shopChance", 0.0)),
                int(ds.get("tags", 0)),
                int(ds.get("physics", 0)),
                int(ds.get("rarity", 0)),
                int(ds.get("price", 0)),
                int(ds.get("classes", 0)),
                1 if ds.get("randomUniquePool", False) else 0,
                1 if ds.get("hasBattleRageEffect", False) else 0,
                str(ds.get("startsSubclass", "")).encode("utf-8"),
                (str(ds["gateItem"]).encode("utf-8") if ds.get("gateItem") else b""),
                1 if ds.get("animationScene", False) else 0,
                1 if ds.get("flickerAni", False) else 0,
                float(ds.get("flickerMinDist", 0.1)),
                float(ds.get("flickerMaxDist", 3.0)),
                float(ds.get("flickerMinSpeed", 0.3)),
                float(ds.get("flickerMaxSpeed", 1.0)),
                1 if ds.get("connectorReadyRoll", False) else 0,
                1 if ds.get("gemRoll", False) else 0,
                int(ds.get("sceneDepth", 2)),
                int(ds.get("releaseState", 1)),
                int(ds.get("gainedStacks", 0)),
                int(ds.get("removedStacks", 0)),
                int(ds.get("usedStacks", 0)),
                params_buf,
                len(params),
                ecd_buf,
                len(extra_cds),
                types_buf,
                len(types),
                np_keys_buf,
                np_vals_buf,
                len(np_items),
                _encode_recipes(ds.get("originatingRecipes") or []),
            )
            self.item_ids[key] = int(item_id)

    def _charge_frame_of(self, key: str, rotation: int) -> Tuple[int, int]:
        """np25 P3-3：chargeFrame 取运行时数据按 rotation 的真值。

        主仓引擎 _build_side 恒用 _place_of 的 charge_frame
        （simulator/gd_core_engine.py:1434 `it.chargeFrame = [vec(cf)]*4`），
        夹具条目自身的 charge_frame 不参与。电荷路径（Battery.chargeCells 等
        本地格经 _chargeInventoryCells 映射）按 fd 下标取修正项——
        取 (0,0) 会让旋转后的电荷落点整体偏移，接错物品
        （run1160_r18 首分歧根因：py id4 Resistor heat vs native Battery）。"""
        ent = self.data["items"].get(key)
        if ent:
            r = (ent.get("rot") or {}).get(str(int(rotation) % 360))
            if r:
                cf = r.get("charge_frame")
                if cf:
                    return (int(cf[0]), int(cf[1]))
        return (0, 0)

    def pack_side(self, side: dict, gem_lens=None, activation_order=None, *, strict=False) -> PackedSideHandle:
        """Pack either an oracle_align case side dict or a v3/v4 lineup dict."""
        if "class" in side:
            char_class = int(side["class"])
            health = float(side["health"])
            stamina = float(side["stamina"])
            base_max_stamina = float(side.get("base_max_stamina", stamina))
            regen = float(side["regen"])
            snap_stam = float(side.get("snapshot_stamina", -1.0) or -1.0)
            round_id = int(side.get("round_id", 1))
        else:
            char_class = class_id_of(side, self.data["classes"])
            stats = character_stats(side, self.data["characters"])
            health = float(stats["health"])
            stamina = float(stats["stamina"])
            base_max_stamina = float(side.get("base_max_stamina", stamina))
            regen = float(stats["regen"])
            # ★ B 阶段修复（2026-11-14）：神谕对齐路径的体力/血量/回复夹具真值直通
            #   （镜像 py 引擎 p_stats/o_stats，simulator/gd_core_engine.py:1010-1016
            #   2026-11-09 修的同一缺口——夹具 stamina 取 history.db roundData
            #   （= base + Stamina Sack 等），character_stats 只取 class_modifiers
            #   base，不同源时长局先撞 OutofStamina，事件流分叉；run704991/
            #   run704752/run300225 等 native 侧 type15 分歧即此）。键缺省 = 保持
            #   原行为（闸1 的 GDCoreEngine 默认路径零影响）。
            if side.get("stamina") is not None:
                stamina = float(side["stamina"])
            if side.get("health") is not None:
                health = float(side["health"])
            if side.get("regen") is not None:
                regen = float(side["regen"])
            snap_stam = float(side["snapshot_stamina"]) if side.get("snapshot_stamina") is not None else -1.0
            round_id = int(side.get("round", 1))

        entries = _extract_placed_entries(side, self.data)
        n_items = len(entries)
        items_buf = (PackedItem * max(1, n_items))()

        xy_flat: List[int] = []
        aff_groups: List[Tuple[int, int, int]] = []

        for idx, it in enumerate(entries):
            pi = items_buf[idx]
            key = it.get("key") or it.get("id") or ""
            pi.item_id = self.item_ids.get(key, -1)
            if strict and pi.item_id < 0:
                raise ValueError(f"Unknown item in native training input: {key}")
            pi.rotation = int(it.get("rotation", it.get("r", 0)) or 0) % 360
            cr = it.get("crafted")
            pi.crafted = -1 if cr is None else (1 if cr else 0)
            pi.storage = 1 if it.get("storage") else 0
            # chargeFrame 恒取运行时真值（同主仓引擎 _build_side 口径），
            # 不读条目自身 charge_frame——见 _charge_frame_of 注释
            cf = self._charge_frame_of(key, int(it.get("rotation", it.get("r", 0)) or 0))
            pi.charge_frame_x = int(cf[0])
            pi.charge_frame_y = int(cf[1])

            occ = it.get("occupied") or []
            pi.occupied_off = len(xy_flat) // 2
            pi.n_occupied = len(occ)
            for c in occ:
                xy_flat.append(int(c[0]))
                xy_flat.append(int(c[1]))

            col = it.get("collision") or []
            pi.collision_off = len(xy_flat) // 2
            pi.n_collision = len(col)
            for c in col:
                xy_flat.append(int(c[0]))
                xy_flat.append(int(c[1]))

            aff = it.get("affected") or {}
            if key in {'Acorn Collar', 'Magic Collar', 'Holy Collar', 'Vampiric Collar'} and occ and 8 not in aff and "8" not in aff:
                geometry = self.data["items"].get(key, {}).get("rot", {}).get(str(pi.rotation), {})
                extended = geometry.get("affected", {}).get("8")
                if extended:
                    left = min(int(c[0]) for c in occ)
                    top = min(int(c[1]) for c in occ)
                    aff = {**aff, 8: [(x + left, y + top) for x, y in extended]}
            pi.affected_group_off = len(aff_groups)
            pi.n_affected_groups = len(aff)
            for col_k, cells in aff.items():
                off = len(xy_flat) // 2
                aff_groups.append((int(col_k), len(cells), off))
                for c in cells:
                    xy_flat.append(int(c[0]))
                    xy_flat.append(int(c[1]))

            _gl = gem_lens[idx] if (gem_lens is not None and idx < len(gem_lens)) else None
            pi.n_sockets = -1 if _gl is None else int(_gl)
            gems = it.get("gems") or []
            pi.n_gems = min(8, len(gems))
            for gi in range(8):
                if gi < pi.n_gems and gems[gi] is not None:
                    g = gems[gi]
                    gk = g if isinstance(g, str) else (g.get("key") or g.get("id") or "")
                    pi.gems[gi] = self.item_ids.get(gk, -1)
                    if strict and pi.gems[gi] < 0:
                        raise ValueError(f"Unknown gem in native training input: {gk}")
                else:
                    pi.gems[gi] = -1

            effs = it.get("effects") or []
            pi.n_effects = min(8, len(effs))
            placement = it.get("placement_effects")
            if placement:
                if len(placement) != len(effs) or len(effs) + len(placement) > 8:
                    raise ValueError(f"Invalid placement effects for {it['key']}")
                pi.n_placement_effects = len(placement)
                effs = [*effs, *placement]
            for index in range(pi.n_effects + pi.n_placement_effects):
                effect = effs[index]
                pi.effects[index].trigger_type = int(effect["triggerType"])
                pi.effects[index].stack_type = int(effect["stackType"])

        if activation_order:
            ao_buf = (ctypes.c_int32 * len(activation_order))(*[int(x) for x in activation_order])
        else:
            ao_buf = (ctypes.c_int32 * 1)(0)
        cells_buf = (ctypes.c_int16 * max(1, len(xy_flat)))(*xy_flat) if xy_flat else (ctypes.c_int16 * 1)(0)
        aff_buf = (PackedAffectedGroup * max(1, len(aff_groups)))()
        for ai, (col_k, cnt, off) in enumerate(aff_groups):
            aff_buf[ai].color = col_k
            aff_buf[ai].count = cnt
            aff_buf[ai].offset = off

        ps = PackedSide(
            char_class=char_class,
            health=health,
            stamina=stamina,
            base_max_stamina=base_max_stamina,
            regen=regen,
            snapshot_stamina=snap_stam,
            n_items=n_items,
            items=items_buf,
            cells_xy=cells_buf,
            affected_groups=aff_buf,
            n_activation_order=len(activation_order) if activation_order else 0,
            activation_order=ao_buf,
        )
        return PackedSideHandle(ps, items_buf, cells_buf, aff_buf, ao_buf, round_id=round_id)

    def make_options(
        self,
        *,
        seed: int = 1,
        round_id: int = 1,
        below_master: bool = False,
        custom_health_multiplier: float = 100.0,
        label_rng_enabled: bool = True,
        native_activation_order: bool = True,
        reseed_after_player_character: bool = True,
        formal_ev_gate: int = 25000,
        max_ticks: int = 20000,
        max_time: float = 0.0,
        record_per_item: bool = False,
        rng_state=None,
    ) -> BattleOptions:
        return BattleOptions(
            seed=int(seed) & 0xFFFFFFFFFFFFFFFF,
            round_id=int(round_id),
            below_master=1 if below_master else 0,
            custom_health_multiplier=float(custom_health_multiplier),
            label_rng_enabled=1 if label_rng_enabled else 0,
            native_activation_order=1 if native_activation_order else 0,
            reseed_after_player_character=1 if reseed_after_player_character else 0,
            formal_ev_gate=int(formal_ev_gate),
            max_ticks=int(max_ticks),
            max_time=float(max_time),
            record_per_item=1 if record_per_item else 0,
            rng_state=(int(rng_state) & 0xFFFFFFFFFFFFFFFF) if rng_state is not None else 0,
            has_rng_state=1 if rng_state is not None else 0,
        )

    def run_one(
        self,
        player: dict | PackedSideHandle,
        opponent: dict | PackedSideHandle,
        **opt_kwargs: Any,
    ) -> BattleResult:
        ph = player if isinstance(player, PackedSideHandle) else self.pack_side(player)
        oh = opponent if isinstance(opponent, PackedSideHandle) else self.pack_side(opponent)
        if "round_id" not in opt_kwargs:
            opt_kwargs["round_id"] = ph.round_id
        initial = opt_kwargs.pop("replay_initial", None)
        training = opt_kwargs.pop("training", False)
        opts = self.make_options(**opt_kwargs)
        res = BattleResult()
        arguments = [ctypes.byref(ph.side), ctypes.byref(oh.side), ctypes.byref(opts), ctypes.byref(res)]
        if training:
            if initial is not None:
                raise ValueError("Training initialization and recorded replay are mutually exclusive")
            self.lib.gd_sim_run_one_training(*arguments)
        elif initial is None:
            self.lib.gd_sim_run_one(*arguments)
        else:
            if not hasattr(self.lib, "gd_sim_run_one_replay_v2"):
                raise RuntimeError("This DLL does not support the observed initial replay context")
            idle = initial["idle_left"]
            if len(idle) != 2:
                raise ValueError("idle_left must contain player and opponent timer values")
            state = initial.get("activation_rng_state")
            flickers = initial.get("flickers")
            native_scene_delays = initial.get("native_scene_delays", False)
            packed = (PackedFlicker * len(flickers))() if flickers is not None else None
            pending_arrays = []
            for i, flicker in enumerate(flickers or []):
                calls = flicker["pending"]
                if any(call["method"] != "playAni" for call in calls):
                    raise ValueError("Unsupported initial flicker callback")
                fields = ("left", "order", "left_at_first_physics") if native_scene_delays else ("left",)
                pending = (ctypes.c_double * (len(calls) * len(fields)))(
                    *(float(call[key]) for call in calls for key in fields))
                pending_arrays.append(pending)
                attachment = 2 if flicker.get("native_opponent") else int(flicker["inside_tree"])
                packed[i] = PackedFlicker(float(flicker.get("position_precise", flicker["position"])),
                                          float(flicker.get("speed_precise", flicker["speed"])),
                                          float(flicker["length"]), *map(float, flicker["limits"]),
                                          int(flicker["playing"]), attachment, int(flicker["loop"]),
                                          len(calls), pending)
            replay = ReplayInitial(int(state is not None), int(state or 0) & 0xFFFFFFFFFFFFFFFF,
                                   float(idle[0]), float(idle[1]),
                                   len(flickers) if flickers is not None else -1, packed)
            observed_buffs = initial.get("buff_state")
            buffs = None
            if observed_buffs is not None:
                if not hasattr(self.lib, "gd_sim_run_one_replay_buff_state"):
                    raise RuntimeError("This DLL does not support observed permanent stacks")
                if len(observed_buffs) != 2:
                    raise ValueError("buff_state must have two sides")
                rows = []
                for side, observed in enumerate(observed_buffs):
                    for type_id, current, permanent, temporary_count in observed:
                        if int(temporary_count) != 0:
                            raise ValueError("Replay does not import active temporary stacks")
                        rows.append(PackedReplayBuff(side, int(type_id), int(current), int(permanent)))
                packed_buffs = (PackedReplayBuff * len(rows))(*rows)
                buffs = ReplayBuffState(len(rows), packed_buffs)
            observed_engine = initial.get("engine_rng")
            engine = None
            if observed_engine is not None:
                if not hasattr(self.lib, "gd_sim_run_one_replay_engine_rng"):
                    raise RuntimeError("This DLL does not support observed global RNG state")
                prepare_seed, prepare_offset, activate_seed, activate_offset, label_mode = map(int, observed_engine)
                if not (0 <= prepare_offset < 8192 and 0 <= activate_offset < 8192 and 0 <= label_mode <= 3):
                    raise ValueError("Invalid replay RNG offset or damage-number mode")
                engine = ReplayEngineRng(prepare_seed, activate_seed, prepare_offset, activate_offset, label_mode)
            buff_arg = ctypes.byref(buffs) if buffs is not None else None
            util_time = initial.get("util_time")
            host_draws = initial.get("host_rng_draws")
            if host_draws:
                if not hasattr(self.lib, "gd_sim_run_one_replay_host_phases"):
                    raise RuntimeError("This DLL does not support observed host draws")
                if util_time is None:
                    raise ValueError("Observed host draws require the original process clock")
                engine_arg = ctypes.byref(engine) if engine is not None else None
                rows = [ReplayHostDraw(int(tick), int(phase), int(before), int(after))
                        for tick, phase, before, after in host_draws]
                packed_draws = (ReplayHostDraw * len(rows))(*rows)
                status = self.lib.gd_sim_run_one_replay_host_phases(
                    *arguments, ctypes.byref(replay), buff_arg, engine_arg, int(native_scene_delays),
                    float(util_time), packed_draws, len(rows))
                if status == -1:
                    raise ValueError("Invalid host draw schedule")
                if status:
                    raise HostRngReplayMismatch(-status - 1, res)
            elif util_time is not None:
                if not hasattr(self.lib, "gd_sim_run_one_replay_native_clock"):
                    raise RuntimeError("This DLL does not support the original Util clock")
                engine_arg = ctypes.byref(engine) if engine is not None else None
                self.lib.gd_sim_run_one_replay_native_clock(
                    *arguments, ctypes.byref(replay), buff_arg, engine_arg, int(native_scene_delays), float(util_time))
            elif native_scene_delays:
                if not hasattr(self.lib, "gd_sim_run_one_replay_scene_delays"):
                    raise RuntimeError("This DLL does not support observed SceneTreeTimer delays")
                engine_arg = ctypes.byref(engine) if engine is not None else None
                self.lib.gd_sim_run_one_replay_scene_delays(*arguments, ctypes.byref(replay), buff_arg, engine_arg)
            elif engine is not None:
                self.lib.gd_sim_run_one_replay_engine_rng(*arguments, ctypes.byref(replay), buff_arg, ctypes.byref(engine))
            elif buffs is not None:
                self.lib.gd_sim_run_one_replay_buff_state(*arguments, ctypes.byref(replay), ctypes.byref(buffs))
            else:
                self.lib.gd_sim_run_one_replay_v2(*arguments, ctypes.byref(replay))
        return res

    def run_batch(
        self,
        pairs: Sequence[Tuple[dict | PackedSideHandle, dict | PackedSideHandle, BattleOptions]],
        *,
        n_threads: int = 8,
        training: bool = False,
    ) -> List[BattleResult]:
        n = len(pairs)
        if n == 0:
            return []
        handles = []
        p_arr = (PackedSide * n)()
        o_arr = (PackedSide * n)()
        opt_arr = (BattleOptions * n)()
        out_arr = (BattleResult * n)()
        for i, (ps, os, opt) in enumerate(pairs):
            ph = ps if isinstance(ps, PackedSideHandle) else self.pack_side(ps)
            oh = os if isinstance(os, PackedSideHandle) else self.pack_side(os)
            handles.append((ph, oh))
            p_arr[i] = ph.side
            o_arr[i] = oh.side
            opt_arr[i] = opt
        run = self.lib.gd_sim_run_batch_training if training else self.lib.gd_sim_run_batch
        run(n, p_arr, o_arr, opt_arr, out_arr, int(n_threads))
        return list(out_arr)


_DEFAULT_SIM: Optional[NativeSimulator] = None


def get_simulator() -> NativeSimulator:
    global _DEFAULT_SIM
    if _DEFAULT_SIM is None:
        _DEFAULT_SIM = NativeSimulator()
    return _DEFAULT_SIM
