# Custom Caching Library
Implemented an In-Memory Custom Cache library with C++

1. Supports Put, Get and Remove functionalities in the Cache.
2. Used standard eviction policies like FIFO, LIFO, LRU along with interface to add new eviction policy.
3. For data storage, unordered map is used, also any new data storage can be implemented using data store interface.

## Usage
To use this custom cache, clone this repo.
1. Add Cache.h header in your file.
2. Create an object for MapDataStore with capacity
eg: data store for string , int key value pair
```
MapDataStore<std::string, int> MapDataStore(4);
```
3. Create an object for eviction policy which you want to use 
eg: eviction policy where key taken is string
```
FIFO<std::string> fifoPolicy;
LIFO<std::string> lifoPolicy;
LRU<std::string> lruPolicy;
```
4. Create an object for cache and pass the eviction policy and data store you want to use.
eg: cache with string,int key value pair using lru policy and map data store
```
Cache<std::string, int> test(lruPolicy, MapDataStore);
```
5. Now using this cache object you can use different cache methods
eg:
```
test.put("ABCD", 5);
test.get("ABCD");
test.remove("ABCD");
```

## Custom Eviction Policy
To create any custom eviction policy
1. Use the eviction policy interface.
2. Implement its functions in your new eviction policy
```
void accessKey(Key k)
void removeKey(Key k)
std::pair<Key, bool> evict()
```

## Custom Data Storage
To create and use a new data storage
1. Use the data store interface.
2. Implement its functions in your new data storage
```
void addToDataStore(Key k, Value v)
void deleteFromDataStore(Key k)
std::pair<Value, bool> getFromDataStore(Key k)
bool isDataStoreFull()
void printFromDataStore()
```
