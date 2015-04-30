{
	"target_defaults" : {
		"default_configuration" : "Debug",
		"configuration" : {
			"Debug" : {
				"defines" : ["DEBUG", "_DEBUG"]
			},
			"Release" : {
				"defines" : ["NODEBUG"]
			}
		}
	},
	"targets" : [
		{
			"target_name" : "libsamplerate",
			"type" : "static_library",
			"cflags" : [
				"-Wall",
				"-Wno-unused-parameter",
				"-Wno-missing-field-initializers",
				"-Wextra"
			],
			"include_dirs": [
				"config/linux/"
			],
			"sources" : [
				"libsamplerate/src/src_linear.c",
				"libsamplerate/src/src_sinc.c",
				"libsamplerate/src/src_zoh.c",
				"libsamplerate/src/samplerate.c",
			]
		}
	]
}
