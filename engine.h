#ifndef ENGINE_H
#define ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
  #include "market.h"

  int montecarlo(Market *market);
  int printJapaneseCandle(Market *market);
  
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* ENGINE_H */
