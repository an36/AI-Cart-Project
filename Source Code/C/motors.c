#include "cart.h"

void bwd(int speed){		//setup motors to move forward
	digitalWrite(motor1Pin1,LOW);
	digitalWrite(motor1Pin2,HIGH);
	digitalWrite(motor2Pin1,HIGH);
	digitalWrite(motor2Pin2,LOW);
	softPwmWrite(enable1Pin,speed);
	softPwmWrite(enable2Pin,speed);
	printw("Move Backward...\n");
}

void fwd(int speed){		//setup motors to move backward
	digitalWrite(motor1Pin1,HIGH);
	digitalWrite(motor1Pin2,LOW);
	digitalWrite(motor2Pin1,LOW);
	digitalWrite(motor2Pin2,HIGH);
	softPwmWrite(enable1Pin,speed);
	softPwmWrite(enable2Pin,speed);
	printw("Move Forward...\n");
}

void turn_right(int speed){	//setup motors to rotate the cart counter-clockwise
	digitalWrite(motor1Pin1,HIGH);
	digitalWrite(motor1Pin2,LOW);
	digitalWrite(motor2Pin1,HIGH);
	digitalWrite(motor2Pin2,LOW);
	softPwmWrite(enable1Pin,speed);
	softPwmWrite(enable2Pin,speed);
	printw("Turning right...\n");
}

void turn_left(int speed){	//setup motors to rotate the cart clockwise
	digitalWrite(motor1Pin1,LOW);
	digitalWrite(motor1Pin2,HIGH);
	digitalWrite(motor2Pin1,LOW);
	digitalWrite(motor2Pin2,HIGH);
	softPwmWrite(enable1Pin,speed);
	softPwmWrite(enable2Pin,speed);
	printw("Turning left..\n");
}

void stopp(){	//setup motors to stop cart
	digitalWrite(motor1Pin1,LOW);
	digitalWrite(motor1Pin2,LOW);
	digitalWrite(motor2Pin1,LOW);
	digitalWrite(motor2Pin2,LOW);
	softPwmWrite(enable1Pin,0);
	softPwmWrite(enable2Pin,0);
	printw("Motor Stop...\n");
}

void init_pins1(){	//function to initialize and setup the mode of each used pin
	pinMode(enable1Pin,OUTPUT);
	pinMode(motor1Pin1,OUTPUT);
	pinMode(motor1Pin2,OUTPUT);
	pinMode(enable2Pin,OUTPUT);
	pinMode(motor2Pin1,OUTPUT);
	pinMode(motor2Pin2,OUTPUT);
	softPwmCreate(enable1Pin,0,255);//define PMW pin
	softPwmCreate(enable2Pin,0,255);//define PMW pin
}


