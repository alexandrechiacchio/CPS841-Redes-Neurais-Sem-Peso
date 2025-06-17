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
        .def("getNumberOfKernels", &KernelCanvas2::getNumberOfKernels)
        .def("getShape", &KernelCanvas2::getShape)
        .def("getClosestKernel", &KernelCanvas2::getClosestKernel)
        .def("mutateKernel", &KernelCanvas2::mutateKernel, py::arg("mutationFactor") = 0.1)
        
        // Pickle support:
        .def(py::pickle(
            [](const KernelCanvas2 &self) { // __getstate__
                return py::make_tuple(
                    self.getShape(),
                    self.getNumberOfKernels(),
                    self.bitsPerKernel,
                    self.activationDegree,
                    self.getKernelPoints()
                );
            },
            [](py::tuple t) { // __setstate__
                auto obj = new KernelCanvas2(
                    t[0].cast<std::pair<int, int>>(),
                    t[1].cast<int>(),
                    t[2].cast<int>(),
                    t[3].cast<float>()
                );
                // Restore kernel_points
                auto kernel_points = t[4].cast<std::vector<std::pair<int, int>>>();
                obj->kernel_points = kernel_points;
                obj->findClosestKernels();
                return obj;
            }
        ));
}