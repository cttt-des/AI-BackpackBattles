"""BitStream 解码器（Godot 3.x 背包乱斗 run/摆盘格式）。

对应 decompiled_full/Utility/BitStream.gd 与 Utility/RunData.gd 的 deserializeStream。
"""
import json, math, os
from pathlib import Path

BASE = Path(__file__).resolve().parents[4]
MAP_PATH = os.environ.get("BPB_ITEM_MAP") or (BASE / "assets" / "item_index_map.json")

BASE64OFFSET = 62
MAX_HEALTH = 999
MAX_STAMINA = 999
GRID_X = 10
GRID_Y = 10
FACE_BITS = 4


def bits_ceil(n: int) -> int:
    return int(math.ceil(math.log2(n))) if n > 1 else 1


class BitStream:
    def __init__(self, data: str):
        self.bits = []
        for ch in data:
            b = ord(ch) - BASE64OFFSET
            if b < 0 or b > 63:
                raise ValueError(f"非法字符 {ch!r}")
            for shift in range(5, -1, -1):
                self.bits.append((b >> shift) & 1)
        self.pos = 0

    def bits_left(self) -> int:
        return len(self.bits) - self.pos

    def pull(self, range_max: int) -> int:
        nbits = bits_ceil(range_max)
        value = 0
        for shift in range(nbits - 1, -1, -1):
            if self.pos >= len(self.bits):
                return -1
            value += self.bits[self.pos] << shift
            self.pos += 1
        return value


class ItemMap:
    def __init__(self, path: Path = MAP_PATH):
        raw = json.loads(path.read_text(encoding="utf-8"))
        self.total_items = int(raw["total_items"])
        self.index_to_name = {int(k): v for k, v in raw["index_to_name"].items()}
        self.gem_order = list(raw["gem_order"])
        self.total_num_gems = int(raw["total_num_gems_ceil"])
        self.empty_socket_id = int(raw["empty_socket_id"])
        self.num_sockets = dict(raw["num_sockets"]) if isinstance(raw["num_sockets"], dict) else {}

    def name(self, idx: int) -> str:
        return self.index_to_name.get(idx, f"<{idx}>")

    def sockets(self, name: str) -> int:
        return int(self.num_sockets.get(name, 0) or 0)


def decode_round(metadata: str, imap: ItemMap, version_new: bool = True):
    """解出一轮的 health/stamina/物品列表。"""
    bs = BitStream(metadata)
    health = bs.pull(MAX_HEALTH)
    if health == -1:
        return None
    stamina = bs.pull(MAX_STAMINA)
    if stamina == -1:
        return None
    total_items = imap.total_items if version_new else 510
    items = []
    while bs.bits_left() >= 8:
        idx = bs.pull(total_items)
        if idx == -1 or idx >= total_items:
            break
        name = imap.name(idx)
        x = bs.pull(GRID_X)
        y = bs.pull(GRID_Y)
        face = bs.pull(FACE_BITS)
        if x < 0 or y < 0 or face < 0:
            break
        gems = []
        if imap.sockets(name) > 0:
            has_gems = bs.pull(2)
            if has_gems == 1:
                for _ in range(imap.sockets(name)):
                    g = bs.pull(imap.total_num_gems)
                    if g < 0:
                        break
                    gems.append(("" if g == imap.empty_socket_id else (imap.gem_order[g] if g < len(imap.gem_order) else f"<gem{g}>")))
        items.append({"id": name, "gid": idx, "x": x, "y": y, "face": face, "gems": gems})
    return {"health": health, "stamina": stamina, "items": items}


def decode_run(metadata_json: str, imap: ItemMap | None = None):
    """解一场 run：{"0": "<bitstream>", ..., "17": ...}。"""
    imap = imap or ItemMap()
    data = json.loads(metadata_json) if isinstance(metadata_json, str) else metadata_json
    rounds = []
    for key in [str(i) for i in range(18)]:
        if key not in data:
            break
        try:
            rounds.append(decode_round(data[key], imap))
        except Exception as e:
            rounds.append({"error": str(e)})
    return rounds
