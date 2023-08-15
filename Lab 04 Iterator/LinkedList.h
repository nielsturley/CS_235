#ifndef LAB_03_LINKED_LIST_LINKEDLIST_H
#define LAB_03_LINKED_LIST_LINKEDLIST_H
#include "LinkedListInterface.h"

//I'm way too lazy to comment all of the linked list stuff from last time, so I'll just comment on the new stuff

template <typename T>
class LinkedList : public LinkedListInterface<T> {
private:
    struct Node {
        Node(T data, Node* next, Node* previous) {
            this->data = data;
            this->next = next;
            this->previous = previous;
        }
        ~Node() = default;
        Node* GetNext() const { return next; }
        Node* GetPrevious() const { return previous; }
        T GetData() const { return data; }
        void SetNext(Node* next) { this->next = next; }
        void SetPrevious(Node* previous) { this->previous = previous; }
        void SetData(T data) { this->data = data; } //added this function for the replace command
        T data;
        Node* next;
        Node* previous;
    };
    Node* head;
    Node* tail;
public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedList() {
        clear();
    }

    /** Insert Node(value) at beginning of linked list */
    virtual void push_front(const T& value) {
        Node* node = new Node(value, head, nullptr);
        if (node->GetNext() == nullptr) {
            tail = node;
        }
        else {
            node->GetNext()->SetPrevious(node);
        }
        head = node;
    }

    /** Remove Node at beginning of linked list */
    virtual void pop_front(void) {
        if (head != nullptr) {
            if (head->GetNext() == nullptr) {
                delete head;
                tail = nullptr;
                head = nullptr;
            }
            else {
                Node* tempVal = head;
                head = head->GetNext();
                delete tempVal;
                head->SetPrevious(nullptr);
            }
        }
    }

    /** Return reference to value of Node at beginning of linked list */
    virtual T& front(void) {
        return head->data;
    }

