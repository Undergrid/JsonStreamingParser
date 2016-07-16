#pragma once

#include "application.h"
#include "JsonListener.h"

class ExampleListener: public JsonListener {

  public:
    void whitespace(char c);

    void value(String key, String value);

    void startDocument();
    void endDocument();

    void startArray(String key);
    void endArray();
    
    void startObject(String key);
    void endObject();
};