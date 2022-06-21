#include <Arduino.h>
#include "gui/gui.h"
#include "SPIFFS.h"
#include "btn_cb.h"
#include "gui/app/app.h"
// button mybutton1({14},1,{buttonDefaultConfig});
// button mybutton2({21},2,{buttonDefaultConfig});
// button mybutton3({27},3,{buttonDefaultConfig});
void setup()
{
    // Serial.begin(115200);
    // log_w("in setup app_list %x is %d long",app_t::app_list_ptr,app_t::app_list_ptr->size());
    // helloworld_app* main_helloworld_app = new helloworld_app(&hello_world_app_info);
    log_d("CPU Freq: %d",getCpuFrequencyMhz());
    ButtonEventHandler = indrv::btn_handler;
    button::setUp(buttonDefaultSetup);
    
    pinMode(22, OUTPUT);
    if (!SPIFFS.begin()){
        log_e("SPIFFS Mount Failed");
    }
    else{
        log_w("SPIFFS Mounted");
        // File root = SPIFFS.open("/");
        // File file = root.openNextFile(); 
        // while(file){
        //     Serial.print("FILE: ");
        //     Serial.println(file.name());
        //     file = root.openNextFile();
        // }
    }
    guiSetUp();digitalWrite(22,HIGH);
}

void loop()
{
    // printf("%d\n",GPIO_ns::Read({14}));
    // vTaskDelay(1000);
    // Serial.println(GIT_REV);
    // log_w("Set to High");
    digitalWrite(22,HIGH);
    vTaskDelay(5);
    // log_w("Set to Low");
    // digitalWrite(22,LOW);
    // vTaskDelay(5);
}

// //--------------------------------
// #include <Arduino.h>
// #include "gui/gui.h"
// #include "SPIFFS.h"
// static const int LEFT_PIN=14;
// static const int CENTER_PIN=21;
// static const int RIGHT_PIN=27;
// void setup()
// {
//     Serial.begin(115200);
//     pinMode(LEFT_PIN, INPUT);
//     pinMode(CENTER_PIN, INPUT);
//     pinMode(RIGHT_PIN, INPUT);
// }

// void loop()
// {
//     log_w("left:%d right:%d center:%d",digitalRead(LEFT_PIN),digitalRead(RIGHT_PIN),digitalRead(CENTER_PIN));
//     vTaskDelay(1000);
// }

// //--------------------------------

// // A basic everyday NeoPixel strip test program.
// #include <Adafruit_NeoPixel.h>
// #define LED_PIN    19
// #define LED_COUNT 5

// // Declare our NeoPixel strip object:
// Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// // Some functions of our own for creating animated effects -----------------
// void colorWipe(uint32_t color, int wait) {
//   for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
//     strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
//     strip.show();                          //  Update strip to match
//     delay(wait);                           //  Pause for a moment
//   }
// }

// // Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// // a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// // between frames.
// void theaterChase(uint32_t color, int wait) {
//   for(int a=0; a<10; a++) {  // Repeat 10 times...
//     for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
//       strip.clear();         //   Set all pixels in RAM to 0 (off)
//       // 'c' counts up from 'b' to end of strip in steps of 3...
//       for(int c=b; c<strip.numPixels(); c += 3) {
//         strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
//       }
//       strip.show(); // Update strip with new contents
//       delay(wait);  // Pause for a moment
//     }
//   }
// }

// // Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
// void rainbow(int wait) {
//   // Hue of first pixel runs 5 complete loops through the color wheel.
//   // Color wheel has a range of 65536 but it's OK if we roll over, so
//   // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
//   // means we'll make 5*65536/256 = 1280 passes through this loop:
//   for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
//     // strip.rainbow() can take a single argument (first pixel hue) or
//     // optionally a few extras: number of rainbow repetitions (default 1),
//     // saturation and value (brightness) (both 0-255, similar to the
//     // ColorHSV() function, default 255), and a true/false flag for whether
//     // to apply gamma correction to provide 'truer' colors (default true).
//     strip.rainbow(firstPixelHue);
//     // Above line is equivalent to:
//     // strip.rainbow(firstPixelHue, 1, 255, 255, true);
//     strip.show(); // Update strip with new contents
//     delay(wait);  // Pause for a moment
//   }
// }

// // Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
// void theaterChaseRainbow(int wait) {
//   int firstPixelHue = 0;     // First pixel starts at red (hue 0)
//   for(int a=0; a<30; a++) {  // Repeat 30 times...
//     for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
//       strip.clear();         //   Set all pixels in RAM to 0 (off)
//       // 'c' counts up from 'b' to end of strip in increments of 3...
//       for(int c=b; c<strip.numPixels(); c += 3) {
//         // hue of pixel 'c' is offset by an amount to make one full
//         // revolution of the color wheel (range 65536) along the length
//         // of the strip (strip.numPixels() steps):
//         int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
//         uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
//         strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
//       }
//       strip.show();                // Update strip with new contents
//       delay(wait);                 // Pause for a moment
//       firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
//     }
//   }
// }

// // setup() function -- runs once at startup --------------------------------

// void setup() {
//   strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
//   strip.show();            // Turn OFF all pixels ASAP
//   strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
// }


// // loop() function -- runs repeatedly as long as board is on ---------------

// void loop() {
//   // Fill along the length of the strip in various colors...
//   colorWipe(strip.Color(255,   0,   0), 50); // Red
//   colorWipe(strip.Color(  0, 255,   0), 50); // Green
//   colorWipe(strip.Color(  0,   0, 255), 50); // Blue

//   // Do a theater marquee effect in various colors...
//   theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
//   theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
//   theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

//   rainbow(10);             // Flowing rainbow cycle along the whole strip
//   theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
// }




// //--------------------------------




// #include <BH1750.h>
// #include <Wire.h>

// /*
//   BH1750 can be physically configured to use two I2C addresses:
//     - 0x23 (most common) (if ADD pin had < 0.7VCC voltage)
//     - 0x5C (if ADD pin had > 0.7VCC voltage)

//   Library uses 0x23 address as default, but you can define any other address.
//   If you had troubles with default value - try to change it to 0x5C.

// */
// BH1750 lightMeter(0x23);

// void setup() {

//   Serial.begin(115200);

//   // Initialize the I2C bus (BH1750 library doesn't do this automatically)
//   Wire.begin(32,33);
//   // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);

//   /*

//     BH1750 has six different measurement modes. They are divided in two groups;
//     continuous and one-time measurements. In continuous mode, sensor
//     continuously measures lightness value. In one-time mode the sensor makes
//     only one measurement and then goes into Power Down mode.

//     Each mode, has three different precisions:

//       - Low Resolution Mode - (4 lx precision, 16ms measurement time)
//       - High Resolution Mode - (1 lx precision, 120ms measurement time)
//       - High Resolution Mode 2 - (0.5 lx precision, 120ms measurement time)

//     By default, the library uses Continuous High Resolution Mode, but you can
//     set any other mode, by passing it to BH1750.begin() or BH1750.configure()
//     functions.

//     [!] Remember, if you use One-Time mode, your sensor will go to Power Down
//     mode each time, when it completes a measurement and you've read it.

//     Full mode list:

//       BH1750_CONTINUOUS_LOW_RES_MODE
//       BH1750_CONTINUOUS_HIGH_RES_MODE (default)
//       BH1750_CONTINUOUS_HIGH_RES_MODE_2

//       BH1750_ONE_TIME_LOW_RES_MODE
//       BH1750_ONE_TIME_HIGH_RES_MODE
//       BH1750_ONE_TIME_HIGH_RES_MODE_2

//   */

//   // begin returns a boolean that can be used to detect setup problems.
//   if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
//     Serial.println(F("BH1750 Advanced begin"));
//   } else {
//     Serial.println(F("Error initialising BH1750"));
//   }
// }

// void loop() {
//   if (lightMeter.measurementReady()) {
//     float lux = lightMeter.readLightLevel();
//     Serial.print("Light: ");
//     Serial.print(lux);
//     Serial.println(" lx");
//   }
// }

//-----------------------------------------------------
// #include <Wire.h>

// #include "SparkFun_LIS2DH12.h" //Click here to get the library: http://librarymanager/All#SparkFun_LIS2DH12
// SPARKFUN_LIS2DH12 accel;       //Create instance

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println("SparkFun Accel Example");

//   Wire.begin(32,33);

