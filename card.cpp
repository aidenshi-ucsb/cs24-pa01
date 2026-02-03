// card.cpp
// Author: Aiden Shi
// Implementation of the classes defined in card.h
#include "card.h"
#include <iostream>
#include <string>

Card::Card(std::string line) {
  char s = line[0];
  std::string r = line.substr(2);
  switch (s) {
  case 'c': suit = clubs; break;
  case 'd': suit = diamonds; break;
  case 's': suit = spades; break;
  case 'h': suit = hearts; break; 
  }

  switch (r[0]) {
  case 'a': rank = 1; break;
  case 'k': rank = 13; break;
  case 'q': rank = 12; break;
  case 'j': rank = 11; break;
  default: rank = std::stoi(r); break;
  }
}

int Card::value() const {
  return ((int)suit * 64) + rank;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
  switch (card.suit) {
  case clubs: os << "c "; break;
  case diamonds: os << "d "; break;
  case spades: os << "s "; break;
  case hearts: os << "h "; break;
  }

  if (card.rank == 1) {
    os << 'a';
  } else if (card.rank <= 10) {
    os << card.rank;
  } else {
    char lut[] = {'j', 'q', 'k'};
    os << lut[card.rank - 11];
  }
  return os;
}

bool operator==(const Card& self, const Card& other) {
  return self.value() == other.value();
}

bool operator>(const Card& self, const Card& other) {
  return self.value() > other.value();
}

bool operator<(const Card& self, const Card& other) {
  return other > self;
}
