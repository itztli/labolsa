#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "stock.h"

User newUser(int index, float money){
  User user;
  user.index = index;
  user.money = money;
  return user;
}

  //ask to participate in buy action in stock
int askOrderBuy(User user, Stock stock){
  int r;
  r = rand();
  if ( (r%2 == 0) && (user.money >= stock.price)){
    return 1;
  }else{
    return 0;
  }
}

  //ask
int askOrderSell(User user, Stock stock){
  return 1;
}

