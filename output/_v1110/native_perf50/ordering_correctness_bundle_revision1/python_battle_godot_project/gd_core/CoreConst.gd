# =============================================================================
# CoreConst.gd — 无头战斗内核：全局枚举与栈语义
# =============================================================================
# 对齐源码（Core/Game.gd）：
#   EventType          Game.gd:441-484
#   ItemMetrics        Game.gd:488-511
#   numStackTypes      Game.gd:486
#   getStacks()        Game.gd:5643-5644
#   getBuffs()         Game.gd:5647-5648
#   getDebuffs()       Game.gd:5650-5651
#   isBuff/isDebuff/isStack  Game.gd:5654-5661
#
# 剥离内容：
#   · typeToKeyword / eventTypeKeys / Util.tra / Util.getIcon —— 纯文本渲染，剔除；
#     文本由日志层钩子（CoreHooks）另行生成，不参与任何判定。
# =============================================================================
extends Reference
class_name CoreConst


# ── 对齐 Game.gd:441-484 ──
enum EventType{
	Activation, 
	DealDamage, 
	CriticalDamage, 
	MissedAttack, 
	TakeDamage, 
	LoseHealth, 
	AttackSpeed, 
	InvulnerableStart, 
	InvulnerableEnd, 
	Stun, 
	StunResisted, 
	CriticalResisted, 
	Health, 
	Stamina, 
	DrainStamina, 
	OutofStamina, 
	DamageBuff, 
	DamReduction, 
	DamIncrease, 
	TemporaryMaxHealth, 
	TemporaryMaxStamina, 
	BattleRageStart, 
	BattleRageEnd, 
	Reincarnate, 
	CooldownAdvance, 
	Unhealing = 98, 
	Fatigue = 99, 
	Block = 100, 
	Lucky = 101, 
	Regeneration = 102, 
	Vampirism = 103, 
	Spikes = 104, 
	Mana = 105, 
	Empower = 106, 
	Heat = 107, 
	Poison = 108, 
	Blind = 109, 
	Cold = 110, 
	Win = 111, 
	Loss
}


# ── 对齐 Game.gd:488-511 ──
enum ItemMetrics{
	Damage, 
	Heal, 
	Overheal, 
	Misses, 
	Activations, 
	DamageBlocked, 
	MaxHealth, 
	OutOfStamina, 
	Stamina, 
	Block, 
	Lucky, 
	Regeneration, 
	Vampirism, 
	Spikes, 
	Mana, 
	Empower, 
	Heat, 
	Poison, 
	Blind, 
	Cold
}


# ── 对齐 Character.gd:14-17（ID）与 Character.gd:616-619（StaminaResult） ──
# ★ 为什么放在这里：这两个枚举被 CoreItem 使用。若 CoreItem 直接写
#   `CoreCharacter.ID.PLAYER`，就会形成 CoreItem ↔ CoreCharacter 的 class_name
#   循环依赖（GDScript 3 禁止，会报 "couldn't be fully loaded / cyclic dependency"）。
#   收拢到零依赖的 CoreConst 后取值与原版逐项相同，判定不变。
#   工具：tools/check_class_cycles.py 负责守住这条约束。
enum CharID{
	PLAYER = 0, 
	OPPONENT = 1
}


enum StaminaResult{
	Sufficient, 
	Insufficient
}


# ── 对齐 Items/Item.gd:241-252（Item.Stat） ──
# ★ 为什么放在这里：CoreCharacter 的快照出口需要用 Item.Stat 作下标
#   （Character.gd:1509-1517 的 snapshotItemTooltipStat(item, Item.Stat.MinDamage)）。
#   若 CoreCharacter 直接写 `CoreItem.Stat`，就会形成 CoreItem ↔ CoreCharacter 的
#   class_name 循环依赖。收拢到零依赖的 CoreConst 后取值与原版逐项相同。
#   原 CoreItem.Stat 已改为引用本枚举，全仓库只此一处定义。
enum ItemStat{
	MinDamage, 
	MaxDamage, 
	StaminaCost, 
	Speed, 
	BaseCooldown, 
	Accuracy, 
	CritChance, 
	Chance, 
	Chance2, 
	Cooldown
}


# ── 对齐 Items/Item.gd:148-155（Item.Rarity） ──
enum Rarity{
	Common = 0, 
	Rare = 1, 
	Epic = 2, 
	Legendary = 3, 
	Godly = 4, 
	Unique = 5
}


# ── 对齐 Items/ItemDescriptor.gd:4-15（ItemDescriptor.StuffedClasses） ──
# 收拢到 CoreConst 的理由同上：CoreItemData / CoreItem 都要用它，
# 放在任一方都会引入 CoreItemData ↔ CoreItem 的 class_name 互相引用。
enum StuffedClasses{
	Undefined = - 1, 
	None = 0, 
	Ranger = 1, 
	Reaper = 2, 
	Berserker = 4, 
	Pyromancer = 8, 
	Mage = 16, 
	Adventurer = 32, 
	Engineer = 64, 
	Neutral = 127
}


# ── 对齐 Items/Item.gd:23-38（Item.Owner） ──
# 内核里物品只可能属于玩家的背包/储物箱或对手，故 ownerType 由 Character 推出
# （见 CoreCombat.prepareItems）。判定读取点 isOwnable / isOwnedByOpponent
# 的取值域与原版一致。
enum Owner{
	Shop, 
	PlayerInventory, 
	PlayerStorageBox, 
	Opponent, 
	Title, 
	RecipeBook, 
	Tooltip, 
	Socket, 
	ItemLibrary, 
	InfoPanelIcon, 
	BuildViewer, 
	BuildViewerIcon, 
	GridStorage, 
	Undefined
}


