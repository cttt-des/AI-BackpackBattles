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
if "_base_cls_Exclusive__Wisp" not in globals():
	from ..Gems.Gem import Gem as _base_cls_Exclusive__Wisp





class Exclusive__Wisp(_base_cls_Exclusive__Wisp):

	resource_path = "res://gd_core_items/Exclusive/Wisp.gd"

	def _init_fields(self):
		super()._init_fields()
		self._damageAcc = 0
		self.luck = None
		self.regen = None
		self.natureSpeed = None
		self.damageForSpikes = None
		self.spikes = None

	@property
	def damageAcc(self):
		return self._damageAcc
	@damageAcc.setter
	def damageAcc(self, v):
		self._damageAcc = int(v)
	gemColor = Color(0.783203, 0.972054, 1)

	def hasCooldown(self):
		return (self.getGemMode() == self.GemMode.Inventory or 
				self.getGemMode() == self.GemMode.Armor)


	def canAffect(self, item):
		return item.hasType(_H_1)


	def prepareInventory(self):
		self.addSpeed(self.getNumAffectedItems() * self.natureSpeed)


	def prepareWeapon(self):
		self.damageAcc = 0
		self.connectForCombat(self.socket.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit():
			self.damageAcc += damageRes.damage
			numProccs = _div(self.damageAcc, self.damageForSpikes)
			if numProccs > 0:
				self.damageAcc %= self.damageForSpikes
				self.giveSpikes(self.spikes * numProccs)
				self.miniActivate()


	def combatStart(self):
		if self.getGemMode() == self.GemMode.Inventory:
				self.baseCooldownOverride = self.getBaseCooldownIndex(0)
		elif self.getGemMode() == self.GemMode.Armor:
				self.baseCooldownOverride = self.getBaseCooldownIndex(1)
		super().combatStart()


	def doCooldownEffect(self):
		if self.getGemMode() == self.GemMode.Inventory:
				self.giveLucky(self.luck)
				self.giveRegeneration(self.regen)
				self.onAfterEffectFinished()

		elif self.getGemMode() == self.GemMode.Armor:
				bonusHealth = _div(self.getP_m('maxhealth'), 100.0) * self.character().getCurrentHealth()
				bonusHealth *= self.getGemPower()
				self.giveMaxHealth(bonusHealth)
				self.onAfterEffectFinished(False)
				self.consumed = True
				self.miniActivate()


	def playPickupSound(self):
		# decomp Items/Exclusive/Wisp.gd:62 Sound.playSound_process(pickupSound, - 8, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/Wisp.gd:66 Sound.playSound(dropSound, volume - 8, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.regen = int(self.getP("regen"))
		self.natureSpeed = _div(self.getP('speed'), 100.0)
		self.damageForSpikes = int(self.getP("dam"))
		self.spikes = int(self.getP("spikes"))


_R.reg("res://gd_core_items/Exclusive/Wisp.gd", Exclusive__Wisp)
_R.reg("Wisp", Exclusive__Wisp)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
