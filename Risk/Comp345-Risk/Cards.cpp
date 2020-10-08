#include "Cards.h"
#include <iostream>
#include <cstdlib>
#include <iterator>


Cards::Cards()
{

}

Cards::Cards(const Cards& card)
{
	type = card.type;
	num_of_types = card.num_of_types;
}

Cards :: ~Cards()
{

}

Cards& Cards :: operator= (const Cards& card)
{
	type = card.type;
	num_of_types = card.num_of_types;
	return *this;
}



Deck::Deck() // deck default constructor 
{

}

Deck::Deck(const Deck& orig) : cards_list(orig.cards_list.size()) // deck copy contrustor for vector
{
	for (std::size_t i = 0; i < orig.cards_list.size(); ++i)
		cards_list[i] = new Cards(*orig.cards_list[i]);
}

Deck :: ~Deck() // deck destructor
{
	for (int i = 0; i < cards_list.size(); i++)
	{
		delete cards_list[i];
		cards_list[i] = NULL;
	}
}

Deck& Deck::operator= (const Deck& deck)
{
	// do the copy
	cards_list = deck.cards_list;
	deck_multiplier = deck.deck_multiplier;
	return *this;
}


Hand::Hand() // hand default constuructor 
{

}

Hand::Hand(const Hand& orig) : hand(orig.hand.size()) // hand copy contrustor for vector
{
	for (std::size_t i = 0; i < orig.hand.size(); ++i)
		hand[i] = new Cards(*orig.hand[i]);
}

Hand :: ~Hand() // hand destructor
{
	for (int i = 0; i < hand.size(); i++)
	{
		delete hand[i];
		hand[i] = NULL;
	}
}

Hand& Hand::operator= (const Hand& h)
{
	hand = h.hand;
	return *this;
}



void Cards::Print_Card() // prints Every card, matches enum index to card type
{
	if (type == 0)
		std::cout << "Card type = bomb" << std::endl;
	else if (type == 1)
		std::cout << "Card type = reinforcement" << std::endl;
	else if (type == 2)
		std::cout << "Card type = blockade" << std::endl;
	else if (type == 3)
		std::cout << "Card type = airlift" << std::endl;
	else if (type == 4)
		std::cout << "Card type = diplomacy" << std::endl;
}

void Deck::Initialize(Deck& deck, Cards& card) // initizialtes the deck, inserts pointer to Card objects into Vector Cards_list of object Deck
{
	for (int j = 0; j < deck.deck_multiplier; ++j) // deck_multipler used to create size of deck 
	{
		//int num_of_types = 6;
		for (int i = 0; i < card.num_of_types; ++i) // loops through all card types, creates a Card and places into the vector
		{
			Cards* card = new Cards();
			card->type = Type(i);
			deck.cards_list.push_back(card);
		}
	}

}


void Deck::Print_Deck(const Deck& deck)  // calls print_card method to print the whole deck 
{
	for (Cards* c : deck.cards_list)
	{

		c->Cards::Print_Card();
	}
}


void Deck::shuffle(Deck& deck)  // shuffles the deck so it is randomly generated 
{
	vector <Cards*> shuffled_Deck;
	while (!deck.cards_list.empty())
	{
		size_t randomizer = rand() % deck.cards_list.size();
		shuffled_Deck.push_back(deck.cards_list[randomizer]);
		deck.cards_list.erase(deck.cards_list.begin() + randomizer);
	}
	for (Cards* card : shuffled_Deck)
	{
		deck.cards_list.push_back(card);
	}

}



void Hand::Draw(Deck& deck, Hand& h) // draws from a shuffled deck and places in a vector which is the players hand 
{
	//for (int i = 0; i < hand_size; i ++)
	//{
	h.hand.push_back(deck.cards_list[0]);
	deck.cards_list.erase(deck.cards_list.begin());
	//}


}


void Hand::Print_Hand(const Hand& hand) // print the hand vector by calling print_card
{
	for (Cards* c : hand.hand)
	{
		c->Cards::Print_Card();
	}
}



void Hand::Play()// need order list to do 
{

}








