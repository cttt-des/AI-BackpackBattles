# -*- coding: utf-8 -*-
"""gen_core_item_book.py — 从原版 ItemBook.gd 生成内核描述符注册表 CoreItemBook.gd

背景
----
原版 `ItemBook` 是 autoload 单例，`getDescriptor(itemName)` 从 `items` 字典取
`ItemDescriptor` **资源**（ItemBook.gd:145-146）。无头内核没有资源系统，无法
`load()` 那些 .tres，于是物品脚本里 `ItemBook.magicRingDescriptor` 这类引用
会被判为残留外部符号 → 整函数剥离（FannyPack/Everburning/KingoftheBling 等
8 个战斗函数就是这么丢的）。

方案
----
改用**标识符注册表**：同一标识符恒返回同一 `CoreItemData` 实例。
之所以必须是同一实例 —— `Item.isA(desc)` 的原版语义就是
    func isA(_descriptor) -> bool: return descriptor == _descriptor   # Item.gd:703
引用相等。装配层只要用 `getDescriptor()` 给物品的 `descriptor` 赋值，`isA` 即成立，
与「资源实例唯一」的原版行为一致。

覆盖范围
--------
ItemBook.gd 里**全部** `XxxDescriptor = getDescriptor("...")` 声明。战斗函数
其实只用到其中少数，但全量生成成本为零，且能避免「用到哪个补哪个」的漏项。
名字→标识符的对应关系**逐条取自原版源码**，不做任何推测。

★ 原版把「声明」与「赋值」分成两处写（`var platinCardDescriptor` 在 :50，
  赋值 `platinCardDescriptor = getDescriptor("Platin Customer Card")` 在 :1001），
  故本工具匹配的是**赋值行**而非声明行 —— 只认 `var X = getDescriptor(...)`
  会漏掉 59/69 条。

用法
----
    python tools/gen_core_item_book.py [--check]
"""
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "decompiled_full", "Sheets", "ItemBook.gd")
OUT = os.path.join(ROOT, "gd_core", "CoreItemBook.gd")

DECL_RE = re.compile(r"^\s*(?:var\s+)?([A-Za-z_]\w*)\s*(?::[^=\n]+?)?\s*=\s*"
                     r"getDescriptor\(\s*\"([^\"]+)\"\s*\)", re.M)

HEADER = '''# =============================================================================
# CoreItemBook.gd — 无头战斗内核：物品描述符注册表（ItemBook 的无头子集）
# =============================================================================
# ★ 本文件由 tools/gen_core_item_book.py 从 decompiled_full/Sheets/ItemBook.gd
#   自动生成 —— **请勿手工维护**，重新生成即可。
#
# 原版 ItemBook 是 autoload 单例，getDescriptor(itemName) 从 items 字典取
# ItemDescriptor **资源**（ItemBook.gd:145-146）。内核没有资源系统，改用
# **标识符注册表**：同一标识符恒返回同一 CoreItemData 实例。
#
# 为什么「同一实例」是硬要求 —— Item.isA(desc) 的原版语义就是引用相等
# （Item.gd:703-704：return descriptor == _descriptor）。装配层用
# getDescriptor() 给物品的 descriptor 赋值，isA 即与原版行为一致。
#
# 覆盖：ItemBook.gd 里全部 %d 条 `XxxDescriptor = getDescriptor("...")` 声明，
#   名字→标识符的对应关系逐条取自原版源码，未做任何推测。
# =============================================================================
extends Reference
class_name CoreItemBook


var descriptors := {}

# 由 CoreContext 注入（对齐 ItemBook 是 autoload、能直接访问 Game.PLAYER / OPPONENT）
var _ctx


# ── 对齐 ItemBook.gd 的描述符名字 → 标识符表 ──
# ★ **只保留这张表，不另开成员变量**。原版 `ItemBook.magicRingDescriptor` 与
#   `getDescriptor("Magic Ring")` 指向同一份资源，故内核里两者也必须恒等价；
#   若既存表又存成员变量，`register()` 覆盖注册表后成员变量仍指向旧占位实例，
#   `isA()` 会静默判假（真踩过）。转译器把 `ItemBook.<名>Descriptor` 直接
#   改写成 `ctx.item_book.getDescriptor("<标识符>")`，单一真值源，无同步问题。
const DESCRIPTOR_IDS := {
%s
}


func _init() -> void :
	pass


# 对齐 ItemBook.gd:145-146（`return items[itemName]`；此处惰性建占位实例）
func getDescriptor(itemName: String) -> CoreItemData:
	if not descriptors.has(itemName):
		# 未注册 → 造一个**只有身份**的占位描述符：数值字段全零，等价于
		# 「原版资源尚未加载」。调用方只用它做身份比较（isA），不读数值。
		descriptors[itemName] = CoreItemData.new().fromDict(
			{"identifier": itemName, "name": itemName})
	return descriptors[itemName]


func hasDescriptor(itemName: String) -> bool:
	return descriptors.has(itemName)


# 装配层用真实数据（battle_items.json）覆盖占位实例。
# 同时按 name / identifier 两个键登记 —— 原版 items 字典的键是**显示名**
# （getDescriptor("Magic Ring")），而 CoreItemData.identifier 可能取别的写
# 法；两个键指向同一实例，故 isA 的引用相等语义不受影响。
func register(data: CoreItemData) -> CoreItemData:
	if data.name != "":
		descriptors[data.name] = data
	if data.identifier != "":
		descriptors[data.identifier] = data
	return data


# =============================================================================
# 按描述符查询库存物品（对齐 ItemBook.gd:272-335 / :387-391）
# =============================================================================
# 原版在**全局索引** ownableItems / opponentItems（descriptor → [Item]）上查询；
# 无头内核没有商店/储物箱/图鉴这些场外容器，等价做法是遍历对应角色的网格
# （ctx.player.inventory / ctx.opponent.inventory）逐件比描述符 —— 与
# CoreItem.countAllPlacedOfType 用的是同一条判据。
# ★ 描述符比较用 `==`（引用相等），与 ItemBook 的 Dictionary 键一致：
#   要求装配层对同一物品类型复用同一个 CoreItemData 实例（原版共享一份 .tres）。
#   内核侧保证这一点的入口就是本类的 getDescriptor() / register()。
#
# 两侧的筛选口径**刻意不同**（照抄原版）：
#   本方     —— 只算 ownerType ∈ {PlayerInventory, Socket}
#   对手方   —— 不过滤（对手网格里的物品在对局视角下都算「在场」）

func _sideItems(opponentSide: bool) -> Array:
	if opponentSide:
		if _ctx.opponent == null:
			return []
		return _ctx.opponent.inventory.getItemsAndGems()
	if _ctx.player == null:
		return []
	return _ctx.player.inventory.getItemsAndGems()


func _inventorySide(item) -> bool:
	return (item.ownerType == CoreConst.Owner.PlayerInventory
		or item.ownerType == CoreConst.Owner.Socket)


func _filter(descr, opponentSide: bool) -> Array:
	var out = []
	for item in _sideItems(opponentSide):
		if item == null or item.descriptor != descr:
			continue
		if opponentSide or _inventorySide(item):
			out.push_back(item)
	return out


# 对齐 ItemBook.gd:272-281
func getItemsInInventoryOfType(descr) -> Array:
	return _filter(descr, false)


# 对齐 ItemBook.gd:387-388
func getItemsInInventoryOfType_opponent(descr) -> Array:
	return _filter(descr, true)


# 对齐 ItemBook.gd:283-292
func countItemsInInventoryOfType(descr) -> int:
	return _filter(descr, false).size()


# 对齐 ItemBook.gd:390-391
func countItemsInInventoryOfType_opponent(descr) -> int:
	return _filter(descr, true).size()


# 对齐 ItemBook.gd:294-303（额外要求 PlayerInventory 侧 `placed`；Socket 侧不要求）
func countPlacedItemsInInventoryOfType(descr) -> int:
	var count = 0
	for item in _sideItems(false):
		if item == null or item.descriptor != descr:
			continue
		if item.ownerType == CoreConst.Owner.Socket:
			count += 1
		elif item.ownerType == CoreConst.Owner.PlayerInventory and item.placed:
			count += 1
	return count


# 对齐 ItemBook.gd:326-335
func isItemInInventory(descr) -> bool:
	return not _filter(descr, false).empty()


# 对齐 ItemBook.gd:337-338
func isItemInInventory_opponent(descr) -> bool:
	return not _filter(descr, true).empty()
'''


