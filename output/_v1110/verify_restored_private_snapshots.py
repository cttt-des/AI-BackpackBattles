"""Compare independent actual DLLs and test the private view's fallback contract."""
import json
import os
import re
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_restored_private_snapshots import STAGE,WORK,ACCEPTED,EXPECTED,sha

def verify(source,dll,out):
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not out.exists()
    cache=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'
    root=Path(tempfile.mkdtemp(prefix='private-snapshots-differential-',dir=cache));scratch=root/'scratch';scratch.mkdir()
    environment=dict(os.environ,TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))
    records={};raw_files={}
    retained=json.loads((WORK/'retained_baseline.json').read_bytes()) if (WORK/'retained_baseline.json').exists() else None
    for label,headers,library in [('baseline',ACCEPTED/'bundle_src',ACCEPTED/'bundle.dll'),('candidate',source,dll)]:
        assert sha(ACCEPTED/'bundle.dll')==EXPECTED
        folder=root/label;folder.mkdir();shutil.copyfile(library,folder/'libgdcore.dll');records[label]={}
        exports=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-p',str(folder/'libgdcore.dll')]).decode('utf8',errors='replace').split('The Export Tables',1)[1]
        export_name=re.search(r'(?m)^Name\s+[0-9a-fA-F]+\s+(\S+)',exports).group(1)
        assert '/' not in export_name and '\\' not in export_name and export_name.endswith('.dll')
        if export_name!='libgdcore.dll':shutil.copyfile(library,folder/export_name)
        for fixture,flags in [('identity_snapshots',['-DGD_EVENT_IDENTITY_PRODUCTION']),('private_buff_loops',[])]:
            if label=='baseline' and retained:
                assert retained['baseline_dll_sha256']==EXPECTED
                assert retained['fixture_sha256'][fixture]==sha(STAGE/('test_native_'+fixture+'.cpp'))
                row=retained['receipts'][fixture];receipt=Path(row['path']);assert sha(receipt)==row['sha256']
                records[label][fixture]=json.loads(receipt.read_bytes());raw_files[receipt.relative_to(WORK).as_posix()]=sha(receipt)
                continue
            local_fixture=folder/('test_native_'+fixture+'.cpp');shutil.copyfile(STAGE/local_fixture.name,local_fixture)
            exe=folder/(fixture+'.exe');log=out.parent/(label+'_'+fixture+'.log');assert not log.exists()
            with log.open('w',encoding='utf8') as stream:
                command=['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off',*flags,
                    '-I',str(headers),str(local_fixture),str(folder/'libgdcore.dll'),'-o',str(exe)]
                subprocess.run(command,stdout=stream,stderr=subprocess.STDOUT,env=environment,check=True)
                run=subprocess.run([str(exe)],capture_output=True,text=True,env=environment)
                stream.write(run.stderr);stream.flush();run.check_returncode()
            raw=out.parent/(label+'_'+fixture+'_cases.json');assert not raw.exists();raw.write_text(run.stdout,encoding='utf8')
            records[label][fixture]=json.loads(run.stdout);raw_files[raw.name]=sha(raw)
    counts={};differences={}
    for fixture,expected in [('identity_snapshots',143360),('private_buff_loops',18432)]:
        a=records['baseline'][fixture];b=records['candidate'][fixture]
        assert a['passed'] and b['passed'] and a['cases']==b['cases']==expected
        assert len(a['hashes'])==len(b['hashes'])==expected
        differences[fixture]=[i for i,(x,y) in enumerate(zip(a['hashes'],b['hashes'])) if x!=y]
        counts[fixture]=expected
    folder=root/'candidate';exe=folder/'private_view.exe'
    local_helper=folder/'test_native_private_integer_view.cpp';shutil.copyfile(STAGE/local_helper.name,local_helper)
    with (out.parent/'private_integer_view.log').open('w',encoding='utf8') as stream:
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(source),
            str(local_helper),str(folder/'libgdcore.dll'),'-o',str(exe)],
            stdout=stream,stderr=subprocess.STDOUT,env=environment,check=True)
        run=subprocess.run([str(exe)],capture_output=True,text=True,env=environment)
        stream.write(run.stdout+run.stderr);stream.flush();run.check_returncode()
    helper=json.loads(run.stdout);assert helper['passed'] and helper['cases']==73088
    result=dict(passed=not any(differences.values()),cases=sum(counts.values())+helper['cases'],actual_dll_cases=counts,
        helper_cases=helper['cases'],difference_counts={k:len(v) for k,v in differences.items()},
        first_differences={k:v[:30] for k,v in differences.items()},baseline_dll_sha256=EXPECTED,dll_sha256=sha(dll),
        raw_cases_sha256=raw_files,fixture_sha256={p.name:sha(p) for p in [STAGE/('test_native_'+n+'.cpp') for n in ['identity_snapshots','private_buff_loops','private_integer_view']]},
        text_boundaries_mutation_trace_toggle_literal_nested_and_unknown_receivers=True,
        four_rounding_and_four_daz_ftz_modes=True,old_six_counts_per_case_checked=True,no_throughput_claim=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2),flush=True)
    assert result['passed'],result['first_differences']
    return result

def main():
    p=psutil.Process();(WORK/'live_semantic_verification.json').write_text(json.dumps(dict(pid=p.pid,created=p.create_time(),script=str(Path(__file__).resolve())))+'\n',encoding='utf8')
    r=json.loads((WORK/'live_semantic_build.json').read_bytes())
    try:
        other=psutil.Process(r['pid'])
        if other.create_time()==r['created']:other.wait()
    except psutil.NoSuchProcess:pass
    assert json.loads((WORK/'build.json').read_bytes())['passed']
    verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'correctness.json')

if __name__=='__main__':main()
