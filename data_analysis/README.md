# README
This directory contains all data used for final data analysis. BOATLOG is the direct output from the radio logging during the demonstration. I have written a short python script to convert this data into a more useful CSV format (including voltage to sensor reading conversion). This can then be added into software like QGIS for visualisation.

## Maybefinal2
Maciek's sensor program is named maybefinal2.ino. I have included it here for reference. To ensure my conversions were correct, and that I have understood maybefinal2, I modified it and created maybefinal2.cpp, which can be compiled with g++ and outputs a "known-correct" calculation based directly off Maciek's original.
