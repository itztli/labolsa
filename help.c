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
#include "help.h"

void print_help(){
  printf("LaBolsa ver 1.0\n");
  printf("Error: Missing arguments.\n");
  printf("Seven arguments are required:\n");
  printf("Example: ./labolsa <name> <companies> <users> <orders> <stock_value> <n_stocks> <cash> <max_itera>\n");
  printf("Where:\n");
  printf("name: Market name [code of 8 characters maximum].\n");
  printf("companies: Number of Publicly Traded Companies in the Market [Integer].\n");
  printf("users: Number of clients in the Market [Integer].\n");
  printf("orders: Total number of orders allowed in the market by cycle [Integer].\n");
  printf("stock_value: Individual price for each stock [Float].\n");
  printf("n_stocks: Number of stocks maximum for each company [Integer].\n");
  printf("cash: Initial cash for each user [Float].\n");
  printf("max_itera: Number of iterations of the model [Int].\n");
}
