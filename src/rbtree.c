#include "rbtree.h"
#include <stdlib.h>
// #include <stdio.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t * nil = (node_t *)calloc(1,sizeof(node_t));
  nil->color = RBTREE_BLACK;
  p->root = nil;
  p->nil = nil;
  return p;
}

void _delete_rbtree(rbtree *t, node_t *node){
 if (node == t->nil || node ==NULL) {return;}
 _delete_rbtree(t, node->left);
 _delete_rbtree(t, node->right);
 free(node); 
}
void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  _delete_rbtree(t, t->root);
  free(t->nil);
  free(t);
}

// void _rbt_print(rbtree* t, node_t*root){
//   if (root==NULL||root==t->nil) return;  
//   _rbt_print(t, root->left);
//   printf("(%d, %d) ",root->key,root->color);
//   _rbt_print(t, root->right);
// }
// void rbt_print(rbtree* tree){
//   _rbt_print(tree, tree->root);
//   printf("(root data: %d)\n",tree->root->key);
// }


void rbtree_left_rotate(rbtree *t,node_t *x){
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != t->nil) y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == t->nil) t->root = y;
  else if (x==x->parent->left) x->parent->left = y;
  else x->parent->right = y;
  x->parent = y;
  y->left = x;
  return ;
}

void rbtree_right_rotate(rbtree *t,node_t *x){
  node_t *y = x->left;
  x->left = y->right;
  if (y->right != t->nil) y->right->parent = x;
  y->parent = x->parent;
  if (x->parent == t->nil) t->root = y;
  else if (x==x->parent->right) x->parent->right = y;
  else x->parent->left = y;
  x->parent = y;
  y->right = x;
  return;
}

void _rbtree_insert_fixup(rbtree *t, node_t *z){
  while (z->parent->color==RBTREE_RED){
    if (z->parent == z->parent->parent->left){
      node_t *y = z->parent->parent->right;
      if (y->color==RBTREE_RED){
        z->parent->color=RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color=RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        if (z==z->parent->right){
          z = z->parent;
          rbtree_left_rotate(t,z);
        }
        z->parent->color=RBTREE_BLACK;
        z->parent->parent->color=RBTREE_RED;
        rbtree_right_rotate(t,z->parent->parent);
      }
    }
    else {
      node_t *y = z->parent->parent->left;
      if (y->color==RBTREE_RED){
        z->parent->color=RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color=RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        if (z==z->parent->left){
          z = z->parent;
          rbtree_right_rotate(t,z);
        }
        z->parent->color=RBTREE_BLACK;
        z->parent->parent->color=RBTREE_RED;
        rbtree_left_rotate(t,z->parent->parent);
      }
    }
  }
  t->root->color=RBTREE_BLACK;
  return;
}

void _rbtree_insert(rbtree *t, node_t *z){
  node_t *y = t->nil;
  node_t *x = t->root;
  while (x!=t->nil){
    y = x;
    if (z->key < x->key) x = x->left;
    else x = x->right;
  }
  z->parent = y;
  if (y == t->nil) t->root = z;
  else if(z->key < y->key) y->left=z;
  else y->right=z;
  _rbtree_insert_fixup(t,z);
  return;
}
node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *node = (node_t *)calloc(1,sizeof(node_t));
  node->key=key;
  node->color = RBTREE_RED;
  node->left = node->right = node->parent = t->nil;
  _rbtree_insert(t, node);
  return node;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t * cursor = t->root;
  while (cursor != t->nil){
    if (cursor->key == key) return cursor;
    else if (cursor->key < key) cursor=cursor->right;
    else cursor=cursor->left;
  }
  return NULL;
}

node_t *_rbtree_min(const rbtree *t,node_t *node){
  node_t* tmp = node;
  while (tmp->left != t->nil){
    tmp = tmp->left;
  }
  return tmp;
}
node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return _rbtree_min(t,t->root);
}

