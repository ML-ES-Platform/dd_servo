/*
 * dd_servo_demo.cpp
 *
 *  Created on: May 8, 2020
 *      Author: Andrei Bragarenco
 */

#include "ESW/dd_pca9685/dd_pca9685.h"
#include "ESW/dd_servo/dd_servo.h"
#include <ESW/dd_servo/dd_servo_demo.h>


#define PWM_MIN  0 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define PWM_MAX  180 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define PCA9685_PWM_FREQ 50 // Analog servos run at ~50 Hz updates

//The setup function is called once at startup of the sketch
void dd_servo_demo_setup() {
// Add your initialization code here
	Serial.begin(9600);
	Serial.println("SERVO demo !");
	Std_ReturnType error = E_OK;

	error = PCA9685_DeviceInit(PCA9685_PWM_FREQ);

	error += DD_PCA9685_ChannelSetup(PCA9685_PWM_1, 0);
	error += DD_PCA9685_ChannelSetup(PCA9685_PWM_2, 1);
	error += DD_PCA9685_ChannelSetup(PCA9685_PWM_3, 2);
	// error += DD_PCA9685_ChannelSetup(PCA9685_PWM_4, 3);

	Serial.print("DD pca9685 configured - Error : ");
	Serial.println(error);
	
	error += DD_SERVO_ChannelSetup(DD_SERVO_1, PCA9685_PWM_1);
	error += DD_SERVO_ChannelSetup(DD_SERVO_2, PCA9685_PWM_2);
	error += DD_SERVO_ChannelSetup(DD_SERVO_3, PCA9685_PWM_3);
	// error += DD_SERVO_ChannelSetup(DD_SERVO_4, PCA9685_PWM_4);

	error += DD_SERVO_SetPushMethod(DD_SERVO_1, PCA9685_WriteChannel);
	error += DD_SERVO_SetPushMethod(DD_SERVO_2, PCA9685_WriteChannel);
	error += DD_SERVO_SetPushMethod(DD_SERVO_3, PCA9685_WriteChannel);
	// error += DD_SERVO_SetPushMethod(DD_SERVO_4, PCA9685_WriteChannel);

	Serial.print("DD SERVO configured - Error : ");
	Serial.println(error);

	delay(10);
}

void dd_servo_demo_loop() {

	// our servo # counter
	static uint8_t servoNum = 0;

	Serial.print("DD SERVO -> Operating channel : ");
	Serial.println(servoNum);

	for (uint16_t angle = PWM_MIN; angle < PWM_MAX; angle++) {
		DDSERVO_SetAngle(servoNum, angle);
		delay(10);

	}

	delay(500);
	for (uint16_t angle = PWM_MAX; angle > PWM_MIN; angle--) {
		DDSERVO_SetAngle(servoNum, angle);
		delay(10);
	}

	delay(500);

	servoNum++;
	if (servoNum >= DD_SERVO_CHANNEL_NR_OF)
		servoNum = 0; // Testing the first 8 servo channels
}
