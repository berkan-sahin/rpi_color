#!/usr/bin/env python3

import time
import posix_ipc as ipc
import signal
from sys import exit

mq = ipc.MessageQueue("/colorRGB", ipc.O_CREAT)

print("/colorRGB üzerinde mesaj bekleniyor...")

def yakala(mq):
    mesaj, _ = mq.receive()
    if(mesaj == "BYE"):
        print("Kuyruk kapandı")
        signal.raise_signal(signal.SIGINT)

    print(mesaj)
    mq.request_notification((yakala, mq))

def temizlik(signum, frame):
    mq.close()
    mq.unlink()
    exit(0)


signal.signal(signal.SIGINT, temizlik)
mq.request_notification((yakala, mq))
signal.pause()
