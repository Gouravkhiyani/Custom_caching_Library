#ifndef lifo
#define lifo

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

    std::pair<Key, bool> evict()
    {
        Key temp;
        if (keys.empty())
            return {temp, false};

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