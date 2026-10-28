#include "modules_main.hpp"
#include "test_module.hpp"

#include <iostream>
#include <stdio.h>

namespace cc
{


    template<int N>
class Clock {
    public:

    void RegisterEngine(Engine* engine) {
        if(registered_engines_ >= N) {
            return;
        }

        engines[registered_engines_] = engine;
        registered_engines_++;

        printf("Nr of registered engines = %d\n", registered_engines_);
    }

    void Init() {
        for(int i = 0; i < registered_engines_; i++) {
            if(engines[i] == nullptr) 
                continue;

            engines[i]->Init();
        }
    }

    // ticks once pr ms.
    void Tick() {
        ticks_++;

        if(ticks_ == 15) {
            for(int i = 0; i < registered_engines_; i++) {
                if(engines[i] == nullptr)
                    continue;

                engines[i]->Update(10);
            }
            ticks_ = 0;
        }
    }

    int ticks_ = 0;
    Engine* engines[N] {}; // 0 -> world, 1 -> player, 2 -> forrest.
    int registered_engines_ = 0;
};

int Run()
{
    World world;
    Player player;
    Forrest forreset;
    Clock<5> clock;

    clock.RegisterEngine(&world);
    clock.RegisterEngine(&player);
    clock.RegisterEngine(&forreset);

    clock.Init();

    for(int i = 0; i < 16; i++) {
        clock.Tick();
    }

    return 0;
}
}
