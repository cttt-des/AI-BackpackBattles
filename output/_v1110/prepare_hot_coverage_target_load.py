"""One loaded comparison after the new independent fit fell below the old fit."""
import ast
from pathlib import Path

STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/hot_coverage_bundle'


def main():
    text=(STAGE/'native_perf50/item_locality_bundle/compare_target_load.py').read_text('utf8')
    text=text.replace("REPO/'dist/native_1_1_10_before_item_locality_bundle_20261121/libgdcore.dll'", "REPO/'dist/native_1_1_10/libgdcore.dll'")
    text=text.replace('444e75c6872fa2acec57f42d88eb6687c29f2dc97a82b88ba3e66fdf849312cc','14263d42d22021a83849baffddf2f6288694886f2733a66c0473850b37407548')
    text=text.replace('8e7d574055c36e7535cb54139e11514729e72088c4314ad028c623d42ae32cfa','401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259')
    text=text.replace('133.9979024452513','114.95502937494335')
    text=text.replace('original fitted134.00 estimate remains recorded','original fitted114.96 estimate remains recorded')
    text=text.replace("'original_wide_fit_kept':True", "'original_wide_fit_kept':True,\n        'prior24_pair_evidence':'All3 group CPU/wall medians positive; combined medians +1.9328%/+1.6319%, sums +0.3556%/+0.6082%.',\n        'reason_for_this_condition':'The independent20-load fit fell from139.72 to114.96 despite positive paired comparisons; compare actual baseline/candidate under the same fixed added load before deployment.',\n        'only_one_loaded_run':True,'no_repeat_until_pass':True")
    ast.parse(text);path=WORK/'compare_target_load.py';assert not path.exists()
    path.write_text(text,encoding='utf8',newline='\n');print(path)


if __name__=='__main__':main()
