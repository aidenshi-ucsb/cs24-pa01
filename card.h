// card.h
// Author: Aiden Shi
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H
#include <string>

enum Suit { clubs, diamonds, spades, hearts };

class Card {
 public:
  Suit suit;
  int rank;
  Card(Suit s, int r) : suit(s), rank(r) {};
  Card(std::string line);
  int value() const;

  friend bool operator==(const Card& self, const Card& other);
  friend bool operator<(const Card& self, const Card& other);
  friend bool operator>(const Card& self, const Card& other);

  friend std::ostream& operator<<(std::ostream& os, const Card& card);
};


#endif
