"""Check the exact source scope and all evaluation gates before formal build."""
import ast
import hashlib
import json
import re
from prepare_native_private_snapshots import WORK as PROBE,STAGE,ACCEPTED,EXPECTED,sha

WORK=STAGE/'native_perf50/private_snapshots_bundle'

def digest(s):return hashlib.sha256(s.encode('utf8')).hexdigest()

def main():
    native=PROBE/'prototype_src';old=ACCEPTED/'bundle_src'
    before=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    after=json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    assert after=={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert sorted(set(after)-set(before))==['native_private_snapshots.hpp']
    assert sorted(n for n in before if before[n]!=after[n])==['gen/shards/shard_00.cpp','gen/shards/shard_12.cpp']
    function=re.compile(r'^gd::GdVal Gd__gd_core__CoreBuff::fn_(gainTemporary|loseStacks|onTimeout)\([^\n]*\n(.*?)^}',re.M|re.S)
    a=(old/'gen/shards/shard_00.cpp').read_text('utf8');b=(native/'gen/shards/shard_00.cpp').read_text('utf8')
    prologue_old=re.compile(r'(?m)^\s*gd::GdVal (_t\d+) = gd::gd_iter_seq\(gd_ctx.arena, (.*)\);\n'
        r'\s*gd::GdArr\* (_t\d+) = \(\1.kind == gd::GdVal::Kind::Arr\) \? \1.arr : nullptr;\n'
        r'\s*uint32_t (_len__t\d+) = \3 \? \3->len : 0u;')
    prologue_new=re.compile(r'(?m)^\s*gd::NativePrivateIntegerView (_t\d+)\(gd_ctx, (.*)\);\n\s*uint32_t (_len__t\d+) = \1.length;')
    methods={}
    for first,second in zip(function.finditer(a),function.finditer(b)):
        assert first[1]==second[1]
        x,old_count=prologue_old.subn(lambda m:'\nPRIVATE_SEQUENCE '+m[1]+' '+m[2]+' '+m[4],first[2])
        y,new_count=prologue_new.subn(lambda m:'\nPRIVATE_SEQUENCE '+m[1]+' '+m[2]+' '+m[3],second[2])
        # Each original element read changes only how its existing integer value
        # is obtained. The complete remainder of every body must match bytes.
        y=re.sub(r'(_t\d+)\.at\((_t\d+)\)',lambda m:f'_t{int(m[1][2:])+1}->data[{m[2]}]',y)
        assert x==y,first[1]
        assert old_count==new_count==(2 if first[1]=='onTimeout' else 6)
        methods[first[1]]=dict(loops=old_count,original_remaining_body_sha256=digest(x))
    assert len(methods)==3
    a=(old/'gen/shards/shard_12.cpp').read_text('utf8');b=(native/'gen/shards/shard_12.cpp').read_text('utf8')
    b=b.removeprefix('#include "native_private_snapshots.hpp"\n')
    b=b.replace('    gd::NativeEventIdentitySnapshot _identity_snapshot;\n','')
    b=b.replace('gd::native_try_event_identity_snapshot(gd_ctx,lv_emitter,&battle_string_literals[3],lv__eid2,_identity_snapshot)',
                'gd::native_try_event_identity(gd_ctx,lv_emitter,&battle_string_literals[3],lv__eid2)')
    b=b.replace('_identity_snapshot.value(gd_ctx,lv__eid2)','lv__eid2')
    assert a==b,'No other event body expression may change'
    from prototype_native_private_snapshots_bundle import optimize
    # Importing is safe; only an actual completed semantic receipt permits use.
    proof=json.loads((PROBE/'correctness.json').read_bytes());assert proof['passed'] and proof['cases']==234880
    assert proof['dll_sha256']==sha(PROBE/'prototype.dll')
    from tempfile import TemporaryDirectory
    import shutil
    with TemporaryDirectory(prefix='private-snapshot-reproduction-') as directory:
        from pathlib import Path
        copy=Path(directory)/'src';shutil.copytree(old,copy)
        result=optimize(copy);assert result['source_sha256']==after
    scripts={p.name:p.read_text('utf8') for p in WORK.glob('*.py')}
    for name,text in scripts.items():ast.parse(text,filename=name)
    validate=scripts['validate_then_compare.py'];assert validate.index("run('verify_private_snapshots.py'")<validate.index("run('run_comparison.py'")
    assert "'affected_private_snapshot_cases'" in scripts['install_verified.py']
    assert 'verify_private(' in scripts['verify_object_routes_after_ab.py']
    assert 'private_snapshots_prototype/transform.json' in scripts['verify_targeted_timers.py']
    assert scripts['build_bundle.py'].count('-save-temps=obj')==2
    assert "tempfile.tempdir=str(scratch)" in scripts['build_bundle.py']
    assert '-flto=2' in (STAGE/'build_native_hot_lto.py').read_text('utf8')
    assert json.loads((WORK/'bounded_followup_policy.json').read_bytes())==json.loads((ACCEPTED/'bounded_followup_policy.json').read_bytes())
    count=sum(p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py' for p in native.rglob('*') if p.is_file())
    assert count==708
    result=dict(passed=True,baseline_dll_sha256=EXPECTED,source_files=count,source_sha256=after,
        full_source_matches_tested_prototype=True,private_loop_remaining_bodies=methods,
        event_remaining_body_byte_identical=True,semantic_receipt_sha256=sha(PROBE/'correctness.json'),
        semantic_cases=234880,persistent_temp_and_original_gate_policy=True,no_speed_claim=True)
    (WORK/'transform_preflight.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print('Passed234880 actual/header cases and708-source exact reproduction; formal timings not started')

if __name__=='__main__':main()
