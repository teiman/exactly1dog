

#include "actor.h"

class Cabeza : public Actor {
public:
	Cabeza(edict_t* e); 
    void enable(edict_t* player);
	Cabeza * sync();
	Cabeza * sync_position();

	static Cabeza * Allocate();
private:
	edict_t * player;	
};

