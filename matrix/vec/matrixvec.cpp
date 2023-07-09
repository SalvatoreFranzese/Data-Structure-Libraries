
namespace lasd {

/* ************************************************************************** */

// Default constructor

template <typename Data>
MatrixVec<Data>::MatrixVec() {
  rowNum = 0;
  columnNum = 0;
  size = 0;
  rowsVec.Resize(size);
}

/* ************************************************************************** */

// Specific constructors

template <typename Data>
MatrixVec<Data>::MatrixVec(const unsigned long rows, const unsigned long columns) {
  rowNum = rows;
  columnNum = columns;
  size = rowNum * columnNum;
  rowsVec.Resize(size);
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
MatrixVec<Data>::MatrixVec(const MatrixVec<Data>& matrix) {
  rowNum = matrix.rowNum;
  columnNum = matrix.columnNum;
  size = matrix.size;
  rowsVec = matrix.rowsVec;
}

// Move constructor

template <typename Data>
MatrixVec<Data>::MatrixVec(MatrixVec<Data>&& matrix) noexcept {
  std::swap(rowNum, matrix.rowNum);
  std::swap(columnNum, matrix.columnNum);
  std::swap(size, matrix.size);
  std::swap(rowsVec, matrix.rowsVec);
}

/* ************************************************************************** */

// Destructor

template <typename Data>
MatrixVec<Data>::~MatrixVec() {
  if (size > 0)
    Clear();
}

/* ************************************************************************ */

// Copy assignment

template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec<Data>& matrix) {
  MatrixVec<Data>* tmpMatrixVec = new MatrixVec<Data>(matrix);
  std::swap(*tmpMatrixVec, *this);
  delete tmpMatrixVec;
  return *this;
}

// Move assignment

template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& matrix) noexcept {
  std::swap(rowNum, matrix.rowNum);
  std::swap(columnNum, matrix.columnNum);
  std::swap(size, matrix.size);
  std::swap(rowsVec, matrix.rowsVec);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool MatrixVec<Data>::operator==(const MatrixVec<Data>& matrix) const noexcept {
  return (rowNum == matrix.rowNum && columnNum == matrix.columnNum && rowsVec == matrix.rowsVec);
}

template <typename Data>
bool MatrixVec<Data>::operator!=(const MatrixVec<Data>& matrix) const noexcept {
  return !(*this == matrix);
}

/* ************************************************************************** */

// Specific member functions (inherited from Matrix)

template <typename Data>
void MatrixVec<Data>::RowResize(const unsigned long newRowNumber) {
  if (newRowNumber == 0)
    rowsVec.Clear();
  else if (rowNum != newRowNumber) {
    size = newRowNumber * columnNum;
    rowsVec.Resize(size);
  }
  rowNum = newRowNumber;
}

template <typename Data>
void MatrixVec<Data>::ColumnResize(const unsigned long newColumnNumber) {
  if (newColumnNumber == 0)
    rowsVec.Clear();
  else if (columnNum != newColumnNumber) {
    size = rowNum * newColumnNumber;
    Vector<Data> tmpMatrixVec(size);

    unsigned long limit = (newColumnNumber > columnNum) ? columnNum : newColumnNumber;

    for (unsigned long i = 0; i < rowNum; ++i) {
      for (unsigned long j = 0; j < limit; ++j) {
        std::swap(tmpMatrixVec[i * newColumnNumber + j], rowsVec[i * columnNum + j]);
      }
    }

    std::swap(tmpMatrixVec, rowsVec);
  }
  columnNum = newColumnNumber;
}

template <typename Data>
inline bool MatrixVec<Data>::ExistsCell(const unsigned long row, const unsigned long column) const noexcept {
  return (row < rowNum && column < columnNum);
}

template <typename Data>
Data& MatrixVec<Data>::operator()(const unsigned long row, const unsigned long column) {
  return const_cast<Data&>(static_cast<const Matrix<Data>*>(this)->operator()(row, column));
}

template <typename Data>
const Data& MatrixVec<Data>::operator()(const unsigned long row, const unsigned long column) const {
  if (row < rowNum && column < columnNum)
    return rowsVec[row * columnNum + column];
  else
    throw std::out_of_range("Cell doesn't exists!");
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void MatrixVec<Data>::Clear() {
  if (size > 0) {
    rowNum = 0;
    columnNum = 0;
    size = 0;
    rowsVec.Clear();
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void MatrixVec<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  rowsVec.MapPreOrder(fun, par);
}

template <typename Data>
void MatrixVec<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  rowsVec.MapPostOrder(fun, par);
}

/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void MatrixVec<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  rowsVec.FoldPreOrder(fun, par, acc);
}

template <typename Data>
void MatrixVec<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
  rowsVec.FoldPostOrder(fun, par, acc);
}

/* ************************************************************************** */

}
