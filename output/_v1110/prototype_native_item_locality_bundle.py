"""Keep dense timer/gem scan fields and their arena-lifetime headers together."""
import hashlib
from pathlib import Path

HEADER='gen/hdrs/Gd__gd_core__CoreItem.hpp'
OLD='''    alignas(64) gd::GdVal f_timers;
    gd::GdArr native_timer_header_;
    bool native_timer_header_used_ = false;
'''
NEW='''    alignas(64) gd::GdVal f_timers;
    gd::GdVal f_gems;
    gd::GdArr native_timer_header_;
    gd::GdArr native_bridge_gems_header_;
    bool native_timer_header_used_ = false;
    bool native_bridge_gems_header_used_ = false;
    gd::GdArr* native_make_bridge_gems(gd::BattleCtx& battle,uint32_t count) {
        // Only the bridge's post-setup replacement uses this distinct header.
        // init_fields keeps its original independent gems array, and no used
        // header is reset or reused while an alias can still observe it.
        if(battle.native_inline_timer_headers && !native_bridge_gems_header_used_ &&
           battle.arena.owns_storage(this,sizeof(*this))) {
            native_bridge_gems_header_used_=true;
            if(count>0) {
                native_bridge_gems_header_.data=battle.arena.alloc_array<gd::GdVal>(count);
                native_bridge_gems_header_.cap=count;
            }
            return &native_bridge_gems_header_;
        }
        return gd::GdArr::create(battle.arena,count);
    }
'''

def optimize(native,expected):
    current={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()}
    assert current==expected,'Full source must match the selected accepted or retained composition input'
    header=(native/HEADER).read_text('utf8')
    assert header.count(OLD)==1 and header.count('    gd::GdVal f_gems;\n')==1
    assert 'GdVal() : kind(Kind::Null), i(0) {}' in (native/'gd_rt.hpp').read_text('utf8')
    # Header default construction is pure; generated init_fields assignment order
    # and its first timer header lifetime remain untouched.
    updated=header.replace('    gd::GdVal f_gems;\n','',1).replace(OLD,NEW,1)
    wrapper=(native/'engine_wrapper.cpp').read_text('utf8')
    old='    gd::GdArr* gems_arr = gd::GdArr::create(battle.arena, static_cast<uint32_t>(std::max<int32_t>(0, _n_sockets)));'
    new='    gd::GdArr* gems_arr = ci->native_make_bridge_gems(battle, static_cast<uint32_t>(std::max<int32_t>(0, _n_sockets)));'
    assert wrapper.count(old)==1
    (native/HEADER).write_text(updated,encoding='utf8',newline='\n')
    (native/'engine_wrapper.cpp').write_text(wrapper.replace(old,new,1),encoding='utf8',newline='\n')
    # Correct a stale explanatory comment in the frozen preceding diagnostic
    # candidate. Actual safety rejects unknown getters and does not assume the
    # argument evaluation order of nested gd_add calls.
    shard=native/'gen/shards/shard_00.cpp';body=shard.read_text('utf8')
    old_comment='''        // The original descriptor getter precedes the coordinate call. An
        // unknown getter could repair future fields, so reject it before any
        // speculative read of the occupied-cells header or its contents.'''
    new_comment='''        // Nested argument evaluation need not read the descriptor first.
        // Reject unknown getters before speculative field reads; fallback keeps
        // the original expression and its actual callback evaluation order.'''
    if old_comment in body:shard.write_text(body.replace(old_comment,new_comment,1),encoding='utf8',newline='\n')
    return {
        'status':'implemented_source_only_uncompiled_unmeasured',
        'components':['adjacent timer/gems values and inline timer length','distinct embedded bridge-assembled gems header'],
        'generated_init_fields_and_frame_traversal_unchanged':True,
        'new_sparse_index_or_mutation_tracking':False,
        'header_lifetime':'One use only, arena-owned items and existing bridge opt-in; escaped init_fields and previous replacement arrays remain independent',
        'source_input_sha256':current,
        'required':['actual base/derived sizeof/align/offsets','zero/large sockets, alias, reinit, copy, foreign/stack lifetime tests','full20 rebuild and fresh18 PGO','direct combined A/B and existing release gates']}
