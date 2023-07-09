
namespace lasd {

/* ************************************************************************** */

// NodeVec

// Specific constructors

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& dat, unsigned long index, Vector<NodeVec*>* vec) {
  data = dat;
  pos = index;
  rifTreeVec = vec;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& dat, unsigned long index, Vector<NodeVec*>* vec) noexcept {
  data = std::move(dat);
  pos = std::move(index);
  rifTreeVec = vec;
}

/* ********************************************************************** */

// Copy assignment

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec& node) {
  data = node.data;
  pos = node.pos;
  rifTreeVec = node.rifTreeVec;
  return *this;
}

// Move assignment

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& node) noexcept {
  std::swap(data, node.data);
  std::swap(pos, node.pos);
  std::swap(rifTreeVec, node.rifTreeVec);
  return *this;
}

/* ************************************************************************** */

// Specific member functions (inherited from Node)

template <typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
  return data;
}

template <typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
  return data;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept {
  return !(HasLeftChild() && HasRightChild());
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
  if ((pos * 2) + 1 < rifTreeVec->Size()) {
    if ((*rifTreeVec)[(pos * 2) + 1] != nullptr)
      return true;
  }
  return false;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
  if ((pos * 2) + 2 < rifTreeVec->Size()) {
    if ((*rifTreeVec)[(pos * 2) + 2] != nullptr)
      return true;
  }
  return false;
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
  if (HasLeftChild())
    return *(*rifTreeVec)[(pos * 2) + 1];
  else
    throw std::out_of_range("Left child doesn't exists!");
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
  if (HasRightChild())
    return *(*rifTreeVec)[(pos * 2) + 2];
  else
    throw std::out_of_range("Right child doesn't exists!");
}

/* ************************************************************************** */

// Specific constructors

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& container) {
  size = container.Size();
  treeVec.Resize(size);
  for (unsigned long index = 0; index < size; ++index) {
    treeVec[index] = new NodeVec(container[index], index, &treeVec);
  }
}

/* ************************************************************************ */

// Copy constructor

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& binaryTree) {
  size = binaryTree.Size();
  treeVec.Resize(binaryTree.treeVec.Size());
  for (unsigned long index = 0; index < binaryTree.treeVec.Size(); ++index) {
    treeVec[index] = new NodeVec(binaryTree.treeVec[index]->Element(), index, &treeVec);
  }
}

// Move constructor

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& binaryTree) noexcept {
  std::swap(size, binaryTree.size);
  std::swap(treeVec, binaryTree.treeVec);
  for (unsigned long index = 0; index < size; ++index) {
    treeVec[index]->rifTreeVec = &treeVec;
  }
}

/* ************************************************************************ */

// Destructor

template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
  if (size > 0)
    Clear();
}

/* ************************************************************************ */

// Copy assignment

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& binaryTree) {
  BinaryTreeVec<Data>* tmpBTvec = new BinaryTreeVec<Data>(binaryTree);
  std::swap(size, tmpBTvec->size);
  std::swap(treeVec, tmpBTvec->treeVec);
  for (unsigned long index = 0; index < size; ++index) {
    treeVec[index]->rifTreeVec = &treeVec;
  }
  delete tmpBTvec;
  return *this;
}

// Move assignment

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& binaryTree) noexcept {
  std::swap(size, binaryTree.size);
  std::swap(treeVec, binaryTree.treeVec);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& binaryTree) const noexcept {
  return BinaryTree<Data>::operator==(binaryTree);
}

template <typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& binaryTree) const noexcept {
  return BinaryTree<Data>::operator!=(binaryTree);
}

/* ************************************************************************** */

// Specific member functions (inherited from BinaryTree)

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
  if (size > 0)
    return *treeVec[0];
  else
    throw std::length_error("Access to an empty binary tree vector!");
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void BinaryTreeVec<Data>::Clear() {
  if (size > 0) {
    for (unsigned long index = 0; index < size; ++index) {
      delete treeVec[index];
      treeVec[index] = nullptr;
    }
    size = 0;
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from BinaryTree)

template <typename Data>
void BinaryTreeVec<Data>::MapBreadth(const MapFunctor fun, void* par) {
  if (size > 0) {
    for (unsigned long index = 0; index < size; ++index) {
      fun(treeVec[index]->Element(), par);
    }
  }
}

template <typename Data>
void BinaryTreeVec<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const {
  if (size > 0) {
    for (unsigned long index = 0; index < size; ++index) {
      fun(treeVec[index]->Element(), par, acc);
    }
  }
}

}
