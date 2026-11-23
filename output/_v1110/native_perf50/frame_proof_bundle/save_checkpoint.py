"""Commit only this round and fast-forward the verified source/DLL backup."""
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]
PREVIOUS='1b18298e39ed36f0fd0dbe5d0e00699d9407c643'
BRANCH='refs/heads/codex/native-perf50-verified'

def git(*args,env=None):return subprocess.check_output(['git',*args],cwd=REPO,env=env)
def digest(data):return hashlib.sha256(data).hexdigest()

def add_paths(paths,env=None):
    # Thousands of per-case receipts exceed the Windows command-line limit.
    with tempfile.NamedTemporaryFile(prefix='native-verified-paths-',suffix='.txt',delete=False) as output:
        path=Path(output.name);output.write(b''.join(name.encode('utf8')+b'\0' for name in paths))
    try:git('-c','core.autocrlf=false','add','-f',f'--pathspec-from-file={path}','--pathspec-file-nul',env=env)
    finally:path.unlink()

def main():
    assert not git('diff','--cached','--name-only').strip(),'Retain preexisting staged work'
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==PREVIOUS
    installation=json.loads((WORK/'bundle_installation.json').read_bytes())
    verified=json.loads((WORK/'post_install_verification.json').read_bytes())
    assert verified['passed'] and verified['strict_event_cases']==2604
    assert verified['dll_sha256']==installation['dll_sha256']==digest((WORK/'bundle.dll').read_bytes())
    manifest=json.loads((WORK/'regeneration_manifest.json').read_bytes())
    paths={p for p in WORK.iterdir() if p.is_file() and p.suffix in ('.py','.json','.txt','.log','.hpp') and not p.name.startswith('checkpoint')}
    paths.update((WORK/'bundle_src'/row['path']) for row in manifest['files'])
    paths.update(p for p in (WORK/'before_runtime').rglob('*') if p.is_file())
    paths.update(REPO/p for p in installation['changed_native_files'])
    paths.update(REPO/p for p in ('dist/native_1_1_10/libgdcore.dll','dist/native_1_1_10/manifest.json','docs/C++模拟器性能优化清单.md','docs/C++模拟器下一阶段优化评估.md'))
    paths.add(WORK/'bundle.dll')
    paths.update(STAGE/p for p in ('native_lazy_diagnostics.hpp','prepare_native_lazy_diagnostics.py','prepare_native_buff_diagnostics.py','test_native_lazy_diagnostics.cpp','test_native_buff_diagnostics.cpp','probe_native_lazy_diagnostics.py','probe_native_buff_diagnostics.py','snapshot_label_diagnostic_screen.py','prototype_native_frame_proof_bundle.py','setup_frame_proof_bundle.py','preflight_native_lazy_bundle.py'))
    paths.update(p for p in (WORK.parent/'lazy_diagnostics_probe').iterdir() if p.is_file())
    paths.update(STAGE/p for p in ('prototype_native_frame_proof_bundle.py','preflight_native_member_frame.py','setup_frame_proof_bundle.py','test_native_member_fields.cpp','test_native_frame_segments.cpp'))
    paths.update(STAGE/p for p in ('prototype_native_member_frame_bundle.py','setup_member_frame_bundle.py','test_native_frame_cost.cpp','probe_native_frame_cost.py'))
    prior=WORK.parent/'member_frame_bundle'
    paths.update(p for p in prior.iterdir() if p.is_file())
    paths.update(p for p in (prior/'bundle_src').rglob('*') if p.is_file())
    paths.update(STAGE/p for p in ('prototype_native_frame_proof_bundle.py','setup_frame_proof_bundle.py'))
    paths.update(STAGE/p for p in ('prepare_native_static_collections.py','test_native_static_collections.cpp','probe_native_static_collections.py','prototype_native_frame_proof_bundle.py','preflight_native_static_bundle.py','setup_frame_proof_bundle.py'))
    paths.update(p for p in (WORK.parent/'static_collections_probe').iterdir() if p.is_file())
    paths.update(STAGE/p for p in ('prepare_native_static_setup.py','test_native_static_setup.cpp','probe_native_static_setup.py','prototype_native_frame_proof_bundle.py','preflight_native_frame_proof_bundle.py','setup_frame_proof_bundle.py'))
    paths.update(p for p in (WORK.parent/'static_setup_probe').iterdir() if p.is_file())
    paths.update(STAGE/p for p in ('prepare_native_dispatch_chain.py','test_native_dispatch_chain.cpp','probe_native_dispatch_chain.py','extend_dispatch_chain_cases.py','reproduce_dispatch_chain_hash.py','prototype_native_frame_proof_bundle.py','preflight_native_frame_proof_bundle.py','setup_frame_proof_bundle.py'))
    paths.update(STAGE.glob('dispatch_chain*.log'))
    paths.update(p for p in (WORK.parent/'dispatch_chain_probe').iterdir() if p.is_file())
    paths.update(STAGE/p for p in ('prepare_native_spatial.py','test_native_spatial.cpp','probe_native_spatial.py','prototype_native_frame_proof_bundle.py','preflight_native_frame_proof_bundle.py','setup_frame_proof_bundle.py'))
    paths.update(p for p in (WORK.parent/'spatial_probe').iterdir() if p.is_file())
    paths.update(STAGE/p for p in ('prepare_native_motion_indices.py','test_native_motion_indices.cpp','probe_native_motion_indices.py','prototype_native_frame_proof_bundle.py','preflight_native_frame_proof_bundle.py','setup_frame_proof_bundle.py'))
    paths.update(p for p in (WORK.parent/'motion_indices_probe').iterdir() if p.is_file())
    # Preserve the rejected damage bundle's exact measurements and local probes.
    paths.update(STAGE/p for p in ('prepare_native_damage_records.py','test_native_damage_records.cpp','probe_native_damage_records.py','test_native_damage_records_extended.cpp','probe_native_damage_records_extended.py','prepare_native_damage_combo.py','probe_native_damage_combo.py','test_native_damage_source_helpers.cpp','probe_native_damage_source_helpers.py','test_native_damage_active_helpers.cpp','probe_native_damage_active_helpers.py','prototype_native_damage_combo_bundle.py','preflight_native_damage_combo_bundle.py','setup_damage_combo_bundle.py'))
    for folder in ('damage_records_probe','damage_combo_probe','damage_combo_bundle'):
        paths.update(p for p in (WORK.parent/folder).iterdir() if p.is_file())
    paths.update(STAGE/p for p in ('native_targeted_timers.hpp','prepare_native_targeted_timers.py','review_fix_targeted_timer_prototype.py','build_native_targeted_timer_prototype.py','inspect_targeted_timer_fixed200.py','test_native_targeted_timers.cpp','probe_native_targeted_timers.py','test_targeted_timer_safety.cpp','probe_targeted_timer_safety.py','test_targeted_timer_local_cost.cpp','probe_targeted_timer_local_cost.py','test_targeted_timer_ownership.cpp','probe_targeted_timer_ownership.py','repair_targeted_timer_ownership.py','prototype_native_frame_proof_bundle.py','setup_frame_proof_bundle.py','inspect_native_timer_sparsity.py'))
    for folder in ('targeted_timer_probe','targeted_timer_prototype','targeted_timer_bundle_revision1_build','targeted_timer_bundle'):
        paths.update(p for p in (WORK.parent/folder).iterdir() if p.is_file())
    paths.update(STAGE/p for p in ('prototype_native_targeted_timer_bundle.py','setup_targeted_timer_bundle.py','preflight_native_targeted_timer_bundle.py'))
    paths.update(STAGE/p for p in ('prepare_native_closed_timer.py','repair_closed_timer_diagnostic.py','inspect_closed_timer_fixed200.py','test_closed_timer_registry.cpp','verify_closed_timer_prototype.py','verify_closed_timer_known_cases.py','verify_closed_timer_registry.py'))
    paths.update(p for p in (WORK.parent/'closed_timer_prototype').iterdir() if p.is_file())
    paths.update(STAGE/p for p in ('prepare_native_active_cooldowns.py','build_native_active_cooldown_prototype.py','native_active_cooldowns.hpp','test_native_active_cooldowns.cpp','verify_native_active_cooldown_prototype.py','verify_native_active_cooldown_coverage.py','inspect_native_active_cooldown_fixed200.py','prototype_native_frame_proof_bundle.py','verify_native_active_cooldown_final.py','setup_frame_proof_bundle.py'))
    for folder in ('active_cooldown_prototype','typed_hotchain_prototype','typed_hotchain_bundle','cooldown_sparsity_probe','dict_cost_probe'):
        paths.update(p for p in (WORK.parent/folder).rglob('*') if p.is_file())
    paths.update(STAGE/p for p in ('prepare_native_typed_hotchain.py','extend_native_typed_hotchain.py','native_typed_damage_math.hpp','test_native_typed_damage_math.cpp','probe_native_typed_damage_math.py','probe_native_typed_hotchain.py','prototype_native_typed_hotchain_bundle.py','setup_typed_hotchain_bundle.py','preflight_native_typed_hotchain_bundle.py','verify_native_typed_hotchain_final.py','test_native_typed_damage_ranges.cpp','inspect_native_dict_cost.py','inspect_native_cooldown_sparsity.py'))
    paths.update(STAGE/p for p in ('inspect_native_geometry_cost.py','native_integer_grid.hpp','test_native_integer_grid_slots.cpp','probe_native_integer_grid_slots.py','build_native_semantic_base.py','prepare_native_integer_grid.py','build_native_integer_grid_prototype.py','test_native_integer_grid_dict.cpp','verify_native_integer_grid_dict.py','verify_native_integer_grid_queries.py','prepare_native_grid_cooldown.py','build_native_grid_cooldown_prototype.py','verify_native_grid_cooldown_prototype.py','prototype_native_frame_proof_bundle.py','verify_native_integer_grid_final.py','setup_frame_proof_bundle.py','preflight_native_frame_proof_bundle.py'))
    for folder in ('geometry_cost_probe','integer_grid_prototype','grid_cooldown_prototype','semantic_base_55b6'):
        paths.update(p for p in (WORK.parent/folder).rglob('*') if p.is_file())
    paths.update(STAGE/p for p in ('inspect_native_event_param_capacity.py','prepare_native_event_capacity.py','build_native_event_capacity_prototype.py','test_native_event_capacity.cpp','verify_native_event_capacity.py','prototype_native_frame_proof_bundle.py','setup_frame_proof_bundle.py','preflight_native_frame_proof_bundle.py'))
    for folder in ('event_param_capacity_probe','event_capacity_prototype'):
        paths.update(p for p in (WORK.parent/folder).rglob('*') if p.is_file())
    paths.update(STAGE/p for p in ('prototype_native_grid_cooldown_bundle.py','setup_grid_cooldown_bundle.py','preflight_native_grid_cooldown_bundle.py'))
    audit=json.loads((WORK/'full_type_audit.json').read_bytes())
    for root in map(Path,audit['receipts']):
        paths.update(root/name for name in ('native_resolved_audit.json','native_type_audit.json','native_property_audit.json','native_type_constructor_audit.json','native_hot_slot_audit.json','native_event_identity_audit.json','native_lazy_diagnostic_audit.json','native_static_collection_audit.json','native_static_setup_audit.json','native_dispatch_chain_audit.json','summary.json'))
    # Preserve per-case event hashes for this comparison and its actual baseline.
    for root in map(Path,audit['receipts']):paths.update(root.glob('*.json'))
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths)
    missing=[p for p in relative if not (REPO/p).is_file()]
    assert not missing,missing
    if '--check-only' in sys.argv:
        print(json.dumps({'paths':len(relative),'missing':missing,'dll_sha256':installation['dll_sha256']}))
        return
    # Preserve raw bytes, including pinned JSON report hashes and DLL manifests.
    add_paths(relative)
    staged=git('diff','--cached','--name-only','-z').decode().split('\0')
    assert set(p for p in staged if p).issubset(relative)
    git('commit','-m','perf: reduce event parameter dictionary initial capacity')
    local=git('rev-parse','HEAD').decode().strip()
    with tempfile.TemporaryDirectory(prefix='native-dispatch-array-backup-') as directory:
        env=dict(os.environ,GIT_INDEX_FILE=str(Path(directory)/'index'))
        git('read-tree',PREVIOUS,env=env)
        add_paths(relative,env=env)
        tree=git('write-tree',env=env).decode().strip()
    commit=git('commit-tree',tree,'-p',PREVIOUS,'-p',local,'-m','backup: preserve verified event parameter storage').decode().strip()
    native=STAGE/'sim_native/native_sim_cpp/native_sim'
    source=[p for p in native.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py')]
    assert len(source)==707
    checked=sorted(set(source)|{REPO/path for path in relative}|{native/'libgdcore.dll'})
    data=subprocess.check_output(['git','cat-file','--batch'],cwd=REPO,input=''.join(f'{commit}:{p.relative_to(REPO).as_posix()}\n' for p in checked).encode('utf8'))
    stream=io.BytesIO(data)
    for path in checked:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob'
        assert stream.read(int(header[2]))==path.read_bytes(),path
        assert stream.read(1)==b'\n'
    subprocess.run(['git','push','origin',f'{commit}:{BRANCH}'],cwd=REPO,check=True)
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==commit
    print(json.dumps({'local_commit':local,'remote_verified_commit':commit,
        'source_files_verified':len(source),'dll_sha256':installation['dll_sha256'],'own_files_saved':len(relative)}))

if __name__=='__main__':main()
