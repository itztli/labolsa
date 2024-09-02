#ifndef MARKET_H
#define MARKET_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stock.h"
  
  typedef struct{
    char name[8];
    int nstocks; // total stocks
    int nusers;  // total users
    int index;
    Stock *stocks;
  }Market;

  Market *newMarket(char name[], int nstocks, int nusers);

  int addStock(Market *market, Stock stock);

  void printMarket(Market *market);
  
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* MARKET_H */
