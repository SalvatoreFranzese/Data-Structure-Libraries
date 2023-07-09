
namespace lasd {

/* ************************************************************************** */

// Default constructor

template <typename Data>
QueueVec<Data>::QueueVec() {
  size = 2;
  Elements = new Data[size] {};
  front = 0;
  rear = -1;
}

/* ************************************************************************** */

// Specific constructor

template <typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& container) {
  size = container.Size();
  Elements = new Data[size] {};
  for (unsigned long index = 0; index < size; ++index) {
    Elements[index] = container[index];
  }
  front = 0;
  rear = size - 1;
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec& queueVec) {
  Elements = new Data[queueVec.size] {};
  std::copy(queueVec.Elements, queueVec.Elements + queueVec.Size(), Elements);
  front = queueVec.front;
  rear = queueVec.rear;
  size = queueVec.size;
}

// Move constructor

template <typename Data>
QueueVec<Data>::QueueVec(QueueVec&& queueVec) noexcept : Vector<Data>::Vector(std::move(queueVec)) {
  std::swap(front, queueVec.front);
  std::swap(rear, queueVec.rear);
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queueVec) {
  QueueVec<Data>* tmpQueueVec = new QueueVec<Data>(queueVec);
  std::swap(*tmpQueueVec, *this);
  delete tmpQueueVec;
  return *this;
}

// Move assignment

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& queueVec) noexcept {
  Vector<Data>::operator=(std::move(queueVec));
  std::swap(front, queueVec.front);
  std::swap(rear, queueVec.rear);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& queueVec) const noexcept {
  if (queueVec.Size() == Size()) {
    unsigned long i = front;
    unsigned long j = queueVec.front;
    while (i != rear) {
      if (Elements[i] != queueVec.Elements[j])
        return false;
      i = (i+1) % size;
      j = (j+1) % size;
    }
    return true;
  }
  else
    return false;
}

template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& queueVec) const noexcept {
  return !(*this == queueVec);
}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)

template <typename Data>
void QueueVec<Data>::Enqueue(const Data& data) {
  if (Size() == size - 1) {
    Expand();
  }
  rear = (rear + 1) % size;
  Elements[rear] = data;
}

template <typename Data>
void QueueVec<Data>::Enqueue(Data&& data) noexcept {
  if (Size() == size - 1) {
    Expand();
  }
  rear = (rear + 1) % size;
  Elements[rear] = std::move(data);
}

template <typename Data>
Data& QueueVec<Data>::Head() const {
  if (Size() > 0) {
    return Elements[front];
  }
  else
    throw std::length_error("Access to an empty queue vector!");
}

template <typename Data>
void QueueVec<Data>::Dequeue() {
  if (Size() > 0) {
    front = (front + 1) % size;
    if (Size() < (size/4)) {
      Reduce();
    }
  }
  else
    throw std::length_error("Access to an empty queue vector!");
}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue() {
  if (Size() > 0) {
    Data data = std::move(Head());
    Dequeue();
    return data;
  } else {
    throw std::length_error("Access to an empty queue vector!");
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
inline bool QueueVec<Data>::Empty() const noexcept {
  return (Size() == 0);
}

template <typename Data>
inline unsigned long QueueVec<Data>::Size() const noexcept {
  return ((rear + (size + 1)) - front + 1) % (size + 1);
}

template <typename Data>
void QueueVec<Data>::Clear() {
  delete[] Elements;
  size = 2;
  Elements = new Data[size] {};
  front = 0;
  rear = -1;
}

/* ************************************************************************ */

// Auxiliary member functions

template <typename Data>
void QueueVec<Data>::Expand() {
  Vector<Data>::Resize(size*2);
}

template <typename Data>
void QueueVec<Data>::Reduce() {
  Vector<Data>::Resize(size*1.25);
}

}
