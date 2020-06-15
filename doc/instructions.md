# Instructions

1. Print the plastic front for holding the ultrasonic sensor on a 3D printer.
2. Solder on the short female headers to the Feather M0. The female headers should be soldered facing upwards (i.e. the headers and components are on the same side). 
3. Wire up the ultrasonic sensor to the Feather and run a test to check proper function of the sensor and the feather. 

Note that the SRF05 sensor requires 5V power and the Feather runs on 3.3V. While the Trig signal can be 3V or 5V, the ‘return’ Echo signal is 5V logic. As the Feather can only handle 3.3V, use the two resistors as a divider to convert the 5V logic level to a safe 2.5V. Be careful with wiring up to prevent damage to the Feather.

4. Connect the SRF05 GND to a GND pin of the Feather M0,
5. Connect the second GND pin of the Feather M0 to a Jetson Nano GND pin,
6. Connect the SRF05 VCC to the 5V power pin of the Jetson Nano,
7. Connect the SRF04 TRIG pin to pin 11 of the Feather M0,
8. Connect the SRF04 ECHO via a divider bridge (using the two resistors) to pin 12 of the Feather M0.

If done correctly, your test assembly should resemble something like the breadboard lay-out as shown.

![breadboard](https://github.com/thestrongestlink/ultrasonic-jetbot/blob/master/doc/images/ultrasonic_M0_feather_bb.png?raw=true)

9. Start up the Jetson Nano so that 5V is provided to the sensor, hook up a USB cable between the feather and your computer and upload the source code ultrasonic_ic.c using the Arduino IDE.
10. When uploading is completed, open the Arduino Monitor. Hold your hand in front of the sensor and the distance between the sensor and your hand should be displayed in the monitor. Move your hand closer and further away from the ultrasonic sensor and note the changing readout on the monitor. 
11. Switch off power on both Jetson Nano and the Feather M0. 
12. Temporarily disconnect the I2C connection to the motor driver from pins 3 and 5 of the Jetson Nano (remember their positions!).
13. Make an I2C connection between the Jetson Nano and the Feather M0. You do this by connecting the SCL pin of the Feather M0 with the SCL pin of the Jetson Nano (pin 5) and connecting the SDA pin of the Feather M0 with the SDA pin of the Jetson Nano (pin 3). 
14. Power up again and once the Jetbot software has loaded, connect to the JupyterLab interface on your computer and create a new python session. 
15. Upload the short Python test script ultrasonic_test.py to JupyterLab.
16. Start the script by pressing shift-enter in JupyterLab and you should see the result of a distance measurement every second. Try holding and moving your hand at several distances from the ultrasonic sensor and note that the reported distance changes in the JupyterLab output. 

If everything works as described, you now have a working distance measurement system communicating with the Jetbot over I2C.

17. Unscrew the DC motor driver Feather Wing from the Jetbot and disconnect the jumper wires from the Feather M0 microcontroller. 
18. Desolder the 2-pin and 3-pin headers on the motor driver, move these headers to the inner rows of the DC motor driver board same pins and resolder. 
19. Solder an additional 2-pin header to pins 11 and 12 of the DC motor driver board using the inner rows, and solder a 1-pin header to the second GND of the DC motor driver board. 
20. Solder the new short male headers strips to the bottom of the DC motor driver board. 
21. Position the M0 Feather on the location of the motor driver and secure in place using the micro screws that where used to hold the motor driver in postion.
22. Fasten the ultrasonic sensor to the 3D printed front using two micro screws. 
23. Connect the jumper wires to the sensor if required and then fasten the 3D printed front to the Jetbot using two micro screws in the top holes of the 3D printed front.
24. Fix the motor driver Feather Wing in place on top of the M0 Feather by inserting the short male headers into the short female headers and re-attach the jumper wires in their original positions. 
25. Connect the ECHO and TRIG pins of the ultrasonic sensor to the 2-pin header (pins 11 and 12) of the motor driver Feather Wing.
26. Connect the GND pin of the ultrasonic sensor to the second GND single header pin on the motor driver. 
27. Route the 5V jumper wire from the sensor to the 5V pin of the Jetson Nano. Reconnect the I2C wires you disconnected from the Jetson Nano earlier. 
28. Check all your wiring one last time and power up the Jetbot, open the JupyterLab environment on your computer and try the ultrasonic_drive.py Python Script to prove the integration has been succesful.

If all’s well, your Jetbot should now be cruising along the floor and once it encounters a wall it will back up a little bit, make a left turn and will then continue it’s journey. More information can be found at https://thestrongestlink.nl. 

