
namespace lasd {

/* ************************************************************************ */

// TreeCompare

template <typename Data>
bool BinaryTree<Data>::TreeCompare(const Node& firstNode, const Node& secondNode) const noexcept {
  if (firstNode.Element() == secondNode.Element()) {
    if (firstNode.HasLeftChild() != secondNode.HasLeftChild() || firstNode.HasRightChild() != secondNode.HasRightChild())
      return false;
    else {
      if (firstNode.HasLeftChild())
        return TreeCompare(firstNode.LeftChild(), secondNode.LeftChild()); // Richiamo sottoalbero SX
      if (secondNode.HasRightChild())
        return TreeCompare(firstNode.RightChild(), secondNode.RightChild()); // Richiamo sottoalbero DX
      return true;
    }
  }
  else
    return false;
}

// Comparison operators

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& binaryTree) const noexcept {
  if (size == binaryTree.Size() && size > 0)
    return TreeCompare(Root(), binaryTree.Root());
  return false;
}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& binaryTree) const noexcept {
  return !(*this == binaryTree);
}

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  if (size > 0)
    MapPreOrder(fun, par, &Root());
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  if (size > 0)
    MapPostOrder(fun, par, &Root());
}

/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if (size > 0)
    FoldPreOrder(fun, par, acc, &Root());
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if (size > 0)
    FoldPostOrder(fun, par, acc, &Root());
}

/* ************************************************************************** */

// Specific member functions (inherited from InOrderMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par) {
  if (size > 0)
    MapInOrder(fun, par, &Root());
}

/* ************************************************************************** */

// Specific member functions (inherited from InOrderFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if (size > 0)
    FoldInOrder(fun, par, acc, &Root());
}

/* ************************************************************************** */

// Specific member functions (inherited from BreadthMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par) {
  if (size > 0)
    MapBreadth(fun, par, &Root());
}

/* ************************************************************************** */

// Specific member functions (inherited from BreadthFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const {
  if (size > 0)
    FoldBreadth(fun, par, acc, &Root());
}

/* ************************************************************************** */

// Auxiliary member functions (for MappableContainer)

template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par, Node* node) {
  if (node != nullptr) {
    fun(node->Element(), par);
    if (node->HasLeftChild()) { MapPreOrder(fun, par, &node->LeftChild()); }
    if (node->HasRightChild()) { MapPreOrder(fun, par, &node->RightChild()); }
  }
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par, Node* node) {
  if (node != nullptr) {
    if (node->HasLeftChild()) { MapPostOrder(fun, par, &node->LeftChild()); }
    if (node->HasRightChild()) { MapPostOrder(fun, par, &node->RightChild()); }
    fun(node->Element(), par);
  }
}

// Auxiliary member functions (for InOrderMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par, Node* node) {
  if (node != nullptr) {
    if (node->HasLeftChild()) { MapInOrder(fun, par, &node->LeftChild()); }
    fun(node->Element(), par);
    if (node->HasRightChild()) { MapInOrder(fun, par, &node->RightChild()); }
  }
}

// Auxiliary member functions (for BreadthMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par, Node* node) {
  if (node != nullptr) {
    QueueLst<Node*> queue;
    queue.Enqueue(node);
    Node* tmp;
    while (!queue.Empty()) {
      tmp = queue.HeadNDequeue();
      fun(tmp->Element(), par);
      if (tmp->HasLeftChild()) { queue.Enqueue(&tmp->LeftChild()); }
      if (tmp->HasRightChild()) { queue.Enqueue(&tmp->RightChild()); }
    }
  }
}

/* ************************************************************************** */

// Auxiliary member functions (for FoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc, Node* node) const {
  if (node != nullptr) {
    fun(node->Element(), par, acc);
    if (node->HasLeftChild()) { FoldPreOrder(fun, par, acc, &node->LeftChild()); }
    if (node->HasRightChild()) { FoldPreOrder(fun, par, acc, &node->RightChild()); }
  }
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, Node* node) const {
  if (node != nullptr) {
    if (node->HasLeftChild()) { FoldPostOrder(fun, par, acc, &node->LeftChild()); }
    if (node->HasRightChild()) { FoldPostOrder(fun, par, acc, &node->RightChild()); }
    fun(node->Element(), par, acc);
  }
}

