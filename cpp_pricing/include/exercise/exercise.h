#pragma once

class Option;

class Exercise {
public:
  virtual ~Exercise() = default;
  virtual bool canExercise(
      const Option& option,
      double t
      ) const = 0;
  virtual char tag() const = 0;
};
