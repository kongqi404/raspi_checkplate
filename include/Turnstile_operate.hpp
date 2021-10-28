#ifndef _TS_
#define _TS_
#include<wiringPi.h>
#include<softPwm.h>
#define PORT 1
#define RANGE 200
class Turnstile_operate
{
private:
    float degree;
    int d;
public:
    Turnstile_operate();
    ~Turnstile_operate();
    int init_ts();
    int ts_normally_open();
    int ts_normally_close();
    int ts_start();
};
Turnstile_operate::Turnstile_operate()
{
    init_ts();
}

Turnstile_operate::~Turnstile_operate()
{
}
int Turnstile_operate::init_ts()
{
    wiringPiSetup();
    softPwmCreate(PORT,5,RANGE);
    delay(1000);
    return 1;
}
int Turnstile_operate::ts_normally_open()
{
    
    degree = 95.0;
    d = 5+degree/180.0*20.0;
    softPwmWrite(PORT,d);
    delay(1000);
    return 1;
}
int Turnstile_operate::ts_normally_close()
{
    
    degree = 0.0;
    d = 5+degree/180.0*20.0;
    softPwmWrite(PORT,d);
    delay(1000);
    return 1;

}

int Turnstile_operate::ts_start()
{
    softPwmWrite(PORT,5);
    delay(1000);
    softPwmWrite(PORT,15);
    delay(5000);
    softPwmWrite(PORT,5);
    delay(1000);
    return 1;
}
#endif