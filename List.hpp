#ifndef LIST_HPP
#define LIST_HPP

#include <cassert>

template <typename T>
class List
{
private:
  struct Node
  {
    Node *next;
    Node *prev;
    T datum;
    Node(const T &d, Node *p, Node *n)
        : next(n), prev(p), datum(d) {}
  };

  Node *first;
  Node *last;
  int sz;

  void copy_all(const List &other)
  {
    for (Node *cur = other.first; cur; cur = cur->next)
    {
      push_back(cur->datum);
    }
  }

public:
  class Iterator
  {
  private:
    const List *list_ptr;
    Node *node_ptr;

    Iterator(const List *lp, Node *np)
        : list_ptr(lp), node_ptr(np) {}

    friend class List;

  public:
    Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}

    T &operator*() const
    {
      return node_ptr->datum;
    }

    Iterator &operator++()
    {
      if (node_ptr)
        node_ptr = node_ptr->next;
      return *this;
    }

    Iterator operator++(int)
    {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const Iterator &rhs) const
    {
      return list_ptr == rhs.list_ptr && node_ptr == rhs.node_ptr;
    }

    bool operator!=(const Iterator &rhs) const
    {
      return !(*this == rhs);
    }
  };

  List() : first(nullptr), last(nullptr), sz(0) {}

  ~List()
  {
    clear();
  }

  List(const List &other)
      : first(nullptr), last(nullptr), sz(0)
  {
    copy_all(other);
  }

  List &operator=(const List &other)
  {
    if (this != &other)
    {
      clear();
      copy_all(other);
    }
    return *this;
  }

  bool empty() const
  {
    return first == nullptr;
  }

  int size() const
  {
    return sz;
  }

  T &front()
  {
    return first->datum;
  }

  T &back()
  {
    return last->datum;
  }

  void push_front(const T &datum)
  {
    Node *n = new Node(datum, nullptr, first);
    if (first)
      first->prev = n;
    first = n;
    if (!last)
      last = n;
    ++sz;
  }

  void push_back(const T &datum)
  {
    Node *n = new Node(datum, last, nullptr);
    if (last)
      last->next = n;
    last = n;
    if (!first)
      first = n;
    ++sz;
  }

  void pop_front()
  {
    Node *tmp = first;
    first = first->next;
    if (first)
      first->prev = nullptr;
    else
      last = nullptr;
    delete tmp;
    --sz;
  }

  void pop_back()
  {
    Node *tmp = last;
    last = last->prev;
    if (last)
      last->next = nullptr;
    else
      first = nullptr;
    delete tmp;
    --sz;
  }

  void clear()
  {
    Node *cur = first;
    while (cur)
    {
      Node *next = cur->next;
      delete cur;
      cur = next;
    }
    first = nullptr;
    last = nullptr;
    sz = 0;
  }

  Iterator begin() const
  {
    return Iterator(this, first);
  }

  Iterator end() const
  {
    return Iterator(this, nullptr);
  }

  Iterator erase(Iterator it)
  {
    Node *n = it.node_ptr;
    Node *nxt = n->next;
    Node *prv = n->prev;

    if (n == first)
      first = nxt;
    if (n == last)
      last = prv;

    if (prv)
      prv->next = nxt;
    if (nxt)
      nxt->prev = prv;

    delete n;
    --sz;

    return Iterator(this, nxt);
  }

  Iterator insert(Iterator it, const T &datum)
  {
    Node *pos = it.node_ptr;

    if (!pos)
    {
      push_back(datum);
      return Iterator(this, last);
    }

    Node *prv = pos->prev;
    Node *n = new Node(datum, prv, pos);

    pos->prev = n;
    if (prv)
      prv->next = n;
    else
      first = n;

    ++sz;
    return Iterator(this, n);
  }
};

#endif
