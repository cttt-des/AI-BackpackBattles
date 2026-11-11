# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import (  # noqa: F401

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
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_MrStruggles_2" not in globals():
	from .Item import Item_2 as _base_cls_MrStruggles_2





class MrStruggles_2(_base_cls_MrStruggles_2):

	resource_path = "res://gd_core_items/MrStruggles.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.speedbuffTimer = None
		self.activationParticles = None
		self.healthThreshold = None
		self.bonusSpeed = None
		self.fatigueDam = None
		self.speedBuffParticles1 = None
		self.speedBuffParticles2 = None

	plushies = ["Mrs Struggles", "Miss Fortune"]

	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		_ch = self.character()
		for debuff in _iter(_H_1.getDebuffs()):
			self.connectForCombat(_ch, _ch.buffs[debuff].signalName, 
			"onDebuffed")


		self.hasActivated = False
		self.setState(False)
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True
			self.setState(True)
			for item in _iter(self.getAffectedItems()):
				item.addSpeed(self.bonusSpeed)
			self.speedbuffTimer.start(self.getP_m("dur_speed"))


	def onSpeedbuffTimeout(self):
		self.setState(False)
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.bonusSpeed)


	def onDebuffed(self, amount, event):
		# ★ np24 诊断（受控）：镜像神谕 MSROLL 行（oracle/Items/MrStruggles.gd 取证桩
		#   同位），逐次记录掷点前的 BalancedRng 状态与 chance 修正，供两侧对位。
		#   np25棋盘面重建回植（builder 无此手补，chessfix 重建实测被冲掉）。
		self.ctx.rng.trace_diag("MSROLL", String(self.descriptor.identifier), int(self.ownerType),
				"type=" + str(event.type) + " amt=" + str(amount)
				+ " ew=" + str(self.chanceRng.expectedWins) + " w=" + str(self.chanceRng.wins)
				+ " lr=" + str(self.chanceRng.lastResult))
		if self.checkTriggerCount(10):
			if self.rollChance():
				debuffType = event.type
				dur = event.getParam("duration", - 1)
				self.giveStacksTemporary(self.opponent(), debuffType, amount, dur, event)



	def doCooldownEffect(self):
		self.inflictFatigueDamage(self.fatigueDam)
		self.activate()






	def onCombatEnd(self):
		self.speedbuffTimer.stop()


	def getTriggerPriority(self):
		return _H_2 + 3


	def getDescription(self, wrapInColor=True):
		return ""

	def rollShopChance(self, shopChance=GD_DEFAULT):
		if shopChance is GD_DEFAULT:
			shopChance = self.descriptor.shopChance
		return False

	def getGatedDescriptor(self, rarity):
		return self.ctx.item_book.getDescriptor(self.ctx.util.pickRandomElement(self.plushies))


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, speedBuffActive):
		if speedBuffActive:
			pass
		else:
			pass


	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.speedbuffTimer = self.newItemTimer("SpeedbuffTimer", "onSpeedbuffTimeout", False)
		self.healthThreshold = _div__loc(self.getP2(), 100.0) - 0.0001
		self.bonusSpeed = _div__loc(self.getP3(), 100.0)
		self.fatigueDam = int(self.getP1())


_R.reg("res://gd_core_items/MrStruggles.gd", MrStruggles_2)
_R.reg("MrStruggles", MrStruggles_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreConst")
try:
	_H_2 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
