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
    //-0.05 , 0.02
    //  0.02 + 1 (-0.05 - 0.02 ) = 0.02 - 0.07 = -0.05  
    //return b + rvalue * (a - b) //bug;
    //  -0.05 + 1 (0.02 + 0.05 ) = -0.05 + ( 0.07) = 0.02
    return a + rvalue * (b - a); //fixed
}


float randomFloatInRange(float a, float b) {
    // Generar un número aleatorio flotante entre 0 y 1
    float scale = rand() / (float) RAND_MAX;
    // Ajustar el valor al rango [a, b]
    return a + scale * (b - a);
}

Order createrOrder_buy(Market *market,Stock *stock, User *user){
  Order order;
  float risk;
  if (market->index_order_buy < market->norders_buy){
  
  //necesitamos una funcion que de valores entre 0.02 y - 0.05)
  risk = randomFloatInRange(-0.05, 0.02);
  order.stock = stock;
  order.user = user;
  order.typeOrder = 1;
  order.bid = stock->price*(1.0+risk);
  order.n_actions = (int)((user->money/order.bid)*randomFloatInRange(0.0, 1.0));
  order.stock->begin_flag = 1;
  if (order.n_actions < 1){
    order.n_actions = 1;
  }
  user->money -= ((float)order.n_actions)*order.bid;
  user->money_in_orders += ((float)order.n_actions)*order.bid;
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
  int nmax,nstock;
  int nget;
  //determinamos si hay memoria para crear una nueva orden
  if (market->index_order_sell < market->norders_sell){    
    //necesitamos una funcion que de valores entre 0.02 y - 0.05)
    risk = randomFloatInRange(-0.02, 0.05);
    order.stock = stock;
    order.user = user;
    order.typeOrder = 0;
    order.ask = stock->price*(1.0+risk);
    //calculamos cuantas acciones vamos a vender
    nget = get(*user,stock->code);
    if (nget <0){
      printf("Warning2: get < 0\n");
    }
    order.n_actions = (int)(nget*randomFloatInRange(0.0, 1.0));
    if (order.n_actions < 1){
      order.n_actions = 1;
    }
    //checar el numero maximo de acciones a vender
    nmax = get(*user,stock->code);
    if (order.n_actions > nmax){
      order.n_actions = nmax; 
    }
    
    market->orders_sell[market->index_order_sell] = order;
    market->index_order_sell++;

    //BUG 2: frozen stock push on sell
    nstock =  get(*user,stock->code);
    if (nstock <0){
      printf("Warning3: nstock < 0\n");
    }
    //printf("BUG3: %i\n",nstock-order.n_actions);
    insert(user, stock->code, nstock-order.n_actions);

  }else{
    printf("Warning: Not enough memory to create order.\n");
    order.typeOrder = -1;
  }
  return order;    
}

void printOrders(Market *market){
  
  printf("Orders Buy\n");
  printf("INDEX\tUSER\tACTIONS\tSTOCK\tBID\n");
  for (int i=0; i < market->index_order_buy; i++){
    printf("%i\t%i\t%i\t%s\t%f\n",i,market->orders_buy[i].user->index,market->orders_buy[i].n_actions,market->orders_buy[i].stock->code,market->orders_buy[i].bid);
  }
  printf("Orders Sell\n");
  printf("INDEX\tUSER\tACTIONS\tSTOCK\tASK\n");
  for (int i=0; i < market->index_order_sell; i++){
    printf("%i\t%i\t%i\t%s\t%f\n",i,market->orders_sell[i].user->index, market->orders_sell[i].n_actions,market->orders_sell[i].stock->code,market->orders_sell[i].ask);
  }
  
}

//warning: in this function we implement down the sell orders and up the price of the buy orders.
int orders_trash_collector(Market *market){
  Order *orders_buy_new;
  Order *orders_sell_new;
  int norders,j;
  int norders_buy, norders_sell;
  float risk;
  float update_price;
  float bid,last_price;
  
  norders_buy = market->norders_buy;
  norders_sell = market->norders_sell; 
    
  orders_buy_new = malloc(sizeof(Order)*norders_buy);
  orders_sell_new = malloc(sizeof(Order)*norders_sell);
  j=0;
  for (int i=0; i< market->index_order_buy; i++){
    market->orders_buy[i].stock->index_avg_price =0;
    if(market->orders_buy[i].n_actions > 0){
      memcpy(&orders_buy_new[j], &market->orders_buy[i], sizeof(Order));
      //implements random up offer to buy
      risk = randomFloatInRange(0.01, 0.05);
      last_price = orders_buy_new[j].bid; //store temporary price     
      //orders_buy_new[j].bid = orders_buy_new[j].bid*(1.0+risk);
      orders_buy_new[j].bid = last_price*(1.0+risk);
      update_price = last_price*risk; //computing diference
      //checando que hay suficiente dinero para esta nueva oferta
     
      if ((float)market->orders_buy[i].n_actions*update_price > market->orders_buy[i].user->money){
	//printf("WARNING99\n");
	orders_buy_new[j].bid=last_price + (market->orders_buy[i].user->money / (float)market->orders_buy[i].n_actions);
	update_price = orders_buy_new[j].bid-last_price; //computing diference
      }
      
      orders_buy_new[j].user->money_in_orders += update_price*((float)market->orders_buy[i].n_actions);
      orders_buy_new[j].user->money -= update_price*((float)market->orders_buy[i].n_actions);

      
      //      orders_buy_new[j] = market->orders_buy[i];
      j++;
    }
  }
  market->index_order_buy = j;
  j=0;
  for (int i=0; i< market->index_order_sell; i++){
    if(market->orders_sell[i].n_actions > 0){
      memcpy(&orders_sell_new[j], &market->orders_sell[i], sizeof(Order));
      risk = randomFloatInRange(-0.05, -0.01);
      orders_sell_new[j].ask = orders_sell_new[j].ask*(1.0+risk);
      //orders_sell_new[j] = market->orders_sell[i];
      j++;
    }
  }
  market->index_order_sell = j;
  free(market->orders_buy);
  free(market->orders_sell);

  market->orders_buy = orders_buy_new;
  market->orders_sell = orders_sell_new;
  

}

