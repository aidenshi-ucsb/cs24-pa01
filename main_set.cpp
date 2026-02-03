// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

void playGame(set<Card>& hand_a, set<Card>& hand_b) {
  bool found = true;
  while (found) {
    found = false;
    for (auto it_a = hand_a.begin(); it_a != hand_a.end(); it_a++) {
      if (hand_b.find(*it_a) != hand_b.end()) {
	cout << "Alice picked matching card " << *it_a << "\n";
        Card to_erase = *it_a;
        hand_a.erase(to_erase);
        hand_b.erase(to_erase);
	found = true;
	break;
      }
    }

    for (auto it_b = hand_b.rbegin(); it_b != hand_b.rend(); it_b++) {
      if (hand_a.find(*it_b) != hand_a.end()) {
	cout << "Bob picked matching card " << *it_b << "\n";
        Card to_erase = *it_b;
        hand_a.erase(to_erase);
        hand_b.erase(to_erase);
        found = true;
	break;
      }
    }
  }

  cout << "\nAlice's cards:\n";
  for (auto i = hand_a.begin(); i != hand_a.end(); i++) {
    cout << *i << "\n";
  }

  cout << "\nBob's cards:\n";
  for (auto i = hand_b.begin(); i != hand_b.end(); i++) {
    cout << *i << "\n";
  }
}

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  set<Card> hand_a{};
  set<Card> hand_b{};

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    hand_a.insert(Card(line));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    hand_b.insert(Card(line));
  }
  cardFile2.close();

  playGame(hand_a, hand_b);
  
  return 0;
}
