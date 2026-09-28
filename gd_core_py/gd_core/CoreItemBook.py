# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreItemBook(GodotObject):

	resource_path = "res://gd_core/CoreItemBook.gd"

	def _init_fields(self):
		super()._init_fields()
		self.descriptors = {}
		self._ctx = None

	# =============================================================================
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
	# 覆盖：ItemBook.gd 里全部 49 条 `XxxDescriptor = getDescriptor("...")` 声明，
	#   名字→标识符的对应关系逐条取自原版源码，未做任何推测。
	# =============================================================================



	# 由 CoreContext 注入（对齐 ItemBook 是 autoload、能直接访问 Game.PLAYER / OPPONENT）


	# ── 对齐 ItemBook.gd 的描述符名字 → 标识符表 ──
	# ★ **只保留这张表，不另开成员变量**。原版 `ItemBook.magicRingDescriptor` 与
	#   `getDescriptor("Magic Ring")` 指向同一份资源，故内核里两者也必须恒等价；
	#   若既存表又存成员变量，`register()` 覆盖注册表后成员变量仍指向旧占位实例，
	#   `isA()` 会静默判假（真踩过）。转译器把 `ItemBook.<名>Descriptor` 直接
	#   改写成 `ctx.item_book.getDescriptor("<标识符>")`，单一真值源，无同步问题。
	DESCRIPTOR_IDS = {
		"boxOfRichesDescriptor": "Box of Riches",
		"deckOfCardsDescriptor": "Deck of Cards",
		"crossbladesDescriptor": "Crossblades",
		"platinCardDescriptor": "Platin Customer Card",
		"customerCardDescriptor": "Customer Card",
		"staminaSackDescriptor": "Stamina Sack",
		"presentDescriptor": "Present",
		"flameDescriptor": "Flame",
		"forgingHammerDescriptor": "Forging Hammer",
		"amuletDescriptor": "Amulet Unidentified",
		"amuletOfFeastingDescriptor": "Amulet of Feasting",
		"starOfCourageDescriptor": "Star of Courage",
		"toolboxDescriptor": "Toolbox",
		"stableRecombobulatorDescriptor": "Stable Recombobulator",
		"unstableRecombobulatorDescriptor": "Unstable Recombobulator",
		"extraBagsDescriptor": "Extra Bags",
		"rainbowBadgeDescriptor": "Rainbow Badge",
		"stoneBadgeDescriptor": "Stone Badge",
		"spiritBellsDescriptor": "Spirit Bells",
		"bagOfGivingDescriptor": "Bag of Giving",
		"chessboardDescriptor": "Chess Board",
		"snowmanDescriptor": "Snowman",
		"uniquelyUniqueDescriptor": "Uniquely Unique",
		"bagtacularDescriptor": "Bagtacular",
		"justStatsDescriptor": "Just Stats",
		"moreStatsDescriptor": "More Stats",
		"unidentifiedSkillDescriptor": "Unidentified Skill",
		"digDeeperDescriptor": "Dig Deeper",
		"puzzleboxDescriptor": "Puzzlebox",
		"puzzleBadgeDescriptor": "Puzzle Badge",
		"sewingCaseDescriptor": "Sewing Case",
		"twineDescriptor": "Twine",
		"arcaneIntellectDescriptor": "Arcane Intellect",
		"fedoraDescriptor": "Fedora",
		"piggyOfRichesDescriptor": "Piggy of Riches",
		"batteryDescriptor": "Battery",
		"coilDescriptor": "Coil",
		"chargeSplitterDescriptor": "Charge Splitter",
		"manaCrystalDescriptor": "Mana Crystal",
		"lightningStaffDescriptor": "Lightning Staff",
		"boxofCogsDescriptor": "Engineer Bag 2",
		"cogDescriptor": "Cog",
		"generatorDescriptor": "Generator",
		"cogBadgeDescriptor": "Cog Badge",
		"contraptronDescriptor": "Con-Trap-Tron",
		"bloodAmuletDescriptor": "Blood Amulet",
		"magicRingDescriptor": "Magic Ring",
		"superiorRingDescriptor": "Superior Ring",
		"hyperCubeDescriptor": "Hypercube",
	}


	def _init(self):
		pass


	# 对齐 ItemBook.gd:145-146（`return items[itemName]`；此处惰性建占位实例）
	def getDescriptor(self, itemName):
		if not (itemName in self.descriptors):
			# 未注册 → 造一个**只有身份**的占位描述符：数值字段全零，等价于
			# 「原版资源尚未加载」。调用方只用它做身份比较（isA），不读数值。
			self.descriptors[itemName] = _R.C("CoreItemData")().fromDict(
				{"identifier": itemName, "name": itemName})
		return self.descriptors[itemName]


	def hasDescriptor(self, itemName):
		return (itemName in self.descriptors)


	# 装配层用真实数据（battle_items.json）覆盖占位实例。
	# 同时按 name / identifier 两个键登记 —— 原版 items 字典的键是**显示名**
	# （getDescriptor("Magic Ring")），而 CoreItemData.identifier 可能取别的写
	# 法；两个键指向同一实例，故 isA 的引用相等语义不受影响。
	def register(self, data):
		if data.name != "":
			self.descriptors[data.name] = data
		if data.identifier != "":
			self.descriptors[data.identifier] = data
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

	def _sideItems(self, opponentSide):
		if opponentSide:
			if self._ctx.opponent == None:
				return []
			return self._ctx.opponent.inventory.getItemsAndGems()
		if self._ctx.player == None:
			return []
		return self._ctx.player.inventory.getItemsAndGems()


	def _inventorySide(self, item):
		return (item.ownerType == _R.C("CoreConst").Owner.PlayerInventory
			or item.ownerType == _R.C("CoreConst").Owner.Socket)


	def _filter(self, descr, opponentSide):
		out = []
		for item in _iter(self._sideItems(opponentSide)):
			if item == None or item.descriptor != descr:
				continue
			if opponentSide or self._inventorySide(item):
				out.append(item)
		return out


	# 对齐 ItemBook.gd:272-281
	def getItemsInInventoryOfType(self, descr):
		return self._filter(descr, False)


	# 对齐 ItemBook.gd:387-388
	def getItemsInInventoryOfType_opponent(self, descr):
		return self._filter(descr, True)


	# 对齐 ItemBook.gd:283-292
	def countItemsInInventoryOfType(self, descr):
		return len(self._filter(descr, False))


	# 对齐 ItemBook.gd:390-391
	def countItemsInInventoryOfType_opponent(self, descr):
		return len(self._filter(descr, True))


	# 对齐 ItemBook.gd:294-303（额外要求 PlayerInventory 侧 `placed`；Socket 侧不要求）
	def countPlacedItemsInInventoryOfType(self, descr):
		count = 0
		for item in _iter(self._sideItems(False)):
			if item == None or item.descriptor != descr:
				continue
			if item.ownerType == _R.C("CoreConst").Owner.Socket:
				count += 1
			elif item.ownerType == _R.C("CoreConst").Owner.PlayerInventory and item.placed:
				count += 1
		return count


	# 对齐 ItemBook.gd:326-335
	def isItemInInventory(self, descr):
		return not (not self._filter(descr, False))


	# 对齐 ItemBook.gd:337-338
	def isItemInInventory_opponent(self, descr):
		return not (not self._filter(descr, True))


_R.reg("res://gd_core/CoreItemBook.gd", CoreItemBook)
_R.reg("CoreItemBook", CoreItemBook)
_R.reg("CoreItemBook", CoreItemBook)
