"""Group item fields used by every physics pass without changing initialization order."""
import argparse
import hashlib
from pathlib import Path
import re


HOT = ('_cooldown_active', 'gems', 'timers', 'ctx', 'character_', '_cooldown_blocked_epoch',
       'triggerTime', 'speedScale', 'statDisplayOverrides', 'placed', 'iterationCooldown')


def optimize(native):
    runtime = (native/'gd_rt.hpp').read_text('utf8')
    if 'GdVal() : kind(Kind::Null), i(0) {}' not in runtime:
        raise ValueError('GdVal default construction is no longer the verified pure initialization')
    header = native/'gen/hdrs/Gd__gd_core__CoreItem.hpp'
    source = header.read_text('utf8')
    block = re.search(r'(?:^    gd::GdVal f_\w+;\n)+', source, re.M)
    if not block:
        raise ValueError('Item field declarations are missing')
    fields = re.findall(r'gd::GdVal f_(\w+);', block[0])
    expected = '61c34f04783837937f05d7996f9914a23b894b059b8d201d47e4ad86a82c6d2c'
    field_hash = hashlib.sha256('\n'.join(sorted(fields)).encode()).hexdigest()
    if (len(fields) != len(set(fields)) or not set(HOT) <= set(fields)
            or field_hash != expected):
        raise ValueError('Item fields do not match the expected layout')
    order = [*HOT, *(name for name in fields if name not in HOT)]
    reordered = ''.join(f'    gd::GdVal f_{name};\n' for name in order)
    if reordered == block[0]:
        print('Hot item field layout is already applied', flush=True)
        return
    header.write_text(source[:block.start()] + reordered + source[block.end():], encoding='utf8', newline='\n')
    print(f'Grouped {len(HOT)} hot item fields among {len(fields)} declarations. Full dependent rebuild required.', flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('native', type=Path)
    args = parser.parse_args()
    optimize(args.native)
