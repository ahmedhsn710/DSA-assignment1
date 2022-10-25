#include<fstream>
#include<iostream>
#include<string.h>
#include "Dictionary.h"
#include "List.h"
using namespace std;

void mainMenu() //menu function
{
  linkedList<Dictionary> list;
  string word, meaning; //stores the word and meaning
  char choice;  //stores user choice for the actions

  cout << "\e[1;35mInput 's' to terminate the program anytime.\e[0;37m" << endl;
  while (choice != 's') //while loop until 's' is entered
  {
    cout << "\n\x1b[36mPlease select an action: " << endl << endl;
    cout << "\t1. Read file data" << endl;
    cout << "\t2. Write to file" << endl;
    cout << "\t3. Print the list" <<endl;
    cout << "\t4. Print the reverse list" <<endl;
    cout << "\t5. Reverse the list" <<endl;
    cout << "\t6. filterby letter" <<endl;
    cout << "\t7. Rearrange by length" <<endl;
    cout << "\x1b[0m"; cin >> choice; cout << endl;
    switch(choice)  //switch statement to check user input and calling respective functions
    {
      case('1'):
      {
        readFileData(&(list.head));
      }; break;
      case('2'):
      {
        writeToFile(list.head);
      }; break;
      case('3'):
      {
        printList(list.head);
      }; break;
      case('4'):
      {
        printnodereverse(list.head);
      }; break;
      case('5'):
      {
        list.head = reverseList(list.head);
        writeToFile(list.head);
      }; break;
      case('6'):
      {
        string let;
        cout<<"Search for : ";
        cin>>let;
        list.head = filterByLetters(list.head, let);
        writeToFile(list.head);
      }; break;
      case('7'):
      {
        list.head = rearrangeByEvenOddLength(list.head);
        writeToFile(list.head);
      }; break;
      case('s'):
      {
        cout << "\e[1;33mProgram terminated." << endl;
      }; break;
      default:
        cout << "\x1b[31mInvalid action selected!\x1b[37m" << endl;
    }
  }
}


int main()
{
  mainMenu(); //call the main menu function from Parser.h
  return 0;
}