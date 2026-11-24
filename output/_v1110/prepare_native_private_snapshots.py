"""Prepare private bounded iteration and pre-callback identity byte snapshots."""
import hashlib
import json
from pathlib import Path
import re
import shutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/object_routes_bundle'
WORK=STAGE/'native_perf50/private_snapshots_prototype'
EXPECTED='f950b64c74684ae70ce4e41b9622541c849da0121e1235ab88b7aaface22a6d7'
ARCHIVE='b8c939d55dd51d31b7a2f11d98b5a0ebc2a6e94d'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

HEADER=r'''#pragma once
#include "native_event_kernel.hpp"

namespace gd {
void native_private_snapshot_hit(unsigned);
// Only generated private sequences use this view. Fallback arrays retain their
// original pointer and length snapshot; each element reads the current data.
struct NativePrivateIntegerView {
    GdArr* array;
    uint32_t length;
    explicit NativePrivateIntegerView(BattleCtx& ctx,const GdVal& input) {
        if(input.kind==GdVal::Kind::Int && input.i<=1024) {
            array=nullptr;length=input.i>0?static_cast<uint32_t>(input.i):0;
            if(ctx.native_resolved_collect)native_private_snapshot_hit(0);
        } else {
            if(ctx.native_resolved_collect)native_private_snapshot_hit(1);
            const auto sequence=gd_iter_seq(ctx.arena,input);
            array=sequence.kind==GdVal::Kind::Arr?sequence.arr:nullptr;
            length=array?array->len:0;
        }
    }
    GdVal at(uint32_t index)const {
        return array?array->data[index]:GdVal::from_int(index);
    }
};

// Capture text at the original observation point, before any callback. Large
// text retains eager allocation; no live source string survives in this view.
struct NativeEventIdentitySnapshot {
    char bytes[128];
    uint32_t length=0;
    bool pending=false;
    bool capture(const GdVal& identifier,const GdStr* delimiter,const GdVal& owner) {
        if(identifier.kind!=GdVal::Kind::Str || owner.kind!=GdVal::Kind::Int)return false;
        char digits[32];
        const auto converted=std::to_chars(digits,digits+sizeof(digits),owner.i);
        if(converted.ec!=std::errc{})return false;
        const uint32_t a=identifier.str?identifier.str->len:0;
        const uint32_t b=delimiter?delimiter->len:0;
        const uint32_t c=static_cast<uint32_t>(converted.ptr-digits);
        const uint64_t total=uint64_t{a}+b+c;
        if(total>sizeof(bytes))return false;
        if(a)std::memcpy(bytes,identifier.str->data,a);
        if(b)std::memcpy(bytes+a,delimiter->data,b);
        std::memcpy(bytes+a+b,digits,c);
        length=static_cast<uint32_t>(total);pending=true;return true;
    }
    GdVal value(BattleCtx& ctx,const GdVal& eager)const {
        return pending?GdVal::from_str(make_str(ctx.arena,bytes,length)):eager;
    }
};

inline bool native_try_event_identity_snapshot(BattleCtx& ctx,const GdVal& emitter,
        const GdStr* delimiter,GdVal& out,NativeEventIdentitySnapshot& snapshot) {
    const auto miss=[&]{if(ctx.native_resolved_collect)native_event_identity_hit(1);return false;};
    if(!ctx.native_resolved_dispatch)return miss();
    const auto descriptor_getter=native_event_identity_getter(ctx,emitter,8);
    const auto owner_getter=native_event_identity_getter(ctx,emitter,18);
    if(!descriptor_getter || !owner_getter)return miss();
    const auto descriptor=(emitter.obj->*descriptor_getter);
    const auto identifier_getter=native_event_identity_getter(ctx,descriptor,9);
    if(!identifier_getter)return miss();
    const auto owner=(emitter.obj->*owner_getter);
    const auto identifier=(descriptor.obj->*identifier_getter);
    const bool captured=snapshot.capture(identifier,delimiter,owner);
    if(!captured && !native_event_identity_string(ctx.arena,identifier,delimiter,owner,out))return miss();
    if(ctx.native_resolved_collect) {
        native_private_snapshot_hit(captured?2:3);
        native_event_identity_hit(0);
        native_inline_property_hit(0);native_inline_property_hit(0);native_inline_property_hit(0);
    }
    return true;
}
}
'''

