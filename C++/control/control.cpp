#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <thread>

#include <SDL2/SDL.h>
#include <gtkmm.h>
#include <gdkmm.h>

#define PORT 31337 

float parseFloat(uint8_t* array){
        uint32_t axisYInteger=0;
        axisYInteger|=uint32_t(array[0])<<24;
        axisYInteger|=uint32_t(array[1])<<16;
        axisYInteger|=uint32_t(array[2])<<8;
        axisYInteger|=uint32_t(array[3])<<0;
        float value=(float)*(static_cast<float*>(static_cast<void*>(&axisYInteger)));

        return value;
}

 
void insertFloat(float value,uint8_t* array){
	array[0]=uint8_t((uint32_t(*(static_cast<uint32_t*>(static_cast<void*>(&value))))>>24) & 0xff);
	array[1]=uint8_t((uint32_t(*(static_cast<uint32_t*>(static_cast<void*>(&value))))>>16) & 0xff);
	array[2]=uint8_t((uint32_t(*(static_cast<uint32_t*>(static_cast<void*>(&value))))>>8) & 0xff);
	array[3]=uint8_t((uint32_t(*(static_cast<uint32_t*>(static_cast<void*>(&value))))>>0) & 0xff);
}

bool connected=false;

bool quit(GdkEventAny* event){
	exit(0);
 	return true;
}

Gtk::Label* voltageLabel;
Gtk::Label* current0Label;
Gtk::Label* current1Label;
Gtk::Label* current2Label;
Gtk::Label* current3Label;
Gtk::Label* current4Label;
Gtk::Label* current5Label;
Gtk::Label* current6Label;
Gtk::Label* current7Label;
Gtk::Label* current8Label;
Gtk::Label* current9Label;
Gtk::Label* current10Label;
Gtk::Label* current11Label;
Gtk::Label* current12Label;
Gtk::Label* current13Label;
Gtk::Label* current14Label;
Gtk::Label* current15Label;
Gtk::Entry* ipAddressEntry;
Gtk::Label* connectionStatusLabel;

bool guiReady=false;

int sock = 0; 
void connectToServer(){
	struct sockaddr_in address; 
	int valread; 
	struct sockaddr_in serv_addr; 
	std::string hello("Hello from client"); 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 

	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
		connected=false;
		printf("\n Socket creation error \n"); 
		connectionStatusLabel->set_text("Socket Creation Error");
		Gdk::RGBA red;
		red.set_rgba(1.0,0,0,1.0);
		connectionStatusLabel->override_background_color(red);
		return; 
	} 
	if(inet_pton(AF_INET, ipAddressEntry->get_text().c_str(), &serv_addr.sin_addr)<=0)  { 
		connected=false;
		printf("\nInvalid address/ Address not supported \n");
		connectionStatusLabel->set_text("Invalid Address");
		Gdk::RGBA red;
		red.set_rgba(1.0,0,0,1.0);
		connectionStatusLabel->override_background_color(red);
		return;
	} 
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
		connected=false;
		printf("\nConnection Failed \n"); 
		connectionStatusLabel->set_text("Connection Failed");
		Gdk::RGBA red;
		red.set_rgba(1.0,0,0,1.0);
		connectionStatusLabel->override_background_color(red);
	}else{
		connected=true;
		send(sock , hello.c_str() , strlen(hello.c_str()) , 0 ); 
		printf("Hello message sent\n"); 
		valread = read( sock , buffer, 1024); 
		printf("%s\n",buffer ); 
		fcntl(sock,F_SETFL, O_NONBLOCK);

		printf("\nConnected \n"); 
		connectionStatusLabel->set_text("Connected");
		Gdk::RGBA green;
		green.set_rgba(0,1.0,0,1.0);
		connectionStatusLabel->override_background_color(green);
	}
}


