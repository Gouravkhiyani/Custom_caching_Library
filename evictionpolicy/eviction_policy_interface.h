#ifndef eviction_policy_interface
#define eviction_policy_interface

template <class Key>
class EvictionPolicy
{
public:
    EvictionPolicy()
    {
    }
    virtual ~EvictionPolicy()
    {
    }
    virtual void accessKey(Key k) = 0;
    virtual std::pair<Key, bool> evict() = 0;
};

#endif