#ifndef AVL_TREE_HPP_
# define AVL_TREE_HPP_

# include <cstddef>
# include <memory>
# include <utility>
# include <functional>
# include <algorithm>

namespace Tree
{
  template <typename T>
  class AVLTree
  {
  public :
    class Node
    {
    private :
      T _value;
      short _balance;
      Node *_parent;
      Node *_left;
      Node *_right;
      
    public :
      Node(const T&,
	   short = 0,
	   Node * = nullptr,
	   Node * = nullptr,
	   Node * = nullptr);
      
      Node(T&&,
	   short = 0,
	   Node * = nullptr,
	   Node * = nullptr,
	   Node * = nullptr);
      
      Node(const Node&) = default;
      ~Node() = default;
      Node& operator=(const Node&) = default;
      const T& getValue() const;
      T& getValue();
      void setValue(const T&);
      void setValue(T&&);
      const Node *getParent() const;
      Node *getParent();
      void setParent(Node *);
      const Node *getLeft() const;
      Node *getLeft();
      void setLeft(Node *);
      const Node *getRight() const;
      Node *getRight();
      void setRight(Node *);
      short getBalance() const;
      short& getBalance();
      void setBalance(short);
    };

  public :
    using FunctorNode = std::function<void (const Node *)>;
    
  private :
    Node *_root;
    std::size_t _size;
    
  public :
    AVLTree();
    ~AVLTree();
    void insert(const T&);
    void insert(T&&);
    void erase(const T&);
    void apply(const FunctorNode&) const;

  private :
    std::size_t height(const Node *) const;
    int calcBalance(const Node *) const;
    bool insert(Node *, const T&);
    bool insert(Node *, T&&);
    Node *erase(Node *, const T&);
    Node *erase(Node *);
    Node *findMax(Node *) const;
    void eraseAll(Node *);
    void apply(const FunctorNode&, const Node *) const;
    void handleRotation(Node *);
    bool canRotate(const Node *) const;
    void rotate(Node *);
    void rotateLeft(Node *);
    void rotateRight(Node *);
    void rootReset();
  };

  template <typename T>
  AVLTree<T>::Node::Node(const T& value,
			 short balance,
			 Node *parent,
			 Node *left,
			 Node *right) :
    _value(value),
    _balance(balance),
    _parent(parent),
    _left(left),
    _right(right)
  { }

  template <typename T>
  AVLTree<T>::Node::Node(T&& value,
			 short balance,
			 Node *parent,
			 Node *left,
			 Node *right) :
    _value(std::move(value)),
    _balance(balance),
    _parent(parent),
    _left(left),
    _right(right)
  { }

  template <typename T>
  const T& AVLTree<T>::Node::getValue() const { return _value; }

  template <typename T>
  T& AVLTree<T>::Node::getValue() { return _value; }

  template <typename T>
  void AVLTree<T>::Node::setValue(const T& value) { _value = value; }

  template <typename T>
  void AVLTree<T>::Node::setValue(T&& value) { _value = std::move(value); }

  template <typename T>
  const typename AVLTree<T>::Node *
  AVLTree<T>::Node::getParent() const { return _parent; }

  template <typename T>
  typename AVLTree<T>::Node *AVLTree<T>::Node::getParent() { return _parent; }

  template <typename T>
  void AVLTree<T>::Node::setParent(Node *parent) { _parent = parent; }
  
  template <typename T>
  const typename AVLTree<T>::Node *
  AVLTree<T>::Node::getLeft() const { return _left; }

  template <typename T>
  typename AVLTree<T>::Node *AVLTree<T>::Node::getLeft() { return _left; }

  template <typename T>
  void AVLTree<T>::Node::setLeft(Node *left) { _left = left; }

  template <typename T>
  const typename AVLTree<T>::Node *
  AVLTree<T>::Node::getRight() const { return _right; }

  template <typename T>
  typename AVLTree<T>::Node *AVLTree<T>::Node::getRight() { return _right; }

  template <typename T>
  void AVLTree<T>::Node::setRight(Node *right) { _right = right; }
  
  template <typename T>
  short AVLTree<T>::Node::getBalance() const { return _balance; }

  template <typename T>
  short& AVLTree<T>::Node::getBalance() { return _balance; }

  template <typename T>
  void AVLTree<T>::Node::setBalance(short balance) { _balance = balance; }
  
  
  template <typename T>
  AVLTree<T>::AVLTree() :
    _root(nullptr),
    _size(0)
  { }

  template <typename T>
  AVLTree<T>::~AVLTree() { eraseAll(_root); }

  template <typename T>
  void AVLTree<T>::insert(const T& value)
  {
    bool isInserted = true;
    
    if (_root
	&& (isInserted = insert(_root, value)))
      rootReset();
    else
      _root = new Node(value);
    if (isInserted)
      ++_size;
  }

  template <typename T>
  void AVLTree<T>::insert(T&& value)
  {
    bool isInserted = true;
    
    if (_root
	&& (isInserted = insert(_root, std::forward<T>(value))))
      rootReset();
    else
      _root = new Node(std::forward<T>(value));
    if (isInserted)
      ++_size;
  }

  template <typename T>
  void AVLTree<T>::erase(const T& value)
  {
    _root = erase(_root, value);
    rootReset();
  }

  template <typename T>
  void AVLTree<T>::apply(const FunctorNode& functor) const
  {
    apply(functor, _root);
  }

  template <typename T>
  std::size_t AVLTree<T>::height(const Node *node) const
  {
    return node ?
      1 + std::max(height(node->getLeft()), height(node->getRight())) : 0;
  }

  template <typename T>
  int AVLTree<T>::calcBalance(const Node *node) const
  {
    return height(node->getRight()) - height(node->getLeft());
  }
  
