
extern "C" {
	#include "quakedef.h"
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
		return "";
	}

	return lastMsg;
}

std::map<ConversationState, std::vector<std::string>> responses = {
	{ConversationState::WaitingForLoading, {}},
	{ConversationState::Saluting, {"The watchers will watch you fight","Oh, a fine fighter from Earth", "You would do a fine adition to our forces"}},
	{ConversationState::WaitingEvent, {}},
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

void TalkAlot::handleEvent(TalkEvent event){

	if(currentState == ConversationState::WaitingForLoading)
		if(event == TalkEvent::Loaded){
			currentState = ConversationState::Saluting;			
			updateMessage();
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