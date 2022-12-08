#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4Motors motors;

/* two ways of using buttons:
buttonA.waitForButton();
buttonB.isPressed();
*/

//const int sizeArray = 5;
//char commands[sizeArray];

// int duration = 400;

struct RoverControl {
  char command ='f';
  int speed =0;
  int time =0;
  int distance = 0;

  RoverControl *next = NULL;
  }
  
};

RoverControl* createNode (char c, int s, int t){
  RoverControl* newNode = new RoverControl();
  newNode->command = c;
  newNode->speed = s;
  newNode->time = t;
  newNode->next = NULL;

  return newNode;
}

void insertNode(Node* node, char c, int s, int t){
  if (node->next ==NULL)
    node->next = createNode(c,s,t);
  else insertNode(node->next,c,s,t)
}

RoverControl *root = createNode('f', 200, 400);

insertNode(root, 'b', 400, 300)

const int sizeArray = 5;
RoverControl commands[sizeArray];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void commandInterface(){

  String cArray[] = {"forward", "backward", "left", "right"};
  for (int i=0; i<sizeArray; i++){
    int c = 0;
    do{
        lcd.clear();
        lcd.print("Command: ");
        lcd.gotoXY(0,1);
        lcd.print(cArray[c%4]);
        delay(500);
        if (buttonA.isPressed()) c++;
    } while (!buttonB.isPressed());

    lcd.clear();
    lcd.print("Selected:");
    lcd.gotoXY(0,1);
    lcd.print(cArray[c%4]);
    delay(500);
    
      if (cArray[c%4] == "forward") commands[i].command = 'f';
      else if (cArray[c%4] == "backward") commands[i].command = 'b';
      else if (cArray[c%4] == "left") commands[i].command = 'l';
      else commands[i].command = 'r';

      commands[i].setTime(400);
  }
}

void moveForward(int mspeed){
  motors.setSpeeds(mspeed, mspeed);
}

void moveBackward(int mspeed){
  motors.setSpeeds(-mspeed, -mspeed);
}

void turnLeft(int mspeed){
  motors.setSpeeds(mspeed, -mspeed);
}

void turnRight(int mspeed){
  motors.setSpeeds(-mspeed, mspeed);
}

int randomNumber(int max){
  return random(1, max);
}


void loop() {
  int r =0;
  commandInterface();

  do {
  for (int i=0; i<sizeArray; i++){
    switch(commands[i].command){
       case 'f': moveForward(randomNumber(500)); break;
       case 'b': moveBackward(randomNumber(500)); break;
       case 'r': turnRight(randomNumber(500)); break;
       case 'l': turnLeft(randomNumber(500)); break;
       default: motors.setSpeeds(0, 0);
    }
    //commands[i].wait();
    delay(commands[i].getTime());
    motors.setSpeeds(0, 0);
    delay(commands[i].getTime());

    r=randomNumber(100);
  }
  } while(r<51);


  if (r>80 && r<=100){
    for (;;)
      delay(1000);
  }

}
