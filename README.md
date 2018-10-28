# laser-turret
An Arduino UNO controlled laser pointer.

## Software

This project was programmed using the VSCode editor.

Setting files for the [Arduino extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) are included.

## Hardware

### Electronics Parts

- 1x Arduino UNO
- 2x Tower Pro SG90 servos
- 1x Laser diode
- 1x Joystick module

### 3D Printed parts
3D Design files were created using [Solvespace](http://solvespace.com/index.pl).

- `attach.slvs`: servo shaft mount
- `laserMount.slvs`: attachment for laser diode board with screw holes
  - `attachWithLaserMount`: `laserMount` with servo shaft mount
- `servoMount.slvs`: attachment for servo with screw holes
  - `attachWithServoMount`: `servoMount` with servo shaft mount
- `screwtest.slvs`: test piece for finding ideal screw hole size

## Pin IO

**Output:** \
3: X Servo \
5: Y Servo \
7: Laser diode

**Input:** \
0: Joystick click \
A0: X Joystick \
A2: Y Joystick

## Basic Function

The joystick controls the servos for vertical and horizontal movement. Clicking in the joystick toggles the laser output.

## Future

Potential future expansions:
- Smaller processor
  - ATTiny85: current limitation in number of pins, 1 too few for joystick click input
    - See [here](http://www.technoblogy.com/show?LSE) for how to use 1 pin for input and output.

- RC

- Wheeled platform