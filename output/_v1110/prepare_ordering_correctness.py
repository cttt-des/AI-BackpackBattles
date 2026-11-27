"""Freeze the backed-up production and prepare only the two confirmed fixes."""
import ast,hashlib,io,json,subprocess,shutil
from pathlib import Path
STAGE=Path(__file__).resolve().parent
REPO=STAGE.parents[1]
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/assembly_membership_bundle'
WORK=STAGE/'native_perf50/ordering_correctness_bundle'
EXPECTED='291d58514d69e9bdf8eb30b875a133bcfa7d8a2af357d95fb92773c9ebff851d'
ARCHIVE='8bf07f634452eeaa947258d263b27ac1a29b9823'
REF='refs/heads/codex/native-perf50-verified'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def save(name,value):(WORK/name).write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
def once(t,a,b):assert t.count(a)==1,(a[:120],t.count(a));return t.replace(a,b,1)
def inventory(root):return {p.relative_to(root).as_posix():sha(p) for p in root.rglob('*') if p.is_file() and '__pycache__' not in p.parts and p.suffix not in ('.dll','.o','.gcda','.gcno','.pyc')}

def verify_projection(source):
    """Invert only the reviewed fixes, retaining all prior optimizations."""
    actual=inventory(source);expected=json.loads((WORK/'source_before_build.json').read_bytes())
    assert actual==expected
    old=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert set(actual)-set(old)=={'native_godot_sort.hpp'}
    for name,h in old.items():
        if name not in ('gd_rt.cpp','gen/shards/shard_12.cpp'):assert actual[name]==h,name
    text=(source/'gen/shards/shard_12.cpp').read_text('utf8')
    a='for (uint32_t _t1646 = 0; _t1645 && _t1646 < _t1645->len; ++_t1646) {';b='for (uint32_t _t1646 = 0; _t1646 < _len__t1646; ++_t1646) {'
    assert text.count(a)==3 and text.replace(a,b)==(ACCEPTED/'bundle_src/gen/shards/shard_12.cpp').read_text('utf8')
    text=(source/'gd_rt.cpp').read_text('utf8');baseline=(ACCEPTED/'bundle_src/gd_rt.cpp').read_text('utf8')
    start=text.index('// Preserve this exported symbol for existing callers;');end=text.index('\n}\n',start)+2
    old_start=baseline.index('void sort_custom_stable(');old_end=baseline.index('\n}\n',old_start)+2
    inverse=(text[:start]+baseline[old_start:old_end]+text[end:]).replace('#include "native_godot_sort.hpp"\n','',1)
    assert inverse==baseline
    return dict(passed=True,exact_inverse_matches_retained_source=True,all674_object_headers_and_all_layouts_unchanged=True,full_original_bodies_retained_except_declared_correctness_fixes=True,all_prior_optimizations_retained=True,semantic_changes_declared=True)

