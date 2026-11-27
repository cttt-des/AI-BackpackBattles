"""Compare batch staging with literal git-add, including bytes and file modes."""
import json,os,shutil,subprocess,stat
from pathlib import Path
import psutil
from native_build_storage import workspace,checked,ROOT
from native_backup_index import stage_files,verify_tree_files
from prepare_quiet_round import WORK,save


def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    with workspace('backup-index-fixture') as root:
        repo=root/'fixture';repo.mkdir()
        def git(*args,env=None):return subprocess.check_output(['git',*args],cwd=repo,env=env)
        git('init','--quiet')
        rows={'中文 文件.txt':b'a\r\nb\r\n','literal[abc].cpp':b'\0\1\xffbinary','runner.py':b'print(42)\n','keep.txt':b'unchanged'}
        for name,data in rows.items():(repo/name).write_bytes(data)
        env=dict(os.environ,GIT_INDEX_FILE=str(root/'reference-index'))
        git('--literal-pathspecs','-c','core.autocrlf=false','add','-f','--',*rows,env=env)
        git('update-index','--chmod=+x','runner.py',env=env)
        original=git('write-tree',env=env).decode().strip();before=git('ls-files','--stage','-z',env=env)
        fast=dict(os.environ,GIT_INDEX_FILE=str(root/'batch-index'))
        git('read-tree',original,env=fast)
        stage_files(repo,list(rows),fast);assert git('write-tree',env=fast).decode().strip()==original
        assert git('ls-files','--stage','-z',env=env)==before
        (repo/'中文 文件.txt').write_bytes(b'changed\r\n')
        (repo/'new file.json').write_bytes(b'{"ok":true}')
        selected=['中文 文件.txt','new file.json','literal[abc].cpp']
        git('--literal-pathspecs','-c','core.autocrlf=false','add','-f','--',*selected,env=env)
        expected=git('write-tree',env=env).decode().strip()
        stage_files(repo,selected,fast);actual=git('write-tree',env=fast).decode().strip();assert actual==expected
        verify_tree_files(repo,actual,list(rows)+['new file.json'])
        # Reject a mismatch rather than accepting a tree that only has filenames.
        (repo/'keep.txt').write_bytes(b'wrong')
        try:verify_tree_files(repo,actual,['keep.txt'])
        except AssertionError:pass
        else:raise AssertionError('Blob mismatch was not detected')
        result=dict(passed=True,actual_tree=actual,reference_tree=expected,trees_identical_to_literal_git_add=True,unicode_spaces_and_square_brackets_literal=True,CRLF_and_binary_bytes_preserved=True,executable_mode_preserved=True,untouched_index_preserved=True,streamed_blob_comparison_passed=True,changed_blob_rejected=True)
        owned=checked(repo,ROOT/'work')
        def readonly(func,path,error):
            file=Path(path).resolve();assert file.is_relative_to(owned)
            if isinstance(error,PermissionError) and file.is_file() and not(file.stat().st_mode&stat.S_IWRITE):
                file.chmod(stat.S_IWRITE|stat.S_IREAD);func(path)
            else:raise error
        shutil.rmtree(owned,onexc=readonly)
        for name in ('reference-index','batch-index'):(root/name).unlink()
    assert not root.exists();result['D_fixture_workspace_removed']=True
    save('backup_batch_index_test.json',result);print(json.dumps(result,indent=2))


if __name__=='__main__':main()