# ── 对齐 Core/Game.gd:148-154（Game.Mode） ──
# 消费方：ChessBoard.onPrepare 的 `Game.curMode != Game.Mode.History`。
# 无头内核不模拟局外流程，ctx.cur_mode 默认 Ranked（≠ History）。
enum GameMode{
	Ranked = 0, 
	Unranked = 1, 
	Lobbies = 2, 
	Unselected = 3, 
	History = 4
}


# ── 对齐 Items/Item.gd:118-124（Item.Affected） ──
# 联动颜色：主/次/三级 + 闪电。物品行为的 canAffect_color / getAffectedItems 以它取色。
enum Affected{
	Primary, 
	Secondary, 
	Tertiary, 
	Lightning
}


# 真值化（GDScript 3.x 没有 bool() 构造函数，那是 4.x 才有的内置转换）。
# 语义 = GDScript 自身的条件真值：null/false/0/0.0/""/空容器 → false，其余 → true。
# ★ 放在零依赖的 CoreConst 上，是为了让 CoreUtil 与 CoreItemData 都能用它而**不互相引用**
#   （两者互相引用会构成 class_name 依赖环，Godot 3 会拒绝加载）。
static func truth(v) -> bool:
	if v:
		return true
	return false


# 对齐 Game.gd:5643-5644
static func getStacks() -> Array:
	return [EventType.Block] + getBuffs() + getDebuffs()


# 对齐 Game.gd:5647-5648
static func getBuffs() -> Array:
	return range(EventType.Lucky, EventType.Heat + 1)


# 对齐 Game.gd:5650-5651
static func getDebuffs() -> Array:
	return range(EventType.Poison, EventType.Cold + 1)


# 对齐 Game.gd:5654-5655
static func isBuff(_type) -> bool:
	return _type >= EventType.Block and _type <= EventType.Heat


# 对齐 Game.gd:5657-5658
static func isDebuff(_type) -> bool:
	return _type >= EventType.Poison and _type <= EventType.Cold


# 对齐 Game.gd:5660-5661
static func isStack(_type) -> bool:
	return _type >= EventType.Block and _type <= EventType.Cold


# 对齐 Game.gd:486 `var numStackTypes = getStacks().size()`
static func numStackTypes() -> int:
	return getStacks().size()


# ── 对齐 Item.gd:109-111 Stack 位掩码（供 gain/remove/use 标志判定） ──
enum Stack{
	None = 0, 
	Block = 1, 
	Lucky = 2, 
	Regeneration = 4, 
	Vampirism = 8, 
	Spikes = 16, 
	Mana = 32, 
	Empower = 64, 
	Heat = 128, 
	Poison = 256, 
	Blind = 512, 
	Cold = 1024, 
	Buff = 128 + 64 + 32 + 16 + 8 + 4 + 2, 
	Debuff = 1024 + 512 + 256, 
	BuffNoLuck = 128 + 64 + 32 + 16 + 8 + 4
}


# ── 对齐 Item.gd:83-94 Tag 位掩码 ──
enum Tag{
	None = 0, 
	Lifesteal = 1, 
	Stone = 2, 
	Scroll = 8, 
	Dragon = 16, 
	Staff = 32, 
	BattleRage = 64, 
	Singular = 128, 
	Transient = 256, 
	Bow = 512
}


# ── 对齐 Item.gd:69-75 Priority ──
enum Priority{
	Lowest = - 10000, 
	Low = - 1000, 
	Normal = 0, 
	High = 1000, 
	Highest = 10000
}


# ── 对齐 Item.gd:259-266 StackChangeType ──
enum StackChangeType{
	Added_Player, 
	Added_Opponent, 
	Removed_Player, 
	Removed_Opponent, 
	Used_Player, 
	Used_Opponent
}


# ── 对齐 Item.gd:164-168 StatModified ──
enum StatModified{
	No = 0, 
	Positive = 1, 
	Negative = 2
}


# ── 对齐 Item.gd:157-162 FaceDirection ──
# ★ 战斗判定输入：放置期由 Inventory.orientItem → setFaceDirectionInstant 写入，
#   战斗期**只读**（rotateLeft/rotateRight 只由玩家按键触发，战斗中不可用）。
#   SpintoWin.doCooldownEffect/gainsStack 按方向分流给 heat/lucky/regen/mana；
#   LongSpear/RainbowPotion 也按方向分流。故内核必须持有该字段。
enum FaceDirection{
	UP = 0, 
	RIGHT = 1, 
	DOWN = 2, 
	LEFT = 3
}


# ── 对齐 Game.gd:131-146（职业） ──
# 消费方：Character.setClass/setClassResource（职业资源决定 maxHealth / baseMaxStamina）。
enum Classes{
	Ranger = 0, 
	Reaper = 1, 
	Berserker = 2, 
	Pyromancer = 3
}

enum Classes_Full{
	Ranger = 0, 
	Reaper = 1, 
	Berserker = 2, 
	Pyromancer = 3, 
	Mage = 4, 
	Adventurer = 5, 
	Engineer = 6
}


# ── 对齐 Item.gd:34-67 Type ──
enum Type{
	Bag, 
	Consumable, 
	Food, 
	Pet, 
	Weapon, 
	Shield, 
	Armor, 
	Gloves, 
	Shoes, 
	Helmet, 
	Accessory, 
	Potion, 
	Card, 
	Gem, 
	Scroll, 
	Book, 
	Skill, 
	ChessPiece, 
	Spell, 
	Melee, 
	Ranged, 
	Effect, 
	Holy, 
	Magic, 
	Vampiric, 
	Dark, 
	Nature, 
	Fire, 
	Ice, 
	Musical
}
