"""Prepare a scoped archive for the callback candidate and its cost probes."""
import ast
import re
from pathlib import Path

STAGE=Path(__file__).resolve().parent
SCRIPTS=('probe_native_bound_arguments.py','prepare_native_callback_dispatch.py','build_native_callback_dispatch.py',
    'test_native_callback_dispatch.cpp','verify_native_callback_dispatch.py','probe_native_callback_arrays.py',
    'probe_native_object_callbacks.py','prototype_native_callback_dispatch_bundle.py','setup_callback_dispatch_bundle.py',
    'preflight_native_callback_dispatch.py','run_callback_dispatch_formal.py','close_callback_dispatch_round.py',
    'archive_callback_dispatch_round.py','setup_callback_dispatch_archive.py','analyze_native_dispatch.py','repair_callback_validation_harness.py','repair_callback_validation_harness_2.py','resume_callback_dispatch_validation.py','review_callback_dispatch_release.py','record_callback_dispatch_deployment.py')

def main():
    text=(STAGE/'archive_literal_spans_round.py').read_text('utf8')
    text=text.replace('literal_spans_bundle','callback_dispatch_bundle').replace('literal_spans_prototype','callback_dispatch_prototype')
    text=text.replace('8c40f0b1b2cbb1ce5227f69757f89eca3bbc644a','a27d289f2009c3ad42145d61334d50647b2c060f')
    text=text.replace('d8a7365191ad57a48ac378a7db77e8587169814f6f74298734f7d0b4786e3a76','c46cc19c06fb3c424a470f04bb7a0ef5acf8b7ff01caaccd5f41a5c44d955ee1')
    text=re.sub(r'^SCRIPTS=.*$','SCRIPTS='+repr(SCRIPTS),text,flags=re.M)
    text=text.replace("(WORK,WORK.parent/'callback_dispatch_prototype')", "(WORK,WORK.parent/'callback_dispatch_prototype',WORK.parent/'bound_callbacks_prototype')")
    text=text.replace("STAGE/'native_perf50/storage_bundle/checkpoint_receipt.json'", "STAGE/'native_perf50/literal_spans_bundle/checkpoint_receipt.json'")
    text=text.replace('literal-spans-backup-20261123','callback-dispatch-backup-20261123')
    text=text.replace('native-literal-spans-backup-','native-callback-dispatch-backup-')
    text=text.replace('preserve independent literal event span evaluation','preserve exact-type callback dispatch evaluation')
    text=text.replace('preserve literal span trials with actual production runtime','preserve callback dispatch trials with actual production runtime')
    ast.parse(text)
    out=STAGE/'archive_callback_dispatch_round.py';assert not out.exists()
    out.write_text(text,encoding='utf8',newline='\n')
    print('Prepared archive for final callback outcome; unfinished candidate not uploaded')

if __name__=='__main__':main()
