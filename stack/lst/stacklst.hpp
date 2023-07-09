
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>, virtual protected List<Data> {

private:

protected:

  using List<Data>::size;
  using List<Data>::head;
  using typename List<Data>::Node;

public:

  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const LinearContainer<Data>&); // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst&);

  // Move constructor
  StackLst(StackLst&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackLst& operator=(const StackLst&);

  // Move assignment
  StackLst& operator=(StackLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst&) const noexcept;
  inline bool operator!=(const StackLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  void Push(const Data&) override; // Copy of the value
  void Push(Data&&) noexcept override; // Move of the value
  Data& Top() const override;
  void Pop() override;
  Data TopNPop() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override;

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
