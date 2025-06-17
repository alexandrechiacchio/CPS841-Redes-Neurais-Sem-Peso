

compile:
	c++ -O3 -Wall -shared -std=c++17 -fPIC $(shell python3 -m pybind11 --includes) kernelcanvas2.cc wrapper.cc -o kernelcanvas2$(shell python3-config --extension-suffix)

install: compile
	pip install .