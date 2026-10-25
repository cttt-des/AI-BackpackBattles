# -*- coding: utf-8 -*-
"""内核 .gd 二分器：在 恢复版/基线版 之间切换文件子集，单场计时定位阻塞罪件。
用法：python _bisect_kernel.py <模式>
模式 = recovered（全恢复）| base（全基线）| core_base_items_rec | core_rec_items_base
       或文件清单文件路径（每行一个相对路径，这些用恢复版，其余基线）
"""
import subprocess
import os
import sys
import shutil
import time
import glob

REPO = os.getcwd()
GD = os.path.join(REPO, "gd_core")
GI = os.path.join(REPO, "gd_core_items")
TGD = os.path.join(REPO, "gd_core_test", "gd_core")
TGI = os.path.join(REPO, "gd_core_test", "gd_core_items")
OUT = os.path.join(REPO, "output", "_recovery", "t_bisect")


def gd_files():
    rels = [os.path.relpath(p, GD).replace("\\", "/")
            for p in glob.glob(os.path.join(GD, "**", "*.gd"), recursive=True)]
    rels += [os.path.relpath(p, GI).replace("\\", "/")
             for p in glob.glob(os.path.join(GI, "**", "*.gd"), recursive=True)]
    return rels


def backup_all():
    bdir = os.path.join(REPO, "output", "_recovery", "_gd_backup")
    shutil.rmtree(bdir, ignore_errors=True)
    os.makedirs(bdir + "/gd_core", exist_ok=True)
    os.makedirs(bdir + "/gd_core_items", exist_ok=True)
    for f in gd_files():
        src = os.path.join(GD, f) if os.path.exists(os.path.join(GD, f)) else os.path.join(GI, f)
        dst = os.path.join(bdir, "gd_core", f) if src.startswith(GD) else os.path.join(bdir, "gd_core_items", f)
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        shutil.copy2(src, dst)
    return bdir


def restore(bdir, rel, recovered: bool):
    """把 rel 恢复成 恢复版(备份) 或 基线版(git)。"""
    bfile = os.path.join(bdir, "gd_core", rel)
    if not os.path.exists(bfile):
        bfile = os.path.join(bdir, "gd_core_items", rel)
    base = subprocess.run(["git", "show", "HEAD:" + ("gd_core/" + rel if subprocess.run(
        ["git", "cat-file", "-e", "HEAD:gd_core/" + rel], capture_output=True).returncode == 0
        else "gd_core_items/" + rel)], capture_output=True, cwd=REPO)
    content = open(bfile, "rb").read() if recovered else base.stdout
    dst = os.path.join(GD, rel)
    if not os.path.exists(dst):
        dst = os.path.join(GI, rel)
    open(dst, "wb").write(content)
    # 同步 test 副本
    td = os.path.join(TGD, rel)
    if not os.path.exists(td):
        td = os.path.join(TGI, rel)
    if os.path.dirname(td):
        os.makedirs(os.path.dirname(td), exist_ok=True)
        open(td, "wb").write(content)


def run_case(timeout=180):
    shutil.rmtree(OUT, ignore_errors=True)
    env = dict(os.environ)
    env["APPDATA"] = r"D:\文件资料\学习\自动背包AI\output\_recovery\appdata"
    env["ORACLE_ALIGN_OUT"] = OUT
    env["ORACLE_ALIGN_CASES"] = "run569_r11"
    env["ORACLE_ALIGN_CHUNK"] = "0"
    env["ORACLE_ALIGN_SELFCHECK"] = "0"
    env["ORACLE_ALIGN_NO_PERM_HARVEST"] = "1"
    env["ORACLE_ALIGN_NO_WARM_LATCH"] = "1"
    env["ORACLE_ALIGN_NO_R5_DUAL_EXEC"] = "1"
    t0 = time.time()
    try:
        with open(os.path.join(REPO, "output/_recovery/bis_out.txt"), "wb") as fo:
            subprocess.run([os.path.join(REPO, "output/godot36/Godot_v3.6-stable_win64.exe"),
                            "--headless", "--audio-driver", "Dummy", "--path", "gd_core_test",
                            "--script", "OracleAlignBattle.gd"],
                           stdout=fo, stderr=subprocess.DEVNULL, env=env, cwd=REPO,
                           timeout=timeout)
        wall = time.time() - t0
    except subprocess.TimeoutExpired:
        wall = -1
    has = os.path.exists(os.path.join(OUT, "run569_r11", "events.json"))
    return wall, has


if __name__ == "__main__":
    mode = sys.argv[1]
    files = gd_files()
    bdir = backup_all()
    core_recs = [f for f in files if subprocess.run(
        ["git", "cat-file", "-e", "HEAD:gd_core/" + f], capture_output=True).returncode == 0]
    item_recs = [f for f in files if f not in core_recs]
    if mode == "recovered":
        rec_set = set(files)
    elif mode == "base":
        rec_set = set()
    elif mode == "core_base_items_rec":
        rec_set = set(item_recs)
    elif mode == "core_rec_items_base":
        rec_set = set(core_recs)
    else:
        rec_set = set(open(mode, encoding="utf-8").read().split())
    for f in files:
        restore(bdir, f, f in rec_set)
    wall, has = run_case()
    print("MODE=%s 恢复件=%d wall=%s events=%s" % (mode, len(rec_set),
                                                   ("超时" if wall < 0 else round(wall, 1)), has))
