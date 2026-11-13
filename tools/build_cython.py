# -*- coding: utf-8 -*-
"""build_cython.py — F1 Cython 编译批（docs/性能优化执行路径.md S5-F1）

单模块编译：.py → (cython) → .c → (gcc/MinGW) → .pyd，产物落原目录——
importlib 扩展优先级（.pyd > .py）使内核自动走编译件；.py 保留为回落腿
（模块导入失败时 _bootstrap 记失败并回退——GD_CYTHON=0 环境门可强制回落：
  删除 .pyd 或设 GD_CYTHON=0？注：Python 无法按 env 选扩展，回落手段=删
  .pyd 或 _bootstrap 捕获 ImportError。故 .pyd 缺陷即删文件回滚，单模块粒度）。

后端：MinGW gcc（D:/mingw64，x86_64-w64-mingw32/msvcrt）直链 python314.dll。
Cython 产物只用 Python C API（无跨 CRT 堆/FILE 交互），msvcrt gcc + UCRT
Python 实践兼容。MSVC（winget BuildTools）为后续正式化路径，当前不可用。

用法:
    python tools/build_cython.py gd_core_py/gd_core/CoreItem.py
    python tools/build_cython.py --all          # F1 热 8 模块
"""
import argparse
import io
import os
import time
import multiprocessing as _mp
from concurrent.futures import ProcessPoolExecutor
import subprocess
import sys
import sysconfig

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GCC = r"D:\mingw64\bin\gcc.exe"
PY_DIR = os.path.dirname(sys.executable)
MSVC_VCVARS = (r"C:\Program Files (x86)\Microsoft Visual Studio\2022"
               r"\BuildTools\VC\Auxiliary\Build\vcvars64.bat")
BACKEND = "mingw"

#: MSVC 中间产物（.obj / .lib / .exp / .pdb）落点。
#  ★ 2026-11-12：cl **只给 /OUT:**（最终 .pyd）时，中间产物按 cwd 落盘——而
#    本脚本两处 cl 都是 cwd=ROOT，等于把 525 模块 × 3 类文件全砸进仓库根目录
#    （实测 1575 个 / 143 MB，每次打包重来一遍）。逐模块显式 /Fo /Fd /
#    /link /IMPLIB 指到 build/ 下（该目录已 .gitignore，双保险）。
OBJ_DIR = os.path.join(ROOT, "build", "cython_objs")


# ── 并行编译（2026-11-13）────────────────────────────────────────────
# 动机：单模块 cython 实测 4–8.5 s（大模块更久），串行 668 模块 ≈ 45–90 min，
# 是修复回路的主要瓶颈。实测 4 进程 2.87x、8 进程 2.59x（4 物理核已饱和）。
# cl 步本身很快（~0.5 s/模块），但原先挤在一个 bat 里串行 —— 同样分片并行。
#
# 并行化的三条约束（都不改语义）：
#   ① 只并行「编译」这个纯函数步骤，mtime 筛选 / MISS 统计 / 错误汇报仍由主进程做；
#   ② 每个子进程只写自己的 .c 或 .pyd，无共享写；
#   ③ 失败要能定位到模块（子进程返回 (rel, rc, 错误尾部)）。

# ★ 编译指令包（2026-11-13）：GD_CY_DIRECTIVES="boundscheck=False,wraparound=False"。
#   默认空前缀，产物与历史逐字节等价（指令包是实验开关，不进默认路径）。
#   安全性前提已全树验证：gd_core(159) + gd_core_items(509) 共 668 模块里
#   **没有一处 `except IndexError`、没有一处裸 `except:`** ⇒ 关闭越界检查不会
#   把「靠异常做控制流」的路径改静默。nonecheck 关掉后 None 属性访问从
#   AttributeError 变 C 层访问（本树无此路径，但该项仍单独可关）。
_CY_DIR_ENV = os.environ.get("GD_CY_DIRECTIVES", "").strip()
_CY_FLAGS = []
if _CY_DIR_ENV:
    for _d in _CY_DIR_ENV.split(","):
        _d = _d.strip()
        if _d:
            _CY_FLAGS += ["-X", _d]



