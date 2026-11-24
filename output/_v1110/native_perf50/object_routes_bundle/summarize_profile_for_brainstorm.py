"""Produce a mutually exclusive phase summary from the deployed DLL sample."""
import hashlib
import json
from collections import Counter
from pathlib import Path

work = Path(__file__).resolve().parent
profile_path = work / 'profile_depth64.json'
profile = json.loads(profile_path.read_bytes())
verified = json.loads((work / 'post_install_verification.json').read_bytes())
assert profile['dll_sha256'] == verified['dll_sha256']
phases = Counter()
tls_callers = Counter()
for row in profile['resolved_stacks']:
    functions, count = row['functions'], row['samples']
    phase = 'outside_replay'
    if any('run_one_internal' in name for name in functions):
        phase = 'other_setup_export'
        if any('build_side_items' in name for name in functions):
            phase = 'assembly'
        elif any('CoreCombat::fn_physicsTick' in name for name in functions):
            phase = 'trigger_chain' if any('CoreItem::fn_trigger(' in name for name in functions) else 'other_frame'
    phases[phase] += count
    if functions and ('pthread' in functions[0] or 'emutls' in functions[0]):
        caller = next((name for name in functions if 'pthread' not in name and 'emutls' not in name), 'unresolved')
        tls_callers[caller] += count
assert sum(phases.values()) == profile['samples']
replay = profile['samples'] - phases['outside_replay']
leaf = Counter(dict(profile['leaf']))
fps = verified['target_at20_fps']
result = {
    'dll_sha256': profile['dll_sha256'],
    'inputs_sha256': profile['inputs_sha256'],
    'profile_sha256': hashlib.sha256(profile_path.read_bytes()).hexdigest(),
    'samples': profile['samples'], 'replay_root_samples': replay,
    'exclusive_phase_samples': dict(phases),
    'replay_phase_pct': {key: count / replay * 100 for key, count in phases.items() if key != 'outside_replay'},
    'dictionary_and_hash_leaf_samples': sum(count for name, count in leaf.items() if 'gd::GdDict::' in name or 'gd::gd_val_hash' in name),
    'generic_method_leaf_samples': sum(count for name, count in leaf.items() if name.startswith('gd::call_method(')),
    'tls_leaf_callers': tls_callers.most_common(),
    'load20_fitted_fps': fps, 'goal_fps': 200,
    'implied_throughput_increase_pct': (200 / fps - 1) * 100,
    'implied_time_reduction_pct': (1 - fps / 200) * 100,
    'limits': ['Sample attribution is not measured speedup or an optimization ceiling.',
               'Phase classification uses stack names; inlined work stays with its emitted parent.',
               'The load fit does not remove frequency, temperature or workload-type effects.',
               'Unchanged ordering, RNG, arithmetic and observable aliases remain required.'],
}
(work / 'brainstorm_profile_summary.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf8')
print(json.dumps(result, ensure_ascii=False))
