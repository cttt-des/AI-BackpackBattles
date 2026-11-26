"""Record emitted producer/consumer instructions without a speed claim."""
from collections import Counter
import json
import re
import subprocess
from prepare_native_weapon_chain import STAGE,WORK as PROBE,EXPECTED,sha,verify_projection
WORK=STAGE/'native_perf50/weapon_chain_bundle'

def main():
    verify_projection(WORK/'bundle_src')
    target=WORK/'weapon_chain_machine';assert not target.exists();target.mkdir()
    symbols=subprocess.check_output(['D:/mingw64/bin/nm.exe','--defined-only','bundle.dll'],cwd=WORK,text=True)
    rows=[s for s in symbols.splitlines() if 'weapon_chain' in s and re.search(r' [Tt] ',s)]
    assert rows,'Private typed boundaries not emitted'
    (target/'symbols.txt').write_text('\n'.join(rows)+'\n',encoding='utf8')
    records=[];edges=Counter()
    for i,row in enumerate(rows):
        symbol=row.split()[-1]
        asm=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--no-show-raw-insn','--disassemble='+symbol,'bundle.dll'],cwd=WORK,text=True)
        p=target/f'function_{i}.txt';p.write_text(asm,encoding='utf8')
        calls=Counter()
        for line in asm.splitlines():
            if not re.search(r'\bcall\b',line):continue
            m=re.search(r'<([^>]+)>',line)
            if m:
                calls[m.group(1)]+=1
                if 'weapon_chain' in m.group(1):edges[(symbol,m.group(1))]+=1
        records.append(dict(symbol=symbol,assembly_sha256=sha(p),static_direct_call_sites=calls.most_common()))
    assert any('take_damage' in r['symbol'] for r in records)
    # PGO may inline the small character producer into another typed caller.
    assert any('take_damage' in b and a!=b for a,b in edges)
    profile=json.loads((PROBE/'profile_semantic_path.json').read_bytes())
    assert profile['dll_sha256']==sha(PROBE/'prototype.dll') and profile['samples']>=400
    result=dict(passed=True,dll_sha256=sha(WORK/'bundle.dll'),baseline_dll_sha256=EXPECTED,
        actual_emitted_functions=records,private_direct_edges=[dict(caller=a,callee=b,static_sites=n) for (a,b),n in edges.items()],
        semantic_workload_profile_sha256=sha(PROBE/'profile_semantic_path.json'),
        producer_consumer_typed_source_pointer_and_typed_result_abi_present=True,
        whole_original_generic_bodies_retained=True,all_object_layouts_unchanged=True,
        static_sites_and_diagnostic_samples_are_not_dynamic_cost_or_speed_gain=True)
    (WORK/'weapon_chain_machine_receipt.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(passed=True,private_functions=len(records),private_call_edges=len(edges),dll_sha256=result['dll_sha256'])),flush=True)

if __name__=='__main__':main()
