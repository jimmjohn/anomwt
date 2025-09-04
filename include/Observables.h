#pragma once
#include "EventInitilizers.h"

class Observables {
public:
  // public outputs
  double y1 = 0.0;
  double y2 = 0.0;
  double acoplanarity_angle = 0.0;  // in [0, 2π)
  // compute from one event (does not modify evtIn)
  void Acoplanarity(EventInitilizers& evtIn);
private:

};