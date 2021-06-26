#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>
#include <softPwm.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int fd;
int v1,v2, res;
double volts;


int read_byte_2c(int addr)
{
  int val;
  val = wiringPiI2CReadReg8(fd, addr);
  //~ val = val << 8;
  //~ val += wiringPiI2CReadReg8(fd, addr+1);
  //~ if (val >= 0x8000)
    //~ val = -(65536 - val);

  return val;
}

int main()
{
  fd = wiringPiI2CSetup (0x64);
  wiringPiI2CWriteReg8 (fd,0x01,0xC0);//disable sleep mode 
  printf("set 0x6B=%X\n",wiringPiI2CReadReg8 (fd,0x6B));
  
  while(1) {

    v1 = read_byte_2c(0x08);
    v2 = read_byte_2c(0x09);
    printf("v1: %d\n",v1);
    printf("v2: %d\n",v2);
    
    res = (v1 << 8) | v2;
    //~ if (volts >= 0x8000){
    //~ volts = -(65536 - volts);}
    volts = 23.6 * (res/65535.0);
    printf("volts: %lf\n",volts);
    
    usleep(1);
    system("clear");
  }
  return 0;
}
