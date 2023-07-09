
namespace lasd {

/* ************************************************************************** */

// Default constructor

template <typename Data>
MatrixCSR<Data>::MatrixCSR() {
  rowsVec.Resize(1);
  rowsVec[0] = &head;
}

/* ************************************************************************** */

// Specific constructors

template <typename Data>
MatrixCSR<Data>::MatrixCSR(const unsigned long rows, const unsigned long columns) {
  rowNum = rows;
  columnNum = columns;
  rowsVec.Resize(rowNum + 1);

  for (unsigned long index = 0; index <= rowNum; ++index) {
    rowsVec[index] = &head;
  }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& matrix) : MatrixCSR(matrix.rowNum, matrix.columnNum) {
  for (unsigned long i = 0; i < rowNum; ++i) {
    for (Node** ptr = matrix.rowsVec[i]; ptr != matrix.rowsVec[i + 1]; ptr = &((*ptr)->next)) {
      Node& node = **ptr;
      (*this)(i, node.data.second) = node.data.first;
    }
  }
}

// Move constructor

template <typename Data>
MatrixCSR<Data>::MatrixCSR(MatrixCSR&& matrix) noexcept {
  std::swap(rowNum, matrix.rowNum);
  std::swap(columnNum, matrix.columnNum);
  std::swap(rowsVec, matrix.rowsVec);
  std::swap(head, matrix.head);
  std::swap(size, matrix.size);

  unsigned long index = 0;
  while (index < rowsVec.Size() && rowsVec[index] == &matrix.head) {
    rowsVec[index] = &head;
    ++index;
  }

  index = 0;
  while (index < matrix.rowsVec.Size() && matrix.rowsVec[index] == &head) {
    matrix.rowsVec[index] = &matrix.head;
    ++index;
  }
}

/* ************************************************************************** */

template <typename Data>
MatrixCSR<Data>::~MatrixCSR() {
  if (size > 0)
    Clear();
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data>& matrix) {
  MatrixCSR<Data>* tmpMatrixCSR = new MatrixCSR<Data>(matrix);
  std::swap(*tmpMatrixCSR, *this);
  delete tmpMatrixCSR;
  return *this;
}

// Move assignment

template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data>&& matrix) noexcept {
  std::swap(rowNum, matrix.rowNum);
  std::swap(columnNum, matrix.columnNum);
  std::swap(rowsVec, matrix.rowsVec);
  std::swap(head, matrix.head);
  std::swap(size, matrix.size);

  unsigned long index = 0;
  while (index < rowsVec.Size() && rowsVec[index] == &matrix.head) { // Le celle che puntavano a &matrix.head adesso puntano a &head
    rowsVec[index] = &head;
    ++index;
  }

  index = 0;
  while (index < matrix.rowsVec.Size() && matrix.rowsVec[index] == &head) { // Le celle che puntavano a &head adesso puntano a &matrix.head
    matrix.rowsVec[index] = &matrix.head;
    ++index;
  }

  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
inline bool MatrixCSR<Data>::operator==(const MatrixCSR<Data>& matrix) const noexcept {
  return (rowNum == matrix.rowNum) && (columnNum == matrix.columnNum) && List<std::pair<Data, unsigned long>>::operator==(matrix);
}

template <typename Data>
bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data>& matrix) const noexcept {
  return !(*this == matrix);
}

/* ************************************************************************** */

// Specific member functions (inherited from Matrix)

template <typename Data>
void MatrixCSR<Data>::RowResize(const unsigned long newRowNumber) {
  if (newRowNumber == 0) {
    List<std::pair<Data, unsigned long>>::Clear();
    rowsVec.Resize(1);
  }
  else if (newRowNumber > rowNum) {

    rowsVec.Resize(newRowNumber + 1);

    // Copio il puntatore dell'ultima cella (in posizione rowNum) nelle nuove celle
    for (unsigned long index = rowNum; index < newRowNumber; ++index) {
      rowsVec[index + 1] = rowsVec[rowNum];
    }
  }
  else if (newRowNumber < rowNum) {

    // Elimino i nodi a partire da newRowNumber
    Node* tmpDelete = *rowsVec[newRowNumber]; // Punto al next del nodo che precede il nodo da cui inizia la riga
    Node* tmpCurr = nullptr;

    // Scorro la lista e elimino i nodi
    while (tmpDelete != nullptr) {
      tmpCurr = tmpDelete->next;
      delete tmpDelete;
      tmpDelete = tmpCurr;
      --size;
    }

    rowsVec.Resize(newRowNumber + 1);
    *rowsVec[newRowNumber] = nullptr; // L'ultimo nodo avrà next = nullptr
  }
  rowNum = newRowNumber;
}

