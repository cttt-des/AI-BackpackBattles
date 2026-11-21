"""Apply the screened static getter and fixed-table setup transformation."""
import hashlib
import json
from pathlib import Path
from prepare_native_static_setup import analyze, helper
STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/static_collections_bundle'
PROBE=STAGE/'native_perf50/static_setup_probe'

def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def optimize(native):
    before=json.loads((BASE/'source_before_build.json').read_bytes())
    assert before=={p.relative_to(native).as_posix():digest(p) for p in native.rglob('*') if p.is_file()}
    screen=json.loads((PROBE/'screen.json').read_bytes())
    assert screen['passed'] and screen['cases']==6436
    assert digest(PROBE/'static_setup_helper.hpp')==screen['helper_sha256']
    assert (PROBE/'static_setup_helper.hpp').read_text('utf8')==helper()
    classes,old_setup,new_setup,metrics=analyze(native)
    for shard in sorted({row['shard'] for row in classes if row['fast']}):
        path=native/'gen/shards'/shard;text=path.read_text('utf8')
        for row in classes:
            if row['shard']!=shard or not row['fast']:continue
            original=row['original'];assert text.count(original)==1
            switch='    switch (prop) {\n'+''.join(f'        case {symbol}: out = {expression}; return true;\n' for symbol,expression in row['fast'])+'        default: break;\n    }\n'
            updated=original.replace('{\n','{\n'+switch,1)
            text=text.replace(original,updated,1)
        path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_00.cpp';text=path.read_text('utf8');assert text.count(old_setup)==1
    inline_helper=helper().replace('#pragma once\n','').replace('#include "gd_rt.hpp"\n','')
    text=text.replace(old_setup,inline_helper+'\n'+new_setup,1)
    for old,new in metrics.values():assert text.count(old)==1;text=text.replace(old,new,1)
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp'
    path.write_text(path.read_text('utf8')+'''
namespace gd {
static thread_local uint64_t native_static_setup_counts[4]{};
void native_static_setup_hit(unsigned index){if(index<4)++native_static_setup_counts[index];}
}
extern "C" uint64_t gd_diag_native_static_setup_stat(unsigned index){return index<4?gd::native_static_setup_counts[index]:0;}
''',encoding='utf8',newline='\n')
    after={p.relative_to(native).as_posix():digest(p) for p in native.rglob('*') if p.is_file()}
    changed=sorted(name for name in before if before[name]!=after[name])
    assert all(name=='engine_wrapper.cpp' or name.startswith('gen/shards/shard_') and name.endswith('.cpp') for name in changed)
    report=json.loads((BASE/'transform.json').read_bytes())
    report.update(baseline_dll_sha256=screen['baseline_dll_sha256'],components=['TLS-free proven primitive static properties','constant metric counts','non-escaping fixed setup loops','ordered fresh dictionary bulk initialization'],
        modified_native_files=changed,pure_getter_classes=sum(bool(row['fast']) for row in classes),pure_getter_cases=sum(len(row['fast']) for row in classes),
        original_getter_sha256={row['name']:hashlib.sha256(row['original'].encode()).hexdigest() for row in classes if row['fast']},
        local_differential_cases=6436,mutable_static_collections_and_fallbacks_unchanged=True,
        setup_unknown_nonempty_reserved_and_alias_fallbacks_preserved=True,original_dictionary_capacity_bucket_order_and_hashes_preserved=True,
        object_context_layout_headers_and_public_arithmetic_unchanged=True,no_whole_fight_gain_claim=True)
    return report
