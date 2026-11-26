"""Isolated first-use storage for the existing display array, never cached values."""
import hashlib
import json
from pathlib import Path
import shutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/control_word_bundle'
WORK=STAGE/'native_perf50/display_storage_prototype'
EXPECTED='680f3e37ed7485daac1d6b023bc8530706efb22370a479a02b2e212609c39775'
ARCHIVE='6f14e73f2b7a6fd3a055dd8a858115cf339d3352'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(t,a,b):
    assert t.count(a)==1,(a[:120],t.count(a))
    return t.replace(a,b,1)

STORAGE='''    // This first array shares its arena-owned object's lifetime. The original
    // GdArr remains mutable and every read still follows f_statDisplayOverrides.
    gd::GdArr native_display_header_;
    gd::GdVal native_display_values_[10];
'''
METHODS='''    bool native_display_header_used_ = false;
    bool native_display_values_used_ = false;
    gd::GdArr* native_make_display_array(gd::BattleCtx& battle) {
        if(battle.native_inline_timer_headers && !native_display_header_used_ &&
           battle.arena.owns_storage(this,sizeof(*this))) {
            native_display_header_used_=true;
            return &native_display_header_;
        }
        return gd::GdArr::from_init(battle.arena,{});
    }
    void native_prepare_display_resize(gd::BattleCtx& battle,const gd::GdVal& size) {
        // Run only after the original size expression, immediately before the
        // original resize. No user code runs between installing storage and
        // resize/fill. Escaped old headers/buffers are never recycled.
        if(!battle.native_inline_timer_headers || native_display_values_used_ ||
           !native_display_header_used_ || size.kind!=gd::GdVal::Kind::Int ||
           size.i<=0 || size.i>10 ||
           f_statDisplayOverrides.kind!=gd::GdVal::Kind::Arr ||
           f_statDisplayOverrides.arr!=&native_display_header_ ||
           native_display_header_.data || native_display_header_.len ||
           native_display_header_.cap || native_display_header_.is_pool_real ||
           native_display_header_.timer_watch ||
           !battle.arena.owns_storage(this,sizeof(*this)))return;
        native_display_values_used_=true;
        native_display_header_.data=native_display_values_;
        // Empty-array resize allocates max(n,0*2), exactly n, not ten.
        native_display_header_.cap=static_cast<uint32_t>(size.i);
    }
'''
INIT='gd::GdArr::from_init(gd_ctx.arena, {})'
SIZE_EXPR='gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1398), gd::SYM_size, nullptr, 0)'

def transform(native):
    p=native/'gen/hdrs/Gd__gd_core__CoreItem.hpp';t=p.read_text('utf8')
    t=once(t,'    gd::GdVal f_statDisplayOverrides;\n','    gd::GdVal f_statDisplayOverrides;\n'+STORAGE)
    t=once(t,'    bool native_bridge_gems_header_used_ = false;\n','    bool native_bridge_gems_header_used_ = false;\n'+METHODS)
    p.write_text(t,encoding='utf8',newline='\n')
    p=native/'gen/shards/shard_00.cpp';t=p.read_text('utf8')
    old='this->f_statDisplayOverrides = gd::GdVal::from_arr('+INIT+');'
    t=once(t,old,'this->f_statDisplayOverrides = gd::GdVal::from_arr(this->native_make_display_array(gd_ctx));')
    old='gd::GdVal _ca[] = {'+SIZE_EXPR+'}; return gd::native_inline_call(gd_ctx, this->f_statDisplayOverrides, gd::SYM_resize, _ca, 1);'
    t=once(t,old,'gd::GdVal _ca[] = {'+SIZE_EXPR+'}; this->native_prepare_display_resize(gd_ctx,_ca[0]); return gd::native_inline_call(gd_ctx, this->f_statDisplayOverrides, gd::SYM_resize, _ca, 1);')
    p.write_text(t,encoding='utf8',newline='\n')

def verify_projection(native):
    ref=ACCEPTED/'bundle_src'
    p=Path('gen/hdrs/Gd__gd_core__CoreItem.hpp');t=(native/p).read_text('utf8')
    t=once(t,STORAGE,'');t=once(t,METHODS,'');assert t==(ref/p).read_text('utf8')
    p=Path('gen/shards/shard_00.cpp');t=(native/p).read_text('utf8')
    t=once(t,'this->native_make_display_array(gd_ctx)',INIT)
    t=once(t,'this->native_prepare_display_resize(gd_ctx,_ca[0]); ','')
    assert t==(ref/p).read_text('utf8')
    changed={'gen/hdrs/Gd__gd_core__CoreItem.hpp','gen/shards/shard_00.cpp'}
    files=[p for p in ref.rglob('*') if p.is_file()]
    assert all(sha(p)==sha(native/p.relative_to(ref)) for p in files if p.relative_to(ref).as_posix() not in changed)
    return dict(passed=True,exact_inverse_recovers_all_baseline707_sources=True,
        old_init_order_size_expression_resize_fill_reads_callbacks_and_mutations_preserved=True,
        intentional_core_item_layout_change=True,full20_rebuild_required=True,
        gdval_gdarr_context_watch_and_c_api_layouts_unchanged=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    receipt=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert receipt['remote_upload_verified'] and receipt['remote_verified_commit']==ARCHIVE
    before={p.relative_to(BASE).as_posix():sha(p) for p in BASE.rglob('*') if p.is_file() and p.suffix not in ('.dll','.pyc')}
    frozen=json.loads((ACCEPTED/'source_before_build.json').read_bytes());assert before==frozen
    assert not WORK.exists();WORK.mkdir()
    src=WORK/'prototype_src';shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    transform(src);after={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    modified=sorted(n for n in before if before[n]!=after[n])
    assert modified==['gen/hdrs/Gd__gd_core__CoreItem.hpp','gen/shards/shard_00.cpp']
    result=dict(source_sha256=after,baseline_dll_sha256=EXPECTED,modified_files=modified,
        baseline_verified_backup=ARCHIVE,projection=verify_projection(src),not_for_deployment=True,no_speed_claim=True)
    (WORK/'transform.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(modified=modified,full20_semantic_rebuild_required=True,no_speed_claim=True)))

if __name__=='__main__':main()
