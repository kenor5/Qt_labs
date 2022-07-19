//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
class BinaryDimonTree;
class TreeNode
{
  friend ostream &operator<<(ostream &out,TreeNode &b);
  friend istream &operator>>(istream &in,TreeNode &b);
  friend istream &operator>>(istream &in, BinaryDimonTree &tree);
  friend class BinaryTree;
  friend class BinaryDimonTree;

private:
  /* data */

  TreeNode* left;
  TreeNode* right;
public:
  int data[2];
  int idx;
  /* methods */
  TreeNode();
  TreeNode(int x,int y);
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  ~TreeNode(); /* DO NOT CHANGE */
};


class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:
  /* data */
  TreeNode *root;
  TreeNode *ts;
public:
  /* methods */
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */
  void BuildtheTree(TreeNode* &ro,int l,int r,int dep);
  void recur_search(TreeNode* &cur, int x, int y, long long int &min_distance, TreeNode ** &guess);
  ~BinaryDimonTree();
};

#endif //C_BINARYDIMEN_TREE_H
