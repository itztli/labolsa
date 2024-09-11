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
  if (market->index_order < market->norders){
  
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
  market->orders[market->index_order] = order;
  market->index_order++;
  }else{
    printf("Warning: Not enough memory to create order.\n");
    order.typeOrder = -1;
  }
  return order;    
}
  
Order createrOrder_sell(Market *market,Stock *stock, User *user){
  Order order;
  return order;
}

void printOrders(Market *market){
  for (int i=0; i < market->index_order; i++){
    printf("%i,%i\n",i,market->orders[i].n_actions);
  }
}
  
