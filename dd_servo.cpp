/*
 * vd_servo.cpp
 *
 *  Created on: Apr 23, 2020
 *      Author: Andrei Bragarenco
 */

#include "dd_servo.h"

DDSERVO_ChannelType DDSERVO_Channels[DD_SERVO_CHANNEL_NR_OF];



DDSERVO_ChannelType* DDSERVO_GetChannelRef(Std_ChannelIdType channelId){
	DDSERVO_ChannelType *channelRef = &DDSERVO_Channels[channelId];
	return channelRef;

}

Std_ReturnType DD_SERVO_ChannelSetup(Std_ChannelIdType servoChannelId, Std_ChannelIdType pulseChannelId){
	Std_ReturnType error;
	if (servoChannelId < DD_SERVO_CHANNEL_NR_OF) {
		DDSERVO_ChannelType *channelRef = DDSERVO_GetChannelRef(servoChannelId);
		channelRef->pulseChannelId = pulseChannelId;
		error = E_OK;
	} else {
		error = E_NOT_OK;
	}
	return error;
}


Std_ReturnType DD_SERVO_SetPushMethod( Std_ChannelIdType channelId,  Std_RawSetterType SetPulse){
	Std_ReturnType error;
	if (channelId < DD_SERVO_CHANNEL_NR_OF) {
		DDSERVO_ChannelType *channelRef = DDSERVO_GetChannelRef(channelId);
		channelRef->SetPulse = SetPulse;
		error = E_OK;
	} else {
		error = E_NOT_OK;
	}
	return error;
}


Std_ReturnType DDSERVO_GroupSetup(Std_ChannelIdType *srcIds, Std_ChannelIdType *targhetIds, uint8_t nr_of_channels)
{
	Std_ReturnType error = E_OK;

	for (size_t i = 0; i < nr_of_channels; i++)
	{
		Std_ChannelIdType srcId = srcIds[i];
		Std_ChannelIdType targhetId = targhetIds[i];
		error += DD_SERVO_ChannelSetup(srcId, targhetId);
	}
	return error;
}

Std_ReturnType DDSERVO_SetGroupDevSetter(Std_ChannelIdType *srcIds, Std_RawSetterType deviceSetter, uint8_t nr_of_channels)
{
	Std_ReturnType error = E_OK;

	for (size_t i = 0; i < nr_of_channels; i++)
	{
		Std_ChannelIdType srcId = srcIds[i];
		error += DD_SERVO_SetPushMethod(srcId, deviceSetter);
	}
	return error;
}


Std_ReturnType DDSERVO_SetPulseLimits(DDSERVO_ChannelType *channelRef, Std_RawDataType PULSE_USMIN, Std_RawDataType PULSE_USMAX){
	Std_ReturnType error;
	if (channelRef->SetPulse) {
		channelRef->PULSE_USMIN = PULSE_USMIN;
		channelRef->PULSE_USMAX = PULSE_USMAX;
	} else {
		error = E_NOT_OK;
	}
	return error;
}

Std_ReturnType DDSERVO_SetAngleLimits(DDSERVO_ChannelType *channelRef, Std_PhyDataType ANGLE_MIN, Std_PhyDataType ANGLE_MAX){
	Std_ReturnType error;
	if (channelRef->SetPulse) {
		channelRef->ANGLE_MIN = ANGLE_MIN;
		channelRef->ANGLE_MAX = ANGLE_MAX;
	} else {
		error = E_NOT_OK;
	}
	return error;
}

Std_ReturnType DDSERVO_SetPulse(DDSERVO_ChannelType *channelRef, Std_RawDataType Microseconds) {
	Std_ReturnType error;
	if (channelRef->SetPulse) {
		channelRef->angleVal = map_float(Microseconds, channelRef->PULSE_USMIN, channelRef->PULSE_USMAX, channelRef->ANGLE_MIN, channelRef->ANGLE_MAX);
		channelRef->pulseVal = Microseconds;
		error = channelRef->SetPulse(channelRef->pulseChannelId, Microseconds);
	} else {
		error = E_NOT_OK;
	}
	return error;
}

Std_ReturnType DDSERVO_SetPulse(Std_ChannelIdType channelId, Std_RawDataType Microseconds) {
	Std_ReturnType error;
	if (channelId < DD_SERVO_CHANNEL_NR_OF) {
		DDSERVO_ChannelType *channelRef = &DDSERVO_Channels[channelId];
		error = DDSERVO_SetPulse(channelRef, Microseconds);
	} else {
		error = E_NOT_OK;
	}
	return error;
}

Std_ReturnType DDSERVO_SetAngle(DDSERVO_ChannelType *channelRef, Std_PhyDataType angle) {
	Std_ReturnType error;
	if (channelRef->SetPulse) {
		channelRef->angleVal = angle;
		channelRef->pulseVal = map_float(angle, channelRef->ANGLE_MIN, channelRef->ANGLE_MAX, channelRef->PULSE_USMIN, channelRef->PULSE_USMAX);
		error = DDSERVO_SetPulse(channelRef, channelRef->pulseVal);
	} else {
		error = E_NOT_OK;
	}
	return error;
}

Std_ReturnType DDSERVO_SetAngle(Std_ChannelIdType channelId,
		Std_PhyDataType angle) {
	Std_ReturnType error;
	if (channelId < DD_SERVO_CHANNEL_NR_OF) {
		DDSERVO_ChannelType *channelRef = &DDSERVO_Channels[channelId];
		error = DDSERVO_SetAngle(channelRef, angle);
	} else {
		error = E_NOT_OK;
	}
	return error;
}

Std_PhyDataType DDSERVO_AngleGet(Std_ChannelIdType channelId) {

	DDSERVO_ChannelType *cnlRef = DDSERVO_GetChannelRef(channelId);

	return cnlRef->angleVal;

}

Std_RawDataType DDSERVO_PulseGet(Std_ChannelIdType channelId) {

	DDSERVO_ChannelType *cnlRef = DDSERVO_GetChannelRef(channelId);

	return cnlRef->pulseVal;

}
