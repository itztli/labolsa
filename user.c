#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "stock.h"

//from: https://www.geeksforgeeks.org/implementation-on-map-or-dictionary-data-structure-in-c/
// Function to get the index of a key in the keys array 
int getIndex(User user, char key[]) 
{ 
    for (int i = 0; i < user.size; i++) { 
        if (strcmp(user.keys[i], key) == 0) { 
            return i; 
        } 
    } 
    return -1; // Key not found 
} 
  
// Function to insert a key-value pair into the map 
void insert(User *user, char key[], int value) 
{ 
  int index = getIndex(*user, key); 
    if (index == -1) { // Key not found 
        strcpy(user->keys[user->size], key); 
        user->values[user->size] = value; 
        user->size++; 
    } 
    else { // Key found 
        user->values[index] = value; 
    } 
} 
  
// Function to get the value of a key in the map 
int get(User user, char key[]) 
{ 
  int index = getIndex(user, key); 
    if (index == -1) { // Key not found 
        return -1; 
    } 
    else { // Key found 
        return user.values[index]; 
    } 
} 
  
// Function to print the map 
void printMap(User user) 
{ 
    for (int i = 0; i < user.size; i++) { 
        printf("\t%s: %d\n", user.keys[i], user.values[i]); 
    } 
} 
//end from

User newUser(int index, float money){
  User user;
  user.index = index;
  user.money = money;
  user.money_in_orders = 0.0;
  user.size = 0;
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
  int r;
  //printf("INFO get: %i\n",get(user, stock.code));
  if (get(user, stock.code) > 0){
    r = rand();
    if (r%2 == 0){
      //printf("INFO:Sell\n");
      return 1;
    }else{
      return 0;
    }
  }else{
    return 0; // the user is not owner of the stock
  }
}

