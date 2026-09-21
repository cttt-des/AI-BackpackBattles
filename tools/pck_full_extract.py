"""Full PCK extractor (Godot 3.x, pack v1) — extracts every entry, verifies MD5, zero skips."""
import struct, os, sys, hashlib, json

def extract(pck_path, out_dir, verify=True):
    entries_ok, bad = 0, []
    with open(pck_path, 'rb') as f:
        assert f.read(4) == b'GDPC'
        pack_ver, major, minor, patch = struct.unpack('<IIII', f.read(16))
        f.read(64)
        count = struct.unpack('<I', f.read(4))[0]
        print(f"Godot {major}.{minor}.{patch} pack v{pack_ver}, {count} entries")
        metas = []
        for _ in range(count):
            plen = struct.unpack('<I', f.read(4))[0]
            p = f.read(plen).rstrip(b'\x00').decode('utf-8')
            off, size = struct.unpack('<QQ', f.read(16))
            md5 = f.read(16).hex()
            metas.append((p, off, size, md5))

        for i, (p, off, size, md5) in enumerate(metas):
            rel = p[6:] if p.startswith('res://') else p
            outp = os.path.join(out_dir, rel.replace('/', os.sep))
            os.makedirs(os.path.dirname(outp), exist_ok=True)
            f.seek(off)
            data = f.read(size)
            if verify and hashlib.md5(data).hexdigest() != md5:
                bad.append(rel)
            with open(outp, 'wb') as o:
                o.write(data)
            entries_ok += 1
            if (i + 1) % 1000 == 0:
                print(f"  {i+1}/{count}")
    print(f"extracted={entries_ok}/{count} md5_mismatch={len(bad)}")
    for b in bad[:20]:
        print("  BAD:", b)
    return len(bad) == 0

if __name__ == '__main__':
    base = r'D:\文件资料\学习\自动背包AI'
    pck = os.path.join(base, 'Backpack Battles', 'BackpackBattles.pck.bak')
    out = os.path.join(base, 'unpacked_new')
    ok = extract(pck, out)
    sys.exit(0 if ok else 1)
