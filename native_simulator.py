if __name__ == '__main__':
    import sys
    try:
        from backpack_native.gui import main
        main()
    except Exception:
        if len(sys.argv) == 3 and sys.argv[1] == '--selftest':
            import json
            import traceback
            from pathlib import Path
            Path(sys.argv[2]).write_text(
                json.dumps({'error': traceback.format_exc()}, ensure_ascii=False, indent=2),
                encoding='utf-8')
            sys.exit(1)
        raise
