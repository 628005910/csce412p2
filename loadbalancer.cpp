#include "server.cpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <string>

using namespace std;

class loadbalancer {
    public:
        loadbalancer() {
            systemTime = 0;
        }
        int getTime() {
            return systemTime;
        }
        void incTime() {
            systemTime++;
        }
        void addRequest(request r) {
            requestQ.push(r);
            incTime();
        }
        request getRequest() {
            incTime();
            if (!requestQ.empty()) {
                request r = requestQ.front();
                requestQ.pop();
                return r;
            }
        }
        bool empty() {
            return requestQ.empty();
        }

        int bruh() {
            return requestQ.size();
        }
    private:
        int systemTime;
        queue<request> requestQ;
};

string generateIP() {
    return to_string(rand() % 256) + '.' + to_string(rand() % 256) + '.' + to_string(rand() % 256) + '.' + to_string(rand() % 256);
}

request createRequest() {
    return request(generateIP(), generateIP(), rand()%1264);
}

int main() {
    srand(time(0));
    loadbalancer lb;
    int numServers, loadBalanceIngestion, clockCycles;
    cout << "Number of servers: ";
    cin >> numServers;
    cout << "Load balance ingestion rate (1 means new requests every tick, 32 means new request every 32 ticks, etc): ";
    cin >> loadBalanceIngestionRate;
    cout << "Number of clock cycles: ";
    cin >> clockCycles;

    for (int _ = 0; _ < 2*numServers; _++) {
        lb.addRequest(createRequest());
    }
    server servers[numServers];
    for (int i = 0; i < numServers; i++) {
        server s(i+1);
        s.consume(lb.getRequest(), lb.getTime());
        servers[i] = s;
    }

    while (lb.getTime() < clockCycles) {
        int currTime = lb.getTime();
        if (servers[currTime%numServers].hasPrinted()) {
            if (!lb.empty()) {
                servers[currTime%numServers].consume(lb.getRequest(), currTime);
                servers[currTime%numServers].setPrinted(false);
            }
            else {
                cout << "Time " << currTime << ": Server #" << servers[currTime%numServers].getLabel() << " is waiting for a request to process" << endl;
            }
        }
        
        else if (servers[currTime%numServers].isRequestDone(currTime)) {
            request r = servers[currTime%numServers].getRequest();
            cout << "Time " << currTime << ": Server #" << servers[currTime%numServers].getLabel() << " processed request from " << r.IPin << " to " << r.IPout << endl;
            if (!lb.empty()) servers[currTime%numServers].consume(lb.getRequest(), currTime);
            else servers[currTime%numServers].setPrinted(true);
        }

        if (rand() % loadBalanceIngestionRate == 0 ) {
            request r = createRequest();
            lb.addRequest(r);
        }
        lb.incTime();
    }
}