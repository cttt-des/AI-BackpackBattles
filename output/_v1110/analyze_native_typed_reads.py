"""Prove typed field bindings without modifying simulation source."""
import hashlib
import json
from pathlib import Path
import re

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'native_perf50/hot_coverage_bundle'
SHA='401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259'


def analyze(native):
    previous=json.loads((BASE/'transform.json').read_bytes())
    parents={};declared={}
    for path in sorted((native/'gen/hdrs').glob('*.hpp')):
        match=re.search(r'^struct (Gd__\w+) : public ([\w:]+) \{',path.read_text('utf8'),re.M)
        if match:parents[match[1]]=match[2];declared[match[1]]=set(re.findall(r'\bgd::GdVal (f_\w+);',path.read_text('utf8')))
    assert len(parents)==674
    def ancestors(cls):
        result=[]
        while cls in parents:
            assert cls not in result;result.append(cls);cls=parents[cls]
        assert cls=='gd::GdObj'
        return result
    ancestry={cls:ancestors(cls) for cls in parents}
    def field_owner(cls,field):
        return next((owner for owner in ancestry[cls] if field in declared[owner]),None)
    source='\n'.join(path.read_text('utf8') for path in sorted((native/'gen/shards').glob('*.cpp')))
    pure={}
    for match in re.finditer(r'^gd::GdVal (Gd__\w+)::fn_(\w+)\([^\n]*\n(.*?)^\}',source,re.M|re.S):
        cls,name,body=match[1],match[2],match[3]
        body=re.sub(r'^\s*gd::BattleCtx& gd_ctx = \*this->rt_ctx_;\s*','',body)
        field=re.fullmatch(r'\s*return this->(f_\w+);\s*(?:return gd::GdVal::null\(\);\s*)?',body)
        if not field:continue
        owner=field_owner(cls,field[1]);assert owner,(cls,name,field[1])
        pure[(cls,name)]=(owner,field[1])
    header=(native/'native_inline_dispatch.hpp').read_text('utf8')
    start=header.index('inline constexpr auto native_resolved_slots=')
    end=header.index('    return value; }();',start)
    methods=[symbol for symbol,index in re.findall(r'value\[([\w:]+)\]=(\d+);',header[start:end])]
    assert len(methods)==128
    dispatch=(native/'native_resolved_dispatch.hpp').read_text('utf8')
    rows=re.findall(r'^    \{&META_(Gd__\w+),&native_property_rows\[(\d+)\],(\d+)ULL,\{(.*?)\}\},$',dispatch,re.M)
    assert len(rows)==674
    bindings={};original_cells={}
    for index,(cls,pid,mask,values) in enumerate(rows):
        assert previous['class_rows'][cls]==index and previous['class_property_rows'][cls]==int(pid)
        cells=re.findall(r'&native_resolved_invoke<(Gd__\w+), &(Gd__\w+)::fn_(\w+)>|\b(nullptr)\b',values)
        assert len(cells)==128
        original_cells[cls]=values
        row=[]
        for owner,method_owner,method,null in cells:
            if null:row.append(None);continue
            assert owner==method_owner and owner in ancestry[cls]
            value=pure.get((owner,method))
            if value:assert value[0] in ancestry[cls]
            row.append(value)
        bindings[cls]=row
    property_bindings=[]
    for column in range(64):
        values=sorted({tuple(row[column]) for row in previous['property_rows'] if row[column]})
        assert 0<len(values)<256
        for owner,field in values:assert field in declared[owner]
        property_bindings.append(values)
    method_slots=[slot for slot in range(128) if any(row[slot] for row in bindings.values())]
    method_bindings=[]
    for slot in method_slots:
        values=sorted({row[slot] for row in bindings.values() if row[slot]})
        assert 0<len(values)<256;method_bindings.append(values)
    assert 0<len(method_slots)<=128
    property_tags={};method_tags={};read_rows={};classes={}
    for cls in sorted(parents):
        old_id=previous['class_property_rows'][cls]
        fields=previous['property_rows'][old_id]
        tags=tuple(property_bindings[i].index(tuple(value))+1 if value else 0 for i,value in enumerate(fields))
        mtags=tuple(method_bindings[i].index(bindings[cls][slot])+1 if bindings[cls][slot] else 0 for i,slot in enumerate(method_slots))
        for value in fields:
            if value:assert value[0] in ancestry[cls]
        property_tags[cls]=tags;method_tags[cls]=mtags
        key=(old_id,tags,mtags)
        if key not in read_rows:read_rows[key]=len(read_rows)
        classes[cls]=read_rows[key]
    return {'baseline_dll_sha256':SHA,'generated_classes':674,'method_slots':128,'property_slots':64,
        'method_symbols':methods,'pure_method_slots':method_slots,
        'pure_method_symbols':[methods[slot] for slot in method_slots],
        'pure_method_bindings':method_bindings,'property_symbols':[row['symbol'] for row in previous['selected_properties']],
        'property_bindings':property_bindings,'class_read_rows':classes,
        'read_rows':[{'getter_row':key[0],'property_tags':list(key[1]),'method_tags':list(key[2])} for key in read_rows],
        'class_method_bindings':bindings,'original_method_cells':original_cells,
        'class_ancestors':ancestry,'source_pure_functions':len(pure),'source_original_getters_retained':True,
        'source_proof_scope':'Only a context-reference declaration and a direct GdVal field return, with optional unreachable Null return; no argument reads, callbacks, numerical operations or RNG.',
        'implementation_plan':'Per-symbol typed switches, compact property/method tags, shared original getter table; exact cache validation and every original fallback retained.'}


def main():
    native=STAGE/'sim_native/native_sim_cpp/native_sim'
    assert hashlib.sha256((native/'libgdcore.dll').read_bytes()).hexdigest()==SHA
    result=analyze(native);out=STAGE/'native_perf50/typed_read_bundle/source_design.json'
    assert not out.exists();out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps({key:result[key] for key in ('generated_classes','source_pure_functions','pure_method_symbols')},indent=2))
    print(f'{len(result["read_rows"])} compact read rows, {sum(map(len,result["property_bindings"]))} property bindings, {sum(map(len,result["pure_method_bindings"]))} pure method bindings')


if __name__=='__main__':main()
