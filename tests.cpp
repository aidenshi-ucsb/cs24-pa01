// tests.cpp
// Author: Aiden Shi
// Test cases for CardList BST implementation

#include <iostream>
#include <sstream>
#include <vector>
#include "card.h"
#include "card_list.h"

using namespace std;

int tests_passed = 0;
int tests_failed = 0;

void test(bool condition, const string& name) {
  if (condition) {
    cout << "PASS: " << name << endl;
    tests_passed++;
  } else {
    cout << "FAIL: " << name << endl;
    tests_failed++;
  }
}

// copied from main.cpp
void playGame(CardList& hand_a, CardList& hand_b, vector<Card>& alice_picks, vector<Card>& bob_picks) {
  bool found = true;
  while (found) {
    found = false;
    for (auto it_a = hand_a.begin(); it_a != hand_a.end(); ++it_a) {
      if (hand_b.contains(*it_a)) {
        Card to_erase = *it_a;
        alice_picks.push_back(to_erase);
        hand_a.remove(to_erase);
        hand_b.remove(to_erase);
        found = true;
        break;
      }
    }
    for (auto it_b = hand_b.rbegin(); it_b != hand_b.rend(); --it_b) {
      if (hand_a.contains(*it_b)) {
        Card to_erase = *it_b;
        bob_picks.push_back(to_erase);
        hand_a.remove(to_erase);
        hand_b.remove(to_erase);
        found = true;
        break;
      }
    }
  }
}

// ==================== BST PUBLIC METHODS TESTS ====================
void test_empty_tree() {
  CardList list;
  test(list.contains(Card(hearts, 5)) == false, "empty tree: contains returns false");
  test(list.remove(Card(hearts, 5)) == false, "empty tree: remove returns false");
  test(list.insert(Card(hearts, 5)) == true, "empty tree: insert returns true");
  stringstream buf;
  streambuf* old = cout.rdbuf(buf.rdbuf());
  CardList list2;
  list2.printInOrder();
  cout.rdbuf(old);
  test(buf.str() == "", "empty tree: printInOrder prints nothing");
}

void test_single_node() {
  CardList list;
  list.insert(Card(hearts, 5));
  test(list.contains(Card(hearts, 5)) == true, "single node: contains returns true");
  test(list.contains(Card(clubs, 3)) == false, "single node: contains non-existent returns false");
  stringstream buf;
  streambuf* old = cout.rdbuf(buf.rdbuf());
  list.printInOrder();
  cout.rdbuf(old);
  test(buf.str().find("h 5") != string::npos, "single node: printInOrder prints node");
  test(list.remove(Card(hearts, 5)) == true, "single node: remove returns true");
  test(list.contains(Card(hearts, 5)) == false, "single node: after remove contains returns false");
}

void test_multiple_nodes() {
  CardList list;
  list.insert(Card(hearts, 5));
  list.insert(Card(clubs, 3));
  list.insert(Card(spades, 10));
  test(list.contains(Card(hearts, 5)) && list.contains(Card(clubs, 3)) && list.contains(Card(spades, 10)),
       "multiple nodes: contains all inserted nodes");
  stringstream buf;
  streambuf* old = cout.rdbuf(buf.rdbuf());
  list.printInOrder();
  cout.rdbuf(old);
  string out = buf.str();
  test(out.find("c 3") < out.find("s 10") && out.find("s 10") < out.find("h 5"),
       "multiple nodes: printInOrder in correct order");
  list.remove(Card(clubs, 3));
  test(!list.contains(Card(clubs, 3)) && list.contains(Card(hearts, 5)) && list.contains(Card(spades, 10)),
       "multiple nodes: remove only affects target node");
}

void test_edge_cases() {
  CardList list;
  list.insert(Card(hearts, 5));
  test(list.insert(Card(hearts, 5)) == false, "edge case: insert duplicate returns false");
  test(list.remove(Card(clubs, 3)) == false, "edge case: remove non-existent returns false");
  list.insert(Card(clubs, 3));
  list.remove(Card(clubs, 3));
  stringstream buf;
  streambuf* old = cout.rdbuf(buf.rdbuf());
  list.printInOrder();
  cout.rdbuf(old);
  test(buf.str().find("c 3") == string::npos, "edge case: removed node not in printInOrder");
}

void test_memory_management() {
  {
    CardList list;
    list.insert(Card(hearts, 5));
    list.insert(Card(clubs, 3));
    list.insert(Card(spades, 10));
  }
  test(true, "memory: destructor cleans up without crash");
  
  {
    CardList list;
    list.insert(Card(hearts, 5));
    list.insert(Card(clubs, 3));
    list.insert(Card(spades, 10));
    list.remove(Card(hearts, 5));
    list.remove(Card(clubs, 3));
    list.remove(Card(spades, 10));
  }
  test(true, "memory: remove all nodes without crash");
}

