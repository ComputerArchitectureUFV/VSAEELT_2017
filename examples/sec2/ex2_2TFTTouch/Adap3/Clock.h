#include "Time.h"

class Clock
{
  private:
    Time t;
    Time alarm;
    Time chron;
    bool chronPaused;

  public:
    Clock();

    Time& getTime();
    Time& getAlarm();
    Time& getChronometer();
    void setTime(Time t);
    void setAlarm(Time alarm, bool active = true);
    void activateAlarm();
    void startChronometer();
    void pauseChronometer();

    void update();
};

Clock::Clock() {
  t.fromMS(millis());
}

Time& Clock::getTime() {
  return t;
}
Time& Clock::getAlarm() {
  return alarm;
}
Time& Clock::getChronometer() {
  return chron;
}

void Clock::setTime(Time t) {
  this->t.setTime(t);
}

void Clock::setAlarm(Time alarm, bool active)
{
  alarm.setTime(alarm);
  alarm.setActive(active);
}

void Clock::activateAlarm() {
  alarm.setActive();
}

void Clock::startChronometer()
{
  if (!chronPaused) chron.setTime(getTime());
  chron.setActive();
}

void Clock::pauseChronometer()
{
  chronPaused = true;
  chron.setActive(false);
}

void Clock::update()
{
  t.update();
  if (chron.isActive()) chron.update();

  if (alarm == t)
  {
    // Blink and buzz!
    alarm.setActive(false);
  }
}
