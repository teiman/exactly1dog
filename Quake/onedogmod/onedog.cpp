

extern "C" {
    #include "quakedef.h"

	void M_PrintAlignedEx (int cx, int cy, int align, int dim, qboolean color, const char *str);
	void M_Print (int cx, int cy, const char *str);
	void M_PrintEx (int cx, int cy, int dim /* font size */, const char *str);

	extern "C" void onedog_screen_start();
	extern "C" void onedog_overtext_rendering();
	extern "C" void onedog_gameplay();

	int NUM_FOR_EDICT(edict_t*);
} 

#include "onedog.h"
#include "cabeza.h"

void onedog_cleanup();

static Cabeza* cabeza = nullptr;

void onedog_screen_start(){
	Con_Printf ( va("%cCorruption detected!...\n",2));

	onedog_cleanup();
}


void onedog_cleanup(){
	if (cabeza != nullptr){
		delete cabeza;
        cabeza = nullptr;
	}
}

void onedog_cabeza(){
	if(!cabeza)
		cabeza = Cabeza::Allocate();
	
	cabeza && cabeza->sync();
}

void onedog_gameplay()
{
	if( current_time()<5) // skip first seconds
		return; 

	onedog_cabeza(); //creates the cabeza and animate it 
}

extern "C" void Sbar_DrawPicAlpha (int x, int y, qpic_t *pic, float alpha);

extern "C" static qpic_t *sb_sigil[4];
extern "C" qpic_t *Sbar_InventoryBarPic (void);

void onedog_overtext_rendering()
{
	if (cls.state != ca_connected)// otherwise the game lagsss
		return;

	char text[] = "Corruption level: 0 - time: %f";

	M_PrintEx (320/2, 32, 16,  randomizerText(va(text, cl.time)) );	

	cabeza && cabeza->sync_position();

	//Sbar_DrawPicAlpha (50, 50, sb_sigil[1], 1);
	//Sbar_DrawPicAlpha (100, 100, Sbar_InventoryBarPic () , 1);	 
}

