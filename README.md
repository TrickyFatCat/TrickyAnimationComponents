# TrickyAnimationComponents

A small plugin with a collection of actor and scene components which can help with the animation of actors and their parts.

## Installation

The plugin can be used in both C++ and Blueprint projects.

### Blueprint projects

1. Download package file;
2. Unzip the package to the Plugins folder in engine folder, e.g. `C:\Program Files\Epic Games\UE_4.27\Engine\Plugins`;
3. Restart the project;

In this case the plugin can be used for any blueprint project.

### C++ projects

1. Create the Plugins folder in the project directory;
2. Create the TrickyAnimationComponents folder in the Plugins folder;
3. Download the plugin source code into that folder;
4. Rebuild the project;

## Components

The plugin contains:

1. RotationAnimationComponent;
2. FloatingAnimationComponent;
3. EaseAnimationComponent;
4. TimelineAnimationComponent;
5. SplineAnimationComponent;

### RotationAnimationComponent

A scene component which rotates along the chosen axis.

#### Parameters

1. `RotateX` - toggle rotation along the X axis;
2. `RotateY` - toggle rotation along the Y axis;
3. `RotateZ` - toggle rotation along the Z axis;
4. `RotationSpeed` - determines the rotation speed along each axis;

#### Functions

1. `SetIsRotating` - toggles rotation along XYZ axis;

### FloatingAnimationComponent

A scene component which creates a floating animation along the chosen axis.

#### Parameters

1. `FloatX` - toggle floating along X axis;
2. `FloatY` - toggle floating along Y axis;
3. `FloatY` - toggle floating along Z axis;
4. `Frequency` - determines the animation speed;
5. `Amplitude` - determines the position offset;

#### Functions

1. `SetIsFloating` - toggles floating animation along XYZ axis;

### EaseAnimationComponent

An actor component which moves the actor towards a target using interpolation functions.

#### Parameters

1. `IsEnabled` - toggles the easing animation;
2. `FollowActor` - switches between using location from a target actor or a specific world location.
3. `TargetActor` - an actor which world location will be used as a target location;
4. `SpecificLocation` - a world location which will be used as a target location;
5. `LocationOffset` - location offset relative to the target location;
6. `EasingFunction` - a type of the function which will be used for moving an owner;
7. `Alpha` - determines the speed of the movement;
8. `Exponent` - blend exponent, used only with EaseIn, EaseOut, EaseInOut easing functions. The higher the steeper the graph.
9. `SubSteps` - the number of substeps for the Step easing function;

### TimelineAnimationComponent

An actor component which animates transforms of the chosen scene components of an actor using a timeline.

#### Setup

1. Add the component to the chosen actor;
2. Fill the `AnimatedComponents` array using the `SetAnimatedComponents` function in the construction script;
   * Only for scene components;
   * Omits nullptr entries;
3. Fill the `TransformOffsets` array by hand;
   * The number of offsets must be equal to the number of animated components;
4. Create or use existing curve float for the `AnimationCurve` variable;

#### Parameters

1. `InitialState` - the initial state of the animation on begin play;
2. `AnimationTime` - the length of the animation;
3. `AnimationCurve` - a float curve object used by the timeline component for the animation. It's better to use a curve with length equal 1.f;
4. `TransformOffsets` - an array with transform offsets for each scene component in the AnimatedComponents array. The number of offsets must be equal to the number of animated components;

#### Functions

1. `Start` - starts the animation;
2. `Reverse` - reverse the current animation. Works only if current state is a transition state;
3. `Pause` - pauses the animation;
4. `Resume` - resumes the animation;
5. `SetAnimatedComponents` - fills the Animated components array with the chosen scene components. It'll omit nullptr entries;
6. `CanPlayAnimation` - returns if the animation can be played or not;

### SplineAnimationComponent

An actor component which moves an actor along a spline component using a timeline component.

#### Parameters

#### Functions