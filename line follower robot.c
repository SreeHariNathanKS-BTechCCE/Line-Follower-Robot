#include <lpc214x.h>

#define LEFT_SENSOR_THRESHOLD 1
#define RIGHT_SENSOR_THRESHOLD 1
																 
void init() {
  // Set P0.0 and P0.1 as digital outputs for left motor
  IO0DIR |= (1<<0) | (1<<1);
  //0001<<   0001 | 0010

  // Set P0.2 and P0.3 as digital outputs for right motor
  IO0DIR |= (1<<2) | (1<<3);
  //0001<<  0100 | 1000 

  // Set P0.4 and P0.5 as digital inputs for IR sensors
  IO0DIR &= ~((1<<4) | (1<<5));
  //0001<<   0001 0000 | 0010 0000
  IO0DIR  &= 0xFFFFFFBF; //P0.6 - switch
	IO0DIR  |= 0x00000100; //P0.8 - led

}

void set_motor_speed(int left_speed, int right_speed) {
  // Set left motor speed
  if (left_speed > 0) {
    // Forward
    IO0SET = (1<<0);
    IO0CLR = (1<<1);
  } else if (left_speed < 0) {
    // Reverse
    IO0SET = (1<<1);
    IO0CLR = (1<<0);
  } else {
    // Stop
    IO0CLR = (1<<0);
    IO0CLR = (1<<1);
  }

  // Set right motor speed
  if (right_speed > 0) {
    // Forward
    IO0SET = (1<<2);
    IO0CLR = (1<<3);
  } else if (right_speed < 0) {
    // Reverse
    IO0SET = (1<<3);
    IO0CLR = (1<<2);
  } else {
    // Stop
    IO0CLR = (1<<2);
    IO0CLR = (1<<3);
  }
}

int main() {
  init();

  while (1) {
    //int left_sensor = (IO0PIN & (1<<4)) >> 4;
    //int right_sensor = (IO0PIN & (1<<5)) >> 5;


    switchStatus = (IOPIN0 & 0x40);
		if (switchStatus == 1)
		{
      // Both sensors detect line, go straight
      set_motor_speed(50, 50);
    } 
  }

  return 0;
}