def transform(native):
    header=native/'native_private_snapshots.hpp';assert not header.exists()
    header.write_text(HEADER,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_00.cpp';text=path.read_text('utf8');sites=[]
    function=re.compile(r'^gd::GdVal Gd__gd_core__CoreBuff::fn_(gainTemporary|loseStacks|onTimeout)\([^\n]*\n(.*?)^}',re.M|re.S)
    loop=re.compile(r'^(\s*)gd::GdVal (_t\d+) = gd::gd_iter_seq\(gd_ctx.arena, (.*)\);\n'
        r'\s*gd::GdArr\* (_t\d+) = \(\2.kind == gd::GdVal::Kind::Arr\) \? \2.arr : nullptr;\n'
        r'\s*uint32_t (_len__t\d+) = \4 \? \4->len : 0u;\n'
        r'(\s*for \(uint32_t (_t\d+) = 0; \7 < \5; \+\+\7\) \{)\n'
        r'(\s*)gd::GdVal lv_i = \4->data\[\7\];',re.M)
    def rewrite_function(match):
        def rewrite(row):
            sites.append(dict(method=match[1],sequence=row[2],input_expression=row[3]))
            return (row[1]+f'gd::NativePrivateIntegerView {row[2]}(gd_ctx, {row[3]});\n'
                +row[1]+f'uint32_t {row[5]} = {row[2]}.length;\n'+row[6]+'\n'
                +row[8]+f'gd::GdVal lv_i = {row[2]}.at({row[7]});')
        body,n=loop.subn(rewrite,match[2]);assert n==(2 if match[1]=='onTimeout' else 6)
        return match[0].replace(match[2],body,1)
    text,n=function.subn(rewrite_function,text);assert n==3 and len(sites)==14
    text='#include "native_private_snapshots.hpp"\n'+text
    text+='\nnamespace gd {static thread_local uint64_t private_snapshot_counts[4]{};void native_private_snapshot_hit(unsigned i){if(i<4)++private_snapshot_counts[i];}}\nextern "C" uint64_t gd_diag_native_private_snapshot_stat(unsigned i){return i<4?gd::private_snapshot_counts[i]:0;}\n'
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gen/shards/shard_12.cpp';text=path.read_text('utf8')
    # The literal helper and native emitAndLog have the existing exact fast
    # identity call. The generic branch and every original fallback stay intact.
    original='if(!gd::native_try_event_identity(gd_ctx,lv_emitter,&battle_string_literals[3],lv__eid2)) {'
    assert text.count(original)==2
    text=text.replace(original,'if(!gd::native_try_event_identity_snapshot(gd_ctx,lv_emitter,&battle_string_literals[3],lv__eid2,_identity_snapshot)) {')
    for signature in ('gd::GdVal gd_native_emit_literal_body(', 'gd::GdVal Gd__gd_core__CoreEventBus::fn_emitAndLog('):
        start=text.index(signature);end=text.index('\n}',start)
        body=text[start:end];position=body.index('    gd::GdVal lv__eid2 =')
        body=body[:position]+'    gd::NativeEventIdentitySnapshot _identity_snapshot;\n'+body[position:]
        # This is the only diagnostic consumer in the optimized native branch.
        consumer='gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), lv__eid2)'
        first=body.index(consumer)
        body=body[:first]+body[first:].replace(consumer,'gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), _identity_snapshot.value(gd_ctx,lv__eid2))',1)
        text=text[:start]+body+text[end:]
    text='#include "native_private_snapshots.hpp"\n'+text
    path.write_text(text,encoding='utf8',newline='\n')
    return dict(private_integer_sites=sites,maximum_fast_integer=1024,identity_byte_capacity=128,
        identity_snapshot_sites=2,original_loop_bodies_and_unknown_fallbacks_retained=True,
        no_layout_change=True,no_float_rewrite=True,no_speed_claim=True)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    backup=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert backup['remote_upload_verified'] and backup['remote_verified_commit']==ARCHIVE
    assert not WORK.exists();WORK.mkdir()
    source=WORK/'prototype_src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(source)
    after={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    changed=sorted(n for n in before if before[n]!=after[n]);assert changed==['gen/shards/shard_00.cpp','gen/shards/shard_12.cpp']
    result=dict(baseline_dll_sha256=EXPECTED,verified_backup=ARCHIVE,source_sha256=after,
        modified_files=changed,new_files=['native_private_snapshots.hpp'],component=component,not_for_deployment=True)
    (WORK/'transform.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(modified=changed,added=['native_private_snapshots.hpp'],sites=14,identity_sites=2)))

if __name__=='__main__':main()
