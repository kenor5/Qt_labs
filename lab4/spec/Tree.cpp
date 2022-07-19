#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

bool cmp1(const TreeNode &x,const TreeNode &y){
    return x.getX()<y.getX();
}

bool cmp2(const TreeNode &x,const TreeNode &y){
    return x.getY()<y.getY();
}

bool cmp3(const TreeNode &x,const TreeNode &y){
    return x.getX()==y.getX();
}
bool (*cmp[3])(const TreeNode &x,const TreeNode &y)={cmp1,cmp2,cmp3};
TreeNode::TreeNode()
{
      data[0]=0;
      data[1]=0;
      idx=0;
      left=nullptr;
      right=nullptr;
  }
TreeNode::TreeNode(int x,int y){
    data[0]=x;
    data[1]=y;
    idx=0;
    left=nullptr;
    right=nullptr;
}
ostream &operator<<(ostream &out, const TreeNode &b){
    out<<b.data[0]<<b.data[1];
    return out;
}

istream &operator>>(istream &in,TreeNode &b){
    in>>b.data[0]>>b.data[1];
    return in;
}

int TreeNode::getX() const{
    return data[0];
}

int TreeNode::getY() const{
    return data[1];
}

TreeNode::~TreeNode(){

}

istream &operator>>(istream &in, BinaryDimonTree &tree){
    int m;
    in>>m;
    tree.ts=new TreeNode [m];
    for(int i=0;i<m;i++){
        in>>tree.ts[i];
    }
     tree.BuildtheTree(tree.root,0,m-1,0);
    return in;
}
void BinaryDimonTree::BuildtheTree(TreeNode* &ro, int l, int r, int dep){
    if(l>r)
        return;
    sort(ts+l,ts+r+1,cmp[dep]);
    int mid=(l+r)/2;
    ro=&ts[mid];
    ro->idx=dep;
    dep=(dep+1)%2;
    BinaryDimonTree::BuildtheTree(ro->left,l,mid-1,dep);
    BinaryDimonTree::BuildtheTree(ro->right,mid+1,r,dep);
    return ;
}
BinaryDimonTree::BinaryDimonTree(){
    root=nullptr;
    ts=nullptr;
}
TreeNode *BinaryDimonTree::find_nearest_node(int x, int y){
    long long int ll=LLONG_MAX;
    TreeNode** guess=nullptr;
    recur_search(root,x,y,ll,guess);
    return *guess;
}
long long int dist(int x,int y,int a,int b){
    long long int dx=x-a,dy=y-b;
    return dx*dx+dy*dy;
}
void BinaryDimonTree::recur_search(TreeNode* &cur, int x, int y, long long int &min_distance, TreeNode ** &guess){
    if(cur==nullptr)
        return;
    long long int distance=dist(cur->getX(),cur->getY(),x,y);
    if(distance==min_distance){
        if(cmp[0](*cur,**guess)||(cmp[2](*cur,**guess)&&cmp[1](*cur,**guess))){
            min_distance=distance;
            guess=&cur;
        }
    }
    if(distance<min_distance)
    {
        min_distance=distance;
        guess=&cur;
    }
    int split[2]={cur->getX()-x,cur->getY()-y};
    if(split[cur->idx]>0)
        BinaryDimonTree::recur_search(cur->left,x,y,min_distance,guess);
    else
        BinaryDimonTree::recur_search(cur->right,x,y,min_distance,guess);
    if(split[cur->idx]*split[cur->idx]<min_distance){
        if(split[cur->idx]>0)
            BinaryDimonTree::recur_search(cur->right,x,y,min_distance,guess);
        else
            BinaryDimonTree::recur_search(cur->left,x,y,min_distance,guess);
    }
}
BinaryDimonTree::~BinaryDimonTree(){
   delete [] ts;
}
