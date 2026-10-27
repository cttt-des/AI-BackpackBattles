$target = Get-Date '2026-10-26 23:55:00'
$now = Get-Date
$sec = [int]($target - $now).TotalSeconds
if ($sec -gt 0) { Start-Sleep -Seconds $sec }
Get-Process ZCode -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Process -FilePath 'shutdown.exe' -ArgumentList '/s','/t','60','/c','scheduled shutdown at 23:55 (run shutdown /a to cancel)' -WindowStyle Hidden
