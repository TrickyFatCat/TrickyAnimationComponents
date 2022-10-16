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

#### Parameters

#### Functions

### SplineAnimationComponent

An actor component which moves an actor along a spline component using a timeline component.

#### Parameters

#### Functions