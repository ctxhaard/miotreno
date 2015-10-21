#pragma once

#include "schedule.h"

/**
* Identify a train and a station on its route
*/
struct ScheduleID {
  /// The start station code (as coded by Viaggiatreno API)
  char *cod_partenza;
  /// The train code (as coded by Viaggiatreno API)
  char *cod_treno;
  /// The station code (as coded by Viaggiatreno API)
  char *cod_stazione;
};

struct Schedule {
  struct ScheduleID id;
  char *expected_departure;
  char *last_station;
  char *status;
  // TODO: manage icon ICON
  char *destination;
  char *station;
};
