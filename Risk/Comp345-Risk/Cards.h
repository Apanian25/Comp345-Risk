#pragma once
#include "Orders.h"
#include <vector>
#include <iostream>
using namespace std;

/// <summary>
/// free function of enum type to hold all types of cards for simplicity
/// </summary>
enum Type { bomb, reinforcement, blockade, airlift, diplomacy };



/// <summary>
/// Crad class that initializes each separate card
/// each card has a type whihc is held in the enum 
/// there is a max of 5 types of cards
/// </summary>
class Cards
{
public:
	Type type;
	int num_of_types = 5;
	Cards();
	~Cards();
	Cards(const Cards& card);
	Cards& operator= (const Cards& c);

	friend ostream & operator << (ostream& output, const Cards& card);
	
};

/// <summary>
/// class that creates the Deck
/// the Deck is simply a vector that holds pointers to cards objects
/// deck_multiplier can be change depending on what size the deck should be 
/// </summary>
class  Deck
{
public:
	vector<Cards*> cards_list;
	int deck_multiplier = 5;
	void Initialize(Deck& deck, Cards& card);
	void shuffle(Deck&);
	Deck();
	~Deck();
	Deck(const Deck& orig);
	Deck& operator= (const Deck& deck);

	friend ostream & operator << (ostream &output, const Deck& deck);
};


/// <summary>
/// a class for the Hand of a player 
/// similar to the Deck class and hand is a vector of pointers to  card objects
/// </summary>
class Hand
{
public:
	vector<Cards*> hand; 
	void Draw(Deck&, Hand&);
	void Play(Hand& h, OrderList& ol, Deck& d);
	Hand();
	~Hand();
	Hand(const Hand& orig);
	Hand& operator= (const Hand& hand);

	friend ostream& operator << (ostream& output, const Hand& hand);

};


namespace CardsDriver {
	int main();
}