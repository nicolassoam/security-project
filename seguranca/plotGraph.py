import matplotlib.pyplot
import os
import datetime
# plot the graph with execution times of the hash decryption
def plotDecrypt():
    file = open("times.txt", "r")
    lines = file.readlines()
    file.close()
    x = []
    y = []
    for line in lines:
        line = line.split(':')
        time = line[2] +":" + line[3] 
        time = datetime.datetime.strptime(time[:-1], '%M:%S.%f')
        x.append(line[0])
        y.append(time)
    matplotlib.pyplot.plot(x, y)
    matplotlib.pyplot.xlabel('Hash')
    matplotlib.pyplot.ylabel('Time')
    matplotlib.pyplot.title('Hash Decryption Times')
    matplotlib.pyplot.show()
plotDecrypt()