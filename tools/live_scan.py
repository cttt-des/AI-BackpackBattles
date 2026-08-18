"""Launch Backpack Battles, let it set the script key, suspend it, then
brute-force the script key from its frozen memory using scan_key.exe.

Strategy:
  - Spawn the game (--headless so no display needed).
  - Wait a few seconds for engine init (project settings -> key set).
  - NtSuspendProcess so it cannot crash/exit during the scan.
  - Run scan_key.exe <pid> (validated AES-256-ECB brute forcer).
  - Kill the process afterwards.
"""
import subprocess, sys, time, os, ctypes
from ctypes import wintypes

kernel32 = ctypes.windll.kernel32
ntdll = ctypes.windll.ntdll

EXE = r"D:/steam/steamapps/common/Backpack Battles/BackpackBattles.exe"
TOOLS = os.path.dirname(os.path.abspath(__file__))
SCANNER = os.path.join(TOOLS, "scan_key.exe")
GDE = os.path.join(TOOLS, "Combat.gde")
OUT = os.path.join(TOOLS, "candidates_live.txt")
ATTEMPTS = 5
INIT_WAIT = 6.0  # seconds to let the engine read project settings / set key

def open_err(pid, access):
    h = kernel32.OpenProcess(access, False, pid)
    if h:
        kernel32.CloseHandle(h)
        return 0, "OK"
    return ctypes.GetLastError(), "ERR"

def suspend(pid):
    h = kernel32.OpenProcess(0x0800, False, pid)  # PROCESS_SUSPEND_RESUME
    if not h:
        return False, ctypes.GetLastError()
    # NtSuspendProcess(pid) via handle; ntdll signature: (HANDLE)->NTSTATUS
    status = ntdll.NtSuspendProcess(h)
    kernel32.CloseHandle(h)
    return (status == 0), status

def kill(pid):
    h = kernel32.OpenProcess(0x0001, False, pid)  # TERMINATE
    if h:
        kernel32.TerminateProcess(h, 0)
        kernel32.CloseHandle(h)

def main():
    for attempt in range(1, ATTEMPTS+1):
        print(f"[attempt {attempt}] launching game...")
        proc = subprocess.Popen([EXE, "--headless"],
                                stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        pid = proc.pid
        print(f"  pid={pid}")
        # wait until alive for INIT_WAIT seconds
        t0 = time.time()
        alive_for = 0.0
        while time.time() - t0 < INIT_WAIT + 8:
            if proc.poll() is not None:
                print(f"  game exited early (code {proc.returncode})")
                break
            time.sleep(0.3)
            alive_for = time.time() - t0
        else:
            pass
        if proc.poll() is not None:
            continue  # relaunch
        # probe access
        err, msg = open_err(pid, 0x410)  # VM_READ(0x10) | QUERY_INFO(0x400)
        print(f"  OpenProcess(VM_READ) err={err} ({msg})")
        if err != 0:
            print("  cannot read process memory; aborting this attempt")
            kill(pid)
            continue
        # suspend
        ok, st = suspend(pid)
        print(f"  suspend: ok={ok} status={st}")
        if not ok:
            print("  suspend failed; killing and retrying")
            kill(pid)
            continue
        # run scanner
        print(f"  running scanner on pid={pid} ...")
        r = subprocess.run([SCANNER, str(pid), GDE, OUT],
                           capture_output=True, text=True)
        print("  SCANNER STDOUT:\n" + r.stdout)
        if r.stderr.strip():
            print("  SCANNER STDERR:\n" + r.stderr[-1000:])
        print("  === candidates ===")
        try:
            print(open(OUT).read())
        except Exception as e:
            print("  (no candidate file)", e)
        kill(pid)
        return 0
    print("ALL ATTEMPTS FAILED")
    return 1

if __name__ == "__main__":
    raise SystemExit(main())
