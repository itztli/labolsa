#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"

Stock newStock(char code[], float price, int nstocks){
  Stock stock;
  strcpy(stock.code, code);
  stock.price = price;
  stock.nstocks = nstocks;
  return stock;
}
