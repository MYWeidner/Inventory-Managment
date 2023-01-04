#include <gtest/gtest.h>
#include "../code/Treap.h"

#include <iostream>
#include <string>

using namespace std;

class test_Treap : public ::testing::Test {
// These functions are not needed as grading is not assigned to each test (this will be a simple pass or fail)
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}
    
	// this function runs before every TEST_F function
	void SetUp() override {
    }

	// this function runs after every TEST_F function
	void TearDown() override {
	}
};

TEST_F(test_Treap, InitializeTest){
	Treap mytreap; // declare Treap object
	shared_ptr<TreapNode> t = mytreap.InitNode(50, 80, 20, 10, "Hammers"); // initialize treap node with new node specifications
	ASSERT_TRUE(t); // node initialized
	ASSERT_EQ(50,t->key); // should match given value
	ASSERT_EQ(80, t->max_inv); // should match given value
	ASSERT_EQ(20, t->curr_inv); // should match given value
	ASSERT_EQ(10, t->min_inv); // should match given values
	ASSERT_EQ("Hammers",t->item); // should match given string
	ASSERT_FALSE(t->left); // left child should be NULL
	ASSERT_FALSE(t->right); // right child should be NULL
	ASSERT_EQ(75,t->priority); // priority should be 100 - (20/80) * 100 = 75
}

TEST_F(test_Treap, InsertTest){
	// build treap like this
	/*       top
			 50 (key for BST order)
	         15 (priority for heap order)              
            / \             
      top_LC   top_RC
		   30  70
		   5   10
          / \  
	lC_LC    LC_RC
		20   40 
		2    4   
	*/ 
	
	// inserted out of order so testing below will capture if rotations were done properly
	shared_ptr<TreapNode> top(new TreapNode); // root
	Treap mytreap; // declare Treap object
	mytreap.Insert(top, 50, 100, 85, 1, "Nails"); // root
	mytreap.Insert(top, 20, 100, 98, 3, "Screw Driver"); // left child's left child
	mytreap.Insert(top, 70, 100, 90, 2, "Bucket"); // root's right child
	mytreap.Insert(top, 40, 100, 96, 4, "Nail Gun"); // left child's right child
	mytreap.Insert(top, 30, 100, 95, 1, "Hammer"); // root's left child

	// check BST key for nodes (should match order in treap from diagram above)
	ASSERT_EQ(50,top->key);
	ASSERT_EQ(30,top->left->key);
	ASSERT_EQ(70,top->right->key);
	ASSERT_EQ(20,top->left->left->key);
	ASSERT_EQ(40,top->left->right->key);

	// check priority for nodes (should match order in treap from diagram above)
	ASSERT_EQ(15,top->priority);
	ASSERT_EQ(5,top->left->priority);
	ASSERT_EQ(10,top->right->priority);
	ASSERT_EQ(2,top->left->left->priority);
	ASSERT_EQ(4,top->left->right->priority);
}

TEST_F(test_Treap, RemoveLeafTest){
	// build treap like this
	/*       top
			 50 (key for BST order)
	         15 (priority for heap order)              
            /              
      top_LC   
		   30  
		   5   
	*/ 
	
	// hand build
	shared_ptr<TreapNode> top(new TreapNode); // root
	shared_ptr<TreapNode> top_LC(new TreapNode); // root's left child
	top->key = 50;
    top->priority = 15;
	top_LC->key = 30;
    top_LC->priority = 5;

	Treap mytreap;	// declare Treap object
	
    mytreap.Remove(top, 30); // remove root's left child
	EXPECT_FALSE(top->left != NULL); // should be null since removed
    ASSERT_EQ(50,top->key); // confirm root's key
	mytreap.Remove(top, 50); // remove root
	EXPECT_FALSE(top != NULL); // should be null since removed
}

