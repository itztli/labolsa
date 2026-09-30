/**
    <labolsa> Montecarlo model of market stocks.
    
    Copyright (C) 2025  Victor De la Luz 
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

Update (9/9/2025)
    
VERSION Beta (10/22/2024)
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "help.h"
#include "user.h"
#include "stock.h"
#include "market.h"
#include "engine.h"
#include "order.h"
#include "common.h"

#define EXIT_SUCCESS 0      // Ejecución exitosa
#define EXIT_FAILURE 1      // Error general no especificado
#define EX_USAGE     64     // Uso incorrecto de comando

// https://claude.ai/share/41b3ea27-333b-430e-b03f-117f9ecb1c46

/* Uniforme en (0,1), sin incluir 0 ni 1 */
double uniforme01(void) {
    return (rand() + 1.0) / (RAND_MAX + 2.0);
}

/* Cash que crece exponencialmente con la edad, con variación aleatoria
   exponencial truncada para no pasar de cash_max */
double cash_exponencial(int edad, double cash_min, double cash_max) {
    double rango = cash_max - cash_min;
    double t = (edad - 18) / 62.0;                 /* 0 a los 18, 1 a los 80 */

    /* Piso que crece exponencialmente con la edad */
    double k = 2.0;                                /* curvatura del crecimiento */
    double piso = cash_min + 0.7 * rango * (exp(k * t) - 1.0) / (exp(k) - 1.0);

    /* Variación exponencial truncada entre piso y cash_max */
    double hueco  = cash_max - piso;
    double lambda = 1.0 / (0.10 * rango);          /* variación media ~10 % del rango */
    double u = uniforme01();
    double x = -log(1.0 - u * (1.0 - exp(-lambda * hueco))) / lambda;

    return piso + x;
}

// NOTE: The user not update the price of the order after the first execution. We need to create a new function to ask to the user if wants to update price after each execution ends.

int main(int argn, char **argv){
  User *user;
  Stock *stock;
  Market *market;    
  char code[8];
  int i,j,k,n;
  int M;             // number of companies.
  int N;             // number of users.
  int P;             // number of orders.
  float stock_value; // individual price for each stock.
  //float cash;        // cash for each user.
  float cash_min;
  float cash_max;
  int n_stocks_by_company; //number of stocks maximum for each company.
  float memory_used;
  int max_itera;
  
  //printf("%i\n",argn);
  if (argn == 10){

    if (strlen(argv[1]) > 8){
      print_help();
      return EX_USAGE;
    }

    if (sscanf(argv[2],"%i", &M) <= 0){
      print_help();
      return EX_USAGE;
    }
    
    if (sscanf(argv[3],"%i", &N) <= 0){
      print_help();
      return EX_USAGE;
    }
      
    if (sscanf(argv[4],"%i", &P)<= 0){
      print_help();
      return EX_USAGE;
    }

    if (sscanf(argv[5],"%f", &stock_value)<= 0){
      print_help();
      return EX_USAGE;
    }
    
    if (sscanf(argv[6],"%i", &n_stocks_by_company)<= 0){
      print_help();
      return EX_USAGE;
    }

    if (sscanf(argv[7],"%f", &cash_min)<= 0){
      print_help();
      return EX_USAGE;
    }

    if (sscanf(argv[8],"%f", &cash_max)<= 0){
      print_help();
      return EX_USAGE;
    }
    

    if (sscanf(argv[9],"%i", &max_itera)<= 0){
      print_help();
      return EX_USAGE;
    }


    
    market = newMarket(argv[1],M,N,P);
    
    //user = malloc(sizeof(User)*N);
    //stock = malloc(sizeof(Stock)*M);
    printf("%i\n",M); //INFO: This variable is used as input in vizualization.py   
    printf("# Labolsa simulator ver 20250909_1105\n");
    printf("# GNU/GPL License.\n");
    printf("# By: Victor De la Luz <vdelaluz@enesmorelia.unam.mx>\n");
    // Creating stocks
    printf("# Generating %i companies... ",M);
    for(i=0; i < M; i++){
      sprintf(code,"%s%i",argv[1],i);
      // running with stock_value = 10.0
      // n_stocks_by_company = 1000
      addStock(market,newStock(code,stock_value, n_stocks_by_company));      
      //stock[i] = newStock(code,100.0);
    }
    printf("#Ready!\n");
    //srand(time(NULL));
    srand(1);
    printf("#Generating %i users... ",N);
    for(i=0; i < N; i++){
      int age = 18 + rand() % (80 - 18 + 1);   /* 18 + (0..62) */
      //double cash_min = 1000.0;
      //double cash_max = 50000.0;
      float new_cash = cash_exponencial(age, cash_min, cash_max);
      //float new_cash = randomValue(0.1*cash, cash);
      addUser(market,newUser(i,new_cash,age));
    }
    printf("#Ready!\n");
     //printf("%s:%f\n",stock[0].code,stock[0].price);
    memory_used = (float)(sizeof(User)*N+sizeof(Stock)*M)/1e6; 
    printf("#Memory used: %f Mb \n",memory_used);
    //print_divergence(market);
    // create the OPIs of our model. We create a random asignator of OPIS for all the users.
    // srand(time(NULL));
    k=0;
    printf("#Computing IOPs...\n");
    do{

      //(*market).index_stock   ===    market->index_stock
	
      for(int i=0; i < market->index_user;i++){
	j = (int)randomValue(0.0, (float)market->index_stock);
	  n = (int)((market->users[i].money/market->stocks[j].price)*randomValue(0.0, 1.0));
	  //printf("INFO: n= %i\n",n);
	  if (n >= 1){
	    buy_OPI(&market->stocks[j],&market->users[i],n,market->stocks[j].price);
	  }
	  /*
	  if (( n >0 ) && ( n < 1)){
	    n = 1; //fixed bug
	    //printf("INFO1:%s\n",market->stocks[j].code);
	  }
	  if (n >= 1){
	    buy_OPI(&market->stocks[j],&market->users[i],n,market->stocks[j].price);
	  }
	  */	  
      }
      k++;
      //printMarket(market);
    }while(remain_stocks(*market) > 0);

    printf("#IOPs iterations: %i\n",k);
    //print_divergence(market);
    //printMarket(market);

    printf("#Running Montecarlo...\n");
    for(int i=0; i < max_itera; i++){
      printf("#%i:",i);
      montecarlo(market);
      printJapaneseCandle(market);
      //printOrders(market);
      //printMarket(market);
      //print_divergence(market);
    }
    
    //printMarket(market);
    print_divergence(market);
    //free(user);
    //free(stock);
    closeMarket(market);
  }else{
    print_help();
    return EX_USAGE;
  }
  return EXIT_SUCCESS;
}
