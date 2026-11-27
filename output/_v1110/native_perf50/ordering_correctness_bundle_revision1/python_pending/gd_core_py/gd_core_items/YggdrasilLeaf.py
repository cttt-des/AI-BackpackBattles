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
if "_base_cls_YggdrasilLeaf_2" not in globals():
	from .Item import Item_2 as _base_cls_YggdrasilLeaf_2





class YggdrasilLeaf_2(_base_cls_YggdrasilLeaf_2):

	resource_path = "res://gd_core_items/YggdrasilLeaf.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaUsed = 0
		self.manaNeeded = None


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.manaUsed = 0

		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")


	def onCombatStart(self):
		self.giveMana(self.getP1() * len(self.getAffectedItems()))
		self.giveRegeneration(self.getP2() * len(self.getAffectedItems()))
		self.activate()


	def onManaChanged(self, amount, event):
		if amount < 0 and event.getParam("used", False):
			# ★ np26fH：显式 int 截断（GDScript 语义冗余、py 转写必需）——py 侧事件
			#   amount 为 float（mana 系统 float 化），直加会把 manaUsed 浮化、
			#   _div(float,int)=真除 → activations 浮动 → heal 29/34/24 波动
			#   （run1151_r13 定谳）。gd 侧 int(int) 无害；gd_to_py 转写自带。
			self.manaUsed += int(- amount)
			activations = _div(self.manaUsed, self.manaNeeded)
			self.manaUsed %= self.manaNeeded
			if activations >= 1:
				self.heal(self.getP_m("heal") * activations, event)
				self.cleanseRandomDebuffs(self.getP5() * activations, event)
				self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP3())


_R.reg("res://gd_core_items/YggdrasilLeaf.gd", YggdrasilLeaf_2)
_R.reg("YggdrasilLeaf", YggdrasilLeaf_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
