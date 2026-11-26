"""Relink the verified instrumentation objects with a bounded C export table."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import psutil

psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from build_native_hot_lto import HOT_UNITS,build_dll,collect_profiles

def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def create_instrumented_exports(objects):
    baseline=STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'
    assert digest(baseline)=='0a6d24f459eb1011a0bfcc1bc5c4188c1ca67add410b9caf0e04c8f5d30d44d4'
    names=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','--defined-only',baseline.name],cwd=baseline.parent,text=True)
    exports={line.split()[-1] for line in names.splitlines() if line.split() and line.split()[-1].startswith('gd_')}
    assert sum(name.startswith('gd_sim_') for name in exports)==22
    exports.add('gd_diag_native_variant_stat')
    exports.add('gd_diag_native_property_stat')
    exports.add('gd_diag_native_type_constructor_stat')
    exports.add('gd_diag_native_hot_slot_stat')
    exports.add('gd_diag_native_event_identity_stat')
    exports.add('gd_diag_native_lazy_diagnostic_stat')
    exports.add('gd_diag_native_static_collection_stat')
    exports.add('gd_diag_native_static_setup_stat')
    exports.add('gd_diag_native_dispatch_chain_stat')
    exports.add('gd_diag_native_spatial_stat')
    exports.add('gd_diag_native_motion_index_stat')
    exports.add('gd_diag_native_targeted_timer_stat')
    exports.add('gd_diag_native_active_cooldown_stat')
    exports.add('gd_diag_native_integer_grid_stat')
    exports.add('gd_diag_native_object_route_stat')
    exports.update(('gd_diag_native_timer_registry_closed','gd_diag_native_timer_closed_mode'))
    exports.add('gd_test_native_timer_control')
    exports.add('gd_diag_native_private_snapshot_stat')
    definition=objects/'instrumented_exports.def'
    definition.write_text('EXPORTS\n'+''.join('    '+name+'\n' for name in sorted(exports)),encoding='ascii',newline='\n')
    return definition,sorted(exports)
