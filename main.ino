#include <Arduino.h>
#include <Servo.h>

struct GENERIC_DIGITAL
{
	bool on;
	uint8_t pin;

	void set(uint8_t inPin, bool inOn = false)
	{
		pin = inPin;
		pinMode(pin, OUTPUT);

		on = inOn;
	}

	void change()
	{
		digitalWrite(pin, on);
	}
};

struct SERVO
{
	Servo servo;
	int pos;
	int oldPos;

	void set(int inPin)
	{
		servo.attach(inPin);
		pos = 90;
		oldPos = -1;
		move();
	}

	void move()
	{
		if (pos != oldPos)
			servo.write(pos);
		oldPos = pos;
	}
};

struct JOYSTICK
{
	uint8_t xPin, yPin, clickPin;
	int lastX, x;
	int lastY, y;
	int16_t lastClick, click;

	void set(uint8_t inXPin, uint8_t inYPin, uint8_t inClickPin)
	{
		xPin = inXPin;
		yPin = inYPin;
		clickPin = inClickPin;

		click = false;
		lastClick = false;

		x = 0;
		lastX = 0;

		y = 0;
		lastY = 0;
	}

	void read()
	{
		lastX = x;
		x = analogRead(xPin) - 512;

		lastY = y;
		y = analogRead(yPin) - 512;

		lastClick = click;
		click = !digitalRead(clickPin);
	}
};

SERVO servo1;
SERVO servo2;
JOYSTICK joystick;
GENERIC_DIGITAL laser;

void setup()
{
	Serial.begin(9600);
	servo1.set(3);
	servo2.set(5);
	joystick.set(A0, A2, 0);
	laser.set(7);
}

void loop()
{
	// Serial.println("cab");
	joystick.read();

	if(abs(joystick.x) > 50)
	{
		float normalX = joystick.x / 512.0f;
		servo1.pos = servo1.pos - normalX * 3;
		servo1.pos = max(0, min(180, servo1.pos));
	}
	if(abs(joystick.y) > 50)
	{
		float normalY = joystick.y / 512.0f;
		servo2.pos = servo2.pos + normalY * 3;
		servo2.pos = max(0, min(180, servo2.pos));
	}
	if(joystick.click && joystick.click != joystick.lastClick)
	{
		laser.on = !laser.on;
		laser.change();
	}
	// Serial.println("Start");
	// Serial.println(laser.on);
	// Serial.println(servo1.pos);
	// Serial.println(servo2.pos);
	// Serial.println(joystick.x);
	// Serial.println(joystick.y);

	servo1.move();
	servo2.move();

	delay(20);
}
