
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

protected:

public:

  // Destructor
  virtual ~Iterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  Iterator& operator=(const Iterator&) = delete;

  // Move assignment
  Iterator& operator=(Iterator&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Iterator&) const noexcept = delete;
  bool operator!=(const Iterator&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& operator*() const = 0;

  virtual bool Terminated() const noexcept = 0;

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator : virtual public Iterator<Data> {

private:

protected:

public:

  // Destructor
  virtual ~ForwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ForwardIterator& operator=(const ForwardIterator&) = delete;

  // Move assignment
  ForwardIterator& operator=(ForwardIterator&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ForwardIterator&) const noexcept = delete;
  bool operator!=(const ForwardIterator&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual ForwardIterator& operator++() = 0;

};

/* ************************************************************************** */

template <typename Data>
class BackwardIterator : virtual public Iterator<Data> {

private:

protected:

public:

  // Destructor
  virtual ~BackwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BackwardIterator& operator=(const BackwardIterator&) = delete;

  // Move assignment
  BackwardIterator& operator=(BackwardIterator&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BackwardIterator&) const noexcept = delete;
  bool operator!=(const BackwardIterator&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual BackwardIterator& operator--() = 0;

};

/* ************************************************************************** */

template <typename Data>
class BidirectionalIterator : virtual public ForwardIterator<Data>, virtual public BackwardIterator<Data> {

private:

protected:

public:

  // Destructor
  virtual ~BidirectionalIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BidirectionalIterator& operator=(const BidirectionalIterator&) = delete;

  // Move assignment
  BidirectionalIterator& operator=(BidirectionalIterator&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BidirectionalIterator&) const noexcept = delete;
  bool operator!=(const BidirectionalIterator&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Terminated() override = 0; // Override Iterator member

  virtual bool ForwardTerminated() noexcept = 0;

  virtual bool BackwardTerminated() noexcept = 0;

};

/* ************************************************************************** */

}

#endif