//   if (accel.begin() == false)
//   {
//     Serial.println("Accelerometer not detected. Check address jumper and wiring. Freezing...");
//     vTaskDelay(portMAX_DELAY);
//   }
// }

// void loop()
// {
//   //Print accel values only if new data is available
//   if (accel.available())
//   {
//     float accelX = accel.getX();
//     float accelY = accel.getY();
//     float accelZ = accel.getZ();
//     float tempC = accel.getTemperature();

//     Serial.print("Acc [mg]: ");
//     Serial.print(accelX, 1);
//     Serial.print(" x, ");
//     Serial.print(accelY, 1);
//     Serial.print(" y, ");
//     Serial.print(accelZ, 1);
//     Serial.print(" z, ");
//     Serial.print(tempC, 1);
//     Serial.print("C");
//     Serial.println();

//     //    int rawX = accel.getRawX();
//     //    int rawY = accel.getRawY();
//     //    int rawZ = accel.getRawZ();
//     //
//     //    Serial.print("Acc raw: ");
//     //    Serial.print(rawX);
//     //    Serial.print(" x, ");
//     //    Serial.print(rawY);
//     //    Serial.print(" y, ");
//     //    Serial.print(rawZ);
//     //    Serial.print(" z");
//     //    Serial.println();
//   }
// }

//-----------------------------------------------------

// /*
//   Rui Santos
//   Complete project details at https://RandomNerdTutorials.com/esp32-microsd-card-arduino/
  
//   This sketch can be found at: Examples > SD(esp32) > SD_Test
// */

// #include "FS.h"
// #include "SD.h"
// #include "SPI.h"

// void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
//   Serial.printf("Listing directory: %s\n", dirname);

//   File root = fs.open(dirname);
//   if(!root){
//     Serial.println("Failed to open directory");
//     return;
//   }
//   if(!root.isDirectory()){
//     Serial.println("Not a directory");
//     return;
//   }

//   File file = root.openNextFile();
//   while(file){
//     if(file.isDirectory()){
//       Serial.print("  DIR : ");
//       Serial.println(file.name());
//       if(levels){
//         listDir(fs, file.name(), levels -1);
//       }
//     } else {
//       Serial.print("  FILE: ");
//       Serial.print(file.name());
//       Serial.print("  SIZE: ");
//       Serial.println(file.size());
//     }
//     file = root.openNextFile();
//   }
// }

// void createDir(fs::FS &fs, const char * path){
//   Serial.printf("Creating Dir: %s\n", path);
//   if(fs.mkdir(path)){
//     Serial.println("Dir created");
//   } else {
//     Serial.println("mkdir failed");
//   }
// }

// void removeDir(fs::FS &fs, const char * path){
//   Serial.printf("Removing Dir: %s\n", path);
//   if(fs.rmdir(path)){
//     Serial.println("Dir removed");
//   } else {
//     Serial.println("rmdir failed");
//   }
// }

// void readFile(fs::FS &fs, const char * path){
//   Serial.printf("Reading file: %s\n", path);

//   File file = fs.open(path);
//   if(!file){
//     Serial.println("Failed to open file for reading");
//     return;
//   }

//   Serial.print("Read from file: ");
//   while(file.available()){
//     Serial.write(file.read());
//   }
//   file.close();
// }

// void writeFile(fs::FS &fs, const char * path, const char * message){
//   Serial.printf("Writing file: %s\n", path);

//   File file = fs.open(path, FILE_WRITE);
//   if(!file){
//     Serial.println("Failed to open file for writing");
//     return;
//   }
//   if(file.print(message)){
//     Serial.println("File written");
//   } else {
//     Serial.println("Write failed");
//   }
//   file.close();
// }

// void appendFile(fs::FS &fs, const char * path, const char * message){
//   Serial.printf("Appending to file: %s\n", path);

//   File file = fs.open(path, FILE_APPEND);
//   if(!file){
//     Serial.println("Failed to open file for appending");
//     return;
//   }
//   if(file.print(message)){
//       Serial.println("Message appended");
//   } else {
//     Serial.println("Append failed");
//   }
//   file.close();
// }

