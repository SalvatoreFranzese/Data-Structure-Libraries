
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data> {

private:

protected:

  struct NodeVec : virtual public BinaryTree<Data>::Node {

  private:

  protected:

    Data data;
    unsigned long pos = 0; // Index Node
    Vector<NodeVec*>* rifTreeVec = nullptr; // Riferimento al treeVec di BinaryTreeVec

  public:

    friend class BinaryTreeVec<Data>;

    NodeVec() = default;

    /* ********************************************************************** */

    // Specific constructors
    NodeVec(const Data&, unsigned long, Vector<NodeVec*>*);
    NodeVec(Data&&, unsigned long, Vector<NodeVec*>*) noexcept;

    /* ********************************************************************** */

    // Destructor
    ~NodeVec() = default;

    /* ********************************************************************** */

    // Copy assignment
    NodeVec& operator=(const NodeVec&);

    // Move assignment
    NodeVec& operator=(NodeVec&&) noexcept;

    /* ********************************************************************** */

    // Specific member functions (inherited from Node)

    Data& Element() noexcept override; // Mutable access to the element
    const Data& Element() const noexcept override; // Immutable access to the element

    inline bool IsLeaf() const noexcept override;
    bool HasLeftChild() const noexcept override;
    bool HasRightChild() const noexcept override;

    NodeVec& LeftChild() const override;
    NodeVec& RightChild() const override;

  };

  using BinaryTree<Data>::size;
  Vector<NodeVec*> treeVec;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec&) const noexcept;
  bool operator!=(const BinaryTreeVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  using typename MappableContainer<Data>::MapFunctor;
  void MapBreadth(const MapFunctor, void*) override; // Override BinaryTree member

  using typename FoldableContainer<Data>::FoldFunctor;
  void FoldBreadth(const FoldFunctor, const void*, void*) const override; // Override BinaryTree member

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
