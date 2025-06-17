from setuptools import setup, Extension
import sys
import pybind11

ext_modules = [
    Extension(
        "kernelcanvas",  # <--- as a submodule!
        sources=["wrapper.cc", "kernelcanvas2.cc"],
        include_dirs=[pybind11.get_include()],
        language="c++",
        extra_compile_args=["-std=c++17"],
    ),
]

setup(
    name="kernelcanvas",
    version="0.1",
    description="Python bindings for KernelCanvas2 using pybind11",
    ext_modules=ext_modules,
    packages=[],
    package_data={
        "": ["stubs/*.pyi"],  # Include all .pyi files in the stubs folder
    },
    zip_safe=False,
)