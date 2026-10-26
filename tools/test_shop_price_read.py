#!/usr/bin/env python3
"""商店价格读取的 mock 结构自测（无需运行游戏）。

按解包源码的内存布局伪造一份假进程镜像（Game 单例 / Shop / ShopOffer 槽位 /
成员 Variant 序 / 价格 encode 编码），全链路跑 godot_reader + item_reader：

  1. decode_game_price 与 Game.encode/decode 语义往返一致
  2. 商店物品读取：价格/打折/免费/预订/已购 全字段正确
  3. read_shop_offers 对外 API（含已购槽位 item 不在 Items 子树）
  4. randnum 定位：标定下标缺失时结构扫描命中；gold_internal 同编码诱饵
     被金币交叉验证排除（gold≠0）；gold=0 边界（gold_internal==randnum）
  5. randnum 不可确证（破坏）→ 商店物品照常列出、价格省略（宁缺勿错）
  6. ShopOffer 成员序整体漂移 / 单槽签名不符 → 跳过槽位不误报

用法：python tools/test_shop_price_read.py
"""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.godot_reader import GodotReader, decode_game_price, price_signature  # noqa: E402
from core.item_reader import ItemReader  # noqa: E402

U64 = (1 << 64) - 1
PAGE = 0x1000
MODULE_BASE = 0x140000000
OS_RVA = 0x40000


def encode_price(g, randnum):
    """Game.encode 的 1:1 复刻（Game.gd:4784）。"""
    return ((g + (g << 32)) & U64) ^ (randnum & U64)


# ---------------- 假进程内存 ----------------
class FakeVM:
    def __init__(self):
        self.pages = {}
        self.cursor = 0x10000000

    def alloc(self, size):
        addr = self.cursor
        self.cursor += (size + 0xFF) & ~0xFF
        return addr

    def _w(self, addr, data):
        for i, b in enumerate(data):
            p, o = divmod(addr + i, PAGE)
            self.pages.setdefault(p, bytearray(PAGE))[o] = b

    def read(self, addr, size):
        out = bytearray()
        for i in range(size):
            p, o = divmod(addr + i, PAGE)
            pg = self.pages.get(p)
            out.append(pg[o] if pg else 0)
        return bytes(out)

    def w8(self, addr, v):
        self._w(addr, struct.pack("<B", v & 0xFF))

    def w32(self, addr, v):
        self._w(addr, struct.pack("<I", v & 0xFFFFFFFF))

    def w64(self, addr, v):
        self._w(addr, struct.pack("<Q", v & U64))


def make_string_data(vm, s):
    """CowData<Char>：count 在 _ptr-4，返回 _ptr 值。"""
    raw = s.encode("utf-16-le")
    base = vm.alloc(8 + len(raw) + 16)
    vm.w32(base, len(s))
    vm._w(base + 4, raw)
    return base + 4


def make_stringname_data(vm, s):
    d = vm.alloc(0x20)
    vm.w64(d + 0x10, make_string_data(vm, s))
    return d


def make_node(vm, name, script_path=None, children=(), members=None):
    node = vm.alloc(0x400)
    vm.w64(node + 0x130, make_stringname_data(vm, name))
    if children:
        base = vm.alloc(8 * len(children) + 8)
        vm.w32(base, len(children))
        for i, ch in enumerate(children):
            vm.w64(base + 4 + 8 * i, ch)
        vm.w64(node + 0x108, base + 4)  # _ptr；count 在 _ptr-4
    if script_path or members is not None:
        si = vm.alloc(0x40)
        vm.w64(node + 0x58, si)
        if script_path:
            script = vm.alloc(0x100)
            vm.w64(si + 0x10, script)
            vm.w64(script + 0x40, make_string_data(vm, script_path))
        if members is not None:
            vm.w64(si + 0x20, make_members(vm, members))
    return node


