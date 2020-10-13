#include <iostream>
#include "Cards.h"
#include "Orders.h"
#include <vector> 

namespace CardsDriver {
	int main() {
		std::cout << "CardsDriver" << std::endl;

		Cards* card = new Cards();
		Deck* My_Deck = new Deck();
		OrderList* ol = new OrderList();
		Hand* H1 = new Hand();
		Hand* H2 = new Hand();

		std::cout << "-----------------Initial Deck---------------------" << std::endl;
		My_Deck->initialize(*My_Deck, *card);
		cout << *My_Deck;
		
		std::cout << "------------------shuffled Deck-------------------------" << std::endl;
		My_Deck->shuffle(*My_Deck);
		My_Deck->shuffle(*My_Deck);
		cout << *My_Deck;
		
		
		for (int i = 0; i < 3; i++)
		{
			H1->draw(*My_Deck, *H1);
			H2->draw(*My_Deck, *H2);
		}
		
		std::cout << " -----------------------Hand1-------------------------------" << std::endl;
		cout << *H1;
		

		std::cout << " -----------------------Hand2-------------------------------" << std::endl;
		cout << *H2;
		

		std::cout << " ----------------------Deck View after Cards Drawn-----------------------------" << std::endl;
		cout << *My_Deck;
		
		for (int i = 0; i < 3; i++)
		{
			std::cout << " -----------------------Play Method Called-------------------------------" << std::endl;
			H1->play(*H1, *ol, *My_Deck);
			
		}
		std::cout << " -----------------------Hand view after play methods-------------------------------" << std::endl;
		cout << *H1;


		std::cout << "----------------------------- order list after all cards are played-----------------------------" << std::endl;
		for (int i = 0; i < ol->list.size(); i++)
		{
			std::cout << *(ol->list[i]) << std::endl;
		}
		
		
		std::cout << " ----------------------Deck View after Play function-----------------------------" << std::endl;
		cout << *My_Deck;
		

		return 1;
	}
}