def main():
    assert not WORK.exists();WORK.mkdir()
    backup=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes());assert backup['remote_verified_commit']==ARCHIVE and backup['remote_upload_verified']
    assert subprocess.check_output(['git','ls-remote','--exit-code','https://github.com/cttt-des/AI-BackpackBattles.git',REF],cwd=REPO,text=True,timeout=30).split()[0]==ARCHIVE
    assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    before=json.loads((ACCEPTED/'source_before_build.json').read_bytes());assert before==inventory(BASE)
    names=[p.relative_to(REPO).as_posix() for p in [*(BASE/n for n in before),BASE/'libgdcore.dll']]
    stream=io.BytesIO(subprocess.check_output(['git','cat-file','--batch'],cwd=REPO,input=''.join(f'{ARCHIVE}:{n}\n' for n in names).encode('utf8')))
    for name in names:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob';assert stream.read(int(header[2]))==(REPO/name).read_bytes(),name;assert stream.read(1)==b'\n'
    boundary=json.loads((STAGE/'same_frame_potion_audit_20261127/workspace_before.json').read_bytes())
    assert all(sha(REPO/n)==h for n,h in boundary['protected'].items())
    boundary['staged_entries_sha256']=hashlib.sha256(subprocess.check_output(['git','ls-files','--stage','-z'],cwd=REPO)).hexdigest()
    save('user_boundary_before.json',boundary);save('baseline_verified.json',dict(archive_commit=ARCHIVE,dll_sha256=EXPECTED,source_sha256=before))
    src=WORK/'bundle_src';shutil.copytree(ACCEPTED/'bundle_src',src)
    # Keep Godot's MIT notice and sorting algorithm; adapt only header plumbing.
    upstream=STAGE/'godot_3_6_sources/godot-3.6-stable/core/sort_array.h'
    h=upstream.read_text('utf8')
    h=h.replace('SORT_ARRAY_H','GD_NATIVE_GODOT36_SORT_HPP')
    h=once(h,'#include "core/error_macros.h"\n#include "core/typedefs.h"','#include <utility>\n\nnamespace gd::godot36 {')
    start=h.index('#define ERR_BAD_COMPARE');end=h.index('\ntemplate <class T>',start)
    h=h[:start]+'#define GD_SORT_BAD_COMPARE(cond) if (cond) { break; }\n'+h[end:]
    start=h.index('#ifdef DEBUG_ENABLED');end=h.index('\ntemplate <class T, class Comparator',start)
    h=h[:start]+h[end:]
    h=h.replace('Validate = SORT_ARRAY_VALIDATE_ENABLED','Validate = false').replace('_FORCE_INLINE_','inline').replace('ERR_BAD_COMPARE(','GD_SORT_BAD_COMPARE(').replace('SWAP(','std::swap(')
    h=once(h,'#endif // GD_NATIVE_GODOT36_SORT_HPP','} // namespace gd::godot36\n#undef GD_SORT_BAD_COMPARE\n#endif // GD_NATIVE_GODOT36_SORT_HPP')
    (src/'native_godot_sort.hpp').write_text(h,encoding='utf8',newline='\n')
    rt=src/'gd_rt.cpp';original=rt.read_text('utf8');text=once(original,'#include "gd_rt.hpp"','#include "gd_rt.hpp"\n#include "native_godot_sort.hpp"')
    start=text.index('void sort_custom_stable(');end=text.index('\n}\n',start)+2
    old=text[start:end]
    new='''// Preserve this exported symbol for existing callers; its behavior is now
// Godot 3.6 SortArray, including equal-key order and comparator call sequence.
void sort_custom_stable(BattleCtx& ctx, GdArr* arr, GdObj* obj, SymId method) {
    NativeTimerMutation native_mutation(arr?arr->timer_watch:nullptr);
    if (!arr || arr->len < 2 || !obj) return;
    struct CustomComparator {
        BattleCtx* ctx;
        GdObj* obj;
        SymId method;
        bool operator()(const GdVal& a, const GdVal& b) const {
            GdVal args[2] = {a, b};
            GdVal out = GdVal::null();
            native_timer_observe_object(*ctx,obj);
            obj->call_method(*ctx, method, args, 2, out);
            return gd_truth(out);
        }
    };
    godot36::SortArray<GdVal, CustomComparator> sorter;
    sorter.compare = {&ctx,obj,method};
    sorter.sort(arr->data,static_cast<int>(arr->len));
}'''
    text=text[:start]+new+text[end:];rt.write_text(text,encoding='utf8',newline='\n')
    shard=src/'gen/shards/shard_12.cpp';text=shard.read_text('utf8')
    start=text.index('gd::GdVal Gd__gd_core__CoreEventBus::fn_emitAndLog(');end=text.index('\n}\n',start)+2
    body=text[start:end];anchor='for (uint32_t _t1646 = 0; _t1646 < _len__t1646; ++_t1646) {'
    assert body.count(anchor)==2
    body=body.replace(anchor,'for (uint32_t _t1646 = 0; _t1645 && _t1646 < _t1645->len; ++_t1646) {')
    text=text[:start]+body+text[end:];shard.write_text(text,encoding='utf8',newline='\n')
    # A scoped compiler contract prevents regeneration from restoring the bug.
    gen=STAGE/'sim_native/native_sim_cpp/tools/gd_to_cpp.py';gt=gen.read_text('utf8')
    anchor='                lines.append(f"{ind}    for (uint32_t {idx_t} = 0; {idx_t} < _len_{idx_t}; ++{idx_t}) {{")'
    replacement='''                # EventBus callbacks may grow or shrink the current listener
                # array. Godot Variant::iter_next reads its current size.
                # Other loop contracts are audited separately, not changed here.
                live_listeners = (ci.res_path == "res://gd_core/CoreEventBus.gd"
                                  and isinstance(st.seq, IdentExpr) and st.seq.name == "_bus_list")
                if live_listeners:
                    lines.append(f"{ind}    for (uint32_t {idx_t} = 0; {arr_t} && {idx_t} < {arr_t}->len; ++{idx_t}) {{")
                else:
                    lines.append(f"{ind}    for (uint32_t {idx_t} = 0; {idx_t} < _len_{idx_t}; ++{idx_t}) {{")'''
    gt=once(gt,anchor,replacement);ast.parse(gt)
    (WORK/'gd_to_cpp_pending.py').write_text(gt,encoding='utf8',newline='\n')
    shutil.copyfile(gen,WORK/'gd_to_cpp_before.py')
    after=inventory(src);changed=[n for n in before if before[n]!=after[n]];added=sorted(set(after)-set(before))
    assert changed==['gd_rt.cpp','gen/shards/shard_12.cpp'] and added==['native_godot_sort.hpp'],(changed,added)
    assert all(after[n]==h for n,h in before.items() if n.startswith('gen/hdrs/'))
    save('transform.json',dict(baseline_dll_sha256=EXPECTED,source_sha256=after,modified_files=changed,new_files=added,no_layout_changes=True,all674_object_headers_unchanged=True,sorting_upstream_sha256=sha(upstream),generator_before_sha256=sha(gen),generator_after_sha256=sha(WORK/'gd_to_cpp_pending.py'),intentional_semantic_changes=['Godot SortArray equal-key and callback sequence','EventBus current listener array length'],old_optimization_components_retained=True,not_a_new_performance_optimization=True))
    save('source_before_build.json',after)
    print(json.dumps(dict(prepared=True,source_files=len(after),changed=changed,added=added,production_unchanged=True,no_new_branches=True)))

if __name__=='__main__':main()
