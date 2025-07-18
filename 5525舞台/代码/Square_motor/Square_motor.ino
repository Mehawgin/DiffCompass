
/*
 Stepper Motor Control - one step at a time

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.

 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.

 Created 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>

#define   KEY_BOOT 		9			//按键引脚
#define   KEY_21 		21			//按键引脚

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 7, 5, 6, 8);
static int play_1_time = 0;

/*********************************************************/
/********************* 按键扫描函数 ***********************/
/*********************************************************/
void key_scan()
{
	static bool direction = 0, Ispressed = 0;
	if(digitalRead(KEY_BOOT) == LOW)
	{
		//延时消抖
		delay(5);
		//如果仍为低电平，按键按下
		while(digitalRead(KEY_BOOT) == LOW)
		{		
			Serial.println("Botton pressed！");
			Ispressed = 1;
			if (direction)
			{
				myStepper.step(100);
			}
			else
			{
				myStepper.step(-100);
			}

			delay(50);  
			
			//等待按键松开
			//while(digitalRead(KEY_BOOT) == LOW);
		}

		if (Ispressed)
		{
		 	Ispressed = 0;
			direction = !direction;	
		}
	}
	if(digitalRead(KEY_21) == LOW)
	{
		//延时消抖
		delay(5);
		//如果仍为低电平，按键按下
		while(digitalRead(KEY_21) == LOW)
		{		
			Serial.println("Botton_21 pressed！");
			play_1_time = 1;
			//等待按键松开
			//while(digitalRead(KEY_BOOT) == LOW);
		}
	}
	
} 

void setup() 
{
	// initialize the serial port:
	Serial.begin(115200);
	pinMode(KEY_BOOT,INPUT_PULLUP);  
	pinMode(KEY_21,INPUT_PULLUP);  
	myStepper.setSpeed(15); 
}

void loop() 
{
	int dalay_100ms = 210,i = 0;;

	key_scan();
	if (play_1_time)
	{
		play_1_time = 0;
		for (i = 0; i < dalay_100ms; i++)
		{
			delay(100);
			Serial.printf("[%d]s passed! \n\r", i);
			key_scan();
		}

		Serial.printf("one time move! \n\r");
		myStepper.step(1900);
		for (i = 0; i < 20; i ++)
		{
			//myStepper.step(-50);
		}
	}


}

