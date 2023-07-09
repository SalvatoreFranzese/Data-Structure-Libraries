
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>, virtual protected Vector<Data> {

private:

protected:

  using Vector<Data>::size;
  using Vector<Data>::Elements;
  unsigned long stackVecSize = 0;

public:

  // Default constructor
  StackVec();

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const LinearContainer<Data>&); // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec&);

  // Move constructor
  StackVec(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec& operator=(const StackVec&);

  // Move assignment
  StackVec& operator=(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec&) const noexcept;
  inline bool operator!=(const StackVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  void Push(const Data&) override; // Copy of the value
  void Push(Data&&) noexcept override; // Move of the value
  Data& Top() const override;
  void Pop() override;
  Data TopNPop() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override;

  inline unsigned long Size() const noexcept override;

  void Clear() override;

protected:

  // Auxiliary member functions

  void Expand();
  void Reduce();

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
