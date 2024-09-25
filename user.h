#ifndef USER_H
#define USER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
  
#include "stock.h"
#include <string.h>
  
#define MAX_SIZE 100
  // Maximum number of elements in the map 
    
  typedef struct{
    int index;
    float money; //total money of the user
    float money_in_orders; //money compromised in orders
    int size; // Current number of elements in the map 
    char keys[MAX_SIZE][100]; // Array to store the keys 
    int values[MAX_SIZE]; // Array to store the values 
  }User;

  User newUser(int index, float money);

  //ask to participate in buy action in stock
  int askOrderBuy(User user, Stock stock);

  //ask
  int askOrderSell(User user, Stock stock);

  int get(User user, char key[]);
  
  void insert(User *user, char key[], int value);

  void printMap(User user); 

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* USER_H */
