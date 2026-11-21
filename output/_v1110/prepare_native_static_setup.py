"""Prepare source-proved TLS-free constants and ordered fixed-table setup."""
import hashlib
import json
from pathlib import Path
import re

STAGE = Path(__file__).resolve().parent
BASE = STAGE / 'sim_native/native_sim_cpp/native_sim'
WORK = STAGE / 'native_perf50/static_setup_probe'
EXPECTED = '541238b57e2e18ce258a0afa9f548115761da28f4a1c119812277b4c0dae2983'

def body(text, signature):
    start = text.index(signature)
    return text[start:text.index('\n}', start) + 2]

def analyze(native):
    classes = []
    # Only literal value constructors and addresses of immutable generated metadata.
    number = r'-?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?(?:LL)?'
    pure = re.compile(r'gd::GdVal::(?:from_enum\(&_enum_\w+\)|from_cls\(&META_\w+\)|from_int\(-?\d+LL\)|from_bool\((?:true|false)\)|from_float\(' + number + r'\)|from_vec2\(' + number + r', ' + number + r'\))')
    for path in sorted((native / 'gen/shards').glob('shard_*.cpp')):
        text = path.read_text('utf8')
        for name in re.findall(r'gd::GdVal (Gd__\w+)::get_static_const_or_enum\(', text):
            const = body(text, f'gd::GdVal {name}::get_static_const_or_enum(')
            getter = body(text, f'bool {name}::get_static_prop_fn(')
            assert getter.startswith(f'bool {name}::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {{\n    static thread_local gd::BattleCtx s_const_ctx(1u << 16);')
            cases = re.findall(r'^        case (SYM_GEN_\w+): return (.*);$', const, re.M)
            fast = [(symbol, expr) for symbol, expr in cases if pure.fullmatch(expr)]
            classes.append(dict(name=name, shard=path.name, cases=cases, fast=fast, original=getter))
    assert len(classes) == 674
    constants = (native / 'gen/shards/shard_06.cpp').read_text('utf8')
    from prepare_native_static_collections import transformed
    transformed(native)  # Proves the original getStacks/getBuffs/getDebuffs bodies and binding.
    for name, count in [('ItemMetrics', 20), ('StackChangeType', 6), ('Affected', 4)]:
        assert re.search(r'static const gd::GdEnum _enum_Gd__gd_core__CoreConst_' + name + r' = \{"' + name + r'", _ekv_Gd__gd_core__CoreConst_' + name + ', ' + str(count) + r'u\};', constants)
    affected_members = re.search(r'static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_Affected\[\] = \{(.*?)\};', constants)
    assert affected_members and re.findall(r'\{"([^"]+)", (-?\d+)LL\}', affected_members[1]) == [('Primary','0'),('Secondary','1'),('Tertiary','2'),('Lightning','3')]
    text = (native / 'gen/shards/shard_00.cpp').read_text('utf8')
    setup = body(text, 'gd::GdVal Gd__gd_core__CoreItem::fn_setup(')
    stack_start = setup.index('    {\n        gd::GdVal _t4 = ')
    stack_end = setup.index('\n    (void)', stack_start)
    stack_block = setup[stack_start:stack_end]
    expected = '''    {
        gd::GdVal _t4 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getStacks_1023, nullptr, 0));
        gd::GdArr* _t5 = (_t4.kind == gd::GdVal::Kind::Arr) ? _t4.arr : nullptr;
        uint32_t _len__t6 = _t5 ? _t5->len : 0u;
        for (uint32_t _t6 = 0; _t6 < _len__t6; ++_t6) {
            gd::GdVal lv_buff = _t5->data[_t6];
            { gd::GdVal _t7 = this->f_buffPowers; gd::GdVal _t8 = lv_buff; gd::native_array_set_index(gd_ctx, _t7, _t8, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t9 = this->f_buffAmplificationChances; gd::GdVal _t10 = lv_buff; gd::native_array_set_index(gd_ctx, _t9, _t10, gd::GdVal::from_float(0.0)); }
        }
    }'''
    assert stack_block == expected
    replacement = '''    if (gd_ctx.native_resolved_dispatch) {
        if (!gd::native_setup_empty_stack_tables(gd_ctx, this->f_buffPowers, this->f_buffAmplificationChances)) {
            if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(1);
            for (int64_t stack = 100; stack <= 110; ++stack) {
                gd::GdVal lv_buff = gd::GdVal::from_int(stack);
                { gd::GdVal target = this->f_buffPowers; gd::native_array_set_index(gd_ctx, target, lv_buff, gd::GdVal::from_float(1.0)); }
                { gd::GdVal target = this->f_buffAmplificationChances; gd::native_array_set_index(gd_ctx, target, lv_buff, gd::GdVal::from_float(0.0)); }
            }
        }
    } else ''' + stack_block.lstrip()
    new_setup = setup.replace(stack_block, replacement, 1)
    affected_start = setup.index('    {\n        gd::GdVal _t11 = ')
    affected_end = setup.index('\n    return gd::GdVal::from_obj(this);', affected_start)
    affected = setup[affected_start:affected_end]
    assert affected.count('SYM_GEN_Affected_867') == 1 and affected.count('native_array_set_index') == 1
    assignment = '            { gd::GdVal _t14 = this->f_currentAffectedItems; gd::GdVal _t15 = lv_color; gd::native_array_set_index(gd_ctx, _t14, _t15, gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))); }'
    assert assignment in affected
    new_affected = '''    if (gd_ctx.native_resolved_dispatch) {
        if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(3);
        for (int64_t color = 0; color < 4; ++color) {
            gd::GdVal lv_color = gd::GdVal::from_int(color);
''' + assignment + '''
        }
    } else ''' + affected.lstrip()
    new_setup = new_setup.replace(affected, new_affected, 1)
    metrics = {}
    for name, value in [('getNumNonStackItemMetrics', 14), ('getNumItemMetrics', 80)]:
        old = body(text, f'gd::GdVal Gd__gd_core__CoreItem::sf_{name}(')
        assert len(old.splitlines()) == 4 and old.count('SYM_GEN_StackChangeType_871') == 1
        if name == 'getNumNonStackItemMetrics':
            assert 'gd::GdVal::from_int(9LL)' in old and 'gd::GdVal::from_int(8LL)' in old
        else:
            assert 'SYM_GEN_ItemMetrics_1396' in old
        new = old.replace('{\n', '{\n    if (gd_ctx.native_resolved_dispatch) { if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(2); return gd::GdVal::from_int(' + str(value) + 'LL); }\n', 1)
        metrics[name] = (old, new)
    return classes, setup, new_setup, metrics

