"""A varied-input cost screen; reuse the unchanged header's semantic proof."""
import json,shutil,subprocess,tempfile
from pathlib import Path
import psutil
from native_build_storage import isolated_build,sha
STAGE=Path(__file__).resolve().parent;WORK=STAGE/'native_perf50/architecture_three_bundle'
@isolated_build
def main():
    proof=json.loads((WORK/'exact_countdown_probe_receipt.json').read_bytes())
    assert proof['passed'] and proof['source_sha256']['exact_countdown_jump.hpp']==sha(STAGE/'exact_countdown_jump.hpp')
    assert not (WORK/'exact_countdown_varied_raw.json').exists()
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);root=Path(tempfile.mkdtemp(prefix='countdown-varied-'))
    for n in ('exact_countdown_jump.hpp','bench_exact_countdown_jump.cpp'):shutil.copyfile(STAGE/n,root/n)
    with (WORK/'exact_countdown_varied_compile.log').open('xb') as log:subprocess.run(['D:/mingw64/bin/g++.exe','-O3','-std=c++20','-march=native','-ffp-contract=off','-static',str(root/'bench_exact_countdown_jump.cpp'),'-o',str(root/'bench.exe')],check=True,stdout=log,stderr=subprocess.STDOUT,cwd=root)
    p=psutil.Popen([str(root/'bench.exe')],stdout=subprocess.PIPE,stderr=subprocess.PIPE,creationflags=subprocess.CREATE_NO_WINDOW|subprocess.BELOW_NORMAL_PRIORITY_CLASS);p.cpu_affinity([2]);out,error=p.communicate(timeout=120)
    (WORK/'exact_countdown_varied_raw.json').write_bytes(out);(WORK/'exact_countdown_varied_stderr.log').write_bytes(error)
    if p.returncode:raise RuntimeError(error.decode('utf8','replace')[-1500:])
    r=json.loads(out)
    for n in (4,8,32,128):assert len({x['signature'] for x in r['samples'] if x['steps']==n})==1
    (WORK/'exact_countdown_varied_receipt.json').write_text(json.dumps(dict(passed=True,semantic_proof_reused_by_unchanged_header_SHA=True,proof_receipt_sha256=sha(WORK/'exact_countdown_probe_receipt.json'),source_sha256=sha(STAGE/'bench_exact_countdown_jump.cpp'),raw_sha256=sha(WORK/'exact_countdown_varied_raw.json'),not_release_gain=True),indent=2)+'\n',encoding='utf8')
    print('Varied-input cost screen complete; existing semantic proof reused')
if __name__=='__main__':main()
