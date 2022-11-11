# Assignment3

**#Functions**

**linear_probing.h, quadratic_probing.h, and double_hashing**

-enum EntryType - Enum datatype that was to help determine the status of a element in a hash table.

-explicit HashTableLinear(size_t size = 101) : array_(NextPrime(size)) - Creates a hash table with size 101 and makes sure the table is emptry with the MakeEmpty() function.

-bool Contains(const HashedObj &x) const - returns true if an element is in the hash table and false if otherwise.

-void MakeEmpty() - makes the number of elements in the hash table equal to 0 and sets every open spot in the hash table to be EMPTY.

-bool Insert(const HashedObj &x) - Uses the FindPos function to see if a given space for the given element is available and puts it in if the space is open and returns  true, otherwise, returns false. The insert also checks if the number of elements is more than 1/2 the table size and rehashes if its true, used for L-values.

-bool Insert(const HashedObj &&x) - Uses the FindPos function to see if a given space for the given element is available and puts it in if the space is open and returns  true, otherwise, returns false. The insert also checks if the number of elements is more than 1/2 the table size and rehashes if its true, used for R-values.

-bool Remove(const HashedObj & x) - returns true if the given object is removal goes through and false if the object is not removed.

-size_t numberOfElements() - returns the number of elements in the hash table, via current_size_.

-size_t tableSize() - returns the capacity of the hash table, via array_.size().

-size_t numberOfProbes() - returns the number of tries taken to find spaces for elements to be put in the hash table.

-size_t numberOfCollisions() - returns the total collisions that occurred when finding spaces for the elements in the hash table.

-float getLoadFactor() - returns the load factor of a given hash table.

-bool IsActive(size_t current_pos) const - checks if element is currently in a hash table, returns true if yes, otherwise, returns false.

-void Rehash - rehashes the hash table by storing old hash table and creating an new hash table with double the old one's size and inserts the old element's into the new hash table.

**linear_probing.h only**

-size_t InternalHash(const HashedObj &x) const - Hash function that uses linear probing to find spaces to put elements in the hash table.

-size_t FindPos(const HashedObj &x) const - Function that finds a space for an element to fit it and finds the number of collisions and probes while doing so.

**quadratic_probing.h**

-bool IsPrime(size_t n) - Function used to test if a positive number is prime or not.

-int NextPrime(size_t n) - Function used to find a prime number that is greater or equal to n, while using the IsPrime function.

-size_t FindPos(const HashedObj &x) const - Function that finds a space for an element to fit it and finds the number of collisions and probes while doing so.

-size_t InternalHash(const HashedObj &x) - Hash function that uses quadratic probing to find spaces to put elements in the hash table.

**double_hashing.h**

-size_t FindPos(const HashedObj &x) - Function that finds a space for an element that uses double hashing and finds the number of collisions and probes while doing so.

-size_t FindPos(const HashedObj &x) - Same functionality as in linear_probing.h

**spell_check.cc**

-HashTableDouble<string> MakeDictionary(const string &dictionary_file) - Function that populates the hash table with double hashing and the dictionary_file and returns the resulting hash table.

-void SpellChecker(const HashTableType& dictionary, const string &document_file) - Function that takes the words that are considered proper words and a file that needs to be checked for correct spelling. The function decides if a word is correct or not, then performs three set operations. The function can perform a swap between two characters on a word, add a letter to the word, or remove a letter/puncuation from a word.  The program outputs the possible corrections that the user might be looking for.
  
-std::string Swap(HashTableType &hash_table, std::string changed_word) - Iterates throught the word and keeps swapping two characters until the end of the loop is reached or one of the swapping of characters leads to correct word. Outputs correct word, or "Incorrect" if loop is finished.
  
-std::string Add(HashTableType &hash_table, std::string changed_word) - Iterates with a nested for loop to add letters to the word, one at a time, until the end of the loop or if a word with an added character is found. Outputs correct word, or "Incorrect" if loop is finished.
  
-std::string Remove(HashTableType &hash_table, std::string changed_word) - Iterates with a for loop and erases from the word, one letter at a time, until the end of the loop or if a correct word is found. Outputs correct word, or "Incorrect" if loop is finished.
  
-int testSpellingWrapper(int argument_count,  char** argument_list) - Function used to test SpellChecker function and MakeDictionary function.
  
**create_and_test_hash**
  
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename,  const string &query_filename) - Function that constructs a hash table from a file and tests a hash table from a file. Finds the number of elements, size of the table, load factor, number of collisions, and average collisions when creating the hash table. The function also if a word is found or not and the number of probes needed to do so. 
  

