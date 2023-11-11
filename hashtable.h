#ifndef HASHTABLE_H
#define HASHTABLE_H

// Project Identifier: 2C4A3C53CD5AD45A7BEA3AE5356A3B1622C9D04B

// INSTRUCTIONS:
// fill out the methods in the class below.

// You may assume that the key and value types can be copied and have default
// constructors.

// You can also assume that the key type has (==) and (!=) methods.

// You may assume that Hasher is a functor type with a
// size_t operator()(const Key&) overload.

// The key/value types aren't guaranteed to support any other operations.

// Do not add, remove, or change any of the class's member variables.
// The num_deleted counter is *optional*. You might find it helpful, but it
// is not required to pass the lab assignment.

// Do not change the Bucket type.

// SUBMISSION INSTRUCTIONS:
// Submit this file, by itself, in a .tar.gz.
// Other files will be ignored.

#include <cstdint>
#include <functional> // where std::hash lives
#include <vector>
#include <cassert> // useful for debugging!

using namespace std;

// A bucket's status tells you whether it's empty, occupied, 
// or contains a deleted element.
enum class Status : uint8_t {
    Empty,
    Occupied,
    Deleted
};

template<typename K, typename V, typename Hasher = std::hash<K>>
class HashTable {
    // used by the autograder; do not change/remove.
    friend class Verifier;
public:
    // A bucket has a status, a key, and a value.
    struct Bucket {
        // Do not modify Bucket.
        Status status = Status::Empty;
        K key;
        V val;
    };

    HashTable() {
        // TODO: a default constructor (possibly empty).
        buckets.resize(20);
        // You can use the following to avoid implementing rehash_and_grow().
        // However, you will only pass the AG test cases ending in _C.
        // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
        //    buckets.resize(10000);
    }

    size_t size() const {
        return num_elements;
    }

    // returns a reference to the value in the bucket with the key, if it
    // already exists. Otherwise, insert it with a default value, and return
    // a reference to the resulting bucket.
    V& operator[](const K& key) {
        Hasher func;
        size_t loc = func(key) % buckets.size();

        V val();
        if(buckets[loc].status != Status::Occupied){
            insert(key, val);
        }
        //search
        for(size_t i=0; i<buckets.size(); i++){
            size_t temploc = (loc+i) % buckets.size();
            if(buckets[temploc].status == Status::Occupied){
                if(buckets[temploc].key == key){
                    return buckets[temploc].val;
                }
            }
        }
        return val;
        // TODO
    }

    // insert returns whether inserted successfully
    // (if the key already exists in the table, do nothing and return false).
    bool insert(const K& key, const V& val) {
        // TODO
        Hasher func;
        size_t loc = func(key) % buckets.size();
        if(buckets[loc].status == Status::Empty){
            buckets[loc].status = Status::Occupied;
            buckets[loc].val = val;
            buckets[loc].key = key;
            num_elements++;
            return true;
        }
        if(buckets[loc].status == Status::Occupied && buckets[loc].key == key){
            return false;
        }
        if(buckets[loc].status == Status::Deleted || buckets[loc].status == Status::Occupied){
            for(size_t i=0; i<buckets.size(); i++){
                size_t temploc = (loc+i) % buckets.size();
                if(buckets[temploc].status == Status::Occupied){
                    if(buckets[temploc].key == key){
                        return false;
                    }
                }
                else{
                    buckets[temploc].status = Status::Occupied;
                    buckets[temploc].val = val;
                    buckets[temploc].key = key;
                    num_elements++;
                    return true;
                }
            }
        }
        return false;
    }
    // erase returns the number of items remove (0 or 1)
    size_t erase(const K& key) {
        Hasher func;
        size_t loc = func(key) % buckets.size();
        
        for(size_t i=0; i<buckets.size(); i++){
            size_t temploc = (loc+i) % buckets.size();
            if(buckets[temploc].status == Status::Occupied){
                if(buckets[temploc].key == key){
                    buckets[temploc].status = Status::Deleted;
                    num_elements--;
                    return 1;
                }
            }
            else{
                return 0;
            }
        }
        return 0;
    }

private:
    size_t num_elements = 0;
    size_t num_deleted = 0; // OPTIONAL: you don't need to use num_deleted to pass
    std::vector<Bucket> buckets;

    void rehash_and_grow() {
        // You can avoid implementing rehash_and_grow() by calling
        //    buckets.resize(10000);
        // in the constructor. However, you will only pass the AG test cases ending in _C.
        // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
        vector<Bucket> old = buckets;
        buckets.clear();
        buckets.resize(2*old.size());
        num_elements=0;
        for(auto i: old){
            if(i.status == Status::Occupied){
                insert(i.key, i.val);
            }
        }
    }

    // You can add methods here if you like.
    // TODO
    size_t linearProbe(size_t initial, const K& key){
        size_t ret = initial;
        
    }
};

#endif // HASHTABLE_H
