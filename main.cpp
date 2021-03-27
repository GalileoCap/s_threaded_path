#include <thread>
#include <string>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define TOTAL_POINTS 10

struct Point {
    bool visited = false;
    float x = 0.0;
    float y = 0.0;
} Points [TOTAL_POINTS];

struct Path {
    struct Point points[TOTAL_POINTS];
    int path[TOTAL_POINTS];
    void basic() { //U: Creates a basic path
        for (int i = 0; i < TOTAL_POINTS; ++i) {
            points[i] = Points[i]; path[i] = i;
        }
    }
    float length(const int &depth) { //U: Calculates the length of the path
        float res = 0;
        for (int i = 0; i < depth; ++i) {
            struct Point p0 = points[path[i]], p1 = points[path[i + 1]]; //U: This point and the next one
            res += sqrt(pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2)); //A: Cartesian distance
        }
        return res;
    }
    void print(const int &depth) { //U: Prints the path
        cout << "LENGTH: " << length(depth) << " PATH:";
        for (int i = 0; i <= depth; ++i) { cout << ' ' << path[i]; }
        cout << endl;
    }
} Best;

float RandomFloat(float a, float b) { //U: Returns a random float between a and b
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void calc_best_path(const struct Path &path, const int &depth) { //U: Calculates the best path
    struct Path new_path = path;
    for (int i = 0; i < TOTAL_POINTS; ++i, new_path = path) {
        struct Point &p = new_path.points[i];
        if (!p.visited) {
            p.visited = true; new_path.path[depth] = i; //A: Mark this point as visited
            if (depth == (TOTAL_POINTS - 1)) { //A: I've visited all points
                //DBG: cout << new_path.length(depth) << ' ' << Best.length(depth) << ' '; new_path.print(depth);
                if (new_path.length(depth) < Best.length(depth)) { Best = new_path; } //A: It's the new best path
            } else {
                calc_best_path(new_path, depth + 1);
            }
        }
    }
}

void calc_best_path_n() { //U: Calculates the best path without using multithreading
    const time_t time0 = time(0);

    struct Path p; p.basic();
    calc_best_path(p, 0);

    const time_t time1 = time(0) - time0;
    cout << "Normal BEST PATH IN " << time1 << ' '; Best.print(TOTAL_POINTS - 1);
}

int main() {
    for (struct Point& point : Points) {
        point.x = RandomFloat(0, 10); point.y = RandomFloat(0, 10);
    }

    Best.basic(); //A: Resetting Best
    calc_best_path_n();
    return 0;
}
