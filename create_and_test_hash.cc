// YOUR NAME.
#include <fstream>
#include <iostream>
#include <string>

// Uncomment when you implemented linear probing & double hashing
#include "linear_probing.h"
#include "double_hashing.h"

#include "quadratic_probing.h"

using namespace std;


// You can add more functions here

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
			      const string &words_filename,
			      const string &query_filename) {
    //..Insert your own code
    ifstream words(words_filename), query(query_filename);
    std::string insert_line;
    
    while(words >> insert_line){
        if(insert_line.length() > 0){
            hash_table.insert(insert_line);
        }
    }
    while(query >> insert_line){
        if(hash_table.Contains(insert_line)){
            std::cout << insert_line << "Found " << hash_table.numberOfProbes(insert_line) << std::endl;
        }
        else{
            std::cout << insert_line << "Not_Found " << hash_table.numberOfProbes(insert_line) << std::endl;
        }
    }
}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue);
    }

    if (param_flag == "linear") {
      // Uncomment below when you have implemented linear probing.
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
        std::cout << "number_of_elements: " << linear_probing_table.numberOfElements() << std::endl;
        std::cout << "size_of_table: " << linear_probing_table.tableSize() << std::endl;
        std::cout << "load_factor: " << linear_probing_table.getLoadFactor() << std::endl;
        std::cout << "collisions: " << linear_probing_table.numberOfCollisions() << std::endl;
        float avg_collisions = static_cast<float>(linear_probing_table.numberOfCollisions()) / static_cast<float>(linear_probing_table.numberOfElements());
        std::cout << "avg_collisions: " << avg_collisions << std::endl;
    }
    else if (param_flag == "quadratic") {
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
        std::cout << "number_of_elements: " << quadratic_probing_table.numberOfElements() << std::endl;
        std::cout << "size_of_table: " << quadratic_probing_table.tableSize() << std::endl;
        std::cout << "load_factor: " << quadratic_probing_table.getLoadFactor() << std::endl;
        std::cout << "collisions: " << quadratic_probing_table.numberOfCollisions() << std::endl;
        float avg_collisions = static_cast<float>(quadratic_probing_table.numberOfCollisions()) / static_cast<float>(quadratic_probing_table.numberOfElements());
        std::cout << "avg_collisions: " << avg_collisions << std::endl;
    }
    else if (param_flag == "double") {
        cout << "r_value: " << R << endl;
        // Uncomment below when you have implemented double hashing.
        HashTableDouble<string> double_probing_table;
        TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
        std::cout << "number_of_elements: " << double_probing_table.numberOfElements() << std::endl;
        std::cout << "size_of_table: " << double_probing_table.tableSize() << std::endl;
        std::cout << "load_factor: " << double_probing_table.getLoadFactor() << std::endl;
        std::cout << "collisions: " << double_probing_table.numberOfCollisions() << std::endl;
        float avg_collisions = static_cast<float>(double_probing_table.numberOfCollisions()) / static_cast<float>(double_probing_table.numberOfElements());
        std::cout << "avg_collisions: " << avg_collisions << std::endl;
        
    }
    else {
        cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
    
    
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
