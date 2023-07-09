#include <iostream>
#include <string>
#include <random>

#include "test.hpp"

#include "../vector/vector.hpp"

#include "../matrix/matrix.hpp"
#include "../matrix/vec/matrixvec.hpp"
#include "../matrix/csr/matrixcsr.hpp"

using namespace std;
using namespace lasd;


/* ************************************************************************** */

template <typename Data>
void print(const Data& dat, void* _) {
  cout << dat << " ";
}

/* ************************************************************************** */


void foldProduct(const int& dat, const void* par, void* acc) {
  if (dat < *(int*) par)
    *((int*) acc) *= dat;
}

void foldSum(const double& dat, const void* par, void* acc) {
  if (dat > *(double*) par)
    *((double*) acc) += dat;
}

void foldStringAppend(const string& dat, const void* par, void* acc) {
  if (dat.length() <= *(int*) par)
    *((string*)acc) += dat;
}

void selectFoldFunction(const MatrixVec<int>& matrix) {
  unsigned int n = 0, acc = 1;
  cout << "\nInsert value: ";
  cin >> n;
  matrix.FoldPreOrder(&foldProduct, &n, &acc);
  cout << "The product of all the values smaller than " << n << " is: " << acc << endl;
}

void selectFoldFunction(const MatrixVec<double>& matrix) {
  double n = 0, acc = 0;
  cout << "\nInsert value: ";
  cin >> n;
  matrix.FoldPreOrder(&foldSum, &n, &acc);
  cout << "The sum of all the values bigger than " << n << " is: " << acc << endl;
}

void selectFoldFunction(const MatrixVec<string>& matrix) {
  unsigned int n = 0;
  string acc{""};
  cout << "\nInsert value: ";
  cin >> n;
  matrix.FoldPreOrder(&foldStringAppend, &n, &acc);
  cout << "The concatenation of all strings shorter than or equal to " << n << " is: " << acc << endl;
}

/* ************************************************************************** */

void mapDouble(int& dat, void* _) {
  cout << (dat *= 2) << " ";
}

void mapCube(double& dat, void* _) {
  cout << (dat = dat * dat * dat) << " ";
}

void mapConcatenationRoot(string& dat, void* str) {
  cout << (dat = (*(string*)str) + dat) << " ";
}

void selectMapFunction(MatrixVec<int>& matrix) {
  cout << "\nFunction: 2*n" << endl;
  matrix.MapPreOrder(&mapDouble, nullptr);
  cout << "\nElements modified correctly!" << endl;
}

void selectMapFunction(MatrixVec<double>& matrix) {
  cout << "\nFunction: n^3" << endl;
  matrix.MapPreOrder(&mapCube, nullptr);
  cout << "\nElements modified correctly!" << endl;
}

void selectMapFunction(MatrixVec<string>& matrix) {
  cout << "\nFunction: concatenation string in root" << endl;
  string str;
  cout << "Insert string: ";
  cin >> str;
  matrix.MapPreOrder(&mapConcatenationRoot, &str);
  cout << "\nElements modified correctly!" << endl;
}

/* ************************************************************************** */

string genRandomString(int lengthString) {
  default_random_engine seed(lengthString);
  uniform_int_distribution<char> fillString('a','z');

  char str[lengthString + 1];
  for (unsigned int i = 0; i < lengthString; ++i) {
    str[i] = fillString(seed);
  }
  str[lengthString] = '\0';

  return str;
}

/* ************************************************************************** */

void fillMatrixVec(MatrixVec<int>& matrix, unsigned long row, unsigned long column) {
  default_random_engine generator(random_device{}());
  uniform_int_distribution<unsigned int> distribution(0, 100);

  for (ulong i = 0; i < row; ++i) {
    for (ulong j = 0; j < column; ++j) {
      matrix(i,j) = distribution(generator);
    }
  }
}

void fillMatrixVec(MatrixVec<double>& matrix, unsigned long row, unsigned long column) {
  default_random_engine generator(random_device{}());
  uniform_real_distribution<double> distribution(0, 100);

  for (ulong i = 0; i < row; ++i) {
    for (ulong j = 0; j < column; ++j) {
      matrix(i,j) = distribution(generator);
    }
  }
}

void fillMatrixVec(MatrixVec<string>& matrix, unsigned long row, unsigned long column) {
  default_random_engine generator(random_device{}());
  uniform_int_distribution<int> distribution(1,15);

  for (ulong i = 0; i < row; ++i) {
    for (ulong j = 0; j < column; ++j) {
      matrix(i,j) = genRandomString(distribution(generator));
    }
  }
}

