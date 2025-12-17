# AudioFX

C++ implementation of a guitar pedalboard

### How to use this program?

1) download the repo
2) compile with `make`
3) run program using `./AudioFX input.wav output.wav`

Note: This program only works with **mono** .wav files


This pedal board inlcues bitcrusher, boost, distortion, overdrive and tremolo effects. The commands to implement each effect are shown below.

```
EFFECT         COMMAND
Bitcrusher     bitcrusher <bit depth> <rate>
Distortion     distortion <gain>
Overdrive      overdrive <gain>
Tremolo        tremolo <depth> <modulation frequency>
```

The help menu can be triggered with `help`.

When using effects, each affect is recommened they're used with a specific range.


| effect     | parameter            |type| range| 
|:----------|:----------------------|:----|:---:|
| bitcrusher | bit depth            |int  | [1,1] |
|            | rate                 |int  | [1,1] |
| distortion | gain                 |float| [50,100]|
|overdrive   | gain                 |float| [10,50]|
| tremolo    | depth                |float| [0,1]|
|            | modulation frequency |float| [0.5,20]|

After applying effects, enter `save` to save the processed audio.
