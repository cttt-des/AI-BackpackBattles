"""Steam 排行榜直连（需游戏进程上下文或 publisher key）。

实测结论：独立进程调用 FindLeaderboard 恒返回 ioFailure=1（handle=0），
即使 Steam 已登录、app 已拥有、UserStats 通道可用。因此本模块提供两种可选后端：

1. web：Steam Web API GetLeaderboardData（需要该 app 的 publisher key）
2. dll：ctypes 直调 Steamworks（仅当调用方本身是游戏进程时可用）

默认不可用，调用即抛错，由采集器回退到公开数据源。
"""
from __future__ import annotations

import json
import os
import urllib.error
import urllib.parse
import urllib.request
from pathlib import Path
from typing import Any

UA = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 Chrome/126.0 Safari/537.36"
APP_ID = 2427700
BOARD = "bpb-runs3"


def leaderboard_via_web(*, api_key: str, board: str = BOARD, start: int = 1,
                        end: int = 2000, app_id: int = APP_ID) -> bytes:
    """Steam Web API：需要 publisher 权限的 key。"""
    query = urllib.parse.urlencode({
        "key": api_key,
        "appid": app_id,
        "leaderboardid": board,
        "rangestart": start,
        "rangeend": end,
    })
    url = f"https://api.steampowered.com/ISteamUserStats/GetLeaderboardData/v1/?{query}"
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    try:
        with urllib.request.urlopen(req, timeout=60) as response:
            return response.read()
    except urllib.error.HTTPError as error:
        body = error.read()[:300].decode("utf-8", "replace")
        raise RuntimeError(f"GetLeaderboardData 失败 {error.code}: {body}") from error


def leaderboard_via_dll(dll_path: Path, board: str = BOARD) -> dict[str, Any]:
    """ctypes 直调；仅在被游戏进程调用时有效（独立进程恒 ioFailure）。"""
    import ctypes
    from ctypes import c_bool, c_char_p, c_int32, c_uint64, byref, Structure, POINTER

    if not Path(dll_path).exists():
        raise FileNotFoundError(dll_path)

    class Msg(Structure):
        _fields_ = [("user", c_int32), ("id", c_int32), ("param", ctypes.c_void_p), ("size", c_int32)]

    api = ctypes.WinDLL(str(dll_path))
    api.SteamAPI_InitSafe.restype = c_bool
    if not api.SteamAPI_InitSafe():
        raise RuntimeError("Steam 初始化失败")
    pipe = api.SteamAPI_GetHSteamPipe()
    api.SteamAPI_ManualDispatch_Init()
    api.SteamAPI_ManualDispatch_RunFrame.argtypes = [c_int32]
    api.SteamAPI_ManualDispatch_GetNextCallback.argtypes = [c_int32, POINTER(Msg)]
    api.SteamAPI_ManualDispatch_GetAPICallResult.restype = c_bool
    api.SteamAPI_SteamUserStats_v012.restype = ctypes.c_void_p
    stats = api.SteamAPI_SteamUserStats_v012()
    api.SteamAPI_ISteamUserStats_FindLeaderboard.restype = c_uint64
    api.SteamAPI_ISteamUserStats_FindLeaderboard.argtypes = [ctypes.c_void_p, c_char_p]
    call = api.SteamAPI_ISteamUserStats_FindLeaderboard(stats, board.encode())
    return {"call": str(call), "note": "独立进程下预期 ioFailure=1"}


def steam_batch_available() -> dict[str, Any]:
    """报告 Steam 直连的实测状态，供采集器决定是否回退。"""
    return {
        "app_id": APP_ID,
        "board": BOARD,
        "web_api": {"available": bool(os.environ.get("STEAM_WEB_API_KEY"))},
        "dll_direct": {"available": False, "reason": "独立进程 FindLeaderboard 恒 ioFailure=1"},
    }
