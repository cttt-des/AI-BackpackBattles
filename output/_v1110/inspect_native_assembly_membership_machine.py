"""Record the actual local caller instructions; static sites are not gains."""
from collections import Counter
import json
import re
import subprocess
from prepare_native_assembly_membership import STAGE,WORK as PROBE,HEADER_NAME,sha,verify_projection
WORK=STAGE/'native_perf50/assembly_membership_bundle'

def main():
    verify_projection(WORK/'bundle_src')
    target=WORK/'assembly_membership_machine';assert not target.exists();target.mkdir()
    symbols=subprocess.check_output(['D:/mingw64/bin/nm.exe','--defined-only','bundle.dll'],cwd=WORK,text=True)
    assert not any('assembly_membership' in s and re.search(r' [Tt] ',s) for s in symbols.splitlines()),'Local membership helper was not inlined'
    rows=[s for s in symbols.splitlines() if 'Gd__gd_core__CoreItem14fn_onItemAdded' in s and re.search(r' [Tt] ',s)]
    assert rows
    (target/'symbols.txt').write_text('\n'.join(rows)+'\n',encoding='utf8');records=[]
    for i,row in enumerate(rows):
        symbol=row.split()[-1];asm=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--no-show-raw-insn','--disassemble='+symbol,'bundle.dll'],cwd=WORK,text=True)
        p=target/f'caller_{i}.txt';p.write_text(asm,encoding='utf8');calls=Counter()
        for line in asm.splitlines():
            if not re.search(r'\bcall\b',line):continue
            m=re.search(r'<([^>]+)>',line)
            if m:calls[m.group(1)]+=1
        records.append(dict(symbol=symbol,assembly_sha256=sha(p),static_direct_call_sites=calls.most_common()))
    counts=STAGE/'native_perf50/assembly_membership_assessment/dictionary_lengths/counts.json'
    data=json.loads(counts.read_bytes());assert data['passed'] and data['families']['affected_object_set']['calls']==1009420
    result=dict(passed=True,dll_sha256=sha(WORK/'bundle.dll'),private_helper_has_no_emitted_out_of_line_function=True,
        exact_header_sha256=sha(WORK/'bundle_src'/HEADER_NAME),caller_instructions=records,
        diagnostic_counts_sha256=sha(counts),all_original_query_commit_and_callback_positions_retained=True,
        mechanism='Inlined Obj/unindexed-empty checks return a primitive false before pointer hashing and boxed gd_in return; nonempty dictionaries call original has and other containers retain gd_in',
        source_projection=verify_projection(WORK/'bundle_src'),static_sites_and_diagnostic_frequencies_not_runtime_cost_or_speed_gain=True)
    p=WORK/'assembly_membership_machine_receipt.json';assert not p.exists();p.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(dict(passed=True,callers=len(records),dll_sha256=result['dll_sha256'])),flush=True)

if __name__=='__main__':main()
