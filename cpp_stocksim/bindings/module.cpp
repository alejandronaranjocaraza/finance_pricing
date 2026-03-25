#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "../include/geometricBrownian.h"
#include "../include/randomWalk.h"

namespace py = pybind11;

PYBIND11_MODULE(stocksim, m) {
  m.doc() = "Stock simulation library.";

  m.def(
      "randomWalk",
      &randomWalk,
      py::arg("S0"),
      py::arg("T"),
      py::arg("r"),
      py::arg("sigma"),
      py::arg("nPaths") = 1,
      py::arg("nSteps") = 100,
      "Stock price simulation with multiplicative random walk."
      );

  m.def(
      "geometricBrownian",
      &geometricBrownian,
      py::arg("S0"),
      py::arg("T"),
      py::arg("r"),
      py::arg("sigma"),
      py::arg("nPaths") = 1,
      py::arg("nSteps") = 100,
      "Stock price simulation with geometric Brownian motion."
      );
}
