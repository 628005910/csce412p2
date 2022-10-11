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

        /**
         * This function returns the loadbalancer's clock time.
        */
        int getTime() {
            return systemTime;
        }

        /**
         * This function increments the loadbalancer's clock time.
        */
        void incTime() {
            systemTime++;
        }

        /**
         * This function adds a request to the request queue, and increments the loadbalancer's clock time.
        */
        void addRequest(request r) {
            requestQ.push(r);
            incTime();
        }

        /**
         * This function dequeues the element at the front of the queue, and returns the element. It also increments the loadbalancer's clock time.
        */
        request getRequest() {
            incTime();
            if (!requestQ.empty()) {
                request r = requestQ.front();
                requestQ.pop();
                return r;
            }
        }

        /**
         * returns whether or not the request queue is empty.
         * 
         * @retval TRUE the request queue is empty
         * @retval FALSE the request queue is not empty
        */
        bool empty() {
            return requestQ.empty();
        }
    private:
        int systemTime;
        queue<request> requestQ;
};

string generateIP() {
    return to_string(rand() % 256) + '.' + to_string(rand() % 256) + '.' + to_string(rand() % 256) + '.' + to_string(rand() % 256);
}

request createRequest(int requestUpperLimit) {
    return request(generateIP(), generateIP(), rand()%requestUpperLimit);
}

/*! \mainpage Load Balancing Wiki
 *
 * \section intro_sec Introduction
 *
 * Load balancing refers to efficiently distrbuting incoming network traffic across a group of servers. 
 * It plays a crucial role in ensuring no single server is at rest nor are any single server overworked.
 * This code aims to simulate a real life load balancer by distributing a barrage of requests and allowing the user
 * to visualize how the requests are being distributed across the different servers.
 * \n\n
 *
 * \section Setup
 *
 * \subsection c - Compiling the code
 * 
 *       Compile the code using $g++ loadbalancer.cpp
 *
 * \subsection r - Running the simulation
 * 
 *        Run the code using $./a.out
 * 
 * \n
 * 
 * 
 * \section Simulation Parameters
 * 
 * When you run the simulation, the program will ask to enter a couple of parameters to tweak the settings of the simulation.
 * Below explains the different parameters, its purpose, and what to enter for them.
 * 
 * \subsection a - Number of Servers
 * 
 * This parameters expects a number representing the number of servers in your network. Generally a lower number of servers
 * results in a longer time to get through all the requests. In fact, with a small server number like 1 or 2, the servers
 * will likely never get through all the requests in time. Conversely, a higher amount of servers results in a shorter time
 * to finish all requests. 
 * \n\n
 * 
 * \subsection b - Max Request Processing Time
 * 
 * This parameter expects a number representing the maximum time for a request to finish. In the code, there is a createRequest function
 * that generates a random IP for the source and destination, and a random amount of time for a request to finish. This paramater
 * represents the upper bound on the generation of the task processing time. For example, if 500 was inputed, then any request
 * created will have a procesing time in the range [0,500] clock cycles.
 * \n\n
 * \subsection q - Incoming Request Rate
 * 
 * This parameter expects a number representing how often a new request is coming. In the real world, there is not simply a queue
 * of requests that is static since there is always requests coming in. This parameter tweaks how often requests are coming in
 * with respect to clock cycles. For example, if 10 was inputted, a new request would be added to the queue every 10 clock cycles.
 * Generally, a lower clock cycle means the servers will need to work harder to get through all the requests, and vise versa
 * for a higher incoming request rate.
 * \n\n
 * \subsection w - Number of Clock Cyles
 * 
 * This parameter expects a number representing the amount of clock cycles to simulate the load balancer. This is simply to
 * limit how long the simulation goes on for, and there may still be requests in the queue once the clock cyles have been reached.
 * For example, if 10000 was inputted, then the simulation will run for 10000 clock cyles but there may still be requests in the queue.
 * If you would like to simulate the load balancer endlessly, input -1.
 */



int main() {
    srand(time(0));
    loadbalancer lb;
    int numServers, loadBalanceRequestRate, clockCycles, requestUpperLimit;
    cout << "Number of servers: ";
    cin >> numServers;
    cout << "Max Request Processing Time: ";
    cin >> requestUpperLimit;
    cout << "Load balance request rate: ";
    cin >> loadBalanceRequestRate;
    cout << "Number of clock cycles: ";
    cin >> clockCycles;

    for (int _ = 0; _ < 2*numServers; _++) {
        lb.addRequest(createRequest(requestUpperLimit));
    }
    server servers[numServers];
    for (int i = 0; i < numServers; i++) {
        server s(i+1);
        s.consume(lb.getRequest(), lb.getTime());
        servers[i] = s;
    }

    while (lb.getTime() < clockCycles) {
        int currTime = lb.getTime();
        if (servers[currTime%numServers].isCurrentlyWaiting()) {
            if (!lb.empty()) {
                servers[currTime%numServers].consume(lb.getRequest(), currTime);
                servers[currTime%numServers].setWaiting(false);
            }
            else {
                cout << "Time " << currTime << ": Server #" << servers[currTime%numServers].getLabel() << " is waiting for a request to process" << endl;
            }
        }
        
        else if (servers[currTime%numServers].isRequestDone(currTime)) {
            request r = servers[currTime%numServers].getRequest();
            cout << "Time " << currTime << ": Server #" << servers[currTime%numServers].getLabel() << " processed request from " << r.IPin << " to " << r.IPout << endl;
            if (!lb.empty()) servers[currTime%numServers].consume(lb.getRequest(), currTime);
            else servers[currTime%numServers].setWaiting(true);
        }

        if (lb.getTime() % loadBalanceRequestRate == 0 ) {
            request r = createRequest(requestUpperLimit);
            lb.addRequest(r);
        }
        lb.incTime();
    }
}