#pragma once
#include "Player.h"
#include "Deck.h"
#include <vector>

using std::vector;

class GameManager
{
private:

	void drawCard(Player* playerWhoDraws, vector<Card*>* deckToDrawFrom, int timesToDraw);
	void playBlackjack(Player* player, Player* dealer, Deck* d);
	void printCard(vector<Card*>* cardPile, int i);
	bool checkInstantWin(int playerS, int dealerS);
	void checkWin(int playerS, int dealerS);
	void printHand(Player* player);
	int totalScore(Player* player);
	void displayCurrent();
	int getHitOrStand();
	string getPlayerName();
	void Menu();

public:

	GameManager();
	~GameManager();

};

