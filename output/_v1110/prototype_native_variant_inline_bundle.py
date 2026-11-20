"""Inline original pure container queries and single static-ClassRef dispatch."""
import hashlib
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
PREVIOUS=STAGE/'native_perf50/inline_dispatch_bundle'

LANES='''    if(ctx.native_resolved_dispatch) {
        if(recv.kind==GdVal::Kind::Arr) {
            GdArr* a=recv.arr;
            if(!a)return GdVal::null();
            switch(method) {
                case SYM_size:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(0);
                    return GdVal::from_int(a->len);
                case SYM_empty:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(1);
                    return GdVal::from_bool(a->len == 0);
                case SYM_has:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(2);
                    return GdVal::from_bool(argc >= 1 && a->has_val(args[0]));
                case SYM_front:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(3);
                    return a->len > 0 ? a->data[0] : GdVal::null();
                case SYM_back:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(4);
                    return a->len > 0 ? a->data[a->len - 1] : GdVal::null();
                default:break;
            }
        } else if(recv.kind==GdVal::Kind::Dict) {
            GdDict* d=recv.dict;
            if(!d)return GdVal::null();
            switch(method) {
                case SYM_size:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(5);
                    return GdVal::from_int(d->len);
                case SYM_empty:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(6);
                    return GdVal::from_bool(d->len == 0);
                case SYM_has:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(7);
                    return GdVal::from_bool(argc >= 1 && d->has(args[0]));
                case SYM_get:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(8);
                    return argc >= 1 ? d->get(args[0], argc >= 2 ? args[1] : GdVal::null()) : GdVal::null();
                default:break;
            }
        } else if(recv.kind==GdVal::Kind::ClassRef && method!=SYM_new) {
            if(ctx.native_resolved_collect)native_inline_variant_hit(9);
            if(recv.cls && recv.cls->call_static_fn) {
                GdVal out=GdVal::null();
                if(recv.cls->call_static_fn(ctx,method,args,argc,out))return out;
            }
            // A false callback is already executed; the original returns Null.
            return GdVal::null();
        }
    }
'''

def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def optimize(native):
    expected=json.loads((PREVIOUS/'source_before_build.json').read_bytes())
    actual={p.relative_to(native).as_posix():digest(p) for p in native.rglob('*') if p.is_file()}
    assert actual==expected,'Start with all accepted source/config bytes'
    path=native/'gd_rt.cpp';runtime=path.read_text('utf8')
    originals=[
        'case SYM_size: return GdVal::from_int(a->len);',
        'case SYM_empty: return GdVal::from_bool(a->len == 0);',
        'case SYM_has: return GdVal::from_bool(argc >= 1 && a->has_val(args[0]));',
        'case SYM_front: return a->len > 0 ? a->data[0] : GdVal::null();',
        'case SYM_back: return a->len > 0 ? a->data[a->len - 1] : GdVal::null();',
        'case SYM_size: return GdVal::from_int(d->len);',
        'case SYM_empty: return GdVal::from_bool(d->len == 0);',
        'case SYM_has: return GdVal::from_bool(argc >= 1 && d->has(args[0]));',
        'return argc >= 1 ? d->get(args[0], argc >= 2 ? args[1] : GdVal::null()) : GdVal::null();',
        'if (recv.cls->call_static_fn(ctx, m, args, argc, out)) return out;']
    assert all(runtime.count(x)==1 for x in originals),'Original branch changed; re-review the copied behavior'
    runtime+='''
namespace gd {
static thread_local uint64_t native_inline_variant_counts[10]{};
void native_inline_variant_hit(unsigned field) {
    if(field<10)++native_inline_variant_counts[field];
}
}
extern "C" uint64_t gd_diag_native_variant_stat(unsigned field) {
    return field<10?gd::native_inline_variant_counts[field]:0;
}
'''
    path.write_text(runtime,encoding='utf8',newline='\n')
    path=native/'native_inline_dispatch.hpp';text=path.read_text('utf8')
    anchor='bool native_resolved_row_matches(const GdObj*,const NativeMethodRow*);'
    assert text.count(anchor)==1
    text=text.replace(anchor,anchor+'\nvoid native_inline_variant_hit(unsigned);',1)
    anchor='    // No virtual/user call has happened yet; fallback performs it exactly once.'
    assert text.count(anchor)==1
    text=text.replace(anchor,LANES+anchor,1)
    path.write_text(text,encoding='utf8',newline='\n')
    report={'baseline_dll_sha256':'1be75dced83e9e90fdbe61dd86f91bc27e19bb44acf9449d295849e928d9cec5',
        'container_lanes':{'array':['size','empty','has','front','back'],'dictionary':['size','empty','has','get']},
        'static_lane':'ClassRef non-new: call original static function once; false/null callback returns original Null, never a second fallback',
        'preserved':['null receivers','argument counts/defaults','object user methods before builtins','new constructor path','native flag disabled path','original bodies/binds/math/RNG/order'],
        'object_and_context_layout_changed':False,'full_rebuild_required':True,
        'diagnostic_counts':['array_size','array_empty','array_has','array_front','array_back','dict_size','dict_empty','dict_has','dict_get','class_lane'],
        'diagnostic_overhead':'Out-of-line TLS hit only with existing native_resolved_collect; performance collection disabled',
        'original_branch_guards':originals}
    print('Added nine pure container query cases and one single-callback static lane; no layout changes',flush=True)
    return report
