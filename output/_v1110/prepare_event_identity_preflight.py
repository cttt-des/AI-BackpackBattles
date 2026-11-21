"""Lower only the native bus emitter identity and preserve its original fallback."""
import hashlib
import json
from pathlib import Path
import re

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/event_identity_probe'


def transformed_body(native):
    source=(native/'gen/shards/shard_12.cpp').read_text('utf8')
    start=source.index('gd::GdVal Gd__gd_core__CoreEventBus::fn_emitAndLog(')
    end=source.index('\ngd::GdVal ',start+1)
    original=source[start:end]
    boundary=original.index('\n    }\n    gd::GdVal lv_emitter')
    prefix=original[:boundary]
    assignments=re.findall(r'^        lv__eid2 = .*;$',prefix,re.M)
    assert len(assignments)==1
    old=assignments[0]
    replacement='''        if(!gd::native_try_event_identity(gd_ctx,lv_emitter,&battle_string_literals[3],lv__eid2)) {
'''+old+'''
        }'''
    candidate=prefix.replace(old,replacement,1)+original[boundary:]
    assert candidate.count('native_try_event_identity')==1
    return source,original,candidate


def main():
    WORK.mkdir(exist_ok=True)
    report=json.loads((WORK/'primitive_screen.json').read_bytes())
    assert report['passed'] and report['metrics']['wall_s']['candidate_wins']==8
    source,original,candidate=transformed_body(BASE)
    strings=re.search(r'constexpr gd::GdStr battle_string_literals\[\] = \{.*?^\};',source,re.M|re.S)
    assert strings
    body=candidate[candidate.index('{')+1:candidate.rindex('}')].replace('this->','bus.')
    header='''#pragma once
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include "native_event_kernel.hpp"
#include "event_identity_receiver_fastpath.hpp"
namespace {
'''+strings[0]+'''\n}
inline gd::GdVal candidate_emit_and_log(Gd__gd_core__CoreEventBus& bus,const gd::GdVal* _args,int _argc) {
'''+body+'}\n'
    (WORK/'preflight_event_bus.hpp').write_text(header,encoding='utf8',newline='\n')
    record={'baseline_dll_sha256':report['baseline_dll_sha256'],
        'original_bus_body_sha256':hashlib.sha256(original.encode()).hexdigest(),
        'candidate_bus_body_sha256':hashlib.sha256(candidate.encode()).hexdigest(),
        'modified_emitter_identity_assignments':1,
        'ordinary_event_kernel_disabled_body_unchanged':True,
        'listener_iteration_callback_and_trace_flag_checks_unchanged':True,
        'unknown_getter_and_nonprimitive_identity_uses_original_expression':True,
        'no_delayed_formatting_or_trace_toggle_assumption':True,
        'no_full_build_or_deployment':True}
    (WORK/'integration_design.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf8')
    print('Prepared one identity assignment; original callback and fallback expressions retained')


if __name__=='__main__':main()
