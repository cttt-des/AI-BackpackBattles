"""Launch headless game, suspend it after init, hold until sentinel file appears, then kill.
Prints 'PID=<n>' once suspended. Never touches the user's own game session."""
import subprocess, sys, time, os, ctypes

k32 = ctypes.windll.kernel32
ntdll = ctypes.windll.ntdll
EXE = r"D:\steam\steamapps\common\Backpack Battles\BackpackBattles.exe"
SENTINEL = os.path.join(r'D:\文件资料\学习\自动背包AI\tools', '_scan_done.flag')
WAIT = float(sys.argv[1]) if len(sys.argv) > 1 else 15.0

if os.path.exists(SENTINEL):
    os.remove(SENTINEL)

proc = subprocess.Popen([EXE, "--headless"], stdout=subprocess.DEVNULL,
                        stderr=subprocess.DEVNULL, cwd=os.path.dirname(EXE))
t0 = time.time()
while time.time() - t0 < WAIT:
    if proc.poll() is not None:
        print(f"exited early code={proc.returncode}"); sys.exit(1)
    time.sleep(0.3)

h = k32.OpenProcess(0x0800, False, proc.pid)  # SUSPEND_RESUME
if not h or ntdll.NtSuspendProcess(h) != 0:
    print("suspend failed"); sys.exit(1)
print(f"PID={proc.pid}", flush=True)

t0 = time.time()
while time.time() - t0 < 900:  # hold up to 15 min
    if os.path.exists(SENTINEL):
        break
    time.sleep(1)

ntdll.NtResumeProcess(h)
k32.TerminateProcess(h, 0)
k32.CloseHandle(h)
proc.wait()
os.remove(SENTINEL) if os.path.exists(SENTINEL) else None
print("temp process cleaned up")
