
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
Vector<Data>::Vector(const unsigned long newsize) {
  Elements = new Data[newsize] {};
  size = newsize;
}

template <typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& container) {
  size = container.Size();
  Elements = new Data[size] {};
  for (unsigned long index = 0; index < size; ++index) {
    Elements[index] = container[index];
  }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vec) {
  Elements = new Data[vec.size] {};
  std::copy(vec.Elements, vec.Elements + vec.size, Elements);
  size = vec.size;
}

// Move constructor

template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
  std::swap(Elements, vec.Elements);
  std::swap(size, vec.size);
}

/* ************************************************************************** */

// Destructor

template <typename Data>
Vector<Data>::~Vector() {
  Clear();
  delete[] Elements;
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec) {
  Vector<Data>* tmpVec = new Vector<Data>(vec);
  std::swap(*tmpVec, *this);
  delete tmpVec;
  return *this;
}

// Move assignment

template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept {
  std::swap(Elements, vec.Elements);
  std::swap(size, vec.size);
  return *this;
}


/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept {
  if(size == vec.size) {
    for (unsigned long index = 0; index < size; ++index) {
      if (Elements[index] != vec.Elements[index])
        return false;
    }
    return true;
  } else {
    return false;
  }
}

template <typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept {
  return !(*this == vec);
}

/* ************************************************************************ */

// Specific member functions

template <typename Data>
void Vector<Data>::Resize(const unsigned long newsize) {
  if (newsize == 0)
    Clear();
  else if (size != newsize) {
    unsigned long limit = (size < newsize) ? size : newsize;
    Data* tmpElements = new Data[newsize] {};
    for (unsigned long index = 0; index < limit; ++index) {
      std::swap(Elements[index], tmpElements[index]);
    }
    std::swap(Elements, tmpElements);
    size = newsize;
    delete[] tmpElements;
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void Vector<Data>::Clear() {
  delete[] Elements;
  Elements = nullptr;
  size = 0;
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

template <typename Data>
Data& Vector<Data>::Front() const {
  if (size != 0)
    return Elements[0];
  else
    throw std::length_error("Access to an empty vector!");
}

template <typename Data>
Data& Vector<Data>::Back() const {
  if (size != 0)
    return Elements[size - 1];
  else
    throw std::length_error("Access to an empty vector!");
}

template <typename Data>
Data& Vector<Data>::operator[](const unsigned long index) const {
  if (index < size)
    return Elements[index];
  else
    throw std::out_of_range("Access at index " + std::to_string(index) + "; vector size " + std::to_string(size) + ".");
}

/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void Vector<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  for (unsigned long index = 0; index < size; ++index) {
    fun(Elements[index], par);
  }
}

template <typename Data>
void Vector<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  unsigned long index = size;
  while (index > 0) {
    fun(Elements[--index], par);
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void Vector<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  for (unsigned long index = 0; index < size; ++index) {
    fun(Elements[index], par, acc);
  }
}

template <typename Data>
void Vector<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
  unsigned long index = size;
  while (index > 0) {
    fun(Elements[--index], par, acc);
  }
}

}
