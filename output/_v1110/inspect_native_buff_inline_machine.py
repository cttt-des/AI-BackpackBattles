"""Retain actual release instructions; static sites are not execution cost."""
from collections import Counter
import json
import re
import subprocess
from prepare_native_buff_inline_types import STAGE,sha
WORK=STAGE/'native_perf50/buff_inline_types_bundle'

def main():
    target=WORK/'machine_code';assert not target.exists();target.mkdir()
    symbols=subprocess.check_output(['D:/mingw64/bin/nm.exe','--defined-only','bundle.dll'],cwd=WORK,text=True)
    rows=[s for s in symbols.splitlines() if 'Gd__gd_core__CoreBuff16fn_gainTemporary' in s]
    assert any(' T _ZN21Gd__gd_core__CoreBuff16fn_gainTemporary' in s for s in rows)
    (target/'symbols.txt').write_text('\n'.join(rows)+'\n',encoding='utf8')
    calls=Counter();sources=[]
    for i,row in enumerate(rows):
        symbol=row.split()[-1]
        asm=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--no-show-raw-insn','--disassemble='+symbol,'bundle.dll'],cwd=WORK,text=True)
        p=target/f'gain_temporary_{i}.txt';p.write_text(asm,encoding='utf8');sources.append(dict(symbol=symbol,assembly_sha256=sha(p)))
        for line in asm.splitlines():
            if re.search(r'\bcall\b',line):
                m=re.search(r'<([^>]+)>',line)
                if m:calls[m.group(1)]+=1
    assert not any('native_buff_integer_' in n or 'native_buff_boolean_' in n for n in calls), 'Required new machine-code effect absent'
    result=dict(dll_sha256=sha(WORK/'bundle.dll'),symbols=sources,static_direct_call_sites=calls.most_common(),
        scope='Actual main method and emitted local lambda instructions, includes native and generic branches',
        not_dynamic_call_frequency_or_speed_claim=True,baseline_assessment='native_perf50/buff_typed_assessment_20261126/assembly_call_sites.json')
    (WORK/'machine_code_receipt.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(symbols=len(rows),static_direct_call_sites=sum(calls.values()),dll_sha256=result['dll_sha256'])),flush=True)

if __name__=='__main__':main()
