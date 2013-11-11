#ifndef __ROSENFELD_OPERATOR_H__
#define __ROSENFELD_OPERATOR_H__

#include "Operation.h"

class RosenfeldOperator : public Operation
{
public:
  RosenfeldOperator(int p);
  
  void perform(Image &image);

private:
  int P;

};

#endif