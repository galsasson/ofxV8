//
//  ofxV8.cpp
//  biopool-kiosk
//
//  Created by Gal Sasson on 11/28/15.
//
//

#include "ofxV8.hpp"

using namespace v8;

void ofxV8::helloWorld() {
	// Initialize V8.
	V8::InitializeICU();
	V8::InitializeExternalStartupData("biopool-kioskDebug");
	Platform* platform = platform::CreateDefaultPlatform();
	V8::InitializePlatform(platform);
	V8::Initialize();

	// Create a new Isolate and make it the current one.
	ArrayBufferAllocator allocator;
	Isolate::CreateParams create_params;
	create_params.array_buffer_allocator = &allocator;
	Isolate* isolate = Isolate::New(create_params);
	{
		Isolate::Scope isolate_scope(isolate);

		// Create a stack-allocated handle scope.
		HandleScope handle_scope(isolate);

		// Create a new context.
		Local<Context> context = Context::New(isolate);

		// Enter the context for compiling and running the hello world script.
		Context::Scope context_scope(context);

		// Create a string containing the JavaScript source code.
		Local<String> source =
		String::NewFromUtf8(isolate, "'Hello' + ', World!'",
							NewStringType::kNormal).ToLocalChecked();

		// Compile the source code.
		Local<Script> script = Script::Compile(context, source).ToLocalChecked();

		// Run the script to get the result.
		Local<Value> result = script->Run(context).ToLocalChecked();

		// Convert the result to an UTF8 string and print it.
		String::Utf8Value utf8(result);
		printf("%s\n", *utf8);
	}

	// Dispose the isolate and tear down V8.
	isolate->Dispose();
	V8::Dispose();
	V8::ShutdownPlatform();
	delete platform;
	return 0;
}