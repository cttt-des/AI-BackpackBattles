#include <vector>
static V input_value(gd::BattleCtx& c,Source& source,unsigned kind){
    const uint64_t bits[]={0,UINT64_C(0x8000000000000000),UINT64_C(1),UINT64_C(0x7ff0000000000000),UINT64_C(0xfff0000000000000),UINT64_C(0x7ff8000000001234),UINT64_C(0xfff8000000004321),UINT64_C(0x7ff0000000001234)};
    if(kind<8)return V::from_float(std::bit_cast<double>(bits[kind]));
    switch(kind){case 8:return V::null();case 9:return V::from_int(INT64_MIN);case 10:return V::from_int(INT64_MAX);case 11:return V::from_bool(false);case 12:return V::from_bool(true);case 13:return V::from_str(gd::make_static_str("12.5"));case 14:return V::from_arr(gd::GdArr::from_init(c.arena,{V::from_int(2)}));case 15:return V::from_dict(gd::GdDict::create(c.arena));case 16:return V::from_vec2(-0.0,1.25);default:return V::from_obj(&source);}
}
static V types_value(gd::BattleCtx& c,Source& source,unsigned kind){
    if(kind<18)return input_value(c,source,kind);
    auto* array=gd::GdArr::create(c.arena);const unsigned mode=kind-18;
    if(mode<4)array->push_back(c.arena,V::from_int(mode==3?98:mode));
    else {
        V a=mode%2==0?V::from_int(0):V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234)));
        V b=mode%2==0?V::from_float(std::bit_cast<double>(UINT64_C(0x7ff0000000001234))):V::from_int(0);
        array->push_back(c.arena,a);array->push_back(c.arena,b);array->push_back(c.arena,V::from_int(mode%4==0?1:2));
        if(mode>7)array->push_back(c.arena,V::from_bool(true));
        if(mode>9)array->push_back(c.arena,V::from_str(gd::make_static_str("0")));
    }
    return V::from_arr(array);
}
static uint64_t check(bool candidate,unsigned method,unsigned type,unsigned key,bool kernel,bool resolved,int rounding){
    assert(std::fesetround(FE_TONEAREST)==0);gd::BattleCtx c;c.native_event_kernel=kernel;c.native_resolved_dispatch=resolved;c.native_resolved_audit=true;c.native_resolved_collect=true;
    Source source(&c);source.init_fields(c);source.f_types=types_value(c,source,type);source.f_flags=input_value(c,source,key);const V value=input_value(c,source,key);
    assert(std::fesetround(rounding)==0);std::feclearexcept(FE_ALL_EXCEPT);V result;
    switch(method){
        case 0:result=candidate?gd::native_damage_record_flag<16LL,&Source::fn_canMiss>(&source):source.fn_canMiss(nullptr,0);break;
        case 1:result=candidate?gd::native_damage_record_flag<32LL,&Source::fn_canCrit>(&source):source.fn_canCrit(nullptr,0);break;
        case 2:result=candidate?gd::native_damage_record_flag<1LL,&Source::fn_canBeBlocked>(&source):source.fn_canBeBlocked(nullptr,0);break;
        case 3:result=candidate?gd::native_damage_record_has_type(&source,&value,1):source.fn_hasType(&value,1);break;
        case 4:result=candidate?gd::native_damage_record_is_attack(&source):source.fn_isAttack(nullptr,0);break;
        default:result=candidate?gd::native_damage_record_is_attack_or_effect(&source):source.fn_isAttackOrEffect(nullptr,0);break;
    }
    const auto flags=std::fetestexcept(FE_ALL_EXCEPT);uint64_t h=mix(hash(result),flags);h=mix(h,hash(source.f_types));h=mix(h,hash(source.f_flags));for(auto count:c.native_resolved_counts)h=mix(h,count);for(auto count:c.native_event_counts)h=mix(h,count);return h;
}
