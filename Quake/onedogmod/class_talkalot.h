
#include <string>

enum class ConversationState {
    WaitingForLoading,
    Saluting,
    WaitingEvent,
	Event777
};


enum class TalkEvent {
    Loaded,
    On777,
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
	std::string lastMsg = nullptr;

	TalkAlot() {}                          // private constructor
    TalkAlot(const TalkAlot&) = delete; // prevent copy
    TalkAlot& operator=(const TalkAlot&) = delete; // prevent assign
};


const char * talkalot_getMessage();
void talkalot_event(TalkEvent event);