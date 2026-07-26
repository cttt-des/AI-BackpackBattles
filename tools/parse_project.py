"""
Parse Godot 3.x project.binary (ECFG format) to extract project settings.
Focus on: autoloads, class registry, display settings, etc.
"""
import struct
import re

proj_path = 'D:/文件资料/学习/自动背包AI/extracted/project.binary'
with open(proj_path, 'rb') as f:
    data = f.read()

print(f"project.binary: {len(data)} bytes")
print(f"Magic: {data[:4]}")  # ECFG

# The ECFG format is a serialized ConfigFile
# Format:
# 4 bytes: "ECFG" magic
# 4 bytes: number of sections or entries
# Then for each entry: key-value pairs

# Let's find all readable strings and look for patterns
strings = re.findall(b'[\x20-\x7e]{3,}', data)
all_strings = [s.decode('ascii', errors='replace') for s in strings]

# Find autoload-related strings
print("\n=== Autoload-related strings ===")
for i, s in enumerate(all_strings):
    if 'autoload' in s.lower():
        # Print context
        print(f"  [{i}] {s}")
        # Print next few strings for context
        for j in range(1, 4):
            if i + j < len(all_strings):
                print(f"       +{j}: {all_strings[i+j]}")

# Find class registry entries (path = res://...)
print("\n=== Class Registry (Items) ===")
for i, s in enumerate(all_strings):
    if s.startswith('res://Items/') or s.startswith('res://Core/'):
        # Print with context
        context = []
        for j in range(-2, 5):
            if 0 <= i + j < len(all_strings):
                context.append(all_strings[i+j])
        print(f"  {s}")
        # Look for base class
        for j in range(1, 6):
            if i + j < len(all_strings):
                if all_strings[i+j] in ['Item', 'Weapon', 'Armor', 'Consumable', 'Reference', 'Node', 'Resource', 'Area2D']:
                    print(f"    base: {all_strings[i+j]}")
                    break

# Find display/settings strings
print("\n=== Display/Application Settings ===")
for i, s in enumerate(all_strings):
    if any(x in s.lower() for x in ['display', 'application', 'rendering', 'physics', 'input', 'layer_names', 'window']):
        print(f"  [{i}] {s}")
        if i + 1 < len(all_strings):
            print(f"       = {all_strings[i+1]}")

# Find all res:// paths (these are script/scene paths)
print("\n=== All res:// paths ===")
res_paths = sorted(set(s for s in all_strings if s.startswith('res://') and s.endswith('.gd')))
for p in res_paths[:50]:
    print(f"  {p}")
print(f"  ... total: {len(res_paths)} .gd paths")

# Parse the ECFG format properly
print("\n=== Parsing ECFG format ===")
pos = 4  # Skip "ECFG" magic

# Read the config file format
# In Godot 3.x, the binary config file format is:
# 4 bytes: magic "ECFG"
# 4 bytes: number of entries
# For each entry:
#   4 bytes: key string length
#   key string (padded to 4 bytes)
#   4 bytes: variant type
#   variant data

num_entries = struct.unpack('<I', data[pos:pos+4])[0]
pos += 4
print(f"Number of entries: {num_entries}")

# Try to parse entries
entries = {}
for i in range(min(num_entries, 200)):
    if pos + 4 > len(data):
        break
    
    key_len = struct.unpack('<I', data[pos:pos+4])[0]
    pos += 4
    
    if key_len > 1000 or pos + key_len > len(data):
        print(f"  Entry {i}: invalid key length {key_len} at pos {pos}")
        break
    
    key = data[pos:pos+key_len].decode('utf-8', errors='replace')
    pos += key_len
    
    # Pad to 4-byte boundary
    pad = (4 - (key_len % 4)) % 4
    pos += pad
    
    if pos + 4 > len(data):
        break
    
    var_type = struct.unpack('<I', data[pos:pos+4])[0]
    pos += 4
    
    # Parse variant based on type
    # Godot variant types: 0=null, 1=bool, 2=int, 3=float, 4=string, 5=Vector2, etc.
    value = None
    if var_type == 0:  # nil
        value = None
    elif var_type == 1:  # bool
        value = struct.unpack('<I', data[pos:pos+4])[0] != 0
        pos += 4
    elif var_type == 2:  # int
        value = struct.unpack('<I', data[pos:pos+4])[0]
        pos += 4
    elif var_type == 3:  # float
        value = struct.unpack('<f', data[pos:pos+4])[0]
        pos += 4
    elif var_type == 4:  # string
        str_len = struct.unpack('<I', data[pos:pos+4])[0]
        pos += 4
        value = data[pos:pos+str_len].decode('utf-8', errors='replace')
        pos += str_len
        pad = (4 - (str_len % 4)) % 4
        pos += pad
    else:
        # Skip unknown types - try to find next entry
        value = f"<type {var_type}>"
        # Try to read as string (common case)
        try:
            str_len = struct.unpack('<I', data[pos:pos+4])[0]
            if 0 < str_len < 1000 and pos + 4 + str_len <= len(data):
                value = data[pos+4:pos+4+str_len].decode('utf-8', errors='replace')
                pos += 4 + str_len
                pad = (4 - (str_len % 4)) % 4
                pos += pad
            else:
                pos += 4
        except:
            pos += 4
    
    entries[key] = (var_type, value)
    
    # Print autoload entries
    if 'autoload' in key.lower():
        print(f"  AUTOLOAD: {key} = {value}")

# Print all entries
print(f"\n=== All parsed entries ({len(entries)}) ===")
for key in sorted(entries.keys()):
    var_type, value = entries[key]
    if len(str(value)) < 200:
        print(f"  [{var_type}] {key} = {value}")
    else:
        print(f"  [{var_type}] {key} = {str(value)[:100]}...")
