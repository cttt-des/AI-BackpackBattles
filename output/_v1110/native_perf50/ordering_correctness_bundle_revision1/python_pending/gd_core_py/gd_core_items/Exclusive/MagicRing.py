# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import (  # noqa: F401

    Color,
    Dictionary,
    EnumDict,
    FuncRef,
    GD_DEFAULT,
    INF,
    NAN,
    Node,
    Node2D,
    OS_has_feature,
    Object,
    PCG32,
    PI,
    PoolStringArray,
    RandomNumberGenerator,
    Reference,
    Resource,
    Signal,
    String,
    TAU,
    TYPE_VECTOR2,
    Vector2,
    Vector3,
    _HoistPending,
    _bind_battle,
    _div,
    _dup,
    _erase,
    _fill,
    _find,
    _gd_fmt,
    _gd_range,
    _gd_str,
    _get_slice,
    _gid,
    _has_behavior_cache_get,
    _has_behavior_cache_put,
    _hash,
    _invert,
    _iter,
    _join,
    _load,
    _mod,
    _os_environ_get,
    _pick_random,
    _pop_at,
    _resize,
    _shuffle,
    _sort_custom,
    _strv,
    _substr,
    ceil,
    clamp,
    deg2rad,
    f32,
    floor,
    fmod,
    gd_round,
    get_stack,
    inverse_lerp,
    is_equal_approx,
    is_instance_valid,
    lerp,
    move_toward,
    posmod,
    pow,
    rad2deg,
    randomize,
    round,
    sign,
    smoothstep,
    snapped,
    sqrt,
    stepify,
    tr,
    typeof,
    wrapf,
    wrapi
,
)

if "GodotObject" not in globals():
	from ..._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from ... import _registry as _R
if "_base_cls_Exclusive__MagicRing" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__MagicRing





class RingEffect(GodotObject):
	def _init_fields(self):
		super()._init_fields()
		self._triggerType = 0
		self._stackType = 0

	@property
	def triggerType(self):
		return self._triggerType
	@triggerType.setter
	def triggerType(self, v):
		self._triggerType = int(v)
	@property
	def stackType(self):
		return self._stackType
	@stackType.setter
	def stackType(self, v):
		self._stackType = int(v)

	def pushEncoded(self, bitStream):
		normalizedStack = self.stackType - _H_2
		bitStream.push(self.triggerType, len(TriggerType))
		bitStream.push(normalizedStack, 16)


	def setFromEncoded(self, bitStream):
		self.triggerType = bitStream.pull(len(TriggerType))
		self.stackType = bitStream.pull(16) + _H_2





