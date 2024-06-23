#ifndef eviction_policy_interface
#define eviction_policy_interface

//Eviction policy based interface to implement any type of eviction policy based on the given functions 
template <class Key>
class EvictionPolicy
{
public:
    EvictionPolicy() {}
    virtual ~EvictionPolicy() {}
    virtual void accessKey(Key k) = 0;
    virtual void removeKey(Key k) = 0;
    virtual std::pair<Key, bool> evict() = 0;
};

#endif