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

层序遍历一个二叉树。就是从左到右一层一层的去遍历二叉树。这种遍历的方式和我们之前讲过的都不太一样。

需要借用一个辅助数据结构即队列来实现，队列先进先出，符合一层一层遍历的逻辑，而是用栈先进后 出适合模拟深度优先遍历也就是递归的逻辑。
      
而这种层序遍历方式就是图论中的广度优先遍历，只不过我们应用在二叉树上。

Leetcode Problems:  
* [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
* [107. Binary Tree Level Order Traversal II](https://leetcode.com/problems/binary-tree-level-order-traversal-ii/)
* [116. Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/)
* [117. Populating Next Right Pointers in Each Node II](https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/)
* [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)
* [429. N-ary Tree Level Order Traversal](https://leetcode.com/problems/n-ary-tree-level-order-traversal/)
* [515. Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/)
* [637. Average of Levels in Binary Tree](https://leetcode.com/problems/average-of-levels-in-binary-tree/)  

# Invert Binary Tree 翻转二叉树

[226. Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)


有同学会把红黑树和二叉平衡搜索树弄分开了，其实红黑树就是一种二叉平衡搜索树，这两个树不是独 立的，所以C++中map、multimap、set、multiset的底层实现机制是二叉平衡搜索树，再具体一点是红 黑树。

递归与迭代究竟谁优谁劣呢? 从时间复杂度上其实迭代法和递归法差不多(在不考虑函数调用开销和函数调用产生的堆栈开销)，但是空间复杂度上，递归开销会大一些，因为递归需要系统堆栈存参数返回值等等。递归更容易让程序员理解，但收敛不好，容易栈溢出。这么说吧，递归是方便了程序员，难为了机器(各种保存参数，各种进栈出栈)。在实际项目开发的过程中我们是要尽量避免递归!因为项目代码参数、调用关系都比较复杂，不容易控制递归深度，甚至会栈溢出。

# Check whether binary tree is symmetric

### 101. Symmetric Tree

[101. Symmetric Tree](https://leetcode.com/problems/symmetric-tree/submissions/)

对于二叉树是否对称，要比较的是根节点的左子树与右子树是不是相互翻转的，理解这一点就知道了其 实我们要比较的是两个树(这两个树是根节点的左右子树)，所以在递归遍历的过程中，也是要同时遍 历两棵树。

在迭代法中我们使用了队列，需要注意的是这不是层序遍历，而且仅仅通过一个容器来成对的存放我们要比较的元素，知道这一本质之后就发现，用队列，用栈，甚至用数组，都是可以的。

# Find out the maximum depth of Binary Tree 二叉树的最大深度

### 104. Maximum Depth of Binary Tree

[104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/)

### 559. Maximum Depth of N-ary Tree

[559. Maximum Depth of N-ary Tree](https://leetcode.com/problems/maximum-depth-of-n-ary-tree/)

# Find out th minimum depth of binary tree 二叉树的最小深度

[111. Minimum Depth of Binary Tree](https://leetcode.com/problems/minimum-depth-of-binary-tree/)

题目中说的是:最小深度是从根节点到最近叶子节点的最短路径上的节点数量. 注意是叶子节点。 什么是叶子节点，左右孩子都为空的节点才是叶子节点!

求二叉树的最小深度和求二叉树的最大深度的差别主要在于处理左右孩 子不为空的逻辑。

# 222. Count Complete Tree Nodes

[222. Count Complete Tree Nodes](https://leetcode.com/problems/count-complete-tree-nodes/)

https://cs.stackexchange.com/questions/32397/is-there-a-difference-between-perfect-full-and-complete-tree

https://stackoverflow.com/questions/2603692/what-is-the-difference-between-tree-depth-and-height

# 110. Balanced Binary Tree

[110. Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/)


