"""
物品读取器 —— 结构性读取当前摆盘（背包网格）与储物箱/商店内的物品

场景树布局（2026-07-26 活体实测，Backpack Battles / Godot 3.6 x64）
------------------------------------------------------------------
root(Viewport)
 └─ Main (current_scene)
     ├─ Player                     ← 玩家区
     │   ├─ Inventory              ← 背包网格锚点 (Node2D, local pos≈(50,60), 80px/格)
     │   ├─ <物品名> (Node2D)      ← 摆盘物品，脚本 res://Items/<Item>.gd
     │   └─ ...
     └─ Shop
         ├─ ShopOffer1..5          ← 商店槽位（脚本 res://Interface/ShopOffer.gd，
         │                            持有 item/价格/打折/购买状态）
         ├─ Items/<物品名>         ← 商店在售物品（Game.shopItemYSort 指向此处）
         └─ Storagebox/<物品名>    ← 储物箱物品（有旋转，local≠global）

判定规则
--------
* 物品节点 = 脚本路径以 res://Items/ 开头的节点，且排除装饰性子节点
  （SocketsNode/GemSocket/BagBorder/GooglyEye/ItemPushZone/Tiles 等）。
* 物品名 = 节点名（游戏用显示名命名节点，如 "Gloves of Haste"）。
* 网格坐标 = (物品局部 pos - Inventory 局部 pos) / 80，四舍五入。
  物品 pos 是其锚点（通常在物品左上格中心附近），列/行取 floor。

商店价格（2026-10-25 依据解包源码 ShopOffer.gd/Shop.gd/Game.gd）
----------------------------------------------------------------
* 价格存于 ShopOffer 槽位脚本成员（不是物品脚本上）：
    item=1 price=2 free=3 onSale=4 bought=6 reserved=7
    normalPrice=8 salePrice=9 saleMode=10   （var 声明序，0 起）
* 价格在内存中经 Game.encode(g)=(g+(g<<32))^randnum 编码（Game.gd:4784），
  randnum 是 Game._ready 生成的 64 位密钥（成员 113）。
  解码时游戏自身校验 low32(e^r)==high32(e^r)，复刻于
  godot_reader.decode_game_price；randnum 的定位自带双重校验
  （签名一致 + gold_internal 解码须等于明文 gold），见 read_randnum。
* 有效成交价 = onSale ? salePrice : normalPrice（成员 price 由
  AnimationPlayer 方法轨道异步写回 updatePrice，存在滞后窗口，不直接采信）；
  free 槽位（SaleMode.Free）成交价为 0。
* 打折价 = ceil(原价×0.5)（ItemDescriptor.getSalePrice），打折与否由
  rollSale 掷签决定，直接读 onSale 标志即可，无需猜测。
* 任一环节校验失败（成员序漂移/randnum 不可确证）→ 商店物品照常列出，
  仅不附价格字段：宁可缺值，绝不给出错值。
"""
from __future__ import annotations

import logging
import struct
from typing import Dict, List, Optional

from .godot_reader import GodotReader, decode_game_price
from .item_db import ItemDB, clean_name

logger = logging.getLogger(__name__)

# 排除的装饰/功能性脚本（不是真实物品）
_EXCLUDE_SCRIPT_SUFFIXES = (
    "SocketsNode.gd", "GemSocket.gd", "BagBorder.gd",
    "GooglyEye.gd", "ItemPushZone.gd",
    "CraftingBond.gd",           # 合成预览链接，非物品
)
_EXCLUDE_SCRIPT_PARTS = ("/Tiles/", "/Animations/")


class ItemInfo(dict):
    """物品信息（dict 子类，便于 JSON/GUI 直接用）。
    字段: name(英文), zh(中文), zone(backpack|storage|shop), is_bag(容器),
          row, col(锚点格), cells([(row,col)..] 占用格), rotation, x, y, script
    """


