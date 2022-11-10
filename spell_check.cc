// YOUR NAME.
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
    ifstream words(dictionary_file);
    std::string insert_line;
    
    while(words >> insert_line){
        if(insert_line.length() > 0){
            dictionary_hash.Insert(insert_line);
        }
    }
    return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file)
{
    ifstream query(document_file);
    std::string insert_line;
    
    while(query >> insert_line)
    {
        for(int i = 0; i < insert_line.length(); i++)
        {
            if(isalpha(insert_line[i]))
            {
                insert_line[i] = tolower(insert_line[i]);
            }
            else if('\'' == insert_line[i])
            {
                while(i < insert_line.length())
                {
                    insert_line.erase(insert_line.begin()+i);
                }
            }
            else{
                insert_line.erase(insert_line.begin() + i);
                --i;
            }
        }
    }
    
    if(insert_line.length() == 0){
        std::cout << "Skipping word" << std::endl;
    }
    else if(!dictionary.Contains(insert_line)){
        bool found_match = false;
        std::cout << insert_line << " is INCORRECT" << std::endl;
        
        //Swap
        for(int i = 0; !found_match and (i < insert_line.length()-1); i++){
            std::string original_1 = insert_line;
            std::swap(insert_line[i], insert_line[i+1]);
            std::cout << "** " << original_1 << " -> " << insert_line << " ** case C" << std::endl;
            if(dictionary.Contains(insert_line)){
                found_match = true;
            }
            else{
                std::swap(insert_line[i], insert_line[i+1]);
            }
        }
        
        //Single Delete
        for(int i = 0; !found_match and i < insert_line.length(); i++){
            std::string original_2 = insert_line;
            char deleted_char = insert_line[i];
            auto itr = insert_line.begin() + i;
            insert_line.erase(itr);
            std::cout << "** " << original_2 << " -> " << insert_line << " ** case B" << std::endl;
            if(dictionary.Contains(insert_line)){
                found_match = true;
            }
            else{
                insert_line.insert(itr, deleted_char);
            }
        }
        
        //Single Insert
        for(auto iterate = insert_line.begin(); !found_match and iterate != insert_line.end()+1; advance(iterate, 1)){
            std::string original_3 = insert_line;
            for(char inserted_char = 'a'; ! found_match and (inserted_char <= 'z'); inserted_char++){
                insert_line.insert(iterate, inserted_char);
                std::cout << "** " << original_3 << " ->" << insert_line << " ** case A" << std::endl;
                if(dictionary.Contains(insert_line)){
                    found_match = true;
                }
                else{
                    insert_line.erase(iterate);
                }
            }
        }
        if(!found_match){
            std::cout << "No match found" << std::endl;
        }
    else{
        std::cout << insert_line << " is CORRECT" << std::endl;
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
