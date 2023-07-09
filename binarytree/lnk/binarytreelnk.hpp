
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data> {

private:

protected:

  using BinaryTree<Data>::size;

  struct NodeLnk : virtual public BinaryTree<Data>::Node {

  private:

  protected:

  public:

    Data data;
    NodeLnk* left = nullptr;
    NodeLnk* right = nullptr;

    friend class BinaryTreeLnk<Data>;

    NodeLnk() = default;

    /* ********************************************************************** */

    // Specific constructors
    NodeLnk(const Data&);
    NodeLnk(Data&&) noexcept;

    /* ********************************************************************** */

    // Destructor
    ~NodeLnk();

    /* ********************************************************************** */

    // Copy assignment
    NodeLnk& operator=(const NodeLnk&);

    // Move assignment
    NodeLnk& operator=(NodeLnk&&) noexcept;

    /* ********************************************************************** */

    // Specific member functions (inherited from Node)

    Data& Element() noexcept override; // Mutable access to the element
    const Data& Element() const noexcept override; // Immutable access to the element

    inline bool IsLeaf() const noexcept override;
    inline bool HasLeftChild() const noexcept override;
    inline bool HasRightChild() const noexcept override;

    NodeLnk& LeftChild() const override;
    NodeLnk& RightChild() const override;

  };
  NodeLnk* root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk&) const noexcept;
  bool operator!=(const BinaryTreeLnk&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeLnk& Root() const override; // Override BinaryTree member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override;

  /* ************************************************************************ */

  // Auxiliary member functions

  void CopyBinaryTree(NodeLnk&, NodeLnk&);
  void InsertIntoBinaryTreeLnk(const LinearContainer<Data>&, NodeLnk*, unsigned long);

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
