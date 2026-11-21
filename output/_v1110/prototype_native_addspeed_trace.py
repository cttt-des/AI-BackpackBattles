"""Suppress only proven-pure arguments to an exact known no-op trace receiver."""
import hashlib
import json
from pathlib import Path
import re

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/sparse_timer_lazy_bundle'

def method(text,owner,name):
    marker=f'gd::GdVal Gd__gd_core__{owner}::fn_{name}('
    start=text.index(marker);end=text.index('\ngd::GdVal ',start+len(marker))
    return start,end,text[start:end]

GUARD='''    const bool native_dead_speed_trace=[&] {
        if(!gd_ctx.native_event_kernel || !gd::native_resolved_cached_generated(gd_ctx,this))return false;
        // The original descriptor getter precedes the coordinate call. An
        // unknown getter could repair future fields, so reject it before any
        // speculative read of the occupied-cells header or its contents.
        const auto& descriptor=this->f_descriptor;
        if(descriptor.kind!=gd::GdVal::Kind::Obj || !descriptor.obj ||
           &typeid(*descriptor.obj)!=&typeid(Gd__gd_core__CoreItemData))return false;
        if(static_cast<const Gd__gd_core__CoreItemData*>(descriptor.obj)->f_identifier.kind!=gd::GdVal::Kind::Str)return false;
        // Only generated methods are covered by the frozen no-override proof.
        // The original coordinate method may call user getters for object cells.
        const auto& cells=this->f_occupiedCells;
        if(cells.kind!=gd::GdVal::Kind::Arr || !cells.arr)return false;
        for(uint32_t i=0;i<cells.arr->len;++i) {
            const auto& cell=cells.arr->data[i];
            if(cell.kind!=gd::GdVal::Kind::Vec2 || !std::isfinite(cell.v2.x) || !std::isfinite(cell.v2.y))return false;
        }
        // Object formatting can allocate observable instance IDs or call meta().
        switch(lv_amount.kind) {
            case gd::GdVal::Kind::Null:case gd::GdVal::Kind::Bool:
            case gd::GdVal::Kind::Int:case gd::GdVal::Kind::Float:case gd::GdVal::Kind::Str:break;
            default:return false;
        }
        if(this->f_ownerType.kind!=gd::GdVal::Kind::Int || this->f_speedScale.kind!=gd::GdVal::Kind::Float)return false;
        const auto& context_value=this->f_ctx;
        if(context_value.kind!=gd::GdVal::Kind::Obj || !context_value.obj ||
           &typeid(*context_value.obj)!=&typeid(Gd__gd_core__CoreContext))return false;
        const auto& rng_value=static_cast<const Gd__gd_core__CoreContext*>(context_value.obj)->f_rng;
        if(rng_value.kind!=gd::GdVal::Kind::Obj || !rng_value.obj ||
           &typeid(*rng_value.obj)!=&typeid(Gd__gd_core__CoreRng))return false;
        const auto* rng=static_cast<const Gd__gd_core__CoreRng*>(rng_value.obj);
        return !gd::gd_truth(rng->f_oracle_trace) || !gd::gd_truth(rng->f__stacktrace);
    }();
'''

def optimize(native,expected=None):
    if expected is None:expected=json.loads((BASE/'source_before_build.json').read_bytes())
    assert expected=={p.relative_to(native).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in native.rglob('*') if p.is_file()},'Use the frozen classification candidate as composition input'
    path=native/'gen/shards/shard_00.cpp';text=path.read_text('utf8')
    start,end,body=method(text,'CoreItem','addSpeed')
    assert hashlib.sha256(body.encode()).hexdigest()=='5dfb34527106bdee3322d9484279d8126759ec2303d08e8161cb36c85df838b9'
    getter=method(text,'CoreItem','getTopLeftCell')[2]
    assert hashlib.sha256(getter.encode()).hexdigest()=='42a46e5b03188f129b66a42c52f79c716312ff63832627cdd30ec13d2d9a5737'
    rng=(native/'gen/shards/shard_03.cpp').read_text('utf8')
    assert hashlib.sha256(method(rng,'CoreRng','trace_diag')[2].encode()).hexdigest()=='4ac5c56fdfc125135acebe70fb4a29766585431a2e1eed81eadcd41cb7af3d82'
    # A generated instance or static shadow would require a different proof.
    owners=set()
    dispatch=re.compile(r'bool (Gd_\w+)::(?:has_own_method|call_method|call_static_fn)\([^\n]*\{[\s\S]*?\n\}')
    for shard in (native/'gen/shards').glob('*.cpp'):
        for match in dispatch.finditer(shard.read_text('utf8')):
            if 'case SYM_GEN_getTopLeftCell_443:' in match[0]:owners.add(match[1])
    assert owners=={'Gd__gd_core__CoreItem'},owners
    lines=[line for line in body.splitlines() if 'SYM_GEN_trace_diag_1741' in line]
    assert len(lines)==1 and body.count('SYM_GEN_snapshotItemTooltipStat_1384')==2
    line=lines[0]
    updated=body.replace(line,GUARD+'    if(!native_dead_speed_trace) {\n'+line+'\n    }',1)
    text=text[:start]+updated+text[end:]
    text='#include "../hdrs/Gd__gd_core__CoreItemData.hpp"\n#include <cmath>\n#include <typeinfo>\n'+text
    path.write_text(text,encoding='utf8',newline='\n')
    return {'status':'implemented_uncompiled_unmeasured','input_source_manifest_sha256':hashlib.sha256(json.dumps(expected,sort_keys=True).encode()).hexdigest(),
        'scope':'CoreItem.addSpeed trace argument construction only',
        'frozen_method_hashes':{'addSpeed':hashlib.sha256(body.encode()).hexdigest(),'getTopLeftCell':hashlib.sha256(getter.encode()).hexdigest()},
        'generated_getTopLeftCell_dispatch_owners':sorted(owners),
        'fast_subset':['native kernel enabled and exact generated receiver row','finite ordinary Vec2 cells','primitive amount, Int ownerType, Float updated speed','exact CoreItemData with String identifier','exact CoreContext and CoreRng','oracle_trace or stacktrace disabled'],
        'preserved':['original numeric update and two later tooltip snapshots','original trace statement exactly once for enabled/unknown cases','custom methods/getters and object-formatting ID/meta side effects via fallback','math order, RNG and event/source values'],
        'required_before_combined_evaluation':['targeted fallback and diagnostic-output differential tests','full source-identical PGO','fixed200 paired comparisons','2604 strict event and raw24 deployment gates']}
