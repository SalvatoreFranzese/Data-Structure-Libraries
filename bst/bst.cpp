
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
BST<Data>::BST(const LinearContainer<Data>& container) {
  for (unsigned long index = 0; index < container.Size(); ++index) {
    Insert(container[index]);
  }
  size = container.Size();
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
BST<Data>::BST(const BST<Data>& bst) : BinaryTreeLnk<Data>::BinaryTreeLnk(bst) {}

// Move constructor

template <typename Data>
BST<Data>::BST(BST<Data>&& bst) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(bst)) {}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst) {
  BinaryTreeLnk<Data>::operator=(bst);
  return *this;
}

// Move assignment

template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
  BinaryTreeLnk<Data>::operator=(std::move(bst));
  return *this;
}

/* ************************************************************************ */

// Comparison operators

template <typename Data>
bool BST<Data>::operator==(const BST<Data>& bst) const noexcept {
  if (size == bst.Size()) {
    BTInOrderIterator<Data> itr1(*this);
    BTInOrderIterator<Data> itr2(bst);

    while (!itr1.Terminated()) {
      if (*itr1 != *itr2)
        return false;

      ++itr1;
      ++itr2;
    }
    return true;
  }
  return false;
}

template <typename Data>
inline bool BST<Data>::operator!=(const BST<Data>& bst) const noexcept {
  return !(*this == bst);
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
void BST<Data>::Insert(const Data& data) {
  NodeLnk*& pointer = FindPointerTo(root, data);
  if (pointer == nullptr) {
    pointer = new NodeLnk(data);
    size++;
  }
}

template <typename Data>
void BST<Data>::Insert(Data&& data) noexcept {
  NodeLnk*& pointer = FindPointerTo(root, data);
  if (pointer == nullptr) {
    pointer = new NodeLnk(std::move(data));
    size++;
  }
}

template <typename Data>
void BST<Data>::Remove(const Data& data) {
  delete Detach(FindPointerTo(root, data));
}

// Min

template <typename Data>
const Data& BST<Data>::Min() const {
  if (root != nullptr)
    return FindPointerToMin(root)->data;
  else
    throw std::length_error("Access to an empty tree!");
}

template <typename Data>
Data BST<Data>::MinNRemove() {
  if (root != nullptr)
    return DataNDelete(DetachMin(root));
  else
    throw std::length_error("Access to an empty tree!");
}

template <typename Data>
void BST<Data>::RemoveMin() {
  if (root != nullptr)
    delete DetachMin(root);
  else
    throw std::length_error("Access to an empty tree!");
}

// Max

template <typename Data>
const Data& BST<Data>::Max() const {
  if (root != nullptr)
    return FindPointerToMax(root)->data;
  else
    throw std::length_error("Access to an empty tree!");
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
  if (root != nullptr)
    return DataNDelete(DetachMax(root));
  else
    throw std::length_error("Access to an empty tree!");
}

template <typename Data>
void BST<Data>::RemoveMax() {
  if (root != nullptr)
    delete DetachMax(root);
  else
    throw std::length_error("Access to an empty tree!");
}

// Predecessor

template <typename Data>
const Data& BST<Data>::Predecessor(const Data& data) const {
  NodeLnk* const* ptr = FindPointerToPredecessor(root, data);
  if (ptr != nullptr)
    return (*ptr)->data;
  else
    throw std::length_error("Predecessor error!");
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& data) {
  NodeLnk** ptr = FindPointerToPredecessor(root, data);
  if (ptr != nullptr)
    return DataNDelete(Detach(*ptr));
  else
    throw std::length_error("Predecessor error!");
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& data) {
  NodeLnk** ptr = FindPointerToPredecessor(root, data);
  if (ptr != nullptr)
    delete Detach(*ptr);
  else
    throw std::length_error("Predecessor error!");
}

// Successor

template <typename Data>
const Data& BST<Data>::Successor(const Data& data) const {
  NodeLnk* const* ptr = FindPointerToSuccessor(root, data);
  if (ptr != nullptr)
    return (*ptr)->data;
  else
    throw std::length_error("Successor error!");
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& data) {
  NodeLnk** ptr = FindPointerToSuccessor(root, data);
  if (ptr != nullptr)
    return DataNDelete(Detach(*ptr));
  else
    throw std::length_error("Successor error!");
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& data) {
  NodeLnk** ptr = FindPointerToSuccessor(root, data);
  if (ptr != nullptr)
    return Detach(*ptr);
  else
    throw std::length_error("Successor error!");
}

/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template <typename Data>
bool BST<Data>::Exists(const Data& data) const noexcept {
  return (FindPointerTo(root, data) != nullptr);
}

/* ************************************************************************** */

// Auxiliary member functions

template <typename Data>
Data BST<Data>::DataNDelete(NodeLnk* node) noexcept {
  Data data;
  std::swap(data, node->data);
  delete node;
  return data;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept {
  if (node != nullptr) {

    if (node->left == nullptr)
      return SkipOnRight(node);
    else if (node->right == nullptr)
      return SkipOnLeft(node);
    else {
      NodeLnk* max = DetachMax(node->left);
      std::swap(node->data, max->data);
      return max;
    }

  }
  return nullptr;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept {
  return SkipOnRight(FindPointerToMin(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& node) noexcept {
  return SkipOnLeft(FindPointerToMax(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnLeft(NodeLnk*& node) noexcept {
  NodeLnk* left = nullptr;
  if (node != nullptr) {
    std::swap(left, node->left);
    std::swap(left, node);
    size--;
  }
  return left;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnRight(NodeLnk*& node) noexcept {
  NodeLnk* right = nullptr;
  if (node != nullptr) {
    std::swap(right, node->right);
    std::swap(right, node);
    size--;
  }
  return right;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& node) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& node) const noexcept {
  NodeLnk* curr = node;
  NodeLnk* const* ptr = &node;
  if (curr != nullptr) {
    while (curr->left != nullptr) {
      ptr = &curr->left;
      curr = curr->left;
    }
  }
  return *ptr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& node) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& node) const noexcept {
  NodeLnk* curr = node;
  NodeLnk* const* ptr = &node;
  if (curr != nullptr) {
    while (curr->right != nullptr) {
      ptr = &curr->right;
      curr = curr->right;
    }
  }
  return *ptr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& node, const Data& data) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(node, data));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& node, const Data& data) const noexcept {
  NodeLnk* curr = node;
  NodeLnk* const* ptr = &node;
  if (curr != nullptr) {
    if (data != curr->data) {
      if (data < curr->data)
        return FindPointerTo(curr->left, data);
      else if (data > curr->data)
        return FindPointerTo(curr->right, data);
    }
  }
  return *ptr;
}

template <typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk*& node, const Data& data) noexcept {
  return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(node, data));
}

template <typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk*& node, const Data& data) noexcept {
  return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(node, data));
}

template <typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToPredecessor(NodeLnk* const& node, const Data& data) const noexcept {
  NodeLnk* const* curr = &node;
  NodeLnk* const* ptr = nullptr;

  while ((*curr) != nullptr && (*curr)->data != data) {

    if ((*curr)->data < data) {
      ptr = curr;
      curr = &(*curr)->right;
    }
    else if ((*curr)->data > data)
      curr = &(*curr)->left;

  }

  if ((*curr) != nullptr && (*curr)->left != nullptr)
    return &FindPointerToMax((*curr)->left);

  return ptr;
}

template <typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(NodeLnk* const& node, const Data& data) const noexcept {
  NodeLnk* const* curr = &node;
  NodeLnk* const* ptr = nullptr;

  while ((*curr) != nullptr && (*curr)->data != data) {

    if ((*curr)->data < data)
      curr = &(*curr)->right;
    else if ((*curr)->data > data) {
      ptr = curr;
      curr = &(*curr)->left;
    }
  }

  if ((*curr) != nullptr && (*curr)->right != nullptr)
    return &FindPointerToMin((*curr)->right);

  return ptr;
}

/* ************************************************************************** */

}
