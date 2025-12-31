#include <pybind11/pybind11.h>

#include "../include/instruments/vanillaOption.h"
#include "optionBuilder.h"

namespace py = pybind11;

PYBIND11_MODULE(pyext, m) {
    m.doc() = "Quant options module";

    py::class_<VanillaOption, std::shared_ptr<VanillaOption>>(m, "VanillaOption")
        .def("maturity", &VanillaOption::maturity)
        .def("payoff", &VanillaOption::getPayoff, py::arg("spot"))
        .def("can_exercise", &VanillaOption::canExercise, py::arg("t"));

    m.def(
        "make_vanilla_option",
        &makeVanillaOption,
        py::arg("strike"),
        py::arg("maturity"),
        py::arg("exercise_type"),
        py::arg("option_type"),
        "Factory function for VanillaOption"
    );
}
