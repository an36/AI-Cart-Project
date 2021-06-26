#include <wiringPi.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>
#include <softPwm.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/i2c-dev.h>
#include <ncurses.h>


#ifndef CART
#define CART

#define trigPin1 4		//trig pin for sensor1  (front center)
#define echoPin1 5		//echo pin for sensor1	(front center)
#define trigPin2 10		//trig pin for sensor2	(front right corner)
#define echoPin2 11		//echo pin for sensor2	(front right corner)
#define trigPin3 12		//trig pin for sensor3	(front left corner)
#define echoPin3 13		//echo pin for sensor3	(front left corner)
#define trigPin4 15		//trig pin for sensor4	(right side)
#define echoPin4 16		//echo pin for sensor4	(right side)
#define trigPin5 29		//trig pin for sensor5	(left side)
#define echoPin5 1		//echo pin for sensor5	(left side)
#define trigPin6 7		//trig pin for sensor6	(back side)
#define echoPin6 14		//echo pin for sensor6	(back side)

#define motor1Pin1 2		//positive end of motor1 and motor3 (left side of cart)
#define motor1Pin2 0		//negative end of motor1 and motor3 (left side of cart)
#define motor2Pin1 26		//positive end of motor2 and motor4 (right side of cart)
#define motor2Pin2 27		//negative end of motor2 and motor4 (right side of cart)
#define enable1Pin 3		//enable pin for motor1 and motor3 (throttle for left side)
#define enable2Pin 28		//enable pin for motor1 and motor3 (throttle for right side)

void msleep(int val){
	usleep(val*1000);
}

void mydelay(int val){
	unsigned long old_time = millis();
	while(1){
		if(millis() - old_time >= val){
			break;
		}
	}
}

#endif
