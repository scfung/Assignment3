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
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file)
{
    ifstream query;
    query.open(document_file);
    std::string insert_line;
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
            std::cout << insert_line << "is CORRECT" << std::endl;
        }
        while(result == false)
        {
            std::cout << insert_line << " is INCORRECT" << std::endl;
            //swap, swaps two characters in the string and checks to see if the resulting string is in dictionary
            for(int i = 0; i < insert_line.length() and result == false; i++)
            {
                std::string original = insert_line;
                swap(insert_line[i], insert_line[i+1]);
                std::cout << "** " << original << " -> " << insert_line << " ** case C" << std::endl;
                if(dictionary.Contains(insert_line) == true)
                    result = true;
                else
                    insert_line = original;
                
            }
            //add, adds a character at different indexes to see if word is valid in dictionary
            for(int i = 0; i < insert_line.length() and result == false; i++)
            {
                std::string original = insert_line;
                for(int j = 97; j < 123; j++)
                {
                    insert_line.insert(i,1,(char)j);
                    std::cout << "** " << original << " -> " << insert_line << " ** case A" << std::endl;
                    if(dictionary.Contains(insert_line) == true)
                        result = true;
                    else
                        insert_line = original;
                }
                    
            }
            //remove, removes a character at different indexes to see if word is valid in dictionary
            for(int i = 0; i < insert_line.length() and result == false; i++)
            {
                std::string original = insert_line;
                insert_line.erase(i,1);
                std::cout << "** " << original << " -> " << insert_line << " ** case B" << std::endl;
                if(dictionary.Contains(insert_line) == true)
                    result = true;
                else
                    insert_line = original;
            }
        }
    }
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