  template <typename T>
  bool AVLTree<T>::insert(Node *current, const T& value)
  {
    if (current->getValue() > value)
      {
	if (current->getLeft())
	  {
	    if (!insert(current->getLeft(), value))
	      return false;
	  }
	else
	  current->setLeft(new Node(value, 0, current));
      }
    else if (current->getValue() < value)
      {
	if (current->getRight())
	  {
	    if (!insert(current->getRight(), value))
	      return false;
	  }
	else
	  current->setRight(new Node(value, 0, current));
      }
    else
      return false;
    handleRotation(current);
    return true;
  }

  template <typename T>
  bool AVLTree<T>::insert(Node *current, T&& value)
  {
    if (current->getValue() > value)
      {
	if (current->getLeft())
	  {
	    if (!insert(current->getLeft(), std::forward<T>(value)))
	      return false;
	  }
	else
	  current->setLeft(new Node(std::forward<T>(value), 0, current));
      }
    else if (current->getValue() < value)
      {
	if (current->getRight())
	  {
	    if (!insert(current->getRight(), std::forward<T>(value)))
	      return false;
	  }
	else
	  current->setRight(new Node(std::forward<T>(value), 0, current));
      }
    else
      return false;
    handleRotation(current);
    return true;
  }

  template <typename T>
  typename AVLTree<T>::Node *AVLTree<T>::erase(Node *current, const T& value)
  {
    if (!current)
      return nullptr;
    else if (current->getValue() > value)
      current->setLeft(erase(current->getLeft(), value));
    else if (current->getValue() < value)
      current->setRight(erase(current->getRight(), value));
    else
      return erase(current);
    handleRotation(current);
    return current;
  }

  template <typename T>
  typename AVLTree<T>::Node *AVLTree<T>::erase(Node *current)
  {
    Node *tmp;

    if (!current->getLeft() && !current->getRight())
      tmp = nullptr;
    else if (!current->getRight())
      tmp = current->getLeft();
    else if (!current->getLeft())
      tmp = current->getRight();
    else
      {
	tmp = findMax(current->getLeft());
	std::swap(current->getValue(), tmp->getValue());
	current->setLeft(erase(current->getLeft(), tmp->getValue()));
	handleRotation(current);
	return current;
      }
    if (tmp)
      tmp->setParent(current->getParent());
    --_size;
    delete current;
    return tmp;
  }

  template <typename T>
  typename AVLTree<T>::Node *AVLTree<T>::findMax(Node *current) const
  {
    return (current->getRight()) ?
      findMax(current->getRight()) : current;
  }

  template <typename T>
  void AVLTree<T>::eraseAll(Node *node)
  {
    if (node)
      {
	eraseAll(node->getLeft());
	eraseAll(node->getRight());
	delete node;
      }
  }

  template <typename T>
  void AVLTree<T>::apply(const FunctorNode& functor, const Node *node) const
  {
    if (node)
      {
	functor(node);
	apply(functor, node->getLeft());
	apply(functor, node->getRight());
      }
  }
  
  template <typename T>
  void AVLTree<T>::handleRotation(Node *node)
  {
    node->setBalance(calcBalance(node));
    if (canRotate(node))
      rotate(node);
  }
  
  template <typename T>
  bool AVLTree<T>::canRotate(const Node *node) const
  {
    return !(node->getBalance() ^ 2) || !(node->getBalance() ^ -2);
  }
  
  template <typename T>
  void AVLTree<T>::rotate(Node *node)
  {
    if (!(node->getBalance() ^ -2) && !(node->getLeft()->getBalance() ^ -1))
      rotateRight(node->getLeft());
    else if (!(node->getBalance() ^ 2)
	     && !(node->getRight()->getBalance() ^ 1))
      rotateLeft(node->getRight());
    else if (!(node->getBalance() ^ -2)
	     && !(node->getLeft()->getBalance() ^ 1))
      {
	rotateLeft(node->getLeft()->getRight());
	rotateRight(node->getLeft());
      }
    else if (!(node->getBalance() ^ 2)
	     && !(node->getRight()->getBalance() ^ -1))
      {
	rotateRight(node->getRight()->getLeft());
	rotateLeft(node->getRight());
      }
  }
  
  template <typename T>
  void AVLTree<T>::rotateLeft(Node *node)
  {
    node->getParent()->setRight(node->getLeft());
    if (node->getLeft())
      node->getLeft()->setParent(node->getParent());
    node->setLeft(node->getParent());
    node->setParent(node->getParent()->getParent());
    if (node->getParent())
      {
	if (node->getParent()->getRight() == node->getLeft())
	  node->getParent()->setRight(node);
	else
	  node->getParent()->setLeft(node);
      }
    node->getLeft()->setParent(node);
    node->getLeft()->setBalance(calcBalance(node->getLeft()));
    node->setBalance(calcBalance(node));
  }
  
  template <typename T>
  void AVLTree<T>::rotateRight(Node *node)
  {
    node->getParent()->setLeft(node->getRight());
    if (node->getRight())
      node->getRight()->setParent(node->getParent());
    node->setRight(node->getParent());
    node->setParent(node->getParent()->getParent());
    if (node->getParent())
      {
	if (node->getParent()->getRight() == node->getRight())
	  node->getParent()->setRight(node);
	else
	  node->getParent()->setLeft(node);
      }
    node->getRight()->setParent(node);
    node->getRight()->setBalance(calcBalance(node->getRight()));
    node->setBalance(calcBalance(node));
  }

  template <typename T>
  void AVLTree<T>::rootReset()
  {
    if (_root && _root->getParent())
      {
	for (Node *node = _root; node; node = node->getParent())
	  _root = node;
      }
  }
}

#endif /* !AVL_TREE_HPP_ */
