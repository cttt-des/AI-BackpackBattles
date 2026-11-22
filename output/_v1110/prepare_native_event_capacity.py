"""Preserve event.params identity while reserving four entries on its first String write."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/grid_cooldown_bundle'
WORK=STAGE/'native_perf50/event_capacity_prototype'
EXPECTED='e0bedc4960077407e85763cb5e4af70175a0623cca15e923403fa89174390687'
ARCHIVE='0526a5b0b241cc76c25c9f5d3dfaf9ef24710114'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(t,a,b):
    assert t.count(a)==1,(a,t.count(a));return t.replace(a,b,1)

def transform(native):
    p=native/'gen/shards/shard_11.cpp';text=p.read_text('utf8')
    start=text.index('gd::GdVal Gd__gd_core__CoreEvent::fn_setParam(')
    end=text.index('\n}',start)+2
    method=text[start:end]
    marker='    { gd::GdVal _t1581 = this->f_params;'
    addition='''    // Only the first String write to a canonical empty dictionary changes
    // storage capacity. Preserve dictionary identity and the original setter;
    // later growth and all non-String/foreign representations use normal code.
    if(gd_ctx.native_timer_watch.closed_world && lv_paramName.kind==gd::GdVal::Kind::Str &&
       this->f_params.kind==gd::GdVal::Kind::Dict && this->f_params.dict) {
        auto* params=this->f_params.dict;
        if(!params->len && !params->cap && !params->entries && !params->buckets && !params->bucket_cap) {
            params->entries=gd_ctx.arena.alloc_array<gd::GdDictEntry>(4);
            params->cap=4;
        }
    }
'''
    method=once(method,marker,addition+marker)
    p.write_text(text[:start]+method+text[end:],encoding='utf8',newline='\n')
    return dict(component='event.params first String write reserves four canonical entries',
        dictionary_identity_and_original_setter_preserved=True,ordinary_growth_unbounded=True,
        nonstring_keys_and_noncanonical_containers_unchanged=True,all_public_layouts_unchanged=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert json.loads((ACCEPTED/'post_install_verification.json').read_bytes())['passed']
    assert json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())['remote_verified_commit']==ARCHIVE
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified']).decode().split()[0]==ARCHIVE
    assert not WORK.exists();WORK.mkdir();source=WORK/'prototype_src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(source)
    after={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert [n for n in before if before[n]!=after[n]]==['gen/shards/shard_11.cpp']
    report=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,
        component=component,diagnostic_receipt_sha256=sha(STAGE/'native_perf50/event_param_capacity_probe/fixed200_counts.json'),
        before_any_formal_timing=True,no_speed_claim=True)
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='source_sha256'},indent=2))

if __name__=='__main__':main()