// ==================== ITERATOR TESTS ====================
void test_iterator_empty_tree() {
  CardList list;
  test(list.begin() == list.end(), "iterator: empty tree begin() == end()");
  test(list.rbegin() == list.rend(), "iterator: empty tree rbegin() == rend()");
}

void test_iterator_single_node() {
  CardList list;
  list.insert(Card(hearts, 5));
  auto it = list.begin();
  test(*it == Card(hearts, 5), "iterator: single node dereference");
  ++it;
  test(it == list.end(), "iterator: single node ++ reaches end");
}

void test_iterator_forward_traversal() {
  CardList list;
  list.insert(Card(hearts, 5));
  list.insert(Card(clubs, 3));
  list.insert(Card(spades, 10));
  vector<Card> cards;
  for (auto it = list.begin(); it != list.end(); ++it) {
    cards.push_back(*it);
  }
  test(cards.size() == 3, "iterator: forward traversal visits all nodes");
  test(cards[0] < cards[1] && cards[1] < cards[2], "iterator: forward traversal in order");
}

void test_iterator_reverse_traversal() {
  CardList list;
  list.insert(Card(hearts, 5));
  list.insert(Card(clubs, 3));
  list.insert(Card(spades, 10));
  vector<Card> cards;
  for (auto it = list.rbegin(); it != list.rend(); --it) {
    cards.push_back(*it);
  }
  test(cards.size() == 3, "iterator: reverse traversal visits all nodes");
  test(cards[0] > cards[1] && cards[1] > cards[2], "iterator: reverse traversal in reverse order");
}

void test_iterator_comparison() {
  CardList list;
  list.insert(Card(hearts, 5));
  list.insert(Card(clubs, 3));
  auto it1 = list.begin();
  auto it2 = list.begin();
  test(it1 == it2, "iterator: == works for same position");
  ++it2;
  test(it1 != it2, "iterator: != works for different positions");
}

// ==================== PLAYGAME TESTS ====================
void test_playgame_common_cards() {
  CardList alice, bob;
  alice.insert(Card(hearts, 5));
  alice.insert(Card(clubs, 3));
  alice.insert(Card(spades, 10));
  bob.insert(Card(hearts, 5));
  bob.insert(Card(diamonds, 7));
  bob.insert(Card(spades, 10));
  
  vector<Card> alice_picks, bob_picks;
  playGame(alice, bob, alice_picks, bob_picks);
  
  test(alice_picks.size() + bob_picks.size() == 2, "playGame: common cards - correct number of matches");
  test(!alice.contains(Card(hearts, 5)) && !alice.contains(Card(spades, 10)),
       "playGame: common cards removed from Alice");
  test(!bob.contains(Card(hearts, 5)) && !bob.contains(Card(spades, 10)),
       "playGame: common cards removed from Bob");
}

void test_playgame_one_empty_hand() {
  CardList alice, bob;
  alice.insert(Card(hearts, 5));
  
  vector<Card> alice_picks, bob_picks;
  playGame(alice, bob, alice_picks, bob_picks);
  
  test(alice_picks.size() == 0 && bob_picks.size() == 0, "playGame: one empty hand - no matches");
  test(alice.contains(Card(hearts, 5)), "playGame: one empty hand - Alice keeps card");
}

void test_playgame_no_common_cards() {
  CardList alice, bob;
  alice.insert(Card(hearts, 5));
  alice.insert(Card(clubs, 3));
  bob.insert(Card(diamonds, 7));
  bob.insert(Card(spades, 10));
  
  vector<Card> alice_picks, bob_picks;
  playGame(alice, bob, alice_picks, bob_picks);
  
  test(alice_picks.size() == 0 && bob_picks.size() == 0, "playGame: no common cards - no matches");
  test(alice.contains(Card(hearts, 5)) && alice.contains(Card(clubs, 3)),
       "playGame: no common cards - Alice keeps all");
  test(bob.contains(Card(diamonds, 7)) && bob.contains(Card(spades, 10)),
       "playGame: no common cards - Bob keeps all");
}

int main() {
  cout << "========== BST PUBLIC METHODS TESTS ==========" << endl;
  test_empty_tree();
  test_single_node();
  test_multiple_nodes();
  test_edge_cases();
  test_memory_management();

  cout << "\n========== ITERATOR TESTS ==========" << endl;
  test_iterator_empty_tree();
  test_iterator_single_node();
  test_iterator_forward_traversal();
  test_iterator_reverse_traversal();
  test_iterator_comparison();

  cout << "\n========== PLAYGAME TESTS ==========" << endl;
  test_playgame_common_cards();
  test_playgame_one_empty_hand();
  test_playgame_no_common_cards();

  cout << "\n========== SUMMARY ==========" << endl;
  cout << "Passed: " << tests_passed << endl;
  cout << "Failed: " << tests_failed << endl;

  return tests_failed > 0 ? 1 : 0;
}