def write_variant(vm, va, vtype, value):
    vm.w32(va, vtype)
    if vtype == 1:                       # BOOL
        vm.w8(va + 8, 1 if value else 0)
    elif vtype == 2:                     # INT
        vm.w64(va + 8, value & U64)
    elif vtype == 3:                     # REAL
        vm._w(va + 8, struct.pack("<d", value))
    elif vtype == 17:                    # OBJECT（间址槽布局）
        slot = vm.alloc(8)
        vm.w64(va + 8, slot)
        vm.w64(slot, value)


def make_members(vm, variants):
    """variants: [(type, value)…] → 返回写到 si+0x20 的 CowData _ptr。"""
    n = len(variants)
    base = vm.alloc(24 * n + 8)
    vm.w32(base, n)
    for i, (t, v) in enumerate(variants):
        write_variant(vm, base + 4 + 24 * i, t, v)
    return base + 4


class FakeReader:
    module_base = MODULE_BASE

    def __init__(self, vm):
        self.vm = vm

    def read(self, addr, size):
        return self.vm.read(addr, size)

    def read_int64(self, addr):
        d = self.vm.read(addr, 8)
        if not d or len(d) < 8:
            return None
        return struct.unpack("<q", d)[0]


class FakeDB:
    """ItemDB 桩：测试不依赖 assets。"""

    def zh(self, name):
        return f"中:{name}"

    def is_bag(self, name):
        return False

    def occupied_cells(self, *a, **k):
        return []


SHOP_OFFER_SCRIPT = "res://Interface/ShopOffer.gd"
GAME_SCRIPT = "res://Core/Game.gd"
ITEM_SCRIPT = "res://Items/%s.gd"


