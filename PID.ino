
#define ch1 2
#define ch2 3

unsigned long int ticks=0;


#define AIN1 10
#define AIN2 9
#define PWMA 11
#define STBY 8

// PID Parameters
#define Kp  2.7    //Proportianal constant
#define Ki  0 //Integral constant
#define Kd  0     //Differential Constant

// Desired Encoder count per time
#define TARGET 100
// Time step
#define TIME_STEP 250
// Standart speed for motors
#define PWM_BASE 120


double proportional=0;
double differential=0;
double integral=0;
double PID=0;



unsigned long long int time_elapsed=0;

unsigned long int count=0;
unsigned long int count_prev=0;


int error=0;
int error_prev=0;



void setup()
{
   Serial.begin(9600);
   // Encoder interrupts
  attachInterrupt(digitalPinToInterrupt(ch1),counts,FALLING);
  attachInterrupt(digitalPinToInterrupt(ch2),counts,FALLING);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(STBY,OUTPUT);


}


void loop()
{

   
   
   ticks=0;
   time_elapsed=millis();
   while(millis()-time_elapsed<=TIME_STEP);{}
   count=ticks;

   

   error=TARGET-count;

   //PID
   proportional=Kp*error;
   differential=Kd*(error-error_prev);
   integral+=Ki*error;

   PID= proportional+integral+differential;


   error_prev=error;

   digitalWrite(AIN2, HIGH);
   digitalWrite(AIN1, LOW);
   digitalWrite(STBY, HIGH);
   analogWrite(PWMA, abs(PWM_BASE+(int)PID));


     Serial.print("count\t");
     Serial.print(count);

     Serial.print("PID\t");
     Serial.println(PID);

   

   
  

}
void counts()
{
  ticks++;
  //Serial.println(ticks);
}