// Auxiliary member functions (for InOrderFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc, Node* node) const {
  if (node != nullptr) {
    if (node->HasLeftChild()) { FoldInOrder(fun, par, acc, &node->LeftChild()); }
    fun(node->Element(), par, acc);
    if (node->HasRightChild()) { FoldInOrder(fun, par, acc, &node->RightChild()); }
  }
}

// Auxiliary member functions (for BreadthFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc, Node* node) const {
  if (node != nullptr) {
    QueueLst<Node*> queue;
    queue.Enqueue(node);
    Node* tmp;
    while (!queue.Empty()) {
      tmp = queue.HeadNDequeue();
      fun(tmp->Element(), par, acc);
      if (tmp->HasLeftChild()) { queue.Enqueue(&tmp->LeftChild()); }
      if (tmp->HasRightChild()) { queue.Enqueue(&tmp->RightChild()); }
    }
  }
}

/* ************************************************************************** */

// PreOrderIterator

// Specific constructors

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& binaryTree) {
  if (binaryTree.Size() > 0)
    currNode = &(binaryTree.Root());
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& itr) {
  currNode = itr.currNode;
  stackLst = itr.stackLst;
}

// Move constructor

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& itr) noexcept {
  std::swap(currNode, itr.currNode);
  std::swap(stackLst, itr.stackLst);
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& itr) {
  BTPreOrderIterator<Data>* tmp = new BTPreOrderIterator<Data>(itr);
  std::swap(*this, *tmp);
  delete tmp;
  return *this;
}

// Move assignment

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& itr) noexcept {
  std::swap(currNode, itr.currNode);
  std::swap(stackLst, itr.stackLst);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator& itr) const noexcept {
  return (currNode == itr.currNode && stackLst == itr.stackLst);
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator& itr) const noexcept {
  return !(*this == itr);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
  return (currNode == nullptr);
}

template <typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
  if (currNode != nullptr)
    return currNode->Element();
  else
    throw std::out_of_range("Terminated");
}

/* ************************************************************************** */

// Specific member functions (inherited from ForwardIterator)

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
  if (currNode != nullptr) {

    if (currNode->HasLeftChild()) {

      if (currNode->HasRightChild())
        stackLst.Push(&currNode->RightChild());

      currNode = &(currNode->LeftChild());
    } else {

      if (currNode->HasRightChild())
        currNode = &(currNode->RightChild());

      else if (!stackLst.Empty())
        currNode = stackLst.TopNPop();
      else
        currNode = nullptr;
    }

  }
  else {
    throw std::out_of_range("Terminated!!");
  }
  return *this;
}

/* ************************************************************************** */

// PostOrderIterator

// Auxiliary member functions

template <typename Data>
typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::getLeftMostLeaf(typename BinaryTree<Data>::Node* node) {
  if (node->HasLeftChild()) {
    stackLst.Push(node);
    node = getLeftMostLeaf(&node->LeftChild());
  }

  if (node->HasRightChild()) {
    stackLst.Push(node);
    node = getLeftMostLeaf(&node->RightChild());
  }

  return node;
}

// Specific constructors

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& binaryTree) {
  if (binaryTree.Size() > 0) {
    currNode = getLeftMostLeaf(&binaryTree.Root());
  }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& itr) {
  currNode = itr.currNode;
  stackLst = itr.stackLst;
}

// Move constructor

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& itr) noexcept {
  std::swap(currNode, itr.currNode);
  std::swap(stackLst, itr.stackLst);
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& itr) {
  BTPostOrderIterator<Data>* tmp = new BTPostOrderIterator<Data>(itr);
  std::swap(*this, *tmp);
  delete tmp;
  return *this;
}

// Move assignment

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& itr) noexcept {
  std::swap(currNode, itr.currNode);
  std::swap(stackLst, itr.stackLst);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator& itr) const noexcept {
  return (currNode == itr.currNode && stackLst == itr.stackLst);
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator& itr) const noexcept {
  return !(*this == itr);
}

/* ************************************************************************** */

// Specific member functions (inherited from Iterator)

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
  return (currNode == nullptr);
}

template <typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
  if (currNode != nullptr)
    return currNode->Element();
  else
    throw std::out_of_range("Terminated");
}

/* ************************************************************************** */

