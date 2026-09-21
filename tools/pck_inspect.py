"""Parse a Godot 3.x PCK directory and optionally diff against a folder."""
import struct, os, sys, json, hashlib

def parse_pck(path):
    with open(path, 'rb') as f:
        magic = f.read(4)
        assert magic == b'GDPC', f'bad magic {magic}'
        pack_ver, major, minor, patch = struct.unpack('<IIII', f.read(16))
        f.read(64)  # 16 reserved u32
        count = struct.unpack('<I', f.read(4))[0]
        entries = []
        for _ in range(count):
            plen = struct.unpack('<I', f.read(4))[0]
            raw = f.read(plen)
            p = raw.rstrip(b'\x00').decode('utf-8', 'replace')
            off, size = struct.unpack('<QQ', f.read(16))
            md5 = f.read(16)
            entries.append({'path': p, 'offset': off, 'size': size, 'md5': md5.hex()})
        return {'pack_ver': pack_ver, 'godot': f'{major}.{minor}.{patch}',
                'count': count, 'entries': entries, 'fh': f}

def dir_files(root):
    out = {}
    for dp, _, fs in os.walk(root):
        for fn in fs:
            full = os.path.join(dp, fn)
            rel = os.path.relpath(full, root).replace('\\', '/')
            out[rel] = os.path.getsize(full)
    return out

if __name__ == '__main__':
    base = r'D:\文件资料\学习\自动背包AI'
    pck_new = os.path.join(base, 'Backpack Battles', 'BackpackBattles.pck')
    pck_bak = os.path.join(base, 'Backpack Battles', 'BackpackBattles.pck.bak')

    for label, p in [('CURRENT(.pck)', pck_new), ('ORIGINAL(.bak)', pck_bak)]:
        info = parse_pck(p)
        exts = {}
        for e in info['entries']:
            ext = os.path.splitext(e['path'])[1].lower() or '(none)'
            exts[ext] = exts.get(ext, 0) + 1
        print(f"== {label}: godot={info['godot']} pack_ver={info['pack_ver']} files={info['count']}")
        for ext, n in sorted(exts.items(), key=lambda kv: -kv[1]):
            print(f"   {ext:<14} {n}")
        # save listing
        with open(os.path.join(base, 'tools', f'pck_listing_{label.split("(")[0]}.txt'), 'w', encoding='utf-8') as f:
            for e in sorted(info['entries'], key=lambda x: x['path']):
                f.write(f"{e['path']}\t{e['size']}\t{e['md5']}\n")
