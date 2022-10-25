#include <iostream>
#include "Dictionary.h"
using namespace std;

//templated defination of ListNode
template <typename T>
class ListNode{   
  public:
    T data;
    ListNode *next;
    ListNode(T val){
      data = val;
      next = nullptr;
    }
};

//templated defination of linkedList
template <typename L>
class linkedList{
public:
    int length;
    ListNode<L> * head;
    ListNode<L> * loc;
    ListNode<L> * ploc;

    linkedList(){
        length = 0;
        head = nullptr;
        loc = nullptr;
        ploc = nullptr;
    }
};

//linkedlist helper functions
template <typename L>
bool isempty(ListNode<L> *head){
    return head == nullptr;
}

template <typename L>
void insertAtTail(ListNode<L> *head, L val){
    auto * newnode = new ListNode<L>(val);
    if (isempty(head)){
        head = newnode;
    }
    else{
        ListNode<L> * temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

template <typename L>
void printList(ListNode<L>* head){
    if (isempty(head)){
        cout<<"empty list"<<endl;
        return;
    }
    ListNode<L> * temp = head;
    while (temp != nullptr){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

template <typename L>
void search(ListNode<L> head ,ListNode<L> loc ,ListNode<L> ploc ,L val){
    
    loc = head;
    ploc = nullptr;
    if(isempty(head)){
        return;
    }
    while(loc != nullptr && loc->data < val){
        ploc = loc;
        loc = loc->next;
    }
    if (loc != nullptr && loc->data != val){
        loc = nullptr;
    }
}

template <typename L>
void delval(ListNode<L> head ,ListNode<L> loc ,ListNode<L> ploc ,L val){
    search(head,loc, ploc, val);
    if (loc != nullptr){
        ListNode<L> * temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        if (ploc == nullptr){
            head = head->next;
        }
        else if (loc == temp){
            temp = ploc;
            temp->next = nullptr;
        }
        else {
            ploc->next = ploc->next->next;
        }
        delete loc;
    }
}

template <typename L>
void destroy(ListNode<L> *head){
    ListNode<L> * todel;
    while (head != nullptr){
        todel = head;
        head =head->next;
        delete todel;
    }
}

//Question 1
void readFileData(ListNode<Dictionary> **headNode)
{
  string filename;
  Dictionary *dict;
  string word, meaning;
  fstream fin;
  cout << "\x1b[46mEnter the filename\x1b[0m "; 
  cin.ignore();
  cin >> filename;
  fin.open(filename);

  
  if (*headNode !=nullptr)
  {
    ListNode<Dictionary> * todel;
    while (*headNode != nullptr){
        todel = *headNode;
        *headNode = (*headNode)->next;
        delete todel;
    }
  }
  

  while( fin >> word )  //write into file name
  {
    fin.ignore();
    getline(fin,meaning);
    dict = new Dictionary(word,meaning); 
    //insertAtTail(*headNode, *dict);
    ListNode<Dictionary>* newnode = new ListNode<Dictionary>(*dict);
    if (*headNode != nullptr)
    {
      ListNode<Dictionary>* temp = *headNode;
      while (temp->next != nullptr)
      {
        temp = temp->next;
      }
      temp->next = newnode;
    }
    else
    {
      *headNode = newnode;
    }

    delete dict;
  }
  fin.close();
  cout << "\x1b[0;32mFile reading succesful.\x1b[0m\n";
}

//Question 2
void writeToFile(ListNode<Dictionary> *headNode) 
{
    string filename;
  string word, meaning;
  
  fstream dictFile; //create fstream object for the file
  cout << "\e[46mEnter the filename in which the output is to be saved\x1b[0m "; 
	cin.ignore();
  cin >> filename;
  dictFile.open(filename, std::ios::app); //create/open a text file in append mode. new information is always added to the end

  ListNode<Dictionary> *iterator = headNode;

  while(iterator != NULL) { //iterate over the linked list
    word = iterator->data.word;
    meaning = iterator->data.meaning;
    dictFile << word << " " << meaning << endl; //write to data file 
    iterator = iterator->next;   //advance to next node
  }
  dictFile.close();
  cout << "\e[0;32mDictionary entries added.\x1b[0m\n";
}

//Question 3
template <typename L>
void printnodereverse(ListNode<L> * head)
{

    if (head == nullptr)
    {
        return;
    }
    
    printnodereverse(head->next);
    cout<<head->data;
}

//Question 4
ListNode<Dictionary> *reverseList(ListNode<Dictionary> *start) 
{
  ListNode<Dictionary>* current = start;
  ListNode<Dictionary> *prev = NULL, *next = NULL;

  while (current != nullptr) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
  }
  start = prev;
  return start;
}

//Question 5
ListNode<Dictionary> *rearrangeByEvenOddLength(ListNode<Dictionary> *start) 
{
  ListNode<Dictionary> * pre = nullptr;
  ListNode<Dictionary> * curr = start;
  ListNode<Dictionary> * last = start;
  while (last->next != nullptr)
  {
    last = last->next;
  }
  ListNode<Dictionary> * end = last;
  while (curr != last){
    if (curr->data.word.size()%2==0){
        pre = curr;
        curr = curr->next;
    }
    else{
        if (pre == nullptr)
        {
            ListNode<Dictionary> * temp = curr;
            pre = curr;
            curr = curr->next;
            start = start->next;
            temp->next= nullptr;
            end->next=temp;
            end=temp;
        }
        else{
            pre->next= pre->next->next;
            ListNode<Dictionary>* temp = curr;
            curr = curr->next;

            temp->next = nullptr; //Move cur (stored in temp) to end
            end->next = temp;
            end = temp;
        }
        
    }
  }
  
  return start;
}

//Question 6
ListNode<Dictionary>* filterByLetters(ListNode<Dictionary>* start, string letter) 
{
	ListNode<Dictionary>* curr = start, * prev = nullptr;
	while (curr != nullptr)
  {
		if (curr->data.word.find(letter) == -1)
		{

			if (prev)
			{
				prev->next = curr->next;
				curr = curr->next;
			}
			else //if start node
			{
				curr = curr->next;
				start = curr;
			}
		}
		else
		{
			curr = (prev = curr)->next; //Move prev and cur
		}
	}
	return start;
}



