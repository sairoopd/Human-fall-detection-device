# Human-fall-detection-device
A wireless human fall detection device that is designed and built using machine learning.

The most challenging part of building a human fall detection device is reducing errors and detect only an actual fall.
Inorder to be able to accurately detect a fall, a lot of sensor reading data needs to be collecetd from various scenarios of human falls.
This data can be visualized and processed in MATLAB using machine learning algrithms like finite tree and SVM. 
Applying these algorithms to collected data will give threshold values in which a fall can happen.
These threshold values are called the upper fall threshold (UFT) and the lower fall threshold (LFT).
After obtaining the UFT and LFT values, they can be incorporated into the software of the device to prdict human falls with higher accuracy.

The sensor used for fall detection is the MPU6050 3- axial Accelerometer/gyroscope.

Acceleration along X, Y, Z axis are denoted as x, y and z respectively.

Acc (resultant acceleration) = √(𝑥2 + 𝑦2 + 𝑧2)

Gyroscope along X, Y, Z axis are denoted as x, y and z respectively

Gyro (resultant acceleration) = √(𝑥2 + 𝑦2 + 𝑧2)

The lower and upper fall thresholds for the acceleration and angular velocity used to identify the fall are derived as follows:

>>>Lower fall threshold (LFT): the negative peaks for the resultant of each recorded activity are referred to as the signal lower peak values (LPVs). The LFT for the acceleration signals are set at the level of the smallest magnitude lower fall peak (LFP) recorded.

>>>Upper fall threshold (UFT): the positive peaks for the recorded signals for each recorded activity are referred to as the signal upper peak values (UPVs). The UFT for each of the acceleration and the angular velocity signals were set at the level of the smallest magnitude UPV recorded. The UFT is related to the peak impact force experienced by the body segment during the impact phase of the fall.

The UFT and LFT values are calculated for both the accelerometer and the gyroscope in the sensor.

During a fall event, the acceleration signal decreases from 1 g to go below the LFT value and within 0.5 s, acceleration and angular velocity increase to cross above UFTacc and UFTgyro, almost simultaneously. With rigorous activities such as running, the peak of accelerations can reach critical LFTacc and UFTacc thresholds indicative of a fall event. But, the confirmatory UFTgyro threshold is never reached. For events such as lying down or sitting up, the threshold is triggered, but the acceleration conditions are not met. Thus, the combination of accelerometer and gyroscope sensor system complement one another for a more robust fall detection algorithm.
