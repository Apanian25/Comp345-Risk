//#include "Player.h"
//#include "Map.h"
//#include "Util.h"
//#include <vector>
//
//void Util::init (std::vector<Player*> p) {
//	players = p;
//}
//
//void Util::updatePlayers(vector<Player*> p) {
//	players = p;
//}
//
///// <summary>
///// 
///// </summary>
///// <param name="id">Player id</param>
///// <param name="territory">Territory to remove</param>
//void Util::removeTerritory(int id, Territory* territory) {
//	for (Player* p : players)
//	{
//		if (p->id == id) {
//			p->territories.erase(std::remove(p->territories.begin(), p->territories.end(), territory), p->territories.end());
//		}
//	}
//}
//
///// <summary>
///// 
///// </summary>
///// <param name="id">Player id</param>
///// <param name="territory">Territory to add</param>
///// <param name="numOfArmies">new number of armies on the territory</param>
//void Util::addTerritory(int id, Territory* territory, int numOfArmies) {
//	for (Player* p : players) {
//		if (p->id = id) {
//			p->territories.push_back(territory);	
//			territory->numberOfArmies = numOfArmies; //update number of armies for the territory
//		}
//	}
//}
//
//void Util::negotiate(int player1ID, int player2ID) {
//	for (Player* p1 : players)
//	{
//		if (p1->id = player1ID)
//		{
//			for (Territory* t : p1->terrToAtk)
//			{
//				if (t->ownedBy == player2ID) {
//					p1->terrToAtk.erase(std::remove(p1->terrToAtk.begin(), p1->terrToAtk.end(), t), p1->terrToAtk.end());
//				}
//			}
//		}
//	}
//	for (Player* p2 : players)
//	{
//		if (p2->id = player2ID)
//		{
//			for (Territory* t : p2->terrToAtk)
//			{
//				if (t->ownedBy == player1ID) {
//					p2->terrToAtk.erase(std::remove(p2->terrToAtk.begin(), p2->terrToAtk.end(), t), p2->terrToAtk.end());
//				}
//			}
//		}
//	}
//	
//}