#ifndef REQUEST_CPP
#include "request.cpp"
#endif

class server {
    public:
        server() {}

        server(int label_) {
            time = 0;
            label = label_;
            alreadyPrinted = false;
        }

        void consume(request r, int currTime) {
            request = r;
            time = currTime;
        }

        request getRequest() {
            return request;
        }

        int getLabel() {
            return label;
        }

        bool isRequestDone(int currTime) {
            return (currTime >= (time + request.startProcessTime));
        }

        void setPrinted(bool x) {
            alreadyPrinted = x;
        }

        bool hasPrinted() {
            return alreadyPrinted;
        }

    private:
        request request;
        int time;
        int label;
        bool alreadyPrinted;
};