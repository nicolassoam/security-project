
import sys
import os
import random 
from datetime import datetime
startTime = datetime.now()

random.seed(30)

def hashCalculator():
    # concat 0 to end of file
    rand = random.randint(1, 5000)
    os.system("echo "+ str(rand) + " >> lorem_crypt.enc")

def checkZero():
    sha256sum = os.popen("sha256sum lorem_crypt.enc").read()
    hash0 = sha256sum.split()[0]
    i = 0

    while (hash0[:5] != "00000"):
        hashCalculator()
        # os.system("time sha256sum lorem_crypt.enc")
        sha256sum = os.popen("sha256sum lorem_crypt.enc").read()
        hash0 = sha256sum.split()[0]    
    print(hash0)
    os.system("echo Execution time for four zeroes: " + str(datetime.now() - startTime) + ">> times.txt")

hashCalculator()
checkZero()