def helper():
    return '''#pragma once
#include "gd_rt.hpp"
namespace gd {
void native_static_setup_hit(unsigned);
inline bool native_setup_empty_stack_tables(BattleCtx& ctx, const GdVal& powers, const GdVal& chances) {
    if (powers.kind != GdVal::Kind::Dict || chances.kind != GdVal::Kind::Dict || !powers.dict || !chances.dict || powers.dict == chances.dict) return false;
    auto* a = powers.dict; auto* b = chances.dict;
    if (a->len || a->cap || a->entries || a->buckets || a->bucket_cap || b->len || b->cap || b->entries || b->buckets || b->bucket_cap) return false;
    a->entries = ctx.arena.alloc_array<GdDictEntry>(16); a->cap = 16;
    b->entries = ctx.arena.alloc_array<GdDictEntry>(16); b->cap = 16;
    a->buckets = ctx.arena.alloc_array<int32_t>(32); a->bucket_cap = 32;
    b->buckets = ctx.arena.alloc_array<int32_t>(32); b->bucket_cap = 32;
    std::memset(a->buckets, -1, 32 * sizeof(int32_t));
    std::memset(b->buckets, -1, 32 * sizeof(int32_t));
    for (uint32_t i = 0; i < 11; ++i) {
        const auto key = GdVal::from_int(100 + i); const auto hash = gd_val_hash(key);
        a->entries[i] = {key, GdVal::from_float(1.0), hash}; ++a->len;
        b->entries[i] = {key, GdVal::from_float(0.0), hash}; ++b->len;
        uint32_t position = uint32_t(hash) & 31;
        while (a->buckets[position] >= 0) position = (position + 1) & 31;
        a->buckets[position] = b->buckets[position] = int32_t(i);
    }
    if (ctx.native_resolved_collect) native_static_setup_hit(0);
    return true;
}
}
'''

