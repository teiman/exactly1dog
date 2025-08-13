extern "C" {
    #include "quakedef.h"

	void M_PrintWhiteEx (int cx, int cy, int dim, const char *str);
	void M_PrintAlignedEx (int cx, int cy, int align, int dim, qboolean color, const char *str);
	void M_Print (int cx, int cy, const char *str);
	void M_PrintEx (int cx, int cy, int dim /* font size */, const char *str);
} 

#include "onedog.h"
#include "class_talkalot.h"

void slots_events(int last_number);

double last_step_time  = 0;
int slot_value[3];
int last_number = 0;

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

	if(last_number){
		M_PrintEx(102, 400, 16, va(" [%03d]", last_number));
	}

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

		last_number = slot_value[2]*100 + slot_value[1] * 10 + slot_value[0] ;

		
		slots_events(last_number);
	} else if(elapsed>4){
		speed = speed + (elapsed-4)/120;

		if(speed>=1){
			speed = 1;
		}
	}

	slot_start_time1 = update_slot_raw(0,slot_start_time1, speed);
	slot_start_time2 = update_slot_raw(1,slot_start_time2, speed);
	slot_start_time3 = update_slot_raw(2,slot_start_time3, speed);
}


void slots_events(int last_number){
	talkalot_event(TalkEvent::OnSlotsStops);

	if (last_number <500){
		talkalot_event(TalkEvent::OnDEBUG_small_num);
	}

}