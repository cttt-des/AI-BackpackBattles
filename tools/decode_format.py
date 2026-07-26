"""
Final ECFG format decoder. Format:
[4B: "ECFG"][4B: num_entries][entries...]

Each entry:
[4B: key_len][key_string][4B: total_variant_size][variant_data(total_variant_size bytes)]

Variant is store_var(value, full=true):
- Each variant starts with [4B: variant_type]
- STRING(4): [4B: string_len][string_bytes][padding to 4B]
- INT(2): [4B: int_value]
- etc.
"""
import struct

with open('D:/文件资料/学习/自动背包AI/extracted/project.binary', 'rb') as f:
    data = f.read()

pos = 4
num_entries = struct.unpack('<I', data[pos:pos+4])[0]
pos += 4
print(f"Num entries: {num_entries}")

entries = {}
for i in range(num_entries):
    if pos + 4 > len(data):
        print(f"\nEntry {i}: EOF")
        break
    
    key_len = struct.unpack('<I', data[pos:pos+4])[0]
    pos += 4
    if key_len > 500 or key_len == 0 or pos + key_len > len(data):
        print(f"\nEntry {i}: bad key_len={key_len}")
        break
    
    key = data[pos:pos+key_len].decode('utf-8', errors='replace')
    pos += key_len
    
    if pos + 4 > len(data):
        break
    
    var_size = struct.unpack('<I', data[pos:pos+4])[0]
    pos += 4
    
    if var_size > 100000 or pos + var_size > len(data):
        print(f"\nEntry {i}: bad var_size={var_size} for key='{key}'")
        break
    
    variant_raw = data[pos:pos+var_size]
    pos += var_size
    
    if len(variant_raw) < 4:
        value = "<too_short>"
    else:
        vartype = struct.unpack('<I', variant_raw[0:4])[0]
        
        if vartype == 4:  # string
            if len(variant_raw) < 8:
                value = "<bad_string>"
            else:
                strlen = struct.unpack('<I', variant_raw[4:8])[0]
                value = variant_raw[8:8+strlen].decode('utf-8', errors='replace')
        elif vartype == 2:  # int
            value = struct.unpack('<i', variant_raw[4:8])[0]
        elif vartype == 1:  # bool
            value = variant_raw[4] != 0
        elif vartype == 3:  # float
            value = struct.unpack('<f', variant_raw[4:8])[0]
        elif vartype == 0:  # nil
            value = None
        else:
            value = f"<type={vartype}, {len(variant_raw)} bytes>"
    
    entries[key] = value
    
    if 'autoload' in key or i < 5 or i == num_entries - 1:
        vp = str(value)[:80] if value else str(value)
        print(f"  [{i:03d}] {key} = {vp}  (var_size={var_size})")

print(f"\nParsed {len(entries)}/{num_entries} entries")
print(f"Final pos: {pos}/{len(data)} ({100*pos/len(data):.1f}%)")

# Extract autoload entries
print(f"\n=== Autoload Entries ===")
for k, v in sorted(entries.items()):
    if 'autoload' in k:
        print(f"  {k} = {v}")
