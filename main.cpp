#include <thread>
#include <iostream>

#include <string>
#include <time.h>
#include <unistd.h>

using namespace std;

time_t start;

void test(const string& s) {
    sleep(3);
    time_t end = time(0) - start;
    cout << s << " IN " << end << endl;
}

int main() {
    start = time(0);

    thread t = thread(&test, "DONE");

    cout << "WAITING..." << endl;

    t.join();

    cout << "FINISHED" << endl;

    return 0;
}
