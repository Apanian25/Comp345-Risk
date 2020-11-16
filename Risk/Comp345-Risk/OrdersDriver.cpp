#include "Orders.h"
#include "Player.h"
#include "Map.h"
//#include "GameEngine.h"
#include <iostream>



void assignment1Test();
void assignment2Test();

namespace OrdersDriver {

	

	int main() {
		
		//assignment1Test();
		assignment2Test();
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
	Player* player1 = new Player(100, "John");
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

	john1->numberOfArmies = 10;
	mark1->numberOfArmies = 4;
	bob1->numberOfArmies = 30;

	Deploy* deploy = new Deploy(player1,john1,10);
	Deploy* deploy2 = new Deploy(player2,mark2,10);

	if (deploy->validate())
	{
		cout << "John1 numbert of armies : " << john1->numberOfArmies << endl;
		std::cout << " deploy is valid" << std::endl;
		deploy->execute();
		cout << "John1 numbert of armies : " << john1->numberOfArmies << endl;
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
	cout << "----------------------------------------------------------------------------------" << endl;

	Advance* advance = new Advance(player1,john1,mark1,6);
	Advance* advance2 = new Advance(player1,john1,mark2,3);

	if (advance->validate())
	{
		cout << "John1 number of armies : " << john1->numberOfArmies << endl;
		cout <<"mark1 number of armies : " <<  mark1->numberOfArmies << endl;
		cout << "mark1 owner (by ID) : " << mark1->ownedBy;
		std::cout << " advance is valid" << std::endl;
		advance->execute();
		cout << "John1 number of armies : " << john1->numberOfArmies << endl;
		cout << "mark1 number of armies : " << mark1->numberOfArmies << endl;
		cout << "mark1 owner (by ID) : " << mark1->ownedBy;
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
	}




	cout << "----------------------------------------------------------------------------------" << endl;
	Airlift* airlift1 = new Airlift(player1,john1,john2,2);
	Airlift* airlift2 = new Airlift(player3,john1,mark3,2);
	if (airlift1->validate())
	{
		cout << "John1 number of armies : " << john1->numberOfArmies << endl;
		cout << "John2 number of armies : " << john2->numberOfArmies << endl;
		std::cout << " airlift is valid" << std::endl;
		airlift1->execute();
		cout << "John1 number of armies : " << john1->numberOfArmies << endl;
		cout << "John2 number of armies : " << john2->numberOfArmies << endl;
	}
	else
	{
		std::cout << " airlift is Invalid" << std::endl;
		airlift1->execute();
	}


	if (airlift2->validate())
	{
		std::cout << " airlift2 is valid" << std::endl;
		airlift2->execute();
		 
	}
	else
	{
		std::cout << " airlift2 is Invalid" << std::endl;
		airlift2->execute();
	}

	cout << "----------------------------------------------------------------------------------" << endl;
	Bomb* bomb = new Bomb(player1,bob1);
	Bomb* bomb2 = new Bomb(player1,john2);

	if (bomb->validate())
	{
		cout << "bob1 number of armies :  " <<  bob1->numberOfArmies << endl;
		std::cout << " bomb is valid" << std::endl;
		bomb->execute();
		cout << "bob1 number of armies : " << bob1->numberOfArmies << endl;
	}
	else
	{
		std::cout << " bomb is Invalid" << std::endl;
		bomb->execute();
	}


	if (bomb2->validate())
	{
		std::cout << " bomb2 is valid" << std::endl;
		bomb2->execute();

	}
	else
	{
		std::cout << " bomb2 is Invalid" << std::endl;
		bomb2->execute();
	}
	cout << "----------------------------------------------------------------------------------" << endl;
	Diplomacy* diplomacy = new Diplomacy(player1,player2);
	Diplomacy* diplomacy2 = new Diplomacy(player1,player1);
	Advance* advance3 = new Advance(player1, john1, bob1, 3);

	if (diplomacy->validate())
	{

		std::cout << " diplomacy is valid" << std::endl;
		diplomacy->execute();
		advance3->execute();

	}
	else
	{
		std::cout << " diplomacy is Invalid" << std::endl;
		diplomacy->execute();
	}


	if (diplomacy2->validate())
	{
		std::cout << " diplomacy2 is valid" << std::endl;
		diplomacy2->execute();


	}
	else
	{
		std::cout << " diplomacy2 is Invalid" << std::endl;
		diplomacy2->execute();
	}
	cout << "----------------------------------------------------------------------------------" << endl;
	Blockade* blockade = new Blockade(player1, john1);
	Blockade* blockade2 = new Blockade(player1, mark1);

	if (blockade->validate())
	{
		cout << "John1 number of armies : " << john1->numberOfArmies << endl;
		cout << "john1 owned (id) : " << john1->ownedBy << endl;
		std::cout << " blockade is valid" << std::endl;
		blockade->execute();
		cout << "John1 number of armies : " << john1->numberOfArmies << endl;
		cout << "john1 owned (id) : " << john1->ownedBy << endl;
		

	}
	else
	{
		std::cout << " blockade is Invalid" << std::endl;
		blockade->execute();
	}


	if (blockade2->validate())
	{
		std::cout << " blockade2 is valid" << std::endl;
		blockade2->execute();


	}
	else
	{
		std::cout << " blockade2 is Invalid" << std::endl;
		blockade2->execute();
	}




	delete player1;
	player1 = NULL;
	delete player2;
	player2 = NULL;
	delete player3;
	player3 = NULL;

	delete john1;
	john1 = NULL;
	delete john2;
	john2 = NULL;
	delete bob1;
	bob1 = NULL;
	delete bob2;
	bob2 = NULL;
	delete mark1;
	mark1 = NULL;
	delete mark2;

	delete mark3;
	
	delete deploy;
	delete deploy2;
	delete advance;
	delete advance2;
	delete advance3;
	delete bomb;
	delete bomb2;
	delete airlift1;
	delete airlift2;
	delete blockade;
	delete blockade2;
	delete diplomacy;
	delete diplomacy2;



}
