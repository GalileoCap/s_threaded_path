#include <thread>
#include <iostream>

#include <string>
#include <time.h>
#include <unistd.h>

using namespace std;

thread Threads[3];

time_t start;

void test(const string& s) {
    sleep(5);
    time_t end = time(0) - start;
    cout << s << " IN " << end << endl;
}

int main() {
    start = time(0);

    for (thread& t : Threads) {
        t = thread(&test, "DONE");
        sleep(1); //U: We should see all outputs with one second in between
    }

    cout << "WAITING..." << endl;

    for (thread &t : Threads) { t.join(); }

    cout << "FINISHED" << endl;

    return 0;
}
