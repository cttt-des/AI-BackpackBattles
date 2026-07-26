"""
路径工具 — 兼容开发模式和 PyInstaller 打包模式
"""

import sys
from pathlib import Path


def is_frozen() -> bool:
    """是否运行在 PyInstaller 打包的 exe 中"""
    return getattr(sys, "frozen", False)


def get_base_dir() -> Path:
    """
    获取程序基准目录：
    - exe 模式: exe 所在目录（config.yaml、logs 放这里，方便用户编辑）
    - 开发模式: 项目根目录
    """
    if is_frozen():
        return Path(sys.executable).parent
    return Path(__file__).parent.parent


def get_resource_dir() -> Path:
    """
    获取打包资源目录：
    - exe 模式: PyInstaller 解压的临时目录 (_MEIPASS)，模板/静态文件在这里
    - 开发模式: 项目根目录
    """
    if is_frozen():
        return Path(sys._MEIPASS)
    return Path(__file__).parent.parent


def get_config_path() -> Path:
    """
    获取配置文件路径：
    优先使用 exe/项目目录下的 config.yaml（用户可编辑），
    不存在时回退到打包内置的默认配置
    """
    external = get_base_dir() / "config.yaml"
    if external.exists():
        return external
    bundled = get_resource_dir() / "config.yaml"
    return bundled
