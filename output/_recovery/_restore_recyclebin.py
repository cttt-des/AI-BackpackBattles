# -*- coding: utf-8 -*-
"""回收站抢救：枚举全部条目，凡原路径在 D:\文件资料 下者，从 $R 内容复制还原到
D:\文件资料\_回收站还原\<原名>（不动回收站本身，不覆盖既有文件）。"""
import os
import glob
import struct

RB = r"D:\$Recycle.Bin"
DEST = r"D:\文件资料\_回收站还原"


def parse_i(path):
    """$I 元素：ver(8) size(8) time(8) namelen(4) name(UTF-16LE)。"""
    try:
        d = open(path, "rb").read()
        ver = struct.unpack("<q", d[0:8])[0]
        size = struct.unpack("<q", d[8:16])[0]
        if ver == 2:
            nlen = struct.unpack("<i", d[24:28])[0]
            name = d[28:28 + nlen * 2].decode("utf-16-le").rstrip("\x00")
        else:  # ver1
            name = d[24:24 + 520].decode("utf-16-le").split("\x00")[0]
        return name, size
    except Exception:
        return None, 0


restored = 0
skipped = 0
listing = []
for sid in os.listdir(RB):
    sdir = os.path.join(RB, sid)
    if not os.path.isdir(sdir):
        continue
    for ip in glob.glob(os.path.join(sdir, "$I*")):
        rp = "$R" + ip.split("$I", 1)[1]
        rpath = os.path.join(sdir, rp)
        if not os.path.exists(rpath):
            continue
        orig, size = parse_i(ip)
        if not orig:
            continue
        norm = orig.replace("/", "\\").lower()
        listing.append((orig, size))
        if norm.startswith("d:\\文件资料"):
            rel = orig.split("文件资料", 1)[1].lstrip("\\")
            dest = os.path.join(DEST, rel)
            os.makedirs(os.path.dirname(dest) or DEST, exist_ok=True)
            try:
                if os.path.isdir(rpath):
                    import shutil
                    shutil.copytree(rpath, dest, dirs_exist_ok=True)
                else:
                    if not os.path.exists(dest):
                        import shutil
                        shutil.copy2(rpath, dest)
                        restored += 1
                    else:
                        skipped += 1
            except Exception as exc:
                print("还原失败:", orig, str(exc)[:60])

print("=== 回收站全部条目 ===")
for o, s in sorted(listing):
    print("%10d  %s" % (s, o))
print("\n已还原文件:", restored, "| 跳过(同名已存在):", skipped)
