#include <iostream>
#include "Cards.h"
#include <vector> 

namespace CardsDriver {
	int main() {
		std::cout << "CardsDriver" << std::endl;

		Cards* card = new Cards();
		Deck* My_Deck = new Deck();
		My_Deck->Initialize(*My_Deck, *card);
		My_Deck->Print_Deck(*My_Deck);


		std::cout << "-----------shuffle----------------" << std::endl;


		/*My_Deck->shuffle(*My_Deck);
		My_Deck->Print_Deck(*My_Deck);
		std::cout << " ---------------end----------------" << std::endl;*/
		My_Deck->shuffle(*My_Deck);
		My_Deck->Print_Deck(*My_Deck);
		std::cout << " ---------------end----------------" << std::endl;


		Hand* H1 = new Hand();
		Hand* H2 = new Hand();

		H1->Draw(*My_Deck, *H1);
		H1->Print_Hand(*H1);
		std::cout << " ---------------Hand 1 ^----------------" << std::endl;

		H2->Draw(*My_Deck, *H2);
		H2->Print_Hand(*H2);
		std::cout << " --------------Hand 2 ^----------------" << std::endl;



		return 0;
		return 1;
	}
}