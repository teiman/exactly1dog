
extern "C" {
    #include "quakedef.h"

	void M_PrintAlignedEx (int cx, int cy, int align, int dim, qboolean color, const char *str);
	void M_Print (int cx, int cy, const char *str);
	void M_PrintEx (int cx, int cy, int dim /* font size */, const char *str);

	extern "C" void onedog_screen_start();
	extern "C" void onedog_overtext_rendering();
	extern "C" void onedog_gameplay();
	extern "C" void Sbar_DrawPicAlpha (int x, int y, qpic_t *pic, float alpha);
	extern "C" qpic_t *Sbar_InventoryBarPic (void);
	extern "C" qpic_t * Sbar_getSigil( int i);
	extern "C" qpic_t * Sbar_getFace(int dx);
	extern "C" void M_PrintWhiteEx (int cx, int cy, int dim, const char *str);

	int NUM_FOR_EDICT(edict_t*);
} 

#include "onedog.h"
#include "class_cabeza.h"
#include "class_talkalot.h"

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
	
	talkalot_event(TalkEvent::Loaded);
}


void onedog_overtext_rendering()
{
	if (cls.state != ca_connected)// otherwise the game lagsss
		return;

	// - Corruption level 
	char text[] = "Corruption level 0%%";
	M_PrintEx (50, 450, 8,  randomizerText(va(text)) );	

	// - Drawing the Stranger face 
	//this appear to be in 320-200 screen
	Sbar_DrawPicAlpha (50, 50, Sbar_getFace(1), 1);//Invis face bg
	Sbar_DrawPicAlpha (50, 50, Sbar_getFace(2), sin(current_time()*4)/3);//Invis face
		
	// - The Stranger text 
	if( talkalot_getMessage() != nullptr)
		M_PrintExCorrupted (50+ 32, 50, 16, talkalot_getMessage());	

	// Random numbers that generate events
	update_slots();
}

