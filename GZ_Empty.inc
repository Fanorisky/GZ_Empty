/** ========================================================================

| Version:
1.0.1

| License:
Copyright (c) 2023 Fanorisky

#Changelog
- Add 2 types of radius zone

// Main Function //
native GZE_CreateRadius(Type, Float:x, Float:y, Float:radius) // This function create simple empty zone with radius. (Type: CIRCLE, SQUARE)
native GZE_Create(Float:minx, Float:miny, Float:maxx, Float:maxy) // This function create Zone with custom cord same as GangZoneCreate.

// Extra Function //
native GZE_Destroy(id)
native GZE_ShowForPlayer(playerid, id, color)
native GZE_ShowForAll(id, color)
native GZE_HideForPlayer(playerid, id)
native GZE_HideForAll(id)
native GZE_FlashForPlayer(playerid, id, flashcolor)
native GZE_FlashForAll(id, flashcolor)
native GZE_StopFlashForPlayer(playerid, id)
native GZE_StopFlashForAll(id)
native GZE_DestroyAll()
======================================================================== **/


#if defined _gze_included
	#endinput
#endif
#define _gze_included


// ==================================] Define [================================== //
#if !defined MAX_GZE
	#define MAX_GZE				25
#endif

// ==================================] Variable [================================== //
static bool:gze_Init;
static bool:gze_Exit;

enum GZ_TYPE
{
	CIRCLE,
	SQUARE
}

enum gze_data
{
	Float:gze_x,
	Float:gze_y,
	gze_Border[MAX_GANG_ZONES],
	bool:gze_Exists
}
static gze_Info[MAX_GZE][gze_data];

static gze_ZoneUsed;


// ==================================] Callbacks [================================== //
public OnFilterScriptInit()
{
    if(!gze_Init)
    {
    	gze_Init = true;
    	gze_ZoneUsed = 0;

      	for(new x = 0; x < MAX_GZE; x++)
      	{
      		for(new y = 0; y < MAX_GANG_ZONES; y++)
      		{
      			gze_Info[x][gze_Border][y] = INVALID_GANG_ZONE;
      		}
      	}
    }

    #if defined gze_OnFilterScriptInit
         return gze_OnFilterScriptInit();
    #else
   	 	return 1;
	#endif
}
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit gze_OnFilterScriptInit
#if defined gze_OnFilterScriptInit
	forward gze_OnFilterScriptInit();
#endif

public OnFilterScriptExit()
{
    if(!gze_Exit)
    {
    	gze_Exit = true;
    	GZE_DestroyAll();
    }

    #if defined gze_OnFilterScriptExit
         return gze_OnFilterScriptExit();
    #else
   	 	return 1;
	#endif
}
#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit gze_OnFilterScriptExit
#if defined gze_OnFilterScriptExit
	forward gze_OnFilterScriptExit();
#endif

