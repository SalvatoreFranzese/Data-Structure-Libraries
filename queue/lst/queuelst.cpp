
namespace lasd {

/* ************************************************************************** */

// Specific constructor

template <typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& container) {
  if (container.Size() > 0) {
    for (unsigned long index = 0; index < container.Size(); ++index) {
      Enqueue(container[index]);
    }
  }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data>& queueList) : List<Data>::List(queueList) {}

// Move constructor

template <typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data>&& queueList) noexcept : List<Data>::List(std::move(queueList)) {}

/* ************************************************************************ */

// Copy assignment

template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& queueList) {
  List<Data>::operator=(queueList);
  return *this;
}

// Move assignment

template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& queueList) noexcept {
  List<Data>::operator=(std::move(queueList));
  return *this;
}

/* ************************************************************************ */

// Comparison operators

template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& queueList) const noexcept {
  return List<Data>::operator==(queueList);
}

template <typename Data>
inline bool QueueLst<Data>::operator!=(const QueueLst& queueList) const noexcept {
  return List<Data>::operator!=(queueList);
}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)

template <typename Data>
void QueueLst<Data>::Enqueue(const Data& data) {
  List<Data>::InsertAtBack(data);
}

template <typename Data>
void QueueLst<Data>::Enqueue(Data&& data) noexcept {
  List<Data>::InsertAtBack(std::move(data));
}

template <typename Data>
Data& QueueLst<Data>::Head() const {
  return List<Data>::Front();
}

template <typename Data>
void QueueLst<Data>::Dequeue() {
  List<Data>::RemoveFromFront();
}

template <typename Data>
Data QueueLst<Data>::HeadNDequeue() {
  return List<Data>::FrontNRemove();
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void QueueLst<Data>::Clear() {
  List<Data>::Clear();
}

/* ************************************************************************** */

}
