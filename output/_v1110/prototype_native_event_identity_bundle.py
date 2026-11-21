"""One event-dispatch identity fast path, without unrelated retained candidates."""
import hashlib
import json
from pathlib import Path
import re
from prepare_event_identity_preflight import transformed_body

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/hot_coverage_bundle'
PROBE=STAGE/'native_perf50/event_identity_probe'


def optimize(native):
    expected=json.loads((BASE/'source_before_build.json').read_bytes())
    assert expected=={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()}
    screen=json.loads((PROBE/'bus_screen.json').read_bytes())
    assert screen['passed'] and screen['metrics']['wall_s']['paired_median_time_reduction_pct']>0
    for name in ('event_identity_fastpath.hpp','event_identity_receiver_fastpath.hpp'):
        assert hashlib.sha256((STAGE/name).read_bytes()).hexdigest()==screen['source_sha256'][name]
    # Every selected getter used by the fast path is a generated direct field
    # accessor. Do not admit a user callback just because a symbol is selected.
    dispatch=(native/'native_resolved_dispatch.hpp').read_text('utf8')
    assert 'GdVal native_resolved_field(const GdObj* object) { return static_cast<const C*>(object)->*Member; }' in dispatch
    start=dispatch.index('static const NativePropertyRow native_property_rows[] = {')
    end=dispatch.index('static const NativeMethodRow native_resolved_rows[]',start)
    rows=re.findall(r'^    \{\{(.*?)\}\},$',dispatch[start:end],re.M)
    assert len(rows)==43
    for row in rows:
        cells=re.split(r',(?=nullptr|&native_resolved_field)',row)
        assert len(cells)==64 and all(cell=='nullptr' or re.fullmatch(r'&native_resolved_field<Gd__\w+, &Gd__\w+::f_\w+>',cell) for cell in cells)
    source,original,candidate=transformed_body(native)
    path=native/'gen/shards/shard_12.cpp'
    path.write_text(source.replace(original,candidate,1),encoding='utf8',newline='\n')
    path=native/'native_event_kernel.hpp';header=path.read_text('utf8')
    for name in ('event_identity_fastpath.hpp','event_identity_receiver_fastpath.hpp'):
        text=(STAGE/name).read_text('utf8').replace('#pragma once\n','').replace('#include "event_identity_fastpath.hpp"\n','')
        header+='\n'+text
    path.write_text(header,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp';text=path.read_text('utf8')
    text+='''
namespace gd {
static thread_local uint64_t native_event_identity_counts[2]{};
void native_event_identity_hit(unsigned index) {if(index<2)++native_event_identity_counts[index];}
}
extern "C" uint64_t gd_diag_native_event_identity_stat(unsigned index) {
    return index<2 ? gd::native_event_identity_counts[index] : 0;
}
'''
    path.write_text(text,encoding='utf8',newline='\n')
    report=json.loads((BASE/'transform.json').read_bytes())
    report.update(status='implemented_uncompiled_unmeasured',baseline_dll_sha256=screen['baseline_dll_sha256'],
        components=['one-allocation primitive emitter identity construction at its original point'],
        modified_native_files=['gen/shards/shard_12.cpp','native_event_kernel.hpp','engine_wrapper.cpp'],
        pure_property_getter_rows_verified=43,selected_getter_slots={'descriptor':8,'identifier':9,'ownerType':18},
        ordinary_branch_original_code_unchanged=True,unknown_and_nonprimitive_fallback_expression_unchanged=True,
        trace_checks_callback_order_snapshot_point_rng_and_ids_preserved=True,
        original_bus_body_sha256=hashlib.sha256(original.encode()).hexdigest(),
        candidate_bus_body_sha256=hashlib.sha256(candidate.encode()).hexdigest(),
        local_screen_scope_only='8 event-bus fixture pairs showed11.94% medianCPU/11.33% wall reduction; no whole-fight conclusion.',
        unrelated_typed_read_arithmetic_timer_cache_changes_included=False,
        object_context_layouts_and_original_arithmetic_source_unchanged=True)
    return report
