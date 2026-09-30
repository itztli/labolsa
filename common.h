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

#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MAX_SIZE 512
  // Maximum number of elements in the map (stocks by user)

    
  typedef struct{
    int index;
    float money; //total money of the user
    float money_in_orders; //money compromised in orders
    int age;
    int size; // Current number of elements in the map 
    char keys[MAX_SIZE][32]; // Array to store the keys (stock codes) 
    int values[MAX_SIZE]; // Array to store the values 
  }User;

  
  
  typedef struct{    
    Stock *stock;
    User *user;
    int n_actions; //number of actions in the transaction.
    int typeOrder; //0:sell 1:buy -1:not enough memory
    float ask; //sell
    float bid; //buy
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
