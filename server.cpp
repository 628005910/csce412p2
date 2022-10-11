#ifndef REQUEST_CPP
#include "request.cpp"
#endif

class server {
    public:

        /**
         * Default constructor for server; creates empty server.
         * 
         * @return empty server
        */
        server() {}

        /**
         * Constructor with label; sets label to server when constructing server.
         * 
         * @param label_ number to assign label to server to
         * @return server with label assigned
        */
        server(int label_) {
            time = 0;
            label = label_;
            isWaiting = false;
        }

        /**
         * This functions assigns a request to the server
         * 
         * @param r request to be assigned to the server
         * @param currTime current time to be updated to the server's internal system clock
        */
        void consume(request r, int currTime) {
            request = r;
            time = currTime;
        }

        /**
         * This functions returns the current request assigned to the server
         * 
        */
        request getRequest() {
            return request;
        }

        /**
         * This functions returns the label of the server, represented by a number.
         * 
        */
        int getLabel() {
            return label;
        }

        /**
         * This function returns whether or not the server is done processing its assigned request.
         * 
         * @param currTime the time value that the request time is being compared to
         * 
         * @retval TRUE the server's assigned request is done processing.
         * @retval FALSE the server's assigned request is still being processed.
        */
        bool isRequestDone(int currTime) {
            return (currTime >= (time + request.startProcessTime));
        }

        /**
         * This function sets the server to waiting or not waiting.
         * 
         * @param state boolean value to set the server's waiting status to 
        */
        void setWaiting(bool state) {
            isWaiting = state;
        }

        /**
         * This function returns if the server is currently waiting for another request to consume.
         * 
         * @retval TRUE the server has completed its assigned request and is waiting for another to consume
         * @retval FALSE the server is currently processing a request, and is NOT waiting for another request to consume.
        */
        bool isCurrentlyWaiting() {
            return isWaiting;
        }

    private:
        request request;
        int time;
        int label;
        bool isWaiting;
};