class Exclusive__MagicRing(_base_cls_Exclusive__MagicRing):

	resource_path = "res://gd_core_items/Exclusive/MagicRing.gd"

	TriggerType = EnumDict("TriggerType", {"StartOfBattle": 0, "Every": 1, "PlayerLow": 2, "OppoLow": 3})



	def _init_fields(self):
		super()._init_fields()
		self.stackToTypes = { _H_2: _H_12, _H_3: _H_12, _H_4: _H_13, _H_5: _H_14, _H_6: _H_15, _H_7: _H_13, _H_8: _H_16, _H_9: _H_17, _H_10: _H_18, _H_11: _H_12, }
		self.stackToColor = { _H_2: Color(0.329826, 1, 0.263672), _H_3: Color(0.700867, 1, 0.263672), _H_4: Color(1, 0.388672, 0.696724), _H_5: Color(1.1, 0.44, 0.24), _H_6: Color(0.900391, 0.04924, 0.04924), _H_7: Color(0.955078, 0.665003, 0.341366), _H_8: Color(0.257812, 0.330292, 1), _H_9: Color(0.569776, 0.196078, 1), _H_10: Color(0.196078, 0.952895, 1), _H_11: Color(0.008865, 0.648438, 0.176254) }
		self.effects = []
		self.effectDict = {}
		self._gainedStacks = 0
		self.playerLowTriggered = False
		self.oppoLowTriggered = False
		self.ringTypes = []
		self._textEffect = 0
		self.numEffects = None
		self.healthThreshold = None
		self.opponentHealthThreshold = None
		self.stones = None
		self.symbols = None

	@property
	def gainedStacks(self):
		return self._gainedStacks
	@gainedStacks.setter
	def gainedStacks(self, v):
		self._gainedStacks = int(v)
	@property
	def textEffect(self):
		return self._textEffect
	@textEffect.setter
	def textEffect(self, v):
		self._textEffect = int(v)

	def hasCooldown(self):
		return self.TriggerType.Every in self.effectDict


	def hasStartofBattle(self):
		return self.TriggerType.StartOfBattle in self.effectDict


	def onPrepare(self):
		self.playerLowTriggered = False
		self.oppoLowTriggered = False

		if self.TriggerType.PlayerLow in self.effectDict:
			self.connectForCombat(self.character(), "character_damaged", "onDamaged")

		if self.TriggerType.OppoLow in self.effectDict:
			self.connectForCombat(self.opponent(), "character_damaged", "onOppoDamaged")


	def onCombatStart(self):
		for effect in _iter(self.effectDict[self.TriggerType.StartOfBattle]):
			self.giveStacksFromEffect(effect)


	def doCooldownEffect(self):
		for effect in _iter(self.effectDict[self.TriggerType.Every]):
			self.giveStacksFromEffect(effect)


	def onDamaged(self, _healthChange, event):
		if self.playerLowTriggered:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.playerLowTriggered = True
			for effect in _iter(self.effectDict[self.TriggerType.PlayerLow]):
				self.giveStacksFromEffect(effect, event)


	def onOppoDamaged(self, _healthChange, event):
		if self.oppoLowTriggered:
			return

		relHealth = self.opponent().getRelativeHealth()
		if relHealth < self.opponentHealthThreshold:
			self.oppoLowTriggered = True
			for effect in _iter(self.effectDict[self.TriggerType.OppoLow]):
				self.giveStacksFromEffect(effect, event)


	def giveStacksFromEffect(self, effect, triggerEvent=None):
		target = None
		if _H_1.isBuff(effect.stackType):
			target = self.character()
		else:
			target = self.opponent()

		stackName = self.ctx.event_type_keys[effect.stackType].lower()
		paramScale = self.getP(_strv("scale", effect.triggerType + 1))
		self.giveStacks(target, effect.stackType, 
			self.getScaledParam(stackName, paramScale), triggerEvent)

		self.activate()



	def sortEffects(self):
		_iter__loc = _iter
		self.gainedStacks = 0
		self.effectDict.clear()
		self.ringTypes.clear()

		effectI = 0
		for effect in (self.effects if self.effects.__class__ is list else _iter__loc(self.effects)):
			effectI += 1

		if not self.isOnlyForDisplay():

			for effect in (self.effects if self.effects.__class__ is list else _iter__loc(self.effects)):
				self.ctx.util.dictAppend(self.effectDict, effect.triggerType, effect)

				self.gainedStacks |= 2 << (effect.stackType - _H_2)

				newType = self.stackToTypes[effect.stackType]
				if not newType in self.ringTypes:
					self.ringTypes.append(newType)


			if self.inventory != None:
				self.inventory.onItemTypeChanged(self)
		else:
			pass


	def getTypes(self):
		return super().getTypes() + self.ringTypes


	def hasType(self, type):
		type = int(type)
		return type in self.ringTypes or super().hasType(type)


	def getNumStaticTypes(self):
		return super().getNumStaticTypes() + len(self.ringTypes)


	def gainsStack(self, stackType):
		return self.gainedStacks & stackType


	def gainsBuffs(self):
		return self.gainedStacks & _H_19


	def inflictsDebuffs(self):
		return self.gainedStacks & _H_20


	def getTextEffect(self):
		return self.textEffect


	def randEffects(self, clearIfOnlyDisplay=True):
		self.effects.clear()

		for i in (self.numEffects if self.numEffects.__class__ is list else _iter(self.numEffects)):
			effect = RingEffect()
			self.effects.append(effect)
			effect.triggerType = self.ctx.rng.randi_range(0, 3)
			effect.stackType = self.ctx.rng.randi_range(_H_2, 
				_H_10)


		self.sortEffects()

		if clearIfOnlyDisplay and self.isOnlyForDisplay():
			self.effects.clear()


	# ★ np24 harness：crafted 效果真值注入（r34 的幽灵调用落地）——宿主
	#   （OracleAlignBattle.gd place_one / py 引擎 _build_side）在 _readyInit 的
	#   randEffects() 链位消耗之后调本方法，用 lineups.json 快照 3 的史真值
	#   （[{triggerType,stackType},...]）覆写随机效果。录制侧同语义：史流
	#   deserializeItems→setData 把真值写回（wasJustCrafted=false 时 randEffects
	#   照常消耗链位，随后被真值覆写）——重放必须同构：先 roll 后覆写，链位/效果
	#   双对齐。此前全树（oracle/decompiled/gd/py）皆无此方法，宿主
	#   has_method/hasattr 守卫恒假 ⇒ 两腿戒指效果恒为随机 roll（run695_r18
	#   Superior Ring idx18：gd/py (104,5) vs 语料真值 (105,6) 实证）。
	# ★ np25棋盘面重建回植：builder 从 decompiled 再生无此手补（chessfix 重建
	#   实测被冲掉），漏植则 np17-A 效果真值静默退化为随机 roll。
	def setCraftedEffects(self, crafted):
		self.effects.clear()
		for e in (crafted if crafted.__class__ is list else _iter(crafted)):
			effect = RingEffect()
			effect.triggerType = int(e["triggerType"])
			effect.stackType = int(e["stackType"])
			self.effects.append(effect)
		self.sortEffects()


	def getScaledParam(self, stackName, paramScale):
		return gd_round(self.getP(stackName) * paramScale)


	def isOnlyForDisplay(self):
		return (self.ownerType == _H_21 or 
			self.ownerType == _H_22 or 
			self.ownerType == _H_23 or 
			self.ownerType == _H_24 or 
			self.ownerType == _H_25)


	def getDescription(self, wrapInColor=True):
		return ""

	def copyFrom(self, otherRing):
		self.setData(otherRing.getData())


	def getData(self):
		pass

	def setData(self, _data):
		pass

	def persistDataInShop(self):
		return True


	def getDataPersistent(self, bitStream):
		for effect in (self.effects if self.effects.__class__ is list else _iter(self.effects)):
			effect.pushEncoded(bitStream)





	def getDataPersistentBits(self):
		return self.numEffects * (2 + 4)



	def onCraftedFrom(self, baseItem, ingredients):
		self.effects.clear()
		self.effects.extend(baseItem.effects)
		self.effects.extend(ingredients[0].effects)


		_pop_at(self.effects, self.ctx.rng.randi_range(0, 3))

		self.sortEffects()


















	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.numEffects = int(self.getP("effects"))
		self.healthThreshold = _div__loc(self.getP('healtht'), 100.0)
		self.opponentHealthThreshold = _div__loc(self.getP('healtht_opp'), 100.0)
		self.stones = []
		self.symbols = []
		if (not self.stones):
			for i in (self.numEffects if self.numEffects.__class__ is list else _iter(self.numEffects)):
				pass

		if self.ownerType == _H_21:
			pass
		else:

			if not self.wasJustCrafted:
				self.randEffects()


	RingEffect = RingEffect


