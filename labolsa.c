#include <stdio.h>
#include <stdlib.h>
#include "help.h"
#include "user.h"
#include "stock.h"
#include "market.h"

int main(int argn, char **argv){
  User *user;
  Stock *stock;
  Market *market;
  char code[8];
  int i,N,M;
  float memory_used;
  
  //printf("%i\n",argn);
  if (argn == 4){
    sscanf(argv[2],"%i", &M);
    sscanf(argv[3],"%i", &N);

    market = newMarket(argv[1],M,N);
    
    user = malloc(sizeof(User)*N);
    stock = malloc(sizeof(Stock)*M);
    
    printf("Labolsa simulator ver 20240828_1056\n");

    // Creating stocks
    printf("Generating %i stock... ",M);
    for(i=0; i < M; i++){
      sprintf(code,"MEX%i",i);
      addStock(market,newStock(code,100.0));
      
      //stock[i] = newStock(code,100.0);
    }
    printf("Ready!\n");
  

    
    printf("Generating %i users... ",N);
    for(i=0; i < N; i++){
      user[i] = newUser(i,1000.00);
    }
    printf("Ready!\n");
     //printf("%s:%f\n",stock[0].code,stock[0].price);
    memory_used = (float)(sizeof(user[0])*N+sizeof(stock[0])*M)/1e6; 
    printf("Memory used: %f Mb \n",memory_used);

    printMarket(market);

    free(user);
    free(stock);
    free(market);
  }else{
    print_help();
  }
  return 0;
}
