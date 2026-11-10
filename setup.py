# -*- coding: utf-8 -*-
"""setup.py — 只为给 wheel 打上正确的平台/ABI 标签（其余配置在 pyproject.toml）。

为什么必须覆写：内核 664 个模块是 .pyd（cp314-win_amd64 ABI）。setuptools 默认把
纯 Python 项目打成 py3-none-any，装到别的 Python/平台上会 ImportError 或悄悄退回
纯 Python 腿（性能 -40% 且用户无感）。这里显式声明标签，让 pip 在错误环境直接拒绝安装。

  真标签 = <python_tag>-<abi_tag>-<platform_tag>
    例如 cp314-cp314-win_amd64（编译进内核的 Python 版本 + Windows x64）
"""
import sys

from setuptools import setup
from wheel.bdist_wheel import bdist_wheel as _bdist_wheel


class bdist_wheel(_bdist_wheel):
    """把 wheel 标成 CPython 特定版本 + win_amd64。"""

    def finalize_options(self):
        super().finalize_options()
        self.root_is_pure = False      # 关键：非纯 Python

    def get_tag(self):
        tag = super().get_tag()
        py_ver = "cp%d%d" % (sys.version_info.major, sys.version_info.minor)
        return (py_ver, py_ver, "win_amd64")


setup(cmdclass={"bdist_wheel": bdist_wheel})
