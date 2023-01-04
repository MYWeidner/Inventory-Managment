# Inventory-Managment
Treap data structure

### Problem Definition & Data Structure Solution:
Inventory management systems are a means by which a company can track goods from one end of their supply chain to the other which ensures that a company knows what inventory it has in stock, where it is, and how to manage it.

I built part of an inventory management system using a treap data structure that tracks inventory levels and triggers when inventory is below a given threshold and should be replenished. A treap uses a main key that maintains a binary search tree ordering property, and a secondary key called a priority that maintains a heap property. The structure of the tree is determined by the requirement that it be heap-ordered which means the priority number for any non-leaf node must be greater than or equal to the priority of its children. The idea here is for the priority of a node to be directly related to its inventory level. If the inventory level for a given item falls below a predetermined threshold, then the item node is given a higher priority in the treap which will trigger the inventory system to replenish stock for that item. Once item quantity has been returned to a quantity above the threshold, then the item will be given a lower priority and the treap will be rebalanced.

In my opinion, a treap is the best way to implement this solution. A treap data structure combines the best of both heaps and binary search trees. When a treap is constructed, we basically build an ordered binary tree and make it satisfy the “heap” property. This means that there is only one arrangement for this treap regardless of the order by which elements are inserted into the tree. A treap is a self-organizing data structure that looks after itself, without the need to be managed.

### Instructions on how to compile and run code
Gtest was used to test all aspects of code. You will need to run cmake from within the build directory to create the rules for making the applications. Next, run make to use those rules to actually build the executable from the source code.
