# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreGrid(GodotObject):

	resource_path = "res://gd_core/CoreGrid.gd"

	def _init_fields(self):
		super()._init_fields()
		self.filledCells = {}   # cell(Vector2) → item
		self.bagCells = {}      # cell(Vector2) → bag
		self.items = []
		self.character = None
		self.curHovered = {}    # 拖拽预览用；内核战斗路径不写入

	# =============================================================================
	# CoreGrid.gd — 无头战斗内核：背包网格（邻接 / 受影响格查询）
	# =============================================================================
	# 对齐源码：Core/Inventory.gd（全文 1331 行）的**战斗相关子集**
	#
	# 原版 Inventory 把三件事塞在一起：① 格子→物品映射；② 拖拽/悬停/放置预览等交互；
	# ③ 与 TileMap 节点耦合的几何换算（global point ↔ cell）。物品行为的邻接判定
	# （canAffect / getAffectedItems / getNeighborItemsAndGems）只用得到 ①。
	# 本类只承载 ① 与 ③ 的**格空间等价形式**。
	#
	# ── 坐标系约定（本内核的核心简化，已记入 docs/gd_core_truth.md 第 5 节） ──
	# 原版受影响格的求值是「格空间 → 全局坐标 → 再回到格空间」的往返：
	#   getAffectedPoints()            = getGlobalPointsForCells(受影响 tile) + getAffectedCells_noRotate()
	#   getAffectedCellsInInventory()  = inventory.getCellsForGlobalPositions(上面那些点)
	#   getAffectedCells_noRotate()    = getGlobalPointsForCells_noRotate(
	#                                        getAffectedCellsAfterRotate(getCellsForGlobalPositions(
	#                                            getCollisionPoints()), color))
	# 逐段代入可见：两次往返各自把一个格心映射回它自己（floor(格心 / cellSize) 恒等于该格），
	# 因此净效果就是**格空间的集合运算**。内核据此直接以格空间求值，剥离全部
	# to_global / world_to_map / map_to_world / halfCellSize 几何调用。
	#
	# 这一折叠的等价性依据与验证方式：
	#   · 项目已有等价模型 simulator/grid.py，且经 47 套真实游戏阵容零冲突验证；
	#   · 内核的格数据由同一套 extract_grid.py 产出（battle_items.json 的 grid 字段）。
	# 风险：若物品的 collisionMap 节点相对背包 TileMap 存在非整格偏移，折叠会引入
	#   一格错位。当前无证据表明存在该偏移；此项列为**里程碑 1 的已知保真风险**
	#   （docs/gd_core_truth.md 第 6 节），后续可用「同一阵容在 simulator 与 CoreGrid
	#   下受影响格集合逐项比对」来证伪。
	#
	# 剥离内容（全部属交互/表现，见 CoreItem 文件头）：拖拽、悬停、放置预览、
	#   冲突高亮、TileMap 绘制、borderCells、排序与自动整理。
	# =============================================================================


	# 对齐 Inventory.gd:51-56 的字段（子集）


	def _init(self, _character=None):
		self.character = _character


	# 对齐 Inventory.gd:377-381 —— 内核里点集与格集在格点上互逆，
	# 故本方法直接返回传入的格（见文件头坐标系约定）。
	def getCellsForGlobalPositions(self, points):
		return points


	# 对齐 Inventory.gd:368-369
	def getItems(self):
		return self.items


	# 对齐 Inventory.gd:371-375
	def getItemsAndGems(self):
		itemsAndGems = _dup(self.items)
		for item in _iter(self.items):
			itemsAndGems.extend(item.getGemsNoNull())
		return itemsAndGems


	# 对齐 Inventory.gd:269-272
	def isHovered(self, cell):
		return cell in self.curHovered


	# 对齐 Inventory.gd:716-717
	def isCellEmpty(self, cell):
		return cell in self.bagCells and not cell in self.filledCells


	# 对齐 Inventory.gd:719-724
	def getEmptyCellsInCells(self, cells):
		num = 0
		for cell in _iter(cells):
			if self.isCellEmpty(cell):
				num += 1
		return num


	# 对齐 Inventory.gd:726-727
	def getItemInCell(self, cell):
		return self.filledCells.get(cell, None)


	# 对齐 Inventory.gd:729-739
	def getItemsInCells(self, cells):
		itemsInCells = []
		for cell in _iter(cells):
			if (cell in self.filledCells):
				item = self.filledCells[cell]
				if not item in itemsInCells and item.placed:
					itemsInCells.append(item)

		return itemsInCells


	# 对齐 Inventory.gd:742-747（Util.dictAdd 记的是「物品 → 命中格数」）
	def countItemsInCells(self, cells):
		itemCounter = {}
		for cell in _iter(cells):
			if (cell in self.filledCells):
				_R.C("CoreUtil").dictAdd(itemCounter, self.filledCells[cell])
		return itemCounter


	# 对齐 Inventory.gd:749-757
	def getBagsInCells(self, cells):
		bags = []
		for cell in _iter(cells):
			if (cell in self.bagCells):
				bag = self.bagCells[cell]
				if not bag in bags:
					bags.append(bag)

		return bags


	# 对齐 Inventory.gd:686-696
	@staticmethod
	def getCellsInLine(cells, direction, distance=7):
		lineCells = []
		for cell in _iter(cells):
			for offset in _iter(_gd_range(1, distance + 1)):
				neighbor = cell + direction * offset

				if (not neighbor in cells and 
					not neighbor in lineCells):
					lineCells.append(neighbor)

		return lineCells


	# 对齐 Inventory.gd:698-709（四邻域去重，排除自身占格）
	@staticmethod
	def getAdjacentCells(cells):
		adjacentCells = []
		for cell in _iter(cells):
			for offset in _iter([Vector2.RIGHT, Vector2.LEFT, Vector2.UP, Vector2.DOWN]):
				neighbor = cell + offset

				if (not neighbor in cells and 
					not neighbor in adjacentCells):
					adjacentCells.append(neighbor)

		return adjacentCells


	# 对齐 Inventory.gd:712-713
	def getAdjacentItems(self, item):
		return self.getItemsInCells(self.getAdjacentCells(item.occupiedCells))


	# ─────────────────────── 全背包批量施加（对齐 Inventory.gd:1299-1308） ───────────────────────
	# 这两个是**判定路径**：Solaris.onPrepare 用 changeBuffAmplification_allItems 把
	# 灼热(buffType=Heat)的加成概率分发给全背包物品，进而影响后续每一次 buff 施加
	# —— 缺了它 Solaris 的整套增益静默不生效（`Nonexistent function` 只打印一行
	# SCRIPT ERROR 然后中断该函数，退出码看不出来）。
	# ★ 遍历口径必须与 getItemsAndGems 一致（物品 + 其插槽内的宝石）。

	# 对齐 Inventory.gd:1295-1297
	def countSocketedGems(self):
		numGems = 0
		for item in _iter(self.items):
			numGems += len(item.getGemsNoNull())
		return numGems


	# 对齐 Inventory.gd:1299-1302
	def changeBuffPower_allItems(self, buffType, amount):
		for item in _iter(self.getItemsAndGems()):
			item.giveBuffPower(buffType, amount)


	# 对齐 Inventory.gd:1304-1308
	def changeBuffAmplification_allItems(self, buffType, amount):
		for item in _iter(self.getItemsAndGems()):
			item.changeAmplificiationChancePercent(buffType, amount)


	# ─────────────────────── 内核装配接口（对齐 Inventory.gd:609-627） ───────────────────────

	# 对齐 Inventory.gd:621-627 —— 只写格子映射
	def addItemCells(self, item, cells):
		if item.isBag():
			for cell in _iter(cells):
				self.bagCells[cell] = item
		else:
			for cell in _iter(cells):
				self.filledCells[cell] = item


	# 对齐 Inventory.gd:609-616。recalculateTilemap() 与 Game.onInventoryChanged()
	# 分别是 TileMap 重绘与全局刷新（表现/元进程）→ 剥离；其余步骤次序逐字保留，
	# 因为 emit_signal("item_added", item) 的**时机**决定了每个物品
	# currentAffectedItems 的键插入顺序（影响 getFirstAffectedItem 的取首项）。
	def addItem(self, item, cells, placedByPlayer=False):
		self.addItemCells(item, cells)
		self.items.append(item)
		item.addToInventory(self, cells, placedByPlayer)

		# emit_signal("item_added", item) —— 所有已登记物品都会收到 onItemAdded
		for other in _iter(self.items):
			other.onItemAdded(item)


	# 对齐 Inventory.gd:629-636 + 移除通知
	def removeItem(self, item, cells, isBag=False):
		self.clearItemCells(item)
		idx = _find(self.items, item)
		if idx >= 0:
			_pop_at(self.items, idx)
		for other in _iter(self.items):
			other.onItemRemoved(item)


	# 对齐 Inventory.gd:629-636
	def clearItemCells(self, item):
		for cell in _iter(item.occupiedCells):
			if item.isBag():
				if self.bagCells.get(cell, None) == item:
					_erase(self.bagCells, cell)
			else:
				if self.filledCells.get(cell, None) == item:
					_erase(self.filledCells, cell)


	# 对齐 Inventory.gd:971-972。原版 emit_signal("item_type_changed", item)，各物品在
	# 装备时（Item.gd:1333）把**自己的** onItemTypeChanged 连到这个信号上，于是
	# 「任一物品类型变化」→ 全背包物品都收到通知并重建受影响集。
	# 内核无信号，直接按**同一次序**逐件派发（items 的 push 次序 = 连接次序）。
	def onItemTypeChanged(self, item):
		for other in _iter(self.items):
			other.onItemTypeChanged(item)


	def cleanUp(self):
		self.filledCells.clear()
		self.bagCells.clear()
		self.items.clear()
		self.curHovered.clear()


_R.reg("res://gd_core/CoreGrid.gd", CoreGrid)
_R.reg("CoreGrid", CoreGrid)
_R.reg("CoreGrid", CoreGrid)
