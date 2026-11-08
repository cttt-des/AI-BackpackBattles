"""解析 Godot 3.x Variant 二进制（store_var 格式）— 提取 runs_steam.cache。

格式：magic(4B) | 顶层类型(u32) | 数据...
类型表（Godot 3.x Variant::Type）：
 1 NIL, 2 BOOL, 3 INT, 4 REAL, 5 STRING, 6 VECTOR2, 7 RECT2, 8 VECTOR3, 9 TRANSFORM2D,
 10 PLANE, 11 QUAT, 12 AABB, 13 BASIS, 14 TRANSFORM, 15 COLOR, 16 NODE_PATH, 17 _RID,
 18 OBJECT, 19 DICTIONARY, 20 ARRAY, 21 POOL_BYTE_ARRAY, 22 POOL_INT_ARRAY,
 23 POOL_REAL_ARRAY, 24 POOL_STRING_ARRAY, 25 POOL_VECTOR2_ARRAY 等
"""
import json
import struct
import sys


class Reader:
    def __init__(self, data: bytes):
        self.data = data
        self.pos = 0

    def u32(self) -> int:
        v = struct.unpack_from("<I", self.data, self.pos)[0]
        self.pos += 4
        return v

    def u64(self) -> int:
        v = struct.unpack_from("<Q", self.data, self.pos)[0]
        self.pos += 8
        return v

    def i32(self) -> int:
        v = struct.unpack_from("<i", self.data, self.pos)[0]
        self.pos += 4
        return v

    def raw(self, n: int) -> bytes:
        b = self.data[self.pos:self.pos + n]
        self.pos += n
        return b

    def string(self) -> str:
        n = self.u32()
        return self.raw(n).decode("utf-8", "replace")


def parse_variant(r: Reader, depth: int = 0):
    if depth > 6:
        raise ValueError("嵌套过深")
    t = r.u32()
    if t == 1:
        return None
    if t == 2:
        return bool(r.u32())
    if t == 3:
        return r.i32()
    if t == 4:
        return struct.unpack_from("<f", r.data, r.pos)[0] if not r.pos else struct.unpack("<f", r.raw(4))[0]
    if t == 5:
        return r.string()
    if t == 19:  # Dictionary
        count = r.u32()
        out = {}
        for _ in range(count):
            k = parse_variant(r, depth + 1)
            v = parse_variant(r, depth + 1)
            out[str(k)] = v
        return out
    if t == 20:  # Array
        count = r.u32()
        return [parse_variant(r, depth + 1) for _ in range(count)]
    if t == 21:  # PoolByteArray
        n = r.u32()
        return list(r.raw(n))
    if t == 22:  # PoolIntArray
        n = r.u32()
        return list(struct.unpack_from("<" + "i" * n, r.data, r.pos)), r.__setattr__("pos", r.pos + 4 * n)
    if t == 23:  # PoolRealArray
        n = r.u32()
        vals = list(struct.unpack_from("<" + "f" * n, r.data, r.pos))
        r.pos += 4 * n
        return vals
    if t == 24:  # PoolStringArray
        n = r.u32()
        return [r.string() for _ in range(n)]
    raise ValueError(f"未支持类型 {t} (pos={r.pos})")


def parse_file(path: str):
    data = open(path, "rb").read()
    r = Reader(data)
    magic = r.raw(4)
    try:
        value = parse_variant(r)
    except Exception as e:
        return {"magic": magic.hex(), "error": str(e), "pos": r.pos, "size": len(data)}
    return {"magic": magic.hex(), "entries": len(value) if hasattr(value, "__len__") else None,
            "type": type(value).__name__, "sample": value[:2] if isinstance(value, list) else None,
            "consumed": r.pos, "size": len(data)}


if __name__ == "__main__":
    result = parse_file(sys.argv[1])
    print(json.dumps(result, ensure_ascii=False)[:1500])
