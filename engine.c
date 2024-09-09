#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "market.h"
#include "order.h"

int montecarlo(Market *market){
  float price;
  int r;
  int n_actions;
  float ask,bid;
  
  srand(time(NULL));
  
  for(int i; i < market->index_stock;i++){
    price = market->stocks[i].price;
    for(int j; j < market->index_user;j++){
      if (price <= market->users[j].money){
	//the user have enough money to make a transaction.
	r = rand();
	if (r%2 == 0){
	  //run in the market
	  n_actions = 0;
	  bid = 0.0;
	  createrOrder_buy(market, &market->stocks[i],&market->users[j],n_actions,bid);
	}else{
	  //pass

	  
	}
      }
    }

  }
  return 1;
}

int printJapaneseCandle(Market *market){
  return 1;
}

