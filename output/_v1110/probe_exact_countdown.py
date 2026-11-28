"""Build just the integer countdown proof/cost harness in disposable D storage."""
import json,shutil,subprocess,tempfile
from pathlib import Path
import psutil
from native_build_storage import isolated_build,sha
STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/architecture_three_bundle'


@isolated_build
def main():
    assert not (WORK/'exact_countdown_probe_receipt.json').exists()
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    root=Path(tempfile.mkdtemp(prefix='exact-countdown-probe-'))
    for name in ('exact_countdown_jump.hpp','test_exact_countdown_jump.cpp'):shutil.copyfile(STAGE/name,root/name)
    with (WORK/'exact_countdown_compile.log').open('xb') as log:
        subprocess.run(['D:/mingw64/bin/g++.exe','-O3','-std=c++20','-march=native','-ffp-contract=off','-static',str(root/'test_exact_countdown_jump.cpp'),'-o',str(root/'probe.exe')],stdout=log,stderr=subprocess.STDOUT,check=True,cwd=root)
    p=psutil.Popen([str(root/'probe.exe')],stdout=subprocess.PIPE,stderr=subprocess.PIPE,creationflags=subprocess.CREATE_NO_WINDOW|subprocess.BELOW_NORMAL_PRIORITY_CLASS);p.cpu_affinity([2])
    out,error=p.communicate(timeout=120);(WORK/'exact_countdown_probe_raw.json').write_bytes(out);(WORK/'exact_countdown_probe_stderr.log').write_bytes(error)
    if p.returncode:raise RuntimeError(error.decode('utf8','replace')[-1500:])
    r=json.loads(out);assert r['passed'] and r['accepted']>10000
    (WORK/'exact_countdown_probe_receipt.json').write_text(json.dumps(dict(passed=True,source_sha256={n:sha(STAGE/n) for n in ('exact_countdown_jump.hpp','test_exact_countdown_jump.cpp')},raw_sha256=sha(WORK/'exact_countdown_probe_raw.json'),accepted=r['accepted'],rejected_without_changes=r['rejected_without_changes'],literal_SSE_reference=True,full_DLL_build=False,not_release_gain=True),indent=2)+'\n',encoding='utf8')
    print('Exact countdown integer proof and cost probe passed',flush=True)


if __name__=='__main__':main()
