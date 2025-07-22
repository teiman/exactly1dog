

#include "class_actor.h"


extern "C" void SV_LinkEdict (edict_t *ent, qboolean touch_triggers);


Actor::Actor(edict_t* e) : ed(e) {};

vec3_t* Actor::origin() {
    return &ed->v.origin;
}

void Actor::set_origin(const vec3_t origin) {
    VectorCopy(origin, ed->v.origin); // usa macro de Quake
}

edict_t* Actor::raw() {
    return ed;
}

void Actor::setModel(char *name){
	ed->v.modelindex = SV_ModelIndex(name);
	ed->v.model = PR_SetEngineString(name);
	
	SV_LinkEdict (ed, false);
}
