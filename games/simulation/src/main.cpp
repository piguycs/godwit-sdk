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

    engine.resourceManager.registerResource<Score>(10);
    engine.resourceManager.addSystem(printScore);

    // run the engine for 2 ticks
    engine.start();
}
