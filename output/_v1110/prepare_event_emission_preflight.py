"""Compose two optimizations of the same event-dispatch path for local screening."""
import hashlib
import json
from pathlib import Path
import re
from prepare_event_identity_preflight import transformed_body

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/event_emission_probe'


def emission_body(native):
    source=(native/'gen/shards/shard_12.cpp').read_text('utf8')
    start=source.index('gd::GdVal Gd__gd_core__CoreEventBus::fn_getEmissionID(')
    end=source.index('\ngd::GdVal ',start+1);original=source[start:end]
    anchor='    lv_signalID = gd::gd_coerce_int(lv_signalID);'
    assert original.count(anchor)==1
    candidate=original.replace(anchor,anchor+'\n    gd::GdVal native_emission;\n    if(gd::native_try_event_emission_id(gd_ctx,lv_emitter,lv_signalID,native_emission))return native_emission;',1)
    return original,candidate


def main():
    WORK.mkdir(exist_ok=True)
    previous=json.loads((STAGE/'native_perf50/event_identity_bundle/ab_assessment.json').read_bytes())
    assert previous['candidate_dll_sha256']=='af3de9457407a4a391aa7bdfb77dc9769a59938d779635a3dadfd58d3f9e46bc'
    for path in (BASE/'gen/shards').glob('*.cpp'):
        assert not re.search(r'case\s+(?:gd::)?SYM_get_instance_id\s*:',path.read_text('utf8')),path
    original,identity=transformed_body(BASE)[1:]
    source=(BASE/'gen/shards/shard_12.cpp').read_text('utf8')
    strings=re.search(r'constexpr gd::GdStr battle_string_literals\[\] = \{.*?^\};',source,re.M|re.S)
    old,new=emission_body(BASE)
    idbody=new[new.index('{')+1:new.rindex('}')].replace('this->','bus.')
    body=identity[identity.index('{')+1:identity.rindex('}')].replace('this->','bus.')
    assert body.count('bus.fn_getEmissionID(_ca, 2)')==2
    body=body.replace('bus.fn_getEmissionID(_ca, 2)','candidate_emission_id(bus,_ca,2)')
    header='''#pragma once
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include "native_event_kernel.hpp"
#include "event_identity_receiver_fastpath.hpp"
#include "event_emission_fastpath.hpp"
namespace {
'''+strings[0]+'''\n}
inline gd::GdVal candidate_emission_id(Gd__gd_core__CoreEventBus& bus,const gd::GdVal* _args,int _argc) {
'''+idbody+'''}
inline gd::GdVal candidate_emit_and_log(Gd__gd_core__CoreEventBus& bus,const gd::GdVal* _args,int _argc) {
'''+body+'}\n'
    (WORK/'preflight_event_bus.hpp').write_text(header,encoding='utf8',newline='\n')
    plan={'status':'declared_before_screen','baseline_dll_sha256':previous['baseline_dll_sha256'],
        'retained_component_dll_sha256':previous['candidate_dll_sha256'],
        'retained_component_evidence':previous['metrics'],
        'components':['retained one-allocation event identity','known generated emitter ID and safe integer composition'],
        'no_generated_instance_id_overrides_verified':True,'unknown_cpp_and_arithmetic_limit_fallbacks_unchanged':True,
        'original_emission_body_sha256':hashlib.sha256(old.encode()).hexdigest(),
        'candidate_emission_body_sha256':hashlib.sha256(new.encode()).hexdigest(),
        'screen_pairs':8,'bus_events_per_arm':1000000,'no_full_simulator_build_before_screen':True,
        'interpretation':'Judge the same-path composition, without requiring each small component to exceed whole-fight noise independently.'}
    (WORK/'screen_protocol.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared same-event-path composition; generated override inventory verified')


if __name__=='__main__':main()
