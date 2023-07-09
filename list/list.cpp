
namespace lasd {

/* ************************************************************************** */

// Node

// Specific constructors

template <typename Data>
List<Data>::Node::Node(const Data& dat) {
  data = dat;
  next = nullptr;
}

template <typename Data>
List<Data>::Node::Node(Data&& dat) noexcept {
  std::swap(data, dat);
  next = nullptr;
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
List<Data>::Node::Node(const Node& node) {
  data = node.data;
  next = node.next;
}

// Move constructor

template <typename Data>
List<Data>::Node::Node(Node&& node) noexcept {
  std::swap(data, node.data);
  std::swap(next, node.next);
}

/* ********************************************************************** */

// Comparison operators

template <typename Data>
bool List<Data>::Node::operator==(const Node& node) const noexcept {
  if (data == node.data && next == node.next)
    return true;
  return false;
}

template <typename Data>
inline bool List<Data>::Node::operator!=(const Node& node) const noexcept {
  return !(*this == node);
}

/* ************************************************************************** */

// List

// Specific constructor

template <typename Data>
List<Data>::List(const LinearContainer<Data>& container) {
  if (container.Size() > 0) {
    Node *curr = new Node(container[0]);
    head = curr;
    size = container.Size();
    unsigned long index = 1;
    while (index < container.Size()) {
      curr->next = new Node(container[index]);
      tail = curr->next;
      curr = curr->next;
      index++;
    }
  }
}

// Copy constructor

template <typename Data>
List<Data>::List(const List<Data>& list) {
  if (list.head != nullptr) {
    head = new Node(list.head->data);
    Node* tmpList = head;
    Node* curr = list.head->next;
    while (curr != nullptr) {
      tmpList->next = new Node(curr->data);
      tmpList = tmpList->next;
      curr = curr->next;
    }
    tail = tmpList;
  } else {
    head = tail = nullptr;
  }
  size = list.size;
}

// Move constructor

template <typename Data>
List<Data>::List(List<Data>&& list) noexcept {
  std::swap(size, list.size);
  std::swap(head, list.head);
  std::swap(tail, list.tail);
}

/* ************************************************************************** */

// Destructor

template <typename Data>
List<Data>::~List() {
  Clear();
  delete head;
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& list) {
  List<Data>* tmpList = new List<Data>(list);
  std::swap(*tmpList, *this);
  delete tmpList;
  return *this;
}

// Move assignment

template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& list) noexcept {
  std::swap(head, list.head);
  std::swap(tail, list.tail);
  std::swap(size, list.size);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool List<Data>::operator==(const List<Data>& list) const noexcept {
  if (size == list.size) {
    Node* tmp = head; // list 1
    Node* curr = list.head; // list 2
    while (curr != nullptr) {
      if(tmp->data != curr->data) {
        return false;
      }
      curr = curr->next;
      tmp = tmp->next;
    }
    return true;
  } else {
    return false;
  }
}

template <typename Data>
inline bool List<Data>::operator!=(const List<Data>& list) const noexcept {
  return !(*this == list);
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
void List<Data>::InsertAtFront(const Data& dat) {
  Node* newNode = new Node(dat);
  if (size == 0) {
    tail = newNode;
  } else {
    newNode->next = head;
  }
  head = newNode;
  size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& dat) noexcept {
  Node* newNode = new Node(std::move(dat));
  if (size == 0) {
    tail = newNode;
  } else {
    newNode->next = head;
  }
  head = newNode;
  size++;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
  if (head != nullptr) {
    Node* tmp = head;
    head = head->next;
    size--;
    delete tmp;
  } else {
    throw std::length_error("Access to an empty list!!");
  }
}

template <typename Data>
Data List<Data>::FrontNRemove() {
  if (head != nullptr) {
    Data dat = std::move(Front());
    RemoveFromFront();
    return dat;
  } else {
    throw std::length_error("Access to an empty list!!");
  }
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& dat) {
  if (head != nullptr) {
    tail->next = new Node(dat);
    tail = tail->next;
    size++;
  } else {
    InsertAtFront(dat);
  }
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& dat) noexcept{
  if (head != nullptr) {
    tail->next = new Node(std::move(dat));
    tail = tail->next;
    size++;
  } else {
    InsertAtFront(dat);
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void List<Data>::Clear() {
  if (head != nullptr) {
    while (head != nullptr) {
      Node* tmp = head;
      head = head->next;
      delete tmp;
    }
    head = tail = nullptr;
    size = 0;
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

template <typename Data>
Data& List<Data>::Front() const {
  if (head != nullptr)
    return head->data;
  else
    throw std::length_error("Access to an empty list!!");
}

template <typename Data>
Data& List<Data>::Back() const {
  if (head != nullptr)
    return tail->data;
  else
    throw std::length_error("Access to an empty list!!");
}

template <typename Data>
Data& List<Data>::operator[](unsigned long index) const {
  if (head != nullptr && index < size) {
    Node* curr = head;
    unsigned long i = 0;
    while (curr->next != nullptr && i < index) {
      curr = curr->next;
      ++i;
    }
    return curr->data;
  } else {
    throw std::out_of_range("Access at index " + std::to_string(index) + "; list size " + std::to_string(size) + ".");
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
inline void List<Data>::MapPreOrder(MapFunctor fun, void* par) {
  MapPreOrder(fun, par, head);
}

template <typename Data>
inline void List<Data>::MapPostOrder(MapFunctor fun, void* par) {
  MapPostOrder(fun, par, head);
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
inline void List<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc) const {
  FoldPreOrder(fun, par, acc, head);
}

template <typename Data>
inline void List<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc) const {
  FoldPostOrder(fun, par, acc, head);
}

/* ************************************************************************ */

// Auxiliary member functions (for MappableContainer)

template <typename Data>
void List<Data>::MapPreOrder(MapFunctor fun, void* par, Node* node) {
  while (node != nullptr) {
    fun(node->data, par);
    node = node->next;
  }
}

template <typename Data>
void List<Data>::MapPostOrder(MapFunctor fun, void* par, Node* node) {
   if (node != nullptr) {
      MapPostOrder(fun, par, node->next);
      fun(node->data, par);
   }
}

/* ************************************************************************ */

// Auxiliary member functions (for FoldableContainer)

template<typename Data>
void List<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc, Node* node) const {
  while (node != nullptr) {
    fun(node->data, par, acc);
    node = node->next;
  }
}

template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc, Node* node) const {
   if (node != nullptr) {
      FoldPostOrder(fun, par, acc, node->next);
      fun(node->data, par, acc);
   }
}

}
