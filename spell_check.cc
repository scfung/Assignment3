// Stanley Fung
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <cstdlib>
#include <cctype>
#include <sstream>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;
// You can add more functions here.

// Creates and fills double hashing hash table with all words from
// dictionary_file, using ifstream library

HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
    HashTableDouble<string> dictionary_hash;
  // Fill dictionary_hash.
    ifstream words;
    words.open(dictionary_file);
    std::string insert_line;
    
    while(!(words.eof())){
        words>>insert_line;
        dictionary_hash.Insert(insert_line);
    }
    return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
template <typename HashTableType>
void SpellChecker(const HashTableType& dictionary, const string &document_file)
{
    ifstream query;
    query.open(document_file);
    std::string insert_line, output;
    while(!(query.eof()))
    {
        query>>insert_line;
        //Makes the word lowercase
        for(int i = 0; i < insert_line.size(); i++)
        {
            insert_line[i] = tolower(insert_line[i]);
        }
        //Checks if given word is valid or not
        for(int i = 0; i < insert_line.size(); i++)
        {
            if(i == insert_line.length()-1 and !isalpha(insert_line[i]) and !isdigit(insert_line[i])){
                insert_line.erase(i, 1);
            }
        }
        
        bool result = false;
        result = dictionary.Contains(insert_line);
        if(result == true)
        {
            std::cout << insert_line << " is CORRECT" << std::endl;
            continue;
        }
        //Runs the word through Swap, Add, and Remove and stops when a word that matches a word in the dictionary is found
        while(result == false)
        {
            std::cout << insert_line << " is INCORRECT" << std::endl;
            output = Add(dictionary, insert_line);
            if(output != "Incorrect")
            {
                result = true;
                break;
            }
            output = Remove(dictionary, insert_line);
            if(output != "Incorrect")
            {
                result = true;
                break;
            }
            output = Swap(dictionary, insert_line);
            if(output != "Incorrect")
            {
                result = true;
                break;
            }
            else
                break;
        }
    }
}

template <typename HashTableType>
//Swaps two characters in the given incorrect word and tests to see if the changed word is in the dictionary
std::string Swap(HashTableType &hash_table, std::string changed_word)
{
    std::string original = changed_word;
    for(int i = 0; i < changed_word.length(); i++)
    {
        std::swap(changed_word[i], changed_word[i+1]);
        if(hash_table.Contains(changed_word) == true)
        {
            std::cout << "** " << original << " -> " << changed_word << " ** case C" << std::endl;
            return changed_word;
        }
        changed_word = original;
    }
    return "Incorrect";
  
}

//Adds a character to the given incorrect word and tests to see if the changed word is in the dictionary
template <typename HashTableType>
std::string Add(HashTableType &hash_table, std::string changed_word)
{
    std::string original = changed_word;
    for(int i = 0; i < changed_word.length(); i++)
    {
        for(int j = 97; j < 123; j++)
        {
            changed_word.insert(i, 1, (char)j);
            if(hash_table.Contains(changed_word) == true)
            {
                std::cout << "** " << original << " -> " << changed_word << " ** case A" << std::endl;
                return changed_word;
            }
            changed_word = original;
        }
    }
    return "Incorrect";
}

//Removs a character to the given incorrect word and tests to see if the changed word is in the dictionary
template <typename HashTableType>
std::string Remove(HashTableType &hash_table, std::string changed_word)
{
    std::string original = changed_word;
    for(int i = 0; i < changed_word.length(); i++)
    {
        changed_word.erase(i, 1);
        if(hash_table.Contains(changed_word) == true)
        {
            std::cout << "** " << original << " -> " << changed_word << " ** case B" << std::endl;
            return changed_word;
        }
        changed_word = original;
    }
    
    return "Incorrect";
}
// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}
/*
// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}
*/
