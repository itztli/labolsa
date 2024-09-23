#ifndef STOCK_H
#define STOCK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

  typedef struct{
    char code[8];
    float price;
    int nstocks; // stocks available for sell.
  }Stock;

  Stock newStock(char code[], float price, int nstocks);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* STOCK_H */