def _cython_batch(rels):
    """子进程：**一批**模块 .py → .c（单次 cython CLI 多文件）。

    ★ 2026-11-13 实测：每模块单起一个 cython 进程要付 Cython 自身 import
      开销（~2-3 s/次，占单模块 4-8.5 s 的一大半）。改成一次 CLI 传整批后：
        24 模块 单批 15.0s（5.67x）/ 4 分片 × 4 进程 8.2s（**10.44x**）
      输出仍按源目录落各自 .c（cython 多文件模式的默认行为）。

    返回 (rels, rc, err_tail)。
    """
    r = subprocess.run([sys.executable, "-m", "cython", "-3",
                        "-X", "binding=True"] + _CY_FLAGS + list(rels),
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        return (list(rels), r.returncode,
                (r.stdout or "")[-1200:] + (r.stderr or "")[-1200:])
    return (list(rels), 0, "")


def _cl_shard(payload):
    """子进程：跑一个分片 bat（内含 vcvars + 若干 cl）。返回 (shard_id, rc, tail)。"""
    sid, bat_path = payload
    r = subprocess.run(["cmd", "/c", bat_path], cwd=ROOT,
                       capture_output=True, text=True,
                       encoding="gbk", errors="replace")
    return (sid, r.returncode, (r.stdout or "")[-800:] + (r.stderr or "")[-400:])


def artifact_paths(rel_base: str) -> dict:
    """按模块相对路径（不含扩展名）给出 MSVC 中间产物的绝对路径。

    stem 扁平化（"gd_core_py/gd_core/CoreItem" → "gd_core_py_gd_core_CoreItem"），
    平铺在 build/cython_objs/ 下：① 同名模块不同目录也不会互相覆盖；
    ② 不建深层目录树，便于整体删除回滚。
    """
    stem = rel_base.replace("/", "_").replace("\\", "_").replace(":", "_")
    os.makedirs(OBJ_DIR, exist_ok=True)
    return {
        "obj": os.path.join(OBJ_DIR, stem + ".obj"),
        "pdb": os.path.join(OBJ_DIR, stem + ".pdb"),
        "lib": os.path.join(OBJ_DIR, stem + ".lib"),
    }

# F1 热 8 模块（规划顺序：CoreItem → CoreCombat → CoreCharacter → CoreTimer →
# CoreRng → CoreBuff → CoreGrid → CoreEventBus）；逐一单独上闸
HOT8 = [
    "gd_core_py/gd_core/CoreItem.py",
    "gd_core_py/gd_core/CoreCombat.py",
    "gd_core_py/gd_core/CoreCharacter.py",
    "gd_core_py/gd_core/CoreTimer.py",
    "gd_core_py/gd_core/CoreRng.py",
    "gd_core_py/gd_core/CoreBuff.py",
    "gd_core_py/gd_core/CoreGrid.py",
    "gd_core_py/gd_core/CoreEventBus.py",
    # S5-F1 续批：_rt shim 床（f32/_iter/_div/Vector2/EnumDict/PCG32 全 C 化，
    # p50 252→216ms）——语义床本体，任何闸红先删 _rt.pyd 回滚
    "gd_core_py/_rt.py",
]


def build_one(py_path: str) -> str:
    """编译单模块，返回 .pyd 路径。任一步失败抛异常（单模块回落=删 .pyd）。"""
    py_path = os.path.relpath(os.path.join(ROOT, py_path), ROOT)
    if not os.path.exists(os.path.join(ROOT, py_path)):
        raise FileNotFoundError(py_path)
    base = os.path.splitext(py_path)[0]          # gd_core_py/gd_core/CoreItem
    c_path = base + ".c"
    pyd_path = base + ".pyd"

    # ① cython：.py → .c（-3 = Python 3 语言语义；module-name 由文件名推断）
    # ★ 严禁 -2（Py2 语义会把 `/` 变整除——REG9 run1514 ev@71 抓获的正是它）
    # ★ M1-4（2026-11-10）→ **2026-11-13 撤回改 binding=True**：binding=False
    #   与「cpdef 方法 + plain 子类 zero-arg super()」不兼容——§11.4 闭环实测
    #   62 场崩 （Greatsword_2.getStaminaCost
    #   → super().getStaminaCost() 栈实证）。binding=True 恢复 CyFunction
    #   __class__ cell（零参 super 兼容），代价是 CyFunction 包装回归
    #   （260 处/单类模块）——正确性优先。
    #   embedsignature 在 Cython3 默认即 False（无产物差异）；
    #   freelist 判不可行：模块级指令被语法接受但 C 产物显式 "nofreelists"
    #   ABI 后缀（3.3.1 不再生成 freelist 池），装饰器形态被拒（class scope）。
    r = subprocess.run([sys.executable, "-m", "cython", "-3",
                        "-X", "binding=True"] + _CY_FLAGS + [
                        py_path, "-o", c_path],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"cython 失败 {py_path}:\n{r.stdout[-800:]}\n{r.stderr[-800:]}")

    # ② 编译 .c → .pyd：后端二选一（--msvc 切换）
    inc = sysconfig.get_paths()["include"]
    if BACKEND == "msvc":
        # MSVC：经 vcvars64 环境后 cl /O2 /LD /MD（与 Python 同族运行时/官方 ABI）
        # ★ python314.lib 在 <PY_DIR>\libs（首版 /LIBPATH 少 libs → LNK1181）
        libs_dir = os.path.join(PY_DIR, "libs")
        bat = os.path.join(ROOT, "tools", "_msvc_build_one.cmd")
        # ★ M1-5（2026-11-10）：/GL+/LTCG 全程序优化（实验）——GD_LTO=1 开启，
        #   默认关。跨翻译单元内联对单 .pyd 边际小（模块内符号为主），且
        #   link 期变慢（每模块 +2-5s）；闸红或无收益即弃。
        # ★ M4-4（2026-11-11）：/Os 体积优先——GD_OS=1 开启（实验门控）。
        lto = "/GL" if os.environ.get("GD_LTO") == "1" else ""
        ltcg = "/LTCG" if os.environ.get("GD_LTO") == "1" else ""
        os_flag = "/Os" if os.environ.get("GD_OS") == "1" else ""
        # ★ 中间产物显式重定向（否则 .obj/.lib/.exp/.pdb 全落 cwd=ROOT）
        ap = artifact_paths(base)
        cmd_line = (
            f'call "{MSVC_VCVARS}" >nul 2>&1 && cl /O2 {os_flag} /LD /MD /nologo '
            f'{lto} /I "{inc}" {c_path} '
            f'/Fo"{ap["obj"]}" /Fd"{ap["pdb"]}" '
            f'/link {ltcg} /IMPLIB:"{ap["lib"]}" '
            f'/LIBPATH:"{libs_dir}" python314.lib '
            f'/OUT:{pyd_path}')
        # ★ 同清单模式：cmd 代码页 65001 ⇒ bat 用 utf-8 写 + 首行 chcp（否则中文路径乱码）
        with io.open(bat, "w", encoding="utf-8", newline="") as fh:
            fh.write("@echo off\r\nchcp 65001 >nul\r\n" + cmd_line + "\r\n")
        r = subprocess.run(["cmd", "/c", bat], cwd=ROOT,
                           capture_output=True, text=True,
                           encoding="gbk", errors="replace")
        if r.returncode != 0 or not os.path.exists(os.path.join(ROOT, pyd_path)):
            raise RuntimeError(f"msvc 失败 {py_path}:\n{r.stdout[-1500:]}\n{r.stderr[-500:]}")
    else:
        # MinGW：直链 python314.dll；-static-libgcc 免带 gcc 运行时 DLL
        r = subprocess.run(
            [GCC, "-O2", "-shared", "-fno-strict-aliasing", "-static-libgcc",
             "-I", inc, "-I", os.path.join(PY_DIR, "Include"),
             "-L", PY_DIR, "-lpython314",
             "-o", pyd_path, c_path],
            cwd=ROOT, capture_output=True, text=True)
        if r.returncode != 0:
            raise RuntimeError(f"gcc 失败 {py_path}:\n{r.stderr[-1500:]}")
    if not os.path.exists(os.path.join(ROOT, pyd_path)):
        raise RuntimeError(f"pyd 未产出: {pyd_path}")
    return pyd_path


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("targets", nargs="*", help="相对 ROOT 的 .py 路径")
    ap.add_argument("--all", action="store_true", help="F1 热 8 模块")
    ap.add_argument("--list", default=None, help="目标清单文件（每行一个相对路径）")
    ap.add_argument("--msvc", action="store_true",
                    help="用 MSVC 后端（需 Build Tools；默认 MinGW）")
    ap.add_argument("--clean", action="store_true",
                    help="删除目标 .pyd/.c（回滚手段）")
    ap.add_argument("--jobs", type=int, default=0,
                    help="并行进程数（0=物理核数；1=旧串行行为）")
    a = ap.parse_args()
    global BACKEND
    if a.msvc:
        BACKEND = "msvc"
    targets = HOT8 if a.all else a.targets
    if a.list:
        with open(a.list, encoding="utf-8") as fh:
            targets = [ln.strip() for ln in fh if ln.strip()]
    if not targets:
        ap.error("需要 targets/--all/--list")

    # ── MSVC 清单模式（S5-F1 续批）：单 bat 内 vcvars 一次 + 逐模块 cl——
    #    首版每模块重调 vcvars（5-8s 纯开销 × 643）不可行。cl 失败的模块无
    #    .pyd 产物 → 回落 .py（幂等重跑只补缺）。──
    # ★ M0 教训修复（2026-11-11）：幂等跳过原为 `if exist .pyd` —— pyd 存在
    #   即跳过、**从不看源 mtime**，导致源变更后的「重编」全部空转（M1-1/
    #   M2/M1-2/M1-4 的 pyd 均未真正进编译态，闸门绿是因为旧 pyd 与新源
    #   语义等价 + 纯 py 臂单独验证过——两件事凑巧掩盖了同一仪器 bug）。
    #   现改为 mtime 判定：pyd 存在且晚于 .py 与伴随 .pxd 才跳过。
    if BACKEND == "msvc" and a.list:
        libs_dir = os.path.join(PY_DIR, "libs")
        inc = sysconfig.get_paths()["include"]
        stale = []
        for t in targets:
            base = os.path.splitext(os.path.join(ROOT, t))[0]
            pyd = base + ".pyd"
            if not os.path.exists(pyd):
                stale.append(t)
                continue
            pyd_m = os.path.getmtime(pyd)
            for dep in (base + ".py", base + ".pxd"):
                if os.path.exists(dep) and os.path.getmtime(dep) > pyd_m:
                    stale.append(t)
                    break
        targets = stale
        if not targets:
            print("[msvc-list] 全部目标新鲜（pyd 晚于 .py/.pxd），零重编")
            return 0
        # ★ cython 步（源 → .c）：清单模式原直接编既有 .c——源变更后 .c 陈旧
        #   是与「pyd 存在即跳过」叠加的第二重空转雷。逐模块跑 cython
        #   （~1-2s/个，清单规模可承受），cl 仍走单 bat 批量。
        # 并行 cython（--jobs；默认物理核数，实测 4 进程 2.87x）
        jobs = a.jobs if a.jobs > 0 else max(1, (_mp.cpu_count() or 4) // 2)
        rels = [os.path.relpath(os.path.join(ROOT, t), ROOT) for t in targets]
        # 分批 + 并行：每批一次 cython CLI（省 import 开销）× N 进程
        # 实测 24 模块：逐模块 85.3s → 单批 15.0s（5.67x）→ 4×4 8.2s（10.44x）
        BATCH = 12 if len(rels) > 48 else max(1, len(rels))
        shards = [rels[i::jobs] for i in range(min(jobs, len(rels)))]
        batches = []
        for sh in shards:
            for i in range(0, len(sh), BATCH):
                batches.append(sh[i:i + BATCH])
        t0 = time.perf_counter()
        fails = []
        if jobs <= 1 or len(batches) <= 1:
            for b in batches:
                _, rc, err = _cython_batch(b)
                if rc != 0:
                    fails.append((b, err))
        else:
            with ProcessPoolExecutor(max_workers=jobs) as ex:
                for got, rc, err in ex.map(_cython_batch, batches, chunksize=1):
                    if rc != 0:
                        fails.append((got, err))
        if fails:
            raise RuntimeError(
                "cython 失败 %d 批（首个含 %s）：\n%s"
                % (len(fails), fails[0][0][:2], fails[0][1]))
        print(f"[msvc-list] cython {len(rels)} 模块 / {len(batches)} 批 / "
              f"{min(jobs, len(rels))} 进程 耗时 {time.perf_counter() - t0:.1f}s")
        # cl 分片并行：每个分片一个 bat（各自 vcvars 一次），并行跑。
        # cl 单模块 ~0.5s，但 668 个串行仍有分钟级；分片后与 cython 阶段同量级。
        def _bat_for(part, idx):
            # ★ 编码坑（2026-11-13 实测）：本机 cmd 代码页是 65001（UTF-8），
            #   而 bat 曾按 gbk 写 ⇒ cl 收到乱码中文路径（"锟斤拷"），
            #   /Fo 目标打不开 → 全部 MISS。修法：bat 用 utf-8 写 + 首行 chcp 65001。
            lines = ["@echo off",
                     "chcp 65001 >nul",
                     f'call "{MSVC_VCVARS}" >nul 2>&1']
            for t in part:
                base = os.path.splitext(t)[0]
                # ★ 目标已在 Python 侧按 mtime 筛过（stale 才进 bat）——bat 内
                #   不再放 `if exist .pyd goto skip`（就是它把重编吞掉的）
                ap = artifact_paths(base)
                lines.append(
                    f'cl /O2 /LD /MD /nologo /I "{inc}" {base}.c '
                    f'/Fo"{ap["obj"]}" /Fd"{ap["pdb"]}" '
                    f'/link /IMPLIB:"{ap["lib"]}" '
                    f'/LIBPATH:"{libs_dir}" python314.lib /OUT:{base}.pyd')
            path = os.path.join(ROOT, "tools", f"_msvc_list_{idx}.cmd")
            with io.open(path, "w", encoding="utf-8", newline="") as fh:
                fh.write("\r\n".join(lines) + "\r\n")
            return path

        # ── 自适应分片（2026-11-13 扫参）──────────────────────────────
        # 实测 60 模块 cl 段：jobs=2 → 161.3s / 4 → 79.2s / 6 → 86.8s / 8 → 81.0s
        #   ⇒ cl 的拐点在 4，再往上不再变快（每分片一次 vcvars ≈5s 固定开销，
        #     且本机 4 物理核）。而 cython 段是 26.5 / 16.6 / 12.4 / 10.0s
        #   ⇒ cython 偏好更多进程（纯 Python 侧，不吃满核也会让出时间片）。
        #
        # 因此分片数不能死等 jobs：**小任务分太碎会让 vcvars 开销占主导**
        # （10 模块切 8 片时，固定开销 > 编译本身）。规则：
        #     n_shards = clamp(ceil(N / MIN_PER_SHARD), 1, min(jobs, N))
        # MIN_PER_SHARD=12：60 模块 → 5 片，30 模块 → 3 片，10 模块 → 1 片。
        MIN_PER_SHARD = 12
        want = -(-len(targets) // MIN_PER_SHARD)          # ceil
        n_shards = 1 if jobs <= 1 else max(1, min(jobs, len(targets), want))
        shards = [targets[i::n_shards] for i in range(n_shards)]
        bats = [(_bat_for(part, i), i) for i, part in enumerate(shards)]
        payloads = [(i, p) for p, i in bats]
        t0 = time.perf_counter()
        if n_shards <= 1:
            rc, tail = _cl_shard(payloads[0])[1:]
            print(f"[msvc-list] bat 执行完成 rc={rc}")
        else:
            rcs = []
            with ProcessPoolExecutor(max_workers=n_shards) as ex:
                for sid, rc, tail in ex.map(_cl_shard, payloads):
                    rcs.append((sid, rc))
                    if rc != 0:
                        print(f"  shard{sid} rc={rc} 尾部：{tail[-300:]}")
            print(f"[msvc-list] cl 并行 {n_shards} 分片 / {len(targets)} 模块 "
                  f"耗时 {time.perf_counter() - t0:.1f}s，"
                  f"非零 rc 分片 {sum(1 for _, rc in rcs if rc)}")
        miss = [t for t in targets
                if not os.path.exists(os.path.join(ROOT, t[:-3] + ".pyd"))]
        for t in miss:
            print(f"  MISS {t}（无 .pyd → 回落 .py）")
        print(f"[msvc-list] 缺失 {len(miss)} / 重编目标 {len(targets)}")
        return 0

    rc = 0
    for t in targets:
        base = os.path.splitext(os.path.join(ROOT, t))[0]
        if a.clean:
            for ext in (".pyd", ".c"):
                p = base + ext
                if os.path.exists(p):
                    os.remove(p)
                    print(f"removed {p}")
            continue
        try:
            pyd = build_one(t)
            print(f"OK  {t} → {pyd}  ({os.path.getsize(os.path.join(ROOT, pyd))//1024} KB)")
        except Exception as e:  # noqa: BLE001
            print(f"FAIL {t}: {e}")
            rc = 1
    return rc


if __name__ == "__main__":
    raise SystemExit(main())
