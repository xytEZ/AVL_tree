#include <iostream>
#include "AVLTree.hpp"

template <typename T>
struct NodeKeyDisplayer
{
  ~NodeKeyDisplayer() { std::cout << std::endl; }

  void operator()(const typename Tree::AVLTree<T>::Node *node)
  {
    std::cout << node->getValue()
	      << "["
	      << node->getBalance()
	      << "]";
    if (node->getParent())
      std::cout << "["
		<< node->getParent()->getValue()
		<< "]";
    else
      std::cout << "[NoVal]";
    std::cout << ' ';
  }
};

int main()
{
  std::cout << "Display format : \"value[balance][parentvalue]\""
	    << std::endl
	    << std::endl
	    << "----------------------------------------------------------"
	    << std::endl
	    << std::endl
	    << std::endl;

  
  Tree::AVLTree<int> tree;
  
  std::cout << "( ( ( ( Insert 16, -35, -99, -35 ) ) ) )" << std::endl;
  tree.insert(16);
  tree.insert(-35);
  tree.insert(-99);
  tree.insert(-35);
  std::cout << std::endl;


  
  // Tree state n°1

  std::cout << "[Tree state n°1]" << std::endl << std::endl;

  std::cout << "( ( ( ( Depth-first search ) ) ) )" << std::endl;

  tree.apply(NodeKeyDisplayer<int>());

  std::cout << std::endl;

  std::cout << "( ( ( ( Erase -35, -99, 16 ) ) ) )" << std::endl;
  tree.erase(-35);
  tree.erase(-99);
  tree.erase(16);
  std::cout << std::endl;
  
  std::cout << "----------------------------------------------------------"
	    << std::endl
	    << std::endl
	    << std::endl;

  
  
  Tree::AVLTree<int> tree2;
  
  std::cout << "( ( ( ( Insert -35, 16, -99, 20, 38 ) ) ) )" << std::endl;
  tree2.insert(-35);
  tree2.insert(16);
  tree2.insert(-99);
  tree2.insert(20);
  tree2.insert(38);
  std::cout << std::endl;

  
  // Tree state n°2

  std::cout << "[Tree state n°2]" << std::endl << std::endl;

  std::cout << "( ( ( ( Depth-first search ) ) ) )" << std::endl;

  tree2.apply(NodeKeyDisplayer<int>());

  std::cout << std::endl;

  std::cout << "( ( ( ( Erase 20, -99, 38, -35, 16 ) ) ) )" << std::endl;
  tree2.erase(20);
  tree2.erase(-99);
  tree2.erase(38);
  tree2.erase(-35);
  tree2.erase(16);
  std::cout << std::endl;

  std::cout << "----------------------------------------------------------"
	    << std::endl
	    << std::endl
	    << std::endl;

  
  
  Tree::AVLTree<int> tree3;

  std::cout << "( ( ( ( Insert 19, 10, 34, 8, 12, 26, 72, 22, 29 ) ) ) )"
	    << std::endl;
  tree3.insert(19);
  tree3.insert(10);
  tree3.insert(34);
  tree3.insert(8);
  tree3.insert(12);
  tree3.insert(26);
  tree3.insert(72);
  tree3.insert(22);
  tree3.insert(29);
  std::cout << std::endl;

  std::cout << "( ( ( ( Erase 8, 12 ) ) ) )" << std::endl;
  tree3.erase(8);
  tree3.erase(12);
  std::cout << std::endl;

  
  // Tree state n°3

  std::cout << "[Tree state n°3]" << std::endl << std::endl;

  std::cout << "( ( ( ( Depth-first search ) ) ) )" << std::endl;

  tree3.apply(NodeKeyDisplayer<int>());

  std::cout << "----------------------------------------------------------"
	    << std::endl
	    << std::endl
	    << std::endl;
  
  

  Tree::AVLTree<int> tree4;

  std::cout << "( ( ( ( Insert 50, 25, 77, 10, 42, 64, 80, 45 ) ) ) )"
	    << std::endl;
  tree4.insert(50);
  tree4.insert(25);
  tree4.insert(77);
  tree4.insert(10);
  tree4.insert(42);
  tree4.insert(64);
  tree4.insert(80);
  tree4.insert(45);
  std::cout << std::endl;
  
  std::cout << "( ( ( ( Erase 64, 80 ) ) ) )" << std::endl;
  tree4.erase(64);
  tree4.erase(80);
  std::cout << std::endl;

  
  // Tree state n°4

  std::cout << "[Tree state n°4]" << std::endl << std::endl;

  std::cout << "( ( ( ( Depth-first search ) ) ) )" << std::endl;

  tree4.apply(NodeKeyDisplayer<int>());
  
  return 1;
}

/*

 Tree state n°1 :


              16                                         -35

             /               Right rotation             /    \

          -35		    ---------------->        -99      16

          /

       -99					       
 




 Tree state n°2 : 


	      -35                                        -35

             /    \                                     /    \

          -99      16          Left rotation         -99      20

                     \       ----------------->             /    \

                      20                                   16    38

                        \

                         38



 Tree state n°3 :

                                           ( Double right-left rotation )
                                               

                 
                   19             		          19			                26
                                 
                 /    \         Right rotation          /    \	      Left rotation	      /    \

              10        34    ----------------->      10      26    ------------------>	    19      34

            /    \    /    \				    /    \		           /  \    /  \

           8     12  26    72				  22	  34                     10   22  29  72 

                   /    \                                       /    \

                  22    29                                     29    72


 Tree state n°4 :

                                           ( Double left-right rotation )



                   50					  50					42
                                 
                 /    \          Left rotation	        /    \	      Right rotation	      /    \

              25        77     ----------------->     42      77    ----------------->	    25      50

            /    \    /    \			    /	 \				  /       /    \

          10     42  64    80			  25	  45				10      45      77

                   \                             /

                   45                          10

*/