/* ************************************************************************** */

template <typename Data>
void MenuMatrixVec() {

  unsigned long row = 0;
  unsigned long column = 0;
  do {
    cout << "\nInsert row number: ";
    cin >> row;
    cout << "Insert column number: ";
    cin >> column;
    if (row <= 0 || column <= 0)
      cout << "Insert a number > 0!" << endl;
  } while (row <= 0 || column <= 0);

  MatrixVec<Data> matrix(row,column);
  fillMatrixVec(matrix, row, column);

  int choice = 0;
  bool exit = false;
  do {
    cout << "\nMATRIX VECTOR MENU'" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Read Value" << endl;
    cout << "3. Row/Column Number" << endl;
    cout << "4. Row Resize" << endl;
    cout << "5. Column Resize" << endl;
    cout << "6. PreOrder/PostOrder Element" << endl;
    cout << "7. Exists" << endl;
    cout << "8. Fold Function" << endl;
    cout << "9. Map Function" << endl;
    cout << "10. Size" << endl;
    cout << "11. Is Empty" << endl;
    cout << "12. Clear Data Structure" << endl;
    cout << "0. Return back" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
      case 1: {
        Data val;
        unsigned long i = 0;
        unsigned long j = 0;
        cout << "\nInsert index row: ";
        cin >> i;
        cout << "Insert index column: ";
        cin >> j;
        cout << "\nInsert value: ";
        cin >> val;
        if (matrix.ExistsCell(i,j))
          matrix(i,j) = val;
        else
          cout << "\nRow/Column NOT Exists!" << endl;
      }
      break;
      case 2: {
        unsigned long i = 0;
        unsigned long j = 0;
        cout << "\nInsert index row";
        cin >> i;
        cout << "Insert index column";
        cin >> j;
        if (matrix.ExistsCell(i,j))
          cout << "\nValue: " << matrix(i,j) << endl;
        else
          cout << "\nRow/Column NOT Exists!" << endl;
      }
      break;
      case 3: {
        cout << "\nRow number: " << matrix.RowNumber() << endl;
        cout << "Column number: " << matrix.ColumnNumber() << endl;
      }
      break;
      case 4: {
        unsigned long i = 0;
        cout << "\nInsert new row number: ";
        cin >> i;
        matrix.RowResize(i);
        cout << "Row number changed successfully!!!" << endl;
      }
      break;
      case 5: {
        unsigned long j = 0;
        cout << "\nInsert new column number: ";
        cin >> j;
        matrix.ColumnResize(j);
        cout << "Column number changed successfully!!!" << endl;
      }
      break;
      case 6: {
        cout << "\nPreOrder: ";
        matrix.MapPreOrder(&print<Data>, &matrix);

        cout << "\nPostOrder: ";
        matrix.MapPostOrder(&print<Data>, &matrix);

        cout << "" << endl;
      }
      break;
      case 7: {
        Data val;
        cout << "\nInsert value: ";
        cin >> val;
        if (matrix.Exists(val))
          cout << "The value " << val << " Exists!" << endl;
        else
          cout << "The value " << val << " NOT Exists!" << endl;
      }
      break;
      case 8: {
        selectFoldFunction(matrix);
      }
      break;
      case 9: {
        selectMapFunction(matrix);
      }
      break;
      case 10: {
        cout << "\nSize Matrix: " << matrix.Size() << endl;
      }
      break;
      case 11: {
        if (matrix.Empty())
          cout << "\nThe data structure is empty!" << endl;
        else
          cout << "\nThe data structure is NOT empty!" << endl;
      }
      break;
      case 12: {
        matrix.Clear();
        cout << "\nData was deleted successfully" << endl;
      }
      break;
      case 0: {
        exit = true;
        cout << "\nReturn Back..." << endl;
      }
      break;
      default:
        cout << "Unexpected behavior!" << endl;
    }
  } while(choice >= 0 && choice <= 12 && exit == false);
}

/* ************************************************************************** */

void selectFoldFunction(const MatrixCSR<int>& matrix) {
  unsigned int n = 0, acc = 1;
  cout << "\nInsert value: ";
  cin >> n;
  matrix.FoldPreOrder(&foldProduct, &n, &acc);
  cout << "The product of all the values smaller than " << n << " is: " << acc << endl;
}

void selectFoldFunction(const MatrixCSR<double>& matrix) {
  double n = 0, acc = 0;
  cout << "\nInsert value: ";
  cin >> n;
  matrix.FoldPreOrder(&foldSum, &n, &acc);
  cout << "The sum of all the values bigger than " << n << " is: " << acc << endl;
}

