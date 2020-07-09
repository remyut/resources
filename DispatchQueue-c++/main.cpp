#include <iostream>
#include <csignal>
#include "DispatchQueue.h"


using namespace std;


bool _continue = true;
 std::string run(void){
         std::thread::id this_id = std::this_thread::get_id();
         std::cout << this_id << std::endl;
         return "from thread";
}

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";
   _continue = false;
}

int main()
{
    signal(SIGINT, signalHandler);
    fp_t myFunc = run;

    DispatchQueue q("Remy Demo Dispatch Queue", 4);


    while(_continue) {
        q.dispatch(std::bind(myFunc));
    }


    return 0;
}




