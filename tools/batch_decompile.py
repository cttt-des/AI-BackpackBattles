"""
batch_decompile.py -- decompile every .gdc produced by match_blobs.py into
readable .gd GDScript, mirroring the directory structure under decompiled_gd/.
Also attempts the raw unmatched blobs (as .gdc) so we can read runtime-generated
scripts too.
"""
import glob
import os
import shutil
import subprocess
import sys

GDRE = r"D:/文件资料/学习/自动背包AI/tools/gdre/gdre_tools.exe"
PROJ = r"D:/文件资料/学习/自动背包AI"
SRC_GDC = os.path.join(PROJ, "extracted_gdc")      # matched scripts
BLOB_DIR = r"C:/tmp/bb/dump"                        # raw dumped blobs
OUT = os.path.join(PROJ, "decompiled_gd")


def decompile_one(gdc_path, cwd):
    """Run gdre --decompile; returns True on success."""
    r = subprocess.run(
        [GDRE, "--headless", "--decompile=" + gdc_path],
        cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        text=True, timeout=120,
    )
    out = (r.stdout or "") + (r.stderr or "")
    return "Decompilation complete" in out or "decompiled" in out.lower(), out


def main():
    os.makedirs(OUT, exist_ok=True)
    jobs = []
    # matched .gdc files (exact length)
    for gdc in glob.glob(os.path.join(SRC_GDC, "**", "*.gdc"), recursive=True):
        jobs.append((gdc, os.path.dirname(gdc), False))
    # raw blobs (copy to .gdc, length may include trailing garbage)
    for blob in glob.glob(os.path.join(BLOB_DIR, "blob_*.bin")):
        dst = blob[:-4] + ".gdc"
        shutil.copy(blob, dst)
        jobs.append((dst, BLOB_DIR, True))

    ok = fail = 0
    for gdc, cwd, is_blob in jobs:
        base = os.path.basename(gdc)
        # gdre writes <base without .gdc>.gd next to cwd
        out_name = base[:-4] + ".gd" if base.endswith(".gdc") else base + ".gd"
        out_path = os.path.join(cwd, out_name)
        success, log = decompile_one(gdc, cwd)
        if not success:
            # try forcing bytecode 3.6.0
            r2 = subprocess.run(
                [GDRE, "--headless", "--decompile=" + gdc, "--bytecode=3.6.0"],
                cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=120)
            success = "Decompilation complete" in (r2.stdout or "") + (r2.stderr or "")
            log = (r2.stdout or "") + (r2.stderr or "")
        if success:
            ok += 1
            # move .gd into OUT mirroring structure
            rel = os.path.relpath(out_path, SRC_GDC if not is_blob else BLOB_DIR)
            target = os.path.join(OUT, rel)
            os.makedirs(os.path.dirname(target), exist_ok=True)
            try:
                shutil.move(out_path, target)
            except Exception:
                pass
            tag = "blob" if is_blob else "matched"
            print(f"  [OK] ({tag}) {rel}")
        else:
            fail += 1
            print(f"  [FAIL] {base}\n{log[-600:]}")
    print(f"\nDone. ok={ok} fail={fail}")


if __name__ == "__main__":
    raise SystemExit(main())
