#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// MODELS
#include "../include/models/bsm.h"
#include "../include/models/binomial.h"

// INSTRUMENTS
#include "../include/instruments/vanillaOption.h"
#include "../include/instruments/stock.h"
#include "../include/instruments/dividend.h"

// PYBIND SPECIFIC FACTORIES
#include "buildBSM.h"
#include "buildBinomial.h"
#include "buildVanillaOption.h"
#include "buildStock.h"

namespace py = pybind11;

PYBIND11_MODULE(pricer, m) {
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
        [](double spot,
           double yieldRate,
           py::object divCashFlow) {

            if (divCashFlow.is_none()) {
                return makeStock(spot, yieldRate, nullptr);
            }

            CashFlows cashFlows =
                divCashFlow.cast<CashFlows>();

            return makeStock(spot, yieldRate, &cashFlows);
        },
        py::arg("spot"),
        py::arg("yield_rate"),
        py::arg("div_cash_flow") = py::none()
    );

    py::class_<BSM, std::shared_ptr<BSM>>(m, "BSM")
      .def("getPrice", static_cast<double (BSM::*)() const>(&BSM::getPrice))
      .def("impliedVol", &BSM::impliedVol);
      // .def("getPrice1", static_cast<double (BSM::*)(double)>(&BSM::getPrice),
        // py::arg("sigma"));

    m.def(
        "make_bsm",
        &makeBSM,
        py::arg("option"),
        py::arg("stock"),
        py::arg("r"),
        py::arg("sigma")
    );

    py::class_<BinomialModel<>, std::shared_ptr<BinomialModel<>>>(m,"Binomial");

    m.def(
        "make_binomial",
        &makeBinomial,
        py::arg("option"),
        py::arg("stock"),
        py::arg("r"),
        py::arg("sigma")
    );


}
