#!/usr/bin/env bash
# Repeatedly download and import opponents in one verified Python operation.
# Usage: bash scripts/download_and_import_opponents_loop.sh [interval_minutes] [--log-format summary|json] [--color auto|always|never]
# Read collection.interval_minutes from configs/opponents.toml once at startup unless overridden; restart to reload.
# Run immediately, then wait the selected minutes after each attempt; Ctrl+C stops the loop.

set -euo pipefail

_usage() {
  printf 'Usage: bash %s [interval_minutes] [--log-format summary|json] [--color auto|always|never]\n' "${BASH_SOURCE[0]}" >&2
  printf 'Interval must be a positive integer in minutes (default: collection.interval_minutes in configs/opponents.toml; restart to reload).\n' >&2
  exit 2
}

_interval_minutes=''
if [[ $# -gt 0 && "$1" != --* ]]; then
  _interval_minutes="$1"
  [[ "$_interval_minutes" =~ ^[1-9][0-9]*$ ]] || _usage
  shift
fi
_log_format=summary
_color=auto
_options=()
while [[ $# -gt 0 ]]; do
  [[ $# -ge 2 ]] || _usage
  case "$1" in
    --log-format)
      [[ "$2" == summary || "$2" == json ]] || _usage
      _log_format="$2"
      ;;
    --color)
      [[ "$2" == auto || "$2" == always || "$2" == never ]] || _usage
      _color="$2"
      ;;
    *) _usage ;;
  esac
  _options+=("$1" "$2")
  shift 2
done

_log_fd=1
[[ "$_log_format" == json ]] && _log_fd=2
_red=''
_reset=''
if [[ "$_log_format" != json && ( "$_color" == always || ( "$_color" == auto && -t 2 && -z "${NO_COLOR-}" && "${TERM-}" != dumb ) ) ]]; then
  _red=$'\033[31m'
  _reset=$'\033[0m'
fi
_separator='================================================================'
_round=0
_round_open=false
_stop() {
  printf '\n对手下载导入循环已停止。\n' >&"$_log_fd"
  if [[ "$_round_open" == true ]]; then
    printf '%s\n' "$_separator" >&"$_log_fd"
  fi
  exit 0
}

cd -- "$(rtk proxy dirname -- "${BASH_SOURCE[0]}")/.." || exit 1
if [[ -z "$_interval_minutes" ]]; then
  _interval_minutes=$(rtk proxy uv run --frozen python - <<'PY'
from pathlib import Path

from bpb_research.opponents.policy import collection_interval_minutes

try:
    print(collection_interval_minutes(Path.cwd()))
except (OSError, ValueError) as error:
    raise SystemExit(f"无法读取 configs/opponents.toml 的采集间隔：{error}") from error
PY
  ) || exit 2
fi
trap _stop INT TERM

while true; do
  _round=$((_round + 1))
  _round_open=true
  TZ=Asia/Shanghai printf -v _started '%(%Y-%m-%d %H:%M:%S)T' -1
  printf '\n%s\n📥 第 %s 轮 | 开始时间：%s（北京时间）\n%s\n' "$_separator" "$_round" "$_started" '----------------------------------------------------------------' >&"$_log_fd"
  if rtk proxy uv run --frozen python scripts/download_and_import_opponents.py "${_options[@]}"; then
    _status=0
  else
    _status=$?
    if [[ "$_status" == 130 || "$_status" == 143 ]]; then
      _stop
    fi
    printf '%s本轮下载或导入失败（退出码 %s）。%s\n' "$_red" "$_status" "$_reset" >&2
  fi

  printf '等待 %s 分钟，按 Ctrl+C 停止。\n%s\n' "$_interval_minutes" "$_separator" >&"$_log_fd"
  _round_open=false
  rtk proxy sleep "${_interval_minutes}m"
done
