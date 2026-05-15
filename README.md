# AudioFX
Description:
C++ implementation of a audio filters commonly used as guitar effects; includes distortion, overdrive, bitcrusher and tremolo filters. 

### Design choices: 
C++ is chosen as it's the industry standard in DSP applications. It's also used in VST plugins which I'd like to write so this was a stepping stone in that direction. 

C++ offers features such as inheritance and polymorphism which were utilized in this project. A general effect class was chosen as the base class for the project from which each effect can inherit. This allows different effect objects to respond the same to an generic `Effect` call.

Each effect was then thought of like a "digital" pedal. This means that when an effect is implemented, the user can input different pedal parameters like gain or bit depth, similar to setting the knob on a physical pedal.

This project contains  the following files:
- WavFile.h, WavFile.cpp: 
	- The header and implementation files for handling WAV file processing. For simplified signal processing algorithms, the program only works with MONO wav files. 
	- Any input wav file is sanitized with ffmpeg first using `ffmpeg -i input.wav -acodec pcm_s16le -ac 1 -ar 44100 -map_metadata -1 -fflags +bitexact input_sanitized.wav` to remove any meta data that makes the wav file have  anon standard 44 byte header. This also ensures the input is a 16-bit mono wav file.
	- This file also converts the audio data from `int` to `float` and stores it in a vector. This simplifies the algorithms for some effects as it doesn't allow overflow which prevents unwanted clipping and preserves precision during mathematical operations (like division) that would be lost with `int`. The choice for using vectors allows dynamic memory allocation and audio data to be indexed like an array without the data size being known at compile time.

- Effect.h, Effect.cpp: 
	- "Serves as the base class for all audio effects. This inheritance structure enables polymorphic behavior, allowing the pedalboard to process audio using a generic `Effect` pointer without needing to know the specific type of effect (e.g., Distortion or Echo) at compile time.

- Bitcrusher.h, Bitcrusher.cpp:  
	- Bitcrusher degrades a singal inboth time and amplitude domains. This implementation of a bitcrusher lowers the bit depth and sample rate producing a lo-fi retro sound. Bit depth reduction introduces quantization noise by snapping the floating point value of the audio data to the nearest "step".  The sample rate is lowered as the audio is sampled every `rate` time. This simulates a lower sampling frequency and introduces aliasing.
	
- Distortion.h, Distortion.cpp: 
	- Physical Audio Singnal Processing [Julias O Smith] introduces a normalized equation for hard clipping where the signal clips abruptly. This is modelled by the distortion.cpp code:

	```
	if (processed > 0.6) {
		processed = 0.6;
	} else if (processed < -0.6) {
	processed = -0.6;
	}
	```

- Overdrive.h, Overdrive.cpp: 
	- Digital Audio Effects (DAFx) by Udo Zolzer provides a piecewise function to model overdrive. When graphed in desmos, this is mathematically similar to a hyperbolic tangent function. Using the `tanh(audio[i] * drive)` allows the processed audio to mimic soft-clipping. Altering the overdrive by the use of a varying drive factor is similar to turning a knob on physical pedals. 
	- The `tanh` function is an odd function which only introduced odd-numbered harmonics. For tube distortion simulations, it's recommended to add even-numbered harmonics. This is done by introducing a different `drive_val` for negative input.
	
- Tremolo.h, Tremolo.cpp:
	- The algorithm used was found in  https://users.cs.cf.ac.uk/Dave.Marshall/CM0268/PDF/10_CM0268_Audio_FX.pdf. To prevent unwanted distortion if `trem > 1`, the `trem` term is normalized by ` trem = trem / (1 + depth_m)`.
	
- main.cpp:
	- Controls the program flow by calling other functions as well as aloowing the user to provide input for program execution.

### How to use this program?
1) download the repo
2) compile with `make`
3) run program using `./AudioFX input.wav output.wav`

Note: This program only works with **16-bit mono wav files.** Sanitizing with the above ffmpeg command is strongly recommened.
 
This pedal board includes bitcrusher, boost, distortion, overdrive and tremolo effects. The commands to implement each effect are shown below.

```
EFFECT         COMMAND                                   RANGE

Bitcrusher     bitcrusher <bit depth> <rate>             [1,16], [1,10]

Distortion     distortion <gain>                         [50,100]

Overdrive      overdrive <gain>                          [10,50]

Tremolo        tremolo <depth> <modulation frequency>    [0,1], [0.5,20]
```
This help menu can be triggered with `help`.

When using effects, each affect is recommended they're used with a specific range.

| effect      | parameter             | type  |  range   |
| :---------- | :-------------------- | :---- | :------: |
| bitcrusher  | bit depth             | int   |  [1,16]  |
|             | rate                  | int   |  [1,10]  |
| distortion  | gain                  | float | [50,100] |
| overdrive   | gain                  | float | [10,50]  |
| tremolo     | depth                 | float |  [0,1]   |
|             | modulation frequency  | float | [0.5,20] |

After applying effects, enter `save` to save the processed audio.