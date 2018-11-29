//
// Created by 宋飞龙 on 2018-11-29.
//

#ifndef RAYTRACING_OBJECTLIST_H
#define RAYTRACING_OBJECTLIST_H

#include "Object.h"
#include "Hit.h"

class ObjectList : public Object {
 public:
  Object ** list;
  int list_size;

  ObjectList(Object ** list, int size) {
    this->list = list;
    this->list_size = size;
  }

  bool intersect(const Ray & ray, double min_t, double max_t, Hit & hit) const {
    Hit rec_tmp;
    bool result = false;
    double curr_t = max_t;

    for (int i = 0; i < list_size; i++) {
      if (list[i]->intersect(ray, min_t, curr_t, rec_tmp)) {
        result = true;
        curr_t = rec_tmp.t;
        hit = rec_tmp;
      }
    }

    return result;
  }
};

#endif //RAYTRACING_OBJECTLIST_H
