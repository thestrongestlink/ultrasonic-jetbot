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
