"""Project-local disposable build workspaces on an ASCII D: path."""
import contextlib,functools,hashlib,json,os,re,shutil,tempfile,uuid
from pathlib import Path

ROOT=Path('D:/CodexNativeBuilds')
LEGACY=Path(os.environ.get('LOCALAPPDATA','C:/Users/Windows/AppData/Local'))/'CodexNativeBuilds'
STAGE=Path(__file__).resolve().parent
ARCHIVE=STAGE/'build_storage/archive'
SCRAP={'.o','.obj','.s','.i','.ii','.exe','.dll','.dylib','.pyd','.lib','.exp','.res','.gcno','.pch','.gch','.pyc'}
_mkdtemp=tempfile.mkdtemp
def sha(path):
    h=hashlib.sha256()
    with Path(path).open('rb') as stream:
        for data in iter(lambda:stream.read(4*1024*1024),b''):h.update(data)
    return h.hexdigest()
def checked(path,parent):
    path=Path(path).resolve();parent=Path(parent).resolve()
    if path.drive.upper()!='D:':raise ValueError('Build workspaces must resolve to D:')
    if path==parent or not path.is_relative_to(parent):raise ValueError(f'Outside owned build workspace: {path}')
    if not str(path).isascii():raise ValueError('Build workspace must have an ASCII path')
    return path
def activate():
    session=os.environ.get('NATIVE_BUILD_SESSION')
    if not session:return
    session=checked(session,ROOT/'work');session.mkdir(parents=True,exist_ok=True)
    tempfile.tempdir=str(session)
    if getattr(tempfile.mkdtemp,'_native_managed',False):return
    def managed_mkdtemp(suffix=None,prefix=None,dir=None):
        target=Path(dir).resolve() if dir is not None else session
        legacy=LEGACY.resolve()
        if target==legacy or target.is_relative_to(legacy):target=session
        return _mkdtemp(suffix=suffix,prefix=prefix,dir=str(target))
    managed_mkdtemp._native_managed=True;tempfile.mkdtemp=managed_mkdtemp
def archive_and_remove(path):
    path=checked(path,ROOT/'work')
    if not path.exists():return
    destination=ARCHIVE/path.name
    destination.mkdir(parents=True,exist_ok=True)
    rows=[];total=discarded=0
    for file in sorted(path.rglob('*')):
        if file.is_symlink() or file.is_junction():raise ValueError(f'Refuse linked build artifact: {file}')
        if not file.is_file():continue
        relative=file.relative_to(path);size=file.stat().st_size;total+=size
        if file.suffix.lower() in SCRAP or '__pycache__' in file.parts:
            discarded+=size;continue
        target=destination/relative;target.parent.mkdir(parents=True,exist_ok=True)
        shutil.copy2(file,target);digest=sha(file)
        if sha(target)!=digest:raise ValueError(f'Archive mismatch: {relative}')
        rows.append(dict(path=relative.as_posix(),sha256=digest,bytes=size))
    receipt=dict(workspace=str(path),archive=str(destination),preserved=rows,total_bytes=total,discarded_rebuildable_bytes=discarded,cleanup_complete=False)
    record=destination/'cleanup_receipt.json';record.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8')
    # Every retained source/log/data file was checked; compiled temporaries are
    # disposable. Exported DLLs and frozen PGO receipts live outside this tree.
    shutil.rmtree(checked(path,ROOT/'work'))
    receipt['cleanup_complete']=not path.exists();record.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8')
def reap_orphans():
    import psutil
    for path in (ROOT/'work').iterdir():
        if path.is_symlink() or path.is_junction():continue
        marker=path/'.native_owner.json'
        if not marker.is_file():continue
        owner=json.loads(marker.read_bytes())
        try:alive=abs(psutil.Process(owner['pid']).create_time()-owner['created'])<0.01
        except psutil.NoSuchProcess:alive=False
        except psutil.AccessDenied:alive=True
        if not alive:archive_and_remove(path)
@contextlib.contextmanager
def workspace(label):
    ROOT.mkdir(parents=True,exist_ok=True);(ROOT/'work').mkdir(exist_ok=True);reap_orphans()
    name=re.sub('[^a-zA-Z0-9_-]','-',label)+'-'+uuid.uuid4().hex[:12]
    path=checked(ROOT/'work'/name,ROOT/'work');path.mkdir()
    import psutil
    (path/'.native_owner.json').write_text(json.dumps(dict(pid=os.getpid(),created=psutil.Process().create_time())),encoding='utf8')
    names=('TEMP','TMP','TMPDIR','NATIVE_BUILD_SESSION','NATIVE_SIM_OBJ','PYTHONPATH')
    before={k:os.environ.get(k) for k in names};previous_temp=tempfile.tempdir;previous_mkdtemp=tempfile.mkdtemp
    hook=STAGE/'native_storage_hook'
    os.environ.update(TEMP=str(path),TMP=str(path),TMPDIR=str(path),NATIVE_BUILD_SESSION=str(path),NATIVE_SIM_OBJ=str(path/'objects'),PYTHONPATH=str(hook)+(os.pathsep+before['PYTHONPATH'] if before['PYTHONPATH'] else ''))
    tempfile.mkdtemp=_mkdtemp;activate()
    try:yield path
    finally:
        tempfile.tempdir=previous_temp;tempfile.mkdtemp=previous_mkdtemp
        for key,value in before.items():
            if value is None:os.environ.pop(key,None)
            else:os.environ[key]=value
        archive_and_remove(path)
def isolated_build(function):
    @functools.wraps(function)
    def run(*args,**kwargs):
        with workspace(function.__module__+'-'+function.__name__):return function(*args,**kwargs)
    return run
def frozen_flags(bundle,name,object_sha):
    """Use the verified object-option receipt, never require an old .o cache."""
    bundle=Path(bundle);receipt=json.loads((bundle/'compiled_option_receipt.json').read_bytes());manifest=json.loads((bundle/'release_objects.json').read_bytes())
    row=receipt['objects'][name];file=bundle/'compiled_options'/(Path(name).stem+'.txt')
    assert receipt['passed'] and receipt['dll_sha256']==manifest['dll_sha256']
    assert row['object_sha256']==manifest['objects_sha256'][name]==object_sha and sha(file)==row['options_sha256']
    flags=re.findall("'([^']*)'",file.read_text('utf8'));assert '-O3' in flags and '-ffp-contract=off' in flags and '-flto=2' in flags
    return flags
def adapt_formal_builder(text):
    old="        assert sha(old_root/name)==digest;actual[name]=sha(objects/name)"
    assert text.count(old)==1;text=text.replace(old,"        actual[name]=sha(objects/name)")
    old="        text,flags=options(objects/name);_,old_flags=options(old_root/name)"
    assert text.count(old)==1;text=text.replace(old,"        from native_build_storage import frozen_flags\n        text,flags=options(objects/name);old_flags=frozen_flags(ACCEPTED,name,digest)")
    return text
def clean_lto_parts(objects):
    objects=Path(objects).resolve()
    if not objects.is_relative_to((ROOT/'work').resolve()):return
    for file in objects.iterdir():
        if file.is_file() and (re.search(r'\.ltrans\d+(?:\.ltrans)?\.(?:o|s)$',file.name) or file.name.endswith(('.ltrans.out','.ltrans_args'))):file.unlink()
