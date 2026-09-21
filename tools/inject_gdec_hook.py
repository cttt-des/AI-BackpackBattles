"""
Inject gdec_hook.dll into a fresh game instance at maximum speed.
Strategy: normal CreateProcess → inject within milliseconds (before startup
decryption storm ends) → poll every 0.5s for candidates.
The key only lives briefly during startup; we must hook it then.
"""
import ctypes, ctypes.wintypes as wt, os, sys, time, struct, subprocess, threading

k32 = ctypes.windll.kernel32

DLL  = r"C:\Users\Windows\AppData\Local\Temp\gdec_hook.dll"
LOG  = r"C:\Users\Windows\AppData\Local\Temp\bp_hook_candidates.log"
STAT = r"C:\Users\Windows\AppData\Local\Temp\bp_hook_stats.txt"
OUT  = r"C:\Users\Windows\AppData\Local\Temp\hook_validated.txt"
EXE  = r"D:\steam\steamapps\common\Backpack Battles\BackpackBattles.exe"
GDE_SAMPLE = r"D:\文件资料\学习\自动背包AI\extracted\addons\controller_icons\ControllerIcons.gde"

PROCESS_ALL = 0x1F0FFF
MEM_CMIT, MEM_RESERVE = 0x1000, 0x2000
PAGE_RW = 0x04

# ── manual structs ──
class MEMORY_BASIC_INFORMATION(ctypes.Structure):
    _fields_ = [
        ("BaseAddress",      ctypes.c_void_p),
        ("AllocationBase",   ctypes.c_void_p),
        ("AllocationProtect", wt.DWORD),
        ("RegionSize",       ctypes.c_size_t),
        ("State",            wt.DWORD),
        ("Protect",          wt.DWORD),
        ("Type",             wt.DWORD),
    ]

class STARTUPINFOW(ctypes.Structure):
    _fields_ = [("cb", wt.DWORD), ("lpReserved", wt.LPWSTR), ("lpDesktop", wt.LPWSTR),
                ("lpTitle", wt.LPWSTR), ("dwX", wt.DWORD), ("dwY", wt.DWORD),
                ("dwXSize", wt.DWORD), ("dwYSize", wt.DWORD), ("dwXCountChars", wt.DWORD),
                ("dwYCountChars", wt.DWORD), ("dwFillAttribute", wt.DWORD),
                ("dwFlags", wt.DWORD), ("wShowWindow", wt.WORD),
                ("cbReserved2", wt.WORD), ("lpReserved2", ctypes.c_void_p),
                ("hStdInput", wt.HANDLE), ("hStdOutput", wt.HANDLE), ("hStdError", wt.HANDLE)]

class PROCESS_INFORMATION(ctypes.Structure):
    _fields_ = [("hProcess", wt.HANDLE), ("hThread", wt.HANDLE),
                ("dwProcessId", wt.DWORD), ("dwThreadId", wt.DWORD)]

# ── ctypes prototypes ──
k32.OpenProcess.restype       = wt.HANDLE
k32.OpenProcess.argtypes      = [wt.DWORD, wt.BOOL, wt.DWORD]
k32.VirtualAllocEx.restype    = ctypes.c_void_p
k32.VirtualAllocEx.argtypes   = [wt.HANDLE, ctypes.c_void_p, ctypes.c_size_t, wt.DWORD, wt.DWORD]
k32.VirtualQuery.restype      = ctypes.c_size_t
k32.VirtualQuery.argtypes     = [ctypes.c_void_p, ctypes.POINTER(MEMORY_BASIC_INFORMATION), ctypes.c_size_t]
k32.WriteProcessMemory.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t)]
k32.ReadProcessMemory.restype  = ctypes.c_size_t
k32.ReadProcessMemory.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t)]
k32.GetModuleHandleW.restype   = wt.HMODULE
k32.GetModuleHandleW.argtypes = [wt.LPCWSTR]
k32.GetProcAddress.restype     = ctypes.c_void_p
k32.GetProcAddress.argtypes    = [wt.HMODULE, wt.LPCSTR]
k32.CreateRemoteThread.restype = wt.HANDLE
k32.CreateRemoteThread.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.c_size_t, ctypes.c_void_p,
                                     ctypes.c_void_p, wt.DWORD, ctypes.POINTER(wt.DWORD)]
