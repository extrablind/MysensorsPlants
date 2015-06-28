// Example sketch showing how to control physical relays. 
// This example will remember relay state even after power failure.

#include <MySensor.h>
#include <SPI.h>
#include <NewPing.h>
//
#define RELAY_1  3  // Arduino Digital I/O pin number for first relay (second on pin+1 etc)
#define NUMBER_OF_RELAYS 1 // Total number of attached relays
#define RELAY_ON 1  // GPIO value to write to turn on attached relay
#define RELAY_OFF 0 // GPIO value to write to turn off attached relay
#define PIN_LED 3
MySensor gw;
// Sonar
#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
unsigned long SLEEP_TIME = 2000; // Sleep time between reads (in milliseconds)
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
MyMessage msg(2, V_DISTANCE);

int lastDist;
boolean metric = true; 



void setup()  
{   
  // Initialize library and add callback for incoming messages
  gw.begin(incomingMessage, 111, false);
  // Send the sketch version information to the gateway and Controller
  gw.sendSketchInfo("ID 111 - ON / OFF RECEIVE LED 13 - ", "1.0");

  gw.present(1, S_LIGHT);
  gw.present(2, S_DISTANCE);
  pinMode(PIN_LED, OUTPUT);   
  boolean metric = gw.getConfig().isMetric;


}


void loop() 
{
    int dist = metric?sonar.ping_cm():sonar.ping_in();

    gw.send(msg.set(dist), false);
  lastDist = dist;
  // Alway process incoming messages whenever possible
  gw.process();
  // Send sonar value
  //Serial.print("Ping: ");
  //Serial.print(dist); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  //Serial.println(metric?" cm":" in");


  gw.sleep(SLEEP_TIME);

}

void incomingMessage(const MyMessage &message) {
  // We only expect one type of message from controller. But we better check anyway.
  if (message.type==V_LIGHT) {
    // Change relay state
    digitalWrite(PIN_LED, message.getInt());
    // Store state in eeprom
    //gw.saveState(message.sensor, message.getBool());
    //Serial.print("Incoming change for sensor:");
    //Serial.print(message.sensor);
    Serial.print("New status LED : ");
    Serial.println(message.getBool());

  } 
}



