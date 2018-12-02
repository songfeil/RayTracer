//
// Created by 宋飞龙 on 2018-11-30.
//

#include "Hit.h"
#include "Object.h"

void Hit::getUV(double &u, double &v) const {
  this->obj_ptr->getUV(this, u, v);
}