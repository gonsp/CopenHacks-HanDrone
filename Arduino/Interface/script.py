import serial


arduinoData = serial.Serial('/dev/ttyACM0', 9600);

while(arduinoData.inWaiting() == 0):
  pass

while True:
  data = arduinoData.readline();
  print data;