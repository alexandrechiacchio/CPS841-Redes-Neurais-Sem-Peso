#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "kernelcanvas2.cc"

namespace py = pybind11;

PYBIND11_MODULE(kernelcanvas2, m) {
    py::class_<KernelCanvas2>(m, "KernelCanvas2")
        .def(py::init<std::pair<int, int>, int, int, float>(),
             py::arg("shape"),
             py::arg("numberOfKernels"),
             py::arg("bitsPerKernel") = 1,
             py::arg("activationDegree") = 0.07)
        .def("transform", &KernelCanvas2::transform)
        .def("tst", &KernelCanvas2::tst)
        .def("getKernelPoints", &KernelCanvas2::getKernelPoints)
        .def("getShape", &KernelCanvas2::getShape)
        .def("getClosestKernel", &KernelCanvas2::getClosestKernel);
}