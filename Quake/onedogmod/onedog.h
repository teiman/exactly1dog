

// Shared stuff with the C world

#ifdef __cplusplus
extern "C" {
#endif

void onedog_screen_start(void);
void onedog_overtext_rendering(void);
void onedog_gameplay();

edict_t* find_first_player(void);

#ifdef __cplusplus
}
#endif

// C++ only stuff

double current_time();
char* randomizerText(const char* text);
void VectoAngles(const vec3_t vec, vec3_t angles);
