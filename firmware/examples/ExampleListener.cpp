#include "ExampleListener.h"
#include "JsonStreamingParser/JsonListener.h"


void ExampleListener::whitespace(char c) {
  Serial.println("whitespace");
}

void ExampleListener::value(String key, String value) {
  Serial.print("key: " + key + ", ");
  Serial.println("value: " + value);
}

void ExampleListener::startDocument() {
  Serial.println("start document");
}

void ExampleListener::endDocument() {
  Serial.println("end document. ");
}

void ExampleListener::startArray(String key) {
   Serial.print("start array: ");
   Serial.println(key);
}

void ExampleListener::endArray() {
  Serial.println("end array. ");
}

void ExampleListener::startObject(String key) {
   Serial.print("start object:");
   Serial.println(key);
}

void ExampleListener::endObject() {
  Serial.println("end object. ");
}
