// general purpose functions


void wait_millis(int _period_ms) {
  unsigned long time_now = millis();
  while(millis() < time_now+_period_ms);
} // of wait_millis