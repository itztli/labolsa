#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "market.h"
#include "order.h"
#include "user.h"

//LOG
// BUG1: segmentation fault.
int montecarlo(Market *market){
  float price;
  int r;
  int n_actions,actual_stock;
  float ask,bid;
  int n_buy, n_sell;
  n_buy=0;
  n_sell=0;
  //CREATING BUY/SELL ORDERS
  printf("Creating NEW orders (old %i/%i):\n",market->index_order_buy,market->index_order_sell);  
  //printf("INFO: index_stock=%i\n",market->index_stock);
  for(int i=0; i < market->index_stock; i++){
    price = market->stocks[i].price;
    for(int j=0; j < market->index_user;j++){
      //if (price <= market->users[j].money){
      //the user have enough money to make a transaction.
      if (askOrderBuy(market->users[j], market->stocks[i])){
	createrOrder_buy(market, &market->stocks[i], &market->users[j]);
	n_buy++;
      }
      //printf("INFO: User=%i code=%s\n",j,market->stocks[i].code);
      if (askOrderSell(market->users[j], market->stocks[i])){
	//printf("INFO: User %i wants to sell!\n",j);
	createrOrder_sell(market, &market->stocks[i], &market->users[j]);
	n_sell++;
      }
      //}
    } //j
  } //i

  printf("#Buy Orders:%i\tSell Orders:%i.\n",n_buy,n_sell);

  // CLEAR BEGIN_FLAGS
  
  // EXECUTINGS ORDERS
  //printf("#Executing orders...\n");
  for (int i=0; i < market->index_order_buy; i++){
    bid = market->orders_buy[i].bid;
    
    //printf("Looking for sell [%i/%s/%i/%f]...",market->orders_buy[i].user->index ,market->orders_buy[i].stock->code,market->orders_buy[i].n_actions  ,bid);
    for (int j=0; j < market->index_order_sell; j++){
      ask = market->orders_sell[j].ask;
      //printf("[%f],",ask);
      if (bid >= ask){
	n_actions = market->orders_buy[i].n_actions;
	if (market->orders_buy[i].n_actions > market->orders_sell[j].n_actions){
	  n_actions = market->orders_sell[j].n_actions;
	}
	//printf("<%i/%s/%i>\n",market->orders_buy[i].user->index,market->orders_buy[i].stock->code, n_actions);
	//update the n_actions in the order
	market->orders_buy[i].n_actions -= n_actions;
	//Update the money in order from the user i
	market->orders_buy[i].user->money_in_orders -= n_actions*bid;
	//transfering money to seller
	market->orders_sell[j].user->money += n_actions*bid;
	//quit the stock from the seller
	//printf("A:%s\n",market->orders_buy[i].stock->code);
	//BUG1 actual_stock = get(*market->orders_sell[j].user, market->orders_buy[i].stock[i].code);
	actual_stock = get(*market->orders_sell[j].user, market->orders_buy[i].stock->code);
	//printf("B\n");
	//BUG1 insert(market->orders_sell[j].user,market->orders_buy[i].stock[i].code,actual_stock-n_actions);
	insert(market->orders_sell[j].user,market->orders_buy[i].stock->code,actual_stock-n_actions);
	// transfer the stock to the buyer
	//BUG1 actual_stock = get(*market->orders_buy[i].user, market->orders_buy[i].stock[i].code);
	actual_stock = get(*market->orders_buy[i].user, market->orders_buy[i].stock->code);
	//BUG1 insert(market->orders_buy[i].user,market->orders_buy[i].stock[i].code,actual_stock+n_actions);
	insert(market->orders_buy[i].user,market->orders_buy[i].stock->code,actual_stock+n_actions);
	// update the price of the stock
	if (market->orders_sell[j].stock->begin_flag == 1){
	  market->orders_sell[j].stock->begin = bid;
	  market->orders_sell[j].stock->begin_flag = 0;
	}
	market->orders_buy[i].stock->price = (market->orders_buy[i].stock->price + bid)/2.0;


	if (bid < market->orders_buy[i].stock->min){
	  market->orders_buy[i].stock->min = bid;
	}

	if (bid > market->orders_buy[i].stock->max){
	  market->orders_buy[i].stock->max = bid;
	}

	market->orders_buy[i].stock->end = bid;
	
      } // if bid >= ask
      
      if (market->orders_buy[i].n_actions == 0){break;}

    }
  }
  //delete all the transactions in 0:
  orders_trash_collector(market);
  
  return 1;
}

int printJapaneseCandle(Market *market){
  //printf("Stocks:\n");
  printf("CODE\tMIN\t\tBEGIN\t\tAVERAGE\t\tEND\t\tMAX\n");
  for(int i=0; i < market->index_stock; i++){
    printf("%s\t%f\t%f\t%f\t%f\t%f\n",market->stocks[i].code,market->stocks[i].min,market->stocks[i].begin,market->stocks[i].price,market->stocks[i].end,market->stocks[i].max);
  }

  return 1;
}

