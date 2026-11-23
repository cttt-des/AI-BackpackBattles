"""Prepare the scoped archive without uploading an unfinished candidate."""
import ast
import re
from pathlib import Path

STAGE=Path(__file__).resolve().parent
SCRIPTS=('prepare_native_literal_spans.py','build_native_literal_spans.py','test_native_literal_spans.cpp',
    'verify_native_literal_spans.py','probe_native_literal_spans.py','prototype_native_literal_spans_bundle.py',
    'setup_literal_spans_bundle.py','preflight_native_literal_spans.py','run_literal_spans_formal.py',
    'close_literal_spans_round.py','archive_literal_spans_round.py','setup_literal_spans_archive.py')

def main():
    text=(STAGE/'archive_storage_round.py').read_text('utf8')
    text=text.replace('storage_bundle','literal_spans_bundle').replace('storage_prototype','literal_spans_prototype')
    text=text.replace('8e6ef3449e7a5a26d9d3fc7f268e380fbc7694fe','8c40f0b1b2cbb1ce5227f69757f89eca3bbc644a')
    text=re.sub(r'^SCRIPTS=.*$', 'SCRIPTS='+repr(SCRIPTS),text,flags=re.M)
    text=text.replace("    paths.add(STAGE/'finalize_storage_evidence.py')\n",'')
    text=text.replace("STAGE/'native_perf50/event_factory_bundle/checkpoint_receipt.json'", "STAGE/'native_perf50/storage_bundle/checkpoint_receipt.json'")
    text=text.replace('storage-backup-20261123','literal-spans-backup-20261123')
    text=text.replace('native-storage-backup-','native-literal-spans-backup-')
    text=text.replace('preserve independent storage coallocation evaluation','preserve independent literal event span evaluation')
    text=text.replace('preserve storage trials with actual production runtime','preserve literal span trials with actual production runtime')
    ast.parse(text)
    path=STAGE/'archive_literal_spans_round.py';assert not path.exists()
    path.write_text(text,encoding='utf8',newline='\n')
    print('Prepared scoped archive; use only after final outcome')

if __name__=='__main__':main()
