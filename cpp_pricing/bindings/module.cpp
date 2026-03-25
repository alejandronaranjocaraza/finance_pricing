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
    m.doc() = "Quant option pricing module";

    py::class_<VanillaOption, std::shared_ptr<VanillaOption>>(m, "VanillaOption")
        .def("maturity", &VanillaOption::maturity)
        .def("payoff", &VanillaOption::getPayoff, py::arg("spot"))
        .def("canExercise", &VanillaOption::canExercise, py::arg("t"));

    m.def(
        "makeVanillaOption",
        &makeVanillaOption,
        py::arg("strike"),
        py::arg("maturity"),
        py::arg("optionType")="p",
        py::arg("exerciseType")="e",
        "Factory function for VanillaOption."
    );

    py::class_<Stock, std::shared_ptr<Stock>>(m, "Stock")
      .def("spot", &Stock::spot)
      .def("dividends",&Stock::name);

    m.def(
        "makeStock",
        [](double spot,
           double divYieldRate,
           std::optional<CashFlows> divCashFlow)
        {
            if (divCashFlow) {
                return makeStock(spot, divYieldRate, &(*divCashFlow));
            }
            return makeStock(spot, divYieldRate, nullptr);
        },
        py::arg("spot"),
        py::arg("yieldRate"),
        py::arg("cashFlow") = std::nullopt
    );

    py::class_<BSM, std::shared_ptr<BSM>>(m, "BSM")
      .def("getPrice", static_cast<double (BSM::*)() const>(&BSM::getPrice))
      .def("impliedVol", &BSM::impliedVol);
      // .def("getPrice1", static_cast<double (BSM::*)(double)>(&BSM::getPrice),
        // py::arg("sigma"));

    m.def(
        "makeBSM",
        &makeBSM,
        py::arg("option"),
        py::arg("stock"),
        py::arg("r"),
        py::arg("sigma")
    );

    py::class_<BinomialModel<>, std::shared_ptr<BinomialModel<>>>(m,"Binomial")
      .def("getPrice", static_cast<double (BinomialModel<>::*)() const>(&BinomialModel<>::getPrice));

    m.def(
        "makeBinomial",
        &makeBinomial,
        py::arg("option"),
        py::arg("stock"),
        py::arg("r"),
        py::arg("sigma"),
        py::arg("n") = 100
    );
}
