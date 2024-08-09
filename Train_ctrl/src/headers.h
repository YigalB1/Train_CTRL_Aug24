#define RED     1 
#define YELLOW  2
#define GREEN   3

#define min_speed 0
#define max_speed 255


class speed_knob {
  public: 
  int potsmtr_pin;
  int speed_knob_val = 0;
  
  int read_speed() {
    
    int speed_val;
    speed_knob_val = analogRead(potsmtr_pin);
    //Serial.print(" speed_knob_val:  ");
    //Serial.print(speed_knob_val);

    speed_val = map(speed_knob_val, 0, 4095, min_speed, max_speed);
    //Serial.print(" speed_val:  ");
    //Serial.println(speed_val);

    return speed_val;
  } // of read_speed()
} ;  // of speed_knob class

class Led {
    public:
    int led_pin;
    
    void init_led() { 
      pinMode(led_pin, OUTPUT);
    }
    void set_led_on() {
        digitalWrite(led_pin,HIGH);
    }
    void set_led_off() {
        digitalWrite(led_pin,LOW);
    }
}; // of class led

class buzzer {
    public:
    int _buz_pin;

    void init_buzzer() { 
      pinMode(_buz_pin, OUTPUT);
      //Serial.print("init_led: ");
      //Serial.println(led_pin);
    }

    void set_buzzer_on() {
        digitalWrite(_buz_pin,HIGH);
    }
    void set_buzzer_off() {
        digitalWrite(_buz_pin,LOW);
    }
};

class push_button {
  public:
  int button_pin;
  int pressed_num = 0 ; // mostly for debug
  //bool pressed = false; need to be volotile because of interrupts, in main

  void init() {
    pinMode(button_pin, INPUT_PULLUP);
  } // of init()

}; // of push_button class


class Train_ctrl {
  public:
    
    Led Red_led;
    Led Yellow_led;
    Led Green_led;
    buzzer buzz;
    motor_control motor;

    push_button start_button;
    push_button stop_button;
    push_button cng_button;
    speed_knob  manual_speed_knob;
    int train_speed = 0; // holds the value of theg speed according to the knob

    // for the ESP32 PWM
    const int freq = 5000;
    const int ledChannel0 = 0;
    const int ledChannel2 = 2;
    const int resolution = 8;

    bool dir_left = true;

    void update_speed() {
      // read every time in loop() to keep the speed updated
      if (motor.dir==GO_FWD) {
        motor.go_fwd(train_speed);
      } // of if()
      if (motor.dir==GO_BCK) {
        motor.go_fwd(train_speed);
      } // of if()

    } // of update_speed

    void led_ctrl(int _led) {
      if (_led ==  RED) {
        Red_led.set_led_on();
        Yellow_led.set_led_off();
        Green_led.set_led_off();
      } // of if()
      if (_led ==  YELLOW) {
        Red_led.set_led_off();
        Yellow_led.set_led_on();
        Green_led.set_led_off();
      } // of if()
      if (_led ==  GREEN) {
        Red_led.set_led_off();
        Yellow_led.set_led_off();
        Green_led.set_led_on();
      } // of if()
    } // of led_ctrl ()

    void test_leds() {
      int blink_delay = 500;
      for (int i=0;i<5;i++) {
        Red_led.set_led_off();
        Yellow_led.set_led_on();
        Green_led.set_led_off();
        
        wait_millis(blink_delay);
        Red_led.set_led_on();
        Yellow_led.set_led_off();
        Green_led.set_led_on();
        
        wait_millis(blink_delay);
      } // of for loop
    } // of test_leds()  
}; // of Train_ctrl Class