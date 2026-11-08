"""Coordinate local archive, resource export, and viewer tasks for WSL users.

``download_and_import_command`` downloads and imports in one process. Viewer workflows consume only verified Steam leaderboard batches and do not read game caches or personal history.
"""

import argparse
import json
import sqlite3
import subprocess
import sys
import time
import webbrowser
from contextlib import redirect_stdout
from http.server import ThreadingHTTPServer
from pathlib import Path
from typing import Any

from bpb_research.opponents.console import (
    _render_failure,
    _render_summary,
    _use_color,
)
from bpb_research.opponents.policy import retention_days
from bpb_research.opponents.store import sync_downloaded_opponents
from bpb_research.runtime.assets import (
    DEFAULT_GAME_DIR,
    DEFAULT_USER_DIR,
    DEFAULT_WINDOWS_PYTHON,
    verify_asset_export,
)
from bpb_research.runtime.opponents import _opponent_batch_session, fetch_opponents
from bpb_research.runtime.resources import (
    _opponent_resource_session,
    export_game_resources,
)
from bpb_research.visualization.server import create_server


def _arguments(description: str, argv: list[str] | None) -> argparse.Namespace:
    parser: argparse.ArgumentParser = argparse.ArgumentParser(description=description)
    parser.add_argument("--game-dir", type=Path, default=DEFAULT_GAME_DIR)
    parser.add_argument(
        "--user-dir", type=Path, default=DEFAULT_USER_DIR, help=argparse.SUPPRESS
    )
    parser.add_argument("--database-dir", type=Path, default=Path("database"))
    parser.add_argument("--windows-python", type=Path, default=DEFAULT_WINDOWS_PYTHON)
    parser.add_argument("--port", type=int, default=8765)
    parser.add_argument("--no-open", action="store_true")
    parser.add_argument(
        "--offline",
        action="store_true",
        help="Browse only the existing archive without preparing or synchronizing inputs",
    )
    args: argparse.Namespace = parser.parse_args(argv)
    return args


def _sync(args: argparse.Namespace, assets: Path | None) -> dict[str, Any]:
    return sync_downloaded_opponents(
        database_dir=args.database_dir,
        retention_days=retention_days(Path(__file__).resolve().parents[2]),
        catalog_path=assets / "catalog.json" if assets else None,
        assets_manifest=assets / "manifest.json" if assets else None,
    )


def download_and_import_command(argv: list[str] | None = None) -> int:
    """Prepare verified resources, download or reuse a Steam batch, and incrementally import it.

    Args:
        argv: Optional CLI arguments; defaults to the process arguments.

    Returns:
        Zero after a complete round, one after a preparation, download or import failure, or 130 after keyboard interruption.
    """
    parser: argparse.ArgumentParser = argparse.ArgumentParser(
        description="Download and import verified Master-or-higher opponents"
    )
    parser.add_argument("--game-dir", type=Path, default=DEFAULT_GAME_DIR)
    parser.add_argument("--database-dir", type=Path, default=Path("database"))
    parser.add_argument("--windows-python", type=Path, default=DEFAULT_WINDOWS_PYTHON)
    parser.add_argument("--log-format", choices=("summary", "json"), default="summary")
    parser.add_argument("--color", choices=("auto", "always", "never"), default="auto")
    parser.add_argument(
        "--resume-batch",
        metavar="BATCH_ID",
        help="Recover a verified local batch and import it without downloading from Steam",
    )
    args: argparse.Namespace = parser.parse_args(argv)
    outcome: dict[str, Any] = {"status": "failed", "stage": "download"}
    try:
        with redirect_stdout(sys.stderr):
            result: dict = _download_and_import(args, _outcome=outcome)
        if args.log_format == "json":
            print(json.dumps(result, ensure_ascii=False), flush=True)
        else:
            print(
                _render_summary(result, color=_use_color(args.color, sys.stdout)),
                flush=True,
            )
        return 0
    except (
        OSError,
        ValueError,
        RuntimeError,
        sqlite3.Error,
        KeyboardInterrupt,
    ) as error:
        interrupted: bool = isinstance(error, KeyboardInterrupt)
        outcome.update(
            status="interrupted" if interrupted else "failed",
            error=str(error) or "用户中断",
        )
        if args.log_format == "json":
            print(json.dumps(outcome, ensure_ascii=False), flush=True)
        print(
            _render_failure(
                outcome,
                color=args.log_format != "json" and _use_color(args.color, sys.stderr),
            ),
            file=sys.stderr,
            flush=True,
        )
        return 130 if interrupted else 1


