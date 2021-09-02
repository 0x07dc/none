# None Audio Application Framework
## About
To provide a framework that provides a simple drop-in component system
and handles any non-creative work consistently.

This framework is built on the JUCE audio plugin framework, which provides
all of the tools for making the actual audio plugin.

While JUCE is a great framework, I found that there are some tasks 
which are repetitive (such as state maintenance), and plenty things that could
go wrong in making a JUCE application. This framework is a solution
to a decoupled, organized, and uniform framework that will allow 
even giant apps to be built, while maintaining maintainability and simplicity.

## Current version - 0.0.0
This is super alpha and definitely not considered production yet, although it is already useful.

## Documentation
The framework contains 4 main types of entities.

- GUI Components
- Midi/Audio Processors
- States
- State Modifiers

With these four entities, any app should be constructable. The framework aims to 
handle everything that is not specifically creating a GUI, running audio processes, 
referring to states, and modifying states.

The NoneApp folder contains a JUCE project that is built using this framework. It
is a simple FM modulator, and uses every component of the framework. It generates
a sine using a state that contains the frequency information. A state modifier
modulates the generator's state, by way of a GUI rotary slider component. This
results in a synthesizer with a controllable frequency modulator.

The `juce_modules` folder contains the modules that this framework used in development.

### Step by step
1) To create a new app, just copy and rename the NoneApp. You'll need Projucer from JUCE to 
open the project file.
2) You'll need to copy the folder `modules/none_app`. That's the starting project. You
will edit this module to configure the app. Consider renaming the namespace to your desire.
3) Include your module in the JUCE project, by adding a module in Projucer.
4) If you renamed your namespace, you'll need to change the app's variable 
declaration in `PluginProcessor.h`.

## Known bugs
- Automation is non-functional in Fl Studio. The parameter only updates on play.

## License
This framework contains two different licenses. This repository contains JUCE module code 
for convenience. A licence document is included in the `juce_modules` folder which details the JUCE license.

Aside from JUCE, this library is licensed with the MIT license, making it very free.