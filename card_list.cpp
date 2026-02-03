// card_list.cpp
// Author: Aiden Shi
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include <iostream>

CardList::CardList() : root(nullptr) {}

CardList::~CardList() {
  clear(root);
}

void CardList::clear(Node* n) {
  if (!n) return;
  clear(n->left);
  clear(n->right);
  delete n;
}

bool CardList::insert(Card card) {
  if (!root) {
    root = new Node(card, nullptr);
    return true;
  }
  return insert(card, root);
}

bool CardList::insert(Card card, Node* n) {
  if (card == n->card) return false;
  if (card < n->card) {
    if (!n->left) {
      n->left = new Node(card, n);
      return true;
    }
    return insert(card, n->left);
  } else {
    if (!n->right) {
      n->right = new Node(card, n);
      return true;
    }
    return insert(card, n->right);
  }
}

CardList::Node* CardList::getNodeFor(Card card, Node* n) const {
  if (!n || card == n->card) return n;
  if (card > n->card) return getNodeFor(card, n->right);
  return getNodeFor(card, n->left);
}

bool CardList::contains(Card card) const {
  return getNodeFor(card, root) != nullptr;
}

CardList::Node* CardList::getMin(Node* n) const {
  if (!n) return nullptr;
  while (n->left) {
    n = n->left;
  }
  return n;
}

CardList::Node* CardList::getMax(Node* n) const {
  if (!n) return nullptr;
  while (n->right) {
    n = n->right;
  }
  return n;
}

CardList::Node* CardList::successor(Node* n) const {
  if (!n) return nullptr;
  if (n->right) {
    return getMin(n->right);
  }
  Node* p = n->parent;
  while (p && n == p->right) {
    n = p;
    p = p->parent;
  }
  return p;
}

CardList::Node* CardList::predecessor(Node* n) const {
  if (!n) return nullptr;
  if (n->left) {
    return getMax(n->left);
  }
  Node* p = n->parent;
  while (p && n == p->left) {
    n = p;
    p = p->parent;
  }
  return p;
}

bool CardList::remove(Card card) {
  Node* to_remove = getNodeFor(card, root);
  if (!to_remove) return false;

  if (!to_remove->left && !to_remove->right) {
    Node* parent = to_remove->parent;
    if (!parent) {
      root = nullptr;
    } else {
      if (parent->right == to_remove) parent->right = nullptr;
      else parent->left = nullptr;
    }
    delete to_remove;
  } else if (!to_remove->left || !to_remove->right) {
    Node* parent = to_remove->parent;
    Node* subtree = to_remove->right ? to_remove->right : to_remove->left;
    if (!parent) {
      root = subtree;
      subtree->parent = nullptr;
    } else {
      subtree->parent = parent;
      if (parent->right == to_remove) parent->right = subtree;
      else parent->left = subtree;
    }
    delete to_remove;
  } else {
    Node* succ = successor(to_remove);
    to_remove->card = succ->card;

    Node* succ_parent = succ->parent;
    Node* succ_right = succ->right;

    if (succ_parent->left == succ) succ_parent->left = succ_right;
    else succ_parent->right = succ_right;

    if (succ_right) succ_right->parent = succ_parent;
    delete succ;
  }
  return true;
}

void CardList::printInOrder(Node* n) const {
  if (!n) return;
  printInOrder(n->left);
  std::cout << n->card << " ";
  printInOrder(n->right);
}

void CardList::printInOrder() const {
  printInOrder(root);
}

CardList::Iterator CardList::begin() {
  return Iterator(getMin(root), this);
}

CardList::Iterator CardList::end() {
  return Iterator(nullptr, this);
}

CardList::Iterator CardList::rbegin() {
  return Iterator(getMax(root), this);
}

CardList::Iterator CardList::rend() {
  return Iterator(nullptr, this);
}

const Card& CardList::Iterator::operator*() const {
  return curr->card;
}

const Card* CardList::Iterator::operator->() const {
  return &(curr->card);
}

CardList::Iterator& CardList::Iterator::operator++() {
  curr = tree->successor(curr);
  return *this;
}

CardList::Iterator& CardList::Iterator::operator--() {
  curr = tree->predecessor(curr);
  return *this;
}
