"""Prepare a local label-function comparison against the deployed original DLL."""
import hashlib
import json
from pathlib import Path
import re

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/lazy_diagnostics_probe'
EXPECTED='b2018eb28b90ae5527d9e0764a8b11e5bf6df0b60df7cb722c67629fcfedb588'

def transformed(native):
    source=(native/'gen/shards/shard_00.cpp').read_text('utf8')
    start=source.index('gd::GdVal Gd__gd_core__CoreItem::fn_getNextFreeLabelPosition(')
    end=source.index('\ngd::GdVal ',start+1)
    original=source[start:end]
    lines=original.splitlines()
    assert 'SYM_GEN_trace_diag_1741' in lines[2] and len(lines[2])>200
    lines[2]='    if(!gd::native_skip_label_diagnostic(gd_ctx,*this)) {\n'+lines[2]+'\n    }'
    candidate='\n'.join(lines)+'\n'
    return source,original,candidate

def main():
    WORK.mkdir(exist_ok=True)
    actual=hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()
    assert actual==EXPECTED
    rows=(BASE/'native_resolved_dispatch.hpp').read_text('utf8')
    checked=0
    for line in rows.splitlines():
        match=re.match(r'    \{&META_\w+,&native_property_rows\[\d+\],(\d+)ULL,\{(.*)\}\},?$',line)
        if not match or int(match[1])&3!=2:continue
        methods=re.findall(r'&native_resolved_invoke<[^>]+>|nullptr',match[2])
        assert len(methods)==128
        assert methods[33]=='&native_resolved_invoke<Gd__gd_core__CoreItem, &Gd__gd_core__CoreItem::fn_character>'
        checked+=1
    assert checked>500,checked
    source,original,candidate=transformed(BASE)
    strings=re.search(r'constexpr gd::GdStr battle_string_literals\[\] = \{.*?^\};',source,re.M|re.S)
    assert strings
    body=candidate[candidate.index('{')+1:candidate.rindex('}')].replace('this->','item.').replace('*this','item').replace('from_obj(this)','from_obj(&item)')
    header='''#pragma once
#include "native_event_kernel.hpp"
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include "native_lazy_diagnostics.hpp"
namespace {
'''+strings[0]+'''\n}
inline gd::GdVal candidate_label(Gd__gd_core__CoreItem& item,const gd::GdVal* _args,int _argc) {
'''+body+'}\n'
    (WORK/'preflight_label.hpp').write_text(header,encoding='utf8',newline='\n')
    report={'baseline_dll_sha256':actual,'original_sha256':hashlib.sha256(original.encode()).hexdigest(),
        'candidate_sha256':hashlib.sha256(candidate.encode()).hexdigest(),
        'omitted_call_only_when_all_arguments_proven_pure':True,'float_formatting_not_skipped':True,'pure_character_rows_checked':checked,
        'label_timestamp_iteration_updates_and_rng_calls_unchanged':True,'no_full_build_or_deployment':True,
        'screen_protocol':{'pairs':8,'calls_per_arm':500000,'same_calls_and_inputs_per_arm':True,
            'preserve_first_results':True,'whole_fight_performance_not_established':True}}
    (WORK/'design.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
