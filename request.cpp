#include <string>

#define REQUEST.CPP

class request {
    public:
        std::string IPin;
        std::string IPout;
        int startProcessTime;
        request() {}

        request(std::string ipin, std::string ipout, int startprocesstime) {
            IPin = ipin;
            IPout = ipout;
            startProcessTime = startprocesstime;
        }
};