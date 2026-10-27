@echo off
taskkill /IM ZCode.exe /F >nul 2>&1
shutdown /s /t 60 /c "23:55 scheduled shutdown - run shutdown /a to cancel"
