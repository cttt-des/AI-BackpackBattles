    gd::BattleCtx ctx;Foreign first(&ctx),second(&ctx);
    gd::GdRng rng_a{},rng_b{};gd::GdFuncRef ref_a{},ref_b{};
    gd::GdClassMeta cls_a{},cls_b{};gd::GdEnum enum_a{},enum_b{};
    std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true)};
    for(int64_t i:{INT64_MIN,INT64_MIN+1,-9007199254740993LL,-4294967296LL,-2LL,-1LL,0LL,1LL,2LL,
            4294967296LL,9007199254740991LL,9007199254740992LL,9007199254740993LL,INT64_MAX})values.push_back(V::from_int(i));
    const uint64_t bits[]={0,0x8000000000000000ULL,1,0x8000000000000001ULL,0xfffffffffffffULL,0x10000000000000ULL,
        0x3ff0000000000000ULL,0xbff0000000000000ULL,0x3fe0000000000000ULL,0x4340000000000000ULL,
        0x7fefffffffffffffULL,0x7ff0000000000000ULL,0xfff0000000000000ULL,0x7ff8000000000001ULL,
        0xfff8000000000042ULL,0x7ff0000000000001ULL,0xfff0000000000042ULL};
    for(auto b:bits)values.push_back(V::from_float(std::bit_cast<double>(b)));
    for(auto b:bits){double f=std::bit_cast<double>(b);values.push_back(V::from_vec2(f,0));values.push_back(V::from_vec2(0,f));}
    double snan=std::bit_cast<double>(UINT64_C(0x7ff0000000000001)),qnan=std::bit_cast<double>(UINT64_C(0x7ff8000000000012));
    gd::GdColor colors[]={{0,0,0,1},{-0.0,0,0,1},{1,2,3,4},{snan,0,0,1},{0,snan,0,1},{0,0,snan,1},{0,0,0,snan},{qnan,0,0,1}};
    values.push_back(V::from_color(nullptr));for(auto& c:colors)values.push_back(V::from_color(&c));
    gd::GdStr collision_a={"ab",2,123},collision_b={"cd",2,123};
    for(auto v:{V::from_str(nullptr),V::from_cstr(ctx.arena,""),V::from_cstr(ctx.arena,"abc"),V::from_cstr(ctx.arena,"abc"),
            V::from_str(gd::make_str(ctx.arena,"a\0b",3)),V::from_cstr(ctx.arena,"a\xc3\xa9"),V::from_str(&collision_a),V::from_str(&collision_b)})values.push_back(v);
    auto* empty_a=gd::GdArr::create(ctx.arena);auto* empty_b=gd::GdArr::create(ctx.arena);
    auto* array_a=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_float(snan)});
    auto* array_b=gd::GdArr::from_init(ctx.arena,{V::from_int(1),V::from_float(snan)});
    auto* nested_a=gd::GdArr::from_init(ctx.arena,{V::from_arr(array_a),V::from_int(2)});
    auto* nested_b=gd::GdArr::from_init(ctx.arena,{V::from_arr(array_b),V::from_int(2)});
    for(auto* a:{static_cast<gd::GdArr*>(nullptr),empty_a,empty_b,array_a,array_b,nested_a,nested_b})values.push_back(V::from_arr(a));
    gd::GdDict dict_a{},dict_b{};
    for(auto* d:{static_cast<gd::GdDict*>(nullptr),&dict_a,&dict_b})values.push_back(V::from_dict(d));
    for(unsigned kind:{9u,10u,11u}){V v;v.kind=V::Kind(kind);v.i=0;values.push_back(v);}
    for(auto v:{V::from_obj(&first),V::from_obj(&second),V::from_cls(&cls_a),V::from_cls(&cls_b),V::from_enum(&enum_a),V::from_enum(&enum_b),
            V::from_funcref(nullptr),V::from_funcref(&ref_a),V::from_funcref(&ref_b),V::from_rng(nullptr),V::from_rng(&rng_a),V::from_rng(&rng_b)})values.push_back(v);
    for(unsigned kind:{14u,255u}){V v;v.kind=V::Kind(kind);v.i=0x12345678;values.push_back(v);}