    /** Return true if linked list size == 0 */
    virtual bool empty(void) const {
        if (head == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    /** Remove all Nodes with value from linked list */
    virtual void remove(const T& value) {
        Node* currentNode = head;
        while (currentNode != nullptr) {
            if (currentNode->GetData() == value) {
                if (currentNode == head) {
                    currentNode = currentNode->GetNext();
                    pop_front();
                }
                else if (currentNode == tail) {
                    pop_back();
                    currentNode = nullptr;
                }
                else {
                    Node* tempVal = currentNode;
                    Node* prevNode = currentNode->GetPrevious();
                    currentNode = currentNode->GetNext();
                    prevNode->SetNext(currentNode);
                    currentNode->SetPrevious(prevNode);
                    delete tempVal;
                }
            }
            else {
                currentNode = currentNode->GetNext();
            }
        }
    }

    /** Remove all Nodes from linked list */
    virtual void clear(void) {
        while (head != nullptr) {
            pop_front();
        }
        head = nullptr;
        tail = nullptr;
    }

    /** Reverse Nodes in linked list */
    virtual void reverse(void) {
        Node* currentNode = head;
        Node* tempNode;
        while (currentNode != nullptr) {
            tempNode = currentNode;
            currentNode = currentNode->GetNext();
            tempNode->SetNext(tempNode->GetPrevious());
            tempNode->SetPrevious(currentNode);
        }
        tail = head;
        head = tempNode;
    }

    /** Return the number of nodes in the linked list */
    virtual size_t size(void) const {
        Node* currentNode = head;
        size_t numNodes = 0;
        while (currentNode != nullptr) {
            numNodes++;
            currentNode = currentNode->GetNext();
        }
        return numNodes;
    }

    /** Return contents of Linked List as a string */
    virtual std::string toString(void) const {
        std::string content;
        Node* currentNode = head;
        while (currentNode != nullptr) {
            content += currentNode->GetData() + " ";
            currentNode = currentNode->GetNext();
        }
        return content;
    }

    /** BONUS ** Insert Node(value) at end of linked list */
    virtual void push_back(const T& value) {
        Node* node = new Node(value, nullptr, tail);
        if (node->GetPrevious() == nullptr) {
            head = node;
        }
        else {
            node->GetPrevious()->SetNext(node);
        }
        tail = node;
    }


    /** BONUS ** Remove Node at end of linked list */
    virtual void pop_back(void) {
        if (tail != nullptr) {
            if (tail->GetPrevious() == nullptr) {
                delete tail;
                tail = nullptr;
                head = nullptr;
            }
            else {
                Node* tempVal = tail;
                tail = tail->GetPrevious();
                delete tempVal;
                tail->SetNext(nullptr);
            }
        }
    }

    /** BONUS ** Return reference to value of Node at end of linked list */
    virtual T& back(void) {
        return tail->data;
    }

    friend std::ostream& operator<< (std::ostream& os, const LinkedList& list) {
        os << list.toString();
        return os;
    }

    //introducing the iterator class
    //just as confusing and pain-inducing as the last lab :)
    class Iterator {
    private:
        Node* iNode;
    public:
        //constructor and destructor
        Iterator(Node* node = nullptr) {
            iNode = node;
        }
        ~Iterator() = default;

        //operator overloading functions
        bool operator!=(const Iterator& rhs) const {
            if (iNode != rhs.iNode) {
                return true;
            }
            return false;
        }

        Iterator& operator++() {
            iNode = iNode->next;
            return *this;
        }

        Iterator& operator--() {
            iNode = iNode->previous;
            return *this;
        }

        T& operator*() const {
            return iNode->data;
        }


        Node* GetNode() const {
            return iNode;
        }

        //these guys. I feel like you can personify functions if you have to call them "friends"
        std::string toString() const {
            return iNode->data;
        }

        friend std::ostream& operator<< (std::ostream& os, const Iterator& itr) {
            os << itr.toString();
            return os;
        }
    };

    //beginning all the iterator commands
    Iterator begin(void) {
        return Iterator(head);
    }

    /** Return iterator pointing to something not in linked list */
    Iterator end(void) {
        return Iterator(nullptr);
    }

    /** Return iterator pointing found value in linked list */
    Iterator find(Iterator first, Iterator last, const T& value) {
        while (first != last) {
            if (*first == value) {
                return first;
            }
            ++first;
        }
        throw std::string(" Not Found");
    }

    /** Return iterator pointing to inserted value in linked list */
    Iterator insert(Iterator position, const T& value) {
        Node* node = new Node(value, position.GetNode(), position.GetNode()->GetPrevious());
        if (node->GetPrevious() != nullptr) { //if not the head node
            node->GetPrevious()->SetNext(node);
            node->GetNext()->SetPrevious(node);
        }
        else {
            head = node;
            node->GetNext()->SetPrevious(node);
        }
        return Iterator(node);
    }

    /** Return iterator pointing to inserted value in linked list */
    Iterator insert_after(Iterator position, const T& value) {
        if (position.GetNode()->GetNext() == nullptr) { //if there isn't a next node
            push_back(value); //cause why would I write more code than I have to
            return ++position;
        }
        ++position;
        Iterator node = insert(position, value); //otherwise just call the regular function after incrementing
        return node;
    }

    /** Return iterator pointing to next item after deleted node linked list */
    Iterator erase(Iterator position) { //confusing stuff here
        if (position.GetNode()->GetPrevious() == nullptr) { //if position is at the head
            if (position.GetNode()->GetNext() == nullptr) { //if position is also the tail
                pop_front();
                return Iterator(nullptr); //pop the node and set to nothing
            }
            else { //otherwise just increment and move on
                ++position;
                pop_front();
                return position;
            }
        }
        else if (position.GetNode()->GetNext() == nullptr) { //else (because I don't want it to double pop) if position is at the tail
            pop_back();
            return Iterator(nullptr); //pop and set to nothing
        }
        Node* tempVal = position.GetNode(); //otherwise it's in the middle of the list and do the usual garbage
        ++position;
        tempVal->GetPrevious()->SetNext(position.GetNode());
        tempVal->GetNext()->SetPrevious(position.GetNode());
        delete tempVal;
        return position;
    }

    /** Replace found old_value(s) with new_value */ //they totally lied here so I fixed it
    void replace(Iterator first, Iterator last, const T& old_value, const T& new_value) {
        while (first != last) {
            if (*first == old_value) { //if you find the value, change it
                Node* tempVal = first.GetNode();
                tempVal->SetData(new_value);
            }
            ++first;
        }
    }
};


//header files that are longer than your main.cpp, lol
#endif //LAB_03_LINKED_LIST_LINKEDLIST_H
