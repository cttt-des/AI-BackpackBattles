"""Generate exact-type resolved method rows; preserve overrides and generic paths."""
import hashlib
import json
from pathlib import Path
import re
from analyze_native_dispatch import analyze

STAGE=Path(__file__).resolve().parent
PROFILE=STAGE/'native_perf50/post_bundle_profile'

def digest(data):return hashlib.sha256(data).hexdigest()

def optimize(native):
    profile=json.loads((PROFILE/'profile_depth64.json').read_bytes())
    plan=json.loads((PROFILE/'next_prototype_plan.json').read_bytes())
    design=analyze(native,profile,extra_symbols=[x['symbol'] for x in plan['direct_fast_method_additions']])
    assert design['generated_classes']==design['eligible_classes_with_pure_inheritance']==674
    assert not (native/'native_resolved_dispatch.hpp').exists(),'Use a fresh isolated source copy'
    slots=len(design['selected_methods']);assert slots==48
    symbols=[x['symbol'] for x in design['selected_methods']]
    enum=(native/'gen/sym_ids.hpp').read_text('utf8')
    last=re.findall(r'^\s+(SYM_GEN_\w+),\s*$',enum,re.M)[-1]
    lines=['#pragma once','#include <array>','#include <typeinfo>','#include <unordered_map>']
    for cls in sorted(design['class_rows']):lines.append(f'#include "gen/hdrs/{cls}.hpp"')
    lines+=['namespace gd {',
        'using NativeResolvedFn = GdVal (*)(GdObj*, const GdVal*, int);',
        f'struct NativeMethodRow {{ std::array<NativeResolvedFn,{slots}> methods; }};',
        'template<class C, GdVal (C::*Method)(const GdVal*,int)>',
        'GdVal native_resolved_invoke(GdObj* object,const GdVal* args,int argc) {',
        '    return (static_cast<C*>(object)->*Method)(args,argc);','}',
        'static const NativeMethodRow native_resolved_rows[] = {']
    for row in design['resolved_rows']:
        values=[f'&native_resolved_invoke<{value[0]}, &{value[0]}::fn_{value[1]}>' if value else 'nullptr' for value in row]
        lines.append('    {{'+','.join(values)+'}},')
    lines+=['};','static const NativeMethodRow native_resolved_empty{};',
        f'static constexpr auto native_resolved_slots=[] {{ std::array<int8_t,static_cast<size_t>({last})+1> value{{}}; value.fill(-1);']
    for i,symbol in enumerate(symbols):lines.append(f'    value[{symbol}]={i};')
    lines+=['    return value; }();',
        'static const NativeMethodRow* native_resolved_exact_row(const GdObj* object) {',
        '    static const auto registry=[] {',
        '        std::unordered_map<const std::type_info*,const NativeMethodRow*> value;',
        f'        value.reserve({len(design["class_rows"])});']
    for cls,row in sorted(design['class_rows'].items()):lines.append(f'        value.emplace(&typeid({cls}),&native_resolved_rows[{row}]);')
    lines+=['        return value;','    }();',
        '    const auto found=registry.find(&typeid(*object));',
        '    return found==registry.end()?&native_resolved_empty:found->second;','}',
        'bool try_native_resolved_dispatch(BattleCtx& ctx,GdObj* object,SymId method,const GdVal* args,int argc,GdVal& out,unsigned route) {',
        '    if(!ctx.native_resolved_dispatch || !object || method>=native_resolved_slots.size())return false;',
        '    const int slot=native_resolved_slots[method]; if(slot<0)return false;',
        '    const NativeMethodRow* row=object->native_call_row_;',
        '    if(!row) {',
        '        row=native_resolved_exact_row(object);object->native_call_row_=row;',
        '        if(ctx.native_resolved_collect) {++ctx.native_resolved_counts[2];if(row==&native_resolved_empty)++ctx.native_resolved_counts[3];}',
        '    }',
        '    if(ctx.native_resolved_audit && row!=native_resolved_exact_row(object)) {',
        '        ++ctx.native_resolved_counts[4];return false;',
        '    }',
        '    const auto function=row->methods[slot];',
        '    if(!function) {if(ctx.native_resolved_collect)++ctx.native_resolved_counts[5];return false;}',
        '    if(ctx.native_resolved_collect)++ctx.native_resolved_counts[route<2?route:0];',
        '    out=function(object,args,argc);return true;','}',
        '} // namespace gd','']
    (native/'native_resolved_dispatch.hpp').write_text('\n'.join(lines),encoding='utf8',newline='\n')
    path=native/'gd_rt.hpp';text=path.read_text('utf8')
    anchor='struct GdObj;\n';assert text.count(anchor)==1
    text=text.replace(anchor,anchor+'struct NativeMethodRow;\n',1)
    anchor='    explicit GdObj(BattleCtx* ctx) : rt_ctx_(ctx) {}\n';assert text.count(anchor)==1
    text=text.replace(anchor,anchor+'''    GdObj(const GdObj& other) : rt_ctx_(other.rt_ctx_), gid_(other.gid_), gid_epoch_(other.gid_epoch_), conns_head_(other.conns_head_) {}
    GdObj& operator=(const GdObj& other) {
        rt_ctx_=other.rt_ctx_;gid_=other.gid_;gid_epoch_=other.gid_epoch_;conns_head_=other.conns_head_;
        native_call_row_=nullptr;return *this;
    }
''',1)
    anchor='    GdConn* conns_head_ = nullptr;\n';assert text.count(anchor)==1
    text=text.replace(anchor,anchor+'    const NativeMethodRow* native_call_row_ = nullptr;\n',1)
    anchor='    uint64_t native_event_counts[5]{};\n';assert text.count(anchor)==1
    text=text.replace(anchor,anchor+'''    bool native_resolved_dispatch = false;
    bool native_resolved_audit = false;
    bool native_resolved_collect = false;
    uint64_t native_resolved_counts[6]{};
''',1)
    anchor='        native_event_kernel = false;\n';assert text.count(anchor)==1
    text=text.replace(anchor,anchor+'        native_resolved_dispatch = false;\n',1)
    anchor='GdVal call_method(BattleCtx& ctx, const GdVal& recv, SymId method, const GdVal* args, int argc);'
    assert text.count(anchor)==1
    text=text.replace(anchor,'bool try_native_resolved_dispatch(BattleCtx&,GdObj*,SymId,const GdVal*,int,GdVal&,unsigned);\n'+anchor,1)
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'gd_rt.cpp';text=path.read_text('utf8')
    replacements={
        '            if (recv.obj->call_method(ctx, m, args, argc, out)) return out;':
        '            if (try_native_resolved_dispatch(ctx,recv.obj,m,args,argc,out,0)) return out;\n            if (recv.obj->call_method(ctx, m, args, argc, out)) return out;',
        '        instance->call_method(ctx, method, all.data(), static_cast<int>(all.size()), out);':
        '        if (!try_native_resolved_dispatch(ctx,instance,method,all.data(),static_cast<int>(all.size()),out,1))\n            instance->call_method(ctx, method, all.data(), static_cast<int>(all.size()), out);',
        '        instance->call_method(ctx, method, args, argc, out);':
        '        if (!try_native_resolved_dispatch(ctx,instance,method,args,argc,out,1))\n            instance->call_method(ctx, method, args, argc, out);'}
    for before,after in replacements.items():assert text.count(before)==1,before;text=text.replace(before,after,1)
    text+='\n#include "native_resolved_dispatch.hpp"\n'
    path.write_text(text,encoding='utf8',newline='\n')
    path=native/'engine_wrapper.cpp';text=path.read_text('utf8')
    anchor='    battle.native_event_kernel = true;\n';assert text.count(anchor)==1
    text=text.replace(anchor,anchor+'    battle.native_resolved_dispatch = true;\n',1)
    text+='''
extern "C" uint64_t gd_diag_native_resolved_stat(unsigned field) {return field<6?tl_battle_ctx.native_resolved_counts[field]:0;}
extern "C" void gd_diag_native_resolved_audit(int enabled) {
    tl_battle_ctx.native_resolved_audit=enabled!=0;
    tl_battle_ctx.native_resolved_collect=enabled!=0;
}
'''
    path.write_text(text,encoding='utf8',newline='\n')
    design.update({'object_layout_changed':True,'full_rebuild_required':True,
        'lookup':'lazy exact RTTI pointer; unsupported types cache an empty row; no metadata getter call',
        'arithmetic_rng_argument_binds':'unchanged','copy_and_assignment':'reset internal row only',
        'coverage_order':['generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback']})
    print('Resolved dispatch:',len(design['class_rows']),'exact types,',slots,'methods,',len(design['resolved_rows']),'rows',flush=True)
    return design
