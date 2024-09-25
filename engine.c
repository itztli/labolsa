#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "market.h"
#include "order.h"
#include "user.h"

int montecarlo(Market *market){
  float price;
  int r;
  int n_actions;
  float ask,bid;
  
  //printf("INFO: index_stock=%i\n",market->index_stock);
  for(int i=0; i < market->index_stock; i++){
    price = market->stocks[i].price;
    for(int j=0; j < market->index_user;j++){
      //if (price <= market->users[j].money){
      //the user have enough money to make a transaction.
      if (askOrderBuy(market->users[j], market->stocks[i])){
	createrOrder_buy(market, &market->stocks[i], &market->users[j]);
      }
      printf("INFO: User=%i code=%s\n",j,market->stocks[i].code);
      if (askOrderSell(market->users[j], market->stocks[i])){
	//printf("INFO: User %i wants to sell!\n",j);
	createrOrder_sell(market, &market->stocks[i], &market->users[j]);
	}
      
      //}
    }
    
  }
  return 1;
}

int printJapaneseCandle(Market *market){
  return 1;
}

