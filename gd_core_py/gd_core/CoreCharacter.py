# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreCharacter(GodotObject):

	resource_path = "res://gd_core/CoreCharacter.gd"

	ID = EnumDict("ID", {"PLAYER": 0, "OPPONENT": 1})

	Stat = EnumDict("Stat", {"Health": 0, "MaxHealth": 1, "Stamina": 2, "MaxStamina": 3, "Invulnerable": 4, "Stunned": 5, "BattleRage": 6, "ReflectStacks": 7, "DebuffResistStacks": 8, "CritStacks": 9, "DodgeStacks": 10, "CritResistStacks": 11, "CritResistance": 12, "StunResistance": 13, "HealEfficiency": 14, "DamageResistance": 15, "MeleeDmgFactor": 16, "RangedDmgFactor": 17, "EffectDmgFactor": 18, "Unhealing": 19, "StaminaRegen": 20, "MaxHealthGain": 21})

	StaminaResult = EnumDict("StaminaResult", {"Sufficient": 0, "Insufficient": 1})



	def _init_fields(self):
		super()._init_fields()
		self.ctx = None
		self.playerId = 0
		self.opponent = None
		self.isDead = False
		self.buffs = {}
		self.maxHealth = 30.0
		self.curHealth = 0.0
		self.temporaryMaxHealth = 0.0
		self.temporaryMaxHealthGain = 1.0
		self.baseMaxStamina = 0.0
		self.maxStamina = 5.0
		self.curStamina = 0.0
		self.temporaryMaxStamina = 0.0
		self.baseStaminaRegen = 1.0
		self.staminaRegen = 0.0
		self.allowStaminaOverflow = False
		self.staminaUpdateQueued = False   # 对齐 Character.gd:971
		self.statsDisplay = []      # 仅统计出口
		self.damageResistance = 0.0
		self.damageReduction = 0
		self.invulnerable = False
		self.dodgeStacks = 0
		self.critResistance = 0.0
		self.critResistStacks = 0
		self.critTokens = 0
		self.stunResistance = 0.0
		self.unhealingAmount = 0.0
		self.healingEfficiency = 1.0
		self.critTokensUsed = 0
		self.debuffResistStacks = 0
		self.debuffReflectStacks = 0
		self.buffProtectStacks = 0
		self.bonusFatigueDamage = 0
		self.empowerDamage = 1.0
		self.blindingLightActive = False
		self.stunnedDuration = 0.0
		self.tickCounter = 0
		self.typedDamageFactors = {}
		self.meleeSpikesLimit = 1.0
		self.rangedSpikesLimit = 0.0
		self.effectSpikesLimit = 0.0
		self.meleeVampirismLimit = 1.0
		self.rangedVampirismLimit = 0.0
		self.battleRageAura = None         # 表现
		self.battleRageBonusDur = 0.0
		self.accuracyRng = None
		self.critRng = None
		self.critResistanceRng = None
		self.stunResistanceRng = None
		self.items = []             # 该角色的参战物品（替代 INVENTORY.getItems()）
		self.inventory = None
		self.INVENTORY = None
		self.character_died_handlers = []
		self.poisonDamageSource = None
		self.spikeDamageSource = None
		self.characterClass = _R.C("CoreConst").Classes.Ranger
		self.chibi = False
		self.invulnerabilityItem = None
		self._invul_left = 0.0
		self._invul_active = False
		self.autoRageItem = None           # 对齐 Character.gd:110（prepare 时从未带 BattleRage 标签的物品里随机选一个）
		self._rage_left = 0.0
		self._rage_active = False
		self._autoRage_left = 0.0
		self._autoRage_active = False

	# =============================================================================
	# CoreCharacter.gd — 无头战斗内核：角色（伤害链 / 体力 / 栈宿主）
	# =============================================================================
	# 对齐源码：Core/Character.gd（全文 1700 行）
	#
	# 逐字保留（本内核的判定主体）：
	#   takeDamage 全链 17 步（Character.gd:495-653，顺序即真值）：
	#     isDead 短路 → attackEffectCount=1+rollDoubleAttackEffect → 命中(accuracyRng/闪避栈)
	#     → preDealDamage_early × count → randDamage（含疲劳加成）→ 暴击（critRng → 攻方
	#       critTokens → 守方 critTokens 代打 → critResisted）→ 抗性 clamp(-10,1) 后 round
	#     → isAttack 才减 damageReduction → invulnerable 归零 → pre_take_damage 信号
	#       （盾牌挂钩）→ 减 damageReduction 并 max(0) → preDealDamage_late × count
	#     → pre_take_damage_late → 格挡（先扣 block，healthDamage=0 或扣血）→ 扣血
	#     → 事件 → character_attacked / character_damaged → onDealtDamage × count
	#     → 死亡判定 → applySpikes
	#   dealDamage / applyVampirism / applySpikes / heal（healingEfficiency + Unhealing 反噬）
	#   loseHealth（不吃减伤）/ useStamina（allowStaminaOverflow 窗口）/ addStamina /
	#   gainStamina / drainStamina / onTick（偶数秒再生、奇数秒毒伤）/ stun / critResisted /
	#   onTick 与疲劳伤害入口 takeFatigueDamage / getMaxHealth / changeMaxHealthTemporary
	#
	# 保真保留的原版疑点（不修）：
	#   · `setBlock(amount)` 实际写入的是 **Spikes** 栈（Character.gd:1182-1183 原样如此）
	#   · `gainStacks(buffType, ..., reflect)` 忽略 reflect，直接转发 buffs[buffType].gainStacks
	#   · `setCurrentHealth` 不做 clamp
	#
	# 剥离内容：动画 / 音效 / 伤害数字与 buff 标签 / 立绘 / 相机 / HUD 信号
	#   → 全部改走 ctx.hooks；伤害数字坐标（randDmgNumberPos 等）整体删除（纯表现）
	#
	# 本期未实现、以接缝占位：
	#   · 战怒（AUTO_RAGE 5s/4s）—— 需要 isBattleRageItem 的物品行为判定，随物品行为一起接
	#   · invulnerabilityTimer / 自动 rage 计时器 —— 需要内核计时驱动，接入点已留（`_tick`）
	# =============================================================================




	AUTO_RAGE_DELAY = 5.0
	AUTO_RAGE_DUR = 4.0





	# 战斗修正量（对齐 Character.gd:64+）

	# 伤害类型系数（对齐 cleanse 里 typedDamageFactors 的初始化：全部 0.0）

	# 近战/远程/效果 尖刺与吸血上限（对齐 Character.gd:389-393）


	# 四类平衡随机源（对齐 Character.gd:299-302）

	# ★ 原版 `Character.INVENTORY`（Character.gd:49 声明、:145 由 inventoryScene 实例化）
	#   这个**大写**名字被物品行为直接引用，共 5 处，全在判定路径上：
	#     BagofStones.gd:13  ctx.player.INVENTORY.getCellsInLine(...)   ← 受影响格覆写
	#     ShinyMantle.gd:25  inventory if placed else ctx.player.INVENTORY
	#     TimeDilator.gd:8   ctx.player.INVENTORY.getItems() + ctx.opponent.INVENTORY.getItems()
	#     RibSawBlade.gd:8   opponent().INVENTORY.getItems()
	#     Bag.gd:55          ctx.player.INVENTORY.canAddBag(self)       ← 只在 _process（拖拽态）里，
	#                                                                     无头内核不调用 _process，故
	#                                                                     CoreGrid 不提供 canAddBag
	#   故内核必须暴露同名属性（与 inventory 同一对象），否则上述物品一上场即
	#   `Invalid get index 'INVENTORY'`。由 _init 与 inventory 同步赋值。

	# 战斗事件信号（对齐 Character.tscn 的 connect）

	# 角色自带伤害源（对齐 Character.tscn 上的 Poison / Spikes / Unhealing DamageSource 节点）

	# 职业（对齐 Character.gd:51 / 53）
	# ★ 战斗相关：setClassResource 用职业资源设 maxHealth / baseMaxStamina / maxStamina。
	#   默认 Ranger=0（对齐 Character.gd:51 `var characterClass = Game.Classes.Ranger`）。

	# 无敌计时（对齐 invulnerabilityTimer，物理帧步进）

	# 战怒计时（对齐 Character.tscn 的 BattleRageTimer / AutoRageTimer，均为 one_shot）
	#   BattleRageTimer.timeout → endBattleRage()
	#   AutoRageTimer.timeout   → startAutoRage()


	def _init(self, _ctx, _playerId):
		self.ctx = _ctx
		self.playerId = _playerId
		self.accuracyRng = self.ctx.rng.BalancedRng(self.ctx.rng)
		self.critRng = self.ctx.rng.BalancedRng(self.ctx.rng)
		self.critResistanceRng = self.ctx.rng.BalancedRng(self.ctx.rng)
		self.stunResistanceRng = self.ctx.rng.BalancedRng(self.ctx.rng)

		# 背包在角色构造时即存在（对齐原版 Character 场景里的 INVENTORY 节点，
		# 它在战斗开始前就参与物品放置，而非战斗期才创建）
		self.inventory = _R.C("CoreGrid")(self)
		self.INVENTORY = self.inventory

		# 对齐 Character.gd:158-162（原版写在 _ready 里，与 INVENTORY 同批）。
		# ★ 这两个是**角色自带**的伤害源（不是 Game 级的 stealLife/unhealing/fatigue）：
		#     spikeDamageSource  → applySpikes（:524）尖刺反弹
		#     poisonDamageSource → tickBuffEffects（:348）中毒跳伤
		#   漏建的直接后果：`spikeDamageSource.setDamage(...)` 报
		#   `Nonexistent function 'setDamage' in base 'Nil'`，且尖刺与中毒两条伤害整条失效
		#   —— 静默少打伤害，闸门 8 首轮抓出 32 次该报错。
		#   `_rng` 对应原版 `Util.rng`（DamageSource.gd:171 掷 min~max 伤害）。
		self.spikeDamageSource = _R.C("CoreDamageSource")()
		self.spikeDamageSource._rng = self.ctx.rng
		self.spikeDamageSource.init(self, _R.C("CoreDamageSource").Type.Spikes, 1)
		self.spikeDamageSource.flags = (_R.C("CoreDamageSource").chipDamageFlags
			+ _R.C("CoreDamageSource").Flags.CanCrit)
		self.poisonDamageSource = _R.C("CoreDamageSource")()
		self.poisonDamageSource._rng = self.ctx.rng
		self.poisonDamageSource.init(self, _R.C("CoreDamageSource").Type.Poison, 1)
		self.poisonDamageSource.flags = (_R.C("CoreDamageSource").chipDamageFlags
			+ _R.C("CoreDamageSource").Flags.CanCrit)

		for stackType in _iter(_R.C("CoreConst").getStacks()):
			buff = _R.C("CoreBuff")()
			buff.init(stackType, self, _gd_fmt('_stacks_changed_%d', stackType))
			self.buffs[stackType] = buff

		self.curHealth = self.maxHealth
		self.baseMaxStamina = self.maxStamina
		self.curStamina = 0.0
		self.staminaRegen = self.baseStaminaRegen

		for type in _iter(list(_R.C("CoreDamageSource").Type.values())):
			self.typedDamageFactors[type] = 0.0


	def setOpponent(self, _opponent):
		self.opponent = _opponent


	def isPlayer(self):
		return self.playerId == self.ID.PLAYER


	def getName(self):
		return ["Player", "Opponent"][self.playerId]


	def registerCharacterDied(self, handler):
		self.character_died_handlers.append(handler)


	# 原版仅有一对 connect（Game.gd:2549 / 2986）。重复 setup 时先清空，
	# 避免同一 handler 被注册多次导致 endCombat 重入判定被跳过之外的副作用。
	def clearCharacterDiedHandlers(self):
		self.character_died_handlers.clear()


	# ─────────────────────────── 准备 / 开始 / 结束（对齐 294-347） ───────────────────────────

	def prepare(self):
		self.staminaRegen = self.baseStaminaRegen

		self.accuracyRng.reset()
		self.critRng.reset()
		self.critResistanceRng.reset()
		self.stunResistanceRng.reset()

		# 对齐 Character.gd:304-310：低于大师或大厅模式，玩家 -0.2、对手 +0.2
		if self.ctx.below_master or self.ctx.lobbies_mode:
			if self.playerId == self.ID.PLAYER:
				self.accuracyRng.setBias( - 0.2)
				self.critRng.setBias( - 0.2)
			else:
				self.accuracyRng.setBias(0.2)
				self.critRng.setBias(0.2)

		# 自动战怒选品（对齐 Character.gd:312-326）：背包里有带 BattleRage 标签的物品时不启用
		# 自动战怒；否则从**含宝石**的物品里随机挑一个 isBattleRageItem() 的。
		# ★ 原版用 Array.pick_random()（Godot 全局 RNG），内核改用注入 rng 以保证同种子可复现。
		self.autoRageItem = None
		hasBattleRageStarter = False
		for item in _iter(self.inventory.getItems()):
			if item.hasTag(_R.C("CoreConst").Tag.BattleRage):
				hasBattleRageStarter = True
				break

		if not hasBattleRageStarter:
			battleRageItems = []
			for item in _iter(self.inventory.getItemsAndGems()):
				if item.isBattleRageItem():
					battleRageItems.append(item)

			if not (not battleRageItems):
				self.autoRageItem = self.ctx.rng.pickRandomElement(battleRageItems)


	# 对齐 Character.gd:328-337
	def combatStart(self):
		self.stunnedDuration = 0.0
		self.tickCounter = 0

		if self.autoRageItem != None:
			self._autoRage_left = self.AUTO_RAGE_DELAY
			self._autoRage_active = True


	# 对齐 Character.gd:339-349（三个一次性计时器全部 stop）
	def combatEnd(self):
		self.attackMovingForward_reset()

		for buffType in _iter(self.buffs):
			self.buffs[buffType].combatEnd()

		self._rage_left = 0.0
		self._rage_active = False
		self._autoRage_left = 0.0
		self._autoRage_active = False
		self._invul_left = 0.0
		self._invul_active = False


	# 原版是动画 tween 复位；无头下只需清标志
	def attackMovingForward_reset(self):
		pass


	def cleanse(self):
		self.isDead = False
		self.temporaryMaxHealth = 0
		self.temporaryMaxHealthGain = 1.0
		self.staminaRegen = self.baseStaminaRegen
		self.healToFull()
		self.setTemporaryMaxStamina(0)
		self.fillUpStamina()
		self.endStun()
		self.setBlock(0)

		for buffType in _iter(self.buffs):
			self.buffs[buffType].reset()

		self.invulnerable = False

		self.damageResistance = 0.0
		self.damageReduction = 0
		self.dodgeStacks = 0
		self.critResistance = 0.0
		self.critResistStacks = 0
		self.stunResistance = 0.0
		self.unhealingAmount = 0.0
		self.healingEfficiency = 1.0
		self.critTokens = 0
		self.debuffResistStacks = 0
		self.debuffReflectStacks = 0
		self.buffProtectStacks = 0
		self.battleRageBonusDur = 0.0
		self.bonusFatigueDamage = 0
		self.blindingLightActive = False
		self.meleeSpikesLimit = 1.0
		self.rangedSpikesLimit = 0.0
		self.effectSpikesLimit = 0.0
		self.meleeVampirismLimit = 1.0
		self.rangedVampirismLimit = 0.0
		self.empowerDamage = 1.0
		for damageType in _iter(list(_R.C("CoreDamageSource").Type.values())):
			self.typedDamageFactors[damageType] = 0.0

		self.poisonDamageSource.critChancePercent = 0
		self.spikeDamageSource.critChancePercent = 0


	# ─────────────────────────── 每秒 Tick（对齐 401-414） ───────────────────────────

	def onTick(self):
		if _mod(self.tickCounter, 2) == 0:
			regen = self.getRegeneration()
			if regen > 0:
				self.heal(regen, _R.C("CoreConst").EventType.Regeneration)
				self.ctx.hooks.activateBuffCounter(self, _R.C("CoreConst").EventType.Regeneration)
		else:
			poison = self.getPoison()
			if poison > 0:
				self.poisonDamageSource.setDamage(poison)
				self.takeDamage(self.poisonDamageSource)
				self.ctx.hooks.activateBuffCounter(self, _R.C("CoreConst").EventType.Poison)

		self.tickCounter += 1


	# ─────────────────────────── 伤害主链（对齐 482-653） ───────────────────────────

	def dealDamage(self, damageSource, triggerEvent=None):
		res = self.opponent.takeDamage(damageSource, triggerEvent)
		self.applyVampirism(res)
		return res


	def takeDamage(self, damageSource, triggerEvent=None):

		damageRes = _R.C("CoreDamageResult")()

		damageSource = _R.C("CoreDamageSource")().fromDamageSource(damageSource)
		# 无头内核的随机源按对象持有（原版为全局 Util.rng），复制出的新实例需补注入；
		# DamageResult 随机取值路径（randDamage）才会与本场战斗同一随机流。
		damageSource._rng = self.ctx.rng
		damageRes.damageSource = damageSource
		damageRes.reset()

		if self.isDead:
			return damageRes

		item = None
		if isinstance(damageSource.origin, _R.C("CoreItem")):
			item = damageSource.origin

		attackEffectCount = 1

		if item != None:
			attackEffectCount += item.rollDoubleAttackEffect()

		if damageSource.canMiss():
			accuracy = damageSource.accuracy
			damageRes.hit = self.accuracyRng.rollPercent(accuracy)
			if damageRes.hit and self.dodgeStacks > 0:
				self.changeDodgeStacks( - 1)
				damageRes.hit = False
		else:
			damageRes.hit = True

		if item != None and damageSource.isAttack():
			item.preDealDamage_early(damageRes)
			if item.hasPreDealDamageEarlyEffect:
				for i in _iter(attackEffectCount):
					item._behavior_call("onPreDealDamage_early", [damageRes])

		if damageRes.hit:
			damageRes.damage += damageSource.randDamage()

			if damageSource.hasType(_R.C("CoreDamageSource").Type.Fatigue):
				damageRes.damage += self.bonusFatigueDamage

			if damageSource.canCrit():
				critical = False

				critChancePercent = damageSource.getCritChancePercent()
				if critChancePercent > 0 and self.critRng.rollPercent(critChancePercent):
					critical = True

				if not damageRes.critical and item != None and item.getCritTokens() > 0:
					item.useCritToken()
					critical = True

				if not damageRes.critical and self.opponent.getCritTokens() > 0:
					self.opponent.useCritToken()
					critical = True

				if critical:
					if self.critResisted():
						self.ctx.hooks.spawnBuffLabel(_R.C("CoreConst").EventType.CriticalResisted, None)
					else:
						damageRes.makeCritical()

			activeDmgResi = clamp(_div(self.damageResistance, 100), -10, 1)
			damageRes.damage = round(damageRes.damage * (1.0 - activeDmgResi))

			if damageRes.damageSource.isAttack():
				damageRes.damage -= self.damageReduction

			if self.invulnerable:
				damageRes.damage = 0

			self.ctx.bus.emitSignal(self, "pre_take_damage", [damageRes])

			damageRes.damage -= damageRes.damageReduction

			damageRes.damage = max(0, damageRes.damage)

			if item != None and damageSource.isAttack():
				item.preDealDamage_late(damageRes)
				if item.hasPreDealDamageLateEffect:
					for i in _iter(attackEffectCount):
						item._behavior_call("onPreDealDamage_late", [damageRes])

			self.ctx.bus.emitSignal(self, "pre_take_damage_late", [damageRes])
			damageRes.healthDamage = damageRes.damage

			if damageSource.canBeBlocked():
				curBlock = self.getBlock()
				if damageRes.damage > curBlock:
					damageRes.healthDamage -= curBlock
					self.loseBlock(curBlock)
				else:
					self.loseBlock(damageRes.damage)
					damageRes.healthDamage = 0

			self.curHealth -= damageRes.healthDamage

			if damageRes.wasCriticalHit():
				self.spawnLabel_native(_R.C("CoreConst").EventType.CriticalDamage, damageRes.damage, item)
			elif damageSource.hasType(_R.C("CoreDamageSource").Type.Fatigue):
				self.spawnLabel_native(_R.C("CoreConst").EventType.Fatigue, damageRes.damage, item)
			elif damageSource.hasType(_R.C("CoreDamageSource").Type.Poison):
				self.spawnLabel_native(_R.C("CoreConst").EventType.Poison, damageRes.damage, item)
			elif damageSource.hasType(_R.C("CoreDamageSource").Type.Spikes):
				self.spawnLabel_native(_R.C("CoreConst").EventType.Spikes, damageRes.damage, item)
			else:
				self.spawnLabel_native(_R.C("CoreConst").EventType.DealDamage, damageRes.damage, item)

			# 原版此处写入 damageAnimation 播放速度与片段（纯表现）→ 已剥离
			self.ctx.hooks.damageAnimation(self, "Fatigue" if damageSource.hasType(_R.C("CoreDamageSource").Type.Fatigue) else "Hit")
		else:
			self.spawnLabel_native(_R.C("CoreConst").EventType.MissedAttack, 0, item)

		event = None
		if item != None:
			event = self.ctx.combat_log.createEvent_Attack(damageRes, triggerEvent)
			self.ctx.bus.emitSignal(item, "dealt_damage_signal_placeholder", [damageRes])
			item.dealtDamage(damageRes)
		else:
			event = self.ctx.combat_log.createEvent_Damage(damageRes, self.opponent.playerId, triggerEvent)

		damageRes.event = event
		self.ctx.bus.emitEvent(self, "character_attacked", event, [damageRes])
		self.ctx.bus.emitSignal(self, "character_damaged", [damageRes.healthDamage, damageRes.event])

		self.ctx.hooks.onHealthChangedUI(self)

		if (item != None and 
			damageSource.isAttack() and 
			item.hasDealtDamageEffect):
			for i in _iter(attackEffectCount):
				item._behavior_call("onDealtDamage", [damageRes])

		if self.curHealth <= 0:
			self.death()

		self.applySpikes(damageRes)

		return damageRes


	def spawnLabel_native(self, type, damage, item=None):
		self.ctx.hooks.spawnLabel_character(self, type, damage, item)


	def applySpikes(self, damageRes):
		if self.getSpikes() > 0 and damageRes.canTriggerSpikes():
			spikesLimit = None
			if damageRes.damageSource.hasType(_R.C("CoreDamageSource").Type.Ranged):
				spikesLimit = self.rangedSpikesLimit
			else:
				spikesLimit = self.meleeSpikesLimit

			if damageRes.damageSource.hasType(_R.C("CoreDamageSource").Type.Effect):
				spikesLimit = max(self.effectSpikesLimit, spikesLimit)

			spikeDam = min(self.getSpikes(), round(damageRes.damage * spikesLimit))
			if spikeDam > 0:
				self.spikeDamageSource.setDamage(spikeDam)
				self.opponent.takeDamage(self.spikeDamageSource, damageRes.event)
				self.ctx.hooks.activateBuffCounter(self, _R.C("CoreConst").EventType.Spikes)


	def applyVampirism(self, damageRes):
		if self.getVampirism() > 0 and damageRes.canTriggerVampirism():
			vampLimit = None
			if damageRes.damageSource.hasType(_R.C("CoreDamageSource").Type.Ranged):
				vampLimit = self.rangedVampirismLimit
			else:
				vampLimit = self.meleeVampirismLimit

			healAmount = min(self.getVampirism(), round(damageRes.damage * vampLimit))
			if healAmount > 0:
				self.heal(healAmount, _R.C("CoreConst").EventType.Vampirism, damageRes.event)
				self.ctx.hooks.activateBuffCounter(self, _R.C("CoreConst").EventType.Vampirism)


	# ─────────────────────────── 治疗 / 直接扣血（对齐 739-869） ───────────────────────────

	def heal(self, amount, origin=None, triggerEvent=None):
		amount *= self.getHealingEfficiency()
		amount = round(amount)

		missingHealth = self.getMaxHealth() - self.curHealth
		overheal = max(0, amount - missingHealth)
		self.curHealth += amount
		self.curHealth = min(self.curHealth, self.getMaxHealth())

		self.ctx.hooks.onHealthChangedUI(self)
		self.ctx.hooks.spawnLabel_character(self, _R.C("CoreConst").EventType.Health, amount, origin)

		event = self.ctx.combat_log.createEvent_Heal(amount, self.playerId, origin, triggerEvent)

		if origin:
			if isinstance(origin, _R.C("CoreItem")):
				origin.addMetric(_R.C("CoreConst").ItemMetrics.Heal, amount)
				origin.addMetric(_R.C("CoreConst").ItemMetrics.Overheal, overheal)
			else:
				self.ctx.combat_log.snapshotMetric(self.playerId, _R.C("CoreConst").ItemMetrics.Heal, origin, amount)
				self.ctx.combat_log.snapshotMetric(self.playerId, _R.C("CoreConst").ItemMetrics.Overheal, origin, overheal)

		self.ctx.bus.emitEvent(self, "character_healed", event, [event.getAmount(), event])
		if overheal > 0:
			self.ctx.bus.emitSignal(self, "character_overhealed", [overheal, event])

		if self.getUnhealing() > 0:
			unhealing = ceil(amount * self.getUnhealing() * (1 + self.typedDamageFactors[_R.C("CoreDamageSource").Type.Unhealing]))
			if unhealing > 0:
				self.ctx.unhealingDamageSource.setDamage(unhealing)
				self.opponent.takeDamage(self.ctx.unhealingDamageSource, event)


	def healToFull(self):
		self.curHealth = self.getMaxHealth()
		self.ctx.hooks.onHealthChangedUI(self)


	def reincarnate(self, healAmount, isHeal, item, triggerEvent):
		self.setCurrentHealth(0)

		healAmount = min(self.getMaxHealth(), healAmount)
		self.setCurrentHealth(healAmount)
		event = self.ctx.combat_log.createEvent_Reincarnate(item, healAmount, triggerEvent)
		item.addMetric(_R.C("CoreConst").ItemMetrics.Heal, healAmount)
		self.ctx.bus.emitEvent(self, "reincarnated", event, [event])
		return event


	def getCurrentHealth(self):
		return self.curHealth


	def getRelativeHealth(self):
		return _div(self.getCurrentHealth(), self.getMaxHealth())


	def getMissingHealth(self):
		return int(ceil(self.getMaxHealth() - self.getCurrentHealth()))


	def setCurrentHealth(self, _curHealth):
		self.curHealth = _curHealth
		self.ctx.hooks.onHealthChangedUI(self)


	def loseHealth(self, amount, item=None, triggerEvent=None):
		self.curHealth -= amount
		event = None
		if item:
			event = self.ctx.combat_log.createEvent_LoseHealth( - amount, self.playerId, item, triggerEvent)
			self.ctx.bus.emitEvent(self, "character_damaged", event, [event.getAmount(), event])

		self.ctx.hooks.onHealthChangedUI(self)

		if self.curHealth <= 0:
			self.death()

		return event


	def setMaxHealth(self, _maxHealth):
		self.maxHealth = _maxHealth
		self.curHealth = self.maxHealth
		self.ctx.hooks.onHealthChangedUI(self)


	def giveMaxHealth(self, amount):
		self.maxHealth += amount
		self.curHealth += amount
		self.ctx.hooks.onHealthChangedUI(self)


	def getBaseMaxHealth(self):
		return self.maxHealth


	def getMaxHealth(self):
		return self.maxHealth + self.temporaryMaxHealth


	def applyTemporaryMaxHealthGain(self, amount):
		return round(amount * self.temporaryMaxHealthGain)


	def changeMaxHealthTemporary(self, amount, item=None, triggerEvent=None):
		if amount != 0:
			self.temporaryMaxHealth += amount

			self.curHealth += amount
			if item != None:
				event = self.ctx.combat_log.createEvent_TemporaryMaxHealth(item, amount, triggerEvent)
				self.ctx.bus.emitEvent(self, "temporary_max_health_changed", event, [event])


	# ─────────────────────────── 体力（对齐 791-848） ───────────────────────────

	def getMaxStamina(self):
		return self.maxStamina + self.temporaryMaxStamina


	def gainStamina(self, amount, item=None, triggerEvent=None):
		self.curStamina += amount

		if not self.allowStaminaOverflow:
			self.clampStamina()

		if item != None:
			event = self.ctx.combat_log.createEvent_Stamina(amount, item, self.playerId, triggerEvent)
			self.ctx.bus.logEvent(event)
			item.staminaChanged(amount, _R.C("CoreConst").StackChangeType.Added_Player)


	def addStamina(self, amount):
		self.curStamina += amount
		self.clampStamina()


	def clampStamina(self):
		self.curStamina = clamp(self.curStamina, 0, self.getMaxStamina())


	def fillUpStamina(self):
		self.addStamina(self.maxStamina)




	def useStamina(self, amount):
		self.allowStaminaOverflow = True
		self.ctx.bus.emitSignal(self, "character_pre_use_stamina", [amount])
		self.allowStaminaOverflow = False

		if self.curStamina >= amount:
			self.curStamina = max(self.curStamina - amount, 0)
			self.clampStamina()
			self.ctx.bus.emitSignal(self, "character_used_stamina", [amount])

			return self.StaminaResult.Sufficient
		else:
			self.clampStamina()

			return self.StaminaResult.Insufficient


	def drainStamina(self, amount, item, triggerEvent=None):
		drained = min(self.curStamina, amount)
		self.curStamina -= drained
		event = self.ctx.combat_log.createEvent_DrainStamina(drained, item, self.playerId, triggerEvent)
		self.ctx.bus.logEvent(event)
		item.staminaChanged(drained, _R.C("CoreConst").StackChangeType.Removed_Opponent)
		return event


	def setTemporaryMaxStamina(self, amount):
		self.temporaryMaxStamina = amount


	def setTemporaryMaxHealthGain(self, amount):
		self.temporaryMaxHealthGain = amount


	# ─────────────────────────── 死亡 / 眩晕 / 抗性（对齐 997-1083, 1390-1408） ───────────────────────────

	def death(self):
		self.isDead = True
		for handler in _iter(self.character_died_handlers):
			handler.call_func()


	def stun(self, duration, item=None, triggerEvent=None):
		if self.stunResisted():
			self.ctx.hooks.spawnBuffLabel(_R.C("CoreConst").EventType.StunResisted, None)
			event = self.ctx.combat_log.createEvent_StunResist(item, self.playerId, triggerEvent)
			self.ctx.bus.logEvent(event)
		else:
			self.stunnedDuration = max(self.stunnedDuration, duration)
			event = self.ctx.combat_log.createEvent_Stun(item, duration, self.playerId, triggerEvent)
			self.ctx.bus.logEvent(event)
			self.ctx.hooks.playStunAnimation(self, duration)


	def endStun(self):
		self.stunnedDuration = 0.0
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.Stunned)


	def isStunned(self):
		return self.stunnedDuration > 0


	def changeDodgeStacks(self, amount):
		self.dodgeStacks = int(max(0, self.dodgeStacks + amount))
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.DodgeStacks)


	def changeCritResistance(self, amount):
		self.critResistance += amount
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.CritResistance)


	def critResisted(self):
		resisted = self.critResistanceRng.rollPercent(self.critResistance)
		if not resisted:
			if self.critResistStacks > 0:
				self.critResistStacks -= 1
				self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.CritResistStacks)
				return True
		return resisted


	def gainCritResistStacks(self, num):
		self.critResistStacks += num
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.CritResistStacks)


	def changeStunResistance(self, amount):
		self.stunResistance += amount


	def stunResisted(self):
		return self.stunResistanceRng.rollPercent(self.stunResistance)


	def giveUnhealing(self, amount):
		self.unhealingAmount += amount
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.Unhealing)


	def reduceUnhealing(self, amount):
		self.unhealingAmount = max(0.0, self.unhealingAmount - amount)
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.Unhealing)


	def getUnhealing(self):
		return self.unhealingAmount


	# 对齐 Character.gd:1421-1422（原版无返回类型标注）
	def getHealingEfficiency(self):
		return max(0.0, self.healingEfficiency)


	def addHealingEfficiency(self, amount):
		self.healingEfficiency += amount
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.HealEfficiency)


	def reduceHealingEfficiency(self, amount):
		self.healingEfficiency -= amount
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.HealEfficiency)


	def getCritTokens(self):
		return self.critTokens


	def gainCritTokens(self, amount):
		self.critTokens += amount


	def changeDebuffResistStacks(self, amount):
		self.debuffResistStacks += amount
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.DebuffResistStacks)


	def changeDebuffReflectStacks(self, amount):
		self.debuffReflectStacks += amount
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.ReflectStacks)


	def changeBuffProtectStacks(self, amount):
		self.buffProtectStacks += amount


	def changeReflectChance(self, debuff, amount):
		self.buffs[debuff].changeReflectChance(amount)


	def changeAllDebuffsReflectChance(self, amount):
		for debuff in _iter(_R.C("CoreConst").getDebuffs()):
			self.changeReflectChance(debuff, amount)


	def changeMeleeSpikesLimit(self, amount):
		self.meleeSpikesLimit += amount


	def changeRangedSpikesLimit(self, amount):
		self.rangedSpikesLimit += amount


	def changeEffectSpikesLimit(self, amount):
		self.effectSpikesLimit += amount


	def changeMeleeVampirismLimit(self, amount):
		self.meleeVampirismLimit += amount


	def changeRangedVampirismLimit(self, amount):
		self.rangedVampirismLimit += amount


	def getBonusFatigueDamage(self):
		return self.bonusFatigueDamage


	def addFatigueDamage(self, amount):
		self.bonusFatigueDamage += amount
		self.ctx.bus.emitSignal(self, "fatigue_damage_changed")


	def takeFatigueDamage(self, item=None):
		self.takeDamage(self.ctx.fatigueDamageSource)


	def startBlindingLight(self):
		self.blindingLightActive = True


	def endBlindingLight(self, event=None):
		self.blindingLightActive = False
		self.ctx.bus.emitSignal(self, "blinding_light_ended", [event])


	# 对齐 Character.gd:1556-1571。★ 签名必须与原版逐字一致——物品行为直接这样调：
	#   BerserkerBag.gd:21 / WolfBadge.gd:27  character().startBattleRage(self, getP_m("dur_rage"), event)
	#   ExtraAngy.gd:28                       character().startBattleRage(self, dur, null, false)
	#   Toolbox.gd:35                         character().startBattleRage(self, getP_m("dur_rage"))
	def startBattleRage(self, item, duration, triggerEvent=None, applyBonus=True):
		fullDur = duration
		if applyBonus:
			fullDur += self.battleRageBonusDur
		self._setRageTimer(fullDur)

		event = self.ctx.combat_log.createEvent_BattleRageStart(item, fullDur, triggerEvent)
		self.ctx.bus.emitEvent(self, "battle_rage_started", event, [event])
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.BattleRage, False, event)
		self.ctx.hooks.playBattleRageAnimation(self, True)
		return event


	# 对齐 Character.gd:1567-1572（原版由 Character.tscn 的
	#   [connection signal="timeout" from="BattleRageTimer" to="." method="endBattleRage"]
	# 驱动；内核改为物理帧步进，超时点在本类 physicsTick 里触发同一方法。）
	def endBattleRage(self):
		self._rage_left = 0.0
		self._rage_active = False
		event = self.ctx.combat_log.createEvent_BattleRageEnd(self.playerId)
		self.ctx.bus.emitEvent(self, "battle_rage_ended", event, [event])
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.BattleRage, False, event)
		self.ctx.hooks.playBattleRageAnimation(self, False)


	# 对齐 Character.gd:192-196
	def getClass(self):
		return self.characterClass


	# 对齐 Character.gd:195-196。★ 原版反编译文本写作 `func isChibi() -> int:`，但函数体
	# 返回的是 bool 字段 chibi —— 该 `-> int` 是反编译器补出来的标注（原版源码不可能编译
	# 通过一个返回 bool 的 -> int 函数），故内核去掉返回类型标注，只保留取值语义。
	def isChibi(self):
		return self.chibi


	# 对齐 Character.gd:198-209。表现部分（nameBanner 贴图 / setSprite / class_changed 信号）
	# 走 hooks 与 ctx.bus；对对手分支原版只调 setSprite（同样走 hooks）——内核两者等价。
	def setClass(self, _class, _chibi, classResource=None):
		self.characterClass = _class
		self.chibi = _chibi
		if classResource == None:
			classResource = self.ctx.class_resources.get(_class, None) if self.ctx.class_resources else None
		if classResource != None and self.playerId == self.ID.PLAYER:
			self.setClassResource(classResource)
		self.ctx.hooks.onClassChanged(self, classResource)
		self.ctx.bus.emitSignal(self, "class_changed", [])


	# 对齐 Character.gd:211-215。setSprite 是表现 → 剥离。职业资源的字段读取用 .get(key)，
	# 同时兼容 Resource（Object.get）与 Dictionary（Dictionary.get）。
	def setClassResource(self, classResource):
		if classResource == None:
			return
		self.setMaxHealth(classResource.get("health"))
		self.baseMaxStamina = classResource.get("stamina")
		self.setMaxStamina(self.baseMaxStamina)
		self.ctx.hooks.onClassChanged(self, classResource)


	# 对齐 Character.gd:1002-1004 / 1006-1011（胜负表现：粒子 + 动画）
	def lose(self):
		self.ctx.hooks.playWinLoseAnimation(self, False)


	def win(self):
		self.ctx.hooks.playWinLoseAnimation(self, True)


	# 对齐 Character.gd:1609-1622（唯一写入口是战斗日志回放的 setStat；
	# 各分支的表现调用统一走 hooks）
	def setStat(self, stat, value):
		if stat == self.Stat.Health:
				self.setCurrentHealth(value)
		elif stat == self.Stat.MaxHealth:
				self.setTemporaryMaxHealth(value)
		elif stat == self.Stat.Stamina:
				self.setCurrentStamina(value)
		elif stat == self.Stat.MaxStamina:
				self.setTemporaryMaxStamina(value - self.maxStamina)
		elif stat == self.Stat.Stunned:
				self.ctx.hooks.playStunAnimation(self, value)
		elif stat == self.Stat.Invulnerable:
				self.ctx.hooks.playInvulnerableAnimation(self, value)
		elif stat == self.Stat.BattleRage:
				self.ctx.hooks.playBattleRageAnimation(self, value)


	# 对齐 Character.gd:1650-1690（逐分支逐字对应；StaminaRegen/HealEfficiency/
	# Unhealing/MaxHealthGain 都是「显示用百分比」，原版就带 *100/(x-1) 换算，照抄）
	def getStat(self, stat):
		if stat == self.Stat.StaminaRegen:
				return (self.getStaminaRegeneration() - 1) * 100.0
		elif stat == self.Stat.Health:
				return self.getCurrentHealth()
		elif stat == self.Stat.MaxHealth:
				return self.getTemporaryMaxHealth()
		elif stat == self.Stat.Stamina:
				return self.getCurrentStamina()
		elif stat == self.Stat.MaxStamina:
				return self.getMaxStamina()
		elif stat == self.Stat.Stunned:
				return self.stunnedDuration
		elif stat == self.Stat.Invulnerable:
				return self.invulnerable
		elif stat == self.Stat.BattleRage:
				return self.isBattleRaging()
		elif stat == self.Stat.ReflectStacks:
				return self.debuffReflectStacks
		elif stat == self.Stat.DebuffResistStacks:
				return self.debuffResistStacks
		elif stat == self.Stat.CritStacks:
				return self.getCritTokens()
		elif stat == self.Stat.DodgeStacks:
				return self.dodgeStacks
		elif stat == self.Stat.CritResistStacks:
				return self.critResistStacks
		elif stat == self.Stat.CritResistance:
				return self.critResistance
		elif stat == self.Stat.StunResistance:
				return self.stunResistance
		elif stat == self.Stat.HealEfficiency:
				return (self.getHealingEfficiency() - 1) * 100
		elif stat == self.Stat.DamageResistance:
				return self.damageResistance
		elif stat == self.Stat.MeleeDmgFactor:
				return self.typedDamageFactors[_R.C("CoreDamageSource").Type.Melee] * 100
		elif stat == self.Stat.RangedDmgFactor:
				return self.typedDamageFactors[_R.C("CoreDamageSource").Type.Ranged] * 100
		elif stat == self.Stat.EffectDmgFactor:
				return self.typedDamageFactors[_R.C("CoreDamageSource").Type.Effect] * 100
		elif stat == self.Stat.Unhealing:
				return self.getUnhealing() * 100
		elif stat == self.Stat.MaxHealthGain:
				return (self.temporaryMaxHealthGain - 1.0) * 100
		return None


	# 对齐 Character.gd:1552-1553（battleRageTimer 一次性计时器是否在跑）
	def isBattleRaging(self):
		return self._rage_active


	# 对齐 Character.gd:1588-1589（AutoRageTimer.timeout → startAutoRage）
	def startAutoRage(self):
		# 原版 startAutoRage 不传 applyBonus → 走默认 true（吃到 battleRageBonusDur）
		self.startBattleRage(self.autoRageItem, self.AUTO_RAGE_DUR)


	# 对齐 Character.gd:1574-1579（表现：粒子/动画/音效）
	def playBattleRageAnimation(self, rageStart):
		self.ctx.hooks.playBattleRageAnimation(self, rageStart)


	# Util.changeTimer 语义：start(t + timeLeft) —— 在**剩余时间**基础上延长。
	def _setRageTimer(self, t):
		if self._rage_active:
			self._rage_left = t + self._rage_left
		else:
			self._rage_left = t
			self._rage_active = True


	# ── 无敌（对齐 Character.gd:1037-1062，Timer 改为物理帧步进） ──

	def makeInvulnerable(self, invuDur, item, triggerEvent=None):
		self.invulnerabilityItem = item

		# 对齐 Character.gd:1038-1044：首次 start(invuDur)；已无敌时 Util.changeTimer
		# （= start(t + timeLeft)，在**剩余时间**上加）→ 所以是延长而非覆盖。
		if not self.invulnerable:
			self._invul_left = invuDur
			self._invul_active = True
			self.invulnerable = True
			self.ctx.hooks.playInvulnerableAnimation(self, True)
		else:
			self._invul_left = invuDur + self._invul_left

		event = self.ctx.combat_log.createEvent_InvulnerableStart(item, invuDur, self.playerId, triggerEvent)
		self.ctx.bus.emitEvent(self, "character_invulnerable_start", event, [event])
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.Invulnerable)
		return event


	def makeVulnerable(self, item, triggerEvent=None):
		pass


	# 对齐 Character.gd:1051-1056（原版由 InvulnerabilityTimer.timeout 驱动）
	def invulnerabilityEnded(self):
		self.invulnerable = False
		event = self.ctx.combat_log.createEvent_InvulnerableEnd(self.invulnerabilityItem, self.playerId)
		self.ctx.bus.emitEvent(self, "character_invulnerable_end", event, [event])
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.Invulnerable)
		self.ctx.hooks.playInvulnerableAnimation(self, False)


	def setInvulnerable(self, active, item=None):
		self.invulnerable = active


	# ─────────────────────────── 栈宿主（对齐 1122-1200+） ───────────────────────────

	def getStacks(self, buffType):
		return self.buffs[buffType].getStacks()


	def getBuffStacks(self):
		stacks = 0
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			stacks += self.getStacks(buff)
		return stacks


	def getDebuffStacks(self):
		stacks = 0
		for debuff in _iter(_R.C("CoreConst").getDebuffs()):
			stacks += self.getStacks(debuff)
		return stacks


	def setStacks(self, buffType, amount):
		self.buffs[buffType].setStacks(amount)


	def setStacksLogged(self, buffType, amount, item=None, triggerEvent=None):
		curStacks = self.getStacks(buffType)
		if amount < curStacks:
			self.loseStacks(buffType, curStacks - amount, item, triggerEvent)
		elif amount > curStacks:
			self.gainStacks(buffType, amount - curStacks, item, triggerEvent)


	def gainStacks(self, buffType, amount, item=None, triggerEvent=None, reflect=False):
		return self.buffs[buffType].gainStacks(amount, item, triggerEvent)


	def gainStacksTemporary(self, buffType, amount, duration, item=None, triggerEvent=None, reflect=False):
		return self.buffs[buffType].gainTemporary(amount, duration, item, triggerEvent, reflect)


	def loseStacks(self, buffType, amount, item=None, triggerEvent=None):
		return self.buffs[buffType].loseStacks(amount, item, triggerEvent)


	def useStacks(self, buffType, amount, item=None, triggerEvent=None):
		return self.buffs[buffType].loseStacks(amount, item, triggerEvent, True)


	def changeResistChance(self, buffType, chance):
		self.buffs[buffType].changeResistChance(chance)


	def changeDebuffResistChances(self, chance):
		for debuff in _iter(_R.C("CoreConst").getDebuffs()):
			self.changeResistChance(debuff, chance)


	def changeResistStacks(self, buffType, amount):
		self.buffs[buffType].changeResistStacks(amount)


	def getBlock(self):
		return self.getStacks(_R.C("CoreConst").EventType.Block)


	# 对齐 Character.gd:1182-1183：原版此处写入的是 Spikes（原样保留，不修）
	def setBlock(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Spikes, amount)


	def gainBlock(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Block, amount, item, triggerEvent)


	def loseBlock(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Block, amount, item, triggerEvent)


	# ── 各栈取值（对齐 1179-1360 的模板） ──

	def getSpikes(self):
		return self.getStacks(_R.C("CoreConst").EventType.Spikes)


	def setSpikes(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Spikes, amount)


	def gainSpikes(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Spikes, amount, item, triggerEvent)


	def loseSpikes(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Spikes, amount, item, triggerEvent)


	def getVampirism(self):
		return self.getStacks(_R.C("CoreConst").EventType.Vampirism)


	def setVampirism(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Vampirism, amount)


	def gainVampirism(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Vampirism, amount, item, triggerEvent)


	def loseVampirism(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Vampirism, amount, item, triggerEvent)


	def getPoison(self):
		return self.getStacks(_R.C("CoreConst").EventType.Poison)


	def setPoison(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Poison, amount)


	def gainPoison(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Poison, amount, item, triggerEvent)


	def losePoison(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Poison, amount, item, triggerEvent)


	def getRegeneration(self):
		return self.getStacks(_R.C("CoreConst").EventType.Regeneration)


	def setRegeneration(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Regeneration, amount)


	def gainRegeneration(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Regeneration, amount, item, triggerEvent)


	def loseRegeneration(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Regeneration, amount, item, triggerEvent)


	def getLucky(self):
		return self.getStacks(_R.C("CoreConst").EventType.Lucky)


	def setLucky(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Lucky, amount)


	def gainLucky(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Lucky, amount, item, triggerEvent)


	def loseLucky(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Lucky, amount, item, triggerEvent)


	def getBlind(self):
		return self.getStacks(_R.C("CoreConst").EventType.Blind)


	def setBlind(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Blind, amount)


	def gainBlind(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Blind, amount, item, triggerEvent)


	def loseBlind(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Blind, amount, item, triggerEvent)


	def getMana(self):
		return self.getStacks(_R.C("CoreConst").EventType.Mana)


	def setMana(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Mana, amount)


	def gainMana(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Mana, amount, item, triggerEvent)


	def loseMana(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Mana, amount, item, triggerEvent)


	def getEmpower(self):
		return self.getStacks(_R.C("CoreConst").EventType.Empower)


	def setEmpower(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Empower, amount)


	def gainEmpower(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Empower, amount, item, triggerEvent)


	def loseEmpower(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Empower, amount, item, triggerEvent)


	def getHeat(self):
		return self.getStacks(_R.C("CoreConst").EventType.Heat)


	def setHeat(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Heat, amount)


	def gainHeat(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Heat, amount, item, triggerEvent)


	def loseHeat(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Heat, amount, item, triggerEvent)


	def getCold(self):
		return self.getStacks(_R.C("CoreConst").EventType.Cold)


	def setCold(self, amount):
		self.setStacks(_R.C("CoreConst").EventType.Cold, amount)


	def gainCold(self, amount, item=None, triggerEvent=None):
		return self.gainStacks(_R.C("CoreConst").EventType.Cold, amount, item, triggerEvent)


	def loseCold(self, amount, item=None, triggerEvent=None):
		return self.loseStacks(_R.C("CoreConst").EventType.Cold, amount, item, triggerEvent)


	def getBuffDamageMod(self):
		return self.getEmpower() * self.empowerDamage


	# 对齐 Character.gd:1353-1354（原版无返回类型标注：int 运算结果原样返回）
	def getBuffAccuracyMod(self):
		return (self.getLucky() - self.getBlind()) * 5


	# ─────────────────────────── 体力（源码补全，对齐 Character.gd:928-992, 1100-1121） ───────────────────────────
	# 面向物品行为 API 面：Items/*.gd 通过 character().<这些> 读写体力。

	# 对齐 Character.gd:935-938
	def getBaseMaxStamina(self):
		return self.baseMaxStamina


	# 对齐 Character.gd:939-941
	def getMaxBaseStamina(self):
		return self.maxStamina


	# 对齐 Character.gd:928-930
	def getCurrentStamina(self):
		return self.curStamina


	# 对齐 Character.gd:931-934
	def setCurrentStamina(self, stamina):
		self.curStamina = stamina


	# 对齐 Character.gd:942-944
	def getMissingStamina(self):
		return self.getMaxStamina() - self.getCurrentStamina()


	# 对齐 Character.gd:945-947
	def isFullStamina(self):
		return self.getMissingStamina() <= 0


	# 对齐 Character.gd:948-952（emit_signal("max_stamina_changed_ui") → 钩子）
	def setMaxStamina(self, _maxStamina):
		self.maxStamina = _maxStamina
		self.curStamina = self.maxStamina
		self.ctx.hooks.onMaxStaminaChangedUI(self)


	# 对齐 Character.gd:953-957
	def giveMaxStamina(self, amount):
		self.maxStamina += amount
		self.curStamina += amount
		self.ctx.hooks.onMaxStaminaChangedUI(self)


	# 对齐 Character.gd:958-962
	def reduceMaxStamina(self, amount):
		self.maxStamina = max(1, self.maxStamina - amount)
		self.curStamina = min(self.maxStamina, self.curStamina)
		self.ctx.hooks.onMaxStaminaChangedUI(self)


	# 对齐 Character.gd:979-992（label 走钩子；filled 语义逐字保留）
	def gainMaxStaminaTemporary(self, amount, item, triggerEvent, filled=True):
		if amount != 0:
			self.temporaryMaxStamina += amount
			if filled and amount > 0:
				self.curStamina += amount
			if item != None:
				event = self.ctx.combat_log.createEvent_TemporaryMaxStamina(item, amount, triggerEvent)
				self.ctx.bus.logEvent(event)
				if filled:
					item.staminaChanged(amount, _R.C("CoreConst").StackChangeType.Added_Player)
				self.ctx.hooks.spawnLabelOnItem(_R.C("CoreConst").EventType.TemporaryMaxStamina, item, amount)
			self.ctx.hooks.onMaxStaminaChangedUI(self)


	# 对齐 Character.gd:1100-1102
	def getStaminaRegeneration(self):
		return self.staminaRegen


	# 对齐 Character.gd:1103-1106
	def giveStaminaRegeneration(self, amount):
		self.staminaRegen += amount
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.StaminaRegen)


	# 对齐 Character.gd:1107-1121（INVENTORY.getItems() → 本内核的 items）
	def getTotalStaminaUsage(self):
		totalStaminaUse = 0.0
		for item in _iter(self.items):
			staminaUse = item.getStaminaCost()
			if item.getCooldown() > 0:
				staminaUse /= item.getCooldown()
			totalStaminaUse += staminaUse
		return totalStaminaUse


	# 对齐 Character.gd:963-969（call_deferred → ctx.defer，帧末 flush）
	def changeBaseMaxStamina(self):
		if self.playerId == self.ID.PLAYER and not self.staminaUpdateQueued:
			self.staminaUpdateQueued = True
			self.ctx.defer(self, "recalculateMaxStamina")


	# 对齐 Character.gd:970-978
	# staminaSackDescriptor = getDescriptor("Stamina Sack")（ItemBook.gd:1003），
	# 内核以 descriptor.name 等值比较替代描述符对象同一性比较（取值域相同）。
	def recalculateMaxStamina(self):
		self.staminaUpdateQueued = False
		self.maxStamina = self.getBaseMaxStamina()
		for item in _iter(self.items):
			if item.descriptor.name == "Stamina Sack":
				self.maxStamina += 1
		self.curStamina = self.maxStamina
		self.ctx.hooks.onMaxStaminaChangedUI(self)


	# ─────────────────────────── 生命上限修正（源码补全，对齐 Character.gd:903-927） ───────────────────────────

	# 对齐 Character.gd:907-909
	def getTemporaryMaxHealth(self):
		return self.temporaryMaxHealth


	# 对齐 Character.gd:910-913
	def setTemporaryMaxHealth(self, tempHealth):
		self.temporaryMaxHealth = tempHealth
		self.ctx.hooks.onHealthChangedUI(self)


	# 对齐 Character.gd:923-927
	def reduceMaxHealth(self, amount):
		self.maxHealth = max(1, self.maxHealth - amount)
		self.curHealth = min(self.maxHealth, self.curHealth)
		self.ctx.hooks.onHealthChangedUI(self)


	# 对齐 Character.gd:903-906
	def changeMaxHealthGain(self, amount):
		self.temporaryMaxHealthGain += amount
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.MaxHealthGain)


	# ─────────────────────────── 伤害修正量（源码补全，对齐 Character.gd:1369-1517） ───────────────────────────

	# 对齐 Character.gd:1379-1381
	def changeDamageReduction(self, amount):
		self.damageReduction += amount


	# 对齐 Character.gd:1369-1378
	def changeDamageResistance(self, amount, item=None, duration=None, triggerEvent=None):

		self.damageResistance += amount
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.DamageResistance)
		if item != None:
			event = self.ctx.combat_log.createEvent_DamChange(item, - amount,
				True, duration, None, triggerEvent)
			self.ctx.bus.logEvent(event)


	# 对齐 Character.gd:1494-1508（INVENTORY.getItems() → items）
	def changeTypedDamageFactor(self, damageType, amount):
		self.typedDamageFactors[damageType] += amount
		for item in _iter(self.items):
			if item.damageSource != None and item.damageSource.hasType(damageType):
				self.ctx.combat_log.snapshotItemTooltipStat(item, _R.C("CoreConst").ItemStat.MinDamage)
				self.ctx.combat_log.snapshotItemTooltipStat(item, _R.C("CoreConst").ItemStat.MaxDamage)

		if damageType == _R.C("CoreDamageSource").Type.Melee:
				self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.MeleeDmgFactor)
		elif damageType == _R.C("CoreDamageSource").Type.Ranged:
				self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.RangedDmgFactor)
		elif damageType == _R.C("CoreDamageSource").Type.Effect:
				self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.EffectDmgFactor)


	# 对齐 Character.gd:1509-1517
	def changeEffectDamageFactor(self, amount):
		self.typedDamageFactors[_R.C("CoreDamageSource").Type.Effect] += amount
		self.typedDamageFactors[_R.C("CoreDamageSource").Type.Unhealing] += amount
		for item in _iter(self.items):
			if item.damageSource != None and item.damageSource.hasType(_R.C("CoreDamageSource").Type.Effect):
				self.ctx.combat_log.snapshotItemTooltipStat(item, _R.C("CoreConst").ItemStat.MinDamage)
				self.ctx.combat_log.snapshotItemTooltipStat(item, _R.C("CoreConst").ItemStat.MaxDamage)
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.EffectDmgFactor)


	# 对齐 Character.gd:1490-1493
	def changeEmpowerDamage(self, amount):
		self.empowerDamage += amount


	# ─────────────────────────── 暴击 / 保护 / 抵消（源码补全，对齐 Character.gd:1175-1456） ───────────────────────────

	# 对齐 Character.gd:1231-1233
	def changePoisonCritChancePercent(self, amount):
		self.poisonDamageSource.addCritChancePercent(amount)


	# 对齐 Character.gd:1234-1236
	def changeSpikesCritChancePercent(self, amount):
		self.spikeDamageSource.addCritChancePercent(amount)


	# 对齐 Character.gd:1439-1442
	def useCritToken(self):
		self.critTokens -= 1
		self.ctx.combat_log.snapshotCharacterStat(self, self.Stat.CritStacks)


	# 对齐 Character.gd:1282-1286
	def useMana(self, amount, item=None, triggerEvent=None):
		event = self.useStacks(_R.C("CoreConst").EventType.Mana, amount, item, triggerEvent)

		return event


	# 对齐 Character.gd:1450-1452
	def changeProtectionChance(self, buffType, chance):
		self.buffs[buffType].changeCleanseProtectionChance(chance)


	# 对齐 Character.gd:1453-1456
	def changeBuffProtectionChance(self, chance):
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			self.buffs[buff].changeCleanseProtectionChance(chance)


	# 对齐 Character.gd:1446-1449
	def changeDebuffProtectionChance(self, chance):
		for debuff in _iter(_R.C("CoreConst").getDebuffs()):
			self.buffs[debuff].changeCleanseProtectionChance(chance)


	# 对齐 Character.gd:1175-1178
	def changeBuffNullifyChances(self, chance):
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			self.changeResistChance(buff, chance)


	# 对齐 Character.gd:1179-1182（与上者成对的减益版本；原版以此形状存在）
	def changeDebuffNullifyChances(self, chance):
		for debuff in _iter(_R.C("CoreConst").getDebuffs()):
			self.changeResistChance(debuff, chance)


	# ─────────────────────────── 战怒 / 无敌查询（源码补全） ───────────────────────────

	# 对齐 Character.gd:1585-1587
	def addBattleRageDuration(self, dur):
		self.battleRageBonusDur += dur


	# 对齐 Character.gd:655-664
	def isVulnerable(self):
		return not self.invulnerable


	# ─────────────────────────── 每帧驱动 ───────────────────────────

	# 对齐 Character.gd:1029-1035（眩晕倒计时递减 + 体力再生）。
	# 追加三个一次性计时器的物理帧步进：原版由 Character.tscn 里的 Godot Timer 节点驱动
	# （InvulnerabilityTimer / BattleRageTimer / AutoRageTimer，均 one_shot=true）：
	#   InvulnerabilityTimer.timeout → invulnerabilityEnded()
	#   BattleRageTimer.timeout      → endBattleRage()
	#   AutoRageTimer.timeout        → startAutoRage()
	# 内核无 Timer 节点，改为在 60Hz 固定步长里递减，超时点触发**同一个方法**，
	# 因此事件与状态迁移次序与原版一致（唯一差别是计时精度来自定步长，见 gd_core_truth 第 6 节）。
	def physicsTick(self, delta):
		if self.isStunned():
			self.stunnedDuration -= delta
			if self.stunnedDuration <= 0.0:
				self.stunnedDuration = 0.0
				self.endStun()

		self.addStamina(self.staminaRegen * delta)

		if self._invul_active:
			self._invul_left -= delta
			if self._invul_left <= 0.0:
				self._invul_left = 0.0
				self._invul_active = False
				self.invulnerabilityEnded()

		if self._rage_active:
			self._rage_left -= delta
			if self._rage_left <= 0.0:
				self.endBattleRage()

		if self._autoRage_active:
			self._autoRage_left -= delta
			if self._autoRage_left <= 0.0:
				self._autoRage_left = 0.0
				self._autoRage_active = False
				self.startAutoRage()


	# Buff 临时栈超时（对齐 Godot Timer 的物理步进）
	def tickBuffs(self, delta):
		for buffType in _iter(self.buffs):
			self.buffs[buffType]._tick(delta)


_R.reg("res://gd_core/CoreCharacter.gd", CoreCharacter)
_R.reg("CoreCharacter", CoreCharacter)
_R.reg("CoreCharacter", CoreCharacter)
