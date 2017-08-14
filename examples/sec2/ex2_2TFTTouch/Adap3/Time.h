class Time
{
  private:
    unsigned int h, m, s;
    bool active;

  public:
    Time(int h = 0, int m = 0, int s = 0);

    int getH();
    int getM();
    int getS();
    bool isActive();
    void setH(int h);
    void setM(int m);
    void setS(int s);
    void setActive(bool active = true);

    void setTime(Time t);
    void update();
    void fromMS(unsigned long int ms);
    String toString();
    friend bool operator==(Time& a, Time& b);
};

Time::Time(int h, int m, int s)
{
  this->h = h;
  this->m = m;
  this->s = s;
  active = false;
}

int Time::getH() {
  return h;
}
int Time::getM() {
  return m;
}
int Time::getS() {
  return s;
}
bool Time::isActive() {
  return active;
}
void Time::setH(int h) {
  this->h = h;
}
void Time::setM(int m) {
  this->m = m;
}
void Time::setS(int s) {
  this->s = s;
}
void Time::setActive(bool active) {
  this->active = active;
}


void Time::setTime(Time t)
{
  this->h = t.h;
  this->m = t.m;
  this->s = t.s;
}

void Time::update()
{
  fromMS(millis() / 1000);
}

void Time::fromMS(unsigned long int ms)
{
  s = (int)(ms);
  m = (int)(s / 60);
  h = (int)(m / 60);

  s -= m * 60;
  m -= h * 60;
}

String Time::toString()
{
  String str;

  if (h < 10) str += "0";
  str += h;
  str += ":";
  if (m < 10) str += "0";
  str += m;
  str += ":";
  if (s < 10) str += "0";
  str += s;

  return str;
}

bool operator==(Time& a, Time& b) {
  return (a.s == b.s && a.m == b.m && a.h == b.h);
}
