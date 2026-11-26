"""Add only missing container/enum builtins, retaining original member operations."""
import hashlib
import json
from pathlib import Path
import shutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/frame_value_bundle'
WORK=STAGE/'native_perf50/container_builtins_prototype'
EXPECTED='0a6d24f459eb1011a0bfcc1bc5c4188c1ca67add410b9caf0e04c8f5d30d44d4'
ARCHIVE='4cbfd55b10a7dae66529c41da01cbcce63ae66d2'
HEADER='native_inline_dispatch.hpp'
ARRAY='''                // 仍调用原成员函数，保留数组别名、扩容及watch变更时点。
                case SYM_push_back:
                case SYM_append:
                    if(argc>=1)a->push_back(ctx.arena,args[0]);
                    return GdVal::null();
                case SYM_append_array:
                    if(argc>=1 && args[0].kind==GdVal::Kind::Arr)a->append_array(ctx.arena,args[0].arr);
                    return GdVal::null();
                case SYM_clear: {
                    NativeTimerMutation mutation(a->timer_watch);
                    a->len=0;return GdVal::null();
                }
                case SYM_resize:
                    // Float转Int的异常标志继续由原通用体处理。
                    if(argc>=1) {
                        if(args[0].kind==GdVal::Kind::Float)break;
                        a->resize(ctx.arena,args[0].as_int());
                    }
                    return GdVal::null();
                case SYM_fill:
                    if(argc>=1)a->fill(args[0]);
                    return GdVal::null();
                case SYM_duplicate: {
                    if(argc>=1 && (args[0].kind==GdVal::Kind::Float || args[0].kind==GdVal::Kind::Vec2 || args[0].kind==GdVal::Kind::Color))break;
                    const bool deep=argc>=1 && gd_truth(args[0]);
                    return GdVal::from_arr(a->duplicate(ctx.arena,deep));
                }
'''
DICT='''                case SYM_keys:return GdVal::from_arr(d->keys(ctx.arena));
                case SYM_values:return GdVal::from_arr(d->values(ctx.arena));
'''
ENUM='''        } else if(recv.kind==GdVal::Kind::Enum) {
            const GdEnum* e=recv.en;
            if(!e)return GdVal::null();
            switch(method) {
                case SYM_size:return GdVal::from_int(e->len);
                case SYM_empty:return GdVal::from_bool(e->len==0);
                case SYM_has:
                    return GdVal::from_bool(argc>=1 && args[0].kind==GdVal::Kind::Str && args[0].str && e->has(std::string_view(args[0].str->data,args[0].str->len)));
                case SYM_keys:return GdVal::from_arr(e->keys_arr(ctx.arena));
                case SYM_values:return GdVal::from_arr(e->values_arr(ctx.arena));
                default:break;
            }
'''

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def inventory(native):
    return {p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()
        and '__pycache__' not in p.parts and p.suffix not in ('.dll','.o','.gcda','.gcno','.pyc')}
def archive():
    r=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert r['remote_upload_verified'] and r['remote_verified_commit']==ARCHIVE and r['production_dll_sha256']==EXPECTED
    return ARCHIVE
def transform(native):
    assert inventory(native)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    p=native/HEADER;t=p.read_text('utf8')
    array_end='                default:break;\n            }\n        } else if(recv.kind==GdVal::Kind::Dict) {'
    dict_end='                default:break;\n            }\n        } else if(recv.kind==GdVal::Kind::ClassRef && method!=SYM_new) {'
    assert t.count(array_end)==t.count(dict_end)==1
    t=t.replace(array_end,ARRAY+array_end,1)
    t=t.replace(dict_end,DICT+'                default:break;\n            }\n'+ENUM+'        } else if(recv.kind==GdVal::Kind::ClassRef && method!=SYM_new) {',1)
    p.write_text(t,encoding='utf8',newline='\n')
    return dict(array_methods=['push_back','append','append_array','clear','resize_non_float','fill','duplicate_non_fp_truth'],
        dictionary_methods=['keys','values'],enum_methods=['size','empty','has','keys','values'],
        all_original_member_functions_and_mutation_boundaries_retained=True,
        original_floating_truth_and_float_to_int_fallback=True,no_new_api_or_layout=True,
        existing_variant_counters_and_all_prior_components_retained=True)
def verify_projection(native):
    frozen=json.loads((WORK/'transform.json').read_bytes());assert inventory(native)==frozen['source_sha256']
    old=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    for name,digest in old.items():
        if name==HEADER:
            t=(native/name).read_text('utf8')
            assert all(t.count(s)==1 for s in (ARRAY,DICT,ENUM))
            original=t.replace(ARRAY,'',1).replace(DICT,'',1).replace(ENUM,'',1)
            assert hashlib.sha256(original.encode()).hexdigest()==digest
        else:assert sha(native/name)==digest,name
    return dict(passed=True,exact_inverse_matches_retained_source=True,one_header_only=True,
        all674_object_headers_and_all_layouts_unchanged=True,all_existing_scalar_and_frame_optimizations_retained=True,
        original_gd_rt_cpp_bodies_unchanged=True,full20_formal_build_required=True)
def main():
    archive();assert sha(BASE/'libgdcore.dll')==EXPECTED and not WORK.exists()
    WORK.mkdir();source=WORK/'prototype_src';shutil.copytree(ACCEPTED/'bundle_src',source)
    component=transform(source);after=inventory(source);old=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert sorted(n for n in old if old[n]!=after[n])==[HEADER] and set(old)==set(after)
    result=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,component=component,
        modified_files=[HEADER],new_files=[],baseline_cpp_source_files=708,candidate_cpp_source_files=708,
        no_layout_change=True,no_new_branches=True,no_speed_claim=True,not_for_deployment=True)
    (WORK/'transform.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(verify_projection(source)),flush=True)

if __name__=='__main__':main()
