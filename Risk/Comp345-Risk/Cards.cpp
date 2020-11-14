#include "Cards.h"
#include "Orders.h"
#include <iostream>
#include <cstdlib>
#include <time.h> 
#include <iterator>
#include <algorithm>

/// <summary>
/// Cards class constructor 
/// </summary>
Cards::Cards()
{

}

/// <summary>
/// Cards class shallow copy constructor
/// </summary>
/// <param name="card"> takes in a constant Card object by reference </param>
Cards::Cards(const Cards& card)
{
	type = card.type;
	num_of_types = card.num_of_types;
}

/// <summary>
/// Cards Class destructor
/// </summary>
Cards :: ~Cards()
{

}

/// <summary>
/// Cards class assignment operator 
/// </summary>
/// <param name="card"> takes in a constant Card object by reference </param>
/// <returns></returns>
Cards& Cards :: operator= (const Cards& card)
{
	type = card.type;
	num_of_types = card.num_of_types;
	return *this;
}


/// <summary>
/// Deck class constructor
/// </summary>
Deck::Deck() // deck Class constructor 
{

}

/// <summary>
/// Deck class deep copy constructor:
///  iterates through the card_list vector and creates a pointer to a new Card in the paramter's deck
/// </summary>
/// <param name="orig"> takes a constant Deck object by reference</param>
Deck::Deck(const Deck& orig) : cards_list(orig.cards_list.size()) 
{
	for (int i = 0; i < orig.cards_list.size(); ++i)
		cards_list[i] = new Cards(*orig.cards_list[i]);
}

/// <summary>
/// Deck class destructor: 
/// iterates through the vector card_list and deletes each slot and then makes the pointer point to null
/// </summary>
Deck :: ~Deck() 
{
	for (int i = 0; i < cards_list.size(); i++)
	{
		delete cards_list[i];
		cards_list[i] = NULL;
	}
}


/// <summary>
/// Deck class assignment operator 
/// </summary>
/// <param name="deck">takes a constant Deck object by reference </param>
/// <returns></returns>
Deck& Deck::operator= (const Deck& deck)
{
	
	cards_list = deck.cards_list;
	deck_multiplier = deck.deck_multiplier;
	return *this;
}

/// <summary>
/// stream insertion operator for Card class: 
/// uses if else block to match the type of the card to the correct type in the enum function. then prints accordingly.
/// </summary>
/// <param name="output"> takes ostream obkject by reference</param>
/// <param name="card"> Takes Cards object by reference</param>
/// <returns> returns output </returns>
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

/// <summary>
/// stream insertion operator for Deck class: 
/// loops through the deck and for every pointer to a Card object it ouptuts it 
/// </summary>
/// <param name="output">takes ostream object by reference</param>
/// <param name="deck"> Takes Cards object by reference</param>
/// <returns> returns output </returns>
ostream& operator << (ostream& output, const Deck& deck)
{
	for (Cards* c : deck.cards_list)
	{

		output << *c;
	}
	return output;
}


/// <summary>
/// Hand class constructor
/// </summary>
Hand::Hand() // hand default constuructor 
{

}

/// <summary>
/// Hand Class copy constructor 
/// functions the exact same way as the Deck class copy constructor
/// </summary>
/// <param name="orig">  takes a constant Hand object by reference</param>
Hand::Hand(const Hand& orig) : hand(orig.hand.size()) // hand copy contrustor for vector
{
	for (int i = 0; i < orig.hand.size(); ++i)
		hand[i] = new Cards(*orig.hand[i]);
}

/// <summary>
/// Hand class destructor:
/// functions exactly like the Deck destructor
/// </summary>
Hand :: ~Hand() // hand destructor
{
	for (int i = 0; i < hand.size(); i++)
	{
		delete hand[i];
		hand[i] = NULL;
	}
}

/// <summary>
/// Hand class assignment operator
/// </summary>
/// <param name="h">takes a constant Hand object by reference</param>
/// <returns></returns>
Hand& Hand::operator= (const Hand& h)
{
	hand = h.hand;
	return *this;
}


/// <summary>
/// stream insertion operator for Hand class: 
/// loops through the players Hand and for every pointer to a Card object it ouptuts it 
/// </summary>
/// <param name="output">takes ostream object by reference</param>
/// <param name="hand">takes a constant Hand object by reference</param>
/// <returns></returns>
ostream& operator << (ostream& output, const Hand& hand)
{
	for (Cards* c : hand.hand)
	{
		output << *c;
	}
	return output;
}



/// <summary>
/// fills the Deck with Cards
/// for every type of Card a new Crad object pointer is created and and type is inserted into the new card 
///  each Crad is then pushed into the card_list vector
/// the Deck_multipler is used to create a bigger deck size having equal amount of every card type
/// deck size will always be a multiple of 5 
/// </summary>
/// <param name="deck">takes a constant Deck object by reference</param>
/// <param name="card">takes a constant Card object by reference</param>
void Deck::initialize(Deck& deck, Cards& card) 
{
	for (int i = 0; i < deck.deck_multiplier; ++i) 
	{
		for (int j = 0; j < card.num_of_types; ++j) 
		{
			Cards* card = new Cards();
			card->type = Type(j);
			deck.cards_list.push_back(card);
		}
	}

}