def main():
    assert hashlib.sha256((BASE / 'libgdcore.dll').read_bytes()).hexdigest() == EXPECTED
    WORK.mkdir(exist_ok=True)
    classes, original, setup, metrics = analyze(BASE)
    (WORK / 'static_setup_helper.hpp').write_text(helper(), encoding='utf8', newline='\n')
    includes = {'Gd__gd_core__CoreItem', 'Gd__gd_core__CoreConst', 'Gd__gd_core__CoreContext', 'Gd__gd_core__CoreRng', 'Gd__gd_core__CoreItemData'} | {row['name'] for row in classes if row['fast']}
    header = '#pragma once\n#include "native_event_kernel.hpp"\n#include "native_array_index.hpp"\n#include "static_setup_helper.hpp"\n'
    header += ''.join(f'#include "gen/hdrs/{name}.hpp"\n' for name in sorted(includes))
    header += 'struct StaticCase {const gd::GdClassMeta* meta; gd::SymId prop; bool (*candidate)(gd::BattleCtx&,gd::SymId,gd::GdVal&); bool fast;};\n'
    for row in classes:
        if not row['fast']: continue
        name = row['name']
        header += f'inline bool candidate_{name}(gd::BattleCtx& scratch,gd::SymId prop,gd::GdVal& out) {{\n    switch(prop) {{\n'
        header += ''.join(f'    case {symbol}: out = {name}::get_static_const_or_enum(scratch,prop); return true;\n' for symbol, _ in row['fast'])
        header += f'    default: return {name}::get_static_prop_fn(prop,out);\n    }}\n}}\n'
    header += 'inline std::vector<StaticCase> static_cases(){return {\n'
    for row in classes:
        fn = f'candidate_{row["name"]}' if row['fast'] else 'nullptr'
        known_fast = {symbol for symbol, _ in row['fast']}
        for symbol, _ in row['cases']:
            header += f'{{&META_{row["name"]},{symbol},{fn},{str(symbol in known_fast).lower()}}},\n'
        for symbol in ('gd::SymId(0)', 'gd::SymId(0xffffffffu)'):
            header += f'{{&META_{row["name"]},{symbol},{fn},false}},\n'
    header += '};}\n'
    setup = setup.replace('Gd__gd_core__CoreItem::fn_setup(const', 'candidate_setup(Gd__gd_core__CoreItem& item,const').replace('this->', 'item.')
    setup = setup.replace('gd::GdVal::from_obj(this)', 'gd::GdVal::from_obj(&item)')
    header += 'inline ' + setup + '\n'
    # Isolate the original setup block for a local cost screen; whole setup
    # correctness below is checked independently against the deployed DLL.
    old_block = original[original.index('    {\n        gd::GdVal _t4 = '):original.index('\n    (void)', original.index('    {\n        gd::GdVal _t4 = '))]
    new_block = setup[setup.index('    if (gd_ctx.native_resolved_dispatch) {'):setup.index('\n    (void)', setup.index('    if (gd_ctx.native_resolved_dispatch) {'))]
    for name, block in [('baseline_stack_block', old_block.replace('this->', 'item.')), ('candidate_stack_block', new_block)]:
        header += f'inline void {name}(Gd__gd_core__CoreItem& item) {{gd::BattleCtx& gd_ctx = *item.rt_ctx_;\n' + block + '\n}\n'
    for name, (_, new) in metrics.items():
        header += 'inline ' + new.replace(f'Gd__gd_core__CoreItem::sf_{name}', 'candidate_' + name) + '\n'
    (WORK / 'preflight_static_setup.hpp').write_text(header, encoding='utf8', newline='\n')
    report = dict(baseline_dll_sha256=EXPECTED, classes=len(classes), fast_getter_classes=sum(bool(row['fast']) for row in classes),
                  pure_getter_cases=sum(len(row['fast']) for row in classes), all_own_static_cases=sum(len(row['cases']) for row in classes),
                  stack_keys=list(range(100, 111)), original_setup_sha256=hashlib.sha256(original.encode()).hexdigest(),
                  mutable_static_collection_getters_unchanged=True, original_dictionary_layout_and_order_preserved=True,
                  existing_nonempty_reserved_aliased_unknown_tables_use_ordered_original_writes=True,
                  screen_protocol=dict(pairs=8, calls_per_arm=[1000000, 20000], retain_first_and_all_results=True, no_whole_fight_gain_claim=True))
    (WORK / 'evaluation_plan.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf8')
    print(json.dumps(report, indent=2))

if __name__ == '__main__': main()
