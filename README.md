Samplerate
==========

This packages provides a method to convert the samplerate of raw audio to a different samplerate.

It is based on the library ```libsamplerate```.

Usage
-----

First, install the package using npm:

	npm install samplerate --save

Then use the package as follows:

```javascript
var Samplerate = require("samplerate");

var originalSamplerate = 22050;
var channels = 1;
var targetSamplerate = 48000;

var data = [...]

var resampledData = Samplerate.resample(data, originalSamplerate, targetSamplerate, channels);

```

License
-------
Copyright 2015 Frederick Gnodtke 
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