/// <summary>
/// shuffles the Deck so cards are in random order
/// take a random number within the range of the card_list vector size
/// the Card at that spot is pushed into a the new shuffled Vector and erased from Card_list
/// once the shuffled vector is full and card_list is empty each card pushed back into the Card_list in the randomized orderr
/// </summary>
/// <param name="deck">takes a constant Deck object by reference</param>
void Deck::shuffle(Deck& deck)   
{
	// initialize random seed: this is done so that the rand object generates different random numbers on each run 
	srand(time(NULL));

	vector <Cards*> shuffled_Deck;
	while (!deck.cards_list.empty())
	{
		int randomizer = rand() % deck.cards_list.size();
		shuffled_Deck.push_back(deck.cards_list[randomizer]);
		deck.cards_list.erase(deck.cards_list.begin() + randomizer);
	}
	for (Cards* card : shuffled_Deck)
	{
		deck.cards_list.push_back(card);
	}

}



/// <summary>
///  draws from a shuffled card_list (deck) and places in a new vector which is the players hand
/// // the card drawn is always the top card of the deck, which is then erased and placed in the hand
/// </summary>
/// <param name="deck">takes a constant Deck object by reference</param>
/// <param name="h">takes a constant Hand object by reference</param>
void Hand::draw(Deck& deck) 
{
	hand.push_back(deck.cards_list[0]);
	deck.cards_list.erase(deck.cards_list.begin());
}



/// <summary>
/// play fuynction allows a player to play a card from their hand 
/// ask the player which card they would like to play and loops through their hand to find it
/// if found, the card is pushed back to the bottom of the deck and erased from the players hand
/// and order is also made for that card and is placed into the order list
/// note** reinforcement is not a special card therefore will not be placed into the order list
/// if card input is not in the hand, the play function is terminated 
/// </summary>
/// <param name="h">takes a constant Hand object by reference</param>
/// <param name="ol">takes a constant OrderList object by reference</param>
/// <param name="d">takes a constant deck object by reference</param>
void Hand::play(Hand& h, OrderList& ol, Deck& d)
{
	
	bool isValidCard = false;
	while (!isValidCard) {

		std::cout << "This is Your Hand" << std::endl  << h << " which card would you like to play?" << std::endl;
		std::string name;
		std::cin >> name;
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (name == "bomb")
		{
			int counter = 0;
			int initialHandSize = h.hand.size();
			for (Cards* c : h.hand)
			{
			
				if (c->type == Type(0))
				{
					d.cards_list.push_back(c);
					h.hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());\
					std::cout << "Bomb Card has been selected" << std::endl;
					isValidCard = true;
					break;
				}		
				counter++;
			}

			if (counter == initialHandSize)
			{
				std::cout << "sorry your Hand doesnt contain this card" << std::endl;
				return;
			}
	 
			Bomb* b = new Bomb();
			ol.list.push_back(b);
			std::cout << "Bomb has been Placed in the Order List" << std::endl;
		}

		else if (name == "reinforcement")
		{
			int counter = 0;
			int initialHandSize = h.hand.size();
			for (Cards* c : h.hand)
			{
				if (c->type == Type(1))
				{
					d.cards_list.push_back(c);
					h.hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());
					isValidCard = true;
					break;
				}
				counter++;
			}

			if (counter == initialHandSize)
			{
				std::cout << "sorry your Hand doesnt contain this card" << std::endl;
				return;
			}

			std::cout << "Reinforcement has been played, this card is not a special order" << std::endl;
		}

		else if (name == "blockade")
		{
			int counter = 0;
			int initialHandSize = h.hand.size();
			for (Cards* c : h.hand)
			{
				if (c->type == Type(2))
				{
					d.cards_list.push_back(c);
					h.hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());
					isValidCard = true;
					break;
				}
				counter++;
			}
			if (counter == initialHandSize)
			{
				std::cout << "sorry your Hand doesnt contain this card" << std::endl;
				return;
			}
	
			Blockade* bl = new Blockade();
			ol.list.push_back(bl);
			std::cout << "Blockade has been Placed in the Order List" << std::endl;
		}

		else if (name == "airlift")
		{
			int counter = 0;
			int initialHandSize = h.hand.size();
			for (Cards* c : h.hand)
			{
				if (c->type == Type(3))
				{
					d.cards_list.push_back(c);
					h.hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());
					isValidCard = true;
					break;
				}
				counter++;
			}
	
			if (counter == initialHandSize)
			{
				std::cout << "sorry your Hand doesnt contain this card" << std::endl;
				return;
			}

			Airlift* a = new Airlift();
			ol.list.push_back(a);
			std::cout << "Airlift has been Placed in the Order List" << std::endl;
		}
		else if (name == "diplomacy")
		{
			int counter = 0;
			int initialHandSize = h.hand.size();
			for (Cards* c : h.hand)
			{
				if (c->type == Type(4))
				{
					d.cards_list.push_back(c);
					h.hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());
					isValidCard = true;
					break;
				}
				counter++;
			}

			if (counter == initialHandSize)
			{
				std::cout << "sorry your Hand doesnt contain this card" << std::endl;
				return;
			}

			Diplomacy* dp = new Diplomacy();
			ol.list.push_back(dp);
			std::cout << "Diplomacy has been Placed in the Order List" << std::endl;
		}
	}
}








