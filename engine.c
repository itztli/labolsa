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
  
  for(int i; i < market->index_stock;i++){
    price = market->stocks[i].price;
    for(int j; j < market->index_user;j++){

      //if (price <= market->users[j].money){
	//the user have enough money to make a transaction.

      if (askOrderBuy(market->users[j], market->stocks[i])){
	  createrOrder_buy(market, &market->stocks[i], &market->users[j]);
	}

      if (askOrderSell(market->users[j], market->stocks[i])){
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

