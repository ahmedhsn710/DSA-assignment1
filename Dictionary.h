#pragma once
#include <string>
using namespace std;

class Dictionary //definitino of class Dictionary
{
  public:
    string word; //data member word and meaning
    string meaning;

    Dictionary() //default constructor
    {
      word.push_back('\0');
      meaning.push_back('\0');
    }

    Dictionary(string word, string meaning) //parametrized constructor
    {
      this->word = word;
      this->meaning = meaning;
    }

    //overloading of boolean comparison operators for sotring data in list
    bool operator==(Dictionary dictionaryEntry)
    {
      return word == dictionaryEntry.word;
    }

    bool operator!=(Dictionary dictionaryEntry)
    {
      return word != dictionaryEntry.word;
    }

    bool operator>(Dictionary dictionaryEntry)
    {
      return word > dictionaryEntry.word;
    }

    bool operator<(Dictionary dictionaryEntry)
    {
      return word < dictionaryEntry.word;
    }

    // << was overloaded for printing and file writing purposes
    friend ostream &operator<<( ostream &output, const Dictionary& dict)
    {
      output << dict.word << " :: " << dict.meaning<<endl;
      return output;
    };
};