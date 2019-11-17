# mDd client Proxymod:

This proxymod should help players to train their abilities for the Quake III Arena modification DeFRaG. It adds hud elements to the standard defrag hud.

## Installation
Quick and easy:
  * Copy the platform specific binary into the 'defrag' directory.
  * Put `seta vm_cgame 0` in your config file (e.g. autoexec.cfg).

You've correctly installed the proxymod if you load your favorite map and you see the following colored text in the console: `[mDd] cgame-proxy: x.x.x.x`

## Configuration
All the commands and cvars start with `mdd_`:

```
  mdd_hud
  mdd_version
  mdd_pps_offset

  mdd_ammo
  mdd_ammo_graph_xywh
  mdd_ammo_text_xh
  mdd_ammo_text_rgba

  mdd_gl_path_draw
  mdd_gl_path_rgba
  mdd_gl_path_preview_draw
  mdd_gl_path_preview_rgba

  mdd_jump
  mdd_jump_maxDelay
  mdd_jump_graph_xywh
  mdd_jump_graph_rgba
  mdd_jump_graph_rgbaOnGround;
  mdd_jump_graph_rgbaPreJump;
  mdd_jump_graph_rgbaPostJump;
  mdd_jump_graph_outline_w;
  mdd_jump_graph_outline_rgba;
  mdd_jump_text_xh
  mdd_jump_text_rgba

  mdd_rl_target_draw
  mdd_rl_target_shader
  mdd_rl_target_size
  mdd_rl_path_draw
  mdd_rl_path_rgba

  mdd_sound_local_only

  mdd_timer
  mdd_timer_xywh
  mdd_timer_item_w
  mdd_timer_item_rgba
  mdd_timer_gb_rgba
  mdd_timer_outline_w
  mdd_timer_outline_rgba

  mdd_trig
  mdd_trig_rgba
```
Default values can be shown by typing the cvar into the console (e.g. `mdd_ammo_graph_xywh`) followed by pressing enter. Note that some cvars end with `_w`, `_xh` or even `_xywh`. Here `w` stands for width, `h` for height and `x` and `y` for the coordinates. It goes without saying that multiple values are separated by spaces.

## Bitset
There are a few cvars have binary-literals as default values (e.g. `mdd_ammo`). These start with `0b` followed by a sequence of `1`'s and `0`'s.

```
mdd_ammo 0b X X X X
            | | | |
            | | | + - draw
            | | + - - no weapon -> no draw
            | + - - - gun
            + - - - - 3D
```
Note that it's not necessary to have the same number of `1`'s and `0`'s as there are *different options*, or even use the binary representation. You can still use the good old decimal equivalent (or the octal and hexadecimal representation to impress your friends).

## Examples

`mdd_ammo 0b1101` will:
  * draw the hud
  * draw the ammo/gun even if you don't have the weapon
  * draw the gun instead of the ammo
  * draw the 3D models instead of the 2D models

So if you want to have 2D models, simply use `mdd_ammo 0b0101`.