// void renameFile(fs::FS &fs, const char * path1, const char * path2){
//   Serial.printf("Renaming file %s to %s\n", path1, path2);
//   if (fs.rename(path1, path2)) {
//     Serial.println("File renamed");
//   } else {
//     Serial.println("Rename failed");
//   }
// }

// void deleteFile(fs::FS &fs, const char * path){
//   Serial.printf("Deleting file: %s\n", path);
//   if(fs.remove(path)){
//     Serial.println("File deleted");
//   } else {
//     Serial.println("Delete failed");
//   }
// }

// void testFileIO(fs::FS &fs, const char * path){
//   File file = fs.open(path);
//   static uint8_t buf[512];
//   size_t len = 0;
//   uint32_t start = millis();
//   uint32_t end = start;
//   if(file){
//     len = file.size();
//     size_t flen = len;
//     start = millis();
//     while(len){
//       size_t toRead = len;
//       if(toRead > 512){
//         toRead = 512;
//       }
//       file.read(buf, toRead);
//       len -= toRead;
//     }
//     end = millis() - start;
//     Serial.printf("%u bytes read for %u ms\n", flen, end);
//     file.close();
//   } else {
//     Serial.println("Failed to open file for reading");
//   }


//   file = fs.open(path, FILE_WRITE);
//   if(!file){
//     Serial.println("Failed to open file for writing");
//     return;
//   }

//   size_t i;
//   start = millis();
//   for(i=0; i<2048; i++){
//     file.write(buf, 512);
//   }
//   end = millis() - start;
//   Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
//   file.close();
// }

// void setup(){
//   Serial.begin(115200);
//   SPIClass* sd_spi = new SPIClass(HSPI);
//   sd_spi->begin(13,15,25);
//   if(!SD.begin(26,*sd_spi)){
//     Serial.println("Card Mount Failed");
//     return;
//   }
//   uint8_t cardType = SD.cardType();

//   if(cardType == CARD_NONE){
//     Serial.println("No SD card attached");
//     return;
//   }

//   Serial.print("SD Card Type: ");
//   if(cardType == CARD_MMC){
//     Serial.println("MMC");
//   } else if(cardType == CARD_SD){
//     Serial.println("SDSC");
//   } else if(cardType == CARD_SDHC){
//     Serial.println("SDHC");
//   } else {
//     Serial.println("UNKNOWN");
//   }

//   uint64_t cardSize = SD.cardSize() / (1024 * 1024);
//   Serial.printf("SD Card Size: %lluMB\n", cardSize);

//   listDir(SD, "/", 0);
//   createDir(SD, "/mydir");
//   listDir(SD, "/", 0);
//   removeDir(SD, "/mydir");
//   listDir(SD, "/", 2);
//   writeFile(SD, "/hello.txt", "Hello ");
//   appendFile(SD, "/hello.txt", "World!\n");
//   readFile(SD, "/hello.txt");
//   deleteFile(SD, "/foo.txt");
//   renameFile(SD, "/hello.txt", "/foo.txt");
//   readFile(SD, "/foo.txt");
//   testFileIO(SD, "/test.txt");
//   Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
//   Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
// }

// void loop(){

// }


//-----------------------------------------------------
// #include <Arduino.h>

// #include <WiFi.h>
// const char *ssid = "btw_i_use_arch";    // SSID
// const char *password = "azxcvbnm"; // Password
// void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
//     log_e("Disconnected from WiFi access point\nWiFi lost connection. Reason: %d\nTrying to Reconnect",info.disconnected.reason);
//     WiFi.begin(ssid, password);
// }

// void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){
//     log_w("Connected to AP successfully!");
// }

// void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info){
//     log_w("Got IP address: %s",WiFi.localIP().toString().c_str());
// }

// void setup()
// {

//     /* Connect WiFi */
//     WiFi.mode(WIFI_STA);
//     WiFi.onEvent(WiFiGotIP, SYSTEM_EVENT_STA_GOT_IP);
//     WiFi.onEvent(WiFiStationConnected, SYSTEM_EVENT_STA_CONNECTED);
//     WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
//     WiFi.begin(ssid, password);
//     vTaskDelay(1000);
    
// }
// // extern int32_t mark;
// void loop()
// {
//     log_w("RSSI:%d\n",WiFi.RSSI());
//     vTaskDelay(300);
// }

