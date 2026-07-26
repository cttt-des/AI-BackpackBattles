"""
Backpack Battles AI - GUI application entry point.
Double-click the exe to launch the native desktop control panel.
"""

import os
import sys
import logging
from datetime import datetime
from pathlib import Path

# Fix Chinese output in Windows console (code page issue)
if os.name == "nt":
    try:
        import ctypes
        kernel32 = ctypes.windll.kernel32
        kernel32.SetConsoleOutputCP(65001)
        kernel32.SetConsoleCP(65001)
    except Exception:
        pass
    try:
        if hasattr(sys.stdout, "reconfigure"):
            sys.stdout.reconfigure(encoding="utf-8")
            sys.stderr.reconfigure(encoding="utf-8")
    except Exception:
        pass

# Ensure project root is on path (dev mode)
if not getattr(sys, "frozen", False):
    sys.path.insert(0, str(Path(__file__).parent))

from core.paths import get_base_dir


def main():
    # Logging to file (GUI shows its own log panel too)
    log_dir = get_base_dir() / "logs"
    log_dir.mkdir(exist_ok=True)
    log_file = log_dir / f"gui_{datetime.now().strftime('%Y%m%d_%H%M%S')}.log"

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        handlers=[
            logging.FileHandler(log_file, encoding="utf-8"),
        ],
    )

    try:
        from gui.app import run
        run()
    except Exception as e:
        logging.error(f"Failed to start GUI: {e}")
        import traceback
        traceback.print_exc()
        try:
            import tkinter.messagebox as mb
            mb.showerror("启动失败", f"{e}")
        except Exception:
            input("Press Enter to exit...")


if __name__ == "__main__":
    main()
