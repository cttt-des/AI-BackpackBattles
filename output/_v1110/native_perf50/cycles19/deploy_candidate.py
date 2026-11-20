"""Wire the generator and install only after all release gates pass."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]

def main():
    pooled=json.loads((WORK/'ltrans_devirt_ab_pooled.json').read_bytes())
    assert pooled['predeclared_direction_test_passed'] and pooled['pairs'] in (24,32)
    cumulative=json.loads((WORK/'ltrans_devirt_ab_cumulative.json').read_bytes())
    assert len(cumulative['pairs'])==8
    assert all(cumulative[field]['median_reduction_pct']>0 for field in ('main_thread_cpu_s','wall_s'))
    gate=json.loads((WORK/'ltrans_devirt_full_gate.json').read_bytes())
    hashes=json.loads((WORK/'ltrans_devirt_event_hashes.json').read_bytes())
    speed_path=WORK/'ltrans_devirt_serial.json'
    speed=json.loads(speed_path.read_bytes())
    sha=pooled['candidate_dll_sha256']
    assert gate['complete'] and gate['dll_sha256']==sha
    assert hashes['candidate_dll_sha256']==sha and hashes['unchanged_cpp_event_streams']==2604
    assert speed['dll_sha256']==sha and speed['repeat']==len(speed['samples'])==24
    assert min(row['fights_per_second'] for row in speed['samples'])>=50
    target=STAGE/'rebuild_native_lovers_candidate.py'
    previous=target.read_bytes()
    anchor='    generate(stage / "optimize_native_inline_timers.py", stage, str(native))\n'
    original=previous.decode().replace('\r\n','\n')
    assert original.count(anchor)==1 and 'optimize_native_ltrans_devirt.py' not in original
    expected=original.replace(anchor,anchor+'    generate(stage / "optimize_native_reverse_stack_names.py", stage, str(native))\n    generate(stage / "optimize_native_ltrans_devirt.py", stage, str(native))\n')
    pending=(WORK/'rebuild_native_lovers_candidate_pending.py').read_text('utf8')
    assert pending==expected
    target.write_text(expected,encoding='utf8',newline='\n')
    try:
        subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'install_verified.py'),
                        'ltrans_devirt','--speed-report',str(speed_path)],check=True)
    except BaseException:
        target.write_bytes(previous)
        raise
    report_path=WORK/'ltrans_devirt_installation.json'
    report=json.loads(report_path.read_bytes())
    report.update({'generator_wired':True,'generator_entry':str(target),
                   'generator_entry_sha256':hashlib.sha256(target.read_bytes()).hexdigest(),
                   'predeclared_ab_gate_passed':True})
    report_path.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')

if __name__=='__main__':main()
