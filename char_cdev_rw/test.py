import os

dev=os.open("/dev/char_cdev_rw",os.O_RDWR)

n = os.write(dev,b"My World")
print(n)

readBytes = os.read(dev,n)
print(readBytes)

os.close(dev)

