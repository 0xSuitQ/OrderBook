# OrderBook

## Task

Orderbook is a component used for trading various assets, including currencies (USD, EUR, UAH), cryptocurrencies (BTC, ETH), and more. The task is to implement a digital order book for two assets: USD and UAH.

Orderbook allows you to exchange two assets:
- Base: the asset traded in this orderbook (UAH in our case).
- Quote: the asset in which the price for the base asset is quoted (USD in our case).

To trade, you need to create an Order and put it into the orderbook. An Order contains the following information:
- User: the person who trades an asset.
- Amount: the amount of UAH to sell or buy.
- Price: the price for 1 UAH in USD. The total price will be the amount * price.
- Side: either sell or buy, specifying if you want to buy UAH at the provided price or sell.

Orderbook stores orders in two different lists:
- Sell orders: for people who want to sell UAH. This list is sorted by price from the lowest price to the highest.
- Buy orders: for people who want to buy UAH. This list is sorted by price from highest to lowest.

The top of the book is where you'll find the highest bid and lowest ask prices. A match occurs when the top sell price is less than or equal to the top buy price. In this case, the person from the sell-side automatically sells UAH and the person from the buy-side automatically buys UAH.

## How to run

1. Run the program by typing `./orderBook`.
2. Provide arguments in one line: `[user_id] [amount] [price] [side (0-buy, 1-sell)]` and press Enter.
3. If you wish to add a new order, enter 'y'. Enter any other letter to stop the program.
4. You will be able to see the order book and changes in balance if the order was fulfilled.


Approximate amount of time spent on the task: 5h.
