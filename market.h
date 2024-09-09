#ifndef MARKET_H
#define MARKET_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stock.h"
#include "user.h"
  //#include "order.h"

  struct Order;
  
  typedef struct{
    char name[8];
    int nstocks; // Maximum stocks
    int nusers;  // Maximum users
    int index_stock; //total stocks
    int index_user; // total user
    int index_order; //total of orders by iteration
    Stock *stocks;
    User *users;
    struct Order *orders;
  }Market;

  Market *newMarket(char name[], int nstocks, int nusers);

  int addStock(Market *market, Stock stock);
  
  int addUser(Market *market, User user);

  void printMarket(Market *market);

  int closeMarket(Market *market);
  
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* MARKET_H */
