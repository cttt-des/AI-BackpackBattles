param(
    [Parameter(Mandatory=$true)][string]$Python,
    [int]$CpuLimit = 75
)

$ErrorActionPreference = 'Stop'
$stage = $PSScriptRoot
$dll = Join-Path $stage 'native_ring_placement.dll'
$verifier = Join-Path $stage 'sim_native/tools/_cpp_verify_events.py'
$observations = Join-Path $stage 'native_controlled_prismatic_run948_placement'
$jobs = @(Get-Content -Raw (Join-Path $stage 'native_host_phases_reuse_plan.json') | ConvertFrom-Json)
$jobs += [pscustomobject]@{source='native_host_observed_expand/expand'; name='native_host_rng_phases_new_expand'; total=19}
$jobs += [pscustomobject]@{source='native_host_observed_base/base'; name='native_host_phases_observed_base_current'; total=124}
$jobs += [pscustomobject]@{source='native_host_observed_base/base'; name='native_host_phases_observed_base_last'; total=8}
$reports = @()
foreach ($job in $jobs) {
    do {
        $cpu = (Get-CimInstance Win32_PerfFormattedData_PerfOS_Processor -Filter "Name='_Total'").PercentProcessorTime
        if ($cpu -ge $CpuLimit) { Start-Sleep -Seconds 15 }
    } while ($cpu -ge $CpuLimit)
    $report = Join-Path $stage ($job.name -replace '^native_', 'native_ring_')
    $reports += $report
    $inputs = Join-Path $stage ($job.name + '_cpp')
    $source = Join-Path $stage $job.source
    Write-Host "CPU $cpu% | $($job.total) fights | $($job.source)"
    if ($job.name -eq 'native_host_phases_observed_base_current') {
        $selection = Join-Path $stage 'native_ring_observed_base_current_ids.json'
        (Get-Content -Raw (Join-Path $inputs 'cases.json') | ConvertFrom-Json).cases.case_id |
            ConvertTo-Json | Set-Content -LiteralPath $selection -Encoding utf8NoBOM
        $name = Split-Path $report -Leaf
        & $Python -u -X utf8 (Join-Path $stage 'check_native_kernel_batch.py') --source $job.source --out $name `
            --limit 0 --direct-cpp --strict-item-origins --native-util-clock --dll $dll `
            --case-ids $selection --ring-placement-observations $observations
        $reports[-1] = Join-Path $report 'cpp'
    } else {
        $log = "$report.log"
        & $Python -u -X utf8 $verifier --case-ids (Join-Path $inputs 'cases.json') `
            --fights-root (Join-Path $inputs 'fights') --align-root (Join-Path $inputs 'align') `
            --cases-json (Join-Path $inputs 'fixtures.json') --strict-gem-origins --strict-item-origins `
            --original-dir $source --native-only --out $report --dll $dll *> $log
    }
    $verifyExit = $LASTEXITCODE
    $summary = Join-Path $reports[-1] 'summary.json'
    if (!(Test-Path -LiteralPath $summary)) { throw "Verifier exited $verifyExit for $($job.name)" }
    $result = Get-Content -Raw $summary | ConvertFrom-Json
    if ($result.total -ne $job.total) { throw "Unexpected report size for $($job.name)" }
    Write-Host "$($result.passed)/$($result.total) strict passes"
}

& $Python -u -X utf8 (Join-Path $stage 'check_native_corpus_gate.py') --dll $dll --report @reports `
    --host-observed-plan (Join-Path $stage 'native_host_observed_reference_plan.json') `
    --ring-placement-observations $observations --out (Join-Path $stage 'native_ring_placement_full_gate.json')
exit $LASTEXITCODE
