"""Prepare fresh semantic build and retain every prior differential fixture."""
import ast
from prepare_native_identity_lookup import STAGE

def save(name,text):
    ast.parse(text,filename=name);p=STAGE/name;assert not p.exists();p.write_text(text,encoding='utf8',newline='\n')

def main():
    text=(STAGE/'build_native_container_builtins.py').read_text('utf8')
    text=text.replace('prepare_native_container_builtins','prepare_native_identity_lookup').replace('container-builtins-semantic-','identity-lookup-semantic-')
    save('build_native_identity_lookup.py',text)
    for old,new in [('verify_native_container_builtins.py','verify_identity_lookup_builtins.py'),
        ('verify_container_builtin_truth.py','verify_identity_lookup_truth.py'),('verify_container_builtin_private.py','verify_identity_lookup_private.py'),
        ('verify_container_builtin_display.py','verify_identity_lookup_display.py'),('verify_container_builtin_control.py','verify_identity_lookup_control.py')]:
        save(new,(STAGE/old).read_text('utf8').replace('prepare_native_container_builtins','prepare_native_identity_lookup'))
    print('Prepared build and all retained semantic adapters',flush=True)

if __name__=='__main__':main()