def _download_and_import(
    args: argparse.Namespace, *, _outcome: dict[str, Any] | None = None
) -> dict[str, Any]:
    started: float = time.perf_counter()
    with _opponent_resource_session() as session, _opponent_batch_session() as batches:
        try:
            options: dict[str, Any] = {}
            if getattr(args, "resume_batch", None) is not None:
                options["resume_batch"] = args.resume_batch
            fetched: dict = fetch_opponents(
                game_dir=args.game_dir,
                database_dir=args.database_dir,
                windows_python=args.windows_python,
                **options,
            )
        except (OSError, ValueError, RuntimeError):
            print(
                "下载失败，本轮跳过数据库导入。",
                file=sys.stderr,
            )
            raise
        if _outcome is not None:
            _outcome.update(stage="import", download=fetched)
        print("正在导入对手 (持久化数据仅手动退役)...", file=sys.stderr, flush=True)
        try:
            session._before_sync()
            assert session.snapshot is not None and session.rules is not None
            assets: Path = (session.snapshot / "assets").resolve()
            phase: float = time.perf_counter()
            days: int = retention_days(Path(__file__).resolve().parents[2])
            sync_options: dict[str, Any] = {}
            if getattr(args, "resume_batch", None) is not None:
                sync_options["batch_id"] = args.resume_batch
            result: dict = sync_downloaded_opponents(
                database_dir=args.database_dir,
                retention_days=days,
                catalog_path=assets / "catalog.json",
                assets_manifest=assets / "manifest.json",
                validation_rules=session.rules,
                **sync_options,
            )
            result["timings"] = {
                **fetched.get("timings", {}),
                **result.get("timings", {}),
                "sync_seconds": time.perf_counter() - phase,
                "total_seconds": time.perf_counter() - started,
                "batch_verifications": batches.verified_batches,
                "batch_validation_reuses": batches.reused_batches,
                "payload_reuses": batches.reused_payloads,
            }
            result.update(status="complete", download=fetched, retention_days=days)
            return result
        except (OSError, ValueError, RuntimeError, sqlite3.Error):
            print("数据库导入失败；未执行数据退役。", file=sys.stderr)
            raise


def resources_command(argv: list[str] | None = None) -> int:
    """Export one verified bilingual resource snapshot, including the item library."""
    parser: argparse.ArgumentParser = argparse.ArgumentParser(
        description="Export complete latest game resources"
    )
    parser.add_argument("--game-dir", type=Path, default=DEFAULT_GAME_DIR)
    parser.add_argument("--output-root", type=Path, default=Path("database/resources"))
    parser.add_argument("--windows-python", type=Path, default=DEFAULT_WINDOWS_PYTHON)
    parser.add_argument(
        "--snapshot-file",
        type=Path,
        help="Write the verified snapshot path for dependent launchers",
    )
    parser.add_argument(
        "--skip-maintenance",
        action="store_true",
        help="Prepare verified resources without running disk reclamation",
    )
    args: argparse.Namespace = parser.parse_args(argv)
    from bpb_research.resource_leases import resource_project
    from bpb_research.storage import storage_lock

    root: Path = args.output_root.resolve()
    try:
        with storage_lock(resource_project(root) or root.parent):
            return _update_resources(args)
    except OSError as error:
        print(str(error), file=sys.stderr)
        return 1


