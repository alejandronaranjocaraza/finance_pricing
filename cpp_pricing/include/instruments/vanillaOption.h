#include "option.h"

class VanillaOption : public Option {
public:
  enum struct OptionType {
    call,
    put
  };
  VanillaOption(
      double K,
      double T,
      std::shared_ptr<Exercise> exercisePtr,
      std::shared_ptr<Payoff> payoffPtr,
      OptionType optionType = OptionType::call
      ) :
    Option(K, T, exercisePtr, payoffPtr),
    optionType_{optionType} {}

  OptionType type() const;
private:
  OptionType optionType_;
};
