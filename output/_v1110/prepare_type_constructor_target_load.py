"""Prepare one independent loaded comparison after mixed wide-load evidence."""
import ast
from pathlib import Path

STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/type_constructor_bundle'


def main():
    text=(STAGE/'native_perf50/item_locality_bundle/compare_target_load.py').read_text('utf8')
    text=text.replace("REPO/'dist/native_1_1_10_before_item_locality_bundle_20261121/libgdcore.dll'", "REPO/'dist/native_1_1_10/libgdcore.dll'")
    text=text.replace('444e75c6872fa2acec57f42d88eb6687c29f2dc97a82b88ba3e66fdf849312cc','14263d42d22021a83849baffddf2f6288694886f2733a66c0473850b37407548')
    text=text.replace('8e7d574055c36e7535cb54139e11514729e72088c4314ad028c623d42ae32cfa','742ef705e583387510341a9f9055ba80bb6160a1f6290f55ef68ac6970fd081a')
    text=text.replace('133.9979024452513','128.83614850480603')
    text=text.replace('original fitted134.00 estimate remains recorded','original fitted128.84 estimate remains recorded')
    text=text.replace("'original_wide_fit_kept':True", "'original_wide_fit_kept':True,\n        'prior32_pair_evidence':'CPU median +0.4425%, wall +0.1727%; sums -0.8505%/-1.4007%; mixed and weak.',\n        'reason_for_this_condition':'Compare current baseline/candidate under identical fixed added load; independent fitted values differed and wide-load paired evidence was weak.',\n        'only_one_loaded_run':True,'no_new_groups_after_this_run':True")
    ast.parse(text)
    path=WORK/'compare_target_load.py';assert not path.exists()
    path.write_text(text,encoding='utf8',newline='\n')
    print(path)


if __name__=='__main__':main()
