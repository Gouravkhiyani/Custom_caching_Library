#ifndef cache
#define cache

#include <iostream>
#include "data\data_store_interface.h"
#include "data\map_data_store.h"
#include "evictionpolicy\eviction_policy_interface.h"
#include "evictionpolicy\lru.h"
#include "evictionpolicy\fifo.h"
#include "evictionpolicy\lifo.h"

// Generic cache class which expects an eviction policy type and a data storage type
template <class Key, class Value>
class Cache
{
private:
    // expects an eviction policy
    EvictionPolicy<Key> &evictPolicy;

    // expects a datastore type
    DataStore<Key, Value> &dataStore;

public:
    // constructor that initializes cache with an evict policy and datastore to be used
    Cache(EvictionPolicy<Key> &evictPolicy, DataStore<Key, Value> &dataStore);

    // add a new value to the cache
    void put(Key k, Value v);

    // get value of given key from cache
    Value get(Key k);

    bool remove(Key k);
};

// cache constructor definition
template <class Key, class Value>
Cache<Key, Value>::Cache(EvictionPolicy<Key> &evictPolicy, DataStore<Key, Value> &dataStore) : evictPolicy(evictPolicy), dataStore(dataStore) {}

// put method with eviction if storage is full
template <class Key, class Value>
void Cache<Key, Value>::put(Key k, Value v)
{
    std::pair<Value, bool> keyValueUpdate = this->dataStore.getFromDataStore(k);

    // if the key is already present in datastore, then update it
    if (keyValueUpdate.second)
    {
        this->dataStore.addToDataStore(k, v);
        this->evictPolicy.accessKey(k);
    }

    // if the datastore has reached its capacity, evict data based on eviction policy
    else if (this->dataStore.isDataStoreFull())
    {
        std::cout << "Data store is full, need to evict data now\n";
        std::pair<Key, bool> keyToDelete = this->evictPolicy.evict();

        // means there is no key in the datastore, so cannot store any new key as well
        if (!keyToDelete.second)
        {
            std::cout << "Data store is full and there is no key to delete. Cannot store new key\n";
            return;
        }

        std::pair<Value, bool> check = this->dataStore.getFromDataStore(keyToDelete.first);

        // if key is actually not stored in datastore due to some error then retry
        if (!check.second)
        {
            std::cout << "Key not present in data store, trying another key\n";
            put(k, v);
            return;
        }

        // Found a key that can be evicted using the current eviction policy
        std::cout << "deleted key " << keyToDelete.first << "\n";
        this->dataStore.deleteFromDataStore(keyToDelete.first);

        // Now another key can be inserted
        put(k, v);
    }

    // Data store is not full, new key can be added without eviction
    else
    {
        this->dataStore.addToDataStore(k, v);
        this->evictPolicy.accessKey(k);
    }
}

template <class Key, class Value>
Value Cache<Key, Value>::get(Key k)
{
    std::pair<Value, bool> value = this->dataStore.getFromDataStore(k);

    // Key k is accessed, update in the current eviction policy
    this->evictPolicy.accessKey(k);

    if (!value.second)
    {
        std::cout << "Key does not exist. Garbage value returned \n";
    }

    return value.first;
}

template <class Key, class Value>
bool Cache<Key, Value>::remove(Key k)
{
    std::pair<Value, bool> keyToDelete = this->dataStore.getFromDataStore(k);

    if(!keyToDelete.second)
    {   
        return false;
    }
        
    this->dataStore.deleteFromDataStore(k);
    this->evictPolicy.removeKey(k);

    return true;
}

#endif