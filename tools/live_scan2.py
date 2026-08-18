"""Robust runtime key scanner for Backpack Battles.

Launch the game headless, wait for the script key to be set at engine init,
SUSPEND the process (so it cannot crash/exit during the scan), then run the
validated scan_key.exe brute-forcer over the frozen memory. Kill at the end.

If no candidate is found, the key may only be materialized when a script is
actually loaded; we retry with a longer init wait.
"""
import subprocess, sys, time, os, ctypes
from ctypes import wintypes

kernel32 = ctypes.windll.kernel32
ntdll = ctypes.windll.ntdll

EXE = r"D:/steam/steamapps/common/Backpack Battles/BackpackBattles.exe"
TOOLS = os.path.dirname(os.path.abspath(__file__))
SCANNER = os.path.join(TOOLS, "scan_key.exe")
GDE = os.path.join(TOOLS, "Combat.gde")
OUT = os.path.join(TOOLS, "candidates_live3.txt")

INIT_WAIT = 15.0  # seconds for engine init to set the script key

def suspend(pid):
    h = kernel32.OpenProcess(0x0800, False, pid)  # PROCESS_SUSPEND_RESUME
    if not h:
        return False, ctypes.GetLastError()
    status = ntdll.NtSuspendProcess(h)
    kernel32.CloseHandle(h)
    return (status == 0), status

def resume(pid):
    h = kernel32.OpenProcess(0x0800, False, pid)
    if not h:
        return
    ntdll.NtResumeProcess(h)
    kernel32.CloseHandle(h)

def kill(pid):
    h = kernel32.OpenProcess(0x0001, False, pid)  # TERMINATE
    if h:
        kernel32.TerminateProcess(h, 0)
        kernel32.CloseHandle(h)

def main():
    init_wait = INIT_WAIT
    for attempt in range(1, 4):
        print(f"[attempt {attempt}] launching game (init wait {init_wait}s)...")
        proc = subprocess.Popen([EXE, "--headless"],
                                stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        pid = proc.pid
        print(f"  pid={pid}")
        # wait until alive for INIT_WAIT seconds
        t0 = time.time()
        while time.time() - t0 < init_wait:
            if proc.poll() is not None:
                print(f"  game exited early (code {proc.returncode}) during init")
                break
            time.sleep(0.3)
        else:
            pass  # survived init wait
        if proc.poll() is not None:
            continue
        # verify read access
        h = kernel32.OpenProcess(0x410, False, pid)  # VM_READ|QUERY_INFO
        if not h:
            print(f"  OpenProcess failed err={ctypes.GetLastError()}; killing")
            kill(pid); continue
        kernel32.CloseHandle(h)
        # suspend so it cannot crash during scan
        ok, st = suspend(pid)
        print(f"  suspend: ok={ok} status={st}")
        if not ok:
            print(f"  suspend failed; killing")
            kill(pid); continue
        # run scanner on the frozen process
        print(f"  running scanner on pid={pid} ...")
        try:
            r = subprocess.run([SCANNER, str(pid), GDE, OUT],
                               capture_output=True, text=True, timeout=300)
            print("  SCANNER STDOUT:\n" + r.stdout)
            if r.stderr.strip():
                print("  SCANNER STDERR:\n" + r.stderr[-1500:])
        except subprocess.TimeoutExpired:
            print("  scanner timed out")
        print("  === candidates ===")
        try:
            print(open(OUT).read())
        except Exception as e:
            print("  (no candidate file)", e)
        kill(pid)
        # if we found something, stop; else retry with longer wait
        try:
            found = len(open(OUT).read().splitlines())
        except Exception:
            found = 0
        if found:
            print("FOUND CANDIDATES")
            return 0
        print("no candidates this attempt; retrying with longer init wait")
        init_wait += 6.0
    print("ALL ATTEMPTS FAILED")
    return 1

if __name__ == "__main__":
    raise SystemExit(main())