node_t *_rbtree_max(const rbtree *t,node_t *node){
  node_t* tmp = node;
  while (tmp->right != t->nil){
    tmp = tmp->right;
  }
  return tmp;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return _rbtree_max(t,t->root);
}

void _rbtree_succeeding(rbtree *t, node_t *del_n, node_t *suc_n){
  //del_n 노드를 삭제하고 그 자리에 suc_n 넣는 함수
  if (del_n->parent == t->nil) t->root = suc_n;
  else if (del_n==del_n->parent->left) del_n->parent->left=suc_n;
  else del_n->parent->right=suc_n;
  suc_n->parent=del_n->parent;
}

void _rbtree_erase_fix(rbtree *t, node_t*x){
  while (x!=t->root && x->color==RBTREE_BLACK){
    if (x==x->parent->left){
      node_t* w = x->parent->right;
      if (w->color==RBTREE_RED){
        w->color=RBTREE_BLACK;
        x->parent->color=RBTREE_RED;
        rbtree_left_rotate(t,x->parent);
        w = x->parent->right;
      }
      if (w->left->color==RBTREE_BLACK && w->right->color==RBTREE_BLACK){
        w->color=RBTREE_RED;
        x=x->parent;
      }
      else{
        if(w->right->color==RBTREE_BLACK){
          w->left->color=RBTREE_BLACK;
          w->color=RBTREE_RED;
          rbtree_right_rotate(t,w);
          w = x->parent->right;
        }
        w->color=x->parent->color;
        x->parent->color=RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        rbtree_left_rotate(t,x->parent);
        x=t->root;
      }
    }
    else{
      node_t* w = x->parent->left;
      if (w->color==RBTREE_RED){
        w->color=RBTREE_BLACK;
        x->parent->color=RBTREE_RED;
        rbtree_right_rotate(t,x->parent);
        w = x->parent->left;
      }
      if (w->left->color==RBTREE_BLACK && w->right->color==RBTREE_BLACK){
        w->color=RBTREE_RED;
        x=x->parent;
      }
      else{
        if(w->left->color==RBTREE_BLACK){
          w->right->color=RBTREE_BLACK;
          w->color=RBTREE_RED;
          rbtree_left_rotate(t,w);
          w = x->parent->left;
        }
        w->color=x->parent->color;
        x->parent->color=RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        rbtree_right_rotate(t,x->parent);
        x=t->root;
      }
    }
  }
  x->color=RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z) {
  // TODO: implement erase
  node_t *y = z;
  node_t *x;
  int y_origin_color = y->color;
  if (z->left == t->nil){
    x = z->right;
    _rbtree_succeeding(t, z,z->right);
  }
  else if(z->right==t->nil){
    x = z->left;
    _rbtree_succeeding(t, z,z->left);
  }
  else{
    y = _rbtree_min(t, z->right);
    y_origin_color = y->color;
    x = y->right;
    if (y->parent==z){
      x->parent=y;
    }
    else{
      _rbtree_succeeding(t, y, y->right);
      y->right = z->right;
      y->right->parent=y;
    }
    _rbtree_succeeding(t,z,y);
    y->left=z->left;
    y->left->parent=y;
    y->color = z->color;
  }
  if(y_origin_color==RBTREE_BLACK){
    _rbtree_erase_fix(t,x);
  }
  free(z);
  return 0;
}


void _rbtree_to_array(const rbtree *t, key_t *arr, const size_t n, node_t*curr, int* idx){
  if (curr==t->nil) return;
  _rbtree_to_array(t,arr,n,curr->left,idx);
  if (*idx<n){
    arr[*idx]=curr->key;
    *idx=*idx+1;
  } 
  _rbtree_to_array(t,arr,n,curr->right,idx);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  node_t* cursor = t->root;
  int idx;
  idx = 0;
  _rbtree_to_array(t,arr,n,cursor,&idx);
  return 0;
}
