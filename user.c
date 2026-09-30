/**
    <labolsa> Montecarlo model of market stocks
    Copyright (C) 2024  Victor De la Luz 
                        <vdelaluz@enesmorelia.unam.mx>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

VERSION Beta (10/22/2024)
**/

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
//warning: not print values == 0
void printMap(User user) 
{ 
    for (int i = 0; i < user.size; i++) {
      if (user.values[i]>0){
        printf("\t%s: %d\n", user.keys[i], user.values[i]); 
      }
    }
} 
//end from

User newUser(int index, float money, int age){
  User user;
  user.index = index;
  user.money = money;
  user.money_in_orders = 0.0;
  user.size = 0;
  user.age = age;
  return user;
}

int randomInRange(int a, int b) {
    int range = b - a + 1;
    int rand_max = RAND_MAX - (RAND_MAX % range);
    int rand_val;

    do {
        rand_val = rand();
    } while (rand_val >= rand_max);

    return a + (rand_val % range);
}

  //ask to participate in buy action in stock
int askOrderBuy(User user, Stock stock){
  int r;
  r = randomInRange(1,10);
  if ((r >= 8) && (user.money >= stock.price))
    return 1;
  else
    return 0;
   
  /*r = rand();
  if ( (r%2 == 0) && (user.money >= stock.price)){
    return 1;
  }else{
    return 0;
    }*/
}

  //ask
int askOrderSell(User user, Stock stock){
  int r;
  //printf("INFO get user %i: %s\t%i\n",user.index, stock.code, get(user, stock.code));
  if (get(user, stock.code) > 0){
    //printf("INFO: User have stock %s!\n",stock.code);
    r = randomInRange(1,10);
    if (r >=2 )
      return 1;
    else
      return 0;
  /*    r = rand();
    if (r%2 == 0){
      //printf("INFO:Sell\n");
      return 1;
    }else{
      return 0;
    }
  */
  }else{
    return 0; // the user is not owner of the stock
  }
}

float value_in_stocks(Market *market, User user){
  float value;
  float total;
  total = 0.0;
  for (int i = 0; i < user.size; i++) { 
    value = get_value_of_stock(market, user.keys[i]);
    total += value*((float)user.values[i]);
  }
  return total;
}
