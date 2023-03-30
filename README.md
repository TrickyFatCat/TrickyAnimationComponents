# TrickyAnimationComponents

A small plugin with a collection of actor and scene components which can help with the animation of actors and their parts.

## Installation

The plugin can be used in both C++ and Blueprint projects.

### Blueprint projects

1. Download [**package file**](https://github.com/TrickyFatCat/TrickyAnimationComponents/releases/);
2. Install the plugin either in your project or for all projects in engine:
   * Unzip the package into Plugins folder of your project, e.g. `D:\UnrealProjects\MyProject\Plugins`;
   * Unzip the package to the Plugins folder in engine folder, e.g. `C:\Program Files\Epic Games\UE_5.0\Engine\Plugins`;
3. Restart the project;

In this case the plugin can be used for any blueprint project.

### C++ projects

1. Create the Plugins folder in the project directory;
2. Create the TrickyAnimationComponents folder in the Plugins folder;
3. Download the plugin source code into that folder;
4. Rebuild the project;

## Components

The plugin contains:

1. EaseAnimationComponent;
2. EasingAnimationSceneComponent;
3. FollowAnimationComponent;
4. OscillationAnimationComponent;
5. RotationAnimationComponent;
6. SplineAnimationComponent;
7. TimelineAnimationComponent;

### EaseAnimationComponent

An actor component which can animate owners location, rotation and scale using easing functions.

#### Variables

1. `AutoPlay` - toggles if the animation will start on begin play or not;
2. `bPlayFromEnd` - if true, PlayFromEnd function will be called on begin play, else PlayFromStart;
3. `AnimationBehavior` - Determines behavior of the animation:
   - `Normal` plays once;
   - `Loop` loops normal behavior;
   - `AdditiveLoop` increment target values by their initial value each cycle;
   - `PingPong` animates from initial values to target and back;
4. `EaseFunction` - ease function which will be used for the animation;
5. `TargetLocation` - target world location of the animation;
6. `TargetRotation` - target world rotation of the animation;
7. `TargetScale` - target world scale of the animation;
8. `Duration` - animation duration;
9. `IsPlaying` - shows if the animation is playing;

#### Functions

1. `PlayFromStart` - starts the animation from initial location/rotation/scale;
2. `PlayFromEnd` - start the animation from target location/rotation/scale;
3. `Stop` - stops the animation;

#### Delegates

1. `OnAnimationFinished` - called when the animation cycle finished;
 
### EasingAnimationComponent

A scene component which can animate its location, rotation and scale using easing functions.

#### Variables

1. `AutoPlay` - toggles if the animation will start on begin play or not;
2. `bPlayFromEnd` - if true, PlayFromEnd function will be called on begin play, else PlayFromStart;
3. `AnimationBehavior` - Determines behavior of the animation:
   - `Normal` plays once;
   - `Loop` loops normal behavior;
   - `AdditiveLoop` increment target values by their initial value each cycle;
   - `PingPong` animates from initial values to target and back;
4. `EaseFunction` - ease function which will be used for the animation;
5. `TargetLocation` - target relative location of the animation;
6. `TargetRotation` - target relative rotation of the animation;
7. `TargetScale` - target relative scale of the animation;
8. `Duration` - animation duration;
9. `IsPlaying` - shows if the animation is playing;

#### Functions

1. `PlayFromStart` - starts the animation from initial location/rotation/scale;
2. `PlayFromEnd` - start the animation from target location/rotation/scale;
3. `Stop` - stops the animation;

#### Delegates

1. `OnAnimationFinished` - called when the animation cycle finished;

### FollowAnimationComponent

A component which interpolates an owning actor location towards a target location/actor.

#### Variables

1. `FollowActor` - toggles if the component will interpolate position towards a target actor or a specific location;
2. `TargetActor` - an actor which world location will be used as a target location;
3. `Location` - the world location which will be used as a target location;
4. `TargetLocationOffsetz` - location offset relative to the target location;
5. `Speed` - determines the speed of interpolation;
6. `IsFollowing` - shows if the component follows the target location;

#### Functions

1. `StartFollowing` - start interpolation;
2. `StopFollowing` - stops interpolation;

### OscillationAnimationComponent

A scene component which create oscillation animation for location, rotation and scale.

#### Variables

1. `IsEnabled` - toggles all the animations;
2. For location, rotation, scale:
   1. `AnimateX` - toggle animation along X axis;
   2. `AnimateY` - toggle animation along Y axis;
   3. `AnimateZ` - toggle animation along Z axis;
   4. `Amplitude` - determines the animation amplitude for each axis;
   5. `Frequency` - determines the animation frequency for each axis;

#### Functions

1. `SetIsEnabled` - toggles oscillation animation;

### RotationAnimationComponent

A scene component which rotates along the chosen axis.

#### Variables

1. `RotateX` - toggle rotation along the X axis;
2. `RotateY` - toggle rotation along the Y axis;
3. `RotateZ` - toggle rotation along the Z axis;
4. `RotationSpeed` - determines the rotation speed along each axis;

#### Functions

1. `SetIsRotating` - toggles rotation along XYZ axis;

### SplineAnimationComponent

An actor component which moves an actor along a spline component using a timeline component.

#### Setup

1. Add component to an actor;
2. Create or use the existing curve float object for the `AnimationCurve` variable;
3. Place the actor in the world;
4. Choose an actor with a spline component as `TargetActor`;
5. Setup animation behavior in blueprints if needed;

#### Variables

1. `AnimationMode` - a mode which determines how the animation will work;
2. `SplineActor` - an actor which contains a spline component;
3. `AnimationCurve` - a float curve object used by the timeline component for the animation;
   * It's better to use a curve with length equal 1.f;
4. `AnimationTime` - length of the animation;
5. `AnimationSpeed` - used for calculation of the animation time;
   * Great for splines with many points and when the animation time between them must be constant;
6. `StartPointIndex` - the point index from which the animation will be started;
7. `IsReversed` - determines if the order of points will be reversed or not;
8. `StopMode` - determines the rules how the owner should stop at the points;
9. `WaitAtAnimationStart` - toggles if the owner will "stop" at the start point;
10. `UseCustomStops` - enables custom stops adjustments;
11. `WaitTimer` - how long the owner will wait at the point;
12. `SplineOffset` - the offset along the spline;
13. `LocationOffset` - location offset relative to the current location along the spline;
14. `InheritRotation` - determines if the rotation along spline must be applied to the owner;
15. `InheritScale` - determines if the scale along spline must be applied to the owner;

### Functions

1. `Start` - starts the animation;
2. `Stop` - stops the animation at the next spline point;
3. `AnimateTo` - animates to the chosen point. Works only in the manual mode;
4. `Pause` - pauses the animation;
5. `Resume` - resumes the animation;
6. `IsPlaying` - returns true if the animation is playing;

### TimelineAnimationComponent

An actor component which animates transforms of the chosen scene components of an actor using a timeline.

#### Setup

1. Add the component to the chosen actor;
2. Fill the `AnimatedComponents` array using the `SetAnimatedComponents` function in the construction script;
   * Only for scene components;
   * Omits nullptr entries;
3. Fill the `TransformOffsets` array by hand;
   * The number of offsets must be equal to the number of animated components;
4. Create or use the existing curve float object for the `AnimationCurve` variable;
5. Setup animation behavior in blueprints;

#### Variables

1. `InitialState` - the initial state of the animation on begin play;
2. `AnimationTime` - the length of the animation;
3. `AnimationCurve` - a float curve object used by the timeline component for the animation. It's better to use a curve with length equal 1.f;
4. `AnimateWholeActor` - if true, the whole actor will be animated. Doesn't require call of `SetAnimatedComponents`;
5. `TransformOffsets` - an array with transform offsets for each scene component in the AnimatedComponents array. The number of offsets must be equal to the number of animated components;

#### Functions

1. `Start` - starts the animation;
2. `Reverse` - reverse the current animation. Works only if current state is a transition state;
3. `Pause` - pauses the animation;
4. `Resume` - resumes the animation;
5. `SetAnimatedComponents` - fills the Animated components array with the chosen scene components. It'll omit nullptr entries;
6. `CanPlayAnimation` - returns if the animation can be played or not;
7. `GetAnimationProgress` - returns progress of the animation;


