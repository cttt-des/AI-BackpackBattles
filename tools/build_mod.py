"""
Build a modified BackpackBattles.pck with the Bridge autoload injected.

Steps:
1. Load the original .pck file
2. Add bridge.gd as a new file
3. Modify project.binary to add autoload/Bridge entry
4. Write the modified .pck
"""
import os
import sys

# Add tools directory to path for imports
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from pck_packer import load_pck, pack_pck
from modify_project import add_autoload


def build():
    base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    
    # Paths
    original_pck = os.path.join(base_dir, 'Backpack Battles', 'BackpackBattles.pck')
    bridge_gd_path = os.path.join(base_dir, 'bridge', 'bridge.gd')
    project_binary_path = os.path.join(base_dir, 'extracted', 'project.binary')
    output_pck = os.path.join(base_dir, 'Backpack Battles', 'BackpackBattles.mod.pck')
    
    # 1. Load original .pck
    print(f"Loading original .pck: {original_pck}")
    files = load_pck(original_pck)
    print(f"  Found {len(files)} files in .pck")
    
    # 2. Add bridge.gd
    print(f"\nAdding bridge.gd...")
    with open(bridge_gd_path, 'rb') as f:
        bridge_data = f.read()
    files['res://bridge.gd'] = bridge_data
    print(f"  bridge.gd: {len(bridge_data)} bytes")
    
    # 3. Modify project.binary
    print(f"\nModifying project.binary...")
    
    # First, save the current project.binary from .pck
    if 'res://project.binary' in files:
        current_pb = files['res://project.binary']
    else:
        print("  ERROR: project.binary not found in .pck!")
        print("  Using extracted version...")
        with open(project_binary_path, 'rb') as f:
            current_pb = f.read()
    
    # Modify in memory
    import struct
    data = bytearray(current_pb)
    
    # Parse entries to find insertion point
    num_entries = struct.unpack('<I', data[4:8])[0]
    pos = 8
    last_autoload_end = 8
    
    for i in range(num_entries):
        key_len = struct.unpack('<I', data[pos:pos+4])[0]
        key_str = data[pos+4:pos+4+key_len].decode('utf-8', errors='replace')
        var_size = struct.unpack('<I', data[pos+4+key_len:pos+4+key_len+4])[0]
        entry_size = 4 + key_len + 4 + var_size
        
        if key_str.startswith('autoload/'):
            last_autoload_end = pos + entry_size
            print(f"  Found autoload: {key_str}")
        
        pos += entry_size
    
    # Build new entry for Bridge
    new_key = 'autoload/Bridge'
    new_value = '*res://bridge.gd'
    new_key_bytes = new_key.encode('utf-8')
    new_value_bytes = new_value.encode('utf-8')
    
    var_raw_size = 4 + 4 + len(new_value_bytes)
    var_pad = (4 - (var_raw_size % 4)) % 4
    new_var_size = var_raw_size + var_pad
    
    # Build new entry bytes
    new_entry = struct.pack('<I', len(new_key_bytes))
    new_entry += new_key_bytes
    new_entry += struct.pack('<I', new_var_size)
    new_entry += struct.pack('<I', 4)  # type = STRING
    new_entry += struct.pack('<I', len(new_value_bytes))
    new_entry += new_value_bytes
    new_entry += b'\x00' * var_pad
    
    # Insert into data
    new_data = data[:last_autoload_end] + new_entry + data[last_autoload_end:]
    
    # Update entry count
    struct.pack_into('<I', new_data, 4, num_entries + 1)
    
    files['res://project.binary'] = bytes(new_data)
    print(f"  Added autoload/Bridge entry (total entries: {num_entries + 1})")
    
    # 4. Write modified .pck
    print(f"\nWriting modified .pck: {output_pck}")
    pack_pck(output_pck, files)
    print(f"\n=== Build Complete ===")
    print(f"Output: {output_pck}")
    print(f"To use: copy/rename {output_pck} to BackpackBattles.pck (backup original first!)")


if __name__ == '__main__':
    build()
