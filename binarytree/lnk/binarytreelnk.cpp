
namespace lasd {

/* ************************************************************************** */

// NodeLnk

// Specific constructors

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& dat) {
  data = dat;
  left = nullptr;
  right = nullptr;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& dat) noexcept {
  data = std::move(dat);
  left = nullptr;
  right = nullptr;
}

/* ********************************************************************** */

// Destructor

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
  if (HasLeftChild())
    delete left;
  if (HasRightChild())
    delete right;
}

/* ********************************************************************** */

// Copy assignment

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& node) {
  data = node.data;
  left = node.left;
  right = node.right;
  return *this;
}

// Move assignment

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& node) noexcept {
  std::swap(data, node.data);
  std::swap(left, node.left);
  std::swap(right, node.right);
  return *this;
}

/* ************************************************************************** */

// Specific member functions (inherited from Node)

template <typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
  return data;
}

template <typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
  return data;
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept {
  return (left == nullptr && right == nullptr);
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
  return (left != nullptr);
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
  return (right != nullptr);
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
  if (left != nullptr)
    return *left;
  else
    throw std::out_of_range("Left child doesn't exists!");
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
  if (right != nullptr)
    return *right;
  else
    throw std::out_of_range("Right child doesn't exists!");
}

/* ************************************************************************** */

// BinaryTreeLnk

template <typename Data>
void BinaryTreeLnk<Data>::InsertIntoBinaryTreeLnk(const LinearContainer<Data>& container, NodeLnk* node, unsigned long index) {
  if ((index * 2) + 1 < size) {
    node->left = new NodeLnk(container[(index * 2) + 1]);
    InsertIntoBinaryTreeLnk(container, node->left, index * 2 + 1);
  }

  if ((index * 2) + 2 < size) {
    node->right = new NodeLnk(container[(index * 2) + 2]);
    InsertIntoBinaryTreeLnk(container, node->right, index * 2 + 2);
  }
}

// Specific constructors

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& container) {
  size = container.Size();
  root = new NodeLnk(container[0]);
  InsertIntoBinaryTreeLnk(container, root, 0);
}

/* ************************************************************************** */

// Copy BinaryTree

template <typename Data>
void BinaryTreeLnk<Data>::CopyBinaryTree(NodeLnk& myRoot, NodeLnk& otherRoot) {
  if (otherRoot.HasLeftChild()) {
    myRoot.left = new NodeLnk(otherRoot.LeftChild().Element());
    CopyBinaryTree(myRoot.LeftChild(), otherRoot.LeftChild());
  }

  if (otherRoot.HasRightChild()) {
    myRoot.right = new NodeLnk(otherRoot.RightChild().Element());
    CopyBinaryTree(myRoot.RightChild(), otherRoot.RightChild());
  }
}

// Copy constructor

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& binaryTree) {
  size = binaryTree.Size();
  root = new NodeLnk(binaryTree.Root().Element());
  CopyBinaryTree(Root(), binaryTree.Root());
}

// Move constructor

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& binaryTree) noexcept {
  std::swap(root, binaryTree.root);
  std::swap(size, binaryTree.size);
}

/* ************************************************************************ */

// Destructor

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
  if (root != nullptr)
    Clear();
}

/* ************************************************************************ */

// Copy assignment

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& binaryTree) {
  BinaryTreeLnk<Data>* tmp = new BinaryTreeLnk<Data>(binaryTree);
  std::swap(*this, *tmp);
  delete tmp;
  return *this;
}

// Move assignment

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& binaryTree) noexcept {
  std::swap(root, binaryTree.root);
  std::swap(size, binaryTree.size);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& binaryTree) const noexcept {
  return BinaryTree<Data>::operator==(binaryTree);
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& binaryTree) const noexcept {
  return BinaryTree<Data>::operator!=(binaryTree);
}

/* ************************************************************************** */

// Specific member functions (inherited from BinaryTree)

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
  if (root != nullptr)
    return *root;
  else
    throw std::length_error("Access to an empty binary tree!");
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)

template <typename Data>
void BinaryTreeLnk<Data>::Clear() {
  delete root;
  root = nullptr;
  size = 0;
}

}