def build_world(randnum, gold=13, game_randnum_idx=113, offer_shift=0,
                corrupt_slot2=False, dup_randnum=True):
    """构造假进程镜像，返回 (vm, gr, ir, expect)。

    offer_shift>0 模拟版本差异导致的成员序整体漂移；
    corrupt_slot2 把 3 号槽 price 成员类型改成 BOOL（单槽签名破坏）；
    dup_randnum=False 时移除 randnum 复本（配合 game_randnum_idx=None
    可构造「randnum 不可确证」的世界）。
    """
    vm = FakeVM()
    enc = lambda g: encode_price(g, randnum)  # noqa: E731

    # ---- Game 单例（成员按解包 Game.gd 声明序的子集）----
    members = [(0, None)] * 120
    members[72] = (2, gold)              # gold（明文）
    members[73] = (2, enc(gold))         # gold_internal（编码，同 randnum 家族诱饵）
    if dup_randnum:
        members[50] = (2, randnum)       # randnum 复本（无害诱饵）
    members[114] = (2, enc(gold))        # gold_internal 复本（签名同、金币关排除）
    members[42] = (2, 42)                # 无关小整数
    members[60] = (1, True)              # 无关 BOOL
    members[90] = (3, 1.5)               # 无关 REAL
    if game_randnum_idx is not None:
        members[game_randnum_idx] = (2, randnum)
    game = make_node(vm, "Game", GAME_SCRIPT, members=members)

    # ---- 商店槽位（ShopOffer.gd 成员序 0..12）----
    def offer_members(slot, item_node, effective, normal, sale, free,
                      on_sale, bought, reserved, sale_mode, stale_price=0):
        vars_ = [(2, slot),                                # 0 index
                 (17, item_node) if item_node else (0, 0),  # 1 item
                 (2, effective and enc(effective) or stale_price),  # 2 price
                 (1, free), (1, on_sale), (1, False),       # 3/4/5
                 (1, bought), (1, reserved),                # 6/7
                 (2, enc(normal)) if normal is not None else (0, 0),   # 8
                 (2, enc(sale)) if sale is not None else (0, 0),       # 9
                 (2, sale_mode),                            # 10 saleMode
                 (17, 0xDEAD0011), (17, 0xDEAD0022)]        # 11+ onready 对象
        if offer_shift:
            vars_ = [(0, 0)] + vars_[:-offer_shift]
        return vars_

    # ---- 物品节点（商店在售 4 件 + 已购 1 件游离）----
    item_nodes = {
        name: make_node(vm, name, ITEM_SCRIPT % name.replace(" ", ""))
        for name in ("Gloves of Haste", "Leather Armor", "Crimson Stone",
                     "Whetstone", "Sword of Doom")
    }

    offers_spec = [
        # (slot, item, effective, normal, sale, free, on_sale, bought, reserved, mode)
        (1, "Gloves of Haste", 12, 12, 6, False, False, False, False, 0),
        (2, "Leather Armor", 8, 16, 8, False, True, False, False, 1),
        (3, "Crimson Stone", 0, None, None, True, False, False, False, 3),
        (4, "Whetstone", 9, 9, 4, False, False, False, True, 0),
        (5, "Sword of Doom", 30, 30, 15, False, False, True, False, 0),
    ]
    offer_nodes = []
    for slot, item, eff, normal, sale, free, on_sale, bought, reserved, mode in offers_spec:
        vars_ = offer_members(slot, item_nodes[item], eff, normal, sale,
                              free, on_sale, bought, reserved, mode)
        if corrupt_slot2 and slot == 3:
            vars_[2] = (1, True)  # price 成员类型破坏 → 签名不符
        n = make_node(vm, f"ShopOffer{slot}", SHOP_OFFER_SCRIPT, members=vars_)
        offer_nodes.append(n)

    items_node = make_node(vm, "Items", None, list(item_nodes.values())[:4])
    storage = make_node(vm, "Storagebox")
    shop = make_node(vm, "Shop", None,
                     offer_nodes + [items_node, storage])
    inventory = make_node(vm, "Inventory")
    player = make_node(vm, "Player", None, [inventory])
    main = make_node(vm, "Main", None, [player, shop])
    root = make_node(vm, "root", None, [game, main])

    # ---- OS → SceneTree 锚点 ----
    os_obj = vm.alloc(0x400)
    main_loop = vm.alloc(0x200)
    vm.w64(MODULE_BASE + OS_RVA, os_obj)
    vm.w64(os_obj + 0x1D0, main_loop)
    vm.w64(main_loop + 0x148, root)

    gr = GodotReader(FakeReader(vm), {"os_singleton_rva": OS_RVA})
    ir = ItemReader(gr, item_db=FakeDB(), use_bridge=False)
    return vm, gr, ir, dict(randnum=randnum, gold=gold)


def check(name, cond, detail=""):
    tag = "PASS" if cond else "FAIL"
    print(f"  [{tag}] {name}" + (f"  {detail}" if detail and not cond else ""))
    return cond


