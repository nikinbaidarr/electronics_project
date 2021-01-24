
# PIN Config Arduino UNO

Arduino has 14 digital I/O pins out of which 6 can be used as PWM
outputs, 6 analog input pins, a USB connection, a power barrel jack, a
3.3V out pin, a 5V out pin, a Vin pin, 3 to 5 ground pins, an IOREF
pin, a reset pin and 6 IPSC pins to change the device's firmware.

[PIN diagram of Arduino UNO](https://www.google.com/search?q=arduino+UNO+pin+diagram&source=lnms&tbm=isch&sa=X&ved=2ahUKEwjF85Pv9LTuAhXijeYKHXyfDI4Q_AUoAXoECBAQAw&biw=1366&bih=670#imgrc=CS8mURVF_yLEGM)
## Powering an Arduino

Arduino board should be powered with 5-20 volts supply but it is
usually recommended to keep the supply in between 7 to 12 volts.
Above 12 volts, the regulators might overheat, and below 7 volts, the
microcontroller might not function properly.

An arduino can be powered in 3 different ways:

1. Using the power barrel jack, the DC barrel jack is connected to a
   battery, usually via. a snap connector.

[Snap Battery Connection](https://www.google.com/search?q=snap+battery+arduino&tbm=isch&ved=2ahUKEwinv6-E9bTuAhW-5nMBHUoaB6AQ2-cCegQIABAA&oq=snap+battery+arduino&gs_lcp=CgNpbWcQAzoECAAQHjoGCAAQBRAeOgYIABAIEB5Q1ChYxy9glDJoAHAAeAGAAasCiAHkCZIBBTAuNy4xmAEAoAEBqgELZ3dzLXdpei1pbWfAAQE&sclient=img&ei=KZYNYOeGI77Nz7sPyrScgAo&bih=670&biw=1366#imgrc=HDkjAG43PrtutM)

2. Using the USB port, which can be connected to a PC via a USB cable.

3. Using the Vin pin, to which an external power source can be
   connected.

The power source used determines the current that drives the entire
circuit. For instance, powering the board using the USB cable limits
the power up to only 500mA. This power is used to power the MCU
itself, its peripherals, the on-board regulators and all the
components connected to it.

### Powering External Circuit Components

The 5V pin and the 3V3 pin provides a regulated 5 and 3.3 volt supply
that powers external components based on their specifications.

## GND, RST and IOREF

In an arduino UNO, there can be multiple ground pins from 3 to 5 GND
pins, which are all interconnected. These GND pins are used to close
all the electrical circuits.

The RST pin is used to reset the arduino.

The IOREF pin is the I/O reference pin and it provides the voltage
reference with which the microcontroller operates.

## Analog Pins

Arduino UNO has 6 analog pins labelled from A0 to A5. All of these
pins utilize Analog to Digital conversion. These pins serve as input
pins for analog signals from sensors or other such devices.
Nonetheless, these pins can also be used as digital inputs or digital
output pins.

The AREF pin is used as the reference voltage for the analog inputs.

### Analog to Digital Conversion

The analog signals read by these pins are converted into digital
signals. This digital representation of analog signals allows the MCU
(a digital device) to effectively measure the analog signal and
process it.

A 10-bit resolution ADC is used in arduino UNO, which converts the
analog voltage into bits which the microprocessor can interpret. 10
bit resolution means that the analog voltage can be represented by
1024 binary digits.

## Digital Pins

Pins 0 through 13 of the Arduino UNO serve as digital I/O pins.

Pins 3,5,6,9,10,11 have PWM capabilities. Nonetheless, each of these
pins can be used as normal I/O pins as well. PWM signals are used for
speed control of DC motors, dimming LEDs and more. PWM is further
explained [[#Pulse Width Modulation (PWM)|here]].

It is important to take into consideration that:

• Each pin can provide or sink only up to 40mA max. The recommended
  current is 20mA.

• The maximum current provided or sank from all the pins together is
  200mA.

The digital pins at any given time remain at either of the two states,
ON or OFF. When ON, the pins are in a High voltage state of 5V and
when OFF, they are in a Low voltage state of 0V.

So when the digital pins are configured as output, they are either set
to 0 or 5 volts.

When these digital pins are configured as input, the voltage is
supplied from an external device. This external voltage can vary
anywhere between 0 to 5 volts which is concerted into digital
representation. Voltages below 0.8V are considered as 0 and voltages
above 2V are considered 1. The voltages between 0.8V and 2V are
undefined, therefore when connecting a component to an i/p digital
pin, it is important to make sure that the logic is matched.

### Pulse Width Modulation (PWM)

Pulse width modulation or pulse-duration modulation, is a method of
reducing the average power delivered by an electrical signal by
effectively chopping it up into discrete parts.

A PWM is comprised of two key components: frequency and duty cycle.
The PWM frequency dictates how long it takes it to complete a single
cycle and how quickly the signal fluctuates from high to low. The duty
cycle determines how long a signal stays high out of the total period.

The duty cycle describes the proportion of 'on' time to the regular
interval or period of time.

Duty cycle is expressed in percent, 100% being fully on. When a
digital signal is on half of the time and off the other half, it has a
duty cycle of 50% and resembles a 'square' wave. When a digital signal
spends more time in the on state than the off state, it has a duty
cycle of >50%. When a digital signal spends more time in the off state
than the on state, it has a duty cycle of <50%. A low duty cycle
corresponds to low power, because the power is off for most of the
time.

In arduino UNO, the PWM enabled pins produce a constant frequency of ~
500Hz, while the duty cycle changes according to the parameters set by
the user.

### Serial Communication

Serial communication is used to exchange data between the Arduino
board and another serial devices such as computers, displays, sensors
and more. Serial communication can be undertaken through either
hardware or software.

Hardware Serial communication is pretty much straightforward and
occurs via the USB (Universal SERIAL Bus) port.

Arduino also supports software serial communication through digital
pins 0 (Rx) and 1 (Tx) using a pin-change interrupt. (whatever the
fuck that means...). SoftwareSerial library is a built-in library for
software serial communication. Software serial communication allows
the processor to stimulate extra serial ports. Meaning, it allows
connection of multiple serial-communication devices and leave the main
serial port for a USB connection.

The drawback of software serial communication is that it requires more
processing and it is a bit slower than hardware serial communication.

### Communication Protocols

#### Serial Peripheral Interface

SPI is a synchronous serial communication interface specification
(basically a protocol) used by microcontrollers for short-distance
communication with one or more external devices in a bus like
connection. (A bus is basically a high speed internal connection used
to send control signals and data between the processor and other
components. Kind of like how a literal bus carries passengers from one
point to another point in space.)

On an SPI bus, there is always one device there is always one device
that is denoted as a Master device and the rest are all slaves. In
most general cases, the microcontroller itself is the master.

The digital pins ~10 (SS), ~11(MOSI), 12 (MISO), 13 (SCK) are SPI
enabled.

• The SS (Slave Select) pin determines which device the master is
  currently communicating with.

• MISO (Master In Slave Out) is a line for sending data to the master
  device from the slaves.

• MOSI (Master Out Slave In) is a line for sending data to
  peripheral device from the master.

• SCK (Serial Clock) A clock signal generated by the master device to
  synchronize data transmission.

#### I2C

I2C is a serial communication protocol that ensures data is
transferred bit by bit along a single wire. Like SPI, I2C is
synchronous, so the output of bits is synchronized to the sampling of
bits by a clock signal shared between the master and slave.

The I2C utilizes a single data line to transmit data and another clock
line to synchronize the data transmission.

## ICSP Pins

ICSP stands for In-circuit Serial Programming. ICSP headers allow
coders to program the Arduino's  firmware. (Firmware is a software
program that is permanently programmed into a hardware device.
Examples keyboard, remote controls. Firmwares are essentially
permanent instructions to communicate with other devices and perform
basic I/O tasks.) There are six ICSP pins available on the chassis
that can be hooked to a programming device via a programming cable.
