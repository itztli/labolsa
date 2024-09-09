#ifndef ORDER_H
#define ORDER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stock.h"
#include "user.h"
  //#include "market.h"

  struct Market;
  
  typedef struct{    
    Stock *stock;
    User *user;
    int n_actions; //number of actions in the transaction.
    int typeOrder; //0:sell 1:buy
    float ask;
    float bid;
  }Order;

  int createrOrder_buy(Market *market, Stock *stock, User *user, int n_actions,float bid);
  
  int createrOrder_sell(Market *market, Stock *stock, User *user, int n_actions,float ask);

  
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* ORDER_H */
