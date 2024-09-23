#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

  
  typedef struct{    
    Stock *stock;
    User *user;
    int n_actions; //number of actions in the transaction.
    int typeOrder; //0:sell 1:buy -1:not enough memory
    float ask;
    float bid;
  }Order;

   typedef struct{
    char name[8];
    int nstocks; // Maximum stocks
    int nusers;  // Maximum users
    int norders_buy; // Maximum number of orders
    int norders_sell;
    int index_stock; //total stocks
    int index_user; // total user
    int index_order_buy; //total of orders by iteration
    int index_order_sell; //total of orders by iteration
    Stock *stocks;
    User *users;
    Order *orders_buy;
    Order *orders_sell;
  }Market;


  
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* COMMON_H */
