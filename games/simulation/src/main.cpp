#include "engine/engine.h"
#include <cstdio>

struct Score {
    int value = 0;
    Score(int value): value(value) {}
};

void printScore(Score& score) {
    printf("THE SCORE IS: %d\n", score.value);
    score.value += 10;
}

int main() {
    engine::Engine engine;

    engine.registerResource<Score>(10);
    engine.addSystem(printScore);

    engine.start();
}
