#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

class Foo {
public:
    explicit Foo(int x) : x_(x) {}

    int value() const {
        return x_;
    }

private:
    int x_;
};

int add(int x, int y) {
  return x+y;
}

int main() {
    Foo f(42);

    std::cout << "Foo value = " << f.value() << std::endl;

    return 0;
}

PYBIND11_MODULE(test, m) {
    m.def("add", &add, "Add two numbers");
}
