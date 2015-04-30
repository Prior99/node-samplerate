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

	Local<Object> inputBuffer = Local<Object>::Cast(args[0]);

	unsigned int fromRatio = (unsigned int) args[1]->NumberValue();
	unsigned int toRatio = (unsigned int) args[2]->NumberValue();
	unsigned int lengthIn, lengthOut;
	short *dataIn, *dataOut;
	float *dataInFloat, *dataOutFloat;
	long inputFrames, outputFrames;
	double ratio = toRatio / (double) fromRatio;
	inputFrames = (long) args[4]->NumberValue();
	unsigned int channels = (unsigned int) args[3]->NumberValue();
	dataIn = (short*) Buffer::Data(inputBuffer);
	lengthIn = Buffer::Length(inputBuffer);
	lengthOut = lengthIn * ratio;
	dataOutFloat = new float[lengthOut];
	dataInFloat = new float[lengthOut];
	dataOut = new short[lengthOut];
	src_short_to_float_array(dataIn, dataInFloat, lengthIn);
	outputFrames = ratio * inputFrames + 1;
	SRC_DATA data;
		data.data_in = dataInFloat;
		data.data_out = dataOutFloat;
		data.input_frames = inputFrames;
		data.output_frames = outputFrames;
		data.src_ratio = ratio;
	src_simple (&data, SRC_SINC_FASTEST, channels);
	outputFrames = data.output_frames_gen;
	inputFrames = data.input_frames_used;
	src_float_to_short_array(dataOutFloat, dataOut, lengthOut);
	Local<Object> outputBuffer = NanNewBufferHandle(reinterpret_cast<char*>(dataOut), lengthOut);
	NanReturnValue(outputBuffer);
}

static void InitSamplerate(Handle<Object> exports) {
	exports->Set(NanNew("resample"), NanNew<FunctionTemplate>(Resample)->GetFunction());
}

NODE_MODULE(node_samplerate, InitSamplerate);
