I decoded SBAS broadcast navigation messages. SBAS is a regional 
network of ground and satellite system that works to boost the accuracy and dependability of GPS and GNSS 
data. The increased accuracy is critical for aviation and is widely used by the geospatial industry for increased 
accuracy in navigation and mapping. SBAS uses stationary land based GNSS monitors to calculate GNSS 
position errors caused by atmospheric and ionospheric disturbances, satellite orbit errors, and inaccurate clocks. 
Each of these errors causes delays in timing, which result in position errors for a receiver. To calculate GNSS 
position errors, GNSS data from satellites are compared against the precisely documented locations of each 
land-based monitor. Any discrepancy is determined to be an error. Corrections to the errors are sent to 
geostationary satellites and broadcast throughout the region. These SBAS corrections – called deviation 
corrections – allow GNSS receivers to more accurately and reliably determine their position. GNSS is normally 
accurate to around five meters. Using SBAS, users can achieve an accuracy of two meters or better. Some 
receivers can apply SBAS corrections with additional techniques to achieve sub-meter or better accuracy.
There are more than one SBAS system currently operating in the world. There are a total of 7 different 
systems expected to be operational by the end of 2022. They are named WAAS over North America, EGNOS in 
Europe, GAGAN in India, MSAS in Japan, SDCM in Russia, BDSBAS in China, and finally KASS in Korea. 
The satellites that make up the Sbas systems are geostationary, that is, the satellites whose positions are fixed 
relative to the earth. Therefore, the location information in the incoming data changes very little or remains 
constant. Due to its location, Turkey can receive data using EGNOS satellites, which are the SBAS system 
located over Europe. EGNOS provides service with a total of three satellites, two of which are active, and one is 
in the testing phase. In the satellite data coming to the GNSS receiver, data comes from only two active 
satellites. However, since position estimation cannot be made with two satellites, the SBAS system should be 
used with other satellite constellations. The purpose of this project is to analyze and make sense of incoming 
SBAS broadcast navigation messages. Location estimations are made using these meaningful messages. Thus, 
using different satellite constellations, we ensure that we have the correct data to estimate where a vehicle that 
has been subjected to jamming is located.
The project was first written on the analysis and interpretation of the .ubx file containing the navigation 
messages. It was later modified to run in real time. It instantly parses the data coming from the GNSS receiver 
and stores it in the necessary data structures. While reading the binary format file, I used a function that takes 
parameters as a template to accept different data types. Thus, a byte or two bytes were read correctly in one 
function. Then, by looking at the values I read, I found which message type it was and sent it to the required 
function to set the message. As soon as we have enough ephemeris data, I call a function to print it. I created an 
array that stores all message types for each satellite. As the messages came, I updated the array by overwriting 
the old message.
The required data is in the SBAS RINEX file. These data are printed in .txt file in tab format. The 
accuracy of the data was checked from the RINEX file published by NASA and no errors were found. The 
location estimation using the generated .txt file gave correct results.
