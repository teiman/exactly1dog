
extern "C" {
	#include "quakedef.h"
	void S_LocalSound (const char *name);

	extern cvar_t sv_gravity;
}

#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <map>

#include "onedog.h"
#include "class_talkalot.h"


std::string TalkAlot::getCurrentString()
{
	if( current_time() - start_time > 6 ){
		talkalot_event( TalkEvent::OnStopTalking );
		return "";
	}

	return lastMsg;
}

std::map<ConversationState, std::vector<std::string>> responses = {
	{ConversationState::WaitingForLoading, {""}},
	{ConversationState::Saluting, {"The watchers will watch you fight","Oh, a fine fighter from Earth", "You would be a fine adition to our forces", "Wellcome Ranger"}},
	{ConversationState::WaitingEvent, {""}},
	{ConversationState::DEBUG_small_num, {"Thats a small number you got."}},
	{ConversationState::LowGravity, {"The gravity is getting eaten"}},
};
	

/**
 * Based on the current state, picks a string to emi
 * if theres more than one string available, picks a random one
 */
void TalkAlot::updateMessage()
{	
	//Timer. after some time the message don't show.
	start_time = current_time(); 

	std::vector<std::string> possibleResponses = responses[currentState];

	if(!possibleResponses.size()){
		lastMsg = "";
		return;
	}
	
    int index = rand() % possibleResponses.size();    
	lastMsg = possibleResponses[index];
}

void TalkAlot::handleEvent(TalkEvent event)
{
	if(currentState == ConversationState::WaitingForLoading){
		if(event == TalkEvent::Loaded){
			//Con_Printf("[debug] Was waiting, now will salute\n");
			currentState = ConversationState::Saluting;			
			updateMessage();
			return;
		}	
	}

	if ( event == TalkEvent::OnSlotsStops){
		//Con_Printf("New choice made!\n");
		S_LocalSound ("misc/talk.wav");
	}

	if ( event == TalkEvent::OnDEBUG_small_num){
		S_LocalSound ("misc/menu1.wav");

		currentState = ConversationState::LowGravity;			
		updateMessage();

		sv_gravity.value = 100;
		return;
	}

	if (event == TalkEvent::OnStopTalking && currentState == ConversationState::LowGravity){
		currentState = ConversationState::Waiting;			
		sv_gravity.value = 800;		
		return;
	}

}

const char * talkalot_getMessage()
{
	TalkAlot &talker = TalkAlot::getInstance();	

	const std::string& line = talker.getCurrentString();

    if (line.empty()) {
        return nullptr;
    }

	return line.c_str(); 
}

void talkalot_event(TalkEvent event)
{
	TalkAlot &talker = TalkAlot::getInstance();

	talker.handleEvent(event);
}