template <typename Data>
void MatrixCSR<Data>::ColumnResize(const unsigned long newColumnNumber) {
  if (newColumnNumber == 0) {
    List<std::pair<Data, unsigned long>>::Clear();
  }
  else if (newColumnNumber < columnNum) {
    unsigned long i = 0;
    Node** ptr = &head;

    // Scorro le righe
    while (i <= rowNum) {
      Node* node;
      Node** ext = rowsVec[i]; // puntatore alla prossima riga

      // Vado a trovare la colonna
      while (ptr != ext && (*ptr)->data.second < newColumnNumber) {
        node = *ptr;
        ptr = &(node->next);
      }

      if (ptr != ext) {
        // Cancellazione nodo
        Node* tmp = *ptr;
        *ptr = (*ptr)->next;
        delete tmp;
        --size;
      }

      // Aggiorno i puntatori
      while (i <= rowNum && rowsVec[i] == ext) {
        rowsVec[i] = ptr;
        ++i;
      }
    }
  }
  columnNum = newColumnNumber;
}

template <typename Data>
bool MatrixCSR<Data>::ExistsCell(const unsigned long row, const unsigned long column) const noexcept {
  if (row < rowNum && column < columnNum) {
    Node** ptr = rowsVec[row];

    while (ptr != rowsVec[row + 1]) {
      Node& node = **ptr;
      if (node.data.second == column)
        return true;

      ptr = &(node.next);
    }
  }
  return false;
}

template <typename Data>
Data& MatrixCSR<Data>::operator()(const unsigned long row, const unsigned long column) {
  if (row < rowNum && column < columnNum) {
    Node** ptr = rowsVec[row];

    // Cerco se esiste il nodo
    while (ptr != rowsVec[row + 1] && (*ptr)->data.second <= column) {
      Node& nodeCurr = **ptr;
      if (nodeCurr.data.second == column)
        return nodeCurr.data.first;

      ptr = &(nodeCurr.next);
    }

    // Creo il nuovo nodo
    std::pair<Data, unsigned long> data;
    data.second = column;
    Node* newNode = new Node(data);

    // Aggancio il nuovo nodo
    newNode->next = (*ptr); // Next del nuovo nodo punta al nodo corrente
    (*ptr) = newNode; // Il nodo corrente punta al nuovo nodo

    // Aggiorno il puntatore nel vec
    for (unsigned long index = row + 1; index < rowNum + 1 && rowsVec[index] == ptr; ++index) {
      rowsVec[index] = &(newNode->next);
    }

    ++size;

    return newNode->data.first;
  }
  else
    throw std::out_of_range("Cell doesn't exists!");
}

template <typename Data>
const Data& MatrixCSR<Data>::operator()(const unsigned long row, const unsigned long column) const {
  if (row < rowNum && column < columnNum) {
    Node** ptr = rowsVec[row];

    while (ptr != rowsVec[row + 1] && (*ptr)->data.second <= column) {
      Node& node = **ptr;
      if (node.data.second == column)
        return node.data.first;

      ptr = &(node.next);
    }
    throw std::length_error("Data doesn't exists!");
  }
  else
    throw std::out_of_range("Cell doesn't exists!");
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void MatrixCSR<Data>::Clear() {
  if (size > 0) {
    List<std::pair<Data, unsigned long>>::Clear();
    rowsVec.Resize(1);
    columnNum = 0;
    rowNum = 0;
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void MatrixCSR<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  List<std::pair<Data, unsigned long>>::MapPreOrder(
    [&fun](std::pair<Data, unsigned long>& dat, void* p) { fun(dat.first, p); }, par);
}

template <typename Data>
void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  List<std::pair<Data, unsigned long>>::MapPostOrder(
    [&fun](std::pair<Data, unsigned long>& dat, void* p) { fun(dat.first, p); }, par);
}

/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  List<std::pair<Data, unsigned long>>::FoldPreOrder(
    [&fun](const std::pair<Data, unsigned long>& dat, const void* p, void* a) { fun(dat.first, p, a); }, par, acc);
}

template <typename Data>
void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
  List<std::pair<Data, unsigned long>>::FoldPostOrder(
    [&fun](const std::pair<Data, unsigned long>& dat, const void* p, void* a) { fun(dat.first, p, a); }, par, acc);
}

}
