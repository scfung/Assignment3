//
//  linear_probing.h
//  Homework3
//
//  Created by Stanley Fung on 10/25/22.
//

#ifndef linear_probing_h
#define linear_probing_h

#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include "quadratic_probing.h"

template <typename HashedObj>

class HashTableLinear{
public:
    //Used to determine the status of an element in the hash table.
    enum EntryType {ACTIVE, EMPTY, DELETED};
    
    //Constructs a hashtable with size 101 and inititalizes the values with MakeEmpty() function
    explicit HashTableLinear(size_t size = 101) : array_(NextPrime(size)){
        MakeEmpty();
    }
    
    //Determines if a element is in the hash table or not.
    bool Contains(const HashedObj & x) const {
        return IsActive(FindPos(x));
    }
    
    //Empties hash table and sets values back to default
    void MakeEmpty() {
        current_size_ = 0;
        probe_num = 1;
        for (auto & entry : array_)
            entry.info_ = EMPTY;
    }
    
    //Inserts L-value element into the hash table
    bool Insert(const HashedObj & x) {
        // Insert x as active
        size_t current_pos = FindPos(x);
        if (IsActive(current_pos))
            return false;
        
        array_[current_pos].element_ = x;
        array_[current_pos].info_ = ACTIVE;
        
        // Rehash; see Section 5.5
        if (++current_size_ > array_.size() / 2)
            Rehash();
        return true;
    }
    
    //Inserts R-value element into the hash table.
    bool Insert(HashedObj && x) {
        // Insert x as active
        size_t current_pos = FindPos(x);
        if (IsActive(current_pos))
            return false;
        
        array_[current_pos] = std::move(x);
        array_[current_pos].info_ = ACTIVE;
        
        // Rehash; see Section 5.5
        if (++current_size_ > array_.size() / 2)
            Rehash();
        
        return true;
    }
    
    //Removes element from the hash table
    bool Remove(const HashedObj & x) {
        size_t current_pos = FindPos(x);
        if (!IsActive(current_pos))
            return false;
        
        array_[current_pos].info_ = DELETED;
        return true;
    }
    
    //Used to find the number of elements in hash table
    size_t numberOfElements(){ return current_size_;}
    
    //Used to find the size of the whole table
    size_t tableSize(){return array_.size();}
    
    //Finds the number of probes needed to place a value in the hash table
    size_t numberOfProbes(){
        return probe_num;
    }
    //Finds the number of collisions that occurred while finding
    size_t numberOfCollisions(){return total_collisions;}
    
    //Checks how full the table is, relative to the table's size
    float getLoadFactor(){
        return static_cast<float>(current_size_) / static_cast<float>(array_.size());
    }
    
private:
    //Created to deal with elements that are put in the hash table
    struct HashEntry {
        HashedObj element_;
        EntryType info_;
    
        HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
        :element_{e}, info_{i} { }
    
        HashEntry(HashedObj && e, EntryType i = EMPTY)
        :element_{std::move(e)}, info_{ i } {}
    };
    

    std::vector<HashEntry> array_;
    size_t current_size_;
    mutable size_t total_collisions = 0;
    mutable size_t probe_num = 1;
    mutable size_t collisions = 0;
    
    //Checks if the an element is currently in the hash table
    bool IsActive(size_t current_pos) const
    { return array_[current_pos].info_ == ACTIVE; }
    
    size_t FindPos(const HashedObj &x) const{
        size_t offset = 1;
        size_t current_pos = InternalHash(x);
        size_t count = 1;
        while(array_[current_pos].info_ != EMPTY and array_[current_pos].element_ != x)
        {
            current_pos += offset;
            collisions++;
            offset++;
            count++;
            if(current_pos >= array_.size())
            {
                current_pos -= array_.size();
            }
        }
        total_collisions += collisions;
        collisions = 0;
        probe_num = count;
        offset = 1;
        return current_pos;
    }
    //Rehashes the hash table
    void Rehash() {
        std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
        array_.resize(NextPrime(2 * old_array.size()));
        for (auto & entry : array_)
            entry.info_ = EMPTY;
    
    // Copy table over.
        current_size_ = 0;
        for (auto & entry :old_array)
            if (entry.info_ == ACTIVE)
                Insert(std::move(entry.element_));
    }
    //Internal Hash function to help find a place for an element to be put in the hash table
    size_t InternalHash(const HashedObj & x) const {
        static std::hash<HashedObj> hf;
        return (hf(x) + collisions) % array_.size( );
  }
};

#endif /* linear_probing_h */








