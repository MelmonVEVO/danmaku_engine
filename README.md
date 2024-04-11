![fumo :)](fumo.jpg)

# Danmaku Engine

Danmaku Engine is a plugin for Godot that allows you to create and manipulate performant bullets for your Touhou clone.
It also comes with an easy to use spawner node that allows you to create all sorts of fun bullet patterns.

<!-- TODO put gif of danmaku engine in action here. -->

## Setup

To get started, create a `BulletPool` node in your scene and set how many bullets you want the pool to... pool. Make sure you set correctly as the node will never activate more bullets than exists within the pool.

To spawn bullets, you can either do so by first creating a `BulletSettings` resource, then activating bullets manually as follows:
```gdscript
var bullet: Bullet2D pool.get_bullet()
bullet.start(relevant, parameters, go, here)
```

Or you can use the included `Emitter2D` node which handles everything for you!

Once a bullet is emitted, it will have the physics layer that you set it to. Add a hitbox to your enemies/player with the matching collision mask!

## Bugs
Probably infinite (although countably infinite). However, the distant screams of Godot running this thing is *not* a bug. It's a feature.
If your game crashes because of this, feel free to let me know, making sure you give me as much juicy detail as possible.

## Licence
Copyright (c) 2024-present MELMON PROJECT.

This program is released under the MIT Licence. In short, you may use, study and modify the source code in any way your heart desires.
If you use this program in your own project, credit is not required but highly appreciated!

THIS SOFTWARE IS PROVIDED "AS IS" WITH NO WARRANTY OR LIABILITY OF ANY KIND. FOR DETAILS, CHECK THE PROVIDED LICENSE FILE.
