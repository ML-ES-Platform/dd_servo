/*
 * vd_servo.h
 *
 *  Created on: Apr 23, 2020
 *      Author: Andrei Bragarenco
 */

#ifndef _DD_SERVO_H_
#define _DD_SERVO_H_

#include "dd_servo_cfg.h"

#ifndef DD_SERVO_CONFIG
enum DD_SERVO_Cnl_IdType {DD_SERVO_CHANNEL_NR_OF = 0 };
#endif


typedef struct DDSERVO_ChannelType_t {

	Std_ChannelIdType pulseChannelId = 0;
	// pulse in microseconds
	Std_RawDataType PULSE_USMIN = 600; // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
	Std_RawDataType PULSE_USMAX = 2400; // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
	Std_RawDataType pulseVal = 0;
	
	Std_PhyDataType ANGLE_MIN = 0;
	Std_PhyDataType ANGLE_MAX = 180;
	Std_PhyDataType angleVal = 0;

	Std_RawSetterType SetPulse = NULL;

}DDSERVO_ChannelType;


Std_ReturnType DD_SERVO_ChannelSetup(Std_ChannelIdType servoChannelId, Std_ChannelIdType pulseChannelId);
DDSERVO_ChannelType* DDSERVO_GetChannelRef(Std_ChannelIdType channelId);
Std_ReturnType DD_SERVO_SetPushMethod( Std_ChannelIdType channelId,  Std_RawSetterType SetPulse);

Std_ReturnType DDSERVO_GroupSetup(Std_ChannelIdType *srcIds, Std_ChannelIdType *targhetIds, uint8_t nr_of_channels);
Std_ReturnType DDSERVO_SetGroupDevSetter(Std_ChannelIdType *srcIds, Std_RawSetterType deviceSetter, uint8_t nr_of_channels);

Std_ReturnType DDSERVO_SetPulseLimits(DDSERVO_ChannelType *channelRef, Std_RawDataType PULSE_USMIN, Std_RawDataType PULSE_USMAX);
Std_ReturnType DDSERVO_SetAngleLimits(DDSERVO_ChannelType *channelRef, Std_PhyDataType ANGLE_MIN, Std_PhyDataType ANGLE_MAX);

Std_ReturnType DDSERVO_SetPulse(DDSERVO_ChannelType *channelRef, Std_RawDataType Microseconds );
Std_ReturnType DDSERVO_SetPulse(Std_ChannelIdType channelId, Std_RawDataType Microseconds);
Std_ReturnType DDSERVO_SetAngle(DDSERVO_ChannelType *channelRef, Std_PhyDataType angle);
Std_ReturnType DDSERVO_SetAngle(Std_ChannelIdType channelId, Std_PhyDataType angle);

Std_PhyDataType DDSERVO_AngleGet(Std_ChannelIdType channelId);
Std_RawDataType DDSERVO_PulseGet(Std_ChannelIdType channelId);



#endif /* _DD_SERVO_H_ */
