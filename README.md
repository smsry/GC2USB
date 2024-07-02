# GC2USB
This is a simple Adapter made from just an Arduino Pro Micro to use Gamecube controllers natively on PC using XInput.

<p align="center">
  <img width="240" height="320" src="https://github.com/smsry/GC2USB/blob/main/Images/1.jpg">
</p>

Allows a Gamecube controller to show up as an Xbox Controller on Windows(or any device really) with Rumble Support!

- Uses Nicohood's Nintendo Library to get data from the Gamecube controller's 3.3v logic pin
- Converts the incoming traffic from the controller into XInput using the ArduinoXInput library
- REQUIRES Xinput USB Core to be flashed prior to uploading this code to your chip. (lookup ARDUINO XINPUT AVR)
- Needs a Logic converter if using a 5v Pro Micro as the GC Controller only sends and recieves 3.3v logic

Nicohood's Nintendo Library DOES have an example code that allows you to directly use an unmodified Gamecube Controller as a HID Device in Windows, so technically it can be used for Dolphin/Ryujinx Emulation as is.
But his HID Library doesnt have Rumble support yet.

So this is a simple way to correct that. The XInput Library has Rumble support, so my code takes the GC Controller inputs and translates them into XInput.

As this acts as an Xbox Controller, it can also be used in any Game that accepts an Xbox Controller and Rumble should work as normal. 

 ### Things to Note:

- As the GC Controller just has one vibration motor, and a typical Xinput setup requires a Big motor and a small motor, you can choose to send only the big motor's signal to the GC Controller, or both. I just chose both as I didnt know how choosing one over the other would effect Rumble in Dolphin.
- Another thing regarding Vibration, because the Nintendo Library just uses a bool value for Controller Rumble, there isnt ant PWM modulation going to the motor, so the motor will vibrate at full 5v all the time.
- Also MAKE SURE YOU WIRE A SEPERATE GROUND IF YOU WANT RUMBLE TO WORK. learned this the hard way but the grounds in a Gamecube controller are'nt common. One of them is exclusively used for Rumble. For me it was the White wire, could be different depending on the controller
- Because the way the Gamecube controller has analog Triggers as well as buttons, that's not exactly possible with XInput as you have an option of either choosing Triggers as buttons or analog. For this project I chose to just use the Analog values of triggers and set that to LT and RT. the trigger buttons dont do anything, but feel free to change that as per requirement.
- The source files has a wiring diagram in it that i followed pretty closely. the only thing thats different is an additional wire has to be connected from the Pro Micro's ground to GC Controller's Rumble ground(white wire on some controllers)
- I also didnt use the 5v VCC pin on the Arduino for Rumble as i was scared of the motor burning the microcontroller, so instead i wired it to the RAW pin as its the raw unregulated 5v being sent from the USB port on my PC. VCC pin should be fine i think as it has a current limit of 500mA or something like that, but I didnt wanna risk it.
- Finally the default analog range values of the triggers and the sticks are configured to my controller, you can use a tester program in the source files to check the analog values of your controller and set the range accordingly.

 ### Used Resources/libraries for this project:

- GC Controller Socket model: https://www.thingiverse.com/thing:5776377
- Nicohood's Nintendo Library: https://github.com/NicoHood/Nintendo
- ArduinoXinput Library: https://github.com/dmadison/ArduinoXInput
