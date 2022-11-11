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

-

