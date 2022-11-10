//
//  double_hashing.h
//  Homework3
//
//  Created by Stanley Fung on 10/25/22.
//

#ifndef double_hashing_h
#define double_hashing_h

namespace {
// Internal method to return a prime number at least as large as n.
int NextPrime(size_t n);

}  // namespace

// Double Hashing Implementation
template <typename HashedObj>
class HashTableDouble {
public:
    enum EntryType {ACTIVE, EMPTY, DELETED};
    
    explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }
    
    bool Contains(const HashedObj & x) const {
        return IsActive(FindPos(x));
    }
    
    void MakeEmpty() {
        current_size_ = 0;
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
    
    int numberOfElements(){return current_size_;}
    
    int tableSize(){return array_.capacity();}
    
    int numberOfProbes(const HashedObj &x) const{
        int offset = 1;
        int starting_pos = InternalHash(x);
        int probe = starting_pos;
        int number_of_probes = 1;
        
        while(array_[probe].info_ != EMPTY and array_[probe].element_ != x){
            ++number_of_probes;
            probe = (starting_pos + (offset * InternalHash2(x))) % array_.capacity();
            ++offset;
        }
        return number_of_probes;
    }
    
    int numberOfCollisions(){
        return collisions;
    }
    
    float getLoadFactor(){
        return static_cast<float>(numberOfElements()) / static_cast<float>(tableSize());
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
        mutable int collisions = 0;
        size_t R = 73;
        
        bool IsActive(size_t current_pos) const
        { return array_[current_pos].info_ == ACTIVE; }
        
    size_t FindPos(const HashedObj & x) const {
            size_t offset = 1;
            size_t current_pos = InternalHash(x);
            size_t probe = current_pos;
            
            while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
                ++collisions;
                probe = (current_pos + (offset * InternalHash2(x))) % array_.capacity();
                offset++;
            }
        return probe;
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
        size_t InternalHash2(const HashedObj & x) const{
            static std::hash<HashedObj> hf;
            return R - (hf(x) % R);
        }
    };
#endif /* double_hashing_h */
