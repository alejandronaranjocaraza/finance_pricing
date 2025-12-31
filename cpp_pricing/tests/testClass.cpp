class test {
public:
  test(
      double a,
      double b,
      double c) :
    a_{a}, b_{b}, c_{c} {};
  void setSum() {
    sum_ = a_ + b_ + c_;
  }
  double getSum() {
    return sum_;
  }
private:
  double a_;
  double b_;
  double c_;
  double sum_;
};
