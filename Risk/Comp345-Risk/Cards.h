#pragma once
#include <vector>
#include <iostream>
using namespace std;


enum Type { bomb, reinforcement, blockade, airlift, diplomacy };


class Cards
{
public:
	Type type;
	int num_of_types = 5;
	//void Print_Card();
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
	//void Print_Deck(const Deck&);
	void shuffle(Deck&);
	Deck();
	~Deck();
	Deck(const Deck& orig);
	Deck& operator= (const Deck& deck);
	friend ostream & operator << (ostream &output, const Deck& deck);


	// stream opeartor overlaod 
};


class Hand
{
public:
	vector<Cards*> hand;
	//int hand_size = 3; decide hand size 
	void Draw(Deck&, Hand&);
	//void Print_Hand(const Hand&);
	void Play();// TO DO
	Hand();
	~Hand();
	Hand(const Hand& orig);
	Hand& operator= (const Hand& hand);
	friend ostream& operator << (ostream& output, const Hand& hand);


	// stream opeartor overlaod 

};




namespace CardsDriver {
	int main();
}