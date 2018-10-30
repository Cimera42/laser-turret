#include <Adafruit_SoftServo.h>

// #include <Arduino.h>
// #include <Servo.h>

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

	// void change()
	// {
	// 	digitalWrite(pin, on);
	// }
};

struct SERVO
{
	Adafruit_SoftServo servo;
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
	// int16_t lastClick, click;

	void set(uint8_t inXPin, uint8_t inYPin)//, uint8_t inClickPin)
	{
		xPin = inXPin;
		yPin = inYPin;
		// clickPin = inClickPin;

		// click = false;
		// lastClick = false;

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

		// lastClick = click;
		// click = !digitalRead(clickPin);
	}
};

SERVO servo1;
SERVO servo2;
JOYSTICK joystick;
GENERIC_DIGITAL laser;
bool lastButton, button;

void setup()
{
	// Serial.begin(9600);
	servo1.set(0);
	servo2.set(1);
	joystick.set(A2, A3);
	// pinMode(0, OUTPUT);
	// pinMode(1, OUTPUT);
	// pinMode(2, OUTPUT);
	// pinMode(3, OUTPUT);
	// pinMode(4, OUTPUT);
	OCR0A = 0xAF;            // any number is OK
	TIMSK |= _BV(OCIE0A); // Turn on the compare interrupt (below!)

	laser.set(2);
	pinMode(laser.pin, INPUT);
	button = HIGH;
	lastButton = HIGH;
}

void loop()
{
	// // Serial.println("cab");
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

	lastButton = button;
	pinMode(laser.pin, INPUT);
	button = digitalRead(laser.pin);
	if(button == LOW && lastButton == HIGH)
	{
		laser.on = !laser.on;
	}
	if(laser.on)
	{
		pinMode(laser.pin, OUTPUT);
	}
	// // Serial.println("Start");
	// // Serial.println(laser.on);
	// // Serial.println(servo1.pos);
	// // Serial.println(servo2.pos);
	// // Serial.println(joystick.x);
	// // Serial.println(joystick.y);

	servo1.move();
	servo2.move();

	delay(20);
}

volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
	// this gets called every 2 milliseconds
	counter += 2;
	// every 20 milliseconds, refresh the servos!
	if (counter >= 20) {
		counter = 0;
		servo1.servo.refresh();
		servo2.servo.refresh();
	}
}
