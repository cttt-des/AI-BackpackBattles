"""Prepare replay, release and backup gates for the composed candidate."""
import ast
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/property_control_bundle'
WORK=STAGE/'native_perf50/type_constructor_bundle'
BASE='14263d42d22021a83849baffddf2f6288694886f2733a66c0473850b37407548'
ARCHIVE='eb898e2b5c80970a1ef71611c57423c377dab078'


def main():
    for name in ('run_full_gate.py','finish_gate.py','run_release_measurements.py','install_verified.py','save_checkpoint.py'):
        text=(OLD/name).read_text('utf8').replace('property_control_bundle','type_constructor_bundle')
        text=text.replace('8e7d574055c36e7535cb54139e11514729e72088c4314ad028c623d42ae32cfa',BASE)
        text=text.replace('ccecb628a9e36e05e6491b6fd1bfbe3a47d0af1e',ARCHIVE)
        if name=='finish_gate.py':
            text=text.replace("WORK.parent/'item_locality_bundle/bundle_full_gate.json'", "WORK.parent/'property_control_bundle/bundle_full_gate.json'")
            text=text.replace("'native_item_locality_bundle_bundle_'", "'native_property_control_bundle_bundle_'")
            text=text.replace('property_counts=[0,0]','property_counts=[0,0];tc_counts=[0]*4')
            text=text.replace("        summary=json.loads", "        tc=json.loads((root/'native_type_constructor_audit.json').read_bytes());assert tc['dll_sha256']==dll and tc['verifier_exit_code']==0\n        for i,key in enumerate(('type_hits','type_fallback','fused_initializations','factory_fallback')):tc_counts[i]+=tc['coverage'][key]\n        summary=json.loads",1)
            text=text.replace('    assert property_counts[0]>0', '    assert property_counts[0]>0 and tc_counts[0]>0 and tc_counts[2]>0')
            text=text.replace("'old_event_kernel_type_mismatches':old_mismatches,", "'type_constructor_coverage':dict(zip(('type_hits','type_fallback','fused_initializations','factory_fallback'),tc_counts)),\n        'old_event_kernel_type_mismatches':old_mismatches,")
        if name=='save_checkpoint.py':
            # The copied list contains historical prototypes; retain them and add this round.
            text=text.replace("    audit=json.loads", "    paths.update(STAGE/p for p in ('prototype_native_type_constructor_bundle.py','analyze_native_type_construction.py','setup_type_constructor_bundle.py','setup_type_constructor_qualification.py','test_native_type_constructor.cpp'))\n    audit=json.loads",1)
            text=text.replace("'native_property_audit.json','summary.json'", "'native_property_audit.json','native_type_constructor_audit.json','summary.json'")
            text=text.replace("    relative=sorted", "    # Preserve the per-case inputs to event-hash comparisons, not only summaries.\n    for root in map(Path,audit['receipts']):paths.update(root.glob('*.json'))\n    previous_audit=__import__('json').loads((WORK.parent/'property_control_bundle/full_type_audit.json').read_bytes())\n    for root in map(Path,previous_audit['receipts']):paths.update(root.glob('*.json'))\n    relative=sorted",1)
            helper="def add_paths(paths,env=None):\n    with tempfile.NamedTemporaryFile(prefix='native-verified-paths-',suffix='.txt',delete=False) as output:\n        path=Path(output.name);output.write(b''.join(name.encode('utf8')+b'\\0' for name in paths))\n    try:git('-c','core.autocrlf=false','add','-f',f'--pathspec-from-file={path}','--pathspec-file-nul',env=env)\n    finally:path.unlink()\n\n\n"
            text=text.replace('def main():',helper+'def main():',1)
            text=text.replace("    git('-c','core.autocrlf=false','add','-f','--',*relative)", '    add_paths(relative)')
            text=text.replace("        git('-c','core.autocrlf=false','add','-f','--',*relative,env=env)", '        add_paths(relative,env=env)')
            start=text.index('    checked=[*source,');end=text.index('\n',start)
            text=text[:start]+"    checked=sorted(set(source)|{REPO/path for path in relative}|{native/'libgdcore.dll'})"+text[end:]
            text=text.replace('perf: deploy pure property rows and compact controls with full replay validation', 'perf: compose exact type checks and typed initialization with full replay validation')
            text=text.replace('backup: preserve verified property cache and compact controls', 'backup: preserve verified exact types and typed initialization')
        ast.parse(text,filename=name)
        (WORK/name).write_text(text,encoding='utf8',newline='\n')
    path=WORK/'audit_verify.py'
    text=path.read_text('utf8')
    assert 'type_constructor_before' not in text
    text=text.replace('property_before=[property_stat(i) for i in range(2)]', 'property_before=[property_stat(i) for i in range(2)]\ntype_constructor_stat=lib.gd_diag_native_type_constructor_stat;type_constructor_stat.argtypes=[ctypes.c_uint];type_constructor_stat.restype=ctypes.c_uint64\ntype_constructor_before=[type_constructor_stat(i) for i in range(4)]')
    text=text.replace('raise SystemExit(exit_code)', "type_constructor_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip(('type_hits','type_fallback','fused_initializations','factory_fallback'),[type_constructor_stat(i)-type_constructor_before[i] for i in range(4)]))}\n(out/'native_type_constructor_audit.json').write_text(json.dumps(type_constructor_report,indent=2)+'\\n',encoding='utf8')\nassert type_constructor_report['coverage']['type_hits']>0 and type_constructor_report['coverage']['fused_initializations']>0\nraise SystemExit(exit_code)")
    ast.parse(text);path.write_text(text,encoding='utf8',newline='\n')
    print('Prepared replay, one-shot release, installation and backup gates')


if __name__=='__main__':main()
