# GZE (GangZone Empty)

[![Fanorisky](https://img.shields.io/badge/Fanorisky-GZE-2f2f2f.svg?style=for-the-badge)](https://github.com/Fanorisky/GZ_Empty)

This include create iner empty gangzone. This will be useful to create boundaries on server (Example: for event)

## Installation

Simply install to your project:

```bash
sampctl package install Fanorisky/GZ_Empty
```

Include in your code and begin using the library:

```c
#include <GZ_Empty>
```

## Usage

### Function

These are the function you can use:<br />

```c
// Main Function //
• GZE_CreateRadius(Float:x, Float:y, Float:radius) // This function create simple Rectangle zone with radius.
• GZE_Create(Float:minx, Float:miny, Float:maxx, Float:maxy) // This function create Zone with custom cord same as GangZoneCreate.

// Extra Function //
• GZE_Destroy(id)
• GZE_ShowForPlayer(playerid, id, color)
• GZE_ShowForAll(id, color)
• GZE_HideForPlayer(playerid, id)
• GZE_HideForAll(id)
• GZE_FlashForPlayer(playerid, id, flashcolor)
• GZE_FlashForAll(id, flashcolor)
• GZE_StopFlashForPlayer(playerid, id)
• GZE_StopFlashForAll(id)
• GZE_DestroyAll()
```
