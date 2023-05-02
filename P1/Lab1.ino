/*
  Traffic light simulation. 
*/

// digital write ports.
int led[] = {2,3,4,5,6};
// digital read ports.
int valRead[] = {21,20,19,18,17};

// id assignment.
int traffic_led_red = led[0];
int traffic_led_yellow = led[1];
int traffic_led_green = led[2];
int ped_led_red = led[3];
int ped_led_green = led[4];

// normal behavior timings.
int red_secs = 8;
int yellow_secs = 2;
int green_secs = 20;


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
  	// initialize digital pin LED_BUILTIN as an output.
	for (int i = 0; i < 5; i++){
		pinMode(led[i], OUTPUT);
		pinMode(valRead[i], INPUT);
	}
}

// Reads digital pins and prints out 
int read_pins(){
	int hour[5] = {0,0,0,0,0}; 
	for (int i = 0; i < 5; i++){
		hour[i] = digitalRead(valRead[i]);
	}
	
	int res = 0;
	int power = 1;
	
	for (int i = 0; i < 5; i++) {
		res += hour[(5 - 1) - i] * power;
	    	power *= 2;
	}
	return res;
}

// the loop function runs over and over again forever
void loop() {
	// Clear all leds before each loop.
	for (int i = 0; i < 5; i++){
		digitalWrite(led[i], LOW);
	}
	
	// Read Hour passed by digital ports.
	int current_hour = read_pins();
	Serial.println(current_hour);
	
	// Nighttime behavior if between midnight and 5am.
	if (current_hour >= 24 || current_hour <= 5){		
		digitalWrite(ped_led_red, HIGH);
		digitalWrite(traffic_led_red, HIGH);
		delay(1000); 
		digitalWrite(ped_led_red, LOW);
		digitalWrite(traffic_led_red, LOW);	
		delay(1000); 
		return;
	}
	
	// Traffic Light Crossing timers, for ped and transit.
	digitalWrite(traffic_led_green, HIGH);
	digitalWrite(ped_led_red, HIGH);
	
	delay(green_secs * 1000);       
	digitalWrite(traffic_led_green, LOW);
	digitalWrite(traffic_led_yellow, HIGH);
	
	delay(yellow_secs * 1000);       
	
	digitalWrite(traffic_led_yellow, LOW);
	digitalWrite(traffic_led_red, HIGH);
	
	digitalWrite(ped_led_red, LOW);
	digitalWrite(ped_led_green, HIGH);
	
	delay(red_secs * 1000); 
}
