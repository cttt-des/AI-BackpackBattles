# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreConst(GodotObject):

	resource_path = "res://gd_core/CoreConst.gd"

	EventType = EnumDict("EventType", {"Activation": 0, "DealDamage": 1, "CriticalDamage": 2, "MissedAttack": 3, "TakeDamage": 4, "LoseHealth": 5, "AttackSpeed": 6, "InvulnerableStart": 7, "InvulnerableEnd": 8, "Stun": 9, "StunResisted": 10, "CriticalResisted": 11, "Health": 12, "Stamina": 13, "DrainStamina": 14, "OutofStamina": 15, "DamageBuff": 16, "DamReduction": 17, "DamIncrease": 18, "TemporaryMaxHealth": 19, "TemporaryMaxStamina": 20, "BattleRageStart": 21, "BattleRageEnd": 22, "Reincarnate": 23, "CooldownAdvance": 24, "Unhealing": 98, "Fatigue": 99, "Block": 100, "Lucky": 101, "Regeneration": 102, "Vampirism": 103, "Spikes": 104, "Mana": 105, "Empower": 106, "Heat": 107, "Poison": 108, "Blind": 109, "Cold": 110, "Win": 111, "Loss": 112})

	ItemMetrics = EnumDict("ItemMetrics", {"Damage": 0, "Heal": 1, "Overheal": 2, "Misses": 3, "Activations": 4, "DamageBlocked": 5, "MaxHealth": 6, "OutOfStamina": 7, "Stamina": 8, "Block": 9, "Lucky": 10, "Regeneration": 11, "Vampirism": 12, "Spikes": 13, "Mana": 14, "Empower": 15, "Heat": 16, "Poison": 17, "Blind": 18, "Cold": 19})

	CharID = EnumDict("CharID", {"PLAYER": 0, "OPPONENT": 1})

	StaminaResult = EnumDict("StaminaResult", {"Sufficient": 0, "Insufficient": 1})

	ItemStat = EnumDict("ItemStat", {"MinDamage": 0, "MaxDamage": 1, "StaminaCost": 2, "Speed": 3, "BaseCooldown": 4, "Accuracy": 5, "CritChance": 6, "Chance": 7, "Chance2": 8, "Cooldown": 9})

	Rarity = EnumDict("Rarity", {"Common": 0, "Rare": 1, "Epic": 2, "Legendary": 3, "Godly": 4, "Unique": 5})

	StuffedClasses = EnumDict("StuffedClasses", {"Undefined": -1, "None": 0, "Ranger": 1, "Reaper": 2, "Berserker": 4, "Pyromancer": 8, "Mage": 16, "Adventurer": 32, "Engineer": 64, "Neutral": 127})

	Owner = EnumDict("Owner", {"Shop": 0, "PlayerInventory": 1, "PlayerStorageBox": 2, "Opponent": 3, "Title": 4, "RecipeBook": 5, "Tooltip": 6, "Socket": 7, "ItemLibrary": 8, "InfoPanelIcon": 9, "BuildViewer": 10, "BuildViewerIcon": 11, "GridStorage": 12, "Undefined": 13})

	GameMode = EnumDict("GameMode", {"Ranked": 0, "Unranked": 1, "Lobbies": 2, "Unselected": 3, "History": 4})

	Affected = EnumDict("Affected", {"Primary": 0, "Secondary": 1, "Tertiary": 2, "Lightning": 3})

	Stack = EnumDict("Stack", {"None": 0, "Block": 1, "Lucky": 2, "Regeneration": 4, "Vampirism": 8, "Spikes": 16, "Mana": 32, "Empower": 64, "Heat": 128, "Poison": 256, "Blind": 512, "Cold": 1024, "Buff": 254, "Debuff": 1792, "BuffNoLuck": 252})

	Tag = EnumDict("Tag", {"None": 0, "Lifesteal": 1, "Stone": 2, "Scroll": 8, "Dragon": 16, "Staff": 32, "BattleRage": 64, "Singular": 128, "Transient": 256, "Bow": 512})

	Priority = EnumDict("Priority", {"Lowest": -10000, "Low": -1000, "Normal": 0, "High": 1000, "Highest": 10000})

	StackChangeType = EnumDict("StackChangeType", {"Added_Player": 0, "Added_Opponent": 1, "Removed_Player": 2, "Removed_Opponent": 3, "Used_Player": 4, "Used_Opponent": 5})

	StatModified = EnumDict("StatModified", {"No": 0, "Positive": 1, "Negative": 2})

	FaceDirection = EnumDict("FaceDirection", {"UP": 0, "RIGHT": 1, "DOWN": 2, "LEFT": 3})

	Classes = EnumDict("Classes", {"Ranger": 0, "Reaper": 1, "Berserker": 2, "Pyromancer": 3})

	Classes_Full = EnumDict("Classes_Full", {"Ranger": 0, "Reaper": 1, "Berserker": 2, "Pyromancer": 3, "Mage": 4, "Adventurer": 5, "Engineer": 6})

	Type = EnumDict("Type", {"Bag": 0, "Consumable": 1, "Food": 2, "Pet": 3, "Weapon": 4, "Shield": 5, "Armor": 6, "Gloves": 7, "Shoes": 8, "Helmet": 9, "Accessory": 10, "Potion": 11, "Card": 12, "Gem": 13, "Scroll": 14, "Book": 15, "Skill": 16, "ChessPiece": 17, "Spell": 18, "Melee": 19, "Ranged": 20, "Effect": 21, "Holy": 22, "Magic": 23, "Vampiric": 24, "Dark": 25, "Nature": 26, "Fire": 27, "Ice": 28, "Musical": 29})



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


	# ── 对齐 Game.gd:441-484 ──


	# ── 对齐 Game.gd:488-511 ──


	# ── 对齐 Character.gd:14-17（ID）与 Character.gd:616-619（StaminaResult） ──
	# ★ 为什么放在这里：这两个枚举被 CoreItem 使用。若 CoreItem 直接写
	#   `CoreCharacter.ID.PLAYER`，就会形成 CoreItem ↔ CoreCharacter 的 class_name
	#   循环依赖（GDScript 3 禁止，会报 "couldn't be fully loaded / cyclic dependency"）。
	#   收拢到零依赖的 CoreConst 后取值与原版逐项相同，判定不变。
	#   工具：tools/check_class_cycles.py 负责守住这条约束。




	# ── 对齐 Items/Item.gd:241-252（Item.Stat） ──
	# ★ 为什么放在这里：CoreCharacter 的快照出口需要用 Item.Stat 作下标
	#   （Character.gd:1509-1517 的 snapshotItemTooltipStat(item, Item.Stat.MinDamage)）。
	#   若 CoreCharacter 直接写 `CoreItem.Stat`，就会形成 CoreItem ↔ CoreCharacter 的
	#   class_name 循环依赖。收拢到零依赖的 CoreConst 后取值与原版逐项相同。
	#   原 CoreItem.Stat 已改为引用本枚举，全仓库只此一处定义。


	# ── 对齐 Items/Item.gd:148-155（Item.Rarity） ──


	# ── 对齐 Items/ItemDescriptor.gd:4-15（ItemDescriptor.StuffedClasses） ──
	# 收拢到 CoreConst 的理由同上：CoreItemData / CoreItem 都要用它，
	# 放在任一方都会引入 CoreItemData ↔ CoreItem 的 class_name 互相引用。


	# ── 对齐 Items/Item.gd:23-38（Item.Owner） ──
	# 内核里物品只可能属于玩家的背包/储物箱或对手，故 ownerType 由 Character 推出
	# （见 CoreCombat.prepareItems）。判定读取点 isOwnable / isOwnedByOpponent
	# 的取值域与原版一致。


	# ── 对齐 Core/Game.gd:148-154（Game.Mode） ──
	# 消费方：ChessBoard.onPrepare 的 `Game.curMode != Game.Mode.History`。
	# 无头内核不模拟局外流程，ctx.cur_mode 默认 Ranked（≠ History）。


	# ── 对齐 Items/Item.gd:118-124（Item.Affected） ──
	# 联动颜色：主/次/三级 + 闪电。物品行为的 canAffect_color / getAffectedItems 以它取色。


	# 真值化（GDScript 3.x 没有 bool() 构造函数，那是 4.x 才有的内置转换）。
	# 语义 = GDScript 自身的条件真值：null/false/0/0.0/""/空容器 → false，其余 → true。
	# ★ 放在零依赖的 CoreConst 上，是为了让 CoreUtil 与 CoreItemData 都能用它而**不互相引用**
	#   （两者互相引用会构成 class_name 依赖环，Godot 3 会拒绝加载）。
	@staticmethod
	def truth(v):
		if v:
			return True
		return False


	# 对齐 Game.gd:5643-5644
	@staticmethod
	def getStacks():
		return [CoreConst.EventType.Block] + CoreConst.getBuffs() + CoreConst.getDebuffs()


	# 对齐 Game.gd:5647-5648
	@staticmethod
	def getBuffs():
		return _gd_range(CoreConst.EventType.Lucky, CoreConst.EventType.Heat + 1)


	# 对齐 Game.gd:5650-5651
	@staticmethod
	def getDebuffs():
		return _gd_range(CoreConst.EventType.Poison, CoreConst.EventType.Cold + 1)


	# 对齐 Game.gd:5654-5655
	@staticmethod
	def isBuff(_type):
		return _type >= CoreConst.EventType.Block and _type <= CoreConst.EventType.Heat


	# 对齐 Game.gd:5657-5658
	@staticmethod
	def isDebuff(_type):
		return _type >= CoreConst.EventType.Poison and _type <= CoreConst.EventType.Cold


	# 对齐 Game.gd:5660-5661
	@staticmethod
	def isStack(_type):
		return _type >= CoreConst.EventType.Block and _type <= CoreConst.EventType.Cold


	# 对齐 Game.gd:486 `var numStackTypes = getStacks().size()`
	@staticmethod
	def numStackTypes():
		return len(CoreConst.getStacks())


	# ── 对齐 Item.gd:109-111 Stack 位掩码（供 gain/remove/use 标志判定） ──


	# ── 对齐 Item.gd:83-94 Tag 位掩码 ──


	# ── 对齐 Item.gd:69-75 Priority ──


	# ── 对齐 Item.gd:259-266 StackChangeType ──


	# ── 对齐 Item.gd:164-168 StatModified ──


	# ── 对齐 Item.gd:157-162 FaceDirection ──
	# ★ 战斗判定输入：放置期由 Inventory.orientItem → setFaceDirectionInstant 写入，
	#   战斗期**只读**（rotateLeft/rotateRight 只由玩家按键触发，战斗中不可用）。
	#   SpintoWin.doCooldownEffect/gainsStack 按方向分流给 heat/lucky/regen/mana；
	#   LongSpear/RainbowPotion 也按方向分流。故内核必须持有该字段。


	# ── 对齐 Game.gd:131-146（职业） ──
	# 消费方：Character.setClass/setClassResource（职业资源决定 maxHealth / baseMaxStamina）。



	# ── 对齐 Item.gd:34-67 Type ──


_R.reg("res://gd_core/CoreConst.gd", CoreConst)
_R.reg("CoreConst", CoreConst)
_R.reg("CoreConst", CoreConst)
