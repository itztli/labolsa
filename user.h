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

#ifndef USER_H
#define USER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
  
#include "stock.h"
#include "common.h"
#include "market.h"
#include <string.h>
  
  // age [year]
  User newUser(int index, float money, int age);

  //ask to participate in buy action in stock
  int askOrderBuy(User user, Stock stock);

  //ask
  int askOrderSell(User user, Stock stock);

  int get(User user, char key[]);
  
  void insert(User *user, char key[], int value);

  void printMap(User user); 

  float value_in_stocks(Market *market, User user);
  
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* USER_H */
