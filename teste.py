import speech_recognition as sr
import serial

ser = serial.Serial('/dev/ttyACM0')
r = sr.Recognizer()
m = sr.Microphone()

try:
    with m as source: r.adjust_for_ambient_noise(source)
    while True:
            with m as source: audio = r.listen(source)
            try:
                value = r.recognize_google(audio)
                if str is bytes:
                    print(u"{}".format(value).encode("utf-8"))
                    ser.write(b"{}".format(value).encode("utf-8"))
                else:
                    print(u"{}".format(value))
                    ser.write(value.encode())
            except sr.UnknownValueError:
                print("I didn't get what you said :(")
except KeyboardInterrupt:
    pass
