#include <string>

#define REQUEST.CPP

class request {
    public:
        std::string IPin;
        std::string IPout;
        int startProcessTime;

        /**
         * Default constructor for request; sets IPin and IPout to empty strings, and startProcessTime to 0.
         * 
         * @return empty request
        */
        request() {}

        /**
         * Full constructor for request; sets all parameters to given parameters.
         * 
         * @param ipin IP for IPin to be set to
         * @param ipout IP for IPout to be set to
         * @param startprocesstime time for startProcessTime to be set to
         * 
         * @return resulting request
        */
        request(std::string ipin, std::string ipout, int startprocesstime) {
            IPin = ipin;
            IPout = ipout;
            startProcessTime = startprocesstime;
        }
};