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
if "_base_cls_Exclusive__BismuthCube" not in globals():
	from .Cube import Cube as _base_cls_Exclusive__BismuthCube





class Exclusive__BismuthCube(_base_cls_Exclusive__BismuthCube):

	resource_path = "res://gd_core_items/Exclusive/BismuthCube.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numActivations = 0
		self.buffCounter = 0
		self.nonOxidated = None
		self.buffsNeeded = None
		self.maxUses = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.setState(0)
		self.buffCounter = 0
		self.affectedItem = self.getFirstAffectedItem()
		self.connectToCharacterBuffs("onBuffsChanged")


	def onBuffsChanged(self, amount, event):
		remainingUses = self.maxUses - self.numActivations
		if remainingUses == 0:
			return

		if amount > 0:
			numProccs = 0
			self.buffCounter += amount
			while self.buffCounter > self.buffsNeeded:
				numProccs += 1
				self.buffCounter -= self.buffsNeeded

			numProccs = min(remainingUses, numProccs)

			if numProccs > 0:
				if self.affectedItem != None:
					if self.ctx.cube_advanced.get(self.affectedItem, self) == self:
						self.ctx.cube_advanced[self.affectedItem] = self
						self.affectedItem.advanceCooldownSeconds(self.cdAdvance * numProccs)
					else:
						self.affectedItem.advanceCooldownSeconds(self.cdAdvance * numProccs * self.penaltyFactor)

				self.giveRandomBuffs(numProccs)
				self.setState(self.numActivations + numProccs)
				self.miniActivate()


	def onShopEntered(self):
		self.onStateChanged(self.maxUses)


	def onStateChanged(self, _numActivations):
		self.numActivations = _numActivations

	def _readyInit(self):
		super()._readyInit()
		self.buffsNeeded = self.getP("buffs")
		self.maxUses = int(self.getP("max"))
		self.onStateChanged(self.maxUses)



_R.reg("res://gd_core_items/Exclusive/BismuthCube.gd", Exclusive__BismuthCube)
_R.reg("BismuthCube", Exclusive__BismuthCube)
