#ifndef lifo
#define lifo

//Last In First Out based eviction, making use of a stack
template <class Key>
class LIFO : public EvictionPolicy<Key>
{
private:
    std::stack<Key> keys;
    std::set<Key> check;

public:
    LIFO()
    {
        clearStack(keys);
        check.clear();
    }

    void accessKey(Key k)
    {
        if (check.count(k) == 0)
        {
            keys.push(k);
            check.insert(k);
        }
    }

    void removeKey(Key k)
    {
        check.erase(k);
    }

    std::pair<Key, bool> evict()
    {
        Key temp;

        //temp stores a garbage value

        if (keys.empty())
            return {temp, false};

        while(check.find(keys.top())==check.end())
            keys.pop();

        Key keyToEvict = keys.top();
        keys.pop();
        check.erase(keyToEvict);
        return {keyToEvict, true};
    }

    void clearStack(std::stack<Key> &key)
    {
        while (!key.empty())
            key.pop();
    }
};

#endif