"""最小验证：ctypes 直接调 Steamworks 读排行榜（不启动游戏）。

依赖：steam_api64.dll 副本、steam_appid.txt、Steam 客户端在线。
"""
import ctypes
import json
import os
import sys
import time

DLL_CANDIDATES = [
    os.path.join(os.getcwd(), "output", "probe_run", "steam_api64.dll"),
    r"D:\Steam\steamapps\common\Backpack Battles\steam_api64.dll",
]


def load_api(path=None):
    for cand in ([path] if path else DLL_CANDIDATES):
        if cand and os.path.exists(cand):
            return ctypes.WinDLL(cand), cand
    raise FileNotFoundError("steam_api64.dll 未找到")


def describe(api):
    out = {}
    for name in ("SteamAPI_InitSafe", "SteamAPI_InitAnonymousUser", "SteamAPI_GetHSteamUser",
                 "SteamAPI_GetHSteamPipe", "SteamAPI_SteamUserStats_v012",
                 "SteamAPI_ISteamUserStats_FindLeaderboard",
                 "SteamAPI_ISteamUserStats_DownloadLeaderboardEntries",
                 "SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry",
                 "SteamAPI_ISteamUserStats_GetLeaderboardEntryCount",
                 "SteamAPI_RunCallbacks", "SteamAPI_Shutdown"):
        out[name] = hasattr(api, name)
    return out


def main():
    api, path = load_api()
    info = {"dll": path, "exports": describe(api)}
    api.SteamAPI_InitSafe.restype = ctypes.c_bool
    api.SteamAPI_InitSafe.argtypes = []
    info["init_safe"] = bool(api.SteamAPI_InitSafe())
    if not info["init_safe"]:
        info["init_anon"] = bool(api.SteamAPI_InitAnonymousUser()) if hasattr(api, "SteamAPI_InitAnonymousUser") else None
        info["anonymous_used"] = True
    info["h_user"] = int(api.SteamAPI_GetHSteamUser())
    info["h_pipe"] = int(api.SteamAPI_GetHSteamPipe())
    out = os.path.join(os.getcwd(), "_probe_sites", "ctypes_steam.json")
    with open(out, "w", encoding="utf-8") as f:
        json.dump(info, f, ensure_ascii=False, indent=2)
    print(json.dumps(info, ensure_ascii=False)[:800])


if __name__ == "__main__":
    main()
