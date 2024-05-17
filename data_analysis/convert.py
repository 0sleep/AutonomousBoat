#! /usr/bin/python3
import math
from datetime import datetime
# Convert logfile format into CSV, with added sensor voltage conversions

# Convert measured voltage to temperature
def conv_temp(vtemp):
    resistance = (1023/(vtemp*255) - 1) * 10000
    rtemp = ((3.3*10000)/vtemp )-10000 #convert measured voltage to resistor, using known second resistor
    # some constants taken from Maciek's maybefinal2.ino program
    R1 = 10000
    beta = 3950
    T1 = 25
    return 1 / (math.log(resistance / R1) / beta + 1 / (T1 + 273.15)) - 273.15;
#Convert measured conductivity to temperature-corrected conductivity
def conv_cond(vcond, temp):
    # constants taken from Maciek's maybefinal2.ino again
    CELL_CONSTANT=353.364
    TEMPERATURE_COEFFICIENT = 0.019
    STANDARD_TEMP = 25
    CONVERSION_FACTOR = 0.64
    # equations adapted from maybefinal2.ino 
    conductivity = vcond * CELL_CONSTANT
    conductivityAtStandardTemp = conductivity / (1+TEMPERATURE_COEFFICIENT*(temp-STANDARD_TEMP))
    tds = conductivityAtStandardTemp * CONVERSION_FACTOR
    return tds

#Convert measured turbidity to ntu
def conv_turb(vturb):
    return 2.65*vturb**2 - 20.26*vturb + 37.86

data = [] # expect list of dicts
with open("BOATLOG") as file:
    f = file.read().split("\n")

for line in f:
    try:
        o = {}
        l = line.split(",")
        for item in l:
            o[item.split(":")[0]] = float(item.split(":")[1])
        data.append(o)
    except:
        print("INVALID LINE")
        print("============")
        print(line)

write_buf = ""
for datapoint in data:
    tstring = datetime.fromtimestamp(int(datapoint["EPOC"])).strftime("%H:%M:%S")
    lat = datapoint["LAT"] / 10000000
    lon = datapoint["LON"] / 10000000
    temp = round(conv_temp(datapoint["TEMP"]), 2)
    cond = round(conv_cond(datapoint["COND"], temp), 2)
    turb = round(conv_turb(datapoint["TURB"]), 2)
    fluo = round(datapoint["FLUO"], 2)
    write_buf += f"{tstring},{lat},{lon},{temp},{cond},{turb},{fluo}\n"
with open("OUTFILE.csv", "w") as file:
    file.write(write_buf)
