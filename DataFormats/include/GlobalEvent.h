#ifndef CaloCubeGlobalEvent_h
#define CaloCubeGlobalEvent_h

namespace CaloCube {
  class GlobalEvent {

    public:		
    
    static unsigned int getEventNumber() {return _eventNumber;}

    static void setEventNumber(unsigned int event) {_eventNumber = event;} 

    private:
    static unsigned int _eventNumber;

  };


}
#endif
