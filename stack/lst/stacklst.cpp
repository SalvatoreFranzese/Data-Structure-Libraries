
namespace lasd {

/* ************************************************************************ */

// Specific constructor

template <typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& container) {
  if (container.Size() > 0) {
    size = container.Size();
    for (unsigned long index = size - 1; index > -1; --index) {
      Push(container[index]);
    }
  }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& stackList) {
  if (stackList.head != nullptr) {
    head = new Node(stackList.head->data);
    Node* tmpStackList = head;
    Node* curr = stackList.head->next;
    while (curr != nullptr) {
      tmpStackList->next = new Node(curr->data);
      tmpStackList = tmpStackList->next;
      curr = curr->next;
    }
  } else {
    head = nullptr;
  }
  size = stackList.size;
}

// Move constructor

template <typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& stackList) noexcept {
  std::swap(size, stackList.size);
  std::swap(head, stackList.head);
}

/* ************************************************************************ */

// Copy assignment

template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stackList) {
  List<Data>::operator=(stackList);
  return *this;
}

// Move assignment

template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stackList) noexcept {
  std::swap(size, stackList.size);
  std::swap(head, stackList.head);
  return *this;
}

/* ************************************************************************ */

// Comparison operators

template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& stackList) const noexcept {
  return List<Data>::operator==(stackList);
}

template <typename Data>
inline bool StackLst<Data>::operator!=(const StackLst<Data>& stackList) const noexcept {
  return List<Data>::operator!=(stackList);
}

/* ************************************************************************** */

// Specific member functions (inherited from Stack)

template <typename Data>
void StackLst<Data>::Push(const Data& data) {
  List<Data>::InsertAtFront(data);
}

template <typename Data>
void StackLst<Data>::Push(Data&& data) noexcept {
  List<Data>::InsertAtFront(std::move(data));
}

template <typename Data>
Data& StackLst<Data>::Top() const {
  return List<Data>::Front();
}

template <typename Data>
void StackLst<Data>::Pop() {
  List<Data>::RemoveFromFront();
}

template <typename Data>
Data StackLst<Data>::TopNPop() {
  return List<Data>::FrontNRemove();
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void StackLst<Data>::Clear() {
  if (head != nullptr) {
    while (head != nullptr) {
      Node* tmp = head;
      head = head->next;
      delete tmp;
    }
    head = nullptr;
    size = 0;
  }
}

/* ************************************************************************** */

}
