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
extends Reference
class_name CoreGrid


# 对齐 Inventory.gd:51-56 的字段（子集）
var filledCells: Dictionary = {}   # cell(Vector2) → item
var bagCells: Dictionary = {}      # cell(Vector2) → bag
var items: Array = []
var character = null
var curHovered: Dictionary = {}    # 拖拽预览用；内核战斗路径不写入


func _init(_character = null) -> void :
	character = _character


# 对齐 Inventory.gd:377-381 —— 内核里点集与格集在格点上互逆，
# 故本方法直接返回传入的格（见文件头坐标系约定）。
func getCellsForGlobalPositions(points: Array) -> Array:
	return points


# 对齐 Inventory.gd:368-369
func getItems() -> Array:
	return items


# 对齐 Inventory.gd:371-375
func getItemsAndGems() -> Array:
	var itemsAndGems = items.duplicate()
	for item in items:
		itemsAndGems.append_array(item.getGemsNoNull())
	return itemsAndGems


# 对齐 Inventory.gd:269-272
func isHovered(cell: Vector2) -> bool:
	return cell in curHovered


# 对齐 Inventory.gd:716-717
func isCellEmpty(cell: Vector2) -> bool:
	return cell in bagCells and not cell in filledCells


# 对齐 Inventory.gd:719-724
func getEmptyCellsInCells(cells):
	var num = 0
	for cell in cells:
		if isCellEmpty(cell):
			num += 1
	return num


# 对齐 Inventory.gd:726-727
func getItemInCell(cell: Vector2):
	return filledCells.get(cell, null)


# 对齐 Inventory.gd:729-739
func getItemsInCells(cells) -> Array:
	var itemsInCells = []
	for cell in cells:
		if filledCells.has(cell):
			var item = filledCells[cell]
			if not item in itemsInCells and item.placed:
				itemsInCells.push_back(item)
	
	return itemsInCells


# 对齐 Inventory.gd:742-747（Util.dictAdd 记的是「物品 → 命中格数」）
func countItemsInCells(cells) -> Dictionary:
	var itemCounter = {}
	for cell in cells:
		if filledCells.has(cell):
			CoreUtil.dictAdd(itemCounter, filledCells[cell])
	return itemCounter


# 对齐 Inventory.gd:749-757
func getBagsInCells(cells):
	var bags = []
	for cell in cells:
		if bagCells.has(cell):
			var bag = bagCells[cell]
			if not bag in bags:
				bags.push_back(bag)
	
	return bags


# 对齐 Inventory.gd:686-696
static func getCellsInLine(cells, direction: Vector2, distance = 7):
	var lineCells = []
	for cell in cells:
		for offset in range(1, distance + 1):
			var neighbor = cell + direction * offset
			
			if (not neighbor in cells and 
				not neighbor in lineCells):
				lineCells.push_back(neighbor)
	
	return lineCells


# 对齐 Inventory.gd:698-709（四邻域去重，排除自身占格）
static func getAdjacentCells(cells):
	var adjacentCells = []
	for cell in cells:
		for offset in [Vector2.RIGHT, Vector2.LEFT, Vector2.UP, Vector2.DOWN]:
			var neighbor = cell + offset
			
			if (not neighbor in cells and 
				not neighbor in adjacentCells):
				adjacentCells.push_back(neighbor)
	
	return adjacentCells


# 对齐 Inventory.gd:712-713
func getAdjacentItems(item):
	return getItemsInCells(getAdjacentCells(item.occupiedCells))


# ─────────────────────── 全背包批量施加（对齐 Inventory.gd:1299-1308） ───────────────────────
# 这两个是**判定路径**：Solaris.onPrepare 用 changeBuffAmplification_allItems 把
# 灼热(buffType=Heat)的加成概率分发给全背包物品，进而影响后续每一次 buff 施加
# —— 缺了它 Solaris 的整套增益静默不生效（`Nonexistent function` 只打印一行
# SCRIPT ERROR 然后中断该函数，退出码看不出来）。
# ★ 遍历口径必须与 getItemsAndGems 一致（物品 + 其插槽内的宝石）。

# 对齐 Inventory.gd:1295-1297
func countSocketedGems():
	var numGems = 0
	for item in items:
		numGems += item.getGemsNoNull().size()
	return numGems


# 对齐 Inventory.gd:1299-1302
func changeBuffPower_allItems(buffType, amount) -> void :
	for item in getItemsAndGems():
		item.giveBuffPower(buffType, amount)


# 对齐 Inventory.gd:1304-1308
func changeBuffAmplification_allItems(buffType, amount) -> void :
	for item in getItemsAndGems():
		item.changeAmplificiationChancePercent(buffType, amount)


# ─────────────────────── 内核装配接口（对齐 Inventory.gd:609-627） ───────────────────────

# 对齐 Inventory.gd:621-627 —— 只写格子映射
func addItemCells(item, cells: Array) -> void :
	if item.isBag():
		for cell in cells:
			bagCells[cell] = item
	else:
		for cell in cells:
			filledCells[cell] = item


# 对齐 Inventory.gd:609-616。recalculateTilemap() 与 Game.onInventoryChanged()
# 分别是 TileMap 重绘与全局刷新（表现/元进程）→ 剥离；其余步骤次序逐字保留，
# 因为 emit_signal("item_added", item) 的**时机**决定了每个物品
# currentAffectedItems 的键插入顺序（影响 getFirstAffectedItem 的取首项）。
func addItem(item, cells, placedByPlayer: bool = false) -> void :
	addItemCells(item, cells)
	items.push_back(item)
	item.addToInventory(self, cells, placedByPlayer)
	
	# emit_signal("item_added", item) —— 所有已登记物品都会收到 onItemAdded
	for other in items:
		other.onItemAdded(item)


# 对齐 Inventory.gd:629-636 + 移除通知
func removeItem(item, cells: Array, isBag: bool = false) -> void :
	clearItemCells(item)
	var idx = items.find(item)
	if idx >= 0:
		items.remove(idx)
	for other in items:
		other.onItemRemoved(item)


# 对齐 Inventory.gd:629-636
func clearItemCells(item) -> void :
	for cell in item.occupiedCells:
		if item.isBag():
			if bagCells.get(cell, null) == item:
				bagCells.erase(cell)
		else:
			if filledCells.get(cell, null) == item:
				filledCells.erase(cell)


# 对齐 Inventory.gd:971-972。原版 emit_signal("item_type_changed", item)，各物品在
# 装备时（Item.gd:1333）把**自己的** onItemTypeChanged 连到这个信号上，于是
# 「任一物品类型变化」→ 全背包物品都收到通知并重建受影响集。
# 内核无信号，直接按**同一次序**逐件派发（items 的 push 次序 = 连接次序）。
func onItemTypeChanged(item) -> void :
	for other in items:
		other.onItemTypeChanged(item)


func cleanUp() -> void :
	filledCells.clear()
	bagCells.clear()
	items.clear()
	curHovered.clear()
