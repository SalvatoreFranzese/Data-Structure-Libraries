
namespace lasd {

/* ************************************************************************** */

template <typename Data>
unsigned long Matrix<Data>::RowNumber() const noexcept {
  return rowNum;
}

template <typename Data>
unsigned long Matrix<Data>::ColumnNumber() const noexcept {
  return columnNum;
}

/* ************************************************************************** */

}
