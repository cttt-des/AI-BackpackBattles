"""Build a narrow spatial-query candidate from the exact deployed source."""
import hashlib
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/spatial_probe'
EXPECTED='39c559a0bc4ef04f89444be63b42b842884a7d2fee1d59c4332fcdc7367d8e0b'
NAMES=('getItemsInCells','countItemsInCells','getBagsInCells')

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def prepare(native):
    source=(native/'gen/shards/shard_13.cpp').read_text('utf8')
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    assert 'case GdVal::Kind::Obj: return a.obj == b.obj;' in runtime
    assert 'for (uint32_t i = 0; i < len; ++i)' in runtime
    helper='''namespace gd {
static thread_local uint64_t native_spatial_counts[4]{};
inline bool native_spatial_lookup(BattleCtx& ctx,const GdVal& receiver,const GdVal& key,GdVal& value) {
    if(ctx.native_resolved_dispatch && receiver.kind==GdVal::Kind::Dict && receiver.dict) {
        if(ctx.native_resolved_collect){native_inline_variant_hit(7);++native_spatial_counts[0];}
        const auto* dict=receiver.dict;
        const auto index=dict->find_index(key);
        if(index<0)return false;
        value=dict->entries[index].val;
        if(ctx.native_resolved_collect)++native_spatial_counts[1];
        return true;
    }
    if(ctx.native_resolved_collect)++native_spatial_counts[3];
    // receiver is a reference to the live field: a custom has callback can replace it.
    if(!gd_truth(native_inline_call(ctx,receiver,SYM_has,&key,1)))return false;
    value=native_array_index(ctx,receiver,key);
    return true;
}
inline bool native_spatial_contains(BattleCtx& ctx,const GdVal& needle,const GdVal& result) {
    if(ctx.native_resolved_dispatch && needle.kind==GdVal::Kind::Obj) {
        if(ctx.native_resolved_collect)++native_spatial_counts[2];
        const auto* items=result.arr;
        for(uint32_t i=0;i<items->len;++i) {
            const auto& entry=items->data[i];
            if(entry.kind==GdVal::Kind::Obj && entry.obj==needle.obj)return true;
        }
        return false;
    }
    return gd_truth(gd_in(needle,result));
}
}
'''
    originals={};updates={}
    for name in NAMES:
        signature=f'gd::GdVal Gd__gd_core__CoreGrid::fn_{name}('
        start=source.index(signature);old=source[start:source.index('\n}',start)+2]
        field='f_bagCells' if name=='getBagsInCells' else 'f_filledCells'
        condition=f'if (gd::gd_truth(([&]() {{ gd::GdVal _ca[] = {{lv_cell}}; return gd::native_inline_call(gd_ctx, this->{field}, gd::SYM_has, _ca, 1); }})())) {{'
        replacement=f'gd::GdVal lv_spatial_value;\n            if (gd::native_spatial_lookup(gd_ctx, this->{field}, lv_cell, lv_spatial_value)) {{'
        assert old.count(condition)==1
        new=old.replace(condition,replacement)
        index=f'gd::native_array_index(gd_ctx, this->{field}, lv_cell)'
        assert new.count(index)==1;new=new.replace(index,'lv_spatial_value')
        for item,result in [('lv_item','lv_itemsInCells'),('lv_bag','lv_bags')]:
            new=new.replace(f'gd::gd_truth(gd::gd_in({item}, {result}))',f'gd::native_spatial_contains(gd_ctx, {item}, {result})')
        originals[name]=old;updates[name]=new
    return dict(helper=helper,originals=originals,updates=updates)

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    WORK.mkdir(exist_ok=True)
    design=prepare(BASE)
    header='#pragma once\n#include "native_inline_dispatch.hpp"\n#include "native_scalar_equal.hpp"\n#include "native_array_index.hpp"\n#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"\n#include "gen/hdrs/Gd__gd_core__CoreUtil.hpp"\n#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"\n'
    header+=design['helper']+'\n#ifndef GD_SPATIAL_PRODUCTION\n'
    for name,new in design['updates'].items():
        header+=new.replace(f'Gd__gd_core__CoreGrid::fn_{name}(const gd::GdVal* _args, int _argc)',f'candidate_{name}(Gd__gd_core__CoreGrid& grid,const gd::GdVal* _args,int _argc)').replace('this->','grid.')+'\n'
    header+='\n#endif\n'
    (WORK/'preflight_spatial.hpp').write_text(header,encoding='utf8',newline='\n')
    plan=dict(baseline_dll_sha256=EXPECTED,helper_sha256=hashlib.sha256(design['helper'].encode()).hexdigest(),methods=list(NAMES),
              components=['one native dictionary lookup instead of has then get','stable object-pointer deduplication'],
              preserve=['live receiver after custom has','per-cell map reads','original input length snapshot','first occurrence order','placed getter timing','original counters','arithmetic RNG and layouts'],
              local_pairs=8,calls_per_arm=100000,whole_fight_gain_unproven=True)
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared three spatial methods; production source unchanged')

if __name__=='__main__':main()
