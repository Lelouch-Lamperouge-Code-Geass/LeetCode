# Types of binary trees

* Complete binary tree
* Perfect binary tree
* Binary search tree
* AVL(Adelson-Velsky and Landis) tree

优先级队列其实是一个堆，堆就是一棵完全二叉树，同时保证父子节点的顺序关系。

C++中map、set、multimap，multiset的底层实现都是平衡二叉搜索树，所以map、set的增删操作 时间时间复杂度是logn，注意我这里没有说unordered_map、unordered_set，unordered_map、 unordered_map底层实现是哈希表。

二叉树可以链式存储，也可以顺序存储。那么链式存储方式就用指针， 顺序存储的方式就是用数组。顾名思义就是顺序存储的元素在内存是连续分布的，而链式存储则是通过指针把分布在散落在各个地址的节点串联一起。

用数组来存储二叉树如何遍历的呢? 如果父节点的数组下表是i，那么它的左孩子就是`i * 2 + 1`，右孩子就是 `i * 2 + 2`。 但是用链式表示的二叉树，更有利于我们理解，所以一般我们都是用链式存储二叉树。 所以大家要了解，用数组依然可以表示二叉树。

# Traversal

二叉树主要有两种遍历方式:
1. 深度优先遍历:先往深走，遇到叶子节点再往回走。 
2. 广度优先遍历:一层一层的去遍历。

这两种遍历是图论中最基本的两种遍历方式，

那么从深度优先遍历和广度优先遍历进一步拓展，才有如下遍历方式:  
* 深度优先遍历:
  * 前序遍历(递归法，迭代法)
  * 中序遍历(递归法，迭代法)
  * 后序遍历(递归法，迭代法)
* 广度优先遍历
  * 层次遍历(迭代法)

在深度优先遍历中:有三个顺序，前中后序遍历.这里前中后，其实指的就是中间节点的遍历顺序，只要大家记住 前中后序指的就是中间节点的位置就可以了。

看如下中间节点的顺序，就可以发现，中间节点的顺序就是所谓的遍历方式

* 前序遍历:中左右
* 中序遍历:左中右
* 后序遍历:左右中

最后再说一说二叉树中深度优先和广度优先遍历实现方式，我们做二叉树相关题目，经常会使用递归的方式来实现深度优先遍历，也就是实现前中后序遍历，使用递归是比较方便的。

__栈其实就是递归的一种是实现结构__，也就说前中后序遍历的逻辑其 实都是可以借助栈使用非递归的方式来实现的。而广度优先遍历的实现一般使用队列来实现，这也是队列先进先出的特点所决定的，因为需要先进先出的结构，才能一层一层的来遍历二叉树。

# Recursive traversal of binary tree 二叉树的递归遍历

每次写递归，都按照这三要素来写:
1. 确定递归函数的参数和返回值
2. 确定终止条件
3. 确定单层递归的逻辑

Leetcode Problems:  
* [144. Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)
* [94.Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
* [145. Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/)

# Iterative traversal of binary tree 二叉树的迭代遍历

递归的实现就是:每一次递归调用都会把函数的局部变量、参数值和返回地址等压入调用栈中，然后递归返回的时候，从栈顶弹出上一次递归的各项参数，所以这就是递归为什么可以返回上一层位置的原因。

Leetcode Problems:  
* [144. Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)
* [94.Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
* [145. Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/)

# Level order traversal of binary tree 二叉树的层序遍历

Leetcode Problems:  
* [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
* [107. Binary Tree Level Order Traversal II](https://leetcode.com/problems/binary-tree-level-order-traversal-ii/)
* [116. Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/)
* [117. Populating Next Right Pointers in Each Node II](https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/)
* [429. N-ary Tree Level Order Traversal](https://leetcode.com/problems/n-ary-tree-level-order-traversal/)
* [515. Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/)
* [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)
