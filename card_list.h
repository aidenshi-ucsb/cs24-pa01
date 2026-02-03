// card_list.h
// Author: Aiden Shi
// All class declarations related to defining a BST that represents a player's hand
#include "card.h"

#ifndef CARD_LIST_H
#define CARD_LIST_H

class CardList {
 public:
  CardList();
  ~CardList();
  bool insert(Card card);
  bool contains(Card card) const;
  bool remove(Card card);
  void printInOrder() const;
  class Iterator;
  Iterator begin();
  Iterator end();
  Iterator rbegin();
  Iterator rend();

 private:
  struct Node {
    Card card;
    Node *parent, *left, *right;
    Node(Card c, Node* p = nullptr) : card(c), parent(p), left(nullptr), right(nullptr) {}
  };
  Node* root;

  void clear(Node* n);
  bool insert(Card card, Node* n);
  Node* getNodeFor(Card card, Node* n) const;
  Node* successor(Node* n) const;
  Node* predecessor(Node* n) const;
  Node* getMin(Node* n) const;
  Node* getMax(Node* n) const;
  void printInOrder(Node* n) const;
};

class CardList::Iterator {
 public:
  Iterator(CardList::Node* pcurr = nullptr, CardList* ptree = nullptr) : curr(pcurr), tree(ptree) {}
  const Card& operator*() const;
  const Card* operator->() const;
  Iterator& operator++();
  Iterator& operator--();
  bool operator==(const Iterator& other) const { return curr == other.curr; }
  bool operator!=(const Iterator& other) const { return curr != other.curr; }

 private:
  CardList::Node* curr;
  CardList* tree;
};

#endif
