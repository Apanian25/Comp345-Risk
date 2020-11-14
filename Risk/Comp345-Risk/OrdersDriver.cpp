#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include <iostream>



void assignment1Test();
void assignment2Test();

namespace OrdersDriver {

	

	int main() {
		
		//assignment1Test();
		return 0;
	
	}
}

void assignment1Test()
{
	OrderList* listoforders;

	Deploy* a2 = new Deploy();
	Deploy* a3 = new Deploy();
	Advance* a4 = new Advance();
	Bomb* a5 = new Bomb();
	Diplomacy* a6 = new Diplomacy();
	Blockade* a7 = new Blockade();
	cout << "Creating different Orders and placing them in the OrderList Object" << endl << endl;
	listoforders = new OrderList();

	listoforders->list.push_back(a2);
	listoforders->list.push_back(a3);
	listoforders->list.push_back(a4);
	listoforders->list.push_back(a5);
	listoforders->list.push_back(a6);
	listoforders->list.push_back(a7);

	cout << "The current size of list is " << listoforders->list.size() << endl;
	cout << "Testing the Stream Insertion Operator" << endl << endl;
	for (int i = 0; i < (int)listoforders->list.size(); i++) {
		cout << *listoforders->list.at(i) << endl;
	}

	cout << "Testing the remove() method by removing Order at index 2" << endl << endl;
	listoforders->remove(2);
	cout << "the current size of list after removing is " << listoforders->list.size() << endl;
	for (int i = 0; i < (int)listoforders->list.size(); i++) {
		cout << *listoforders->list.at(i) << endl;
	}

	cout << "Testing the move() method by moving Order of index 2 to index 4" << endl << endl;
	listoforders->move(2, 4);
	for (int i = 0; i < (int)listoforders->list.size(); i++) {
		cout << *listoforders->list.at(i) << endl;
	}

	cout << "Testing the execute() method by executing Orders at index 0 and 3" << endl << endl;

	listoforders->list.at(0)->execute();
	listoforders->list.at(3)->execute();

	for (int i = 0; i < (int)listoforders->list.size(); i++) {
		cout << *listoforders->list.at(i) << endl;
	}


	//ALL pointers get deleted in the listOfOrders Destructor
	delete listoforders;
	listoforders = NULL;
}


void assignment2Test()
{
	/*Player* player1 = new Player(100, "John");
	Player* player2 = new Player(110, "Bob");
	Player* player3 = new Player(120, "Mark");

	Territory* john1 = new Territory("JohnLand", 1, 2);
	Territory* john2 = new Territory("John Isle", 2, 2);
	Territory* bob1 = new Territory("BobLand", 3, 2);
	Territory* bob2 = new Territory("John Isle", 4, 2);
	Territory* mark1 = new Territory("MarkLand", 5, 2);
	Territory* mark2 = new Territory("John Isle", 6, 2);
	Territory* mark3= new Territory("Mark city", 7, 2);
	
	john1->ownedBy = player1->id;
	john2->ownedBy = player1->id;
	bob1->ownedBy = player2->id;
	bob2->ownedBy = player2->id;
	mark1->ownedBy = player3->id;
	mark2->ownedBy = player3->id;
	mark3->ownedBy = player3->id;

	john1->adjacentTerritoriesTo.push_back(bob1);
	john1->adjacentTerritoriesTo.push_back(mark1);
	john1->adjacentTerritoriesTo.push_back(john2);
	bob1->adjacentTerritoriesFrom.push_back(john1);
	mark1->adjacentTerritoriesFrom.push_back(john1);
	john2->adjacentTerritoriesFrom.push_back(john1);


	Deploy* deploy = new Deploy(player1,john1,10);
	Deploy* deploy2 = new Deploy(player2,bob1,10);

	if (deploy->validate())
	{
		std::cout << " deploy is valid" << std::endl;
		deploy->execute();
	}
	else
	{
		std::cout << " deploy is Invalid" << std::endl;
		deploy->execute();
	}
		
	
	if (deploy2->validate())
	{
		std::cout << " deploy2 is valid" << std::endl;
		deploy2->execute();
	}
	else
	{
		std::cout << " deploy2 is Invalid" << std::endl;
		deploy2->execute();
	}
	

	Advance* advance = new Advance(player1,john1,mark1,3);
	Advance* advance2 = new Advance(player1,john1,mark2,3);

	if (advance->validate())
	{
		
		std::cout << " advance is valid" << std::endl;
		advance->execute();
	}
	else
	{
		std::cout << " advance is Invalid" << std::endl;
		advance->execute();
	}


	if (advance2->validate())
	{
		std::cout << " advance2 is valid" << std::endl;
		advance2->execute();
	}
	else
	{
		std::cout << " advance2 is Invalid" << std::endl;
		advance2->execute();
	}*/





	/*Airlift* airlift = new Airlift(player1,source,target,2);
	Airlift* airlift = new Airlift(player1,source,target,2);
	Bomb* bomb = new Bomb(player1,target2);
	Bomb* bomb = new Bomb(player1,target2);
	Diplomacy* diplomacy = new Diplomacy(player1,player2);*/

}