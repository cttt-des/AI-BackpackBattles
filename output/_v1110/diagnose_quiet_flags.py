"""Keep all failed observations and compare their fingerprints to production."""
import collections,json,re,shutil,subprocess,tempfile
import psutil
from pathlib import Path
from native_build_storage import isolated_build
from prepare_quiet_round import WORK,ACCEPTED,sha,save

@isolated_build
def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    checks=WORK/'flags_diagnostic_v2';assert not checks.exists();checks.mkdir()
    original=WORK/'formal_quiet_core_checks/test_actual_quiet_core.cpp';text=original.read_text('utf8')
    old='unsigned cases=0,accepted=0;';assert text.count(old)==1;text=text.replace(old,'unsigned cases=0,accepted=0,mismatches=0;')
    old='return 2;}';assert text.count(old)==1;text=text.replace(old,'++mismatches;}')
    old=r'{\"passed\":true';assert text.count(old)==1;text=text.replace(old,r'{\"diagnostic_only\":true,\"passed\":false')
    at=text.rfind('}');text=text[:at]+'return mismatches?2:0;\n'+text[at:]
    fixture=checks/'diagnostic.cpp';fixture.write_text(text,encoding='utf8',newline='\n');root=Path(tempfile.mkdtemp(prefix='quiet-flags-diagnostic-'));data={};returns={}
    for label,dll in [('candidate',WORK/'bundle.dll'),('baseline',ACCEPTED/'bundle.dll')]:
        folder=root/label;folder.mkdir();shutil.copyfile(dll,folder/'libgdcore.dll');shutil.copyfile(fixture,folder/'test.cpp')
        with (checks/(label+'_compile.log')).open('wb') as log:subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(ACCEPTED/'bundle_src'),str(folder/'test.cpp'),str(folder/'libgdcore.dll'),'-o',str(folder/'check.exe')],stdout=log,stderr=subprocess.STDOUT,check=True)
        command=[str(folder/'check.exe')]
        if label=='baseline':
            lengths=folder/'lengths.txt';lengths.write_text('\n'.join(map(str,data['candidate']['lengths']))+'\n',encoding='ascii');command.append(str(lengths))
        result=subprocess.run(command,capture_output=True,timeout=180);returns[label]=result.returncode
        (checks/(label+'_raw.json')).write_bytes(result.stdout);(checks/(label+'_stderr.log')).write_bytes(result.stderr)
        assert result.returncode in (0,2);data[label]=json.loads(result.stdout);assert data[label]['diagnostic_only']
    assert returns['candidate']==2 and returns['baseline']==0
    indices=[i for i,(a,b) in enumerate(zip(data['candidate']['hashes'],data['baseline']['hashes'],strict=True)) if a!=b]
    errors=(checks/'candidate_stderr.log').read_text('utf8');modes=collections.Counter(map(int,re.findall(r'Mismatch seed=\d+ mode=(\d+)',errors)))
    assert len(indices)==sum(modes.values()) and all(v=='1' for v in re.findall(r' state=(\d+)',errors))
    save('floating_flags_diagnostic.json',dict(diagnostic_only=True,passed=False,candidate_dll_sha256=sha(WORK/'bundle.dll'),baseline_dll_sha256=sha(ACCEPTED/'bundle.dll'),cases=data['candidate']['cases'],mismatch_count=len(indices),mismatches_by_mode=dict(modes),all_game_fields_and_RNG_match=True,independent_production_DLL_confirms_all_mismatches=True,mismatch_indices=indices,fixture_sha256=sha(fixture),original_first_failure_retained=True,no_AB_samples=True))
    print(json.dumps(dict(mismatches=len(indices),modes=dict(modes),all_game_fields_and_RNG_match=True)),flush=True)
if __name__=='__main__':main()
