#include "cart.h"


#define max_dis 2000 //define the maximum measured distance
#define timeOut max_dis*60 //calculate timeout according to the maximum measured distance


//function pulseIn: obtain pulse time of a pin
int pulseIn(int pin, int level, int timeout);

float getSonar(int trigPin, int echoPin){ //get the measurement result of ultrasonic module with unit: cm
	long pingTime;
	float distance;
	digitalWrite(trigPin,HIGH);
	//~ delayMicroseconds(10);
	mydelay(10);
	digitalWrite(trigPin,LOW);
	pingTime = pulseIn(echoPin,HIGH,timeOut);  //read plus time of echoPin
	distance = (float)pingTime*340.0/2.0/10000.0; //calculate distance with sound speed
	
	return distance;
}

void init_pins2(){	//function to initialize and setup the mode of each used pin
	pinMode(trigPin1,OUTPUT);
	pinMode(echoPin1,INPUT);
	pinMode(trigPin2,OUTPUT);
	pinMode(echoPin2,INPUT);
	pinMode(trigPin3,OUTPUT);
	pinMode(echoPin3,INPUT);
	pinMode(trigPin4,OUTPUT);
	pinMode(echoPin4,INPUT);
	pinMode(trigPin5,OUTPUT);
	pinMode(echoPin5,INPUT);
	pinMode(trigPin6,OUTPUT);
	pinMode(echoPin6,INPUT);
}


int main(){
	printf("Program starting...\n");
	
	wiringPiSetup();
	init_pins2();
	
	float distance1=0, distance2=0, distance3=0,distance4=0,distance5=0,distance6=0;
	char buf[100];
	FILE *fp;
		
	while(1){
		fp=fopen("/var/lib/cart/dists.txt","w");
	
		if(fp==NULL){
			printf("Error opening file...");
			exit(-1);
		}
		distance1 = getSonar(trigPin1,echoPin1);
		gcvt(distance1,6,buf);
		fputs(buf,fp);
		fputs("\n",fp);
		distance2 = getSonar(trigPin2,echoPin2);
		gcvt(distance2,6,buf);
		fputs(buf,fp);
		fputs("\n",fp);
		distance3 = getSonar(trigPin3,echoPin3);
		gcvt(distance3,6,buf);
		fputs(buf,fp);
		fputs("\n",fp);
		distance4 = getSonar(trigPin4,echoPin4);
		gcvt(distance4,6,buf);
		fputs(buf,fp);
		fputs("\n",fp);
		distance5 = getSonar(trigPin5,echoPin5);
		gcvt(distance5,6,buf);
		fputs(buf,fp);
		fputs("\n",fp);
		distance6 = getSonar(trigPin6,echoPin6);
		gcvt(distance6,6,buf);
		fputs(buf,fp);
		fclose(fp);
		mydelay(50);
	}
	return 0;
}

int pulseIn(int pin, int level, int timeout)
{
   struct timeval tn, t0, t1;
   long micros;
   gettimeofday(&t0, NULL);
   micros = 0;
   while (digitalRead(pin) != level)
   {
      gettimeofday(&tn, NULL);
      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros += (tn.tv_usec - t0.tv_usec);
      if (micros > timeout) return 0;
   }
   gettimeofday(&t1, NULL);
   while (digitalRead(pin) == level)
   {
      gettimeofday(&tn, NULL);
      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros = micros + (tn.tv_usec - t0.tv_usec);
      if (micros > timeout) return 0;
   }
   if (tn.tv_sec > t1.tv_sec) micros = 1000000L; else micros = 0;
   micros = micros + (tn.tv_usec - t1.tv_usec);
   return micros;
}
