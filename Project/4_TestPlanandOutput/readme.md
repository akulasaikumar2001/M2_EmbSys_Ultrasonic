# TEST PLAN AND OUTPUT
Test plan is created and verified on both manually as well as Automative.

## High level Test Plan
|Test ID|Description|Input|Expected output|Actual Output|
|:------:|:-----:|:------:|:----------:|:------------:|
|01|LCD Display|Data from MCFS|Displays Amount of Dust stored/level|✓|
|02|Servo Motor|Data from MCFF|Shall change position of SVC|To be done|
|03|Ultrasonic Sensor|Data from Microcontroller|Detect Obstacle upto 4m|To be done|
|04|Level Sesnor|Data from Microcontroller|Give signal when Tanks gets full|To be done|
|05|Bluetooth|Connect from users module|Receive command to perform operations|To be done|
_____________________________________________________________________
## Low level Test Plan
| Test ID (for LCD)| Description | Input | Expected output | Actual Output | passed/not |
| --- | --- | --- | --- | --- | --- |
| 01 | Check for LCD_Char() | N  | N |  N | ✓ |
| 02 | Check for LCD_String() | automation | automation |  automation | ✓ |
| 03 | Check for LCD_String() | Home | Home | Home | ✓ |