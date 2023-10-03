/* All selling prices, percentages, etc have been assumed to be integers. This is a
	reasonable assumption as usually in auctions, the bidding prices, bid increments
	,etc are multiples of 10(i.e integers). This helps us reduce the complexity by
	eliminating floating point assertions, comparisions, etc*/
#ifndef AUCTION_H
#define AUCTION_H

#include <string>
#include <vector>
#include <memory>

/**
 * @brief Container representing our item. Has members item name and its price.
 * 
 */
struct Item{
	std::string name;
	int price;
	bool operator==(Item i){
		return (name==i.name && price==i.price);
	}
};

class Seller;
class Bidder;

/**
 * @brief Main class that conducts the auction.
 * 
 * AuctionHouse is a singleton, and non-copyable and non-moveable
 */
class AuctionHouse{
private:
	// private member variables
	/*AuctionHouse maintains a list of sellers and bidders. We use smart pointers to 
		avoid memory leaks */
	std::vector<std::unique_ptr<Seller>> m_pSellers;
	std::vector<std::unique_ptr<Bidder>> m_pBidders;
	/*We store the commission the AuctionHouse take and the maximum number of rounds
		an item is openned for bidding, and the AuctionHouse earnings in the following
		variables.*/
	int m_commission;
	int m_max_rounds;
	int m_earnings;

	// private member function
	/**
	 * @brief Finds out minimum initial bidding price of an item based on the commission
	 * and sellers minimum requirement.
	 * 
	 * @param item
	 * @return int The minimum initial bidding price
	 */
	int minBidThreshold(Item& item);

	void initAuction();

	// private constructor
	AuctionHouse();

public:
	// public member variables
	int m_min_bid_margin;/*the minimum bidding margin (in percentage)*/

	//public member functions
	/**
	 * @brief Get the Auction House object.
	 * 
	 * @return AuctionHouse& 
	 */
	static AuctionHouse& getAuctionHouse();
	/*Deleting the copy and move constructors and assignments*/
	AuctionHouse& operator=(const AuctionHouse&) = delete;
    AuctionHouse(const AuctionHouse&) = delete;
	AuctionHouse& operator=(AuctionHouse&&) = delete;
    AuctionHouse(AuctionHouse&&) = delete;
	
	/**
	 * @brief Conducts our simulation
	 * 
	 * For each item from each seller, we display the item, check the bids until it is
	 * sold or m_max_rounds have taken place, displaying the max bid each time to the 
	 * bidders, and finally sell the item to the maximum bidder. 
	 */
	void beginAuction();
private:
	// private member variables
	/**
	 * @brief 
	 * 
	 */
	void displayItem(Item& item);
	void checkBids(int, Item, bool);
	void displayMaxBid();//notify bidders
	void sellItem();//notify bidder and seller
};

/**
 * @brief Seller contains a list of items to sell
 * 
 */
class Seller{
private:
	int m_earnings;/*The earnings of the seller*/
public:
	std::vector<Item> m_items;/*List of items on sale*/

	Seller();
	/**
	 * @brief Adds items which are on sale
	 * 
	 * @return true Succesfully added item
	 * @return false Otherwise
	 */
	bool addItem(Item& item);
};

/**
 * @brief Buys items from the auction house
 * 
 */
class Bidder{
public:
	int m_budget;/*Bidders budget*/
	int m_interest_in_items;/*A percentage probability value that represents his probability
	to bid in a round*/
	std::vector<Item> m_boughtItems;

	void notify(Item& item);
	void bid(Item& item);
	/**
	 * @brief Returns the maximum value he is willing to bid on an item
	 * 
	 * @param item 
	 * @return int 
	 */
	int bidUpperLim(Item& item);
	Bidder();
};

#endif