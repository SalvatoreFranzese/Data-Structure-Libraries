
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public LinearContainer<Data>, virtual public MappableContainer<Data>, virtual public FoldableContainer<Data> {

private:

protected:

  using LinearContainer<Data>::size;

  struct Node
  {

    Data data;
    Node* next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    Node(const Data&);
    Node(Data&& dat) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node&);

    // Move constructor
    Node(Node&&) noexcept;

    /* ********************************************************************** */

    // Destructor
    ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    inline bool operator!=(const Node&) const noexcept;

  };
  Node* head = nullptr;
  Node* tail = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const LinearContainer<Data>&); // A list obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List&);

  // Move constructor
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  inline bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&); // Copy of the value
  void InsertAtFront(Data&&) noexcept; // Move of the value
  void RemoveFromFront();
  Data FrontNRemove();

  void InsertAtBack(const Data&); // Copy of the value
  void InsertAtBack(Data&&) noexcept; // Move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override;
  Data& Back() const override;

  Data& operator[](const unsigned long) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  inline void MapPreOrder(MapFunctor, void*) override; // Override MappableContainer member
  inline void MapPostOrder(MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  inline void FoldPreOrder(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
  inline void FoldPostOrder(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

protected:

  // Auxiliary member functions (for MappableContainer)

  void MapPreOrder(MapFunctor, void*, Node*); // Accessory function executing from one point of the list onwards
  void MapPostOrder(MapFunctor, void*, Node*); // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for FoldableContainer)

  void FoldPreOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards
  void FoldPostOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
