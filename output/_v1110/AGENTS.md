# Native build storage

User instruction, 2026-11-27: intermediate build products must use another drive and must be removed when the build is finished.

- Use `D:\CodexNativeBuilds\work` for disposable compiler, LTO, PGO and verifier workspaces. Do not create caches under C:\Users\Windows\AppData\Local or the system TEMP.
- Run experiment/verification Python entrypoints through `python output/_v1110/run_native_managed.py SCRIPT [ARGS...]`. Current build helpers also isolate their build scopes, so objects disappear immediately after final outputs and receipts are saved.
- Keep the two PGO phases within one build scope. Its source objects and profile counts are needed between instrumentation, training and final linking; clean them after the complete build, not between those phases.
- Future rounds perform full normal builds and fresh formal PGO. Do not depend on previous rounds' cached `.o` files. Compare compiler flags using verified `compiled_options/*.txt` and their receipts (`native_build_storage.frozen_flags`).
- Export final DLLs, source snapshots, hashes, build-option receipts, frozen PGO evidence and test logs to the experiment bundle before cleanup. Success and failure paths must clean intermediates. Managed workspaces from forcibly terminated processes are recovered on the next managed invocation.
- Frozen historical runtime sources and manifests must remain byte-identical. Do not edit their `build_windows.py` merely to change paths; the managed launcher redirects temporary storage at runtime.
- This storage maintenance does not resume the paused optimization goal. Await the user's resume instruction.
