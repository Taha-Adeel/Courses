#include "auction.h"
#include <cmath>
#include <stdlib.h>
#include <map>

AuctionHouse::AuctionHouse(){}

AuctionHouse& AuctionHouse::getAuctionHouse(){
	static AuctionHouse instance;

	return instance;
}

int AuctionHouse::minBidThreshold(Item& item){
	int minBid = floor((100.f/(100-m_commission)*item.price)+ 1);
	item.price = minBid;
	return minBid;
}

void AuctionHouse::displayItem(Item& item){
	for(auto& bidder: m_pBidders){
		bidder->notify(item);
	}
}

void AuctionHouse::checkBids(int bid, Item _item, bool reset = false){
	static int maxBid{0};
	// static Item item = _item;
	if(reset)	maxBid = 0;

	if(bid)
	maxBid = std::max(bid, maxBid);
}

int Bidder::bidUpperLim(Item& item){
	// static std::map<Item, int> bidUpperlimits;
	// if(bidUpperlimits.find(item)!= bidUpperlimits.end())
	// 	bidUpperlimits[item] = (((rand()%100)/100.f)+1)*item.price;

	// return bidUpperlimits[item];
}

void Bidder::notify(Item& item){
	int rand = rand()%100;
	if(rand <= m_interest_in_items && item.price <= std::min(m_budget, bidUpperLim(item))
		bid(item);
}

void Bidder::bid(Item& item){
	int bidValue = item.price + ((rand()%10)/100 * m_budget);
	AuctionHouse::getAuctionHouse().checkBids(bidValue);
}