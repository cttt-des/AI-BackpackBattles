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
