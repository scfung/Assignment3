// Stanley Fung
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <cstdlib>
#include <cctype>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;
// You can add more functions here.

// Creates and fills double hashing hash table with all words from
// dictionary_file

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
        for(int i = 0; i < insert_line.size(); i++)
        {
            if(ispunct(insert_line[i]))
            {
                insert_line.erase(i--, 1);
            }
        }
        
        for(int i = 0; i < insert_line.size(); i++)
        {
            insert_line[i] = tolower(insert_line[i]);
        }
        
        bool result = false;
        result = dictionary.Contains(insert_line);
        if(result == true)
        {
            std::cout << insert_line << " is CORRECT" << std::endl;
            continue;
        }
        while(result == false)
        {
            std::cout << insert_line << " is INCORRECT" << std::endl;
            output = Swap(dictionary, insert_line);
            if(output != "Incorrect")
            {
                result = true;
                break;
            }
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
            else
                break;
        }
    }
}

template <typename HashTableType>
std::string Swap(HashTableType &hash_table, std::string changed_word)
{
    std::string original = changed_word;
    for(int i = 0; i < changed_word.length(); i++)
    {
        std::swap(changed_word[i], changed_word[i+1]);
        std::cout << "** " << original << " -> " << changed_word << " case C" << std::endl;
        if(hash_table.Contains(changed_word) == true)
            return changed_word;
        changed_word = original;
    }
    return "Incorrect";
  
}

template <typename HashTableType>
std::string Add(HashTableType &hash_table, std::string changed_word)
{
    std::string original = changed_word;
    for(int i = 0; i < changed_word.length(); i++)
    {
        for(int j = 97; j < 123; j++)
        {
            changed_word.insert(i, 1, (char)j);
            std::cout << "** " << original << " -> " << changed_word << " case A" << std::endl;
            if(hash_table.Contains(changed_word) == true)
                return changed_word;
            changed_word = original;
        }
    }
    return "Incorrect";
}

template <typename HashTableType>
std::string Remove(HashTableType &hash_table, std::string changed_word)
{
    std::string original = changed_word;
    for(int i = 0; i < changed_word.length(); i++)
    {
        changed_word.erase(i, 1);
        std::cout << "** " << original << " -> " << changed_word << " case B" << std::endl;
        if(hash_table.Contains(changed_word) == true)
            return changed_word;
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
