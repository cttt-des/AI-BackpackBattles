"""Read electrical-charge fields directly while preserving callback visibility."""
import argparse
from pathlib import Path
import re

from optimize_native_serial_paths import method_body


def optimize(native):
    shards = native / 'gen/shards'
    path = shards/'shard_00.cpp'
    source = path.read_text('utf8')
    charge = 'Gd__gd_core__CoreItem__INNER__CoreElectricalCharge'
    definition = (shards/'shard_15.cpp').read_text('utf8')
    method = method_body(source, 'CoreItem', '_tickChargePath')
    anchor = '    lv_delta = gd::gd_coerce_float(lv_delta);\n'
    if method[1].count(anchor) != 1:
        raise ValueError('Unexpected charge tick arguments')
    prefix, body = method[1].split(anchor)

    def read(match):
        symbol, name = match.groups()
        if f'case {symbol}: out = this->f_{name}; return true;' not in definition:
            raise ValueError(f'Unexpected charge getter {name}')
        return f'charge->f_{name}'

    lowered, count = re.subn(r'gd::get_prop\(gd_ctx, lv_charge, (SYM_GEN_(\w+)_\d+)\)', read, body)
    if count < 5:
        raise ValueError('Charge tick property reads changed')

    def write(match):
        symbol, name, expression = match.groups()
        if f'case {symbol}: this->f_{name} = val; return true;' not in definition:
            raise ValueError(f'Unexpected charge setter {name}')
        return f'charge->f_{name} = {expression};'

    lowered, writes = re.subn(r'gd::set_prop\(gd_ctx, lv_charge, (SYM_GEN_(\w+)_\d+), ([^\n]+)\);', write, lowered)
    if writes != 5:
        raise ValueError('Charge tick property writes changed')
    fast = (f'    if (lv_charge.kind == gd::GdVal::Kind::Obj && lv_charge.obj &&\n'
            f'            lv_charge.obj->meta() == &META_{charge}) {{\n'
            f'        auto* charge = static_cast<{charge}*>(lv_charge.obj);\n'
            + ''.join('    '+line+'\n' for line in lowered.splitlines()) + '    }\n')
    source = source[:method.start(1)] + prefix + anchor + fast + body + source[method.end(1):]
    include = f'#include "../hdrs/{charge}.hpp"\n'
    if include not in source:
        source = include + source
    path.write_text(source, encoding='utf8', newline='\n')
    print(f'charge path: lowered {count} reads and {writes} writes with exact-type fallback', flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('native', type=Path)
    optimize(parser.parse_args().native)
