/*
 * DigitalIoPin.h
 *
 *  Created on: 31.1.2016
 *      Author: krl
 */

#ifndef DIGITALIOPIN_H_
#define DIGITALIOPIN_H_

class DigitalIoPin {
public:
	enum pinMode {
		output,
		input,
		pullup,
		pulldown
	};
	DigitalIoPin(int port, int pin, pinMode mode, bool invert = false);
	virtual ~DigitalIoPin() = default;

	virtual bool read();
	void write(bool value);

	operator bool();
	bool operator=(bool val);

private:
	int port;
	int pin;
};

#endif /* DIGITALIOPIN_H_ */
