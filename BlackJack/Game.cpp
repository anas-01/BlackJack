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

	cout << endl;
	cout << "Welcome to BlackJack " << endl;
	cout << "It's you vs the computer!" << endl << endl;
	cout << "The rules of Blackjack: first to either hit 21 or get the closest to wins!" << endl;
	cout << "Good Luck!" << endl << endl;

	std::chrono::seconds dura(3);
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

	//Implementation of the 1 or 11 Ace rule
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
			if (input == 1) {
				cout << "You decided to Hit! " << endl << endl;
			}

			if (input == 0) {
				cout << "You decided to Stay" << endl << endl;
			}

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

//Prints the hand of the player
void GameManager::printHand(Player* player)
{
	Player* p = player;
	cout << player->name << "'s cards:" << endl;
	cout << endl;
	for (size_t i = 0; i < p->hand->size(); i++)
	{

		Card* c = (*p->hand)[i];
		cout << c->Face << " of " << c->Suit << " | " << c->cardValue << endl;

		std::chrono::seconds dura(3);
		std::this_thread::sleep_for(dura);

	}
}

string GameManager::getPlayerName()
{
	Menu();

	string name;
	cout << "Enter your name: " << endl;
	cin >> name;

	cout << endl;
	cout << "Welcome " << name << endl << endl;
	cout << "Game is loading..." << endl << endl;
	std::chrono::seconds dura(2);
	std::this_thread::sleep_for(dura);

	cout << "Your cards will be presented to you shortly..." << endl;

	std::chrono::seconds dur(5);
	std::this_thread::sleep_for(dur);
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
		cout << "You went bust!" << endl;
		cout << "You lost!" << endl;
		return;
	}

	if (dScore > 21 || pScore == 21)
	{
		cout << "Dealer went bust!" << endl;
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
		cout << "You Hit 21, You Won! " << endl;
		return true;
	}

	if (ds == 21)
	{
		cout << "Dealer hit 21!" << endl;
		cout << "You Lost!" << endl;
		return true;
	}

	return false;
}