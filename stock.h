#ifndef STOCK_H
#define STOCK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

  typedef struct{
    char code[8];
    float price;
  }Stock;

  Stock newStock(char code[], float price);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* STOCK_H */
