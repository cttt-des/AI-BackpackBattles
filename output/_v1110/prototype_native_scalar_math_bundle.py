"""Compose retained typed reads with exact, locally inlined arithmetic branches."""
import hashlib
import json
from pathlib import Path
import re
from prototype_native_typed_read_bundle import optimize as retained

STAGE=Path(__file__).resolve().parent
INLINE='''#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
'''

HEADER='''
// These wrappers live in the existing non-LTO sym_ids compilation unit. In
// particular, exceptional floating values retain the original evaluator.
GdVal native_numeric_original_add(BattleCtx&,const GdVal&,const GdVal&);
GdVal native_numeric_original_sub(const GdVal&,const GdVal&);
GdVal native_numeric_original_mul(const GdVal&,const GdVal&);
GdVal native_numeric_original_div(BattleCtx&,const GdVal&,const GdVal&);
void native_numeric_math_hit(unsigned);
'''

TOKEN=re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|gd::gd_(?:add|sub|mul|div)(?=\s*\()')


def replace(text,old,new):
    assert text.count(old)==1,old[:100]
    return text.replace(old,new,1)


def helpers():
    lines=[HEADER,INLINE+'''bool native_numeric_is_finite(const GdVal& value) {
    return value.kind!=GdVal::Kind::Float ||
        (std::bit_cast<uint64_t>(value.f)&UINT64_C(0x7ff0000000000000))!=UINT64_C(0x7ff0000000000000);
}
''']
    for op,sign in (('add','+'),('sub','-'),('mul','*'),('div','/')):
        has_context=op in ('add','div')
        params='BattleCtx& ctx,' if has_context else ''
        args='ctx,a,b' if has_context else 'a,b'
        def count(category):
            return f'if(ctx.native_resolved_collect)native_numeric_math_hit({(0 if op=="add" else 3)+category});' if has_context else ''
        lines += [INLINE+f'GdVal native_numeric_{op}({params}const GdVal& a,const GdVal& b) {{',
            '    if(a.kind==GdVal::Kind::Int && b.kind==GdVal::Kind::Int) {']
        if op=='div':
            lines += [f'        if(b.i==0) {{ {count(0)} return GdVal::from_int(0); }}',
                '        if(!(a.i==std::numeric_limits<int64_t>::min() && b.i==-1)) {',
                f'            {count(0)} return GdVal::from_int(a.i/b.i);','        }']
        else:
            lines += ['#if defined(__GNUC__) || defined(__clang__)',
                '        int64_t result;',
                f'        if(!__builtin_{op}_overflow(a.i,b.i,&result)) {{',
                f'            {count(0)} return GdVal::from_int(result);','        }','#endif']
        lines += ['    } else if(a.is_num() && b.is_num() && native_numeric_is_finite(a) && native_numeric_is_finite(b)) {']
        if op=='div':
            lines += ['        const double divisor=b.as_float();',
                '        if((std::bit_cast<uint64_t>(divisor)&UINT64_C(0x7fffffffffffffff))!=0) {',
                f'            {count(1)} return GdVal::from_float(a.as_float()/divisor);','        }']
        else:
            lines += [f'        {count(1)} return GdVal::from_float(a.as_float(){sign}b.as_float());']
        lines += ['    }',f'    {count(2)}',f'    return native_numeric_original_{op}({args});','}','']
    return '\n'.join(lines)


def optimize(native):
    result=retained(native)
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    bodies={match[1]:match[0] for match in re.finditer(r'^GdVal gd_(add|sub|mul|div)\([^\n]*\n.*?^\}',runtime,re.M|re.S)}
    assert set(bodies)=={'add','sub','mul','div'}
    assert 'a.kind == GdVal::Kind::Int && b.kind == GdVal::Kind::Int' in bodies['add']
    assert 'if (b.i == 0) return GdVal::from_int(0);' in bodies['div']
    path=native/'native_inline_dispatch.hpp';header=path.read_text('utf8')
    header=replace(header,'#include <cstddef>','#include <cstddef>\n#include <bit>\n#include <limits>')
    anchor='void native_inline_typed_read_hit(unsigned);'
    header=replace(header,anchor,anchor+'\n'+helpers())
    path.write_text(header,encoding='utf8',newline='\n')
    counts={op:0 for op in bodies};sites={}
    for path in sorted((native/'gen/shards').glob('*.cpp')):
        source=path.read_text('utf8');local=dict.fromkeys(bodies,0)
        def rewrite(match):
            text=match[0]
            if not text.startswith('gd::gd_'):return text
            op=text.removeprefix('gd::gd_');local[op]+=1;counts[op]+=1
            return 'gd::native_numeric_'+op
        changed=TOKEN.sub(rewrite,source)
        path.write_text(changed,encoding='utf8',newline='\n');sites[path.name]=local
    assert all(count>0 for count in counts.values())
    path=native/'gen/sym_ids.cpp';source=path.read_text('utf8')
    assert 'native_numeric_original_' not in source and 'native_inline_dispatch.hpp' not in source
    source+='\nnamespace gd {\n'
    for op in bodies:
        params='BattleCtx& ctx,' if op in ('add','div') else ''
        args='ctx,a,b' if params else 'a,b'
        source+=f'GdVal native_numeric_original_{op}({params}const GdVal& a,const GdVal& b) {{return gd_{op}({args});}}\n'
    source+='}\n';path.write_text(source,encoding='utf8',newline='\n')
    path=native/'native_resolved_dispatch.hpp';source=path.read_text('utf8')
    marker='} // namespace gd';assert source.count(marker)==1
    source=source.replace(marker,'static thread_local uint64_t native_numeric_math_counts[6]{};\nvoid native_numeric_math_hit(unsigned index) {if(index<6)++native_numeric_math_counts[index];}\n'+marker,1)
    source+='\nextern "C" uint64_t gd_diag_native_numeric_stat(unsigned index) {return index<6 ? gd::native_numeric_math_counts[index] : 0;}\n'
    path.write_text(source,encoding='utf8',newline='\n')
    assert (native/'gd_rt.cpp').read_text('utf8')==runtime,'Original evaluators are independent oracles'
    result.update(status='implemented_uncompiled_unmeasured',
        components=result['components']+['inlined safe integer and finite real arithmetic branches','non-LTO original arithmetic fallback'],
        retained_candidate='c0649c77ebaaa9a8d077b01af69cf5ff8fa3ff8aff0b26fda3a794c667117bd7',
        numeric_call_sites=counts,numeric_sites_by_shard=sites,
        original_arithmetic_body_sha256={name:hashlib.sha256(body.encode()).hexdigest() for name,body in bodies.items()},
        arithmetic_argument_signatures_unchanged=True,
        arithmetic_fallbacks='Overflow, nonfinite reals, zero real divisors and every nonnumeric case use the original evaluator through non-LTO wrappers.',
        integer_division_overflow='INT64_MIN/-1 remains on the original path; it is not newly evaluated.',
        numeric_diagnostic_scope='Add and divide count under the existing context diagnostic flag; subtract and multiply add no unconditional counter or TLS load.',
        floating_operations='Same individual binary operation and numeric conversion as the original branch; contraction flags unchanged.')
    return result
