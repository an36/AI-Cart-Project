#include "cart.h"


/*function to check if keyboard key has been pressed*/
int kbhit(void)
{
    int ch = getch();

    if (ch !=ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main(){
	printf("Program starting...\n");
	
	pid_t pid1, pid2, pid3, pid4;
	
	pid1 = fork();
	
	if(pid1 ==-1){
		printf("Error forking....\n");
		exit(-1);
	}
	else if(pid1 == 0){
		execl("sensors","sensors",NULL);
		printf("Failed to execute sensors.exe\n");
		exit(-1);
	}
	else{
		pid2 = fork();
		if(pid2==-1){
			printf("Error forking....\n");
			exit(-1);
		}
		else if(pid2==0){
			mydelay(3000);		//wait 5 seconds before starting the motors.
			execl("motors","motors",NULL);
			printf("Failed to execute motors.exe\n");
			exit(-1);
		}
		else{
			pid3 = fork();
			if(pid3==-1){
				printf("Error forking....\n");
				exit(-1);
			}
			else if(pid3==0){
				system("cd /home/pi/tflite1; source tflite1_env/bin/activate; python3 TFLite_detection_webcam_AREA.py --modeldir=Sample_TFLite_model");
			}
			else{
				pid4 = fork();
				if(pid4==-1){
					printf("Error forking....\n");
					exit(-1);
				}
				else if(pid4==0){
					execl("cartGUI","cartGUI",NULL);
					printf("Failed to execute motors.exe\n");
					exit(-1);
				}
				else{
					initscr();

					cbreak();
					echo();
					nodelay(stdscr, TRUE);
					scrollok(stdscr, TRUE);
					
					while (1) {
						if (kbhit()) {
							int ch = getch();
							if(ch>0){
								nocbreak();
								endwin();
								kill(pid1,SIGKILL);
								kill(pid2,SIGKILL);
								kill(pid3,SIGKILL);
								kill(pid4,SIGKILL);
								kill(getpid(),SIGKILL);
								return 1;
							}
						}
						else {
							mydelay(10);
						}
					}
				}
			}
		}
	}
}

