"""编译 looptest.pyx 并跑 untyped vs typed 循环对比。"""
import os
import subprocess
import sys
import sysconfig
import time

HERE = os.path.dirname(os.path.abspath(__file__))
PYX = os.path.join(HERE, "looptest.pyx")
VCVARS = (r"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools"
          r"\VC\Auxiliary\Build\vcvars64.bat")


def build():
    r = subprocess.run([sys.executable, "-m", "cython", "-3", "-X", "binding=True",
                        PYX, "-o", os.path.join(HERE, "looptest.c")],
                       capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stdout[-1500:], r.stderr[-1500:])
        return 1
    inc = sysconfig.get_paths()["include"]
    pyd = os.path.join(HERE, "looptest.pyd")
    c = os.path.join(HERE, "looptest.c")
    import sysconfig as _sc
    libs = os.path.join(os.path.dirname(_sc.get_paths()["include"]), "libs")
    cmd = ('call "%s" >nul 2>&1 && cl /O2 /LD /MD /nologo /I "%s" "%s" '
           '/link /LIBPATH:"%s" python314.lib /OUT:"%s"'
           % (VCVARS, inc, c, libs, pyd))
    r = subprocess.run(cmd, shell=True, cwd=HERE, capture_output=True,
                       text=True, encoding="gbk", errors="replace")
    if not os.path.exists(pyd):
        print(r.stdout[-2000:], r.stderr[-800:])
        return 1
    print("built", pyd)
    return 0


def bench():
    sys.path.insert(0, HERE)
    import looptest as L
    class Ch:
        pass
    ch = Ch()
    ch.stunnedDuration = 0.0
    items = [L.Base(1.5, True, 1.0, ch) for _ in range(103)]
    n_items, reps = len(items), 100000   # 10.3M item-ticks：typed 臂太快，小了测不出
    DELTA = 1.0 / 60.0

    def timeit(fn, rounds=5):
        best = 1e9
        for _ in range(rounds):
            t0 = time.process_time()
            fn()
            best = min(best, time.process_time() - t0)
        return best

    # 预热
    L.run_untyped(items, DELTA, 50)
    L.run_typed(items, DELTA, 50)
    tu = timeit(lambda: L.run_untyped(items, DELTA, reps))
    tt = timeit(lambda: L.run_typed(items, DELTA, reps))
    per_u = tu / (reps * n_items) * 1e6
    per_t = tt / (reps * n_items) * 1e6
    print()
    print("items=%d reps=%d  (%.2f M item-ticks)" % (n_items, reps, reps * n_items / 1e6))
    print("untyped: %.3f s   %.3f us/item-tick" % (tu, per_u))
    print("typed  : %.3f s   %.3f us/item-tick" % (tt, per_t))
    print("speedup: %.2fx" % (per_u / per_t))
    print()
    print("现状单场 physicsTick 约 167 ms / 93k item-tick = 1.8 us")
    print("若 this ratio holds -> physicsTick ~ %.0f ms" % (167 / (per_u / per_t)))
    return 0


if __name__ == "__main__":
    mode = sys.argv[1] if len(sys.argv) > 1 else "all"
    if mode in ("all", "build"):
        rc = build()
        if rc:
            raise SystemExit(rc)
    if mode in ("all", "bench"):
        raise SystemExit(bench())
