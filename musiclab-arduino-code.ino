int pushButton1 = 2;
int oldButtonState1 = 0;
int pushButton2 = 3;
int oldButtonState2 = 0;

const int threshold = 10;
const int currPotentiometer = 0;

const int potPin0 = A0;
int tempPotRead0 = 0;
int potRead0 = 0;

const int potPin1 = A1;
int tempPotRead1 = 0;
int potRead1 = 0;

const int potPin2 = A2;
int tempPotRead2 = 0;
int potRead2 = 0;

const int potPin3 = A3;
int tempPotRead3 = 0;
int potRead3 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton1, INPUT);
  pinMode(pushButton2, INPUT);
}

void loop() {
  buttonHandler("b1:", pushButton1, oldButtonState1);
  buttonHandler("b2:", pushButton2, oldButtonState1);
  potentiometerHandler("p1:", potPin0, tempPotRead0, potRead0);
  potentiometerHandler("p2:", potPin1, tempPotRead1, potRead1);
  potentiometerHandler("p3:", potPin2, tempPotRead2, potRead2);
  potentiometerHandler("p3:", potPin3, tempPotRead3, potRead3);
  delay(1);        // delay in between reads for stability
}


void potentiometerHandler(String name, int potPin, int potTempVal, int potVal)
{
  potTempVal = analogRead(potPin);
  
  if(potTempVal != potVal)
  {
     if(potTempVal > (potVal+threshold) || potTempVal < (potVal-threshold))
     {
       potVal = potTempVal;
       sendOutput(name, potVal);
     }
  }
}

void buttonHandler(String Name, int button, int oldButtonState){
  int thisButtonState = digitalRead(button);
  if(thisButtonState != oldButtonState)
  {
    oldButtonState = thisButtonState;  
    sendOutput(Name, thisButtonState);
  }
}

void sendOutput(String ctrl, int val){
    String message = ctrl + String(val) + String(";");
    Serial.println(message);
}

