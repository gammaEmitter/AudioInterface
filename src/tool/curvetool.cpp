#include "curvetool.h"


void short_fade_in(CurveModel& model, uint32_t len) {
  model.shape = linear;
  model.end = 0;
  model.length = max(len / 10, 10);
}


void short_fade_out(CurveModel& model, uint32_t len) {
  model.shape = linear;
  model.start = 0;
  model.length = max(len / 10, 10);
}
