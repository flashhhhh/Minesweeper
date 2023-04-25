
template <class T> class node {
    public:
        T value;
        node* next;

        node();
        node(T value);
        ~node();
};

template<class T> node<T>::node() {
    this->next = NULL;
}

template<class T> node<T>::node(T value) {
    this->value = value;
    this->next = NULL;
}

template<class T> node<T>::~node() {}

template<class T> class Queue {
    private:
        node<T>* head; node<T>* tail;
        int size;

    public:
        Queue();
        ~Queue();
        bool isEmpty();
        int getSize();
        T getHead();
        void delete_head();
        void add_tail(T value);
};

template<class T> Queue<T>::Queue() {
    head = tail = NULL;
    size = 0;
}

template<class T> Queue<T>::~Queue() {
    while (head != NULL) {
        node<T>* x = head;
        head = head -> next;
        delete x;
    }

    delete tail;
    tail = NULL;
}

template<class T> bool Queue<T>::isEmpty() {
    return (head == NULL);
}

template<class T> int Queue<T>::getSize() {
    return size;
}

template<class T> T Queue<T>::getHead() {
    assert(!isEmpty());
    return head -> value;
}

template<class T> void Queue<T>::delete_head() {
    node<T>* p = head;
    head = head -> next;
    delete p;

    if (head == NULL) tail == NULL;
    --size;
}

template<class T> void Queue<T>::add_tail(T value) {
    // empty queue
    if (head == NULL) {
        head = new node(value);
        tail = head;
    }
    else {
        node<T>* x = new node(value);

        tail -> next = x;
        tail = x;
    }

    ++size;
}