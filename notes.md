# Notes

## GNSS thread
Purpose: configure and provide current GNSS position in the position struct
Status: Implemented as loc_thread.h

## Radio thread
Purpose: take messages from the radio to-send queue and send them using the nRF. If radio transmission fails, retry. Only then take the next message from the queue
Status: Implemented as radio_thread.h

## Navigation thread
Purpose: take current position and heading, calculate ideal heading and heading error. Use PID controller to set motor speeds
Helper functions:
  * get heading
  * calculate ideal heading (Note magnetic north pole != north pole, earth curvature issues etc)
Status: Not Implemented

## Measurement thread
Purpose: take periodic measurements and submit them to the radio to-send queue along with a timestamp and the current location
Status: Not Implemented
