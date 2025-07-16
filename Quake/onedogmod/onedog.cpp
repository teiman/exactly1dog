

extern "C" {
    #include "quakedef.h"
}


extern "C" void onedog_screen_start(){
	//Con_Printf ("Corruption detected!...\n");
	Con_Printf ( va("%cCorruption detected!...\n",2));
}

#define ALIGN_LEFT		0
#define ALIGN_CENTER	1
#define ALIGN_RIGHT		2

extern "C" void M_PrintAlignedEx (int cx, int cy, int align, int dim, qboolean color, const char *str);
extern "C" void M_Print (int cx, int cy, const char *str);

double current_time(){
	return cl.time;
}


char* randomizerText(const char* text) {
	static double last_glitch_time = 0;
	static double glitch_duration = 0.4;
	static double next_glitch_delay = 0.4;
	static int is_glitching = 0;
	static char buffer[1024];

	double time = current_time();

	if (!text) return "";

	if (!is_glitching && time - last_glitch_time > next_glitch_delay) {
		// Empezar nuevo glitch
		strncpy(buffer, text, sizeof(buffer));
		buffer[sizeof(buffer) - 1] = '\0';

		size_t len = strlen(buffer);
		for (size_t i = 0; i < len; i++) {
			if (rand() % 100 > 80) {
				const char glitch_chars[] = "@#$%&X!";
				buffer[i] = glitch_chars[rand() % (sizeof(glitch_chars) - 1)];
			}
		}

		last_glitch_time = time;
		is_glitching = 1;
	}

	if (is_glitching && time - last_glitch_time > glitch_duration) {
		is_glitching = 0;
	}

	return is_glitching ? buffer : (char*)text;
}


extern "C" void M_PrintEx (int cx, int cy, int dim /* font size */, const char *str);

extern "C" void onedog_overtext_rendering(){
	if (cls.state != ca_connected)// otherwise the game lagsss
		return;

	char text[] = "Corruption level: 0 - time: %f";

	M_PrintEx (320/2, 32, 16,  randomizerText(va(text, cl.time)) );	
}

