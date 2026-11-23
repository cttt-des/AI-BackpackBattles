"""Keep the original actual-DLL cases and extend tick-header counterexamples."""
from pathlib import Path
import ast
from prepare_native_frame_proof import STAGE,WORK,once

def main():
    build=(STAGE/'build_native_display_defaults_prototype.py').read_text('utf8')
    build=build.replace('prepare_native_display_defaults','prepare_native_frame_proof')
    build=once(build,"==['engine_wrapper.cpp','gen/shards/shard_00.cpp','native_active_cooldowns.hpp','native_inline_dispatch.hpp']",
        "==['engine_wrapper.cpp','native_inline_dispatch.hpp']")
    build=build.replace('native-display-defaults-','native-frame-proof-')
    build=once(build,"('gd_diag_native_display_defaults_stat',8),",'')
    build=once(build,"    assert counts[1][0]==counts[1][1]==200 and counts[1][3]>0 and counts[1][4]>0\n",'')
    build=once(build,'display_counts=counts[1],active_cooldown_counts=counts[2],targeted_timer_counts=counts[3]',
        'active_cooldown_counts=counts[1],targeted_timer_counts=counts[2]')
    ast.parse(build);(STAGE/'build_native_frame_proof_prototype.py').write_text(build,encoding='utf8',newline='\n')

    fixture=(STAGE/'test_native_display_defaults.cpp').read_text('utf8')
    fixture=fixture.replace('gd_diag_native_display_frame_tick','gd_diag_native_frame_proof_tick').replace('gd_diag_native_display_phase','gd_diag_native_frame_proof_phase')
    fixture=once(fixture,',const gd::NativeDefaultDisplayToken*','')
    fixture=once(fixture,'extern "C" uint64_t gd_diag_native_display_defaults_stat(unsigned);','')
    fixture=once(fixture,'&snapshot,&delta,nullptr);','&snapshot,&delta);')
    fixture=once(fixture,'#ifndef NOMINMAX','extern "C" uint64_t gd_diag_native_frame_segment_stat(unsigned);\nextern "C" uint64_t gd_diag_native_type_constructor_stat(unsigned);\n#ifndef NOMINMAX')
    fixture=fixture.replace('gd::NativePackedDisplayScope nested(c,characters[0],characters[1]);','')
    fixture=fixture.replace('gd::NativePackedDisplayScope nested(foreign,nullptr,nullptr);','')
    fixture=fixture.replace('gd::NativePackedDisplayScope nested(c,nullptr,nullptr);assert(gd::native_default_display_version(c)==0);','')
    start=fixture.index('#ifdef GD_DISPLAY_NEW\n    std::vector<gd::NativeTimerWatch*> before;')
    end=fixture.index('#endif',start)+len('#endif')
    fixture=fixture[:start]+fixture[end:]
    fixture=once(fixture,'#ifdef GD_DISPLAY_NEW\n    scope.reset();assert(gd::native_default_display_version(f.c)==0);\n#endif','')
    fixture=once(fixture,'std::cout<<gd_diag_native_display_defaults_stat(i);','std::cout<<0;')
    fixture=fixture.replace('s==43 || s==44','s==43 || s==44 || s==61 || s==62')
    fixture=once(fixture,'        hooks.action=[this]', '''        if(s==54)items[1]->f__cooldown_active=V::from_float(1.0);
        if(s==55)items[1]->f_placed=V::from_float(1.0);
        if(s==56)context->f_show_cooldown_progress=V::from_int(1);
        if(s==57)context->f_show_cooldown_progress=V::from_float(snan());
        if(s==58)items[1]->f__cooldown_active=V::from_float(snan());
        if(s==59)items[1]->f_placed=V::null();
        if(s==60)items[1]->f_placed=V::from_obj(context);
        if(s==63)items[1]->f__cooldown_active=V::from_bool(false);
        hooks.action=[this]''')
    fixture=once(fixture,'                if(scenario==43)', '''                if(scenario==61) {
                    V seed=V::from_int(43);
                    auto* other=static_cast<Context*>(gd::construct_class(c,&META_Gd__gd_core__CoreContext,&seed,1).obj);
                    identities.push_back(other);other->f_show_cooldown_progress=V::from_bool(false);
                    items[1]->f_ctx=V::from_obj(other);
                    items[1]->f_statDisplayOverrides.arr->set_idx(3,value);
                } else if(scenario==62) {
                    items[1]->rt_ctx_=&foreign;
                    items[1]->f_statDisplayOverrides.arr->set_idx(3,value);
                } else if(scenario==43)''')
    fixture=once(fixture,'        case 48:{static const gd::GdClassMeta unknown', '''        case 48:items[1]->native_call_row_=nullptr;break;
        case 49:items[1]->native_call_row_=context->native_call_row_;break;
        case 50:items[1]->rt_ctx_=&foreign;break;
        case 51:{
            V seed=V::from_int(43);
            auto* other=static_cast<Context*>(gd::construct_class(c,&META_Gd__gd_core__CoreContext,&seed,1).obj);
            identities.push_back(other);other->f_show_cooldown_progress=V::from_bool(false);
            other->f_timer_pass_epoch=V::from_int(17);items[1]->f_ctx=V::from_obj(other);break;
        }
        case 52:c.native_resolved_dispatch=false;break;
        case 53:c.native_resolved_audit=false;break;
        case 64:{static const gd::GdClassMeta unknown''')
    fixture=once(fixture,'run(48,1,0,0)','run(64,1,0,0)')
    fixture=once(fixture,'s<48','s<64')
    fixture=once(fixture,'    std::feclearexcept(FE_ALL_EXCEPT);', '''    std::array<uint64_t,21> counters{};
    for(unsigned i=0;i<17;++i)counters[i]=gd_diag_native_frame_segment_stat(i);
    for(unsigned i=0;i<4;++i)counters[17+i]=gd_diag_native_type_constructor_stat(i);
    std::feclearexcept(FE_ALL_EXCEPT);''')
    fixture=once(fixture,'const auto result=f.state();','''auto result=f.state();
    for(unsigned i=0;i<17;++i)result=mix(result,gd_diag_native_frame_segment_stat(i)-counters[i]);
    for(unsigned i=0;i<4;++i)result=mix(result,gd_diag_native_type_constructor_stat(i)-counters[17+i]);''')
    fixture=once(fixture,'&item->f_triggerTime,&item->f_statDisplayOverrides',
        '&item->f_ctx,&item->f_placed,&item->f_triggerTime,&item->f_statDisplayOverrides')
    assert 'NativePackedDisplay' not in fixture and 'native_default_display' not in fixture
    (STAGE/'test_native_frame_proof.cpp').write_text(fixture,encoding='utf8',newline='\n')

    verify=(STAGE/'verify_native_display_defaults.py').read_text('utf8')
    verify=verify.replace('prepare_native_display_defaults','prepare_native_frame_proof').replace('test_native_display_defaults.cpp','test_native_frame_proof.cpp')
    verify=verify.replace('2304','3072').replace('2305','3073')
    verify=once(verify,'    assert all(counts[i]>0 for i in (0,1,2,3,4,5,6,7)),counts\n    assert records[\'candidate\',\'registry\'][\'counts\'][4]>0\n','')
    verify=verify.replace('display_counts=counts,registry_counts=', 'original_frame_and_type_counter_deltas_in_hash=True,unused_counts=counts,registry_counts=')
    verify=verify.replace('gem_getter_mutation_checked_before_actual_override_read=True',
        'gem_getter_context_and_override_mutations_checked=True,cleared_mismatched_rows_and_dispatch_flags_checked=True')
    ast.parse(verify);(STAGE/'verify_native_frame_proof.py').write_text(verify,encoding='utf8',newline='\n')
    print('Prepared 3073 actual-DLL header/flag/getter cases, retaining original FP/callback/counter checks')

if __name__=='__main__':main()
