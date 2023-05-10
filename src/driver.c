#include "rbtree.h"
#include <stdio.h>
#include <assert.h>


void test_insert(rbtree* t,const int key){
  node_t *p = rbtree_insert(t, key);
  assert(p != NULL);
  assert(t->root == p);
  assert(p->key == key);
  assert(p->left == t->nil);
  assert(p->right == t->nil);
  assert(p->parent == t->nil);
}


int main(int argc, char *argv[]) {
  //트리 생성 및 초기화
  rbtree *t = new_rbtree();
  assert(t != NULL);
  assert(t->nil != NULL);
  assert(t->root == t->nil);

  // 노드 삽입
  node_t* a;
  node_t*b;
  node_t*c;
  node_t*d;
  node_t*e;
  node_t*f;
  node_t*g;
  node_t*h;
  node_t*i;
  node_t*j;
  d=rbtree_insert(t, 35);
  rbtree_insert(t,20);
  f=rbtree_insert(t,50);
  rbtree_insert(t,10);
  rbtree_insert(t,30);
  e=rbtree_insert(t,40);
  g=rbtree_insert(t,80);
  rbtree_insert(t,5);
  a=rbtree_insert(t,15);
  rbtree_insert(t,25);
  b=rbtree_insert(t,33);
  c=rbtree_insert(t,37);
  rbtree_insert(t,45);
  rbtree_insert(t,2);
  h=rbtree_insert(t,27);
  rbt_print(t);

  rbtree_erase(t,a);
  rbtree_erase(t,b);
  rbtree_erase(t,c);
  rbtree_erase(t,d);
  rbtree_erase(t,e);
  rbtree_erase(t,f);
  rbtree_erase(t,g);
  rbtree_erase(t,h);
  rbt_print(t);
  delete_rbtree(t);
}