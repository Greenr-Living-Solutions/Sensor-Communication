import serial

arduino_port = "/dev/cu.usbmodem142301"
baud = 9600
fileName = "sound-data.csv"
samples = 1000000

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
print("Created file")

line = 1

while line <= samples:
    getData = str(ser.readline())
    data = getData[0:][:-2]
    print(data)
    file = open(fileName, "a")
    file.write(data + "\n")
    line = line + 1
file.close()
print("File Complete")