void selectFoldFunction(const MatrixCSR<string>& matrix) {
  unsigned int n = 0;
  string acc{""};
  cout << "\nInsert value: ";
  cin >> n;
  matrix.FoldPreOrder(&foldStringAppend, &n, &acc);
  cout << "The concatenation of all strings shorter than or equal to " << n << " is: " << acc << endl;
}

/* ************************************************************************** */

void selectMapFunction(MatrixCSR<int>& matrix) {
  cout << "\nFunction: 2*n" << endl;
  matrix.MapPreOrder(&mapDouble, nullptr);
  cout << "\nElements modified correctly!" << endl;
}

void selectMapFunction(MatrixCSR<double>& matrix) {
  cout << "\nFunction: n^3" << endl;
  matrix.MapPreOrder(&mapCube, nullptr);
  cout << "\nElements modified correctly!" << endl;
}

void selectMapFunction(MatrixCSR<string>& matrix) {
  cout << "\nFunction: concatenation string in root" << endl;
  string str;
  cout << "Insert string: ";
  cin >> str;
  matrix.MapPreOrder(&mapConcatenationRoot, &str);
  cout << "\nElements modified correctly!" << endl;
}

/* ************************************************************************** */

void fillMatrixCSR(MatrixCSR<int>& matrix, unsigned long row, unsigned long column) {
  default_random_engine generator(random_device{}());
  uniform_int_distribution<unsigned int> distribution(0, 100);

  uniform_int_distribution<unsigned int> rowRandom(0, row - 1);
  uniform_int_distribution<unsigned int> columnRandom(0, column - 1);

  for (ulong i = 0; i < row; ++i) {
    for (ulong j = 0; j < column; ++j) {
      matrix(rowRandom(generator),columnRandom(generator)) = distribution(generator);
    }
  }
}

void fillMatrixCSR(MatrixCSR<double>& matrix, unsigned long row, unsigned long column) {
  default_random_engine generator(random_device{}());
  uniform_real_distribution<double> distribution(0, 100);

  uniform_int_distribution<unsigned int> rowRandom(0, row - 1);
  uniform_int_distribution<unsigned int> columnRandom(0, column - 1);

  for (ulong i = 0; i < row; ++i) {
    for (ulong j = 0; j < column; ++j) {
      matrix(rowRandom(generator),columnRandom(generator)) = distribution(generator);
    }
  }
}

void fillMatrixCSR(MatrixCSR<string>& matrix, unsigned long row, unsigned long column) {
  default_random_engine generator(random_device{}());
  uniform_int_distribution<int> distribution(1,15);

  uniform_int_distribution<unsigned int> rowRandom(0, row - 1);
  uniform_int_distribution<unsigned int> columnRandom(0, column - 1);

  for (ulong i = 0; i < row; ++i) {
    for (ulong j = 0; j < column; ++j) {
      matrix(rowRandom(generator),columnRandom(generator)) = genRandomString(distribution(generator));
    }
  }
}

/* ************************************************************************** */

