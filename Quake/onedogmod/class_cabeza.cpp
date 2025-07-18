
extern "C" {
	#include "quakedef.h"

	//void SV_StartSound (edict_t *entity, int channel, const char *sample, int volume, float attenuation);
}

#include "onedog.h"
#include "cabeza.h"
#include "mathlib.h"  // For AngleVectors and VectorMA macros/functions
#include "progs.h"    // For SET_MODEL and other engine defs

//vec3_t vec3_origin = {0,0,0};


vec3_t vec3_viewofs = {0,0,24};



extern "C" cvar_t	coop;

Cabeza::Cabeza(edict_t* e) : Actor(e) {
    player = nullptr;
}


Cabeza * Cabeza::sync_position()
{
	vec3_t	forward, right, up;

	if(player == nullptr)
		return nullptr;

    AngleVectors(player->v.v_angle, forward, right, up);

	// Raise view_ofs
	VectorMA(ed->v.origin, 1, vec3_viewofs, ed->v.origin); 

	// Push forward 
	VectorMA(player->v.origin, 30, forward, ed->v.origin); 

	// Push up 
	VectorMA(ed->v.origin, 18, up, ed->v.origin); 

	ed->v.angles[0] = 0;
    ed->v.angles[1] = 0;
    ed->v.angles[2] = 0;

	ed->v.angles[0] = player->v.v_angle[0] -57 ;
	ed->v.angles[1] = player->v.v_angle[1] + 180 ;
    ed->v.angles[2] = -5 ;

	return this;
}

Cabeza * Cabeza::sync()
{
	this->sync_position();

	SV_LinkEdict (ed, false);

	return this;
}


void Cabeza::enable(edict_t* player) 
{
	if(!player){
		Con_Printf("ERROR: assinging null player to Cabeza\n");
		return;
	}

	this->player = player;
	this->setModel("progs/h_player.mdl");		

    ed->v.movetype = MOVETYPE_NONE;
    ed->v.solid = SOLID_NOT;

	this->sync();
}


Cabeza* Cabeza::Allocate() {
	edict_t *e = ED_Alloc();

	if (!e) {
		return nullptr;	
	} 	

	Cabeza * cabeza = new Cabeza(e);
	edict_t * player = find_first_player();		

	if(!player)
		return nullptr;

	cabeza->enable(player);
	return cabeza;
}