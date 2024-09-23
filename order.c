#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "order.h"
#include "market.h"
#include "stock.h"
#include "user.h"


double randomValue(double a, double b) {
    // Generar un número pseudoaleatorio entre 0 y 1
    double rvalue = rand() / (double) RAND_MAX;

    // Escalar el valor al rango [-0.05, 0.02]
    return b + rvalue * (a - b);
}

Order createrOrder_buy(Market *market,Stock *stock, User *user){
  Order order;
  float risk;
  if (market->index_order_buy < market->norders_buy){
  
  //necesitamos una funcion que de valores entre 0.02 y - 0.05)
  risk = (float)randomValue(-0.05, 0.02);
  order.stock = stock;
  order.user = user;
  order.typeOrder = 1;
  order.bid = stock->price*(1.0+risk);
  order.n_actions = (int)((user->money/order.bid)*randomValue(0.0, 1.0));
  if (order.n_actions < 1){
    order.n_actions = 1;
  }
  user->money -= order.n_actions*order.bid;
  user->money_in_orders += order.n_actions*order.bid;
  market->orders_buy[market->index_order_buy] = order;
  market->index_order_buy++;
  }else{
    printf("Warning: Not enough memory to create order.\n");
    order.typeOrder = -1;
  }
  return order;    
}
  
Order createrOrder_sell(Market *market,Stock *stock, User *user){
  Order order;
  float risk;
  if (market->index_order_sell < market->norders_sell){
    
    //necesitamos una funcion que de valores entre 0.02 y - 0.05)
    risk = (float)randomValue(-0.02, 0.05);
    order.stock = stock;
    order.user = user;
    order.typeOrder = 0;
    order.ask = stock->price*(1.0+risk);
    order.n_actions = (int)(get(*user,stock->code)*randomValue(0.0, 1.0));
    if (order.n_actions < 1){
      order.n_actions = 1;
    }

    market->orders_sell[market->index_order_sell] = order;
    market->index_order_sell++;
  }else{
    printf("Warning: Not enough memory to create order.\n");
    order.typeOrder = -1;
  }
  return order;    
}

void printOrders(Market *market){
  
  printf("Orders Buy\n");
  for (int i=0; i < market->index_order_buy; i++){
    printf("%i,%i,%f\n",i,market->orders_buy[i].n_actions,market->orders_buy[i].bid);
  }
  printf("Orders Sell\n");
  for (int i=0; i < market->index_order_sell; i++){
    printf("%i,%i,%f\n",i,market->orders_sell[i].n_actions,market->orders_sell[i].ask);
  }
  
}
  
