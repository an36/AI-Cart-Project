/*
 * cartGUI.c
 * 
 * Copyright 2020  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <gdk/gdkkeysyms.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stddef.h>

//Variables
GtkWidget	*Main;
GtkWidget	*window;
GtkWidget	*Call;
GtkWidget	*Grid1;
GtkWidget	*Progbar1;
GtkWidget	*label1;
GtkBuilder *builder;

int v1,v2, res;
gdouble fraction; // Value for progress bar
int fd; //Error flag
int countMax = 0xFFFF, countCurrent; //Max hex from counter reg, current reg reading
const int address = 0x64; //Coloumb counter address
const int MSB = 0x08; // Reg address for MSB
const int LSB = 0x09; //Reg adress for LSB

//Declarations
gint ReadCharge (gpointer data); // Read charge from counter

int main(int argc, char **argv)
{	
	//~ fd = wiringPiI2CSetup (0x64);
	//~ wiringPiI2CWriteReg8 (fd,0x01,0xC0);
	//~ v1 = wiringPiI2CReadReg8 (fd, MSB); //MSB read
	//~ v2 = wiringPiI2CReadReg8 (fd, LSB);// LSB read
	//~ res = (v1 << 8) | v2;
	//~ fraction = 23.6 * (res/65535.0);
	
	gtk_init(&argc, &argv); //initialize Gtk
	
	builder = gtk_builder_new_from_file ("GUI.glade"); // Gets UI layout from file
	
	Main = GTK_WIDGET(gtk_builder_get_object(builder, "Main")); // Draws object called Main from GUI file
	
	g_signal_connect(Main, "destroy", G_CALLBACK(gtk_main_quit), NULL); //Destroy command on window close
	gtk_builder_connect_signals(builder, NULL); // Retrieves event signals from glade file
	
	Main = GTK_WIDGET(gtk_builder_get_object(builder, "Main"));
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	Call = GTK_WIDGET(gtk_builder_get_object(builder, "Call"));
	Grid1 = GTK_WIDGET(gtk_builder_get_object(builder, "Grid1"));
	Progbar1 = GTK_WIDGET(gtk_builder_get_object(builder, "Progbar1"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));   // Setup ability to call UI features, not all used.
	
	gtk_widget_show(Main);//Build window
	gtk_progress_bar_set_fraction((GtkProgressBar *)Progbar1, 0.0);  //Function call to update progress bar
	g_timeout_add(5000,ReadCharge,NULL);
	gtk_main(); //Gtk main function
	
	return EXIT_SUCCESS;
}

void	on_Call_clicked (GtkButton *b)
{
		system("twinkle --immediate --call 123456"); //Call command to twinkle program, 123456 is generic address
	}
	
gint ReadCharge(gpointer data)
{
	fraction = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(Progbar1));
	fd = wiringPiI2CSetup (0x64);
	wiringPiI2CWriteReg8 (fd,0x01,0xC0);
	v1 = wiringPiI2CReadReg8 (fd, MSB); //MSB read
	v2 = wiringPiI2CReadReg8 (fd, LSB);// LSB read
	res = (v1 << 8) | v2;
	fraction = 23.6 * (res/65535.0);
	fraction = fraction/5.0;
	gtk_progress_bar_set_fraction((GtkProgressBar *)Progbar1, fraction);
	//~ printf("fraction: %lf\n",fraction);
	return 1;
}