TEST_F(test_Treap, RemoveRootWith2ChildrenTest){
    // hand build treap like this
    /*       top
             50 (key for BST order)
             15 (priority for heap order)              
            / \             
      top_LC   top_RC
           30  70
           5   10      
    */ 
    shared_ptr<TreapNode> top(new TreapNode); // root
    shared_ptr<TreapNode> top_LC(new TreapNode); // root's left child
    shared_ptr<TreapNode> top_RC(new TreapNode); // root's right child
    top->key = 50;
    top->priority = 15;
    top->left = top_LC;
    top->right = top_RC;
    top_LC->key = 30;
    top_LC->priority = 5;
    top_RC->key = 70;
    top_RC->priority = 10;

	// remove root with 2 children
    // check nodes are in proper place
	  /*    new top
             70 (key for BST order)
             10 (priority for heap order)              
            /            
      top_LC   
           30  
           5         
    */ 
	Treap mytreap; // declare Treap object
	
    mytreap.Remove(top, 50);
    
    // should match diagram above
    ASSERT_EQ(70,top->key); 
    ASSERT_EQ(30,top->left->key); 
}

TEST_F(test_Treap, RemoveNonRootWith2ChildrenTest){
    // hand build treap like this
    /*       top
             50 (key for BST order)
             15 (priority for heap order)              
            / \             
      top_LC   top_RC
           30  70
           5   10   
		  / \  
    lC_LC    LC_RC
        20   40 
        2    4   
   
    */ 
    shared_ptr<TreapNode> top(new TreapNode); // root
    shared_ptr<TreapNode> top_LC(new TreapNode); // root's left child
    shared_ptr<TreapNode> top_RC(new TreapNode); // root's right child
    shared_ptr<TreapNode> LC_LC(new TreapNode); // left child's left child
	shared_ptr<TreapNode> LC_RC(new TreapNode); // left child's right child
    top->key = 50;
    top->priority = 15;
    top->left = top_LC;
    top->right = top_RC;
    top_LC->key = 30;
    top_LC->priority = 5;
    top_RC->key = 70;
    top_RC->priority = 10;
    top_LC->left = LC_LC;
	top_LC->right = LC_RC;
    LC_LC->key = 20;
    LC_LC->priority = 2;
	LC_RC->key = 40;
    LC_RC->priority = 4;

	// remove nonroot with 2 children
    // check nodes are in proper place
	  /*    top
             50 (key for BST order)
             15 (priority for heap order)              
            / \             
  new_top_LC   top_RC
           40  70
           4   10   
		  /   
    lC_LC    
        20   
        2             
    */ 
    Treap mytreap; // declare Treap object
	
    mytreap.Remove(top, 30);
    
    // should match diagram above
    ASSERT_EQ(50,top->key);
    ASSERT_EQ(40,top->left->key);
    ASSERT_EQ(70,top->right->key);
    ASSERT_EQ(20,top->left->left->key);
    EXPECT_FALSE(top->left->right != NULL); // should be null since LC_RC is now top_LC
}

TEST_F(test_Treap, RemoveNodeWith1ChildTest){
    // hand build treap like this
    /*       top
             50 (key for BST order)
             15 (priority for heap order)              
            / \             
      top_LC   top_RC
           30  70
           5   10   
		  /   
    lC_LC    
        20   
        2      
   
    */ 
    shared_ptr<TreapNode> top(new TreapNode); // root
    shared_ptr<TreapNode> top_LC(new TreapNode); // root's left child
    shared_ptr<TreapNode> top_RC(new TreapNode); // root's right child
    shared_ptr<TreapNode> LC_LC(new TreapNode); // left child's left child
    top->key = 50;
    top->priority = 15;
    top->left = top_LC;
    top->right = top_RC;
    top_LC->key = 30;
    top_LC->priority = 5;
    top_RC->key = 70;
    top_RC->priority = 10;
    top_LC->left = LC_LC;
    LC_LC->key = 20;
    LC_LC->priority = 2;

	// remove nonroot with 2 children
    // check nodes are in proper place
    /*       top
             50 (key for BST order)
             15 (priority for heap order)              
            / \             
    new_top_LC   top_RC
           20  70
           2   10      
    */ 
    Treap mytreap; // declare Treap object
	
    mytreap.Remove(top, 30);
    
    // should match diagram above
    ASSERT_EQ(50,top->key);
    ASSERT_EQ(20,top->left->key);
    ASSERT_EQ(70,top->right->key);
    EXPECT_FALSE(top->left->left != NULL); // should be null since LC_LC is now top_LC
}

