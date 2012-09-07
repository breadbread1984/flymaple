#ifndef PRESSURE_H
#define PRESSURE_H

/**
 * @file	Pressure.h
 * @author	breadbread1984 <breadbread1984@163.com>
 * @date	Fri Sep 7 10:01:00 2012
 * 
 * @section	DESCRIPTION
 * 
 * The static class for manipulating the pressure sensor.
 * 
 * @section LICENSE
 * 
 * GPLv3
 */

#include "Sensor.h"

class Pressure {
	static Pressure pressure;
	
	static const unsigned char PressureAddress;
	static const unsigned char OSS;
	static const unsigned char BMP085_CAL_AC[6];
	static const unsigned char BMP085_CAL_B[2];
	static const unsigned char BMP085_CAL_MB;
	static const unsigned char BMP085_CAL_MC;
	static const unsigned char BMP085_CAL_MD;
	static const unsigned char BMP085_CONTROL;
	static const unsigned char BMP085_CONTROL_OUTPUT;
	static const unsigned char READ_TEMPERATURE;
	static const unsigned char READ_PRESSURE;
	static const int MSLP;
	static const int Altitude_cm_Offset;
	
	static short ac[6],b[2],mb,mc,md;
	static int b5;
  
	/**
	 * Constructor initializing the pressure sensor.
	 * To do the initialization for only once. The constructor is hiden from developer.
	 * The only one Pressure object is a static one created automatically.
	 */
	Pressure();
	short read(unsigned char addr);
	void getRawReading(unsigned int& up,unsigned short& ut);
	int rawToPressure(unsigned int up);
	short rawToTemperature(unsigned short ut);
	int pressureToAltitude(int p);
public:
	/**
	 * Destructor
	 */
	~Pressure();
	/**
	 * Get the pressure, temperature, altitude (in centimeter) of the quadcopter.
	 * 
	 * @return the elements in the returned vector are pressure (of int type), temperature (of short type) and altitude (of int type in centimeter) in sequence.
	 */
	static Vector<double> getReading();
};

#endif