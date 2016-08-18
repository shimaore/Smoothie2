/*
      This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
      Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
      Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
      You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
 */



#ifndef ADC_H
#define ADC_H

#include "PinNames.h" // mbed.h lib
#include "mbed.h"
#include "libs/ADC/BurstADC.h"

#include <cmath>
#include <algorithm>

class Pin;

// 2 bits means the 10bit ADC is 12 bits of resolution
#define OVERSAMPLE 2

class Adc {
public:
	Adc();
	void enable_pin(Pin* pin);
	unsigned int read(Pin* pin);

	static Adc *instance;

	//AnalogIn* analogin;		//TODO remove

	void new_sample(int chan, uint32_t value);
	// return the maximum ADC value, base is 12bits 4095.
#ifdef OVERSAMPLE
	int get_max_value() const { return 65535 << OVERSAMPLE;}
#else
	int get_max_value() const { return 65535;}    //Assuming 16bit reading from mbed
	//int get_max_value() const { return 4294967296;}    //Assuming 32bit reading from mbed
#endif

private:
	PinName _pin_to_pinname(Pin *pin);
	BurstADC* adc;

	static const int num_channels= 8;
#ifdef OVERSAMPLE
	// we need 4^n sample to oversample and we get double that to filter out spikes
	static const int num_samples= powf(4, OVERSAMPLE)*2;
#else
	static const int num_samples= 8;
#endif

	// buffers storing the last num_samples readings for each channel
	uint16_t sample_buffers[num_channels][num_samples];

};



#endif
