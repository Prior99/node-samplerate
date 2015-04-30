#include <v8.h>
#include <nan.h>
#include <node_buffer.h>
#include <iostream>

#include "../deps/libsamplerate/src/samplerate.h"

using namespace node;
using namespace v8;

static NAN_METHOD(Resample) {
	NanScope();
	//First, gather all attributes
	Local<Object> inputBuffer = Local<Object>::Cast(args[0]); // Buffer containing the input
	unsigned int fromRatio = (unsigned int) args[1]->NumberValue(); // Rate from which we convert (e.g. 22050 Hz)
	unsigned int toRatio = (unsigned int) args[2]->NumberValue(); // Rate to which we convert ()
	unsigned int channels = (unsigned int) args[3]->NumberValue(); // Amount of channels (1m = mono, 2 = stereo, 3 = ...)

	// A frame is a sample * amount of channels so for mono one frame
	// contains one sample, for stereo it contains to samples

	double ratio = toRatio / (double) fromRatio; // Ratio calculated by dividing output-ratio by input-ratio

	unsigned int lengthIn = Buffer::Length(inputBuffer) / sizeof(short); //Length of the input data
	unsigned int lengthOut = lengthIn * ratio + 1; //Length of the outputdata

	long inputFrames = (lengthIn / channels); // Divide by 2 as we use 16-bit

	short *dataIn = reinterpret_cast<short*>(Buffer::Data(inputBuffer)); //Buffer for inputdata, as short array
	short *dataOut = new short[lengthOut]; //Buffer for outputdata, as short array
	float *dataOutFloat = new float[lengthOut]; //Buffer for outputdata, as float array
	float *dataInFloat = new float[lengthIn]; //Buffer for inputdata, as float array

	src_short_to_float_array(dataIn, dataInFloat, lengthIn); //Convert the input from short array to float array

	long outputFrames = ratio * inputFrames + 1;
	std::cout << "  Output Frames:" << outputFrames << std::endl;


	SRC_DATA data;
		data.data_in = dataInFloat;
		data.data_out = dataOutFloat;
		data.input_frames = inputFrames;
		data.output_frames = outputFrames;
		data.src_ratio = ratio;
	src_simple (&data, SRC_SINC_MEDIUM_QUALITY, channels);

	outputFrames = data.output_frames_gen; //Get actual values for frames
	inputFrames = data.input_frames_used;

	src_float_to_short_array(dataOutFloat, dataOut, lengthOut);  //Convert the output from float array to short array

	Local<Object> outputBuffer = NanNewBufferHandle(reinterpret_cast<char*>(dataOut), lengthOut*sizeof(short)); //Return the result
	NanReturnValue(outputBuffer);
}

static void InitSamplerate(Handle<Object> exports) {
	exports->Set(NanNew("resample"), NanNew<FunctionTemplate>(Resample)->GetFunction());
}

NODE_MODULE(node_samplerate, InitSamplerate);
