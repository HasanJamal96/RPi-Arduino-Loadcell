import serial, time
from datetime import datetime
import RPi.GPIO as GPIO
from picamera import PiCamera

camera = PiCamera()
BTN_PIN = 27

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(BTN_PIN, GPIO.OUT, initial=GPIO.LOW)


ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
ser.reset_input_buffer()


def TakeIamge(ID):
    x = datetime.now()
    filename = '/home/pi/Pictures/' + x.strftime("%Y_%m_%d_%H_%M_%S_")
    filename += ID + ".jpg"
    camera.capture('')


def WaitSerial():
    time.sleep(1)
    while(ser.in_waiting == 0):
        pass
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
        return line
    return ''


def SendData(txt):
    send_string = (txt)
    ser.write(send_string.encode('utf-8'))


if __name__ == '__main__':
    
    while True:
        if(GPIO.input(BTN_PIN)):
            SendData("start\n")
            payload = WaitSerial()
            if("weight" in payload):
                print("Weight:", payload[7:-1])
                SendData("weigth done\n")
                payload = WaitSerial()
                if("moved,1/4" in payload):
                    TakeIamge('1')
                    SendData("image 1\n")
                    payload = WaitSerial()
                    if("moved,2/4" in payload):
                        TakeIamge('2')
                        SendData("image 2\n")
                        payload = WaitSerial()
                        if("moved,3/4" in payload):
                            TakeIamge('3')
                            SendData("image 3\n")
                            payload = WaitSerial()
                            if("moved,4/4" in payload):
                                TakeIamge('4')
                                SendData("image 4\n")
                                print("Complete")
                            else:
                                print("failed")
                        else:
                            print("failed")
                    else:
                        print("failed")
                else:
                    print("failed")
            else:
                print("failed")



GPIO.cleanup()
SendData("failed\n")
