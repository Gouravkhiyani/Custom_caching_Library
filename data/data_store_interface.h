#ifndef data_store_interface
#define data_store_interface

template <class Key, class Value>
class DataStore
{
public:
    DataStore()
    {
    }
    virtual ~DataStore()
    {
    }
    virtual void addToDataStore(Key k, Value v) = 0;
    virtual void deleteFromDataStore(Key k) = 0;
    virtual std::pair<Value, bool> getFromDataStore(Key k) = 0;
    virtual bool isDataStoreFull() = 0;
    virtual void printFromDataStore() = 0;
};

#endif