#include "../inc/aud/audioevent.h"
#include "../inc/aud/audioeventmap.h"
#include "../inc/aud/clockbase.h"
#include <vector>
#include "resourcemanager.h"
#include <cassert>


int main (int argc, char *argv[]) {
   assert(Intersect::cuts_start == is_intersect(0, 4, 0, 1));
   assert(Intersect::cuts_start == is_intersect(1, 4, 0, 3));

   assert(Intersect::cuts_end == is_intersect(0, 4, 3, 5));

   assert(Intersect::contained_inside == is_intersect(0, 4, 1, 3));
   assert(Intersect::contained_outside == is_intersect(0, 4, 0, 4));
   assert(Intersect::contained_outside == is_intersect(0, 4, 0, 5));
  return 0; 
}
