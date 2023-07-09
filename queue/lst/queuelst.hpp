
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : virtual public Queue<Data>, virtual protected List<Data> {

private:

protected:

  using List<Data>::head;
  using List<Data>::tail;
  using List<Data>::size;
  using typename List<Data>::Node;

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const LinearContainer<Data>&); // A queue obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst&);

  // Move constructor
  QueueLst(QueueLst&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueLst& operator=(const QueueLst&);

  // Move assignment
  QueueLst& operator=(QueueLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst&) const noexcept;
  inline bool operator!=(const QueueLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  void Enqueue(const Data&) override; // Copy of the value
  void Enqueue(Data&&) noexcept override; // Move of the value
  Data& Head() const override;
  void Dequeue() override;
  Data HeadNDequeue() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
