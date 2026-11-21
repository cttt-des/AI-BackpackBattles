"""Stack proven pure diagnostic omissions on the verified event-path baseline."""
import hashlib
import json
from pathlib import Path
from prepare_native_lazy_diagnostics import transformed
from prepare_native_buff_diagnostics import expressions,GUARDS

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/event_emission_bundle'
PROBE=STAGE/'native_perf50/lazy_diagnostics_probe'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def optimize(native):
    expected=json.loads((BASE/'source_before_build.json').read_bytes())
    assert expected=={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    screen=json.loads((PROBE/'buff_screen.json').read_bytes())
    label=json.loads((PROBE/'screen.json').read_bytes())
    assert screen['passed'] and screen['metrics']['cpu_s']['candidate_wins']==8 and label['passed']
    helper=STAGE/'native_lazy_diagnostics.hpp'
    assert sha(helper)==screen['source_sha256'][helper.name]
    source,original,candidate=transformed(native)
    source=source.replace(original,candidate,1)
    source=source.replace('if(!gd::native_skip_label_diagnostic(gd_ctx,*this))',
        'if(gd::native_lazy_diagnostic_required(gd_ctx,0,gd::native_skip_label_diagnostic(gd_ctx,*this)))',1)
    calls=expressions(native)
    for slot,(tag,guard) in enumerate(GUARDS.items(),1):
        original_line=calls[tag]
        assert source.count(original_line)==1
        indent=original_line[:len(original_line)-len(original_line.lstrip())]
        replacement=indent+f'if(gd::native_lazy_diagnostic_required(gd_ctx,{slot},{guard})) {{\n'+original_line+'\n'+indent+'}'
        source=source.replace(original_line,replacement,1)
    (native/'gen/shards/shard_00.cpp').write_text(source,encoding='utf8',newline='\n')
    path=native/'native_event_kernel.hpp'
    addition='''
namespace gd {
void native_lazy_diagnostic_hit(unsigned,bool);
inline bool native_lazy_diagnostic_required(BattleCtx& ctx,unsigned site,bool skipped) {
    if(ctx.native_resolved_collect)native_lazy_diagnostic_hit(site,skipped);
    return !skipped;
}
}
'''
    path.write_text(path.read_text('utf8')+'\n'+helper.read_text('utf8').replace('#pragma once\n','')+addition,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp'
    path.write_text(path.read_text('utf8')+'''
namespace gd {
static thread_local uint64_t native_lazy_diagnostic_counts[14]{};
void native_lazy_diagnostic_hit(unsigned site,bool skipped) {if(site<7)++native_lazy_diagnostic_counts[site*2+(skipped?0:1)];}
}
extern "C" uint64_t gd_diag_native_lazy_diagnostic_stat(unsigned index) {return index<14?gd::native_lazy_diagnostic_counts[index]:0;}
''',encoding='utf8',newline='\n')
    actual={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    changed=sorted(name for name in expected if actual[name]!=expected[name])
    assert changed==['engine_wrapper.cpp','gen/shards/shard_00.cpp','native_event_kernel.hpp'],changed
    report=json.loads((BASE/'transform.json').read_bytes())
    report.update(status='implemented_uncompiled_unmeasured',baseline_dll_sha256=screen['baseline_dll_sha256'],
        components=['retained deployed event identity/emission optimization','guarded pure label diagnostic','six guarded pure Buff diagnostic expressions'],
        modified_native_files=changed,diagnostic_sites=7,float_noninteger_large_and_nonfinite_fallback_preserved=True,
        unknown_receivers_getters_trace_toggles_and_character_overrides_preserved=True,
        label_timestamp_loop_and_all_rng_calls_unchanged=True,object_and_context_layouts_unchanged=True,
        local_differential_cases=label['cases']+screen['cases'],pure_float_flags_checks=screen['pure_float_flags_checks'],
        local_screen_not_whole_fight_evidence=True)
    return report
