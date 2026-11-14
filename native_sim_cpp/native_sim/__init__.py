"""Native C++20 GDScript 3.6 combat simulator package."""

from .sim import (
    BattleOptions,
    BattleResult,
    NativeSimulator,
    PackedSideHandle,
    get_simulator,
)

__all__ = [
    "BattleOptions",
    "BattleResult",
    "NativeSimulator",
    "PackedSideHandle",
    "get_simulator",
]
