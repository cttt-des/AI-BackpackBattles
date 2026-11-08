# 注册 Windows 定时任务（每 20 分钟一轮）
# 需管理员权限；先在「任务计划程序」里确认路径
$script = Join-Path $PSScriptRoot "run_collect.ps1"
$action = New-ScheduledTaskAction -Execute "powershell.exe" -Argument "-NoProfile -ExecutionPolicy Bypass -File \"$script\" -Source bpb2-matches -IntervalMinutes 20"
$trigger = New-ScheduledTaskTrigger -AtLogOn
$settings = New-ScheduledTaskSettingsSet -StartWhenAvailable -DontStopOnIdleEnd
Register-ScheduledTask -TaskName "BPB-Gripper-Collect" -Action $action -Trigger $trigger -Settings $settings -Description "背包乱斗对手/对局数据定时采集"
