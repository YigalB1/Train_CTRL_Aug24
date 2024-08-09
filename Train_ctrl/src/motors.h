//#include <esp_now.h>
//#include <WiFi.h>
#include <OneWire.h> // for the temp sensor (one wire bus)
#include <DallasTemperature.h>

// Motors constants
//#define START_SPEED 200
#define STOP 0
#define GO  1
#define GO_FWD 1
#define GO_BCK 2


// ***********************************************************


// ***********************************************************
  class motor_control {
    public:
    int _en;
    int _in_1;
    int _in_2;
    //int _channel;
    int _freq;
    int _resolution;;
    int _led_channel;

    int status  = STOP;     // 0: stopping  1: Going
    int dir     = GO_FWD; // 1: Going FWD 2: going BCK

    //buzzer _buzzer;

    void init(int __en,int __in_1, int __in_2, int __freq, int __res, int __chan) {
        _en = __en;
        _in_1 = __in_1;
        _in_2 = __in_2;
        _freq = __freq;
        _resolution = __res;
        _led_channel = __chan;
        status = STOP;
        dir = GO_FWD;

        pinMode(__in_1, OUTPUT);
        pinMode(__in_2, OUTPUT);

        ledcSetup(_led_channel, _freq,_resolution);
        ledcAttachPin(_en, _led_channel);

    } // of init()

    void motor_test() {
        //Serial.print("..motor test fwd");
        go_fwd(200);
        wait_millis(3000);
        stop();
        wait_millis(1000);
        go_back(200);
        wait_millis(3000);
        stop();
        wait_millis(1000);
    } // of motor_test()

void stop() {
   // i2c_main.digitalWrite(_in_1, LOW);
   // i2c_main.digitalWrite(_in_2, LOW);
    digitalWrite(_in_1, LOW); // 
    digitalWrite(_in_2, LOW); //
    ledcWrite(_led_channel, 0); 
  } // of stop()

  void go_fwd(int _speed) {
    digitalWrite(_in_1, LOW); // 
    digitalWrite(_in_2, HIGH); // 
    ledcWrite(_led_channel, _speed);    
  } // of go_fwd()

  void go_back(int _speed) {
    digitalWrite(_in_1, HIGH); // 
    digitalWrite(_in_2, LOW); // 
    ledcWrite(_led_channel, _speed);
  } // of go_back()

/*
  void make_buzz(int _buz_time) {
    _buzzer.set_buzzer_on();
    //digitalWrite(Buzzer_pin, HIGH);
    delay(_buz_time); // TBD: change to wait_millies
    _buzzer.set_buzzer_off();
    //digitalWrite(Buzzer_pin, LOW);
  } // of make_buzz()
*/

}; // of class motor_control

/*
class leds {
    Public:
    int _led;

    void set_led_on() {
        digitalWrite(_led,HIGH);
    }
    void set_led_off() {
        digitalWrite(_led,LOW);
    }

*/

class car {
    public:
    int f_dist;
    int b_dist;
    // for PWM (driving motors)
    const int freq = 5000;
    const int ledChannel0 = 0;
    const int ledChannel2 = 2;
    const int resolution = 8;

    int dist_th = 50;       // distance from obstacle to make the car stop
    int turn_time = 100;    // minimal time per turn

    motor_control motors_left;
    motor_control motors_right;
   

    void init() {
   
        
        // TBD
        //ledcSetup(_led_channel, _freq,_resolution);
        //ledcAttachPin(_en, _led_channel);
    } // of init()

    void go_fwd(int _speed) {
        motors_left.go_fwd(_speed);
        motors_right.go_fwd(_speed);
    } // of go_fwd()

    void go_bck(int _speed) {
        motors_left.go_back(_speed);
        motors_right.go_back(_speed);
    } // of go_bck()

    void stop() {
        motors_left.go_back(0);
        motors_right.go_back(0);
    } // of stop()

    void turn_left(int _tm) {
        motors_left.go_fwd(_tm);
        motors_right.go_back(_tm);
    } // of turn_left

        void turn_right(int _tm) {
        motors_left.go_back(_tm);
        motors_right.go_fwd(_tm);
        
    } // of turn_right

    //void go_f_auto(UltraSonic_sensor _sens_f, UltraSonic_sensor _sens_b) {
    void go_f_auto() {
        //int d1 = _sens_f.measure_it();
        //int d2 = _sens_b.measure_it();
        //int d1 = f_sns.measure_it();
        //int d2 = b_sns.measure_it();

  
        




    } // of go_f_auto

}; // of class car