int main(){
	printw("Program starting...\n");
	
	wiringPiSetup();
	initscr();
	noecho();
	scrollok(stdscr, TRUE);
	
	int speed = 255; //(out of 255)
	int tspeed = 180; //(out of 255)
	int frwd = 0;
	int left = 0;
	int right = 0;
	int bkwd = 0;
	int chk=0;
	int cntr=0;
	int obs = 0;
	
	/****PID Variables****/
	//~ float error=0, integ=0, deriv=0, oput=0, preErr=0;
	//~ float Kp = 0, Ki = 0, Kd = 0;
	//~ float interval = 0.002;
	
		init_pins1(); //function to initialize and setup the mode of each used pin
		float distance1=0, distance2=0, distance3=0,distance4=0,distance5=0,distance6=0;
		float area = 0.0;
		int xmax=0,xmin=0,ymax=0,ymin=0;
		FILE *fp;  //for dists.txt
		FILE *fp1; //for area.txt
		//~ FILE *fp2; //for PIDCTRL.txt
		
		while(1){
		SCAN:	
			fp = fopen("/var/lib/cart/dists.txt","r");
			if(fp==NULL){
				printw("Error opening dists.txt...");
				exit(-1);
			}
			fp1 = fopen("/var/lib/cart/area.txt","r");
			if(fp1==NULL){
				printw("Error opening area.txt...");
				fclose(fp);
				exit(-1);
			}
			//~ fp2 = fopen("/var/lib/cart/PIDCTRL.txt","r");
			//~ if(fp2==NULL){
				//~ printw("Error opening PIDCTRL.txt...");
				//~ fclose(fp);
				//~ fclose(fp1);
				//~ exit(-1);
			//~ }
			fscanf(fp,"%f\n%f\n%f\n%f\n%f\n%f",&distance1,&distance2,&distance3,&distance4,&distance5,&distance6);
			fscanf(fp1,"%f\n%d\n%d\n%d\n%d",&area,&xmax,&xmin,&ymax,&ymin);
			//~ fscanf(fp2,"%f\n%f\n%f",&Kp,&Ki,&Kd);
			
			printw("Ultrasonic sensors\n");
			printw("Front Center: %.2f cm\n",distance1);
			printw("Front Right: %.2f cm\n",distance2);
			printw("Front Left: %.2f cm\n",distance3);
			printw("Right Side: %.2f cm\n",distance4);
			printw("Left Side: %.2f cm\n",distance5);
			printw("Back Side: %.2f cm\n\n",distance6);
			printw("Camera\n");
			printw("Person's Area: %.2f\n",area);
			//~ printw("xmax: %d\n",xmax);
			//~ printw("xmin: %d\n",xmin);
			//~ printw("ymax: %d\n",ymax);
			//~ printw("ymin: %d\n\n",ymin);
			fclose(fp);
			fclose(fp1);
			//~ fclose(fp2);
			
			refresh();
			
			/***********PID CONTROLLER************/
			//~ printw("Kp: %0.2f\tKi: %0.2f\tKd: %0.2f\n",Kp,Ki,Kd);
			//~ error = 410.0 - ((xmax+xmin)/2.0);
			//~ integ = integ + (error * (interval));   //try: center the integral to be at zero instead of 410.0
			//~ deriv = (error - preErr)/(interval);
			//~ oput = (Kp*error)+(Ki*integ)+(Kd*deriv);
			//~ preErr = error;
			//~ printw("\n\noput: %0.2f\n",oput);
			//~ printw("pos: %0.2f\n\n",(xmax+xmin)/2.0);
			
			
			if(chk==1){
				stopp();
				chk = 0;
				//~ printw("chk chk chk chk\n");
				mydelay(10);
				goto UTURN;
			}
			if(obs==1){
				obs=0;
				goto OBS1;
			}
			else if(obs==2){
				obs=0;
				goto OBS2;
			}
			cntr=0;
			
			
			
			/*if area is bigger than 250, then stop*/
			if(area>220.0){
				stopp();
				float left_limit = 250.0;	//used to center the user on the frame
				float right_limit = 400.0;	//used to center the user on the frame
				/*if user is left or right then follow/center the user in frame*/
				if((((xmin+xmax)/2.0)<left_limit)||(((xmin+xmax)/2.0)>right_limit)){
					if(((xmin+xmax)/2.0)<left_limit){
						cntr=1;
						left = 1;
						if(frwd == 1 || right == 1 || bkwd ==1){
							frwd =0; right=0; bkwd=0;
							stopp();
							mydelay(10);
						}
						turn_left(tspeed);
					}
					else if(((xmin+xmax)/2.0)>right_limit){
						cntr=1;
						right = 1;
						if(frwd == 1 || left == 1 || bkwd == 1){
							frwd =0; left=0; bkwd=0;
							stopp();
							mydelay(10);
						}
						turn_right(tspeed);
					}
					if(cntr==1){
						goto SCAN;
					}
				}
			}
			/*else if area is less than 250, then scan and follow user*/
			else if(area<=220.0){
				if(area>160.0){
					float left_limit = 180.0;	//used to center the user on the frame
					float right_limit = 500.0;	//used to center the user on the frame
					/*if user is left or right then follow/center the user in frame*/
					if((((xmin+xmax)/2.0)<left_limit)||(((xmin+xmax)/2.0)>right_limit)){
						if(((xmin+xmax)/2.0)<left_limit){
							cntr=1;
							left = 1;
							if(frwd == 1 || right == 1 || bkwd ==1){
								frwd =0; right=0; bkwd=0;
								stopp();
								mydelay(10);
							}
							turn_left(tspeed);
						}
						else if(((xmin+xmax)/2.0)>right_limit){
							cntr=1;
							right = 1;
							if(frwd == 1 || left == 1 || bkwd == 1){
								frwd =0; left=0; bkwd=0;
								stopp();
								mydelay(10);
							}
							turn_right(tspeed);
						}
						if(cntr==1){
							goto SCAN;
						}
					}
				}
				
				/*if path is clear, then go forward*/
				if((distance1 >= 20) && (distance2 >=30) && (distance3>=30) && (distance4>=17) && (distance5>=17)){ 
					frwd = 1;
					if(left == 1 || right == 1 || bkwd==1){
						left = 0;
						right = 0;
						bkwd=0;
						stopp();
						mydelay(10);
					}
					fwd(speed);
					printw("frwd: %d\n",frwd);
				}
				/*if object near front right corner, then turn left*/
				else if(((distance1>=20)&&((distance2<30)||(distance4<20))) && distance3>=30){
					left = 1;
					if(frwd == 1 || right ==1 || bkwd ==1){
						frwd = 0;
						right = 0;
						bkwd = 0;
						stopp();
						mydelay(10);
					}
					turn_left(speed);
					printw("left: %d\n",left);
				}
				/*if object near right side, then turn left*/
				else if(((distance1>=20)&&(distance4<20)) && distance3>=30 && distance5>=20){
					left = 1;
					if(frwd == 1 || right ==1 || bkwd==1){
						frwd = 0;
						right = 0;
						bkwd = 0;
						stopp();
						mydelay(10);
					}
					turn_left(speed);
					printw("left: %d\n",left);
				}
				/*if object near front left corner, then turn right*/
				else if(((distance1>=20)&&((distance3<30)||(distance5<20))) && distance2>=30){
					right = 1;
					if(frwd == 1 || left ==1 || bkwd==1){
						frwd = 0;
						left = 0;
						bkwd = 0;
						stopp();
						mydelay(10);
					}
					turn_right(speed);
					printw("right: %d\n",right);
				}
				/*if object near left side, then turn right*/
				else if(((distance1>=20)&&(distance5<20)) && distance2>=30 && distance4>=20){
					right = 1;
					if(frwd == 1 || left ==1 || bkwd==1){
						frwd = 0;
						left = 0;
						bkwd = 0;
						stopp();
						mydelay(10);
					}
					turn_right(speed);
					printw("right: %d\n",right);
				}
				/*if object is in front of the cart, then turn left or right (whichever has the longest distance)*/
				else if (distance1<20){
					/*if all sides are blocked but the back, then go backward*/
					if(distance2<50 && distance3<50 && distance4<20 && distance5<20 && distance6>=30){
						bkwd = 1;
						if(frwd == 1 || left == 1 || right==1){
							frwd =0; left=0; right=0;
							stopp();
							mydelay(10);
						}
						bwd(speed);
						mydelay(10);
						chk = 1;
						goto SCAN;
					}
					/*else check which side has more space, then turn towards that side*/
					UTURN:
						//~ printw("UTURN UTURN UTURN\n");
						//~ mydelay(1000);
					if(distance4>distance5 /*&& distance4>=20*/){
						right = 1;
						if(frwd == 1 || left == 1 || bkwd == 1){
							frwd =0; left=0; bkwd=0;
							stopp();
							mydelay(10);
						}
						turn_right(speed);
						mydelay(250);
						stopp();
						obs = 1;
						goto SCAN;
					OBS1:
						if(distance1>20&&distance3>20){
							fwd(speed);
							mydelay(90);
							frwd = 1;
							turn_left(speed);
							mydelay(250);
							left=1;
						}
					}
					else if (distance4<distance5 /*&& distance5>=20*/){
						left = 1;
						if(frwd == 1 || right == 1 || bkwd ==1){
							frwd =0; right=0; bkwd=0;
							stopp();
							mydelay(10);
						}
						turn_left(speed);
						mydelay(250);
						stopp();
						obs = 2;
						goto SCAN;
					OBS2:
						if(distance1>20&&distance2>20){
							fwd(speed);
							mydelay(90);
							frwd = 1;
							turn_right(speed);
							mydelay(250);
							right=1;
						}
					}
				}
			}
			//~ system("clear");
		}
	return 1;
}
