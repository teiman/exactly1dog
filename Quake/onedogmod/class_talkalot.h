
#include <string>

enum class ConversationState {
    WaitingForLoading,
	RestoringNormality,//would say something like "Restoring normality"
	Waiting,//Neutral, do nothing state
    Saluting,
    WaitingEvent,
	Event777,
	DEBUG_small_num,
	LowGravity,
};


enum class TalkEvent {
    Loaded,
    On777,
	OnDEBUG_small_num,
	OnSlotsStops,
	OnStopTalking,
};

class TalkAlot {
public: 
	ConversationState currentState;
	float start_time = 0;
	
    static TalkAlot& getInstance() {
        static TalkAlot instance; // created once, thread-safe
        return instance;
    }

	std::string getCurrentString();

	void handleEvent(TalkEvent event);
	void updateMessage();
	
private:
	std::string lastMsg = "";

	TalkAlot() {}                          // private constructor
    TalkAlot(const TalkAlot&) = delete; // prevent copy
    TalkAlot& operator=(const TalkAlot&) = delete; // prevent assign
};


const char * talkalot_getMessage();
void talkalot_event(TalkEvent event);