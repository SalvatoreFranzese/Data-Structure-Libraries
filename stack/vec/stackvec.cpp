
namespace lasd {

/* ************************************************************************** */

// Default constructor

template <typename Data>
StackVec<Data>::StackVec() {
  size = 2;
  stackVecSize = 0;
  Elements = new Data[size] {};
}

/* ************************************************************************** */

template <typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data>& container) {
  size = container.Size();
  stackVecSize = size;
  Elements = new Data[size] {};
  for (unsigned long index = 0; index < size; ++index) {
    Elements[index] = container[index];
  }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& stackVec) {
  Elements = new Data[stackVec.size] {};
  std::copy(stackVec.Elements, stackVec.Elements + stackVec.stackVecSize, Elements);
  size = stackVec.size;
  stackVecSize = stackVec.stackVecSize;
}

// Move constructor

template <typename Data>
StackVec<Data>::StackVec(StackVec&& stackVec) noexcept : Vector<Data>::Vector(std::move(stackVec)) {
  std::swap(stackVecSize, stackVec.stackVecSize);
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stackVec) {
  StackVec<Data>* tmpStackVec = new StackVec<Data>(stackVec);
  std::swap(*tmpStackVec, *this);
  delete tmpStackVec;
  return *this;
}

// Move assignment

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stackVec) noexcept {
  Vector<Data>::operator=(std::move(stackVec));
  std::swap(stackVecSize, stackVec.stackVecSize);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& stackVec) const noexcept {
  if(stackVecSize == stackVec.stackVecSize) {
    for (unsigned long index = 0; index < stackVecSize; ++index) {
      if (Elements[index] != stackVec.Elements[index])
        return false;
    }
    return true;
  } else {
    return false;
  }
}

template <typename Data>
inline bool StackVec<Data>::operator!=(const StackVec<Data>& stackVec) const noexcept {
  return !(*this == stackVec);
}

/* ************************************************************************ */

// Specific member functions (inherited from Stack)

template <typename Data>
void StackVec<Data>::Push(const Data& data) {
  if (stackVecSize == size) {
    Expand();
  }
  Elements[stackVecSize] = data;
  stackVecSize++;
}

template <typename Data>
void StackVec<Data>::Push(Data&& data) noexcept {
  if (stackVecSize == size) {
    Expand();
  }
  Elements[stackVecSize] = std::move(data);
  stackVecSize++;
}

template <typename Data>
Data& StackVec<Data>::Top() const {
  if (stackVecSize != 0)
    return Elements[stackVecSize - 1];
  else
    throw std::length_error("Access to an empty stack vector!");
}

template <typename Data>
void StackVec<Data>::Pop() {
  if (stackVecSize != 0) {
    stackVecSize--;
    if (stackVecSize <= (size/4)) {
      Reduce();
    }
  } else {
    throw std::length_error("Access to an empty stack vector!");
  }
}

template <typename Data>
Data StackVec<Data>::TopNPop() {
  if (stackVecSize != 0) {
    Data data = std::move(Top());
    Pop();
    return data;
  } else {
    throw std::length_error("Access to an empty stack vector!");
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
inline bool StackVec<Data>::Empty() const noexcept {
  return (stackVecSize == 0);
}

template <typename Data>
inline unsigned long StackVec<Data>::Size() const noexcept {
  return stackVecSize;
}

template <typename Data>
void StackVec<Data>::Clear() {
  delete[] Elements;
  size = 2;
  Elements = new Data[size];
  stackVecSize = 0;
}

/* ************************************************************************ */

// Auxiliary member functions

template <typename Data>
void StackVec<Data>::Expand() {
  Vector<Data>::Resize(size*2);
}

template <typename Data>
void StackVec<Data>::Reduce() {
  Vector<Data>::Resize(size*1.25);
}

}