k32.WaitForSingleObject.restype = wt.DWORD
k32.WaitForSingleObject.argtypes = [wt.HANDLE, wt.DWORD]
k32.GetExitCodeThread.restype  = wt.DWORD
k32.GetExitCodeThread.argtypes = [wt.HANDLE, ctypes.POINTER(wt.DWORD)]
k32.CreateProcessW.argtypes    = [wt.LPCWSTR, wt.LPWSTR, ctypes.c_void_p, ctypes.c_void_p,
                                    wt.BOOL, wt.DWORD, ctypes.c_void_p, wt.LPCWSTR,
                                    ctypes.POINTER(STARTUPINFOW), ctypes.POINTER(PROCESS_INFORMATION)]
k32.VirtualFreeEx.restype    = wt.BOOL
k32.VirtualFreeEx.argtypes  = [wt.HANDLE, ctypes.c_void_p, ctypes.c_size_t, wt.DWORD]
k32.CloseHandle.restype      = wt.BOOL
k32.CloseHandle.argtypes     = [wt.HANDLE]
k32.TerminateProcess.restype = wt.BOOL
k32.TerminateProcess.argtypes = [wt.HANDLE, wt.UINT]


def inject_dll(h_process: wt.HANDLE, dll_path: str) -> bool:
    path_w = (dll_path + '\0').encode('utf-16-le')
    remote = k32.VirtualAllocEx(h_process, None, len(path_w),
                                  MEM_CMIT | MEM_RESERVE, PAGE_RW)
    if not remote:
        print(f"  VirtualAllocEx failed err={ctypes.GetLastError()}")
        return False
    written = ctypes.c_size_t(0)
    if not k32.WriteProcessMemory(h_process, remote, path_w, len(path_w), ctypes.byref(written)):
        print(f"  WriteProcessMemory failed err={ctypes.GetLastError()}")
        return False
    llw = k32.GetProcAddress(k32.GetModuleHandleW('kernel32'), b'LoadLibraryW')
    if not llw:
        print("  GetProcAddress(LoadLibraryW) failed")
        return False
    tid = wt.DWORD(0)
    th = k32.CreateRemoteThread(h_process, None, 0, llw, remote, 0, ctypes.byref(tid))
    if not th:
        print(f"  CreateRemoteThread failed err={ctypes.GetLastError()}")
        return False
    k32.WaitForSingleObject(th, 15000)
    code = wt.DWORD(0)
    k32.GetExitCodeThread(th, ctypes.byref(code))
    k32.CloseHandle(th)
    if code.value:
        print(f"  LoadLibraryW ok (base={hex(code.value & 0xFFFFFFFF)})")
        return True
    print(f"  LoadLibraryW returned {code.value}, err={ctypes.GetLastError()}")
    return False


def get_image_base(pid: int) -> int:
    """Read PEB.ImageBaseAddress from the remote process."""
    h = k32.OpenProcess(PROCESS_ALL, False, pid)
    if not h:
        return 0
    try:
        # PEB is at offset 0x60 from TEB; TEB is at FS:[0x18] on x64
        teb_addr = ctypes.c_ulonglong(0)
        mbi = MEMORY_BASIC_INFORMATION()
        # search TEB region via NtQueryInformationProcess is complex —
        # instead, enumerate modules via 64-bit PE snapshot approach:
        # On x64 the PEB can be read directly via NtQueryInformationProcess
        # but kernel32 doesn't expose it. Use the fact that the main module
        # base is in the 0x140000000 range (BackpackBattles.exe typical base).
        # More reliable: use toolhelp32 via ctypes.
        import ctypes.util
        psapi = ctypes.windll.psapi
        psapi.GetModuleBaseNameW.restype = wt.DWORD
        psapi.GetModuleBaseNameW.argtypes = [wt.HANDLE, wt.HMODULE, wt.LPWSTR, wt.DWORD]
        mod_buf = ctypes.create_unicode_buffer(260)
        base = psapi.GetModuleBaseNameW(h, None, mod_buf, 260)
        if base:
            return base  # HMODULE is the base address
        return 0
    finally:
        k32.CloseHandle(h)


def read_candidates(path: str):
    """Parse hook log: {tag: [(src_int, key32_bytes), ...]}"""
    if not os.path.exists(path):
        return {}
    entries = {}
    for line in open(path, encoding='utf-8', errors='replace'):
        line = line.strip()
        if not line or line.startswith('===') or line.startswith('hooked'):
            continue
        parts = line.split()
        if len(parts) < 2:
            continue
        tag = parts[0]
        src_p = next((p for p in parts if p.startswith('src=')), None)
        key_p = next((p for p in parts if p.startswith('key=')), None)
        if not src_p or not key_p:
            continue
        src = int(src_p.split('=')[1], 16)
        key = bytes.fromhex(key_p.split('=')[1])
        if len(key) != 32:
            continue
        entries.setdefault(tag, []).append((src, key))
    return entries


