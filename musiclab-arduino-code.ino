int pushButton1 = 2;
int oldButtonState1 = HIGH;
int pushButton2 = 3;
int oldButtonState2 = HIGH;

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
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(pushButton2, INPUT_PULLUP);
}

void loop() {
  buttonHandler("b1:", pushButton1, oldButtonState1);
  buttonHandler("b2:", pushButton2, oldButtonState1);
  potentiometerHandler("p1:", potPin0, potRead0);
  potentiometerHandler("p2:", potPin1, potRead1);
  potentiometerHandler("p3:", potPin2, potRead2);
  potentiometerHandler("p4:", potPin3, potRead3);
  delay(1);        // delay in between reads for stability
}


void potentiometerHandler(String name, int potPin, int &potVal)
{
    int potTempVal = analogRead(potPin);
  
    if(potTempVal >= (potVal+threshold) || potTempVal <= (potVal-threshold))
    {
       potVal = potTempVal;
       sendOutput(name, potVal);
    }
}

void buttonHandler(String Name, int button, int oldButtonState){
  int thisButtonState = digitalRead(button);
  if(thisButtonState != oldButtonState)
  {
    oldButtonState = thisButtonState; 
    if (thisButtonState == HIGH) {
      sendOutput(Name, 0);  
    } else if (thisButtonState == LOW) {
      sendOutput(Name, 1);
    }
       
  }
}

void sendOutput(String ctrl, int val){
    String message = ctrl + String(val) + String(";");
    Serial.println(message);
}

