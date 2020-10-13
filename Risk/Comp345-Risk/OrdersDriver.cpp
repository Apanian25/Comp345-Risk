#include "Orders.h"
#include <iostream>

namespace OrdersDriver {

	int main() {
		OrderList *listoforders;

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

		return 0;
	
	}
}