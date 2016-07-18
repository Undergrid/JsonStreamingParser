/*
Because sometimes, you just can't parse json via a webhook.

This library is a modified fork of squix78's json-streaming-parser an Arduino library for parsing potentially huge json 
streams on devices with scarce memory.

Changes from squix78's version:

1) Layout changed so it could be deployed as a particle library.
2) Only one startDocument will be raised at the start of a document rather than one for each non-json character.
3) Keys are now passed to the listener as part of the startObject(), startArray() or value() event they are associated 
   with rather than as seperate events.

How to use
----------

This is a streaming parser, which means that you feed a stream of chars into the parser and you take out from that 
stream whatever you are interested in. In order to do that you will create a subclass of JsonListener class and 
implement methods which will be notified in case of certain events in the feed occure. Available events are:

startDocument()
endDocument()

startObject(String key)
endObject()

startArray(String key)
endArray()

value(String key, String value)

In your implementation of these methods you will have to write problem specific code to find the parts of the 
document that you are interested in. Please see the example to understand what that means. In the example the 
ExampleListener implements the event methods declared in the JsonListener interface and prints to the serial 
console when they are called.

*/


#include "JsonStreamingParser/JsonStreamingParser.h"
#include "JsonStreamingParser/JsonListener.h"
#include "ExampleListener.h"

JsonStreamingParser parser;
ExampleListener listener;

void setup() {
  Serial.begin(9600);
  // Wait for a character on the serial port.  Connect with a terminal emulator and press any key to see the output
  while(!Serial.available()) Particle.process(); 
  Serial.println(System.freeMemory());
  parser.setListener(&listener);
  // put your setup code here, to run once:
  char json[] = "{\"a\":3, \"b\":{\"c\":\"4\"}, \"e\":[{\"f\":5},{\"g\":6}]}";
  for (int i = 0; i < sizeof(json); i++) {
    parser.parse(json[i]); 
  }
  Serial.println(System.freeMemory());
}

void loop() {
}