"""
Godot 3.x .pck file packer.
Creates a .pck file from a list of files.
"""
import struct
import hashlib
import os


def pack_pck(output_path: str, files: dict):
    """Create a Godot 3.x .pck file.

    Args:
        output_path: Path to the output .pck file.
        files: Dictionary of {res_path: file_data_bytes}.
               res_path should start with "res://".
    """
    file_count = len(files)
    
    with open(output_path, 'wb') as f:
        # Header
        f.write(b'GDPC')  # magic
        f.write(struct.pack('<I', 1))  # pack version
        f.write(struct.pack('<I', 3))  # engine major
        f.write(struct.pack('<I', 6))  # engine minor
        f.write(struct.pack('<I', 0))  # engine patch
        
        # 16 reserved uint32s (64 bytes of zeros)
        f.write(b'\x00' * 64)
        
        # File count
        f.write(struct.pack('<I', file_count))
        
        # Calculate file offsets
        # Header size: 4 + 4 + 4 + 4 + 4 + 64 + 4 = 88 bytes
        # Index entry size: 4 + padded_path + 8 + 8 + 16 = 36 + padded_path
        header_size = 88
        
        # Calculate index size
        index_size = 0
        for path in files:
            path_bytes = path.encode('utf-8') + b'\x00'
            # Pad to 4-byte boundary
            padded_len = (len(path_bytes) + 3) & ~3
            # Entry: 4 (path_len) + padded_path + 8 (offset) + 8 (size) + 16 (md5)
            index_size += 4 + padded_len + 8 + 8 + 16
        
        data_start = header_size + index_size
        
        # Write file index
        current_offset = data_start
        file_entries = []
        for path, data in files.items():
            path_bytes = path.encode('utf-8') + b'\x00'
            padded_len = (len(path_bytes) + 3) & ~3
            padded_path = path_bytes + b'\x00' * (padded_len - len(path_bytes))
            
            md5 = hashlib.md5(data).digest()
            
            # Path length (including null terminator, padded)
            f.write(struct.pack('<I', padded_len))
            f.write(padded_path)
            # Offset
            f.write(struct.pack('<Q', current_offset))
            # Size
            f.write(struct.pack('<Q', len(data)))
            # MD5
            f.write(md5)
            
            file_entries.append((path, data, current_offset))
            current_offset += len(data)
        
        # Write file data
        for path, data, offset in file_entries:
            assert f.tell() == offset, f"Offset mismatch for {path}: expected {offset}, got {f.tell()}"
            f.write(data)
    
    print(f"Packed {file_count} files into {output_path} ({current_offset} bytes)")


def load_pck(pck_path: str) -> dict:
    """Load all files from a Godot 3.x .pck file.
    
    Returns:
        Dictionary of {res_path: file_data_bytes}.
    """
    files = {}
    with open(pck_path, 'rb') as f:
        magic = f.read(4)
        assert magic == b'GDPC', f"Invalid magic: {magic}"
        
        f.read(4)  # pack version
        f.read(4)  # engine major
        f.read(4)  # engine minor
        f.read(4)  # engine patch
        f.read(64)  # reserved
        
        file_count = struct.unpack('<I', f.read(4))[0]
        
        # Read index
        entries = []
        for _ in range(file_count):
            path_len = struct.unpack('<I', f.read(4))[0]
            path = f.read(path_len).rstrip(b'\x00').decode('utf-8', errors='replace')
            offset = struct.unpack('<Q', f.read(8))[0]
            size = struct.unpack('<Q', f.read(8))[0]
            md5 = f.read(16)
            entries.append((path, offset, size))
        
        # Read file data
        for path, offset, size in entries:
            f.seek(offset)
            files[path] = f.read(size)
    
    return files
