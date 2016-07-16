# JsonStreamingParser

Because sometimes, you just can't parse json via a webhook.

This library is a modified fork of Squix78's json-streaming-parser (https://github.com/squix78/json-streaming-parser) an Arduino library for parsing potentially huge json streams on devices with scarce memory.  Which in turn is a port of Salsify's PHP based json streaming parser (https://github.com/salsify/jsonstreamingparser).

## Changes from Squix78's version:

1) Layout changed so it could be deployed as a particle library.
2) Only one startDocument will be raised at the start of a document rather than one for each non-json character (so it will ignore HTTP headers for example).
3) Keys are now passed to the listener as part of the startObject(), startArray() or value() event they are associated with rather than as seperate events.

## Why yet another JSON parser?

Many people use Particle webhooks for parsing large JSON files, but sometimes your stuck behind a a corporate firewall or corporate policy won't allow you to send data to an off-site webservice and you have to do everything locally.  

Large JSON strings can quickly become a problem and if there's no way to limit the data the server is sending you, you need a streaming parser like this one to help you out.

When working with small (connected) devices you might quickly get to the point where you need to process potentially huge JSON object received from a REST interface. All libraries for processing JSON objects on the Arduino platform had some deficiencies which led me to create one on my own. Not really being an expert in writing parsers I miserably failed the first time.

Squix78's (on GitHub) took Salsify's PHP based parser and ported it to C++ for the Arduino system.  I've taken that parser and modified it to be used as a library for Particle devices, plus made a few changes noted above.

## Why a streaming parser?

Generally speaking when parsing data you have two options to make sense of this data: you either create a document object model (DOM) which contains the whole information of that document and lets you retrieve the nodes with random access. A DOM parser needs the whole document to start parsing and only lets you access the data after it has finished the process. The other option you have when parsing a document is to process it char by char (or byte by byte) while it becomes available to your client code. Compared to the DOM parser this has two advantages: a) you can react the data as soon as meaningful parts are available and b) you can drop information as soon as the parser has processed it. This reduces the memory consumption a lot, especially if you retrieve huge documents when only being interested by a small subset of it. But this efficiency comes at a price: your code will have to do more "magic" than with a DOM parser, the business logic becomes part of the parser.

## How to use

This is a streaming parser, which means that you feed a stream of chars into the parser and you take out from that stream whatever you are interested in. In order to do that you will create a subclass of JsonListener class and implement methods which will be notified in case of certain events in the feed occure. Available events are:

* startDocument()
* endDocument()
* startArray(String key)
* endArray()
* startObject(String key)
* endObject()
* value(String key, String value)

In your implementation of these methods you will have to write problem specific code to find the parts of the document that you are interested in. Please see the example to understand what that means. In the example the ExampleListener implements the event methods declared in the JsonListener interface and prints to the serial console when they are called.

## License

This code is available under the MIT license, which basically means that you can use, modify the distribute the code as long as you give credits to me (and Squix78 and Salsify) and add a reference back to this repository. Please read https://github.com/squix78/json-streaming-parser/blob/master/LICENSE for more detail...

## Credits

First of all I'd like to thank Squix78 and Salsify for making their parsers available to the public. 

You find their repositories here: 

Squix78 - https://github.com/squix78/json-streaming-parser

Salsify - https://github.com/salsify/jsonstreamingparser

