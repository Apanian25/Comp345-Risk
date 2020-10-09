#pragma once
#include "Orders.h"
#include <vector>
#include <iostream>
using namespace std;


enum Type { bomb, reinforcement, blockade, airlift, diplomacy };


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


class Hand
{
public:
	vector<Cards*> hand;
	//int hand_size = 3; decide hand size 
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