"""Pin the deployed x86 add/multiply payload choice only for two float NaNs."""


def optimize(native):
    runtime=native/'gd_rt.cpp';source=runtime.read_text('utf8')
    declarations='\nnamespace gd {\n';extra='\nnamespace gd {\n'
    for op,instruction in (('add','addsd'),('mul','mulsd')):
        name='native_original_ordered_nan_'+op
        declarations+=f'GdVal {name}(const GdVal&,const GdVal&);\n'
        start=source.index(f'GdVal gd_{op}(');opening=source.index('{',start)+1
        guard=f'''
    if (a.kind == GdVal::Kind::Float && b.kind == GdVal::Kind::Float) {{
        uint64_t left_bits, right_bits;
        std::memcpy(&left_bits, &a.f, sizeof(left_bits));
        std::memcpy(&right_bits, &b.f, sizeof(right_bits));
        constexpr uint64_t exponent=UINT64_C(0x7ff0000000000000);
        constexpr uint64_t fraction=UINT64_C(0x000fffffffffffff);
        if ((left_bits&exponent)==exponent && (left_bits&fraction)!=0 &&
            (right_bits&exponent)==exponent && (right_bits&fraction)!=0)
            return {name}(a,b);
    }}'''
        source=source[:opening]+guard+source[opening:]
        extra+=f'''GdVal {name}(const GdVal& a,const GdVal& b) {{
    double value=a.f;
#if defined(__GNUC__) && defined(__x86_64__)
    __asm__ volatile ("{instruction} %1, %0" : "+x"(value) : "x"(b.f) : "memory");
#else
    value = a.f {'+' if op=='add' else '*'} b.f;
#endif
    return GdVal::from_float(value);
}}
'''
    insertion=source.index('namespace gd {')
    source=source[:insertion]+declarations+'}\n'+source[insertion:]
    runtime.write_text(source,encoding='utf8',newline='\n')
    path=native/'gen/sym_ids.cpp'
    path.write_text(path.read_text('utf8')+extra+'}\n',encoding='utf8',newline='\n')
    return {'ordered_nan_scope':'Only two NaN Float operands in original gd_add/gd_mul; actual SSE operation retains left payload, quieting and floating exception flags.',
        'all_other_public_arithmetic_branches_unchanged':True,'non_lto_ordered_nan_functions':2}