def collect():
    with io.open(SRC, encoding="utf-8", errors="replace") as fh:
        body = fh.read()
    assigns = DECL_RE.findall(body)
    # ★ 只保留**顶格声明过**的名字。原版把「声明」与「赋值」分两处写：
    #       var platinCardDescriptor              (顶格, ItemBook.gd:50)
    #       ...
    #       \tplatinCardDescriptor = getDescriptor("Platin Customer Card")   (:1001, 缩进)
    #   赋值行是缩进的，光看缩进区分不了「成员赋值」与「函数内局部变量」
    #   —— ItemBook.gd:1150 的 `var bloodAmulet = getDescriptor("Blood Amulet")`
    #   是 `init()` 里的局部量，曾被误收成成员。故用「顶格 var 声明」作交集过滤。
    declared = set(re.findall(r"^var\s+([A-Za-z_]\w*)", body, re.M))
    seen, out = set(), []
    for name, ident in assigns:
        if name in seen or name not in declared:
            continue
        seen.add(name)
        out.append((name, ident))
    return out


def render(pairs):
    table = "\n".join('\t"%s": "%s",' % (n, i) for n, i in pairs)
    return HEADER % (len(pairs), table)


def main():
    argv = sys.argv[1:]
    check = "--check" in argv
    if not os.path.exists(SRC):
        print("[错误] 找不到原版 ItemBook.gd：%s" % SRC)
        return 1
    pairs = collect()
    if not pairs:
        print("[错误] 未从 ItemBook.gd 解析到任何描述符声明")
        return 1
    text = render(pairs)
    old = None
    if os.path.exists(OUT):
        with io.open(OUT, encoding="utf-8", errors="replace") as fh:
            old = fh.read()
    if old == text:
        print("CoreItemBook.gd 与 ItemBook.gd 一致（%d 个描述符）" % len(pairs))
        return 0
    if check:
        print("[失败] CoreItemBook.gd 已过期，请运行 tools/gen_core_item_book.py")
        return 1
    with io.open(OUT, "w", encoding="utf-8", newline="\n") as fh:
        fh.write(text)
    print("已生成 gd_core/CoreItemBook.gd（%d 个描述符）：" % len(pairs))
    for n, i in pairs[:8]:
        print("   %-34s <= %s" % (n, i))
    if len(pairs) > 8:
        print("   …（余下 %d 个）" % (len(pairs) - 8))
    return 0


if __name__ == "__main__":
    sys.exit(main())
