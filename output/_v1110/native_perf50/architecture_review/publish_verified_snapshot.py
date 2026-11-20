"""Fast-forward the verified runtime backup with the installed follow-up."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import tempfile

WORK = Path(__file__).resolve().parent
REPO = WORK.parents[3]
BRANCH = "refs/heads/codex/native-perf50-verified"
PREVIOUS = "129bfbdeeefb58313b601e9422b9ebbe4c96461d"


def git(*args, env=None):
    return subprocess.check_output(["git", *args], cwd=REPO, env=env)


def remote_head():
    return git("ls-remote", "--exit-code", "origin", BRANCH).decode().split()[0]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("name")
    args = parser.parse_args()
    report = json.loads((WORK / f"{args.name}_installation.json").read_bytes())
    local_commit = git("rev-parse", "HEAD").decode().strip()
    changed = [path for path in git("diff", "--name-only", "-z", "HEAD^", "HEAD").decode().split("\0") if path]
    native_files = report["changed_native_files"]
    assert remote_head() == PREVIOUS
    with tempfile.TemporaryDirectory(prefix="native-followup-index-") as directory:
        env = dict(os.environ, GIT_INDEX_FILE=str(Path(directory) / "index"))
        git("read-tree", PREVIOUS, env=env)
        git("add", "-f", "--", *changed, env=env)

        if native_files:
            git("-c", "core.autocrlf=false", "add", "-f", "--", *native_files, env=env)
        tree = git("write-tree", env=env).decode().strip()
    commit = git("commit-tree", tree, "-p", PREVIOUS, "-p", local_commit,
                 "-m", "backup: preserve verified serial replay follow-up").decode().strip()
    for path in native_files:
        saved = git("show", f"{commit}:{path}")
        assert saved == (REPO / path).read_bytes()
        if path.endswith("/libgdcore.dll"):
            assert hashlib.sha256(saved).hexdigest() == report["dll_sha256"]
    subprocess.run(["git", "push", "origin", f"{commit}:{BRANCH}"], cwd=REPO, check=True)
    assert remote_head() == commit
    print(commit, report["dll_sha256"])


if __name__ == "__main__":
    main()
