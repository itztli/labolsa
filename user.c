#include <stdio.h>
#include <stdlib.h>
#include "user.h"

User newUser(int index, float money){
  User user;
  user.index = index;
  user.money = money;
  return user;
}