template <typename Data>
void MenuMatrixCSR() {

  unsigned long row = 0;
  unsigned long column = 0;
  do {
    cout << "\nInsert row number: ";
    cin >> row;
    cout << "Insert column number: ";
    cin >> column;
    if (row <= 0 || column <= 0)
      cout << "Insert a number > 0!" << endl;
  } while (row <= 0 || column <= 0);

  MatrixCSR<Data> matrix(row, column);
  fillMatrixCSR(matrix, row, column);

  int choice = 0;
  bool exit = false;
  do {
    cout << "\nMATRIX CSR MENU'" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Read Value" << endl;
    cout << "3. Row/Column Number" << endl;
    cout << "4. Row Resize" << endl;
    cout << "5. Column Resize" << endl;
    cout << "6. PreOrder/PostOrder Element" << endl;
    cout << "7. Exists" << endl;
    cout << "8. Fold Function" << endl;
    cout << "9. Map Function" << endl;
    cout << "10. Size" << endl;
    cout << "11. Is Empty" << endl;
    cout << "12. Clear Data Structure" << endl;
    cout << "0. Return back" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
      case 1: {
        Data val;
        unsigned long i = 0;
        unsigned long j = 0;
        cout << "\nInsert index row: ";
        cin >> i;
        cout << "Insert index column: ";
        cin >> j;
        cout << "\nInsert value: ";
        cin >> val;
        matrix(i,j) = val;
      }
      break;
      case 2: {
        unsigned long i = 0;
        unsigned long j = 0;
        cout << "\nInsert index row: ";
        cin >> i;
        cout << "Insert index column: ";
        cin >> j;
        if (matrix.ExistsCell(i,j))
          cout << "\nValue: " << matrix(i,j) << endl;
        else
          cout << "\nRow/Column NOT Exists!" << endl;
      }
      break;
      case 3: {
        cout << "\nRow number: " << matrix.RowNumber() << endl;
        cout << "Column number: " << matrix.ColumnNumber() << endl;
      }
      break;
      case 4: {
        unsigned long i = 0;
        cout << "\nInsert new row number: ";
        cin >> i;
        matrix.RowResize(i);
        cout << "Row number changed successfully!!!" << endl;
      }
      break;
      case 5: {
        unsigned long j = 0;
        cout << "\nInsert new column number: ";
        cin >> j;
        matrix.ColumnResize(j);
        cout << "Column number changed successfully!!!" << endl;
      }
      break;
      case 6: {
        cout << "\nPreOrder: ";
        matrix.MapPreOrder(&print<Data>, &matrix);

        cout << "\nPostOrder: ";
        matrix.MapPostOrder(&print<Data>, &matrix);

        cout << "" << endl;
      }
      break;
      case 7: {
        Data val;
        cout << "\nInsert value: ";
        cin >> val;
        if (matrix.Exists(val))
          cout << "The value " << val << " Exists!" << endl;
        else
          cout << "The value " << val << " NOT Exists!" << endl;
      }
      break;
      case 8: {
        selectFoldFunction(matrix);
      }
      break;
      case 9: {
        selectMapFunction(matrix);
      }
      break;
      case 10: {
        cout << "\nSize Matrix: " << matrix.Size() << endl;
      }
      break;
      case 11: {
        if (matrix.Empty())
          cout << "\nThe data structure is empty!" << endl;
        else
          cout << "\nThe data structure is NOT empty!" << endl;
      }
      break;
      case 12: {
        matrix.Clear();
        cout << "\nData was deleted successfully" << endl;
      }
      break;
      case 0: {
        exit = true;
        cout << "\nReturn Back..." << endl;
      }
      break;
      default:
        cout << "Unexpected behavior!" << endl;
    }
  } while(choice >= 0 && choice <= 12 && exit == false);
}

void myMenu() {
  unsigned int choiceRapp = 0;
  bool exit = false;
  do {
    cout << "\nChoose a rappresentation:" << endl;
    cout << "1. Matrix Vector" << endl;
    cout << "2. Compressed Sparse Row" << endl;
    cout << "0. Reselect test" << endl;
    cout << "Enter your choice: ";
    cin >> choiceRapp;
    switch (choiceRapp) {
      case 1: {
        unsigned int choiceType = 0;
        bool exit = false;
        do {
          cout << "\nChoose the data type:" << endl;
          cout << "1. Integer" << endl;
          cout << "2. Double" << endl;
          cout << "3. String" << endl;
          cout << "0. Reselect rappresentation" << endl;
          cout << "Enter your choice: ";
          cin >> choiceType;
          switch (choiceType) {
            case 1: MenuMatrixVec<int>();
            break;
            case 2: MenuMatrixVec<double>();
            break;
            case 3: MenuMatrixVec<string>();
            break;
            case 0: {
              exit = true;
              cout << "\nReturn Back..." << endl;
            }
            break;
            default:
              cout << "Unexpected behavior!" << endl;
          }
        } while(choiceType >= 0 && choiceType <= 3 && exit == false);
      }
      break;
      case 2: {
        unsigned int choiceType = 0;
        bool exit = false;
        do {
          cout << "\nChoose the data type:" << endl;
          cout << "1. Integer" << endl;
          cout << "2. Double" << endl;
          cout << "3. String" << endl;
          cout << "0. Reselect rappresentation" << endl;
          cout << "Enter your choice: ";
          cin >> choiceType;
          switch (choiceType) {
            case 1: MenuMatrixCSR<int>();
            break;
            case 2: MenuMatrixCSR<double>();
            break;
            case 3: MenuMatrixCSR<string>();
            break;
            case 0: {
              exit = true;
              cout << "\nReturn Back..." << endl;
            }
            break;
            default:
              cout << "Unexpected behavior!" << endl;
          }
        } while(choiceType >= 0 && choiceType <= 3 && exit == false);
      }
      break;
      case 0: {
        exit = true;
        cout << "\nReturn Back..." << endl;
      }
      break;
      default:
        cout << "Unexpected behavior!" << endl;
    }
  } while(choiceRapp >= 0 && choiceRapp <= 2 && exit == false);
}
