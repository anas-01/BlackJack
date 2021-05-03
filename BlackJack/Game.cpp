#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include <string>
#include <vector>
#include <time.h>
#include <iostream>
#include <chrono>
#include <thread>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

Deck* deck;
Player* player;
Player* dealer;
string dealerName = "Dealer";
string playerName = "Player";
vector<Card*>* dealerHand;

GameManager::GameManager()
{
	Deck* deck = new Deck();
	vector<Card*>* playerHand = new vector<Card*>();
	vector<Card*>* dealerHand = new vector<Card*>();

	player = new Player(getPlayerName(), playerHand);
	dealer = new Player(dealerName, dealerHand);

	playBlackjack(player, dealer, deck);
}

void GameManager::Menu() {

	cout << "Welcome to BlackJack " << endl;
	cout << "It's you vs the computer!" << endl << endl;

	std::chrono::seconds dura(5);
	std::this_thread::sleep_for(dura);
}

//Runs the game 
void GameManager::playBlackjack(Player* player, Player* dealer, Deck* d)
{
	Deck* deck = d;
	vector<Card*>* cardPile = deck->get_cards();

	// First draw
	drawCard(player, cardPile, 2);
	drawCard(dealer, cardPile, 2);

	displayCurrent();

	//Win Conditions
	while (true)
	{
		int ps = totalScore(player);
		//int ps = totalScore(player);
		int ds = totalScore(dealer);

		if (checkInstantWin(ps, ds) == true)
		{
			break;
		}

		int input = getHitOrStand();
		//Hit
		if (input == 1)
		{
			drawCard(player, cardPile, 1);
			displayCurrent();

			if (totalScore(player) > 21)
			{
				cout << "You lost!" << endl;
				break;
			}
		}
		//Stick
		if (input == 0)
		{
			while (totalScore(dealer) < 17)
			{
				drawCard(dealer, cardPile, 1);
			}

			displayCurrent();

			int ps = totalScore(player);
			int ds = totalScore(dealer);

			checkWin(ps, ds);

			break;
		}
	}
}

//Displays current scores
void GameManager::displayCurrent()
{
	printHand(player);
	cout << "Total Score: " << totalScore(player) << endl << endl;

	printHand(dealer);
	cout << "Total Score: " << totalScore(dealer) << endl << endl;
}

//Score of the player
int GameManager::totalScore(Player* player)
{
	Player* p = player;
	int total = 0;
	//Ace is either 1 or 11
	bool aceOver21 = false;
	int numOfAces = 0;
	for (int i = 0; i < p->hand->size(); i++)
	{
		Card* c = (*p->hand)[i];
		if (c->cardValue == 11)
		{
			numOfAces += 1;
		}
		total += c->cardValue;
	}

	//Implementation of the 11 or 1 Ace rule
	if (total > 21 && numOfAces != 0)
	{
		while (total > 21 && numOfAces != 0)
		{
			total -= 10;
		}
	}

	return total;
}

//Takes a card from a deck and puts it into a players hand
void GameManager::drawCard(Player* playerWhoDraws, vector<Card*>* deckToDrawFrom, int timesToDraw)
{
	int t = timesToDraw;
	vector<Card*>* d = deckToDrawFrom;
	Player* p = playerWhoDraws;

	for (int i = 0; i < t; i++)
	{
		Card* c = d->front();
		p->hand->push_back(c);
		d->erase(d->begin());
	}
}
int GameManager::getHitOrStand()
{
	int input;
	while (true)
	{
		cout << "Enter 1 to hit or 0 to stay" << endl;
		cin >> input;
		cout << endl;

		if (input == 1 || input == 0)
		{
			std::chrono::seconds dura(5);
			std::this_thread::sleep_for(dura);
			return input;
		}
		else
		{
			cout << "Please enter a valid input..." << endl;
		}

	}

}

//mainly for debug
//void GameManager::printCard(vector<Card*>* cardPile, int i)
//{
//	Card* c = (*cardPile)[i];
//	cout << c->Face << " of " << c->Suit << " : Value " << c->cardValue << endl << endl;
//}

//prints the hand of the specified player
void GameManager::printHand(Player* player)
{
	Player* p = player;
	cout << player->name << "'s cards:" << endl;
	cout << endl;
	for (size_t i = 0; i < p->hand->size(); i++)
	{

		Card* c = (*p->hand)[i];
		cout << c->Face << " of " << c->Suit << " | Value " << c->cardValue << endl;

	}
}

string GameManager::getPlayerName()
{
	Menu();

	string name;
	cout << "Enter your name: " << endl;
	cin >> name;

	std::chrono::seconds dura(3);
	std::this_thread::sleep_for(dura);
	cout << endl;
	return name;

}

void GameManager::checkWin(int playerScore, int dealerScore)
{
	int pScore = playerScore;
	int dScore = dealerScore;

	if (pScore == dScore)
	{
		cout << "It's a tie!" << endl;
		return;
	}

	if (pScore > 21 || dScore == 21)
	{
		cout << "You lost!" << endl;
		return;
	}

	if (dScore > 21 || pScore == 21)
	{
		cout << "You won!" << endl;
		return;
	}

	if (dScore < 21 && dScore > pScore)
	{
		cout << "You lost!" << endl;
		return;
	}

	if (pScore < 21 && pScore > dScore)
	{
		cout << "You won!" << endl;
		return;
	}

}

bool GameManager::checkInstantWin(int playerS, int dealerS)
{
	int ps = playerS;
	int ds = dealerS;

	if (ps == 21 && ps == ds)
	{
		cout << "It's a Tie!" << endl;
		return true;
	}

	if (ps == 21)
	{
		cout << "You Hit 21! You Won " << endl;
		return true;
	}

	if (ds == 21)
	{
		cout << "You Lost!" << endl;
		return true;
	}

	return false;
}