#include "Cards.h"
#include "Orders.h"
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <algorithm>

/// <summary>
/// 
/// </summary>
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

ostream& operator << (ostream& output, const Cards& card)
{
	if (card.type == 0)
		output << "Card type = bomb" << endl;
	else if (card.type == 1)
		output << "Card type = reinforcement" << endl;
	else if (card.type == 2)
		output << "Card type = blockade" << endl;
	else if (card.type == 3)
		output << "Card type = airlift" << endl;
	else if (card.type == 4)
		output << "Card type = diplomacy" << endl;

	return output;
}

ostream& operator << (ostream& output, const Deck& deck)
{
	for (Cards* c : deck.cards_list)
	{

		output << *c;
	}
	return output;
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

ostream& operator << (ostream& output, const Hand& hand)
{
	for (Cards* c : hand.hand)
	{
		output << *c;
	}
	return output;
}


void Deck::Initialize(Deck& deck, Cards& card) // initizialtes the deck, inserts pointer to Card objects into Vector Cards_list of object Deck
{
	for (int j = 0; j < deck.deck_multiplier; ++j) // deck_multipler used to create size of deck 
	{
		for (int i = 0; i < card.num_of_types; ++i) // loops through all card types, creates a Card and places into the vector
		{
			Cards* card = new Cards();
			card->type = Type(i);
			deck.cards_list.push_back(card);
		}
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


/// <summary>
/// 
/// </summary>
/// <param name="h"></param>
/// <param name="ol"></param>
/// <param name="d"></param>
void Hand::Play(Hand& h, OrderList& ol, Deck& d)
{
	
	std::cout << h << "/n" << " which card would you like to play" << std::endl;
	std::string name;
	std::cin >> name;
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	if (name == "bomb")
	{
		for (Cards* c : h.hand)
		{
			if (c->type == Type(0))
			{
				d.cards_list.push_back(c);
				h.hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());
				break;
			}			
		}

		Bomb* b = new Bomb();
		ol.list.push_back(b);
		std::cout << "Bomb has been played" << std::endl;
	}

	else if (name == "reinforcement")
	{
		for (Cards* c : h.hand)
		{
			if (c->type == Type(1))
			{
				d.cards_list.push_back(c);
				h.hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());
				break;
			}
		}
		std::cout << "Reinforcement has been played, this card is not a special order" << std::endl;
	}

	else if (name == "blockade")
	{
		for (Cards* c : h.hand)
		{
			if (c->type == Type(2))
			{
				d.cards_list.push_back(c);
				h.hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());
				break;
			}
		}

		Blockade* bl = new Blockade();
		ol.list.push_back(bl);
		std::cout << "Blockade has been played" << std::endl;
	}

	else if (name == "airlift")
	{
		for (Cards* c : h.hand)
		{
			if (c->type == Type(3))
			{
				d.cards_list.push_back(c);
				h.hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());
				break;
			}
		}

		Airlift* a = new Airlift();
		ol.list.push_back(a);
		std::cout << "Airlift has been played" << std::endl;
	}
	else if (name == "diplomacy")
	{
		for (Cards* c : h.hand)
		{
			if (c->type == Type(4))
			{
				d.cards_list.push_back(c);
				h.hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());
				break;
			}
		}

		Diplomacy* dp = new Diplomacy();
		ol.list.push_back(dp);
		std::cout << "Diplomacy has been played" << std::endl;
	}
	

}








