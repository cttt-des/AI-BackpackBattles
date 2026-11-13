# cython: language_level=3
# cython: binding=True
"""量化「循环变量有无 C 类型」对热循环的影响。

三个类：Typed（cdef 类，有两属性）、Loop 里分别用 untyped / typed 遍历。
物品树现状 = untyped（CoreCombat.py 无 cimport）；提案 = typed。
"""
ctypedef double D


cdef class Base:
    cdef public double triggerTime
    cdef public bint cooldown
    cdef public double speed
    cdef public object ch

    def __init__(self, double tt, bint cd, double sp, object ch):
        self.triggerTime = tt
        self.cooldown = cd
        self.speed = sp
        self.ch = ch

    # ★ 与真实内核一致：§11.7 已把 getSpeed 改成 cpdef double
    #   （Python 可见 + C 直调），这里必须照抄，否则微基准测的不是现状。
    cpdef double getSpeed(self):
        return self.speed

    def character(self):
        return self.ch


cdef class Champ:
    cdef public D stunnedDuration

    def __init__(self, double sd):
        self.stunnedDuration = sd


def run_untyped(list items, D delta, int reps):
    """现状写法：item 是 PyObject，每次属性访问走 getattr。"""
    cdef int r, i, n
    cdef object item
    cdef double acc = 0.0
    n = len(items)
    for r in range(reps):
        for i in range(n):
            item = items[i]
            if item.cooldown:
                if not (item.character().stunnedDuration > 0):
                    item.triggerTime = item.triggerTime - delta * item.getSpeed()
                    acc += item.triggerTime
    return acc


def run_typed(list items, D delta, int reps):
    """提案写法：item 是 cdef Base，属性访问是 C 结构体偏移。"""
    cdef int r, i, n
    cdef Base item
    cdef double acc = 0.0
    cdef double dt = delta
    n = len(items)
    for r in range(reps):
        for i in range(n):
            item = <Base>items[i]
            if item.cooldown:
                if not (<Champ>item.ch).stunnedDuration > 0:
                    item.triggerTime = item.triggerTime - dt * item.getSpeed()
                    acc += item.triggerTime
    return acc
