# 定时采集（Windows 任务计划调用）
# 用法: powershell -ExecutionPolicy Bypass -File run_collect.ps1 -Source bpb2-matches -IntervalMinutes 20
param(
    [string]$Source = "bpb2-matches",
    [int]$IntervalMinutes = 20,
    [string]$DatabaseDir = ""
)
$ErrorActionPreference = "Stop"
$here = Split-Path -Parent $MyInvocation.MyCommand.Path
$src = Join-Path $here "src"
if (-not $DatabaseDir) { $DatabaseDir = Join-Path (Split-Path -Parent $here) "database" }
Set-Location $src
while ($true) {
    python -m bpb_research.collect.cli --source $Source --once --database-dir $DatabaseDir --log-format json
    Start-Sleep -Seconds ($IntervalMinutes * 60)
}
