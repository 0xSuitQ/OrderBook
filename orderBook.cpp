#include "orderBook.h"

void  createOrder(OrderBook &orderBook, Order &newOrder) {
   std::cout << "Enter order details (user_id, amount, price, side (0-buy, 1-sell)): " << std::endl;
   std::cin >> newOrder.user_id >> newOrder.amount >> newOrder.price >> newOrder.side;
}

void  pushOrder(OrderBook &orderBook, Order &newOrder) {
   if (newOrder.amount > 0) {
      if (newOrder.side == 0) {
         orderBook.addBid(newOrder);
      } else {
         orderBook.addAsk(newOrder);
      }
   }
}

void  sortOrderBook(OrderBook &orderBook) {
   orderBook.bids.sort([](Order a, Order b) { return a.price > b.price; });
   orderBook.asks.sort([](Order a, Order b) { return a.price < b.price; });
}

void  calculateBalanceChange(Order &newOrder, Order it, std::vector<BalanceChanges> &balanceChanges, int amount) {
   if (newOrder.side == 0) {
      balanceChanges.push_back({newOrder.user_id, float(amount), "UAH"});
      balanceChanges.push_back({newOrder.user_id, float(-amount) / float(it.price), "USD"});
      balanceChanges.push_back({it.user_id, float(amount) / float(it.price), "USD"});
      balanceChanges.push_back({it.user_id, float(-amount), "UAH"});
   } else {
      balanceChanges.push_back({newOrder.user_id, float(-amount), "UAH"});
      balanceChanges.push_back({newOrder.user_id, float(amount) / float(it.price), "USD"});
      balanceChanges.push_back({it.user_id, float(amount), "UAH"});
      balanceChanges.push_back({it.user_id, float(-amount) / float(it.price), "USD"});
   }
}

void  printBalanceChange(std::vector<BalanceChanges>& balanceChanges) {
   std::cout << "Balance Changes:" << std::endl;
   for (BalanceChanges& change : balanceChanges) {
      std::cout << "User ID: " << change.user_id << ", Value: " << (change.value > 0 ? "+" : "") \
      << change.value << ", Currency: " << change.currency << std::endl;
   }
}

void  executeOrder(OrderBook &orderBook, Order &newOrder, std::vector<BalanceChanges> &balanceChanges) {
   if (newOrder.side == 0) {
      list<Order>::iterator it = orderBook.asks.begin();
         while (it != orderBook.asks.end() && newOrder.amount > 0 && newOrder.price >= it->price) {
            int tradeAmount = std::min(newOrder.amount, it->amount); // Amount for this trade
            newOrder.amount -= tradeAmount;
            it->amount -= tradeAmount;
            calculateBalanceChange(newOrder, *it, balanceChanges, tradeAmount);
            if (it->amount == 0) {
               it = orderBook.asks.erase(it); // Removing fully executed ask
               std::next(it);
            } else {
               break ;
            }
         }
   } else {
      list<Order>::iterator it = orderBook.bids.begin();
         while (it != orderBook.bids.end() && newOrder.amount > 0 && newOrder.price <= it->price) {
            int tradeAmount = std::min(newOrder.amount, it->amount); // Amount for this trade
            newOrder.amount -= tradeAmount;
            it->amount -= tradeAmount;
            calculateBalanceChange(newOrder, *it, balanceChanges, tradeAmount);
            if (it->amount == 0) {
               it = orderBook.bids.erase(it); // Removing fully executed bid
               std::next(it);
            } else {
               break ;
            }
         }
   }
   printBalanceChange(balanceChanges);
}

int main() {
   OrderBook   orderBook;
   char        choice;
   do {
      Order newOrder;
      std::vector<BalanceChanges> balanceChanges;
      createOrder(orderBook, newOrder);
      executeOrder(orderBook, newOrder, balanceChanges);
      pushOrder(orderBook, newOrder);
      sortOrderBook(orderBook);
      orderBook.print();
      std::cout << "Do you want to enter another order? (y/n): " << std::endl;
      std::cin >> choice;
   } while (tolower(choice) == 'y');

   return 0;
}
/*
 Test input:

 1 4000 39 0
 2 5000 40 0
 3 3000 38 0
 4 2000 41 1
 5 1000 42 1
 6 6000 37 1
*/