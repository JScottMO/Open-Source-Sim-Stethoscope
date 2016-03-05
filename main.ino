//This code is in draft form. It is a for a open source hardward/software 
//project to deliver electronic delivering of findings in a clinical simulation 
//environment. 

//This code is for an electronic stethescope that reads RFID tags and then 
//plays sounds based on the tags that are detected. For the audio code we 
//borrowed from the examples provided by tinycircuits: 
//https://codebender.cc/sketch:46085

//Some code was also taken from Reading RFID Tags with an Arduino by MrkTrussell
// http://www.instructables.com/id/Reading-RFID-Tags-with-an-Arduino/step5/Final-Sketch/

//The hardware consists of an ID-12LA RFID reader from ID Innovations
//That is connected to a TinyDuino with the TinyDuino Audio Board, 
// Memory Board, USB Board, and Protoboard

//Here are the pins that are used by the boards:
//USB Board  	Digital Pin 0
//				Digital Pin 1
//Audio Board	Digital Pin 2
//				Digital Pin 3
//				Digital Pin 4
//Memory Board	Digital Pin 10
//				Digital Pin 11
//				Digital Pin 12
//				Digital Pin 13
//Proto Board	Digital Pin 8 Connected to D0 on the RFID Reader
//				Digital Pin 9 Not connected but refered by softserial
//				Analog Pin 0 Connected to Res 
//Note to self, the RES pin can be used to see of the reader is stil over the 
//same RFID chip
//In addition the following connectiosn are made from the Proto Board to the 
//RFID Reader
//GND --> GND
//FORM --> GND (defauly the RFID chip to RS232)
//VCC --> 5V

//Note, this must be powered by USB or a large battery source. You
//cannot power it from the coin cell. 

#include "WaveUtil.h"
#include "WaveHC.h"
#include <SoftwareSerial.h>

#define RFIDResetPin A0

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the filesystem on the card
FatReader f;      // This holds the information for the file we're play

WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time
SoftwareSerial rfid(8, 9); 

bool found =0;

char* allowedTags[] = {
"7C00563C5D", // Heart 1 Tag 
"7C0055ED87", // Heart 2 Tag 
"7C0055FAF6", // Heart 3 Tag 
"7C0055EE46", // Lung 1 Tag 
"7C005634C8", // Lung 2 Tag 
"7C00561822", // Lung 3 Tag 
};

char* SIMfiletoplay[] = {
"h1.wav", // Heart 1
"h2.wav", // Heart 2
"h3.wav", // Heart 3
"l1.wav", // Lung 1
"l2.wav", // Lung 2
"l3.wav", // Lung 3
};

int numberOfTags = sizeof(allowedTags)/sizeof(allowedTags[0]);

// this handy function will return the number of bytes currently free in RAM, great for debugging!   
int freeRam(void){
  extern int  __bss_end; 
  extern int  *__brkval; 
  int free_memory; 
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end); 
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval); 
  }
  return free_memory; 
} 

void sdErrorCheck(void)
{
  if (!card.errorCode()) return;
  Serial.print("\n\rSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  Serial.print(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

void setup()  
{
  pinMode(RFIDResetPin, OUTPUT);
  digitalWrite(RFIDResetPin, HIGH);
  Serial.begin(9600);
  rfid.begin(9600);
  byte i;
  Serial.print("Booting up Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(freeRam());      // if this is under 150 bytes it may spell trouble!
  
  // Set the output pins for the DAC control. This pins are defined in the library
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
 
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    Serial.println("Card init. failed!");  // Something went wrong, lets print out why
    sdErrorCheck();
    while(1);                            // then 'halt' - do nothing!
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
 
// Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {     // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                             // we found one, lets bail
  }
  if (part == 5) {                       // if we ended up not finding one  :(
    Serial.println("No valid FAT partition!");
    sdErrorCheck();      // Something went wrong, lets print out why
    while(1);                            // then 'halt' - do nothing!
  }
  
  if (!root.openRoot(vol)) {
    Serial.println("Can't open root dir!"); // Something went wrong,
    while(1);                             // then 'halt' - do nothing!
  }
  
}


void loop() {
	delay(100);
	byte val = 0;
	byte checksum = 0;
	byte bytesRead = 0;
	byte tempByte = 0;
	byte tagBytes[6]; // "Unique" tags are only 5 bytes but we need an extra byte for the checksum
	char tagValue[10];
	if(rfid.available() > 0)
	{
		if((val = rfid.read()) == 2) { // Check for header	
		//bytesRead = 0;	
			while (bytesRead < 12) { // Read 10 digit code + 2 digit checksum
				if(rfid.available() > 0) {
					val = rfid.read();
					// Append the first 10 bytes (0 to 9) to the raw tag value
					if (bytesRead < 10)
					{
					tagValue[bytesRead] = val;
					}
				
					// Check if this is a header or stop byte before the 10 digit reading is complete
					if((val == 0x0D)||(val == 0x0A)||(val == 0x03)||(val == 0x02)) {
					break; // Stop reading
					}
					if ((val >= '0') && (val <= '9')) {
					val = val - '0';
					}
					else if ((val >= 'A') && (val <= 'F')) {
					val = 10 + val - 'A';
					}
					if (bytesRead & 1 == 1) {
					// Make space for this hex-digit by shifting the previous digit 4 bits to the left
					tagBytes[bytesRead >> 1] = (val | (tempByte << 4));	
					if (bytesRead >> 1 != 5) { // If we're at the checksum byte,
					checksum ^= tagBytes[bytesRead >> 1]; 
					};
					} 
					else {
					tempByte = val; 
					};
					bytesRead++;
				} 
			}
		}
		if (bytesRead == 12) { // 12 digit read is complete
		 	tagValue[10] = '\0'; // Null-terminate the string
		  	delay(100);
		    found = 0;
		  	for (int xx = 0; xx < numberOfTags; xx++) {
				if(strcmp(tagValue, allowedTags[xx]) == 0){
	    			found = 1;
		  			playcomplete(SIMfiletoplay[xx]);
					resetReader(); //reset the RFID reader
		  			break;
					}
		  	}
		  	if (found == 0){
			 	playcomplete("tgiderr.wav");
			 	playcomplete("tagidis.wav");
			  	char filetoplayerror [6];
				for (int iee = 0; iee < 10; iee++) {
		    		filetoplayerror [0]=tagValue[iee];
		    		filetoplayerror [1]='.';
		    		filetoplayerror [2]='w';
		    		filetoplayerror [3]='a';
		    		filetoplayerror [4]='v';
		    		filetoplayerror [5] = '\0'; // 
		    		playcomplete(filetoplayerror);
	    			}
		  	}
		 }
	 bytesRead = 0;
	 }
}

void playcomplete(char *name) {
  playfile(name);
  while (wave.isplaying) {
  }
}
 
void playfile(char *name) {
  if (wave.isplaying) {
    wave.stop(); 
  }
  if (!f.open(root, name)) {
    putstring("Couldn't open file "); Serial.print(name); return;
  }
  if (!wave.create(f)) {
    putstring_nl("Not a valid WAV"); return;
  }
  wave.play();
}

void resetReader(){
  digitalWrite(RFIDResetPin, LOW);
  delay(250);
  digitalWrite(RFIDResetPin, HIGH);
}
