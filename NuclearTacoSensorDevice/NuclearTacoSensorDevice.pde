#include <Servo.h>
#include <Shifter.h>

#define SER_Pin 4 //SER_IN
#define RCLK_Pin 3 //L_CLOCK
#define SRCLK_Pin 2 //CLOCK
#define NUM_REGISTERS 5 //how many registers are in the chain

Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS); 
Servo sweatPointer;

// DEBUG MODE (use flowmeter to test pointer and leds);
boolean DEBUG = false;
boolean DEMO = true;


// PIN VARS
int tempPin = 0;
int humidPin = 1;
int flowPin = 9;
int redLedsPin = 11;
int servoPin = 6;

//MEDIR VARS
int temp = 0;
int humid = 0;
int flow = 0;
int flowState = 0;
int pflowState = 0;

//CALIBRAR VARS
int tempMin = 58;
int tempMax = 100;
int humidMin = 13;
int humidMax = 80;
int flowMin = 0;
int flowMax = 100;

// OUTPUT
int redness = 0;
int pointerAngle = 0;
float numBlueLeds = 8;

boolean barGraphOverride = false;


void setup() {
  
  pinMode(flowPin, INPUT);  
  pinMode(redLedsPin, OUTPUT);
  
  sweatPointer.attach(servoPin);
  
  Serial.begin(9600);
  
  shifter.clear();
  shifter.write();
    
}


void loop() {
  
  temp = analogRead(tempPin);    
  humid = analogRead(humidPin);      
  
  flowState = digitalRead(flowPin);

  if (flowState != pflowState) {
    if (flowState == HIGH) {
      flow++;
      if(DEBUG) {
        redness++;
        if(redness>255) {
          redness = 0; 
        }
        if (!barGraphOverride) {
        numBlueLeds = 8 - map(redness,0,255,0,8);
        }
        pointerAngle = map(redness,0,255,0,180);
      }
    }
  }
  pflowState = flowState;
  
  if(!DEBUG) {
    mapVars();
  }

  doOutputs();
  
  logSerial();
  
  delay(10);
}
  
  
void mapVars() {
 
    if(!DEMO) {
    redness = map(temp,tempMin,tempMax,0,255);
    pointerAngle = map(humid,humidMin,humidMax,0.0,180);
    if(!barGraphOverride) {
    numBlueLeds = 8 - map(flow,flowMin,flowMax,0,7);
    }
    if(redness<0) {
      redness = 0;
    }
    
    if(pointerAngle<0) {
      pointerAngle = 0;
    }
    
    if(redness>255) {
      redness = 255;
    }
        
    if(pointerAngle>180) {
      pointerAngle = 180;
    }
    } else {
      redness++;
      pointerAngle++;
      redness = redness%255;
      pointerAngle = pointerAngle%180;
      numBlueLeds -= 0.1;
	  if (numBlueLeds<0) {
	     numBlueLeds = 8;	
       }
    }
  
}
  
void renderBarGraph() {

  for (int i=0; i<8; i++) {
    if(i<numBlueLeds) {
      shifter.setPin(i, HIGH);
    } else {
      shifter.setPin(i, LOW);
    }
  }  
  shifter.write();

}

void doOutputs() {
 
      analogWrite(11,redness);
      sweatPointer.write(180-pointerAngle);   
      
      renderBarGraph();
      
}



void logSerial() {
 
  Serial.print(temp, DEC);
  Serial.print(" ");
  Serial.print(redness, DEC);
  Serial.print(" ");
  Serial.print(humid, DEC);  
  Serial.print(" ");
  Serial.print(pointerAngle, DEC);  
  Serial.print(" ");
  Serial.print(flow, DEC);  
  Serial.print(" "); 
  Serial.print(numBlueLeds, DEC);  
  Serial.println();   
  
}
