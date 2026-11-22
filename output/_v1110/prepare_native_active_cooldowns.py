"""Stage an ordered cooldown index reusing the accepted structural watcher."""
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/active_cooldown_prototype'
EXPECTED='686f0d6cdb2fc223d4ed50319b31e786eea14383b4ffb9a8fe8633395ee07b43'
ARCHIVE='e5356be288c04804dc645fced2ab24fd360b2238'

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def once(text,old,new):
    assert text.count(old)==1,(old[:100],text.count(old))
    return text.replace(old,new,1)

STORE=r'''
namespace gd {
void native_active_cooldown_hit(unsigned,uint64_t amount=1);
inline void native_active_cooldown_store(BattleCtx* ctx,GdVal& destination,const GdVal& value) {
    if(ctx) {
        auto& watch=ctx->native_timer_watch;
        if(watch.enabled && watch.closed_world &&
           !(destination.kind==GdVal::Kind::Bool && value.kind==GdVal::Kind::Bool && destination.b==value.b)) {
            if(watch.cooldown_version<UINT64_MAX)++watch.cooldown_version;
            if(ctx->native_resolved_collect)native_active_cooldown_hit(6);
        }
    }
    destination=value;
}
}
'''
RUNTIME=r'''
namespace gd {
static thread_local uint64_t native_active_cooldown_counts[10]{};
void native_active_cooldown_hit(unsigned i,uint64_t amount){if(i<10)native_active_cooldown_counts[i]+=amount;}
}
extern "C" uint64_t gd_diag_native_active_cooldown_stat(unsigned i){return i<10?gd::native_active_cooldown_counts[i]:0;}
'''

def transform(native):
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert before==json.loads((STAGE/'native_perf50/closed_timer_bundle/source_before_build.json').read_bytes())
    path=native/'gd_rt.hpp';text=path.read_text('utf8')
    text=once(text,'    void* cache[2]{};','    void* cache[2]{};\n    uint64_t cooldown_version=1;\n    void* cooldown_cache[2]{};')
    text+=STORE;path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gd_rt.cpp';path.write_text(path.read_text('utf8')+RUNTIME,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_00.cpp';text=path.read_text('utf8');stores=[]
    def replace(match):
        stores.append(match.group(0))
        return 'gd::native_active_cooldown_store(this->rt_ctx_,this->f__cooldown_active,'+match.group(1)+');'
    text=re.sub(r'this->f__cooldown_active = ([^;]+);',replace,text)
    assert len(stores)==4
    path.write_text(text,encoding='utf8',newline='\n')
    # Ensure the complete generated write set really is these four sites.
    for p in native.rglob('*'):
        if p.is_file() and p.suffix in ('.cpp','.hpp'):
            assert not re.search(r'(?:->|\.)f__cooldown_active\s*=(?!=)',p.read_text('utf8')),p
    path=native/'gen/shards/shard_03.cpp';text=path.read_text('utf8');blocks=[]
    text=once(text,'#include "../../native_targeted_timers.hpp"','#include "../../native_targeted_timers.hpp"\n#include "../../native_active_cooldowns.hpp"')
    for tag,who in (('_t756','opponent'),('_t762','player')):
        start=text.index('    {\n        gd::GdVal '+tag+' =')
        end=text.index('\n    }',start)+6
        original=text[start:end];blocks.append(original)
        text=text[:start]+f'    if(!gd::active_cooldown_phase(gd_ctx,{who}(),native_segment_snapshot,lv_delta))\n'+original+text[end:]
        assert text.count(original)==1
    path.write_text(text,encoding='utf8',newline='\n')
    shutil.copyfile(STAGE/'native_active_cooldowns.hpp',native/'native_active_cooldowns.hpp')
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    return dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        source_sha256=after,modified_files=[n for n in before if before[n]!=after[n]],new_files=sorted(set(after)-set(before)),
        original_phase_blocks=blocks,original_stores=stores,
        array_header_unchanged=True,battle_context_watch_layout_changes=True,full20_rebuild_required=True,
        only_closed_packed_graph_enabled=True,existing_structural_watch_reused=True,
        eligibility_version_does_not_invalidate_timer_index=True,fresh_cache_buffers_for_nested_rebuilds=True,
        four_store_hooks_use_destination_rt_ctx=True,no_floating_options_rng_or_callback_reordering=True,
        no_correctness_or_speed_claim_before_testing=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified']).decode().split()[0]==ARCHIVE
    assert not WORK.exists();WORK.mkdir();source=WORK/'prototype_src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    report=transform(source)
    (WORK/'transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(source/'gen/shards/shard_03.cpp')],check=True)
    print(json.dumps({k:v for k,v in report.items() if k not in ('source_sha256','original_phase_blocks')},indent=2))

if __name__=='__main__':main()
