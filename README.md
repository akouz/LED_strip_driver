# LED_strip_driver
Arduino Mini Pro driving RGB LED strip. 

Runs from 12V 1A power supply. Uses a photoresistor to sense ambient light. At daytime LED strip is off, average current consumption is about 20 mA. At dusk Arduino switches relay on and runs LED patterns for about 4 hours. After that it switches relay off and keeps it off until next dusk. 

PCP size 50x50mm. Relay is Millionspot H500S12. Arduino Mini Pro 5V 16 MHz. Photoresistor 1 MOhm. Enclosure is a 200 ml transparent plastic storage container from www.sistemaplastic.com

Gerber files for PCB fabrication in LED_strip_drv_rev_1_1.zip

Schematic in LED_strip_drv_rev_1_1.pdf

KiCAD project in LED_strip_drv_KiCAD.zip

Arduino sketch uses FastLED, it is in LED_strip_drv_Sketch.zip
