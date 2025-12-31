#include <pybind11/pybind11.h>

#include "../include/models/bsm.h"
#include "../include/instruments/vanillaOption.h"
#include "../include/instruments/stock.h"
#include "buildBSM.h"
#include "buildVanillaOption.h"
#include "buildStock.h"

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

    py::class_<Stock, std::shared_ptr<Stock>>(m, "Stock")
      .def("spot", &Stock::spot)
      .def("dividends",&Stock::name);

    m.def(
        "make_stock",
        &makeStock,
        py::arg("spot"),
        py::arg("yield"),
        "Factory function for stock"
    );

    py::class_<BSM, std::shared_ptr<BSM>>(m, "BSM")
      .def("getPrice", static_cast<double (BSM::*)() const>(&BSM::getPrice))
      .def("getPrice2", static_cast<double (BSM::*)(double)>(&BSM::getPrice),
        py::arg("sigma"));

    m.def(
        "make_bsm",
        &makeBSM,
        py::arg("option"),
        py::arg("stock"),
        py::arg("r"),
        py::arg("q")
    );

    py::class_<Dividend::CashFlow>(m,"DivCashFlow")
      .def(py::init<double,double>())
      .def_readwrite("time", &Dividend::CashFlow::time)
      .def_readwrite("amount", &Dividend::CashFlow::amount);

    py::class_<DiscreteDividend, Dividend, std::shared_ptr<DiscreteDividend>>(m,"DiscreteDiv")
      .def(py::init([](py::iterable items) {
          std::vector<Dividend::CashFlow> divs;

          for (auto item : items) {
              auto t = py::cast<py::tuple>(item);
              if (t.size() != 2)
                  throw std::runtime_error("Each cashflow must be (time, amount)");

              divs.push_back({
                  t[0].cast<double>(),
                  t[1].cast<double>()
              });
          }

          return std::make_shared<DiscreteDividend>(std::move(divs));
      }), py::arg("cashflows"))

      .def("hasCashSchedule",&DiscreteDividend::hasCashSchedule)
}