def main():
    failures = 0
    print("== 1. decode_game_price 与 Game.encode/decode 往返 ==")
    ok = True
    for g in (0, 1, 3, 12, 37, 999999, (1 << 31) - 1):
        r = 0x8877665544332211
        ok &= check(f"g={g}", decode_game_price(encode_price(g, r), r) == g)
    ok &= check("半字校验拒绝",
                decode_game_price(0x1234567890ABCDEF, 0x8877665544332211) is None)
    ok &= check("签名一致性", price_signature(encode_price(7, r)) == price_signature(r))
    failures += not ok

    print("== 2. 商店物品价格全字段（gold=13 交叉验证激活）==")
    randnum = 0xFEDCBA9876543210
    _, _, ir, _ = build_world(randnum)
    items = ir.read_items()
    shop = {it["name"]: it for it in items["shop"]}
    ok = True
    ok &= check("商店物品数=4", len(items["shop"]) == 4, str(list(shop)))
    ok &= check("原价物品 price=12",
                shop.get("Gloves of Haste", {}).get("price") == 12)
    ok &= check("打折 price=8 原价16",
                shop.get("Leather Armor", {}).get("price") == 8
                and shop["Leather Armor"]["normal_price"] == 16
                and shop["Leather Armor"]["on_sale"])
    ok &= check("免费 price=0/free",
                shop.get("Crimson Stone", {}).get("price") == 0
                and shop["Crimson Stone"]["free"])
    ok &= check("预订 price=9",
                shop.get("Whetstone", {}).get("price") == 9
                and shop["Whetstone"]["reserved"])
    ok &= check("已购物品不在在售列表", "Sword of Doom" not in shop)
    offers = ir.read_shop_offers()
    ok &= check("read_shop_offers 5 槽按槽位序",
                [o["slot"] for o in offers] == [1, 2, 3, 4, 5])
    ok &= check("已购槽位标记+名字",
                offers[4]["bought"] and offers[4]["name"] == "Sword of Doom"
                and offers[4]["price"] == 30)
    ok &= check("中文名附上", shop["Gloves of Haste"]["zh"] == "中:Gloves of Haste")
    failures += not ok

    print("== 3. randnum 结构扫描（无标定下标）+ gold_internal 诱饵排除 ==")
    _, gr, ir, wd = build_world(randnum, game_randnum_idx=None)
    ok = True
    ok &= check("扫描命中真 randnum", gr.read_randnum([]) == wd["randnum"])
    it2 = {it["name"]: it for it in ir.read_items()["shop"]}
    ok &= check("扫描路径价格正确", it2["Gloves of Haste"]["price"] == 12)
    failures += not ok

    print("== 4. gold=0 边界（gold_internal==randnum）==")
    _, gr, ir, _ = build_world(randnum, gold=0, game_randnum_idx=None)
    ok = True
    ok &= check("gold=0 时仍可确证", gr.read_randnum([]) == randnum)
    failures += not ok

    print("== 5. randnum 破坏 → 物品照常、价格省略 ==")
    _, gr, ir, _ = build_world(0x1111111122222222, game_randnum_idx=None,
                               dup_randnum=False)
    ok = True
    ok &= check("确证失败返回 None", gr.read_randnum([]) is None)
    items = ir.read_items()
    shop = {it["name"]: it for it in items["shop"]}
    ok &= check("商店物品数仍=4", len(items["shop"]) == 4)
    ok &= check("编码价格全部省略（免费槽除外）",
                shop["Gloves of Haste"].get("price") is None
                and shop["Leather Armor"].get("price") is None
                and shop["Whetstone"].get("price") is None
                and shop["Crimson Stone"].get("price") == 0)
    failures += not ok

    print("== 6. 成员序漂移 / 单槽签名破坏 ==")
    _, _, ir, _ = build_world(randnum, offer_shift=1)
    items = ir.read_items()
    ok = True
    ok &= check("漂移后物品仍列出", len(items["shop"]) == 4)
    ok &= check("漂移后无价格字段",
                all("price" not in it for it in items["shop"]))
    _, _, ir, _ = build_world(randnum, corrupt_slot2=True)
    items = ir.read_items()
    shop = {it["name"]: it for it in items["shop"]}
    ok &= check("单槽破坏仅该槽无价格",
                "price" not in shop["Crimson Stone"]
                and shop["Gloves of Haste"]["price"] == 12)
    failures += not ok

    print("== 7. summary_lines 展示 ==")
    _, _, ir, _ = build_world(randnum)
    lines = ir.summary_lines()
    shop_lines = [ln for ln in lines if ln.startswith("[商店]")]
    ok = True
    ok &= check("打折行含原价", any("原价16·打折" in ln for ln in shop_lines),
                "\n".join(shop_lines))
    ok &= check("免费行", any("免费" in ln for ln in shop_lines))
    ok &= check("预订行", any("[已预订]" in ln for ln in shop_lines))
    failures += not ok

    print()
    if failures:
        print(f"结果：{failures} 组失败")
        return 1
    print("结果：全部通过")
    return 0


if __name__ == "__main__":
    sys.exit(main())
