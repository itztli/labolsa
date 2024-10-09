#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "market.h"
#include "order.h"
#include "user.h"

int montecarlo(Market *market){
  float price;
  int r;
  int n_actions,actual_stock;
  float ask,bid;

  //CREATING BUY/SELL ORDERS
  printf("Creating orders.\n");  
  //printf("INFO: index_stock=%i\n",market->index_stock);
  for(int i=0; i < market->index_stock; i++){
    price = market->stocks[i].price;
    for(int j=0; j < market->index_user;j++){
      //if (price <= market->users[j].money){
      //the user have enough money to make a transaction.
      if (askOrderBuy(market->users[j], market->stocks[i])){
	createrOrder_buy(market, &market->stocks[i], &market->users[j]);
      }
      //printf("INFO: User=%i code=%s\n",j,market->stocks[i].code);
      if (askOrderSell(market->users[j], market->stocks[i])){
	//printf("INFO: User %i wants to sell!\n",j);
	createrOrder_sell(market, &market->stocks[i], &market->users[j]);
	}
      
      //}
    } //j
  } //i


  
  // EXECUTINGS ORDERS
  printf("INFO200: Executing orders.\n");
  for (int i=0; i < market->index_order_buy; i++){
    bid = market->orders_buy[i].bid;
    for (int j=0; j < market->index_order_sell; j++){
      ask = market->orders_sell[j].ask;
      if (bid >= ask){
	n_actions = market->orders_buy[i].n_actions;
	if (market->orders_buy[i].n_actions > market->orders_sell[j].n_actions){
	  n_actions = market->orders_sell[j].n_actions;
	}
	//update the n_actions in the order
	market->orders_buy[i].n_actions -= n_actions;
	//Update the money in order from the user i
	market->orders_buy[i].user->money_in_orders -= n_actions*bid;
	//transfering money to seller
	market->orders_sell[j].user->money += n_actions*bid;
	//quit the stock from the seller
	actual_stock = get(*market->orders_sell[j].user, market->orders_buy[i].stock[i].code);
	insert(market->orders_sell[j].user,market->orders_buy[i].stock[i].code,actual_stock-n_actions);
	// transfer the stock to the buyer
	actual_stock = get(*market->orders_buy[i].user, market->orders_buy[i].stock[i].code);
	insert(market->orders_buy[i].user,market->orders_buy[i].stock[i].code,actual_stock+n_actions);
	// update the price of the stock
	market->orders_buy[i].stock->price = (market->orders_buy[i].stock->price + bid)/2.0;

      }
    }
  }
  
  return 1;
}

int printJapaneseCandle(Market *market){
  return 1;
}

