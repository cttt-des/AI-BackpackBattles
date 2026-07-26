"""
Modify project.binary to add an autoload entry for the Bridge script.

ECFG binary format:
  [4B: "ECFG"][4B: num_entries]
  For each entry:
    [4B: key_len][key_string][4B: total_variant_size][variant_data(total_variant_size bytes)]
  
  Variant for string (type 4):
    [4B: type=4][4B: string_len][string_bytes][padding to 4B]
"""
import struct
import os


def add_autoload(project_path: str, key: str, value: str, insert_after: str = None) -> bytes:
    """Add an autoload entry to project.binary.
    
    Args:
        project_path: Path to project.binary file.
        key: Autoload key name (e.g. "autoload/Bridge").
        value: Autoload value (e.g. "*res://bridge.gd").
        insert_after: If set, insert after this key (sorted by existing entries).
                      If None, appends after the last autoload entry.
    
    Returns:
        Modified binary data.
    """
    with open(project_path, 'rb') as f:
        data = bytearray(f.read())
    
    # Read existing entry count
    num_entries = struct.unpack('<I', data[4:8])[0]
    
    # Parse all entries to find insertion point
    pos = 8
    entries = []
    for i in range(num_entries):
        key_len = struct.unpack('<I', data[pos:pos+4])[0]
        pos += 4
        key_str = data[pos:pos+key_len].decode('utf-8', errors='replace')
        pos += key_len
        
        var_size = struct.unpack('<I', data[pos:pos+4])[0]
        pos += 4
        pos += var_size
        
        entries.append((key_str, var_size))
    
    # Find insertion point: right after the last autoload entry
    if insert_after:
        insert_idx = None
        for i, (k, _) in enumerate(entries):
            if k == insert_after:
                insert_idx = i
                break
        if insert_idx is None:
            raise ValueError(f"Key '{insert_after}' not found in project.binary")
        insert_pos = 8
        for _, (_, var_size) in enumerate(entries[:insert_idx + 1]):
            insert_pos += 4 + len(entries[_][0].encode('utf-8')) + 4 + var_size
    else:
        # Find the last autoload entry position
        last_autoload_idx = None
        for i, (k, _) in enumerate(entries):
            if k.startswith('autoload/'):
                last_autoload_idx = i
        
        if last_autoload_idx is None:
            # No autoload entries exist, insert after the first few entries
            # (after _custom_features, _global_script_classes, _global_script_class_icons)
            last_autoload_idx = 2
        
        # Calculate insertion position: right after the last autoload entry
        insert_pos = 8
        for i in range(last_autoload_idx + 1):
            k, vs = entries[i]
            insert_pos += 4 + len(k.encode('utf-8')) + 4 + vs
    
    # Build new entry
    new_key_bytes = key.encode('utf-8')
    new_key_len = len(new_key_bytes)
    
    new_value_bytes = value.encode('utf-8')
    new_str_len = len(new_value_bytes)
    
    # Calculate variant size (type:4 + strlen:4 + string + padding)
    new_var_raw_size = 4 + 4 + new_str_len
    new_var_pad = (4 - (new_var_raw_size % 4)) % 4
    new_var_size = new_var_raw_size + new_var_pad
    
    # Build variant data
    variant_data = struct.pack('<I', 4)  # type = STRING
    variant_data += struct.pack('<I', new_str_len)
    variant_data += new_value_bytes
    variant_data += b'\x00' * new_var_pad
    
    # Build entry
    new_entry = struct.pack('<I', new_key_len)
    new_entry += new_key_bytes
    new_entry += struct.pack('<I', new_var_size)
    new_entry += variant_data
    
    # Insert into data
    new_data = data[:insert_pos] + new_entry + data[insert_pos:]
    
    # Update entry count
    new_num = num_entries + 1
    struct.pack_into('<I', new_data, 4, new_num)
    
    return bytes(new_data)


def main():
    project_path = 'D:/文件资料/学习/自动背包AI/extracted/project.binary'
    output_path = 'D:/文件资料/学习/自动背包AI/extracted/project.modified.binary'
    
    # Add Bridge autoload entry
    key = 'autoload/Bridge'
    value = '*res://bridge.gd'
    
    new_data = add_autoload(project_path, key, value)
    
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    with open(output_path, 'wb') as f:
        f.write(new_data)
    
    print(f"Added autoload entry: {key} = {value}")
    print(f"Written to: {output_path}")
    print(f"Size: {len(new_data)} bytes (was {os.path.getsize(project_path)} bytes)")


if __name__ == '__main__':
    main()
