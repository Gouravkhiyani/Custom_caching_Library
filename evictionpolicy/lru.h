#ifndef lru
#define lru

#include "..\utility\doubly_linked_list.h"
#include <unordered_map>

//Least Recently Used based eviction, making use of a doubly linked list
template <class Key>
class LRU : public EvictionPolicy<Key>
{
private:
    DoublyLinkedList<Key> *keys;
    std::unordered_map<Key, Node<Key> *> check;

public:
    LRU()
    {
        this->keys = new DoublyLinkedList<Key>();
        check.clear();
    }

    void accessKey(Key k)
    {
        if (check.find(k) != check.end())
        {
            keys->deleteNode(check[k]);
            keys->addNodeAtLast(check[k]);
        }
        else
        {
            Node<Key> *newNode = keys->addElementAtLast(k);
            check[k] = newNode;
        }
    }

    void removeKey(Key k)
    {
        if(check.find(k)!=check.end())
        {
            keys->deleteNode(check[k]);
        }
    }

    std::pair<Key, bool> evict()
    {
        Node<Key> *nodeToEvict = keys->getFirstNode();
        Key temp;
        if (nodeToEvict == NULL)
            return {temp, false};

        keys->deleteNode(nodeToEvict);
        check.erase(nodeToEvict->data);
        return {nodeToEvict->data, true};
    }
};

#endif