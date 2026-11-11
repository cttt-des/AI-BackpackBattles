# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

from gd_core_py._rt cimport GodotObject


cdef class SignalConnection(GodotObject):

    cdef public object emitter
    cdef public object methodName
    cdef public object receiver
    cdef public object signalName


from gd_core_py.gd_core.CoreItem cimport CoreItem as _base_cls_Item


cdef class Item(_base_cls_Item):

    cdef public object _dropFrame
    cdef public object _pickupFaceDirection
    cdef public object _pickupFrame
    cdef public object affectedCellsActive
    cdef public object affordable
    cdef public object animation
    cdef public object averagedPosition
    cdef public object baseBounce
    cdef public object baseFriction
    cdef public object bondVisuals
    cdef public object bondedBaseItem
    cdef public object bondedIngredients
    cdef public object bonusRotation
    cdef public object bound
    cdef public object brightColor
    cdef public object buildIntoRecipesTooltip
    cdef public object canAffectVisuals
    cdef public object canCancelShaderTween
    cdef public object clickArea
    cdef public object collisionMap
    cdef public object collisionShape
    cdef public object craftingAniReadyTime
    cdef public object craftingLabel
    cdef public object curRecipe
    cdef public object defaultColor
    cdef public object dragParticles
    cdef public object dragParticlesEnabled
    cdef public object draggedInsideItems
    cdef public object draggingParent
    cdef public object focus
    cdef public object focusEnabled
    cdef public object frictionTime
    cdef public object fuseParticles1
    cdef public object fuseParticles2
    cdef public object fuseTween
    cdef public object fusing
    cdef public object fusingBonds
    cdef public object globalAffectVisuals
    cdef public object hasSquishySprite
    cdef public object hoverResponseEnabled
    cdef public object hovered
    cdef public object impactSoundReadyTime
    cdef public object impactSoundVolume
    cdef public object initialized
    cdef public object insideRotationNode
    cdef public object lastCollider
    cdef public object lastCollisionPos
    cdef public object lastVelocity
    cdef public object lock
    cdef public object lockAnimation
    cdef public object locked
    cdef public object me
    cdef public object momentum
    cdef public object momentumStrength
    cdef public object mouseIsOverItem
    cdef public object mouseWheelRotationReadyTime
    cdef public object movebackTween
    cdef public object nonRotatedProgress
    cdef public object notEnoughGoldLabelReadyTime
    cdef public object numStackChangeTypes
    cdef public object ownerTypesWithBuildTooltip
    cdef public object owningBuildIntoRecipesTooltip
    cdef public object pickingEnabled
    cdef public object pickupPosition
    cdef public object pickupRotation
    cdef public object pickupTopLeftCell
    cdef public object pooled
    cdef public object progressMaterial
    cdef public object rotationMomentum
    cdef public object rotationTween
    cdef public object sameOrientationAsPickup
    cdef public object shaderTween
    cdef public object shadowOffset
    cdef public object shadowTween
    cdef public object shadows
    cdef public object sockets
    cdef public object sold
    cdef public object specificDragParticles
    cdef public object spotlight
    cdef public object sprite
    cdef public object spriteScale
    cdef public object spritesWithShadows
    cdef public object tooltip
    cdef public object tooltipEnabled
    cdef public object tooltipMargin
    cdef public object tooltipUpdateQueued
    cdef public object totalWeight
    cdef public object wasJustCrafted
    cdef public object willBeConsumed

