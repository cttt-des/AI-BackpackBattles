"""Keep the deployed x86 NaN operand choice when LTO reshapes arithmetic."""
from prototype_native_scalar_math_bundle import optimize as previous


def optimize(native):
    result=previous(native)
    runtime=native/'gd_rt.cpp';source=runtime.read_text('utf8')
    # The deployed evaluator chooses the left NaN payload for add/multiply.
    # C++ permits the new LTO link to commute these two operations, so pin only
    # the exceptional two-NaN branch. The actual SSE operation still executes:
    # signaling NaNs retain their original floating exception behavior.
    declarations='\nnamespace gd {\n'
    extra='\nnamespace gd {\n'
    for op,instruction in (('add','addsd'),('mul','mulsd')):
        name='native_original_ordered_nan_'+op
        declarations+=f'GdVal {name}(const GdVal&,const GdVal&);\n'
        anchor=f'GdVal gd_{op}('
        start=source.index(anchor);opening=source.index('{',start)+1
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
    declarations+='}\n';extra+='}\n'
    # Insert forward declarations before any namespace or evaluator definition.
    insertion=source.index('namespace gd {')
    source=source[:insertion]+declarations+source[insertion:]
    runtime.write_text(source,encoding='utf8',newline='\n')
    path=native/'gen/sym_ids.cpp';path.write_text(path.read_text('utf8')+extra,encoding='utf8',newline='\n')
    result.update(status='implemented_uncompiled_unmeasured',
        components=result['components']+['baseline-ordered two-NaN add/multiply with real SSE exception behavior'],
        superseded_candidate='993cd7ed2a0ac35886a376dbdb4adad8be3a264e9eff9c1a998b31db49cb751a',
        superseded_reason='12 cross-DLL NaN payload mismatches: LTO commuted the unchanged public add/multiply numeric branches; no A/B or deployment was attempted.',
        original_evaluators='Baseline source retained except explicit two-Float-NaN add/multiply guards. The actual deployed baseline DLL remains the independent bit-and-exception oracle.',
        ordered_nan_scope='Only two NaN floats in add/multiply. Original operand order, payload, quieting and FE_INVALID are verified against deployed DLL; all other original evaluator branches are unchanged.')
    return result
