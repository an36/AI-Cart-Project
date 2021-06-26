8/13/20:
	- I've increased the processing speed of the Raspberry Pi by overclocking it.
		To overclock you Pi:
		- Update your Pi:
			sudo apt update
			sudo apt dist-upgrade
			sudo reboot
		
		- edit the config.txt file under /boot:
			sudo nano /boot/config.txt

		- Scroll down to the section marked:
			#uncomment to overclock the arm. 700 MHz is the default.
			#arm_freq=800

		- Change it to:
			#uncomment to overclock the arm. 700 MHz is the default.
			over_voltage=6
			arm_freq=2000
		
		- press CTRL+O then Enter to save.  Press CTRL+X to exit
		
		- Reboot the Pi:
			sudo reboot

		*NOTE: overclocking the Pi increases the temperature.  Beware of overheating.

	- I've updated the python camera code so that the camera would have a resolution of 820x480
 	  to raise the FPS rate.
	
	- I've edited the delays to be "soft delays" aka non-blocking delays to run processes
	  independetly.

	- I've also updated the C programs to be able to exit the and kill all processes safely.

	- Before running the updated C programs, please install ncurses library using the following
	  command:
		sudo apt-get install libncurses5-dev

	- Also, install GTK 3.0, Twinkle and glade:
		sudo apt-get install libgtk-3-dev
		sudo apt-get install twinkle
		sudo apt-get install glade
  
  	*NOTE: Create text files 'area.txt' & 'dists.txt' under /var/lib/cart:
		sudo mkdir /var/lib/cart
		sudo touch /var/lib/cart/dists.txt
		sudo touch /var/lib/cart/area.txt
	

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	

- To run the Pyhton camera script:
	1- cd tflite1/
	2- source tflite1_env/bin/activate
	3- python3 TFLite_detection_webcam_AREA.py --modeldir=Sample_TFLite_model

  *NOTE: if you have not done this before, then please follow the instruction in this video (
	https://www.youtube.com/watch?v=aimSGOAUI8Y ) to download and configure the Tensor Flow Lite
	which will enable you to run the commands above.  If you've done this before then follow
	the instructions below to run the python script from the C program 'cart.c'


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	

- I've updated the python script again so that it can be executed from a C program.  Follow the
  steps below to run the python script from a C program.

	1- Change the name of these files/folders:
		'tflite1-env' to 'tflite1_env'  (under /home/pi/tflite1)
		'python3.7' to 'python3_7'	(under /home/pi/tflite1/tflite1_env)
		'site-packages' to 'site_packages'	(under /home/pi/tflite1/tflite1_env/python3_7)  *NOTE: if it's already named 'site_packages' then don't change it.
	
	2- Replace the '__init__.py' file in '/home/pi/tflite1/tflite1_env/lib/python3_7/site_packages/cv2' by the one provided in google drive.

	3- Replace the 'interpreter.py' file in '/home/pi/tflite1/tflite1_env/lib/python3_7/site_packages/tflite_runtime' by the one provided in google drive.
	
	4- Replace the 'TFLite_detection_webcam_AREA.py' in '/home/pi/tflite1' by the one provided in google drive.

	5- Download the C program files provided in google drive and place them under one folder/directory.

	6- To compile and build the C program, run these command lines in a terminal:
		cd /home/pi/Desktop/<foldername>
		gcc sensors.c -o sensors -Wall -lwiringPi -lpthread -lncurses -lm -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/arm-linux-gnueabihf/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/uuid -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -rdynamic -export-dynamic -lgmodule-2.0
		gcc motors.c -o motors -Wall -lwiringPi -lpthread -lncurses -lm -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/arm-linux-gnueabihf/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/uuid -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -rdynamic -export-dynamic -lgmodule-2.0
		gcc cartGUI.c -o cartGUI -Wall -lwiringPi -lpthread -lncurses -lm -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/arm-linux-gnueabihf/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/uuid -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -rdynamic -export-dynamic -lgmodule-2.0
		gcc cart.c -o cart -Wall -lwiringPi -lpthread -lncurses -lm -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/arm-linux-gnueabihf/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/uuid -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -rdynamic -export-dynamic -lgmodule-2.0

	7- To run the C program, run this command line in the same terminal:
		sudo ./cart
	or:
		./cart