def _update_resources(args: argparse.Namespace) -> int:
    try:
        output: Path = export_game_resources(
            game_dir=args.game_dir,
            output_root=args.output_root,
            windows_python=args.windows_python,
        )
        manifest: dict = json.loads((output / "manifest.json").read_text())
        if args.snapshot_file is not None:
            args.snapshot_file.write_text(str(output.resolve()) + "\n")
        print(
            f"Verified resources: {output}\nLatest: {args.output_root.resolve() / 'latest'}\nGame: {manifest['game_version']}{manifest['subversion']} · Items: {manifest['items']} · Failures: {manifest['failures']}"
        )
        timing: Path = args.output_root / "timing.json"
        if timing.is_file():
            print(
                json.dumps(
                    {"resource_timings": json.loads(timing.read_text())},
                    ensure_ascii=False,
                )
            )
        from bpb_research.resource_storage import maintain_resources

        owner: Path = args.output_root.resolve().parent.parent
        if (
            not args.skip_maintenance
            and args.output_root.resolve() == owner / "database/resources"
            and output.resolve().is_relative_to(args.output_root.resolve())
        ):
            try:
                maintenance: dict = maintain_resources(owner, apply=True)
                print(
                    json.dumps(
                        {
                            "resource_maintenance": {
                                "status": maintenance["status"],
                                "shared_icons": maintenance["sharing"]["shared_paths"],
                                "retired_generations": maintenance[
                                    "retired_generations"
                                ],
                                "protected_generations": len(maintenance["protected"]),
                                "reclaimed_bytes": maintenance["reclaimed_bytes"],
                                "receipt": maintenance.get("receipt"),
                                "issues": maintenance["issues"],
                            }
                        },
                        ensure_ascii=False,
                    )
                )
            except (
                OSError,
                ValueError,
                RuntimeError,
                KeyError,
                sqlite3.Error,
            ) as error:
                print(
                    f"资源更新成功；资源回收未完成，已保留验证通过的快照：{error}",
                    file=sys.stderr,
                )
        return 0
    except (OSError, ValueError, RuntimeError) as error:
        print(str(error), file=sys.stderr)
        return 1


def viewer_command(argv: list[str] | None = None) -> int:
    """Prepare missing resources, synchronize caches, then serve the local browser."""
    args: argparse.Namespace = _arguments("Open the local opponent build viewer", argv)
    started: float = time.perf_counter()
    timings: dict[str, float] = {}
    try:
        if not args.offline:
            phase: float = time.perf_counter()
            assets: Path | None = None
            if (args.game_dir / "BackpackBattles.pck").is_file():
                bundle: Path = export_game_resources(
                    game_dir=args.game_dir,
                    output_root=args.database_dir / "resources",
                    windows_python=args.windows_python,
                )
                assets = (bundle / "assets").resolve()
            elif (args.database_dir / "resources/latest-assets").is_dir():
                assets = (args.database_dir / "resources/latest-assets").resolve()
                verify_asset_export(assets)
            timings["resources_seconds"] = round(time.perf_counter() - phase, 3)
            phase = time.perf_counter()
            print(json.dumps(_sync(args, assets), ensure_ascii=False, indent=2))
            timings["sync_seconds"] = round(time.perf_counter() - phase, 3)
        database: Path = args.database_dir / "opponents.sqlite"
        library: Path = args.database_dir / "resources/latest"
        if not database.is_file() and not library.is_dir():
            raise FileNotFoundError(
                "No local data; run scripts/update_game_resources.py or Download & Import Opponents first"
            )
        phase = time.perf_counter()
        server: ThreadingHTTPServer = create_server(
            database, port=args.port, resources=library
        )
        timings["server_seconds"] = round(time.perf_counter() - phase, 3)
        timings["startup_seconds"] = round(time.perf_counter() - started, 3)
        print(json.dumps({"atlas_timings": timings}, ensure_ascii=False), flush=True)
        url: str = f"http://127.0.0.1:{server.server_port}"
        print(f"Build viewer: {url}  (Ctrl+C to stop)", flush=True)
        if not args.no_open:
            try:
                subprocess.Popen(
                    ["cmd.exe", "/c", "start", "", url],
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.DEVNULL,
                )
            except OSError:
                webbrowser.open(url)
        try:
            server.serve_forever()
        except KeyboardInterrupt:
            pass
        finally:
            server.server_close()
        return 0
    except (OSError, ValueError, RuntimeError, sqlite3.Error) as error:
        print(str(error), file=sys.stderr)
        return 1
