#ifndef map_data_store
#define map_data_store

#include <iostream>
#include <unordered_map>

//This is an unordered map based data store that stores key value pairs
template <class Key, class Value>
class MapDataStore : public DataStore<Key, Value>
{
private:
    int capacity;
    std::unordered_map<Key, Value> data;

public:
    //Functions of data_store_interface are implemented here
    MapDataStore(int capacity)
    {
        this->capacity = capacity;
        data.clear();
    }

    void addToDataStore(Key k, Value v)
    {
        //a key value pair is added 
        data[k] = v;
    }

    void deleteFromDataStore(Key k)
    {
        if (data.find(k) == data.end())
        {
            std::cout << "Key is not present in data\n";
            return;
        }

        data.erase(k);
    }

    std::pair<Value, bool> getFromDataStore(Key k)
    {
        Value v;
        if (data.find(k) == data.end())
            return {v, false};  //v here represents some garbage value

        else
        {
            v = data[k];
            return {v, true};
        }
    }

    bool isDataStoreFull()
    {
        return (data.size()>=capacity);
    }

    void printFromDataStore()
    {
        for (auto dataSet : data)
            std::cout << dataSet.first << " ";

        std::cout << "\n";
    }
};

#endif