class ItemReader:
    """从场景树结构性读取摆盘/储物箱/商店的物品清单。
    
    支持桥接模式：若有注入的桥接 GDScript（TCP），优先通过桥接获取
    联动/价格等运行时数据；否则回退到直接内存读取。
    """

    def __init__(self, godot_reader: GodotReader, item_db: Optional[ItemDB] = None,
                 use_bridge: bool = True):
        self.gr = godot_reader
        self.db = item_db or ItemDB()
        self._use_bridge = use_bridge
        # 场景树节点地址缓存（减少 ReadProcessMemory）
        self._cache: dict = {"main": None, "player": None, "shop": None,
                             "inv": None, "storage": None, "shop_items": None}

    def _invalidate_cache(self):
        for k in self._cache:
            self._cache[k] = None

    def _cached_find(self, cache_key: str, parent: Optional[int] = None,
                     name: str = "") -> Optional[int]:
        """带缓存的节点查找，只有根节点变化才重新搜索。"""
        cached = self._cache.get(cache_key)
        if cached is not None:
            return cached
        if cache_key == "main":
            node = self._find_main()
        elif parent is not None:
            node = self._find_by_name(parent, name)
        else:
            node = None
        if node is not None:
            self._cache[cache_key] = node
        return node

    def _bridge_cmd(self, cmd: str, args: dict = None) -> Optional[dict]:
        """通过桥接 TCP 获取数据。不可用时返回 None。"""
        if not self._use_bridge:
            return None
        try:
            from .bridge_client import get_bridge
            b = get_bridge()
            if not b.connected:
                if not b.connect():
                    return None
            return b.send_command(cmd, args)
        except Exception as e:
            logger.debug("桥接请求失败(%s): %s", cmd, e)
            return None

    def node_rotation(self, node: int) -> float:
        """读取 Node2D.rotation（实测位于 position 之后 +0x278）。"""
        off = self.gr.off.get("node2d_rot_off", 0x278)
        d = self.gr.reader.read(node + off, 4)
        if not d or len(d) < 4:
            return 0.0
        (rot,) = struct.unpack("<f", d)
        if rot != rot or abs(rot) > 100:  # NaN/离谱值
            return 0.0
        return rot

    # ---------- 内部工具 ----------
    def _is_item_script(self, sp: Optional[str]) -> bool:
        if not sp or not sp.startswith("res://Items/"):
            return False
        if sp.endswith(_EXCLUDE_SCRIPT_SUFFIXES):
            return False
        return not any(p in sp for p in _EXCLUDE_SCRIPT_PARTS)

    def _find_main(self) -> Optional[int]:
        """定位 current_scene 'Main'（root 的直接子节点里找）。"""
        root = self.gr.get_root()
        if not root:
            return None
        for c in self.gr.get_children(root):
            if self.gr.node_name(c) == "Main":
                return c
        return None

    def _child_by_name(self, node: int, name: str) -> Optional[int]:
        for c in self.gr.get_children(node):
            if self.gr.node_name(c) == name:
                return c
        return None

    def _find_by_name(self, node: int, name: str, max_depth: int = 12) -> Optional[int]:
        """在 node 子树内 BFS 递归查找名为 name 的节点（支持任意层级嵌套）。

        游戏场景树的 Player/Inventory/Shop/Storagebox/Items 未必都是直接子节点，
        用递归深搜避免漏读储物箱/商店/背包物品。
        """
        if not node:
            return None
        queue = [(node, 0)]
        i = 0
        while i < len(queue):
            cur, depth = queue[i]
            i += 1
            if self.gr.node_name(cur) == name:
                return cur
            if depth < max_depth:
                for c in self.gr.get_children(cur):
                    queue.append((c, depth + 1))
        return None

    def _collect_items(self, parent: int, zone: str,
                       inv_origin: Optional[tuple]) -> List[ItemInfo]:
        """收集 parent 直接子节点中的物品。"""
        collected: List[tuple] = []  # (ItemInfo, node)
        cell = self.gr.off.get("inv_cell_px", 80)
        for c in self.gr.get_children(parent):
            sp = self.gr.node_script_path(c)
            if not self._is_item_script(sp):
                continue
            raw = self.gr.node_name(c) or sp.rsplit("/", 1)[-1][:-3]
            name = clean_name(raw)
            pos = self.gr.node_pos(c)
            rot = self.node_rotation(c)
            info = ItemInfo(name=name, zh=self.db.zh(name), zone=zone,
                            script=sp, is_bag=self.db.is_bag(name),
                            rotation=round(rot, 4),
                            x=None, y=None, row=None, col=None, cells=[])
            if pos:
                info["x"], info["y"] = round(pos[0], 1), round(pos[1], 1)
                if zone == "backpack" and inv_origin:
                    # 锚点格（物品原点所在格）
                    gx = (pos[0] - inv_origin[0]) / cell
                    gy = (pos[1] - inv_origin[1]) / cell
                    if -2 <= gx < 30 and -2 <= gy < 30:
                        info["col"] = int(gx)
                        info["row"] = int(gy)
                    # 完整占格（tscn CollisionMap 形状 + 旋转）
                    info["cells"] = self.db.occupied_cells(
                        name, pos, rot, inv_origin, cell)
            collected.append((info, c))
        # 容器排前面（GUI 先画袋子再画物品）
        collected.sort(key=lambda ic: (not ic[0]["is_bag"], ic[0]["name"]))
        return [info for info, _ in collected]

    # ---------- 桥接快速路径（一次 TCP 往返获取所有物品）----------
    def _fast_read_lineup(self) -> Optional[Dict[str, List[ItemInfo]]]:
        """通过桥接 TCP 快速读取全部物品数据（一次往返）。

        桥接已在游戏进程内，用 Godot API 遍历节点比外置 ReadProcessMemory
        快数百倍。这个调用是单次 TCP 请求，解析返回的 JSON。
        """
        resp = self._bridge_cmd("get_item_details", {"zone": "all"})
        if not resp or not resp.get("ok"):
            return None
        data = resp.get("data", {})
        if not data or "error" in data:
            return None

        empty = {"backpack": [], "storage": [], "shop": []}

        # 读取背包的 Inventory 坐标锚点（用于算网格位置）
        inv_origin = None
        main = self._cached_find("main")
        if main:
            player = self._cached_find("player", main, "Player")
            if player:
                inv = self._cached_find("inv", player, "Inventory")
                inv_origin = self.gr.node_pos(inv) if inv else None

        cell = self.gr.off.get("inv_cell_px", 80)
        result = dict(empty)

        zone_map = {"backpack": 0, "shop": 1, "storage": 2}
        zones = ["backpack", "shop", "storage"]

        for zone in zones:
            items_data = data.get(zone, [])
            for item in items_data:
                name = clean_name(item.get("name", ""))
                if not name:
                    continue
                pos = item.get("position", {})
                x, y = pos.get("x"), pos.get("y")
                rot = item.get("rotation", 0.0)
                info = ItemInfo(name=name, zh=self.db.zh(name), zone=zone,
                                is_bag=self.db.is_bag(name),
                                rotation=round(float(rot), 4),
                                x=float(x) if x is not None else None,
                                y=float(y) if y is not None else None,
                                row=None, col=None, cells=[],
                                script=item.get("script_path", ""))
                if x is not None and y is not None:
                    if zone == "backpack" and inv_origin:
                        gx = (float(x) - inv_origin[0]) / cell
                        gy = (float(y) - inv_origin[1]) / cell
                        if -2 <= gx < 30 and -2 <= gy < 30:
                            info["col"] = int(gx)
                            info["row"] = int(gy)
                        info["cells"] = self.db.occupied_cells(
                            name, (float(x), float(y)), float(rot),
                            inv_origin, cell)
                result[zone].append(info)
            result[zone].sort(key=lambda i: (not i["is_bag"], i["name"]))

        return result

    def _is_gem_script(self, sp: Optional[str]) -> bool:
        """脚本路径层面判定宝石（socketable gem / rune）。

        结构性识别为主（见 _collect_items 的 in_sockets 标记），这里仅作补充
        判定，覆盖脚本不在 Items/Gems 下的稀有宝石（如 BurningCoal.gd）。
        """
        if not sp:
            return False
        return "/Items/Gems/" in sp or "/Items/Exclusive/" in sp

    def _build_info(self, node, zone: str, inv_origin,
                    compute_grid: bool) -> ItemInfo:
        """构造单个物品的 ItemInfo（gems/contents 为占位，由递归调用填充）。"""
        cell = self.gr.off.get("inv_cell_px", 80)
        sp = self.gr.node_script_path(node)
        raw = self.gr.node_name(node) or (sp or "").rsplit("/", 1)[-1][:-3]
        name = clean_name(raw)
        pos = self.gr.node_pos(node)
        rot = self.node_rotation(node)
        info = ItemInfo(name=name, zh=self.db.zh(name), zone=zone,
                        script=sp, is_bag=self.db.is_bag(name),
                        rotation=round(rot, 4),
                        x=None, y=None, row=None, col=None, cells=[],
                        gems=[], contents=[])
        if pos:
            info["x"], info["y"] = round(pos[0], 1), round(pos[1], 1)
            if compute_grid and zone == "backpack" and inv_origin:
                gx = (pos[0] - inv_origin[0]) / cell
                gy = (pos[1] - inv_origin[1]) / cell
                if -2 <= gx < 30 and -2 <= gy < 30:
                    info["col"] = int(gx)
                    info["row"] = int(gy)
                info["cells"] = self.db.occupied_cells(
                    name, (pos[0], pos[1]), rot, inv_origin, cell)
        return info

    def _collect_items(self, parent, zone: str, inv_origin,
                       depth: int = 0, parent_info: Optional[ItemInfo] = None,
                       in_sockets: bool = False, _visited=None,
                       offers: Optional[Dict[int, dict]] = None) -> List[ItemInfo]:
        """递归收集 parent 子树中的物品，并捕获**镶嵌宝石**与**袋内物品**。

        场景树结构（基于 Items/Item.gd 反编译源码，非臆测）：
          - 镶嵌宝石：setGem() 执行 sockets[id].add_child(gem)，
            sockets = $Icon/Sockets.get_children()，故宝石位于
            物品 → Icon → Sockets → Socket(GemSocket.gd) 之下。
          - 袋内物品：reparent(item, insideRotationNode)，故位于
            袋子 → insideRotationNode 之下。

        判定规则（优先级自上而下）：
          1. 位于 Sockets/GemSocket 子树（in_sockets）下的物品节点 → 宿主 gems
             （覆盖武器/护甲/袋子的镶嵌宝石，含 Exclusive 符文）
          2. Player/Storagebox/Items 的直接子节点 → 顶层物品（含散落宝石）
          3. is_bag 物品子树下的物品节点（非 sockets 子树）→ 宿主 contents
          4. 非袋宿主下、宝石脚本判定的后代物品 → 宿主 gems（兜底）
        """
        if _visited is None:
            _visited = set()
        if parent in _visited or depth > 24:
            return []
        _visited.add(parent)

        collected: List[ItemInfo] = []
        for c in self.gr.get_children(parent):
            if c in _visited:
                continue
            sp = self.gr.node_script_path(c)
            nm = self.gr.node_name(c) or ""
            is_socket_node = bool(sp) and ("GemSocket" in sp or "SocketsNode" in sp)
            child_in_sockets = in_sockets or is_socket_node or (nm == "Sockets")

            if self._is_item_script(sp):
                info = self._build_info(c, zone, inv_origin,
                                        compute_grid=(parent_info is None))
                if parent_info is not None and child_in_sockets:
                    # 任何宿主（武器/护甲/袋子）的镶嵌宝石
                    parent_info["gems"].append({"id": info["name"]})
                    continue
                if parent_info is None:
                    if offers is not None and c in offers:
                        # 商店槽位报价：并上价格/打折/购买状态（槽位 item 指针对号）
                        self._merge_offer(info, offers[c])
                    collected.append(info)          # 顶层物品（含散落宝石）
                elif parent_info.get("is_bag"):
                    parent_info["contents"].append(info)   # 袋内物品
                elif self._is_gem_script(sp):
                    parent_info["gems"].append({"id": info["name"]})  # 兜底
                else:
                    parent_info["contents"].append(info)  # 罕见兜底
                # 继续向下，捕获该物品的宝石 / 嵌套袋内物品
                self._collect_items(c, zone, inv_origin, depth=depth + 1,
                                    parent_info=info, in_sockets=child_in_sockets,
                                    _visited=_visited)
            elif is_socket_node or nm == "Sockets":
                # 宝石槽容器节点：下降并标记 in_sockets，保留 parent_info
                self._collect_items(c, zone, inv_origin, depth=depth + 1,
                                    parent_info=parent_info, in_sockets=True,
                                    _visited=_visited)
            else:
                # 其它装饰/容器节点（Icon / insideRotationNode / Sprite 等）：
                # 下降以发现嵌套的宝石 / 袋内物品
                self._collect_items(c, zone, inv_origin, depth=depth + 1,
                                    parent_info=parent_info,
                                    in_sockets=child_in_sockets,
                                    _visited=_visited)
        # 顶层物品：容器排前面（GUI 先画袋子再画物品）
        if parent_info is None:
            collected.sort(key=lambda i: (not i["is_bag"], i["name"]))
        return collected

    # ---------- 商店报价（ShopOffer 槽位，价格/打折/购买状态）----------
    # ShopOffer.gd 成员序的运行时结构签名（0..10，解包源码声明序）。
    # 类型为 Godot Variant 枚举：0=NIL 1=BOOL 2=INT 17=OBJECT。
    # normalPrice/salePrice 无初始值故可为 NIL；其余按声明默认值判定。
    _OFFER_TYPE_SIGNATURE = (
        {2},          # 0  index
        {17, 0},      # 1  item（对象；reset 后为 NIL）
        {2},          # 2  price
        {1}, {1}, {1}, {1}, {1},   # 3..7 free/onSale/wasOnSale/bought/reserved
        {2, 0},       # 8  normalPrice
        {2, 0},       # 9  salePrice
        {2},          # 10 saleMode
    )
    _SALE_MODES = {0: "roll", 1: "sale", 2: "no_sale", 3: "free"}

    def _read_shop_offers(self, shop_node: int) -> List[dict]:
        """读取 Shop 节点下全部 ShopOffer 槽位的报价信息。

        成员序经结构签名逐槽校验（防版本差异导致错位读数）；randnum 经
        read_randnum 双重校验（价格签名 + gold_internal↔gold 交叉验证）。
        任一槽签名不符则跳过该槽；randnum 不可确证则全部槽只给标志不给价格。
        """
        want_sp = self.gr.off.get("shopoffer_script_path",
                                  "res://Interface/ShopOffer.gd")
        raw_offers: List[dict] = []
        for c in self.gr.get_children(shop_node):
            sp = self.gr.node_script_path(c)
            if sp != want_sp:
                continue
            variants = self.gr.read_variants(c)
            if len(variants) <= self.gr.off.get("shopoffer_sale_mode", 10):
                continue
            if not self._offer_signature_ok(variants):
                logger.debug("ShopOffer 成员序签名不符（node=%#x），跳过", c)
                continue

            def member(i):
                return variants[i][1]

            item_addr = member(self.gr.off.get("shopoffer_item", 1))
            offer = {
                "node_addr": c,
                "item_addr": item_addr if isinstance(item_addr, int) else None,
                "slot": member(0),
                "price_raw": member(self.gr.off.get("shopoffer_price", 2)),
                "free": bool(member(self.gr.off.get("shopoffer_free", 3))),
                "on_sale": bool(member(self.gr.off.get("shopoffer_onsale", 4))),
                "bought": bool(member(self.gr.off.get("shopoffer_bought", 6))),
                "reserved": bool(member(self.gr.off.get("shopoffer_reserved", 7))),
                "normal_raw": member(self.gr.off.get("shopoffer_normal_price", 8)),
                "sale_raw": member(self.gr.off.get("shopoffer_sale_price", 9)),
            }
            sm = member(self.gr.off.get("shopoffer_sale_mode", 10))
            offer["sale_mode"] = self._SALE_MODES.get(sm, str(sm))
            raw_offers.append(offer)

        if not raw_offers:
            return []

        # randnum 校验样本：槽位上全部非 NIL 的编码价格。
        # 有样本 → 签名+金币双重校验；无样本（刚开店/全免费）→ 仅金币校验。
        # 样本校验失败时本轮不给价格（可能是撕裂读，宁缺勿错）。
        samples = []
        for o in raw_offers:
            for key in ("normal_raw", "sale_raw"):
                if isinstance(o[key], int):
                    samples.append(o[key])
        randnum = self.gr.read_randnum(samples)
        if randnum is None:
            logger.debug("randnum 不可确证 → 本轮商店价格省略")

        for o in raw_offers:
            o["normal_price"] = self._decode_price(o["normal_raw"], randnum)
            o["sale_price"] = self._decode_price(o["sale_raw"], randnum)
            if o["free"]:
                o["price"] = 0
            elif o["on_sale"]:
                o["price"] = o["sale_price"]
            else:
                o["price"] = o["normal_price"]
        return raw_offers

    def _decode_price(self, encoded, randnum) -> Optional[int]:
        """解码单个价格。randnum 缺失/校验失败一律返回 None（不猜值）。"""
        if not isinstance(encoded, int) or randnum is None:
            return None
        return decode_game_price(encoded, randnum)

    def _offer_signature_ok(self, variants: List[tuple]) -> bool:
        """校验 ShopOffer 成员序与解包源码声明序一致（类型层面）。"""
        for i, want in enumerate(self._OFFER_TYPE_SIGNATURE):
            t = variants[i][0]
            if t not in want:
                return False
        return True

    def read_shop_offers(self) -> List[dict]:
        """对外 API：读取商店槽位报价（含物品名/价格/打折/购买状态）。

        返回按槽位号排序的 dict 列表：
          slot, name, zh, price(成交价，可能 None), normal_price, sale_price,
          on_sale, free, bought, reserved, sale_mode
        仅供 AI 决策/CLI 使用；GUI 的 read_items 路径会把价格并进商店物品。
        """
        out: List[dict] = []
        main = self._cached_find("main")
        shop = self._cached_find("shop", main, "Shop") if main else None
        if not shop:
            return out
        for o in self._read_shop_offers(shop):
            name = None
            if o.get("item_addr"):
                raw = self.gr.node_name(o["item_addr"])
                name = clean_name(raw) if raw else None
            rec = {k: o.get(k) for k in (
                "slot", "price", "normal_price", "sale_price", "on_sale",
                "free", "bought", "reserved", "sale_mode")}
            rec["name"] = name
            rec["zh"] = self.db.zh(name) if name else None
            out.append(rec)
        out.sort(key=lambda r: (r["slot"] is None, r["slot"]))
        return out

    @staticmethod
    def _merge_offer(info: ItemInfo, offer: dict):
        """把槽位报价字段并入商店物品的 ItemInfo（缺值保持 None）。"""
        info["price"] = offer.get("price")
        info["normal_price"] = offer.get("normal_price")
        info["sale_price"] = offer.get("sale_price")
        info["on_sale"] = bool(offer.get("on_sale"))
        info["free"] = bool(offer.get("free"))
        info["bought"] = bool(offer.get("bought"))
        info["reserved"] = bool(offer.get("reserved"))
        info["slot"] = offer.get("slot")

    # ---------- 对外 API ----------
    def read_items(self) -> Dict[str, List[ItemInfo]]:
        """读取当前摆盘/储物箱/商店的全部物品。

        策略（稳定优先）：
          1) 结构性内存读取（带缓存+优化，已验证稳定）
          2) 桥接 TCP 作为快速增强（可用时尝试获取额外数据）

        返回 {"backpack": [...], "storage": [...], "shop": [...]}
        读不到时返回三个空列表。
        """
        # 策略 A：结构性内存读取（已验证稳定的主路径）
        result = self._mem_read_items()

        # 策略 B：若有桥接则尝试用桥接辅助补充坐标/旋转精度
        # （当前先保持纯内存路径，桥接作为扩展暂不干扰主流程）
        return result

    def _mem_read_items(self) -> Dict[str, List[ItemInfo]]:
        """结构性内存读取（带缓存优化，回退方案）。"""
        empty = {"backpack": [], "storage": [], "shop": []}
        try:
            main = self._cached_find("main")
            if not main:
                self._invalidate_cache()
                return empty

            result = dict(empty)

            player = self._cached_find("player", main, "Player")
            if player:
                inv = self._cached_find("inv", player, "Inventory")
                inv_origin = self.gr.node_pos(inv) if inv else None
                result["backpack"] = self._collect_items(player, "backpack", inv_origin)

            shop = self._cached_find("shop", main, "Shop")
            if shop:
                storage = self._cached_find("storage", shop, "Storagebox")
                if storage:
                    result["storage"] = self._collect_items(storage, "storage", None)
                shop_items = self._cached_find("shop_items", shop, "Items")
                if shop_items:
                    offers = self._read_shop_offers(shop)
                    offers_by_addr = {o["item_addr"]: o
                                      for o in offers if o.get("item_addr")}
                    result["shop"] = self._collect_items(
                        shop_items, "shop", None, offers=offers_by_addr)
            return result
        except Exception as e:  # noqa: BLE001
            logger.debug("内存物品读取失败: %s", e)
            self._invalidate_cache()
            return empty

    def summary_lines(self) -> List[str]:
        """人类可读的物品清单（供日志/CLI 使用）。"""
        data = self.read_items()
        lines: List[str] = []
        for it in data["backpack"]:
            tag = "容器" if it["is_bag"] else "摆盘"
            if it["cells"]:
                cells = ",".join(f"({r},{c})" for r, c in it["cells"])
                lines.append(f"[{tag}] {it['zh']}({it['name']}) 占格 {cells}")
            elif it["row"] is not None:
                lines.append(f"[{tag}] {it['zh']}({it['name']}) @ 格({it['row']},{it['col']})")
            else:
                lines.append(f"[{tag}] {it['zh']}({it['name']}) @ px({it['x']},{it['y']})")
        for it in data["storage"]:
            lines.append(f"[储物箱] {it['zh']}({it['name']})")
        for it in data["shop"]:
            line = f"[商店] {it['zh']}({it['name']})"
            if it.get("free"):
                line += " 免费"
            elif it.get("price") is not None:
                if it.get("on_sale"):
                    line += (f" {it['price']}金"
                             f"（原价{it['normal_price']}·打折）")
                else:
                    line += f" {it['price']}金"
            if it.get("bought"):
                line += " [已购买]"
            elif it.get("reserved"):
                line += " [已预订]"
            lines.append(line)
        return lines

    # ---------------- 战斗双方阵容读取（战斗日志导出用） ----------------
    def read_fight_lineups(self) -> Dict[str, List[ItemInfo]]:
        """读取战斗双方的背包物品（战斗结束瞬间双方 INVENTORY 均在场景中）。

        玩家侧沿用 backpack 读取路径；对手侧在 Main 下找 Opponent 节点，
        同样用 _collect_items 递归（含镶嵌宝石与袋内物品）。
        返回 {"player": [...], "opponent": [...]}。
        """
        out: Dict[str, List[ItemInfo]] = {"player": [], "opponent": []}
        main = self._cached_find("main")
        if not main:
            self._invalidate_cache()
            return out
        player = self._cached_find("player", main, "Player")
        if player:
            inv = self._find_by_name(player, "Inventory")
            origin = self.gr.node_pos(inv) if inv else None
            out["player"] = self._collect_items(player, "backpack", origin)
        opp = self._find_by_name(main, "Opponent", max_depth=3)
        if opp:
            inv = self._find_by_name(opp, "Inventory")
            origin = self.gr.node_pos(inv) if inv else None
            out["opponent"] = self._collect_items(opp, "backpack", origin)
        return out
