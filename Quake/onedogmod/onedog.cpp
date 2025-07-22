

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

	if(0)		
		talkalot_event(TalkEvent::Loaded);
}

extern "C" void Sbar_DrawPicAlpha (int x, int y, qpic_t *pic, float alpha);
extern "C" qpic_t *Sbar_InventoryBarPic (void);
extern "C" qpic_t * Sbar_getSigil( int i);
extern "C" qpic_t * Sbar_getFace(int dx);
extern "C" void M_PrintWhiteEx (int cx, int cy, int dim, const char *str);

double last_step_time  = 0;
int slot_value[3];

double update_slot_raw(int slot, double slot_start_time, double speed) {	
    double now = current_time();
    double elapsed = now - slot_start_time;

    if (elapsed >= speed) {
        slot_value[slot] = rand() % 10; // valor final		

		slot_start_time = now;
    } 
	
	const int delta_aux = 11;
	const int fontsize_aux = 11;
	const int padizq_aux = 3;

	const int slot_dx = 17 * slot;

	M_PrintWhiteEx(50 + padizq_aux + slot_dx, 400 - delta_aux, fontsize_aux, va("%d", abs(slot_value[slot]-1)%9 ));
	M_PrintWhiteEx(50 + padizq_aux + slot_dx, 400 + delta_aux + 5, fontsize_aux, va("%d", (slot_value[slot]+1)%9 ));

	M_PrintEx(50 + slot_dx, 400, 16, va("%d", slot_value[slot]));

	return slot_start_time;
}

void update_slots(){	
	static double slot_start_time1 = 0;
	static double slot_start_time2 = 0;
	static double slot_start_time3 = 0;    
	static double started = 0.0;
	static double speed = 0.01;

	double now = current_time();

	//Like.. after the 2th map
	if(started>now)
		started = 0;

	double elapsed = now - started;		

	if (!started)
		started = now;
	
	if (elapsed>8){
		speed = 0.01;
		started = now;

		slot_start_time1 = 0;
		slot_start_time2 = 0;
		slot_start_time3 = 0;    
	} else if(elapsed>4){
		speed = speed + (elapsed-4)/120;

		if(speed>=1){
			speed = 1;
		}
	}

	slot_start_time1 = update_slot_raw(0,slot_start_time1, speed);
	slot_start_time2 = update_slot_raw(1,slot_start_time2, speed);
	slot_start_time3 = update_slot_raw(2,slot_start_time3, speed);
	//M_PrintEx (50, 300, 16, va("speed=%f", speed) );	
}



void onedog_overtext_rendering()
{
	if (cls.state != ca_connected)// otherwise the game lagsss
		return;
	//cabeza && cabeza->sync_position();

	char text[] = "Corruption level 0%%";
	M_PrintEx (50, 450, 8,  randomizerText(va(text)) );	


	//this appear to be in 320-200 screen
	Sbar_DrawPicAlpha (50, 50, Sbar_getFace(1), 1);//Invis face

	//this appears to be in "current res" pixel size???

	
	if(0){
		if( talkalot_getMessage() != nullptr)
			M_PrintEx (50+ 32, 50 + 25, 16, talkalot_getMessage());	
	}

	//M_PrintEx (50, 400, 16, "0");	

	update_slots();
}

