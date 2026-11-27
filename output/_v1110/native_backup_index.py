"""Stage literal backup paths in an isolated index and verify blobs in a stream."""
import os,re,subprocess
from pathlib import Path


def stage_files(repo,names,env):
    repo=Path(repo).resolve();index=Path(env['GIT_INDEX_FILE']).resolve()
    assert index!=repo/'.git/index' and index.is_relative_to(Path('D:/CodexNativeBuilds/work').resolve())
    assert len(names)==len(set(names))
    for name in names:
        assert name and not name.startswith(('"','/')) and not any(c in name for c in '\r\n\0')
        file=repo/name;assert file.is_file() and not file.is_symlink() and file.resolve().is_relative_to(repo)
    def git(*args,input=None):
        return subprocess.check_output(['git','-c','pack.threads=2',*args],cwd=repo,env=env,input=input)
    modes={}
    for entry in git('ls-files','--stage','-z').split(b'\0'):
        if not entry:continue
        header,name=entry.split(b'\t',1);mode,oid,stage=header.split();assert stage==b'0'
        modes[name.decode('utf8')]=mode
    hashes=git('hash-object','-w','--no-filters','--stdin-paths',input=''.join(n+'\n' for n in names).encode('utf8')).splitlines()
    assert len(hashes)==len(names) and all(re.fullmatch(rb'[0-9a-f]{40}|[0-9a-f]{64}',h) for h in hashes)
    rows=[]
    for name,oid in zip(names,hashes):
        mode=modes.get(name,b'100644');assert mode in (b'100644',b'100755')
        rows.append(mode+b' '+oid+b'\t'+name.encode('utf8')+b'\0')
    git('update-index','-z','--index-info',input=b''.join(rows))


def verify_tree_files(repo,commit,names):
    repo=Path(repo).resolve()
    process=subprocess.Popen(['git','-c','pack.threads=2','cat-file','--batch'],cwd=repo,stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    try:
        for name in names:
            assert not any(c in name for c in '\r\n\0')
            process.stdin.write((commit+':'+name+'\n').encode('utf8'));process.stdin.flush()
            header=process.stdout.readline().split();assert len(header)==3 and header[1]==b'blob',(name,header)
            remaining=int(header[2])
            with (repo/name).open('rb') as file:
                while remaining:
                    blob=process.stdout.read(min(1024*1024,remaining));assert blob and blob==file.read(len(blob)),name
                    remaining-=len(blob)
                assert file.read(1)==b'',name
            assert process.stdout.read(1)==b'\n'
        process.stdin.close();assert process.wait(timeout=30)==0,process.stderr.read()
    finally:
        if process.poll() is None:process.kill();process.wait(timeout=10)
        for stream in (process.stdin,process.stdout,process.stderr):
            if not stream.closed:stream.close()
