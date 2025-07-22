

extern "C" {
	#include "quakedef.h"
}


double current_time(){
	return cl.time;
}

char* randomizerText(const char* text) {
	static double last_glitch_time = 0;
	static double glitch_duration = 0.3;
	static double next_glitch_delay = 0.8;
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
				const char glitch_chars[] = "_ ";
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



void VectoAngles(const vec3_t vec, vec3_t angles)
{
    float yaw, pitch, forward;

    if (vec[0] == 0 && vec[1] == 0)
    {
        yaw = 0;
        if (vec[2] > 0)
            pitch = 90;
        else
            pitch = 270;
    }
    else
    {
        yaw = atan2(vec[1], vec[0]) * (180.0f / M_PI);
        if (yaw < 0)
            yaw += 360;

        forward = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
        pitch = atan2(vec[2], forward) * (180.0f / M_PI);
        if (pitch < 0)
            pitch += 360;
    }

    angles[0] = pitch;
    angles[1] = yaw;
    angles[2] = 0;
}
