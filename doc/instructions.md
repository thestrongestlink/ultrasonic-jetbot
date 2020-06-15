# Instructions

Start with printing of the front and soldering on the short female headers to the Feather M0. The female headers should be soldered facing upwards (i.e. the headers and components are on the same side). Next, we’ll wire up the ultrasonic sensor to the Feather and run a test to check proper function of the sensor and the feather. Note that the SRF05 sensor requires 5V power and the Feather runs on 3.3V. While the Trig signal can be 3V or 5V, the ‘return’ Echo signal is 5V logic. As the Feather can only handle 3.3V, use the two resistors as a divider to convert the 5V logic level to a safe 2.5V. Be careful with wiring up to prevent damage to the Feather.

Connect the SRF05 GND to a GND pin of the Feather M0,
Connect the second GND pin of the Feather M0 to a Jetson Nano GND pin,
Connect the SRF05 VCC to the 5V power pin of the Jetson Nano,
Connect the SRF04 TRIG pin to pin 11 of the Feather M0,
Connect the SRF04 ECHO via a divider bridge (using the two resistors) to pin 12 of the Feather M0.
If done correctly, your test assembly should resemble something like the breadboard lay-out as shown.

Breadboard lay-out for ultrasonic sensor and feather M0 testing

Start up the Jetson Nano so that 5V is provided to the sensor, hook up a USB cable between the feather and your computer and upload the source code ultrasonic_ic.c using the Arduino IDE.

When uploading is completed, open the Arduino Monitor. Hold your hand in front of the sensor and the distance between the sensor and your hand should be displayed in the monitor. Move your hand closer and further away from the ultrasonic sensor and note the changing readout on the monitor. Once you have this functioning, we’re ready for the next step; interfacing with the Jetson Nano using I2C.

Switch off power on both Jetson Nano and the Feather M0. Now temporarily disconnect the I2C connection to the motor driver from pins 3 and 5 of the Jetson Nano (remember their positions!) and make an I2C connection between the Jetson Nano and the Feather M0. You do this by connecting the SCL pin of the Feather M0 with the SCL pin of the Jetson Nano (pin 5) and connecting the SDA pin of the Feather M0 with the SDA pin of the Jetson Nano (pin 3). Now power up again and once the Jetbot software has loaded, connect to the JupyterLab interface on your computer and create a new python session. Upload the short Python test script ultrasonic_drive.py to JupyterLab

Start the script by pressing shift-enter in JupyterLab and you should see the result of a distance measurement every second. Try holding and moving your hand at several distances from the ultrasonic sensor and note that the reported distance changes in the JupyterLab output. If everything works as described, you now have a working distance measurement system communicating with the Jetbot over I2C.

All we need to do now is to integrate the ultrasonic sensor and the Feater M0 microcontroller with the Jetbot. Start with unscrewing the DC motor driver Feather Wing from the Jetbot and disconnecting the jumper wires from the Feather M0 microcontroller. Desolder the 2-pin and 3-pin headers on the motor driver, move these headers to the inner rows of the DC motor driver board same pins and resolder. Solder an additional 2-pin header to pins 11 and 12 of the DC motor driver board using the inner rows, and solder a 1-pin header to the second GND of the DC motor driver board. Next, solder the new short male headers strips to the bottom of the DC motor driver board. Position the M0 Feather on the location of the motor driver and secure in place using the micro screws that where used to hold the motor driver in postion.

Fasten the ultrasonic sensor to the 3D printed front using two micro screws. Connect the jumper wires to the sensor if required and then fasten the 3D printed front to the Jetbot using two micro screws in the top holes of the 3D printed front.

Now fix the motor driver Feather Wing in place on top of the M0 Feather by inserting the short male headers into the short female headers and re-attach the jumper wires in their original positions. Connect the ECHO and TRIG pins of the ultrasonic sensor to the 2-pin header (pins 11 and 12) of the motor driver Feather Wing, and connect the GND pin of the ultrasonic sensor to the second GND single header pin on the motor driver. Route the 5V jumper wire from the sensor to the 5V pin of the Jetson Nano. Reconnect the I2C wires you disconnected from the Jetson Nano earlier. Once finished, it should resemble the picture below. Note that I had to bend the 2-pin and 3-pin headers 90 degrees to allow sufficient ground clearance. Tidy up the jumper wires as good as you can and check whether it resembles (or looks better!) than the picture below. Note the I2C wires at bottom right of the Feather Wing, the TRIG and ECHO wires of the sensor in the middle right and the GND wire of the sensor at the bottom left.

Check all your wiring one last time and power up the Jetbot, open the JupyterLab environment on your computer and try following Python Script to prove the integration has been succesful:

from jetbot import Robot
import smbus
import time

robot = Robot()
bus = smbus.SMBus(1)
address = 8 # I2C address for Ultrasonic bus

def distance():
    """Returns distance measured by ultrasonics in cm"""
    return bus.read_byte_data(address, 0)

while True:
    if (distance() < 20):
       robot.backward(0.4)
       time.sleep(0.6)
       robot.left(0.4)
       time.sleep(0.5)
    else:
       robot.forward(0.4)
If all’s well, your Jetbot should now be cruising along the floor and once it encounters a wall it will back up a little bit, make a left turn and will then continue it’s journey. You will probably note that this will only work correctly when the Jetbot is more or less perpendicular to the wall. When the Jetbot is moving at shallow angles (almost in parallel) with the wall, the ultrasonic beams will bounce of the wall away from the Jetbot and the Jetbot will not pick up a return signal from the sensor. But for me, this solution works for moving around the room than trying to get the AI system to recognize my walls. I find it also a more efficient method (in terms of computing power and power consumption) for basic navigation in a room. I hope you enjoyed my blog and perhaps even managed to replicate my little experient as well. I would love to have your feedback and thoughts on this subject.