public OnGameModeInit()
{
 	if(!gze_Init)
    {
    	gze_Init = true;
    	gze_ZoneUsed = 0;

      	for(new x = 0; x < MAX_GZE; x++)
      	{
      		for(new y = 0; y < MAX_GANG_ZONES; y++)
      		{
      			gze_Info[x][gze_Border][y] = INVALID_GANG_ZONE;
      		}
      	}
    }
    #if defined gze_OnGameModeInit
         return gze_OnGameModeInit();
    #else
   	 	return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit gze_OnGameModeInit
#if defined gze_OnGameModeInit
	forward gze_OnGameModeInit();
#endif

public OnGameModeExit()
{
 	if(!gze_Exit)
    {
    	gze_Exit = true;
    	GZE_DestroyAll();
    }

    #if defined gze_OnGameModeExit
         return gze_OnGameModeExit();
    #else
   	 	return 1;
	#endif
}
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit gze_OnGameModeExit
#if defined gze_OnGameModeExit
	forward gze_OnGameModeExit();
#endif


// ==================================] Basic Function [================================== //

stock FixGZE_Create(Float:minx, Float:miny, Float:maxx, Float:maxy) // This function is the most important
{
	if(minx > maxx)
	{
		new Float:StoreMinValue = minx;
		minx = maxx;
		maxx = StoreMinValue;
	}
	if(miny > maxy)
	{
		new Float:StoreMinValue = miny;
		miny = maxy;
		maxy = StoreMinValue;
	}
	return GangZoneCreate(minx, miny, maxx, maxy);
}

// ==================================] New Function [================================== //

stock GZE_CreateRadius(GZ_TYPE:type, Float:x, Float:y, Float:radius) // This function create simple empty zone with radius. (CIRCLE, SQUARE)
{
	for(new i = 0; i < MAX_GZE; i++)
	{
		new auto_squares = floatround((radius * 512.0)/750.0);
		new free_squares = MAX_GANG_ZONES - gze_ZoneUsed;

		if(auto_squares <= free_squares)
		{
			squares = auto_squares;
		}
		else
		{
			squares = free_squares;
		}

		new free_zone = MAX_GANG_ZONES - gze_ZoneUsed;
		new Float:maplimit = 3000.0; // Don't change this value

        if(free_zone <= 1 || squares <= 1)
        {
            printf("** [GZE] The gangzones couldn't be created, there aren't enough free server gangzones.");
            break;
        }
        
        switch(type)
		{
			case CIRCLE:
			{
				new Float:temp_x;
		        new Float:next_x;
		        new Float:temp_y;
		        new Float:temp_diff;
		        new Float:next_diff;
		        new Float:diff = (max_ang - min_ang) / float(squares);
				new bool:second_quadrant = false;

				for(new j = 0; j < squares; j++)
				{
					temp_diff = diff * float(j);
					next_diff = diff * float(j + 1);

					temp_x = radius * floatcos(temp_diff, degrees);
					temp_y = radius * floatsin(temp_diff, degrees);

					next_x = radius * floatcos(diff * float(j + 1), degrees);

					if(0.0 <= temp_diff <= 90.0)
					{
						if(j == 0)
						{
							temp_y = 0.0;
							temp_x = (3000.0 - x);
						}

						gze_Info[i][gze_Border][j] =  GangZoneCreate((x + next_x), (y + temp_y), (x + temp_x), 3000.0);
					}
					else if(90.0 < temp_diff < 180.0)
					{
						if(next_diff >= 180.0)
						{
							next_x = - (3000.0 + x);
							temp_y = 0.0;

							second_quadrant = true;
						}

						gze_Info[i][gze_Border][j] =  GangZoneCreate((x + next_x), (y + temp_y), (x + temp_x), 3000.0);
					}
					else if(180.0 <= temp_diff <= 270.0)
					{
						if(second_quadrant)
						{
							second_quadrant = false;

							temp_x = - (3000.0 + x);
							temp_y = 0.0;

						}

						gze_Info[i][gze_Border][j] =  GangZoneCreate((x + temp_x), -3000.0, (x + next_x), (y + temp_y));
					}
					else if(270 < temp_diff <= 360.0)
					{
						if((squares - j) <= 1)
						{
							next_x = (3000.0 - x);
							temp_y = 0.0;
						}

						gze_Info[i][gze_Border][j] =  GangZoneCreate((x + temp_x), -3000.0, (x + next_x), (y + temp_y));
					}
				}

				gze_ZoneUsed += squares;
			}
			case SQUARE:
			{
                gze_Info[i][gze_Border][0] = FixGZE_Create((x - radius), maplimit, maplimit, (y + radius)); // Bagian atas ke kanan (top to right).
                gze_Info[i][gze_Border][1] = FixGZE_Create((x + radius), (y + radius), maplimit, -maplimit); // Bagian kanan ke bawah (right to bottom).
                gze_Info[i][gze_Border][2] = FixGZE_Create(-maplimit, (y - radius), (x + radius), -maplimit); // Bagian bawah ke kiri (bottom to left).
                gze_Info[i][gze_Border][3] = FixGZE_Create(-maplimit, maplimit, (x - radius), (y - radius)); // Bagian kiri ke atas (left to top).
        
                gze_ZoneUsed += 4;
            }
        }
        gze_Info[i][gzs_Exists] = true;
		return i;
	}
	return -1;
}

stock GZE_Create(Float:minx, Float:miny, Float:maxx, Float:maxy) // This function create Zone with custom cord same as GangZoneCreate. (SQUARE)
{
	for(new i = 0; i < MAX_GZE; i++)
	{
		new free_zone = MAX_GANG_ZONES - gze_ZoneUsed;
		new Float:maplimit = 3000.0; // Don't change this value

        if(free_zone <= 1)
        {
            printf("** [GZE] The gangzones couldn't be created, there aren't enough free server gangzones.");
            break;
        }
        
        gze_Info[i][gze_Border][0] = FixGZE_Create(minx, maplimit, maplimit, miny); // Bagian atas ke kanan (top to right).
        gze_Info[i][gze_Border][1] = FixGZE_Create(maxx, miny, maplimit, -maplimit); // Bagian kanan ke bawah (right to bottom).
        gze_Info[i][gze_Border][2] = FixGZE_Create(-maplimit, maxy, maxx, -maplimit); // Bagian bawah ke kiri (bottom to left).
        gze_Info[i][gze_Border][3] = FixGZE_Create(-maplimit, maplimit, minx, maxy); // Bagian kiri ke atas (left to top).

        gze_ZoneUsed += 4;
        gze_Info[i][gze_Exists] = true;

		return i;
	}
	return -1;
}

stock GZE_Destroy(id)
{
	if(0 <= id < MAX_GZE)
	{
		if(gze_Info[id][gze_Exists])
		{
			for(new y = 0; y < MAX_GANG_ZONES; y++)
			{
				if(gze_Info[id][gze_Border][y] == INVALID_GANG_ZONE)
				{
					continue;
				}

				gze_ZoneUsed--;

				GangZoneDestroy(gze_Info[id][gze_Border][y]);
				gze_Info[id][gze_Border][y] = INVALID_GANG_ZONE;
			}

			gze_Info[id][gze_Exists] = false;

			return 1;
		}
	}
	return 0;
}

stock GZE_ShowForPlayer(playerid, id, color)
{
	if(0 <= id < MAX_GZE)
	{
		if(gze_Info[id][gze_Exists])
		{
			for(new y = 0; y < MAX_GANG_ZONES; y++)
			{
				if(gze_Info[id][gze_Border][y] == INVALID_GANG_ZONE)
				{
					continue;
				}

				GangZoneShowForPlayer(playerid, gze_Info[id][gze_Border][y], color);
			}

			return 1;
		}
	}
	return 0;
}

stock GZE_ShowForAll(id, color)
{
	if(0 <= id < MAX_GZE)
	{
		if(gze_Info[id][gze_Exists])
		{
			for(new y = 0; y < MAX_GANG_ZONES; y++)
			{
				if(gze_Info[id][gze_Border][y] == INVALID_GANG_ZONE)
				{
					continue;
				}

				GangZoneShowForAll(gze_Info[id][gze_Border][y], color);
			}

			return 1;
		}
	}
	return 0;
}

stock GZE_HideForPlayer(playerid, id)
{
	if(0 <= id < MAX_GZE)
	{
		if(gze_Info[id][gze_Exists])
		{
			for(new y = 0; y < MAX_GANG_ZONES; y++)
			{
				if(gze_Info[id][gze_Border][y] == INVALID_GANG_ZONE)
				{
					continue;
				}

				GangZoneHideForPlayer(playerid, gze_Info[id][gze_Border][y]);
			}

			return 1;
		}
	}
	return 0;
}

stock GZE_HideForAll(id)
{
	if(0 <= id < MAX_GZE)
	{
		if(gze_Info[id][gze_Exists])
		{
			for(new y = 0; y < MAX_GANG_ZONES; y++)
			{
				if(gze_Info[id][gze_Border][y] == INVALID_GANG_ZONE)
				{
					continue;
				}

				GangZoneHideForAll(gze_Info[id][gze_Border][y]);
			}

			return 1;
		}
	}
	return 0;
}

stock GZE_FlashForPlayer(playerid, id, flashcolor)
{
	if(0 <= id < MAX_GZE)
	{
		if(gze_Info[id][gze_Exists])
		{
			for(new y = 0; y < MAX_GANG_ZONES; y++)
			{
				if(gze_Info[id][gze_Border][y] == INVALID_GANG_ZONE)
				{
					continue;
				}

				GangZoneFlashForPlayer(playerid, gze_Info[id][gze_Border][y], flashcolor);
			}

			return 1;
		}
	}
	return 0;
}

stock GZE_FlashForAll(id, flashcolor)
{
	if(0 <= id < MAX_GZE)
	{
		if(gze_Info[id][gze_Exists])
		{
			for(new y = 0; y < MAX_GANG_ZONES; y++)
			{
				if(gze_Info[id][gze_Border][y] == INVALID_GANG_ZONE)
				{
					continue;
				}

				GangZoneFlashForAll(gze_Info[id][gze_Border][y], flashcolor);
			}

			return 1;
		}
	}
	return 0;
}

stock GZE_StopFlashForPlayer(playerid, id)
{
	if(0 <= id < MAX_GZE)
	{
		if(gze_Info[id][gze_Exists])
		{
			for(new y = 0; y < MAX_GANG_ZONES; y++)
			{
				if(gze_Info[id][gze_Border][y] == INVALID_GANG_ZONE)
				{
					continue;
				}

				GangZoneStopFlashForPlayer(playerid, gze_Info[id][gze_Border][y]);
			}

			return 1;
		}
	}
	return 0;
}

stock GZE_StopFlashForAll(id)
{
	if(0 <= id < MAX_GZE)
	{
		if(gze_Info[id][gze_Exists])
		{
			for(new y = 0; y < MAX_GANG_ZONES; y++)
			{
				if(gze_Info[id][gze_Border][y] == INVALID_GANG_ZONE)
				{
					continue;
				}

				GangZoneStopFlashForAll(gze_Info[id][gze_Border][y]);
			}

			return 1;
		}
	}
	return 0;
}

stock GZE_DestroyAll()
{
	for(new x = 0; x < MAX_GZE; x++)
	{
		if(!gze_Info[x][gze_Exists])
		{
			continue;
		}

		for(new y = 0; y < MAX_GANG_ZONES; y++)
  		{
  			if(gze_Info[x][gze_Border][y] == INVALID_GANG_ZONE)
  			{
  				continue;
  			}

  			GangZoneDestroy(gze_Info[x][gze_Border][y]);
  		}

  		gze_Info[x][gze_Exists] = false;
	}
	return 1;
}
