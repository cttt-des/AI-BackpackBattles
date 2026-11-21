"""Move the pure cooldown flag into the existing timer/gem control block."""
import hashlib
import json
from pathlib import Path
import re

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/item_locality_bundle'

def optimize(native,expected=None):
    if expected is None:expected=json.loads((BASE/'source_before_build.json').read_bytes())
    actual={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()}
    assert actual==expected,'Start from frozen accepted8e7 source or an explicitly checked composition input'
    assert 'GdVal() : kind(Kind::Null), i(0) {}' in (native/'gd_rt.hpp').read_text('utf8')
    path=native/'gen/hdrs/Gd__gd_core__CoreItem.hpp';text=path.read_text('utf8')
    field='    gd::GdVal f__cooldown_active;\n'
    anchor='    gd::GdArr native_bridge_gems_header_;\n'
    assert text.count(field)==text.count(anchor)==1
    assert text.index(field)<text.index('    alignas(64) gd::GdVal f_timers;')
    before=re.findall(r'\bgd::GdVal (f_\w+);',text)
    updated=text.replace(field,'',1).replace(anchor,anchor+field,1)
    assert sorted(before)==sorted(re.findall(r'\bgd::GdVal (f_\w+);',updated))
    path.write_text(updated,encoding='utf8',newline='\n')
    return {'status':'implemented_source_only_uncompiled_unmeasured','field_set_unchanged':True,
        'scope':'CoreItem default-constructed pure GdVal member order only; init_fields statements and all methods unchanged',
        'intent':'Place cooldown flag beside bridge gems length; reclaim earlier alignment gap',
        'required':['actual all-type sizes and byte offsets','same-line cooldown/gems-length assertion','fresh20/PGO18 rebuild','existing callback/alias/RNG tests','direct whole-package A/B and full release gates']}
