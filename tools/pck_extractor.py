"""
Godot 3.x .pck file extractor.
Extracts all files from a Godot PCK archive.
"""
import struct
import os
import sys
import argparse


def extract_pck(pck_path: str, output_dir: str, filter_ext: list = None):
    """Extract all files from a Godot 3.x .pck file.

    Args:
        pck_path: Path to the .pck file.
        output_dir: Directory to extract files into.
        filter_ext: Optional list of extensions to extract (e.g. ['.tscn', '.tres']).
                    If None, extracts all files.
    """
    with open(pck_path, 'rb') as f:
        # Header
        magic = f.read(4)
        assert magic == b'GDPC', f"Invalid magic: {magic}"
        pack_ver = struct.unpack('<I', f.read(4))[0]
        major = struct.unpack('<I', f.read(4))[0]
        minor = struct.unpack('<I', f.read(4))[0]
        patch = struct.unpack('<I', f.read(4))[0]
        print(f"Godot {major}.{minor}.{patch}, pack version {pack_ver}")

        # 16 reserved uint32s
        f.read(64)

        file_count = struct.unpack('<I', f.read(4))[0]
        print(f"Total files: {file_count}")

        # Read file index
        entries = []
        for _ in range(file_count):
            path_len = struct.unpack('<I', f.read(4))[0]
            raw_path = f.read(path_len)
            path = raw_path.rstrip(b'\x00').decode('utf-8', errors='replace')
            offset = struct.unpack('<Q', f.read(8))[0]
            size = struct.unpack('<Q', f.read(8))[0]
            md5 = f.read(16)
            entries.append((path, offset, size))

        # Extract files
        extracted = 0
        skipped = 0
        for path, offset, size in entries:
            # Strip res:// prefix
            rel_path = path
            if rel_path.startswith('res://'):
                rel_path = rel_path[6:]

            # Filter by extension
            if filter_ext:
                ext = os.path.splitext(rel_path)[1].lower()
                if ext not in filter_ext:
                    skipped += 1
                    continue

            out_path = os.path.join(output_dir, rel_path.replace('/', os.sep))
            os.makedirs(os.path.dirname(out_path), exist_ok=True)

            f.seek(offset)
            data = f.read(size)

            with open(out_path, 'wb') as out_f:
                out_f.write(data)
            extracted += 1

            if extracted % 500 == 0:
                print(f"  Extracted {extracted} files...")

        print(f"Done: extracted {extracted} files, skipped {skipped}")
        return entries


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Extract Godot 3.x .pck files')
    parser.add_argument('pck', help='Path to .pck file')
    parser.add_argument('-o', '--output', default='extracted', help='Output directory')
    parser.add_argument('-e', '--ext', nargs='*', help='Filter by extension (e.g. .tscn .tres .gde)')
    args = parser.parse_args()

    filter_ext = None
    if args.ext:
        filter_ext = [e if e.startswith('.') else f'.{e}' for e in args.ext]

    extract_pck(args.pck, args.output, filter_ext)
