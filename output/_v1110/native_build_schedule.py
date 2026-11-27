"""Independent frontend/LTRANS budgets; no changes to generated object options."""
import os
import psutil

GIB = 1024 ** 3


def select_jobs(frontend_jobs=0, lto_jobs=None):
    logical = psutil.cpu_count() or 1
    physical = psutil.cpu_count(logical=False) or logical
    cpu_cap = max(1, min(physical - 1, logical - 2))
    available = psutil.virtual_memory().available
    # Frontends for generated shards are much larger than LTRANS workers.
    usable = max(0, available - 2 * GIB)
    frontend_cap = max(1, min(cpu_cap, int(usable / GIB)))
    lto_cap = max(1, min(cpu_cap, int(usable / (0.5 * GIB))))
    if frontend_jobs < 0:
        raise ValueError('frontend jobs must be zero (auto) or positive')
    if lto_jobs is None:
        value = os.environ.get('NATIVE_LTO_JOBS', 'auto')
        lto_jobs = 0 if value == 'auto' else int(value)
    if lto_jobs < 0:
        raise ValueError('LTO jobs must be zero (auto) or positive')
    return dict(frontend_jobs=min(frontend_jobs or frontend_cap, frontend_cap),
                lto_jobs=min(lto_jobs or lto_cap, lto_cap),
                requested_frontend_jobs=frontend_jobs,
                requested_lto_jobs=lto_jobs,
                logical_cpus=logical, physical_cpus=physical,
                cpu_worker_cap=cpu_cap, reserved_physical_cores=1,
                available_bytes=available, reserved_bytes=2 * GIB,
                automatic_frontend_cap=frontend_cap, automatic_lto_cap=lto_cap)
