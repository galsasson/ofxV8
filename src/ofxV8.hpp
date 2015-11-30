//
//  ofxV8.hpp
//  biopool-kiosk
//
//  Created by Gal Sasson on 11/28/15.
//
//

#ifndef ofxV8_hpp
#define ofxV8_hpp

#include <stdio.h>
#include "ofMain.h"
#include "include/v8.h"
#include "include/libplatform/libplatform.h"

class ofxV8
{
public:
	static void helloWorld();
	
};

class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
public:
	virtual void* Allocate(size_t length) {
		void* data = AllocateUninitialized(length);
		return data == NULL ? data : memset(data, 0, length);
	}
	virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
	virtual void Free(void* data, size_t) { free(data); }
};

#endif /* ofxV8_hpp */