// Specific member functions (inherited from ForwardIterator)

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
  if (currNode != nullptr) {
    if (!stackLst.Empty()) {
      if (stackLst.Top()->HasLeftChild() && currNode == &stackLst.Top()->LeftChild()) {

        if (stackLst.Top()->HasRightChild())
          currNode = getLeftMostLeaf(&stackLst.Top()->RightChild());
        else
          currNode = stackLst.TopNPop();

      }
      else
        currNode = stackLst.TopNPop();
    }
    else
      currNode = nullptr;

  }
  else {
    throw std::out_of_range("Terminated!!");
  }
  return *this;
}

/* ************************************************************************** */

// PostOrderIterator

// Auxiliary member functions

template <typename Data>
typename BinaryTree<Data>::Node* BTInOrderIterator<Data>::getLeftMostNode(typename BinaryTree<Data>::Node* node) {
  if (node->HasLeftChild()) {
    stackLst.Push(node);
    node = getLeftMostNode(&node->LeftChild());
  }
  return node;
}

// Specific constructors

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& binaryTree) {
  if (binaryTree.Size() > 0) {
    currNode = getLeftMostNode(&binaryTree.Root());
  }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& itr) {
  currNode = itr.currNode;
  stackLst = itr.stackLst;
}

// Move constructor

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& itr) noexcept {
  std::swap(currNode, itr.currNode);
  std::swap(stackLst, itr.stackLst);
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& itr) {
  BTInOrderIterator<Data>* tmp = new BTInOrderIterator<Data>(itr);
  std::swap(*this, *tmp);
  delete tmp;
  return *this;
}

// Move assignment

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& itr) noexcept {
  std::swap(currNode, itr.currNode);
  std::swap(stackLst, itr.stackLst);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator& itr) const noexcept {
  return (currNode == itr.currNode && stackLst == itr.stackLst);
}

template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator& itr) const noexcept {
  return !(*this == itr);
}

/* ************************************************************************** */

// Specific member functions (inherited from Iterator)

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
  return (currNode == nullptr);
}

template <typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
  if (currNode != nullptr)
    return currNode->Element();
  else
    throw std::out_of_range("Terminated");
}

/* ************************************************************************** */

// Specific member functions (inherited from ForwardIterator)

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
  if (currNode != nullptr) {

    if (currNode->HasRightChild()) {
      currNode = getLeftMostNode(&currNode->RightChild());
    } else if (!stackLst.Empty())
      currNode = stackLst.TopNPop();
    else
      currNode = nullptr;

  } else {
    throw std::out_of_range("Terminated!!");
  }
  return *this;
}

/* ************************************************************************** */

// BTBreadthIterator

// Specific constructors

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& binaryTree) {
  if (binaryTree.Size() > 0) {
    currNode = &binaryTree.Root();
  }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& itr) {
  currNode = itr.currNode;
  queueLst = itr.queueLst;
}

// Move constructor

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& itr) noexcept {
  std::swap(currNode, itr.currNode);
  std::swap(queueLst, itr.queueLst);
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& itr) {
  BTBreadthIterator<Data>* tmp = new BTBreadthIterator<Data>(itr);
  std::swap(*this, *tmp);
  delete tmp;
  return *this;
}

// Move assignment

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& itr) noexcept {
  std::swap(currNode, itr.currNode);
  std::swap(queueLst, itr.queueLst);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator& itr) const noexcept {
  return (currNode == itr.currNode && queueLst == itr.queueLst);
}

template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator& itr) const noexcept {
  return !(*this == itr);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
  return (currNode == nullptr);
}

template <typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
  if (currNode != nullptr)
    return currNode->Element();
  else
    throw std::out_of_range("Terminated");
}

/* ************************************************************************** */

// Specific member functions (inherited from ForwardIterator)

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
  if (currNode != nullptr) {

    if (currNode->HasLeftChild())
      queueLst.Enqueue(&currNode->LeftChild());

    if (currNode->HasRightChild())
      queueLst.Enqueue(&currNode->RightChild());

    if (!queueLst.Empty())
      currNode = queueLst.HeadNDequeue();
    else
      currNode = nullptr;

  }
  else {
    throw std::out_of_range("Terminated!!");
  }
  return *this;
}

}
