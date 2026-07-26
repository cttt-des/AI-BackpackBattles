"""
Analyze project.binary ECFG format properly.
Godot 3.x ConfigFile binary format uses sections, not flat entries.

Format:
  4 bytes: "ECFG"
  4 bytes: number of sections
  For each section:
    4 bytes: section name length (padded to 4)
    section name bytes (padded to 4 bytes)
    4 bytes: number of keys
    For each key:
      4 bytes: key name length (padded to 4)
      key name bytes (padded to 4)
      4 bytes: variant type (uint32)
      variant data

Variant types:
  0=nil, 1=bool(4B), 2=int(4B), 3=float(4B), 4=string(len+data),
  5=Vector2(8B), 12=Color(16B), 14=Dictionary, 17=NodePath,
  18=PackedByteArray, 19=Array, 20=PackedInt32Array, 21=PackedFloat32Array,
  26=PackedVector2Array, 39=PackedInt64Array
"""
import struct

proj_path = 'D:/文件资料/学习/自动背包AI/extracted/project.binary'

with open(proj_path, 'rb') as f:
    data = f.read()

print(f"Total size: {len(data)} bytes")
print(f"\n=== HEADER ===")
print(f"Magic: {data[:4]}")

pos = 4
num_sections_raw = struct.unpack('<I', data[pos:pos+4])[0]
pos += 4
print(f"Num sections: {num_sections_raw}")
print(f"Try interpreting as {num_sections_raw} sections...")

def read_padded_string(data, pos):
    """Read a 4-byte length prefix + string + 4-byte padding."""
    if pos + 4 > len(data):
        return None, pos
    strlen = struct.unpack('<I', data[pos:pos+4])[0]
    pos += 4
    if strlen == 0 or pos + strlen > len(data):
        return None, pos
    s = data[pos:pos+strlen].decode('utf-8', errors='replace')
    pos += strlen
    # Pad to 4-byte boundary
    pad = (4 - (strlen % 4)) % 4
    pos += pad
    return s, pos

def read_variant(data, pos):
    """Read a variant value, return (value_str, new_pos)."""
    if pos + 4 > len(data):
        return ('<EOF>', pos)
    var_type = struct.unpack('<I', data[pos:pos+4])[0]
    pos += 4
    
    if var_type == 0:  # nil
        return ('null', pos)
    elif var_type == 1:  # bool
        v = struct.unpack('<I', data[pos:pos+4])[0] != 0
        pos += 4
        return (str(v).lower(), pos)
    elif var_type == 2:  # int
        v = struct.unpack('<I', data[pos:pos+4])[0]
        pos += 4
        return (str(v), pos)
    elif var_type == 3:  # float
        v = struct.unpack('<f', data[pos:pos+4])[0]
        pos += 4
        return (f"{v:.3f}", pos)
    elif var_type == 4:  # string
        s, pos = read_padded_string(data, pos)
        return (f'"{s}"' if s else '""', pos)
    elif var_type == 5:  # Vector2
        x, y = struct.unpack('<ff', data[pos:pos+8])
        pos += 8
        return (f"Vector2({x},{y})", pos)
    elif var_type == 12:  # Color
        r, g, b, a = struct.unpack('<ffff', data[pos:pos+16])
        pos += 16
        return (f"Color({r},{g},{b},{a})", pos)
    elif var_type == 17:  # NodePath
        s, pos = read_padded_string(data, pos)
        return (f"NodePath({s})" if s else 'NodePath("")', pos)
    else:
        return (f"<type={var_type}>", pos)

# Parse sections
autoload_found = {}
section_sizes = {}
parsed_sections = 0

for sec_idx in range(min(num_sections_raw, 500)):
    section_start = pos
    if pos >= len(data):
        break
    
    # Read section name
    sec_name, pos = read_padded_string(data, pos)
    if sec_name is None:
        print(f"Failed to read section name at pos={pos}")
        break
    
    if pos + 4 > len(data):
        break
    
    num_keys = struct.unpack('<I', data[pos:pos+4])[0]
    pos += 4
    
    if num_keys > 10000:
        print(f"Section '{sec_name}': bad num_keys={num_keys} at pos={pos}")
        break
    
    # Print section header
    if sec_idx < 10 or 'autoload' in sec_name.lower() or 'application' in sec_name.lower() or 'display' in sec_name.lower() or 'input' in sec_name.lower():
        print(f"\n--- Section [{sec_idx}] '{sec_name}' ({num_keys} keys) ---")
    
    for key_idx in range(num_keys):
        key_start = pos
        key_name, pos = read_padded_string(data, pos)
        if key_name is None:
            print(f"  Failed to read key name at pos={pos}")
            break
        
        value_str, pos = read_variant(data, pos)
        
        if 'autoload' in sec_name.lower():
            autoload_found[key_name] = value_str
            print(f"  {sec_name}/{key_name} = {value_str}")
            # Also print the raw bytes for this entry
            raw = data[key_start:pos]
            print(f"    raw({len(raw)}): {raw.hex()}")
        elif sec_idx < 10 or 'application' in sec_name.lower() or 'display' in sec_name.lower() or 'input' in sec_name.lower() or 'window' in sec_name.lower():
            if key_idx < 10:
                print(f"  {key_name} = {value_str}")
    
    section_sizes[sec_name] = pos - section_start
    parsed_sections += 1

print(f"\n=== Summary ===")
print(f"Parsed {parsed_sections}/{num_sections_raw} sections")
print(f"Final pos: {pos}/{len(data)} ({100*pos/len(data):.1f}%)")

if autoload_found:
    print(f"\n=== Autoload Entries ({len(autoload_found)}) ===")
    for k, v in autoload_found.items():
        print(f"  {k} = {v}")
