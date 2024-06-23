#ifndef doubly_linked_list
#define doubly_linked_list

template <class Key>

//Node structure for a doubly linked list
class Node
{
public:
    Key data;
    Node *next, *prev;

    Node(Key k)
    {
        this->data = k;
        this->next = NULL;
        this->prev = NULL;
    }
};

template <class Key>
class DoublyLinkedList
{
private:
    Node<Key> *head, *tail;

public:
    DoublyLinkedList()
    {
        head = new Node<Key>(Key{});
        tail = new Node<Key>(Key{});
        head->next = tail;
        tail->prev = head;
    }

    void deleteNode(Node<Key> *node)
    {
        if (node != NULL)
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }

    void addNodeAtLast(Node<Key> *node)
    {
        if (node == NULL)
            return;

        Node<Key> *prevTail = tail->prev;
        prevTail->next = node;
        node->next = tail;
        tail->prev = node;
        node->prev = prevTail;
    }

    Node<Key> *addElementAtLast(Key data)
    {
        Node<Key> *newNode = new Node<Key>(data);
        addNodeAtLast(newNode);
        return newNode;
    }

    bool isEmpty()
    {
        return head->next == tail;
    }

    Node<Key> *getFirstNode()
    {
        if (!isEmpty())
            return head->next;
        else
            return NULL;
    }

    Node<Key> *getLastNode()
    {
        if (!isEmpty())
            return tail->prev;
        else
            return NULL;
    }

    void printList()
    {
        if (!isEmpty())
        {
            Node<Key> *curr = head->next;
            while (curr != tail)
            {
                std::cout << curr->data << " ";
                curr = curr->next;
            }
            std::cout << "\n";
        }
        else
            std::cout << "Empty List\n";
    }
};

#endif