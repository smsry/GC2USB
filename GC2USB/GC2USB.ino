#include "Nintendo.h"
#include <XInput.h>

// Define a Gamecube Controller Pin
CGamecubeController GamecubeController(7);

void setup()
{
  XInput.setTriggerRange(30, 200); //Measure your own controller's Triggers and Joystick ranges, these may vary from controller to controller
  XInput.setJoystickRange(47, 238);
  XInput.setAutoSend(false);
  XInput.begin();

}

void loop()
{
  uint16_t rumble = XInput.getRumble(); //Required for Rumble 

  if (GamecubeController.read())
  {
    auto report = GamecubeController.getReport();
    sendGamecubeReport(report);
    delay(10);
 
	  if (rumble > 0) { //Rumble logic. Rumble is sadly just a digital signal rather than PWM, but it still feels very close to original GC controller
		  GamecubeController.setRumble(true);
	  }
	  else {
		  GamecubeController.setRumble(false);
	  }
  }

}

void sendGamecubeReport(Gamecube_Report_t &gc_report)
{  
    XInput.setButton(BUTTON_START, gc_report.start);  

    XInput.setButton(BUTTON_A, gc_report.a);
    XInput.setButton(BUTTON_B, gc_report.b);
    XInput.setButton(BUTTON_X, gc_report.x);
    XInput.setButton(BUTTON_Y, gc_report.y);
    XInput.setButton(BUTTON_RB, gc_report.z);
    
    XInput.setDpad(gc_report.dup, gc_report.ddown, gc_report.dleft, gc_report.dright);

    //XInput.setButton(TRIGGER_LEFT, gc_report.l); Trigger buttons arent mapped as Xinput only allows analog values for triggers. You could map them to LB and RB on Xinput if its required, but for dolphin its not required
    //XInput.setButton(TRIGGER_RIGHT, gc_report.r);

    XInput.setTrigger(TRIGGER_LEFT, gc_report.left);
    XInput.setTrigger(TRIGGER_RIGHT, gc_report.right);


    XInput.setJoystickX(JOY_LEFT, gc_report.xAxis);
    XInput.setJoystickY(JOY_LEFT, gc_report.yAxis);

    XInput.setJoystickX(JOY_RIGHT, gc_report.cxAxis);
    XInput.setJoystickY(JOY_RIGHT, gc_report.cyAxis);


    XInput.send();
}
