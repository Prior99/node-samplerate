#include <v8.h>
#include <nan.h>
#include <node_buffer.h>

#include "../deps/libsamplerate/src/samplerate.h"

using namespace node;
using namespace v8;

static int num = 0;

static long Callback(void *callbackData, float **data) {

	return 0;
}

static NAN_METHOD(Resample) {
	NanScope();
	//First, gather all attributes
	Local<Object> inputBuffer = Local<Object>::Cast(args[0]); // Buffer containing the input
	unsigned int fromRatio = (unsigned int) args[1]->NumberValue(); // Rate from which we convert (e.g. 22050 Hz)
	unsigned int toRatio = (unsigned int) args[2]->NumberValue(); // Rate to which we convert ()
	unsigned int channels = (unsigned int) args[3]->NumberValue(); // Amount of channels (1m = mono, 2 = stereo, 3 = ...)

	long inputFrames = (long) args[4]->NumberValue(); // Amount of frames to process

	unsigned int lengthIn = Buffer::Length(inputBuffer); //Length of the input data
	unsigned int lengthOut = lengthIn * ratio; //Length of the outputdata //TODO: How to calculate this value?

	short *dataIn = (short*) Buffer::Data(inputBuffer); //Buffer for inputdata, as short array
	short *dataOut = new short[lengthOut]; //Buffer for outputdata, as short array
	float *dataOutFloat = new float[lengthOut]; //Buffer for outputdata, as float array
	float *dataInFloat = new float[lengthOut]; //Buffer for inputdata, as float array

	double ratio = toRatio / (double) fromRatio; // Ratio calculated by dividing output-ratio by input-ratio

	src_short_to_float_array(dataIn, dataInFloat, lengthIn);
	outputFrames = ratio * inputFrames + 1;
	SRC_DATA data;
		data.data_in = dataInFloat;
		data.data_out = dataOutFloat;
		data.input_frames = inputFrames;
		data.output_frames = outputFrames;
		data.src_ratio = ratio;
	src_simple (&data, SRC_SINC_FASTEST, channels);
	long outputFrames = data.output_frames_gen;
	inputFrames = data.input_frames_used;
	src_float_to_short_array(dataOutFloat, dataOut, lengthOut);
	Local<Object> outputBuffer = NanNewBufferHandle(reinterpret_cast<char*>(dataOut), lengthOut);
	NanReturnValue(outputBuffer);
}

static void InitSamplerate(Handle<Object> exports) {
	exports->Set(NanNew("resample"), NanNew<FunctionTemplate>(Resample)->GetFunction());
}

NODE_MODULE(node_samplerate, InitSamplerate);