def validate_gdec(key32: bytes, gde_path: str) -> bool:
    """AES-256-ECB decrypt gde sample header; check GDSC magic."""
    try:
        from Crypto.Cipher import AES
        ct = open(gde_path, 'rb').read()
        if ct[:4] != b'GDEC':
            return False
        plain = AES.new(key32, AES.MODE_ECB).decrypt(ct[32:])
        return plain[:4] == b'GDSC'
    except Exception:
        return False


def poll_and_report(pid: int, log_path: str, interval: float, timeout: float):
    """Poll candidate log every `interval`s; print new counts."""
    t0 = time.time()
    last = 0
    while time.time() - t0 < timeout:
        time.sleep(interval)
        n = sum(len(v) for v in read_candidates(log_path).values())
        if n != last:
            print(f"  t={time.time()-t0:5.1f}s  candidates={n}", flush=True)
            last = n
        if n >= 8:  # reasonable saturation
            print("  enough candidates, stopping poll early")
            break
    return last


def main():
    # Clear logs by writing empty content (avoids locked-file issue)
    for f in (LOG, STAT, OUT):
        if os.path.exists(f):
            try:
                open(f, 'w').close()
            except PermissionError:
                pass  # file still open by another process — skip

    # ── launch ──
    si = STARTUPINFOW(); si.cb = ctypes.sizeof(si)
    pi = PROCESS_INFORMATION()
    cmd = EXE + ' --headless'
    cmd_buf = ctypes.create_unicode_buffer(cmd)
    print(f"[1] launching: {cmd}")
    if not k32.CreateProcessW(None, cmd_buf, None, None, False,
                               0, None, os.path.dirname(EXE),
                               ctypes.byref(si), ctypes.byref(pi)):
        print(f"CreateProcessW failed err={ctypes.GetLastError()}")
        return 1
    pid = pi.dwProcessId
    print(f"  pid={pid} — injecting ASAP ...", flush=True)

    # ── rapid-fire inject loop (every 20ms for 5s) ──
    ok = False
    t0 = time.time()
    while time.time() - t0 < 5.0:
        try:
            ok = inject_dll(pi.hProcess, DLL)
            if ok:
                print(f"  injected after {time.time()-t0:.3f}s")
                break
        except OSError as e:
            print(f"  inject err={e}")
        time.sleep(0.02)
    k32.CloseHandle(pi.hProcess)
    k32.CloseHandle(pi.hThread)

    if not ok:
        print("INJECT_FAILED")
        return 1

    # ── poll for ~30s (covers the startup decryption storm) ──
    print("[2] polling for candidates (30s) ...", flush=True)
    last_n = poll_and_report(pid, LOG, 0.5, 30.0)
    last_n = sum(len(v) for v in read_candidates(LOG).values())

    # ── terminate the game ──
    h = k32.OpenProcess(PROCESS_ALL, False, pid)
    if h:
        k32.TerminateProcess(h, 0)
        k32.CloseHandle(h)

    # ── validate ──
    print(f"\n[3] validating {last_n} raw candidates ...", flush=True)
    from collections import OrderedDict
    seen = OrderedDict()
    validated = []
    for tag, items in read_candidates(LOG).items():
        for src, key in items:
            if key in seen:
                continue
            seen[key] = True
            ok = validate_gdec(key, GDE_SAMPLE)
            status = "✓ GDSC" if ok else "✗"
            print(f"  {status}  {tag}  src={hex(src)}  {key.hex()}")
            if ok:
                validated.append((tag, src, key))

    # ── save ──
    with open(OUT, 'w') as fh:
        for t, s, k in validated:
            fh.write(f"{t} {s:x} {k.hex()}\n")

    print(f"\n[4] done. validated={len(validated)}, raw_total={last_n}")
    if validated:
        print("VALIDATED KEYS:")
        for t, s, k in validated:
            print(f"  {k.hex()}")
        print(f"output → {OUT}")
    else:
        print("NO KEYS VALIDATED — see troubleshooting above")
    return 0


if __name__ == '__main__':
    sys.exit(main())