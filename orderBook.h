#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <list>
#include <iterator>
#include <iomanip>
using namespace std;

typedef struct s_balanceChanges {
	int				user_id;
	float 			value;
	std::string		currency;
} BalanceChanges;

typedef struct s_order {
	int 	user_id;
	int		amount;
	int 	price;
	bool	side; // 0 - buy, 1 - sell

	bool operator==(const s_order &rhs) const {
		return user_id == rhs.user_id && amount == rhs.amount && price == rhs.price && side == rhs.side;
	}
} Order;

typedef struct OrderBook {
	std::list<Order> bids;
	std::list<Order> asks;

	void addBid(Order order) {
		bids.push_back(order);
	}
	void addAsk(Order order) {
		asks.push_back(order);
	}
	void print() {
		std::cout << "Price(USD):\tAmount(UAH):" << std::endl;
		std::cout << "Ask:" << std::endl;
		for (std::reverse_iterator<std::list<Order>::iterator> it = asks.rbegin(); it != asks.rend(); ++it) {
  			std::cout << it->price << "\t\t" << it->amount << "\n";
		}
		std::cout << std::endl;
		std::cout << "Bid: " << std::endl;
		for (Order bid : bids) {
			std::cout << bid.price << "\t\t" << bid.amount << "\n";
		}
		std::cout << std::endl;
	}
} OrderBook;

#endif