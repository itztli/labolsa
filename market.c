#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "market.h"

Market *newMarket(char name[], int nstocks, int nusers){
  Market *market; 
  market = malloc(sizeof(Market));
  strcpy(market->name, name);
  market->nstocks = nstocks;
  market->nusers = nusers;
  market->stocks = malloc(sizeof(Stock)*nstocks);
  market->index = 0;
  return market;
}

int addStock(Market *market, Stock stock){
  market->stocks[market->index] = stock;
  market->index++;
  return 1;
}

void printMarket(Market *market){
  for(int i=0; i < market->index; i++){
    printf("%s\n",market->stocks[i].code);
  }
}
