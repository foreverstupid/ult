#ifndef LIST_TEMPLATE_CLASS_HPP
#define LIST_TEMPLATE_CLASS_HPP

/*
 * Struct that implements one item of a list
 */
template <typename T>
struct ListItem{
    T *obj;
    ListItem<T> *next;
    ListItem<T> *prev;
};



/*
 * Class that incapsulates a two-linked list
 */
template <typename T>
class List{
protected:
    ListItem<T> *head;
    ListItem<T> *tail;

public:
    List(){ head = tail = 0; }
    virtual ~List();

    void add(T *elem);  /* add element to the end */
    T *peakLast();      /* get the last element deleting it from list */
    void push(T *elem); /* add element to the beginning */
    T *pop();           /* get the first element deleting it from list */

    const T *getFirst() const { return head->obj; }
    const T *getLast() const { return tail->obj; }
    const ListItem<T> *getFirstItem() const { return head; }
    const ListItem<T> *getLastItem() const { return tail; }

    /* find the first list element that holds given value.
       Returns 0 if not found */
    const ListItem<T> *findFirst(const T *elem) const;

    /* find the last list element that holds given value.
       Returns 0 if not found */
    const ListItem<T> *findLast(const T *elem) const;

private:
    List(const List &lst);
    void operator=(const List &lst);
};



template <typename T>
List<T>::~List()
{
    while(head){
        tail = head;
        head = head->next;
        delete tail;
    }
}



template <typename T>
void List<T>::push(T *elem)
{
    ListItem<T> *item = new ListItem<T>();

    item->obj = elem;
    item->next = head;
    item->prev = 0;

    if(head){
        head->prev = item;
    }
    head = item;

    if(!tail){
        tail = item;
    }
}



template <typename T>
T *List<T>::pop()
{
    if(!head){
        return 0;
    }

    T *result = head->obj;
    ListItem<T> *tmp = head;
    head = head->next;

    if(!head){
        tail = 0;
    }else{
        head->prev = 0;
    }

    delete tmp;
    return result;
}



template <typename T>
void List<T>::add(T *elem)
{
    ListItem<T> *item = new ListItem<T>();

    item->obj = elem;
    item->next = 0;
    item->prev = tail;

    if(tail){
        tail->next = item;
    }
    tail = item;

    if(!head){
        head = tail;
    }
}



template <typename T>
T *List<T>::peakLast()
{
    if(!tail){
        return 0;
    }

    T *result = tail->obj;
    ListItem<T> *tmp = tail;
    tail = tail->prev;;

    if(!tail){
        head = 0;
    }else{
        tail->next = 0;
    }

    delete tmp;
    return result;
}



template <typename T>
const ListItem<T> *List<T>::findFirst(const T *elem) const
{
    ListItem<T> *tmp = head;

    while(tmp){
        if(*(tmp->obj) == *elem){
            break;
        }

        tmp = tmp->next;
    }

    return tmp;
}



template <typename T>
const ListItem<T> *List<T>::findLast(const T *elem) const
{
    ListItem<T> *tmp = head;

    while(tmp){
        if(*(tmp->obj) == *elem){
            break;
        }

        tmp = tmp->prev;
    }

    return tmp;
}

#endif
