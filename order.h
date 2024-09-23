#ifndef ORDER_H
#define ORDER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stock.h"
#include "user.h"
#include "common.h"

  //struct Market;
  
  Order createrOrder_buy(Market *market, Stock *stock, User *user);
  
  Order createrOrder_sell(Market *market,Stock *stock, User *user);

  void printOrders(Market *market);
  
  double randomValue(double a, double b);  

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* ORDER_H */
