#ifndef INCLUDED_FORWARDER_H
#define INCLUDED_FORWARDER_H

#include "../matrix.h"
#include "../network_state.h"

#include "./activity.h"
#include "./dropout.h"

Activity *
forward_for_activity(
  NetworkState *network_state,
  Matrix        sample
);

Matrix
forward_for_output(
  NetworkState *network_state,
  Matrix        sample
);

#endif