_R.reg("res://gd_core_items/Exclusive/MagicRing.gd", Exclusive__MagicRing)
_R.reg("MagicRing", Exclusive__MagicRing)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreConst")
try:
	_H_10 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
	_H_10 = _HoistPending(_he)
try:
	_H_11 = _R.C("CoreConst").EventType.Poison
except AttributeError as _he:
	_H_11 = _HoistPending(_he)
try:
	_H_12 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
	_H_12 = _HoistPending(_he)
try:
	_H_13 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
	_H_13 = _HoistPending(_he)
try:
	_H_14 = _R.C("CoreConst").Type.Fire
except AttributeError as _he:
	_H_14 = _HoistPending(_he)
try:
	_H_15 = _R.C("CoreConst").Type.Vampiric
except AttributeError as _he:
	_H_15 = _HoistPending(_he)
try:
	_H_16 = _R.C("CoreConst").Type.Magic
except AttributeError as _he:
	_H_16 = _HoistPending(_he)
try:
	_H_17 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
	_H_17 = _HoistPending(_he)
try:
	_H_18 = _R.C("CoreConst").Type.Ice
except AttributeError as _he:
	_H_18 = _HoistPending(_he)
try:
	_H_19 = _R.C("CoreConst").Stack.Buff
except AttributeError as _he:
	_H_19 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").EventType.Lucky
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_20 = _R.C("CoreConst").Stack.Debuff
except AttributeError as _he:
	_H_20 = _HoistPending(_he)
try:
	_H_21 = _R.C("CoreConst").Owner.ItemLibrary
except AttributeError as _he:
	_H_21 = _HoistPending(_he)
try:
	_H_22 = _R.C("CoreConst").Owner.InfoPanelIcon
except AttributeError as _he:
	_H_22 = _HoistPending(_he)
try:
	_H_23 = _R.C("CoreConst").Owner.Tooltip
except AttributeError as _he:
	_H_23 = _HoistPending(_he)
try:
	_H_24 = _R.C("CoreConst").Owner.RecipeBook
except AttributeError as _he:
	_H_24 = _HoistPending(_he)
try:
	_H_25 = _R.C("CoreConst").Owner.BuildViewerIcon
except AttributeError as _he:
	_H_25 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").EventType.Spikes
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreConst").EventType.Regeneration
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreConst").EventType.Heat
except AttributeError as _he:
	_H_5 = _HoistPending(_he)
try:
	_H_6 = _R.C("CoreConst").EventType.Vampirism
except AttributeError as _he:
	_H_6 = _HoistPending(_he)
try:
	_H_7 = _R.C("CoreConst").EventType.Empower
except AttributeError as _he:
	_H_7 = _HoistPending(_he)
try:
	_H_8 = _R.C("CoreConst").EventType.Mana
except AttributeError as _he:
	_H_8 = _HoistPending(_he)
try:
	_H_9 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_9 = _HoistPending(_he)


# ── L1 跨类裸引用类属性提升（生成器发射）──
TriggerType = Exclusive__MagicRing.TriggerType
