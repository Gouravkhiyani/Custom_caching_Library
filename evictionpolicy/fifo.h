#ifndef fifo
#define fifo


template <class Key>
class FIFO : public EvictionPolicy<Key>
{
private:
    std::queue<Key> keys;
    std::set<Key> check;

public:
    FIFO()
    {
        clearQueue(keys);
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
        if (keys.empty())                // if keys is empty we return a garbage value
            return {temp, false};

        Key keyToEvict = keys.front();
        keys.pop();

        check.erase(keyToEvict);
        return {keyToEvict, true};      // keyToEvict is the key evicted and we receive its value
    }

    void clearQueue(std::queue<Key> &key)
    {
        while (!key.empty())
            key.pop();
    }
};

#endif