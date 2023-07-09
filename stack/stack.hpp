
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack : virtual public Container {

private:

protected:

public:

  // Destructor
  virtual ~Stack() = default;

  /* ************************************************************************ */

  // Copy assignment
  Stack& operator=(const Stack&) = delete;

  // Move assignment
  Stack& operator=(Stack&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Stack&) const noexcept = delete;
  bool operator!=(const Stack&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual void Push(const Data&) = 0; // Copy of the value
  virtual void Push(Data&&) noexcept = 0; // Move of the value
  virtual Data& Top() const = 0;
  virtual void Pop() = 0;
  virtual Data TopNPop() = 0;

};

/* ************************************************************************** */

}

#endif