TEST_F(test_Treap, SearchTest){
// hand build treap like this
    /*       top
             50 (key for BST order)
             15 (priority for heap order)              
            / \             
      top_LC   top_RC
           30  70
           5   10
          / \  
    lC_LC    LC_RC
        20   40 
        2    4   
    */ 
    shared_ptr<TreapNode> top(new TreapNode); // root
    shared_ptr<TreapNode> top_LC(new TreapNode); // root's left child
    shared_ptr<TreapNode> top_RC(new TreapNode); // root's right child
    shared_ptr<TreapNode> LC_LC(new TreapNode); // left child's left child
    shared_ptr<TreapNode> LC_RC(new TreapNode); // left child's right child
    top->key = 50;
    top->priority = 15;
    top->left = top_LC;
    top->right = top_RC;
    top_LC->key = 30;
    top_LC->priority = 5;
    top_RC->key = 70;
    top_RC->priority = 10;
    top_LC->left = LC_LC;
    top_LC->right = LC_RC;
    LC_LC->key = 20;
    LC_LC->priority = 2;
    LC_RC->key = 40;
    LC_RC->priority = 4;

    Treap mytreap; // declare Treap object
	
    // should be true since nodes are in treap
    ASSERT_TRUE(mytreap.Search(top, 50));
    ASSERT_TRUE(mytreap.Search(top, 30));
    ASSERT_TRUE(mytreap.Search(top, 70));
	ASSERT_TRUE(mytreap.Search(top, 20));
    ASSERT_TRUE(mytreap.Search(top, 40));

	// should be false since nodes not in treap
    ASSERT_FALSE(mytreap.Search(top, -5));
    ASSERT_FALSE(mytreap.Search(top, 31));
    ASSERT_FALSE(mytreap.Search(top, 75));
    ASSERT_FALSE(mytreap.Search(top, 21));
    ASSERT_FALSE(mytreap.Search(top, 43));
}

TEST_F(test_Treap, PriorityTest){
// build treap like this
	/*       top
			 50 (key for BST order)
	         15 (priority for heap order)              
            / \             
      top_LC   top_RC*** (increasing priority and key on this node)
		   30  70
		   5   10
	*/ 
	
	// inserted out of order so testing below will capture if rotations were done properly
	shared_ptr<TreapNode> top(new TreapNode); // root
	Treap mytreap; // declare Treap object
	mytreap.Insert(top, 50, 100, 85, 1, "Nails"); // root
	mytreap.Insert(top, 70, 100, 90, 2, "Screws"); // root's right child
	mytreap.Insert(top, 30, 100, 95, 1, "Hammer"); // root's left child
    
    	/* Treap after priority change and rotations   
             top
			 80 (key for BST order)
	         90 (priority for heap order)              
            /              
      top_LC   
		   50   
		   15   
          /   
	lC_LC    
		30    
		5
	*/ 
    
    mytreap.changePriority(top, 70, 80, 10);
    
    // should match diagram above
    ASSERT_EQ(80,top->key);
    ASSERT_EQ(90,top->priority); // 100 - (10 new_curr_inv/100 max_inv) * 100 = 90
    ASSERT_EQ(50,top->left->key);
    ASSERT_EQ(15,top->left->priority);
    ASSERT_EQ(30,top->left->left->key);
    ASSERT_EQ(5,top->left->left->priority);
}