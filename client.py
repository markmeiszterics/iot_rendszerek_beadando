import serial

# serial
s = serial.Serial('COM3', 9600)

while True:
    if s.in_waiting > 0:
        adat = s.readline().decode().rstrip()

        if adat == "attack":
            print("Behatolas!")
        elif adat == "secured":
            print("Kiriasztva!")
        else:
            print("Adatok: ", adat)
        #getPin
        pin = input("Ird be a PIN kodot: ")
        s.write(pin.encode() + b'\n')
