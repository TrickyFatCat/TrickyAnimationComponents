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

#### Functions

### FloatingAnimationComponent

A scene component which creates a floating animation along the chosen axis.

#### Parameters

#### Functions

### EaseAnimationComponent

An actor component which moves the actor towards a target using interpolation functions.

#### Parameters

#### Functions

### TimelineAnimationComponent

An actor component which animates transforms of the chosen scene components of an actor using a timeline.

#### Parameters

#### Functions

### SplineAnimationComponent

An actor component which moves an actor along a spline component using a timeline component.

#### Parameters

#### Functions