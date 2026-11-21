"""Extract only six existing diagnostic expressions for cross-DLL preflight."""
import hashlib
import json
from pathlib import Path
import re

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/lazy_diagnostics_probe'
GUARDS={72:'gd::native_skip_buff_diagnostic(gd_ctx,*this,{lv_duration})',
    75:'gd::native_skip_buff_farthest_diagnostic(gd_ctx,*this,lv_farthestIndex,lv_farthest)',
    77:'gd::native_skip_buff_diagnostic(gd_ctx,*this,{lv_farthestIndex})',
    88:'gd::native_skip_buff_diagnostic(gd_ctx,*this,{this->f_nextTemporaryTimeout})',
    89:'gd::native_skip_buff_diagnostic(gd_ctx,*this,{this->f_nextTemporaryTimeout})',
    90:'gd::native_skip_buff_timeout_diagnostic(gd_ctx,*this,lv_delay,lv_earliestTimeout)'}

def expressions(native):
    source=(native/'gen/shards/shard_00.cpp').read_text('utf8')
    result={}
    for tag in GUARDS:
        lines=[line for line in source.splitlines() if f'battle_string_literals[{tag}]' in line and 'return this->fn__blnd_snap' in line]
        assert len(lines)==1,(tag,len(lines))
        result[tag]=lines[0]
    assert len(result)==6
    return result

def main():
    assert not (WORK/'buff_screen.json').exists()
    lines=expressions(BASE)
    signature='(unsigned site,Gd__gd_core__CoreBuff& buff,const gd::GdVal& lv_duration,const gd::GdVal& lv_farthestIndex,const gd::GdVal& lv_farthest,const gd::GdVal& lv_delay,const gd::GdVal& lv_earliestTimeout)'
    text='#pragma once\n#include "preflight_label.hpp"\n'
    for candidate in (False,True):
        text+=f'inline void {"candidate" if candidate else "original"}_buff_diagnostic{signature} {{\n    auto& gd_ctx=*buff.rt_ctx_;\n    switch(site) {{\n'
        for tag,line in lines.items():
            call=line.strip().replace('this->','buff.')
            guard=GUARDS[tag].replace('*this','buff').replace('this->','buff.')
            text+=f'        case {tag}: {{\n'+(f'            if(!{guard}) {{\n' if candidate else '')+f'            {call}\n'+('            }\n' if candidate else '')+'            break;\n        }\n'
        text+='    }\n}\n'
    (WORK/'preflight_buff_diagnostics.hpp').write_text(text,encoding='utf8',newline='\n')
    report={'sites':list(GUARDS),'baseline_dll_sha256':hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest(),
        'original_expression_sha256':{str(tag):hashlib.sha256(line.encode()).hexdigest() for tag,line in lines.items()},
        'fractional_nonfinite_and_large_float_formatting_preserved':True,
        'integral_float_skip_requires_original_exact_integer_formatter_branch':True,
        'protocol':{'pairs':8,'calls_per_arm':600000,'all_six_sites_alternate_in_fixed_order':True,
            'local_fixture_only':True,'no_rerun_until_favorable':True}}
    (WORK/'buff_design.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Prepared six isolated original diagnostic expressions; original actual DLL snap function retained')

if __name__=='__main__':main()
