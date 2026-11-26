"""Extend only original pure identity cases and conservative container comparisons."""
import hashlib
import json
from pathlib import Path
import shutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/container_builtins_bundle'
WORK=STAGE/'native_perf50/identity_lookup_prototype'
EXPECTED='5bd31fdc2ab2e4a556c63987de62b9541d5793752d67662cc4034a36bdd69ecc'
ARCHIVE='49128c4b04ca42003211f81fff5c3d6b616376b2'
HEADER='native_scalar_equal.hpp'
IDENTITY='''            // 与原gd_eq相同的纯身份分支，不读取对象内容或触发回调。
            case GdVal::Kind::Obj:return a.obj==b.obj;
            case GdVal::Kind::Dict:return a.dict==b.dict;
            case GdVal::Kind::ClassRef:return a.cls==b.cls;
            case GdVal::Kind::Enum:return a.en==b.en;
            case GdVal::Kind::FuncRef:return a.fr==b.fr;
            case GdVal::Kind::Rng:return a.rng==b.rng;
            case GdVal::Kind::Str:if(a.str==b.str)return true;break;
            case GdVal::Kind::Arr:if(a.arr==b.arr)return true;break;
'''
LOOKUP='''// 容器Float查找仍调用原比较体；保持其浮点异常和混合数值语义。
inline bool native_lookup_eq(const GdVal& a,const GdVal& b) {
    if(a.kind==GdVal::Kind::Float || b.kind==GdVal::Kind::Float)return gd::gd_eq(a,b);
    return native_scalar_eq(a,b);
}
'''
INCLUDE='#include "native_scalar_equal.hpp"\n'
FUNCTIONS=[('int64_t GdArr::find_val(', '\nvoid GdArr::resize('),
    ('int64_t GdArr::count_val(', '\nGdArr* GdArr::duplicate('),
    ('int32_t GdDict::find_index(', '\nGdVal GdDict::get(')]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def inventory(native):
    return {p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()
        and '__pycache__' not in p.parts and p.suffix not in ('.dll','.o','.gcda','.gcno','.pyc')}
def archive():
    r=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert r['remote_upload_verified'] and r['remote_verified_commit']==ARCHIVE and r['production_dll_sha256']==EXPECTED
    return ARCHIVE
def replace_functions(t,old,new):
    total=0
    for begin,end in FUNCTIONS:
        assert t.count(begin)==t.count(end)==1
        i=t.index(begin);j=t.index(end,i);s=t[i:j];count=s.count(old)
        assert count in (1,3),(begin,count);total+=count
        t=t[:i]+s.replace(old,new)+t[j:]
    assert total==5,total
    return t
def transform(native):
    assert inventory(native)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    p=native/HEADER;t=p.read_text('utf8');assert t.count('            default:break;')==1
    t=t.replace('            default:break;',IDENTITY+'            default:break;',1)
    assert t.count('} // namespace gd')==1;t=t.replace('} // namespace gd',LOOKUP+'} // namespace gd',1)
    p.write_text(t,encoding='utf8',newline='\n')
    p=native/'gd_rt.cpp';t=p.read_text('utf8');assert t.count('#include "gd_rt.hpp"\n')==1
    t=t.replace('#include "gd_rt.hpp"\n','#include "gd_rt.hpp"\n'+INCLUDE,1)
    t=replace_functions(t,'gd_eq(','native_lookup_eq(');p.write_text(t,encoding='utf8',newline='\n')
    return dict(extended_original_same_kind_identity_cases=True,existing_scalar_cases_retained=True,
        array_search_and_count_sites=2,dictionary_find_sites=3,hash_gating_and_loop_order_unchanged=True,
        float_lookup_and_all_complex_comparisons_retain_original_fallback=True,
        no_color_or_vec2_pointer_shortcut=True,no_new_api_or_layout=True,all_previous_components_retained=True)
def verify_projection(native):
    frozen=json.loads((WORK/'transform.json').read_bytes());assert inventory(native)==frozen['source_sha256']
    old=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    for name,digest in old.items():
        t=None
        if name==HEADER:
            t=(native/name).read_text('utf8');assert t.count(IDENTITY)==t.count(LOOKUP)==1
            t=t.replace(IDENTITY,'',1).replace(LOOKUP,'',1)
        elif name=='gd_rt.cpp':
            t=(native/name).read_text('utf8');assert t.count(INCLUDE)==1
            t=replace_functions(t.replace(INCLUDE,'',1),'native_lookup_eq(','gd_eq(')
        if t is None:assert sha(native/name)==digest,name
        else:assert hashlib.sha256(t.encode()).hexdigest()==digest,name
    return dict(passed=True,exact_inverse_matches_retained_source=True,changed_source_files=[HEADER,'gd_rt.cpp'],
        all674_object_headers_and_all_layouts_unchanged=True,all_existing_scalar_frame_and_container_optimizations_retained=True,
        original_gd_eq_and_generic_call_method_bodies_unchanged=True,full20_formal_build_required=True)
def main():
    archive();assert sha(BASE/'libgdcore.dll')==EXPECTED and not WORK.exists()
    old=json.loads((ACCEPTED/'source_before_build.json').read_bytes());assert inventory(BASE)==old and len(old)==713
    WORK.mkdir();source=WORK/'prototype_src';shutil.copytree(ACCEPTED/'bundle_src',source)
    component=transform(source);after=inventory(source)
    assert sorted(n for n in old if old[n]!=after[n])==['gd_rt.cpp',HEADER] and set(old)==set(after)
    result=dict(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,source_sha256=after,component=component,
        modified_files=['gd_rt.cpp',HEADER],new_files=[],baseline_cpp_source_files=708,candidate_cpp_source_files=708,
        no_layout_change=True,no_new_branches=True,no_speed_claim=True,not_for_deployment=True)
    (WORK/'transform.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(verify_projection(source)),flush=True)

if __name__=='__main__':main()
