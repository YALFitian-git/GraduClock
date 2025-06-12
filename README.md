# GraduClock
GraduClock is an ESP32-based project which serves as a countdown clock to a pre-set timestamp.

# How It Works
The ESP32 connects to an access point (via pre-set credentials), then gets the current timestamp via NTP server, subtracts it from the pre-set timestamp, is divided multiple times into days, hours and minutes, which are then displayed on an OLED.