"""Compose event identity formatting with the same path's instance/signal ID."""
import hashlib
import json
from pathlib import Path
import re
from prototype_native_event_identity_bundle import optimize as identity
from prepare_event_emission_preflight import emission_body

STAGE=Path(__file__).resolve().parent
PROBE=STAGE/'native_perf50/event_emission_probe'


def optimize(native):
    screen=json.loads((PROBE/'bus_screen.json').read_bytes())
    assert screen['passed'] and screen['metrics']['cpu_s']['candidate_wins']==8
    header=STAGE/'event_emission_fastpath.hpp'
    assert hashlib.sha256(header.read_bytes()).hexdigest()==screen['helper_sha256']
    report=identity(native)
    for p in (native/'gen/shards').glob('*.cpp'):
        assert not re.search(r'case\s+(?:gd::)?SYM_get_instance_id\s*:',p.read_text('utf8')),p
    old,new=emission_body(native)
    path=native/'gen/shards/shard_12.cpp';text=path.read_text('utf8');assert text.count(old)==1
    path.write_text(text.replace(old,new,1),encoding='utf8',newline='\n')
    path=native/'native_event_kernel.hpp'
    path.write_text(path.read_text('utf8')+'\n'+header.read_text('utf8').replace('#pragma once\n',''),encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp';text=path.read_text('utf8')
    for before,after in (('native_event_identity_counts[2]{}','native_event_identity_counts[4]{}'),
        ('if(index<2)++native_event_identity_counts[index]','if(index<4)++native_event_identity_counts[index]'),
        ('return index<2 ? gd::native_event_identity_counts[index] : 0','return index<4 ? gd::native_event_identity_counts[index] : 0')):
        assert text.count(before)==1,before;text=text.replace(before,after,1)
    path.write_text(text,encoding='utf8',newline='\n')
    report.update(components=report['components']+['known generated emitter ID and proven safe integer signal composition'],
        retained_identity_dll_sha256='af3de9457407a4a391aa7bdfb77dc9769a59938d779635a3dadfd58d3f9e46bc',
        original_emission_body_sha256=hashlib.sha256(old.encode()).hexdigest(),
        candidate_emission_body_sha256=hashlib.sha256(new.encode()).hexdigest(),
        no_generated_get_instance_id_overrides=True,
        instance_id_assigned_once_before_math=True,
        unknown_cpp_nonobject_unseeded_audit_and_arithmetic_limit_fallbacks_preserved=True,
        local_combined_bus_screen_cpu_median_pct=screen['metrics']['cpu_s']['paired_median_time_reduction_pct'],
        local_combined_bus_screen_not_whole_fight_evidence=True)
    return report
