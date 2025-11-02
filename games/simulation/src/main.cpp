#include "engine/engine.h"
#include <cstdio>

struct Score {
    int value = 0;
    Score(int value): value(value) {}
};

struct PlayerId {
    int id = 10;
};

void printScore(Score& score, PlayerId& id) {
    printf("THE SCORE FOR %d IS: %d\n", id.id, score.value);
    score.value += 10;
}

void renderFps() { raylib::DrawFPS(10, 10); }

int main() {
    engine::Engine engine;

    engine.registerResource<Score>(10);
    engine.registerResource<PlayerId>();

    engine.addSystem(renderFps);
    engine.addSystem(printScore);

    engine.start();
}
