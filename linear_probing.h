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
    enum EntryType {ACTIVE, EMPTY, DELETED};
    
    explicit HashTableLinear(size_t size = 101) : array_(NextPrime(size)){
        MakeEmpty();
    }
    
    bool Contains(const HashedObj & x) const {
        return IsActive(FindPos(x));
    }
    
    void MakeEmpty() {
        current_size_ = 0;
        collisions = 0;
        probes = 1;
        for (auto & entry : array_)
            entry.info_ = EMPTY;
    }
    
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
    
    bool Remove(const HashedObj & x) {
        size_t current_pos = FindPos(x);
        if (!IsActive(current_pos))
            return false;
        
        array_[current_pos].info_ = DELETED;
        return true;
    }
    
    size_t numberOfElements(){ return current_size_;}
    
    size_t tableSize(){return array_.size();}
    
    size_t numberOfProbes(){
        return probes;
    }
    
    size_t numberOfCollisions(){return collisions;}
        
    float getLoadFactor(){
        return static_cast<float>(current_size_) / static_cast<float>(array_.size());
    }
    
private:
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
    mutable size_t collisions = 0;
    mutable size_t probes;

    bool IsActive(size_t current_pos) const
    { return array_[current_pos].info_ == ACTIVE; }
    
    size_t FindPos(const HashedObj &x) const{
        size_t offset = 1;
        size_t current_pos = InternalHash(x);
    
        while(array_[current_pos].info_ != EMPTY and array_[current_pos].element_ != x)
        {
            current_pos += offset;
            collisions++;
            offset++;
            if(current_pos >= array_.size())
            {
                current_pos -= array_.size();
            }
        }
        probes = offset;
        offset = 1;
        return current_pos;
    }
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
  
    size_t InternalHash(const HashedObj & x) const {
        static std::hash<HashedObj> hf;
        return hf(x) % array_.size( );
  }
};

#endif /* linear_probing_h */








