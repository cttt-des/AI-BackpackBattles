$ErrorActionPreference = 'Stop'
$root = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot '..')).Path
$archive = Join-Path $root '_archive/20261119'
$paths = @(
 'output/_backup_pre_deckchain', 'output/_backup_pre_stamina_rerecord',
 'output/_timing_four_way', 'output/oracle', 'output/_v1110/full_corpus',
 'output/_re_extract', 'output/_a1', 'output/_handoff10', 'output/_oldsrc', 'output/_newsrc',
 'output/_v1110/native_fresh_expand_rng_project', 'output/_v1110/native_damage_rng_project',
 'output/_v1110/native_opening_delay_probe_project', 'output/_v1110/native_remaining_rng_probe_project',
 'output/_v1110/native_egg_probe', 'output/_v1110/native_amulet_rng_project',
 'output/_v1110/native_engine_boundary_probe_project', 'output/_v1110/native_buff_carry_project',
 'output/_v1110/native_training_release_probe',
 'output/_v1110/sim_native_cython', 'output/_v1110/sim_native_cython_engine_rng',
 'output/_v1110/sim_native_pure_holy',
 'dist/backpack_battles_sim-0.5.2-cp314-cp314-win_amd64.whl',
 'dist/backpack_battles_sim-0.5.3-cp314-cp314-win_amd64.whl',
 'dist/BackpackSimulator.exe', 'probe2.obj.exp', 'probe2.obj.lib'
)
$null = New-Item -ItemType Directory -Path $archive -Force
$records = @()
foreach ($relative in $paths) {
 $source = [IO.Path]::GetFullPath((Join-Path $root $relative))
 $target = [IO.Path]::GetFullPath((Join-Path $archive $relative))
 if (!$source.StartsWith($root + '\') -or !$target.StartsWith($archive + '\')) { throw 'Path outside approved root' }
 if (!(Test-Path -LiteralPath $source)) { continue }
 if (Test-Path -LiteralPath $target) { throw "Archive already exists: $target" }
 $cursor = $source
 while ($cursor -ne $root) {
  if ((Get-Item -LiteralPath $cursor -Force).Attributes -band [IO.FileAttributes]::ReparsePoint) { throw "Reparse point $cursor" }
  $cursor = Split-Path -Parent $cursor
 }
 $null = New-Item -ItemType Directory -Path (Split-Path -Parent $target) -Force
 Move-Item -LiteralPath $source -Destination $target
 $records += [pscustomobject]@{original=$relative; archived=$target; action='move'; restored_by='Move the archived entry back to its original relative path'}
 $records | ConvertTo-Json -Depth 3 | Set-Content -LiteralPath (Join-Path $archive 'manifest.json') -Encoding utf8
 Write-Output "Archived $relative"
}
$original = Join-Path $root 'output/game_copy/BackpackBattles.pck'
$duplicate = Join-Path $root 'output/game_copy/BackpackBattles.pck.bak'
if (Test-Path -LiteralPath $duplicate) {
 if ((Get-FileHash -LiteralPath $original).Hash -ne (Get-FileHash -LiteralPath $duplicate).Hash) { throw 'PCK backup differs' }
 $resolved = (Resolve-Path -LiteralPath $duplicate).Path
 if (!$resolved.StartsWith($root + '\')) { throw 'PCK outside workspace' }
 Remove-Item -LiteralPath $resolved
 Write-Output 'Deleted verified duplicate PCK backup'
}
