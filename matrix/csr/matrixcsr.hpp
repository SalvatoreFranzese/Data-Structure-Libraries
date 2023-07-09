
#ifndef MATRIXCSR_HPP
#define MATRIXCSR_HPP

/* ************************************************************************** */

#include "../matrix.hpp"

#include "../../list/list.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MatrixCSR : virtual public Matrix<Data>, virtual protected List<std::pair<Data, unsigned long>> {

private:

protected:

  using Matrix<Data>::rowNum;
  using Matrix<Data>::columnNum;

  using typename List<std::pair<Data, unsigned long>>::Node;
  using List<std::pair<Data, unsigned long>>::size;
  using List<std::pair<Data, unsigned long>>::head;

  Vector<Node**> rowsVec;

public:

  // Default constructor
  MatrixCSR();

  /* ************************************************************************ */

  // Specific constructors
  MatrixCSR(const unsigned long, const unsigned long); // A matrix of some specified dimension

  /* ************************************************************************ */

  // Copy constructor
  MatrixCSR(const MatrixCSR&);

  // Move constructor
  MatrixCSR(MatrixCSR&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~MatrixCSR();

  /* ************************************************************************ */

  // Copy assignment
  MatrixCSR& operator=(const MatrixCSR&);

  // Move assignment
  MatrixCSR& operator=(MatrixCSR&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const MatrixCSR&) const noexcept;
  bool operator!=(const MatrixCSR&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Matrix)

  void RowResize(const unsigned long) override; // Override Matrix member
  void ColumnResize(const unsigned long) override; // Override Matrix member

  bool ExistsCell(const unsigned long, const unsigned long) const noexcept override; // Override Matrix member (should not throw exceptions)

  Data& operator()(const unsigned long, const unsigned long) override; // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  const Data& operator()(const unsigned long, const unsigned long) const override; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  using Matrix<Data>::Exists;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void MapPreOrder(const MapFunctor, void*) override; // Override MappableContainer member
  void MapPostOrder(const MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

};

/* ************************************************************************** */

}

#include "matrixcsr.cpp"

#endif
