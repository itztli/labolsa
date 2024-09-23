#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "market.h"
#include "user.h"
#include "order.h"

Market *newMarket(char name[], int nstocks, int nusers, int norders){
  Market *market; 
  market = malloc(sizeof(Market));
  strcpy(market->name, name);
  market->nstocks = nstocks;
  market->nusers = nusers;
  market->norders = norders;
  market->stocks = malloc(sizeof(Stock)*nstocks);
  market->users = malloc(sizeof(User)*nusers);
  market->orders_buy = malloc(sizeof(Order)*norders);
  market->orders_sell = malloc(sizeof(Order)*norders);
  market->index_stock = 0;
  market->index_user = 0;
  market->index_order_buy = 0;
  market->index_order_sell = 0;
  return market;
}

int addStock(Market *market, Stock stock){
  market->stocks[market->index_stock] = stock;
  market->index_stock++;
  return 1;
}

int addUser(Market *market, User user){
  market->users[market->index_user] = user;
  market->index_user++;
  return 1;
}

void printMarket(Market *market){
  printf("Stocks:\n");
  for(int i=0; i < market->index_stock; i++){
    printf("%s\n",market->stocks[i].code);
  }
  printf("Users:\n");
  for(int i=0; i < market->index_user; i++){
    printf("%i %f\n",market->users[i].index, market->users[i].money);
  }
}

int closeMarket(Market *market){
  free(market->stocks);
  free(market->users);
  free(market->orders_buy);
  free(market->orders_sell);
  free(market);
  return 1;
}