void setupGUI(Glib::RefPtr<Gtk::Application> application){
//void setupGUI(int argc, char** argv){
	std::cout << "setting up " << std::endl;
 //	Glib::RefPtr<Gtk::Application> application = Gtk::Application::create(argc, argv, "edu.uark.razorbotz");

	Gtk::Window* window=new Gtk::Window();

	Gtk::Box* topLevelBox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,5));

	Gtk::Box* connectBox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,5));
	Gtk::Label* ipAddressLabel=Gtk::manage(new Gtk::Label("IP Address "));
	ipAddressEntry=Gtk::manage(new Gtk::Entry());
	ipAddressEntry->set_text("192.168.1.2");
        ipAddressEntry->set_text("10.4.62.241");
	Gtk::Button* connectButton=Gtk::manage(new Gtk::Button("Connect"));
	connectButton->signal_clicked().connect(sigc::ptr_fun(&connectToServer));
	connectionStatusLabel=Gtk::manage(new Gtk::Label("Not Connected"));
	Gdk::RGBA red;
	red.set_rgba(1.0,0,0,1.0);
	connectionStatusLabel->override_background_color(red);
	
	Gtk::Box* sensorBox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));

	Gtk::Frame* powerDistributionPanelFrame=Gtk::manage(new Gtk::Frame("Power Distribution Panel"));	
	Gtk::Box* powerDistributionPanelBox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,5));

	Gtk::Box* headerBox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* headerTextLabel=Gtk::manage(new Gtk::Label("Power Distribution Panel"));

	Gtk::Box* voltageBox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* voltageTextLabel=Gtk::manage(new Gtk::Label("Voltage:"));

	voltageLabel=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current0Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current0TextLabel=Gtk::manage(new Gtk::Label("Current 0: "));
	current0Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current1Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current1TextLabel=Gtk::manage(new Gtk::Label("Current 1:"));
	current1Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current2Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current2TextLabel=Gtk::manage(new Gtk::Label("Current 2:"));
	current2Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current3Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current3TextLabel=Gtk::manage(new Gtk::Label("Current 3:"));
	current3Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current4Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current4TextLabel=Gtk::manage(new Gtk::Label("Current 4:"));
	current4Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current5Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current5TextLabel=Gtk::manage(new Gtk::Label("Current 5:"));
	current5Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current6Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current6TextLabel=Gtk::manage(new Gtk::Label("Current 6:"));
	current6Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current7Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current7TextLabel=Gtk::manage(new Gtk::Label("Current 7:"));
	current7Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current8Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current8TextLabel=Gtk::manage(new Gtk::Label("Current 8:"));
	current8Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current9Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current9TextLabel=Gtk::manage(new Gtk::Label("Current 9:"));
	current9Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current10Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current10TextLabel=Gtk::manage(new Gtk::Label("Current 10:"));
	current10Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current11Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current11TextLabel=Gtk::manage(new Gtk::Label("Current 11:"));
	current11Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current12Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current12TextLabel=Gtk::manage(new Gtk::Label("Current 12:"));
	current12Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current13Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current13TextLabel=Gtk::manage(new Gtk::Label("Current 13:"));
	current13Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current14Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current14TextLabel=Gtk::manage(new Gtk::Label("Current 14:"));
	current14Label=Gtk::manage(new Gtk::Label("0"));

	Gtk::Box* current15Box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,2));
	Gtk::Label* current15TextLabel=Gtk::manage(new Gtk::Label("Current 15:"));
	current15Label=Gtk::manage(new Gtk::Label("0"));


	voltageBox->pack_start(*voltageTextLabel,false,true,10);
	voltageBox->pack_end(*voltageLabel,false,true,10);

	current0Box->pack_start(*current0TextLabel,false,true,10);
	current0Box->pack_end(*current0Label,false,true,10);

	current1Box->pack_start(*current1TextLabel,false,true,10);
	current1Box->pack_end(*current1Label,false,true,10);

	current2Box->pack_start(*current2TextLabel,false,true,10);
	current2Box->pack_end(*current2Label,false,true,10);

	current3Box->pack_start(*current3TextLabel,false,true,10);
	current3Box->pack_end(*current3Label,false,true,10);

	current4Box->pack_start(*current4TextLabel,false,true,10);
	current4Box->pack_end(*current4Label,false,true,10);

	current5Box->pack_start(*current5TextLabel,false,true,10);
	current5Box->pack_end(*current5Label,false,true,10);

	current6Box->pack_start(*current6TextLabel,false,true,10);
	current6Box->pack_end(*current6Label,false,true,10);

	current7Box->pack_start(*current7TextLabel,false,true,10);
	current7Box->pack_end(*current7Label,false,true,10);

	current8Box->pack_start(*current8TextLabel,false,true,10);
	current8Box->pack_end(*current8Label,false,true,10);

	current9Box->pack_start(*current9TextLabel,false,true,10);
	current9Box->pack_end(*current9Label,false,true,10);

	current10Box->pack_start(*current10TextLabel,false,true,10);
	current10Box->pack_end(*current10Label,false,true,10);

	current11Box->pack_start(*current11TextLabel,false,true,10);
	current11Box->pack_end(*current11Label,false,true,10);

	current12Box->pack_start(*current12TextLabel,false,true,10);
	current12Box->pack_end(*current12Label,false,true,10);

	current13Box->pack_start(*current13TextLabel,false,true,10);
	current13Box->pack_end(*current13Label,false,true,10);

	current14Box->pack_start(*current14TextLabel,false,true,10);
	current14Box->pack_end(*current14Label,false,true,10);

	current15Box->pack_start(*current15TextLabel,false,true,10);
	current15Box->pack_end(*current15Label,false,true,10);
	
	powerDistributionPanelBox->add(*voltageBox);	
	powerDistributionPanelBox->add(*current0Box);	
	powerDistributionPanelBox->add(*current1Box);	
	powerDistributionPanelBox->add(*current2Box);	
	powerDistributionPanelBox->add(*current3Box);	
	powerDistributionPanelBox->add(*current4Box);	
	powerDistributionPanelBox->add(*current5Box);	
	powerDistributionPanelBox->add(*current6Box);	
	powerDistributionPanelBox->add(*current7Box);	
	powerDistributionPanelBox->add(*current8Box);	
	powerDistributionPanelBox->add(*current9Box);	
	powerDistributionPanelBox->add(*current10Box);	
	powerDistributionPanelBox->add(*current11Box);	
	powerDistributionPanelBox->add(*current12Box);	
	powerDistributionPanelBox->add(*current13Box);	
	powerDistributionPanelBox->add(*current14Box);	
	powerDistributionPanelBox->add(*current15Box);	

	powerDistributionPanelFrame->add(*powerDistributionPanelBox);

	connectBox->add(*ipAddressLabel);
	connectBox->add(*ipAddressEntry);
	connectBox->add(*connectButton);
	connectBox->add(*connectionStatusLabel);

	sensorBox->add(*powerDistributionPanelFrame);

	topLevelBox->add(*connectBox);
	topLevelBox->add(*sensorBox);
	window->add(*topLevelBox);

	window->signal_delete_event().connect(sigc::ptr_fun(quit));
	window->show_all();	

}


 
int main(int argc, char** argv) { 
 	Glib::RefPtr<Gtk::Application> application = Gtk::Application::create(argc, argv, "edu.uark.razorbotz");
	setupGUI(application);

	if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
       		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        	return 1;
    	}
	int joystickCount=SDL_NumJoysticks();
	std::cout << "number of joysticks " << joystickCount << std::endl;

	SDL_Joystick *joy;
	// Check for joystick
	if(SDL_NumJoysticks()>0){
  		// Open joystick new_socket,
  		joy=SDL_JoystickOpen(0);
  
  		if(joy) {
    			printf("Opened Joystick 0\n");
    			printf("Name: %s\n", SDL_JoystickName(0));
    			printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
    			printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
    			printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
  		} else {
    			printf("Couldn't open Joystick 0\n");
		}
	}

	SDL_Event event;
	char buffer[1024] = {0}; 
	int valread=0;


	double speed=0;
	double increment=0.01;

	while(true){
		while(Gtk::Main::events_pending()){
			Gtk::Main::iteration();
		}
		if(!connected)continue;

		valread = read(sock, buffer, 1024); 
		if(valread==0){
			std::cout << "Lost Connection" << std::endl;
			connectionStatusLabel->set_text("Lost Connection");
			Gdk::RGBA red;
			red.set_rgba(1.0,0,0,1.0);
			connectionStatusLabel->override_background_color(red);
			connected=false;
			continue;
		}
		if(valread>0){
			//std::cout << "Got Message" << std::endl;
			uint8_t command=buffer[0];
			if(command==1){
				float voltage=parseFloat((uint8_t*)&buffer[1]);
				float current0=parseFloat((uint8_t*)&buffer[5]);
				float current1=parseFloat((uint8_t*)&buffer[9]);
				float current2=parseFloat((uint8_t*)&buffer[13]);
				float current3=parseFloat((uint8_t*)&buffer[17]);
				float current4=parseFloat((uint8_t*)&buffer[21]);
				float current5=parseFloat((uint8_t*)&buffer[25]);
				float current6=parseFloat((uint8_t*)&buffer[29]);
				float current7=parseFloat((uint8_t*)&buffer[33]);
				float current8=parseFloat((uint8_t*)&buffer[37]);
				float current9=parseFloat((uint8_t*)&buffer[41]);
				float current10=parseFloat((uint8_t*)&buffer[45]);
				float current11=parseFloat((uint8_t*)&buffer[49]);
				float current12=parseFloat((uint8_t*)&buffer[53]);
				float current13=parseFloat((uint8_t*)&buffer[57]);
				float current14=parseFloat((uint8_t*)&buffer[61]);
				float current15=parseFloat((uint8_t*)&buffer[65]);
				voltageLabel->set_label(std::to_string(voltage).c_str());
				current0Label->set_label(std::to_string(current0).c_str());
				current1Label->set_label(std::to_string(current1).c_str());
				current2Label->set_label(std::to_string(current2).c_str());
				current3Label->set_label(std::to_string(current3).c_str());
				current4Label->set_label(std::to_string(current4).c_str());
				current5Label->set_label(std::to_string(current5).c_str());
				current6Label->set_label(std::to_string(current6).c_str());
				current7Label->set_label(std::to_string(current7).c_str());
				current8Label->set_label(std::to_string(current8).c_str());
				current9Label->set_label(std::to_string(current9).c_str());
				current10Label->set_label(std::to_string(current10).c_str());
				current11Label->set_label(std::to_string(current11).c_str());
				current12Label->set_label(std::to_string(current12).c_str());
				current13Label->set_label(std::to_string(current13).c_str());
				current14Label->set_label(std::to_string(current14).c_str());
				current15Label->set_label(std::to_string(current15).c_str());
			}	
		}

		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_JOYHATMOTION:{
				std::cout << "joystick " << event.jhat.which << std::endl;
				std::cout << "timestamp " << event.jhat.timestamp << std::endl;
				std::cout << "value " << (uint32_t)event.jhat.value << std::endl;
				std::cout << "hat " << (uint32_t)event.jhat.hat << std::endl;

				uint8_t message[3];
				message[0]=3;
				message[1]=6;
				message[2]=event.jhat.value;

				send(sock, message, 3, 0); 
				
				break;
			}
			case SDL_JOYBUTTONDOWN:{
				std::cout << "joystick " << event.jbutton.which << std::endl;
				std::cout << "timestamp " << event.jbutton.timestamp << std::endl;
				std::cout << "button " << (uint32_t)event.jbutton.button << std::endl;
				std::cout << "state " << (uint32_t)event.jbutton.state << std::endl;

				uint8_t message[4];
				message[0]=4;	
				message[1]=5;
				message[2]=event.jbutton.button;
				message[3]=event.jbutton.state;

				send(sock, message, 4, 0); 

				break;
			}
			case SDL_JOYBUTTONUP:{
				std::cout << "joystick " << event.jbutton.which << std::endl;
				std::cout << "timestamp " << event.jbutton.timestamp << std::endl;
				std::cout << "button " << (uint32_t)event.jbutton.button << std::endl;
				std::cout << "state " << (uint32_t)event.jbutton.state << std::endl;

				uint8_t message[4];
				message[0]=4;	
				message[1]=5;
				message[2]=event.jbutton.button;
				message[3]=event.jbutton.state;

				send(sock, message, 4, 0); 

				break;
			}
			case SDL_JOYAXISMOTION:
				//std::cout << (int)event.jaxis.axis << "    " << event.jaxis.value << std::endl;
				if(event.jaxis.axis == 0){
					uint8_t command=1;// roll 
					float value=(float) event.jaxis.value/-32768.0;

					uint8_t message[6];
					message[0]=6;
					message[1]=command;
					insertFloat(value,&message[2]);
							
					send(sock, message, 6, 0); 
				}
				if(event.jaxis.axis == 1){
					uint8_t command=2;// pitch 
					float value=(float) event.jaxis.value/-32768.0;

					uint8_t message[6];
					message[0]=6;
					message[1]=command;
					insertFloat(value,&message[2]);
							
					send(sock, message, 6, 0); 
				}
				if(event.jaxis.axis == 2){
					uint8_t command=3;// throttle 
					float value=(float) event.jaxis.value/-32768.0;

					uint8_t message[6];
					message[0]=6;
					message[1]=command;
					insertFloat(value,&message[2]);
								
					send(sock, message, 6, 0); 
				}
				if(event.jaxis.axis == 3){
					uint8_t command=4;// yaw 
					float value=(float) event.jaxis.value/-32768.0;

					uint8_t message[6];
					message[0]=6;
					message[1]=command;
					insertFloat(value,&message[2]);
							
					send(sock, message, 6, 0); 
				}
				break;
			default:
				break;
			}
		}

//		usleep(100000);
	}
	return 0; 
}

