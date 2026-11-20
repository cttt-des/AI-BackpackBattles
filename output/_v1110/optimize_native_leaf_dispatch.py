"""Lower generated self calls only in classes without generated subclasses."""
import argparse
from pathlib import Path
import re


def optimize(native, selected):
    generated = native / 'gen'
    if selected == 'behavior_constants':
        path = generated / 'shards/shard_00.cpp'
        source = path.read_text('utf8')
        constant = re.search(r'case SYM_GEN_SELF_BEHAVIOR_METHODS_61: return gd::GdVal::from_arr\(gd::GdArr::from_init\(gd_ctx.arena, \{([^\n]+)\}\)\);', source)
        if not constant:
            raise ValueError('Unexpected behavior whitelist')
        entries = constant[1].split(', ')
        if not entries or any(not re.fullmatch(r'gd::GdVal::from_str\(&battle_string_literals\[\d+\]\)', entry) for entry in entries):
            raise ValueError('The behavior whitelist is not a literal string array')
        old = 'gd::gd_in(lv_methodName, Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_SELF_BEHAVIOR_METHODS_61))'
        if source.count(old) != 2:
            raise ValueError('Unexpected whitelist query count')
        new = 'gd::GdVal::from_bool(' + ' || '.join(f'gd::gd_eq(lv_methodName, {entry})' for entry in entries) + ')'
        path.write_text(source.replace(old, new), encoding='utf8', newline='\n')
        print(f'behavior_constants: removed two allocations of {len(entries)}-element whitelists', flush=True)
        return
    if selected == 'bus_context':
        from optimize_native_serial_paths import method_body
        path = generated / 'shards/shard_12.cpp'
        source = path.read_text('utf8')
        match = method_body(source, 'CoreEventBus', 'emitAndLog')
        context_source = (generated / 'shards/shard_07.cpp').read_text('utf8')
        def property_read(read):
            symbol, field = read.groups()
            if f'case {symbol}: out = this->f_{field}; return true;' not in context_source:
                raise ValueError(f'Unexpected context property {field}')
            return (f'(this->f__ctx.kind == gd::GdVal::Kind::Obj && this->f__ctx.obj && '
                    f'this->f__ctx.obj->meta() == &META_Gd__gd_core__CoreContext '
                    f'? static_cast<Gd__gd_core__CoreContext*>(this->f__ctx.obj)->f_{field} '
                    f': gd::get_prop(gd_ctx, this->f__ctx, {symbol}))')
        body, count = re.subn(r'gd::get_prop\(gd_ctx, this->f__ctx, (SYM_GEN_(\w+)_\d+)\)',
                              property_read, match[1])
        if not count:
            raise ValueError('No event context property reads found')
        if '#include "../hdrs/Gd__gd_core__CoreContext.hpp"' not in source:
            source = '#include "../hdrs/Gd__gd_core__CoreContext.hpp"\n' + source
            match = method_body(source, 'CoreEventBus', 'emitAndLog')
        path.write_text(source[:match.start(1)] + body + source[match.end(1):], encoding='utf8', newline='\n')
        print(f'bus_context: lowered {count} guarded property reads', flush=True)
        return
    owners = {'buff': 'Gd__gd_core__CoreBuff', 'character': 'Gd__gd_core__CoreCharacter',
              'rng': 'Gd__gd_core__CoreRng', 'rng_native': 'Gd__gd_core__CoreRng'}
    owner = owners[selected]
    if selected == 'rng_native':
        runtime = (native/'gd_rt.cpp').read_text('utf8')
        implementation = ('return GdVal::from_float(argc >= 2 ? recv.rng->randf_range('
                          'args[0].as_float(), args[1].as_float()) : 0.0);')
        if implementation not in runtime:
            raise ValueError('The underlying random-range implementation changed')
    headers = list((generated / 'hdrs').glob('*.hpp'))
    for path in headers:
        if re.search(rf'\bpublic\s+{owner}\b', path.read_text('utf8')):
            raise ValueError(f'{owner} has a subclass in {path}')
    sources = {p: p.read_text('utf8') for p in (generated / 'shards').glob('*.cpp')}
    dispatch = next(s for s in sources.values() if f'bool {owner}::call_method(' in s)
    targets = dict(re.findall(r'case ((?:SYM_GEN_|gd::SYM_)\w+): out = fn_(\w+)\(args, argc\); return true;',
                             re.search(rf'^bool {owner}::call_method\([^\n]*\n(.*?)^\}}',
                                       dispatch, re.M | re.S)[1]))
    pattern = re.compile(r'gd::call_method\(gd_ctx, gd::GdVal::from_obj\(this\), '
                         r'((?:SYM_GEN_|gd::SYM_)\w+), ((?:_ca|nullptr), \d+)\)')
    count = 0
    range_calls = 0

    def direct(match):
        nonlocal count
        name = targets.get(match[1])
        if not name:
            return match[0]
        count += 1
        return f'this->fn_{name}({match[2]})'

    updated_sources = {}
    for path, source in sources.items():
        methods = re.compile(rf'^gd::GdVal {owner}::fn_\w+\([^\n]*\n.*?^\}}', re.M | re.S)
        updated = methods.sub(lambda m: pattern.sub(direct, m[0]), source)
        if selected == 'rng_native':
            old = 'gd::call_method(gd_ctx, this->f_rng, gd::SYM_randf_range, _ca, 2)'
            new = ('(this->f_rng.kind == gd::GdVal::Kind::Rng && this->f_rng.rng '
                   '? gd::GdVal::from_float(this->f_rng.rng->randf_range(_ca[0].as_float(), _ca[1].as_float())) '
                   f': {old})')
            range_calls += sum(m[0].count(old) for m in methods.finditer(updated))
            updated = methods.sub(lambda m: m[0].replace(old, new), updated)
        if updated != source:
            updated_sources[path] = updated
    if not count:
        raise ValueError('No self calls were found')
    if selected == 'rng_native' and range_calls != 2:
        raise ValueError('Unexpected native random-range entry points')
    for path, updated in updated_sources.items():
        path.write_text(updated, encoding='utf8', newline='\n')
    print(f'{selected}: lowered {count} verified self calls', flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('native', type=Path)
    parser.add_argument('--part', choices=('buff', 'character', 'rng', 'rng_native', 'bus_context', 'behavior_constants'), required=True)
    args = parser.parse_args()
    optimize(args.native, args.part)
