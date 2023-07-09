
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>
using namespace std;

/* ************************************************************************** */

int main() {
  cout << "Lasd Libraries 2021" << endl;

  int choice = 0;
  bool exit = false;
  do {
    cout << "\nMenu'" << endl;
    cout << "1. Lasd test;" << endl;
    cout << "2. Salvatore's test;" << endl;
    cout << "0. Exit test." << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
      case 1: lasdtest();
      break;
      case 2: myMenu();
      break;
      case 0: {
        cout << "\nExit..." << endl;
        exit = true;
      }
      break;
      default:
        cout << "Unexpected behavior!" << endl;
    }
  } while(choice >= 0 && choice <=2 && exit == false);
  return 0;
}
