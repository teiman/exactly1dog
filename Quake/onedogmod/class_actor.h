

extern "C" {
	#include "quakedef.h"  // o el header donde esté definido edict_t
}

class Actor {
public:    	
 	Actor(edict_t* e);

    vec3_t * origin();
    void set_origin(const vec3_t origin);
    bool is_alive() const { return ed->v.health > 0; }
    edict_t* raw();
	void setModel(char *name);
protected:
    edict_t* ed;
};
