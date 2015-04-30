{
	"targets" : [
		{
			"target_name" : "node-samplerate",
			"dependencies" : [
				"deps/binding.gyp:libsamplerate"
			],
			"cflags" : [
				"-Wall",
				"-Wno-unused-parameter",
				"-Wno-missing-field-initializers",
				"-Wextra"
			],
			"include_dirs": [
				"<!(node -e \"require('nan')\")"
			],
			"sources" : [
				"src/node-samplerate.cc"
			]
		}
	]
}
