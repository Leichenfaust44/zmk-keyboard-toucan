# Toucan Keyboard — Gallium ZMK Config

Custom ZMK firmware for the [beekeeb Toucan Keyboard](https://beekeeb.com/toucan-keyboard/) using the **Gallium v2** Columnar Staggered layout, optimised for Swiss German (DE-CH) input.

This config uses the **5-col layout** (outer pinky columns unused), making key positions identical to the [Piantor Pro BT](https://github.com/Leichenfaust44/zmk-config) config for easy cross-board maintenance.

[![Keymap](https://github.com/Leichenfaust44/zmk-keyboard-toucan/raw/main/keymap-drawer/toucan.svg)](https://github.com/Leichenfaust44/zmk-keyboard-toucan/blob/main/keymap-drawer/toucan.svg)

\---

## Display

The left half features a **nice!view gem** display (Sharp Memory LCD). It shows the following widgets from top to bottom:

[![Keymap](https://github.com/Leichenfaust44/zmk-keyboard-toucan/raw/main/keymap-drawer/toucan_display.svg)](https://github.com/Leichenfaust44/zmk-keyboard-toucan/blob/main/keymap-drawer/toucan_display.svg)

|Widget|Description|
|-|-|
|**BLE / Layer**|Connection status (BLE/USB) and active layer name|
|**WPM chart**|Bar chart of last 10 WPM values, fixed range 0–100|
|**Batteries**|Charge bars for local (left) and peripheral (right) halves|
|**Gem animation**|Rotating pixel crystal — signature of the nice!view gem shield|
|**BT profile**|5 profile dots, active profile filled|
|**Output mode**|Active output highlighted (BLE or USB)|
|**Active layer**|Current layer name displayed large at the bottom|

Display configuration via [`nice_view_gem`](https://github.com/M165437/nice-view-gem). WPM fixed range and animation speed can be tuned in the shield conf.

\---

## Layout Overview

### Gallium (Default Layer)

[Gallium](https://github.com/GalileoBlues/Gallium) is an alternative layout designed to minimise same-finger bigrams and lateral stretches. This config uses the columnar-staggered version with X and Q swapped.

```
B  L  D  C  V  |  J  Y  O  U  ?/!
N  R  T  S  G  |  P  H  A  E  I
X  Q  M  W  Z  |  K  F  ,/; ./: -/_
```

**Hold-tap keys on the base layer:**

* `,` → `;`
* · `.` → `:`
* · `-` → `_`
* · `?` → `!`

**Home row mods** (cross-hand activation only, balanced flavor):

Two separate behaviors are used — Shift activates faster, Ctrl/Alt/Super require a deliberate hold.

* Left: `N`=Super(slow) · `R`=Alt(slow) · `T`=Ctrl(slow) · `S`=Shift(fast)
* Right: `H`=Shift(fast) · `A`=Ctrl(slow) · `E`=Alt(slow) · `I`=Super(slow)

|Behavior|Keys|`tapping-term-ms`|`require-prior-idle-ms`|
|-|-|-|-|
|`hml_shift` / `hmr_shift`|S, H|200 ms|120 ms|
|`hml_slow` / `hmr_slow`|N, R, T, A, E, I|400 ms|400 ms|

**Thumb cluster:**

```
ESC | Space (hold: Bridge) | SmartShift | MagicKey (hold: Helm) | Backspace/Del | Glyph
```

\---

## Thumb Key Behaviours

|Key|Tap|Hold|
|-|-|-|
|**Space**|Plain space|Bridge layer|
|**SmartShift**|Sticky Shift (capitalises next key only)|Regular Shift|
|**SmartShift** (double-tap)|Caps Word (capitalises until word boundary)|—|
|**MagicKey**|Adaptive key (see below)|Helm layer|
|**Backspace**|Backspace|—|
|**Backspace** (with Shift)|Delete|—|
|**Glyph**|`num_word` (auto-exit number layer)|Momentary Glyph layer|

### Magic Key — Adaptive Substitutions

The Magic Key repeats the last key by default, but applies smart substitutions for common bigrams optimised for German and English on the Gallium layout:

|After typing|Magic Key outputs|Rationale|
|-|-|-|
|`E`|`U`|«eu» SFB Ringfinger rechts — heute/neu/Euro|
|`I`|`E`|«ie» rückwärts Roll — die/wie/nie/viel|
|`L`|`D`|«ld» rückwärts Roll — Wald/Geld/wild|
|`N`|`D`|«nd» rückwärts home→top — und/Kind/Hand|
|`P`|`F`|«pf» SFB Zeigefinger rechts — Pferd/Kopf|
|`Q`|`U`|«qu» Q kommt praktisch nie ohne U vor|
|`-`|`>`|Produces `->`|
|`a` / `A`|`ä` / `Ä`|Umlaut substitution (1 s window)|
|`o` / `O`|`ö` / `Ö`|Umlaut substitution (1 s window)|
|`u` / `U`|`ü` / `Ü`|Umlaut substitution (1 s window)|
|anything else|key repeat|—|

Umlaut substitutions have a 1-second timeout window; all others have a 5-second window.

\---

## Glyph (Layer 1) — Numbers and Symbols

Numbers on the left, symbols on the right. Home row mods mirror the base layer split (Shift fast, Ctrl/Alt/Super slow). Activated by the Glyph thumb (momentary hold) or `num_word` (tap — auto-exits when a non-number/symbol key is pressed).

```
 —   7   8   9   —  |  [   ]   <   >   |
 0   4   5   6   —  |  {   }   ^   `   ~
 .   1   2   3   —  |  `   ´   §   °   —
```

**Thumb cluster:** `to(0) | Space | — | to(0) | Backspace | num_word`

## Helm (Layer 2) — Function Keys and Mouse

Function keys on the left (F1–F12 arranged like a numpad), raw modifier keys on the right home row for `Shift/Ctrl/Alt/Super + Fx` combinations. Activated by holding MagicKey **or by touching the trackpad** (touch processor fires `mo 2`).

```
F10  F7  F8  F9  —  |   —   —    —    —    —
F11  F4  F5  F6  —  |   —  RSft RCtl RAlt RGui
F12  F1  F2  F3  —  |   —   —    —    —    —
```

**Thumb cluster:** `— | — | MClick | — | RClick | MClick`

Mouse clicks are on the thumb cluster — reachable while the trackpad hand moves the cursor.

\---

## Bridge (Layer 3) — Navigation and System Controls

Navigation on the right, system/media controls on the left. Activated by holding Space. **Trackpad acts as scroll wheel on this layer.**

```
BtClrAll  Next  VolUp  RGB_OFF  StudioUnlk | PgUp  Home  Up    End    BtClr 
—          Prev  VolDn  —        —          | PgDn  Left  Down  Right  Reset 
Boot      Play  Mute   MicMute  —          | CapsL  —   PrtSc   —    Boot 
```

**Thumb cluster:** `BT_PRV | — | BT_NXT | — | — | to(Base)`

`\\\*\\\*` = tap-dance safety: single tap does nothing, double-tap triggers the action. (BtClr, BtClrAll, Boot)
`MicMute` = `LGui+RAlt+K` shortcut.  
`CapsL` = Caps Lock (manual toggle).

\---

## Trackpad Behaviour

The Toucan's Cirque Pinnacle trackpad (right half) behaves differently depending on the active layer:

|Layer|Trackpad behaviour|
|-|-|
|**Gallium (0)**|Cursor movement + touch activates Helm (`mo 2`)|
|**Glyph (1)**|Cursor movement only|
|**Helm (2)**|Cursor movement + thumb cluster provides mouse clicks|
|**Bridge (3)**|Scroll wheel (horizontal scroll inverted)|

Pointer speed: 2.5× (`zip_xy_scaler 250 100`). Scroll speed: 1/5× (`zip_scroll_scaler 1 5`).

Power management: trackpad enters idle after 30 seconds of no keypresses, waking in \~300ms on touch. Deep sleep after 60 minutes.

\---

## Combos

All combos are active on Gallium and Glyph layers (Tab and Return also work on Helm).  
All combos use `timeout-ms = 50ms` and `require-prior-idle-ms = 400ms` (300ms for Tab/Return).

**Whitespace (horizontal home row):**

* `R+T` → Tab
* `T+S` → Return

**Symbols — left hand vertical (top+home / home+bottom):**

```
B+N → "    L+R → @    D+T → #    C+S → $
N+X → '    R+Q → %    T+M → \    S+W → =
```

**Symbols — right hand vertical (top+home / home+bottom):**

```
Y+H → +    O+A → *    U+E → €    ?+I → Copy
H+F → -    A+, → /    E+. → &    I+- → Paste
?+- → Cut  (top+bottom pinky stretch)
```

**Brackets — right hand horizontal (bottom row):**

* `F+,` → `(`
* `,+.` → `)`

\---

## Flashing Firmware

### Download

1. Go to the **Actions** tab → latest successful build
2. Download the `firmware` artifact and extract the `.zip`:

   * `seeeduino_xiao_ble_toucan_left-zmk.uf2`
   * `seeeduino_xiao_ble_toucan_right-zmk.uf2`

The keyboard reboots automatically after copying.

\---

## Bluetooth

### Pairing

Turn on both halves and search for "Toucan" on your device. The keyboard is in pairing mode automatically.

### Switching / Managing Profiles

Access the Bridge layer (hold Space) and use the thumb cluster:

* `BT_PRV` / `BT_NXT` — cycle profiles

Destructive BT operations (BT\_CLR, BT\_CLR\_ALL) require a double-tap on Bridge.

\---

## Battery \& Power

* Each half has an ON/OFF switch (OFF = fully disconnected, ON = sleep when idle)
* Deep sleep after 60 minutes of inactivity
* Trackpad enters idle after 30 seconds of no keypresses to save power (\~1.7 mA idle vs 2.9 mA active)

\---

## Modifying the Config

1. Edit `config/toucan.keymap`, `config/toucan_behaviors.dtsi`, or `config/toucan_combos.dtsi`
2. Push → GitHub Actions builds automatically
3. Download the firmware artifact from the Actions tab

The keymap, behaviors, and combos use **identical key positions and logic** to the [Piantor Pro BT config](https://github.com/Leichenfaust44/zmk-config) — changes can be ported between boards with minimal adaptation.

**Tools:**

* [ZMK Studio](https://zmk.studio/download) — GUI editor (use Studio Unlock on Bridge layer)
* [keymap-editor](https://nickcoutsos.github.io/keymap-editor) — browser-based editor

\---

## License

Based on [ZMK Firmware](https://zmk.dev), MIT License.

The included shield `nice_view_gem` is modified from [M165437/nice-view-gem](https://github.com/M165437/nice-view-gem), MIT License.

The embedded font QuinqueFive is designed by GGBotNet, licensed under the SIL Open Font License, Version 1.1.

