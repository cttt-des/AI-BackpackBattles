"""Download complete Steam batches and persist both decisions of the verified Master cohort.

Download and import verified opponents with a colored summary or JSONL; use --help for paths and logging options."""

from bpb_research.workflows import download_and_import_command

if __name__ == "__main__":
    raise SystemExit(download_and_import_command())
