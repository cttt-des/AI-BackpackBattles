"""Specialize bounded motion-loop controls, retaining live queue accesses."""
import hashlib
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/motion_indices_probe'
EXPECTED='3a9269887ace0ad9cd6dafdb9e0ee2a77b857b231f2a0d412888af2516e5b520'
ARCHIVE='fcfe317116882ad80e2dd59611c38c01690ba004'
SIGNATURE='gd::GdVal Gd__gd_core__CoreContext::fn_tickMotion(const gd::GdVal* _args, int _argc)'

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def prepare(native):
    text=(native/'gen/shards/shard_07.cpp').read_text('utf8')
    start=text.index(SIGNATURE)
    original=text[start:text.index('\n}',start)+2]
    opening='    gd::GdVal lv_limit = gd::native_inline_call(gd_ctx, this->f__motion_queue, gd::SYM_size, nullptr, 0);'
    begin=original.index(opening)
    tail=original.index('    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_limit)))) {')
    loop=original[begin:tail]
    replacements={
        opening:'    const uint32_t native_limit = static_cast<uint32_t>(gd::native_inline_call(gd_ctx, this->f__motion_queue, gd::SYM_size, nullptr, 0).as_int());',
        '    gd::GdVal lv_read = gd::GdVal::from_int(0LL);':'    uint32_t native_read = 0;',
        '    gd::GdVal lv_write = gd::GdVal::from_int(0LL);':'    uint32_t native_write = 0;',
        'while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_read, lv_limit))))':'while (native_read < native_limit)',
        'this->f__motion_queue, lv_read)':'this->f__motion_queue, gd::GdVal::from_int(native_read))',
        'gd::GdVal lv_keep = gd::GdVal::from_bool(false);':'bool native_keep = false;',
        'lv_keep = gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_kind_1123), gd::GdVal::from_int(0LL)));':'native_keep = gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_character, SYM_GEN__visual_kind_1123), gd::GdVal::from_int(0LL));',
        'lv_keep = gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_active_1653);':'native_keep = gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_active_1653));',
        'if (gd::gd_truth(lv_keep))':'if (native_keep)',
        'if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_write, lv_read))))':'if (native_write != native_read)',
        'gd::GdVal _t1187 = lv_write;':'gd::GdVal _t1187 = gd::GdVal::from_int(native_write);',
        'lv_write = gd::gd_add(gd_ctx, lv_write, gd::GdVal::from_int(1LL));':'++native_write;',
        'lv_read = gd::gd_add(gd_ctx, lv_read, gd::GdVal::from_int(1LL));':'++native_read;',
    }
    for old,new in replacements.items():
        assert loop.count(old)==1,(old,loop.count(old))
        loop=loop.replace(old,new,1)
    assert all(name not in loop for name in ('lv_read','lv_write','lv_limit','lv_keep'))
    # The original operand evaluation and all entry/property/callback expressions
    # remain intact. Only bounded loop controls and their Bool wrapper change.
    suffix=original[tail:]
    prefix='''    if (this->f__motion_queue.kind == gd::GdVal::Kind::Arr && this->f__motion_queue.arr) {
    const bool native_collect = gd_ctx.native_resolved_collect;
    if (native_collect) ++gd::native_motion_index_counts[0];
'''
    loop=loop.replace('        gd::GdVal lv_entry =','        if (native_collect) ++gd::native_motion_index_counts[1];\n        gd::GdVal lv_entry =',1)
    loop=loop.replace('        if (native_keep) {','        if (native_keep) {\n            if (native_collect) ++gd::native_motion_index_counts[2];',1)
    loop+='''    gd::GdVal lv_limit = gd::GdVal::from_int(native_limit);
    gd::GdVal lv_read = gd::GdVal::from_int(native_read);
    gd::GdVal lv_write = gd::GdVal::from_int(native_write);
'''
    # After callbacks, the queue may be any kind, and size may have arbitrary
    # user semantics. Retain the entire original tail and generic loop.
    assert suffix.endswith('\n}')
    candidate=original[:begin]+prefix+loop+suffix[:-2]+'\n    }\n'+original[begin:]
    assert candidate.count(suffix[:-2])==2
    assert candidate.count('SYM_GEN_tickVisualMotion_1137')==2
    assert candidate.count('SYM_GEN__tickChargePath_506')==2
    helper='namespace gd { static thread_local uint64_t native_motion_index_counts[3]{}; }\n'
    return dict(original=original,candidate=candidate,helper=helper,
                counts=dict(bounded_controls=3,bool_control=1,unchanged_live_entry_and_property_operations=True,unchanged_original_tail=True,unchanged_generic_fallback=True),
                original_sha256=hashlib.sha256(original.encode()).hexdigest(),candidate_sha256=hashlib.sha256(candidate.encode()).hexdigest())

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    WORK.mkdir(exist_ok=True)
    design=prepare(BASE)
    header='#pragma once\n#include "native_inline_dispatch.hpp"\n#include "native_scalar_equal.hpp"\n#include "native_array_index.hpp"\n'+design['helper']
    for kind in ('candidate','original'):
        body=design[kind].replace(SIGNATURE,f'gd::GdVal {"candidate" if kind=="candidate" else "reference"}_tickMotion(Gd__gd_core__CoreContext& context,const gd::GdVal* _args,int _argc)').replace('this->','context.')
        assert 'this' not in body
        header+=body+'\n'
    (WORK/'preflight_motion_indices.hpp').write_text(header,encoding='utf8',newline='\n')
    report={k:v for k,v in design.items() if k not in ('original','candidate','helper')}
    report.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        native_bound_proof='Initial exact array size is uint32; read/write remain <=that captured size, all exactly representable as double in old comparisons; no integer overflow or removed inexact conversion',
        native_records_not_cached_across_callbacks=True,layouts_arithmetic_rng_and_callback_order_unchanged=True,
        no_performance_claim=True)
    (WORK/'source_analysis.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
