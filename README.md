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
This project is published under the terms of version 3 of the GNU General Public License.
