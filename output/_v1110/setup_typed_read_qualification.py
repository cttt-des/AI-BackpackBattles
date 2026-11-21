"""Prepare strict qualification and a scoped backup for typed read candidates."""
import ast
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/hot_coverage_bundle'
WORK=STAGE/'native_perf50/typed_read_bundle'
BASE='401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259'
ARCHIVE='60963d0804db5dc01a5cace6d3fe56c658bfae13'


def main():
    for name in ('run_full_gate.py','finish_gate.py','run_release_measurements.py','install_verified.py',
        'save_checkpoint.py','verify_installed.py','qualify_when_ready.py'):
        text=(OLD/name).read_text('utf8').replace('hot_coverage_bundle','typed_read_bundle')
        text=text.replace('14263d42d22021a83849baffddf2f6288694886f2733a66c0473850b37407548',BASE)
        text=text.replace('eb898e2b5c80970a1ef71611c57423c377dab078',ARCHIVE)
        if name in ('finish_gate.py','verify_installed.py'):
            text=text.replace("'property_control_bundle/bundle_full_gate.json'", "'hot_coverage_bundle/bundle_full_gate.json'")
            text=text.replace("'native_property_control_bundle_bundle_'", "'native_hot_coverage_bundle_bundle_'")
            text=text.replace("'property_control_bundle/bundle_src'", "'hot_coverage_bundle/bundle_src'")
        if name=='finish_gate.py':
            text=text.replace('hot_counts=[0,0]','hot_counts=[0,0];typed_counts=[0,0]')
            text=text.replace("        summary=json.loads", "        typed=json.loads((root/'native_typed_read_audit.json').read_bytes());assert typed['dll_sha256']==dll and typed['verifier_exit_code']==0\n        for i,key in enumerate(('property_reads','pure_method_reads')):typed_counts[i]+=typed['coverage'][key]\n        summary=json.loads",1)
            text=text.replace('    assert all(value>0 for value in hot_counts)', '    assert all(value>0 for value in typed_counts) and typed_counts[0]==property_counts[0]\n    assert all(value>0 for value in hot_counts)')
            text=text.replace("'hot_slot_coverage':dict", "'typed_read_coverage':dict(zip(('property_reads','pure_method_reads'),typed_counts)),\n        'hot_slot_coverage':dict",1)
        if name=='verify_installed.py':
            text=text.replace("'hot_coverage_test.json','property_test.json'", "'hot_coverage_test.json','typed_read_test.json','property_test.json'")
            text=text.replace("    assert all(value>0 for value in audit['hot_slot_coverage'].values())", "    assert all(value>0 for value in audit['typed_read_coverage'].values())\n    assert audit['typed_read_coverage']['property_reads']==audit['property_coverage']['field_hits']\n    assert all(value>0 for value in audit['hot_slot_coverage'].values())")
            text=text.replace("'hot_slot_coverage':audit['hot_slot_coverage'],", "'hot_slot_coverage':audit['hot_slot_coverage'],'typed_read_coverage':audit['typed_read_coverage'],")
        if name=='save_checkpoint.py':
            # The previous verified tree already contains the older experiments
            # and baseline case receipts. Add only this round's owned artifacts.
            text=text.replace("    paths.update(p for p in (WORK.parent/'post_eager_trace_profile').iterdir() if p.is_file())\n",'')
            text='\n'.join(line for line in text.splitlines() if not line.startswith('    paths.update(STAGE/p for p in '))+'\n'
            start=text.index("    retained=WORK.parent/'type_constructor_bundle'")
            end=text.index('    audit=json.loads',start);text=text[:start]+text[end:]
            text=text.replace("    previous_audit=json.loads((WORK.parent/'property_control_bundle/full_type_audit.json').read_bytes())\n    for root in map(Path,previous_audit['receipts']):paths.update(root.glob('*.json'))\n",'')
            text=text.replace("'native_hot_slot_audit.json','summary.json'", "'native_hot_slot_audit.json','native_typed_read_audit.json','summary.json'")
            text=text.replace('    audit=json.loads', "    paths.update(STAGE/p for p in ('prototype_native_typed_read_bundle.py','analyze_native_typed_reads.py','setup_typed_read_bundle.py','setup_typed_read_qualification.py','test_native_typed_reads.cpp'))\n    paths.update(p for p in (WORK.parent/'post_hot_coverage_profile').iterdir() if p.is_file())\n    audit=json.loads",1)
            text=text.replace('perf: expand measured hot method and field coverage with strict replay validation','perf: deploy typed pure reads with full replay validation')
            text=text.replace('backup: preserve verified expanded hot coverage and retained experiments','backup: preserve verified typed reads and all strict receipts')
        ast.parse(text,filename=name);(WORK/name).write_text(text,encoding='utf8',newline='\n')
    path=WORK/'audit_verify.py';text=path.read_text('utf8');assert 'typed_read_before' not in text
    text=text.replace('hot_slot_before=[hot_slot_stat(i) for i in range(2)]', 'hot_slot_before=[hot_slot_stat(i) for i in range(2)]\ntyped_read_stat=lib.gd_diag_native_typed_read_stat;typed_read_stat.argtypes=[ctypes.c_uint];typed_read_stat.restype=ctypes.c_uint64\ntyped_read_before=[typed_read_stat(i) for i in range(2)]')
    text=text.replace('raise SystemExit(exit_code)', "typed_read_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip(('property_reads','pure_method_reads'),[typed_read_stat(i)-typed_read_before[i] for i in range(2)]))}\n(out/'native_typed_read_audit.json').write_text(json.dumps(typed_read_report,indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
    ast.parse(text);path.write_text(text,encoding='utf8',newline='\n')
    print('Prepared strict truth, single-run throughput/calibration, guarded deployment and scoped backup')


if __name__=='__main__':main()
