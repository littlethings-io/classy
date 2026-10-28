#pragma once
#include <stdio.h>

namespace cc {

    // inheritance

    // Pure abstract class, base class.
    class Engine {
        public:
            virtual ~Engine() {}

            // Pure virtual function
            virtual void Update(double dt) = 0;

            virtual void Init() {
                printf("Engine init\n");
            }
            bool started_ = false;        

    };

    class Player : public Engine {
        public:
        virtual ~Player() {}
                
        void Init() override {
            printf("Init player\n");
        }

        void Update(double dt) override {
            printf("Player updated\n");
        }
    };


    class World : public Engine {
        public:
            virtual ~World() {}

        void Init() override {
            printf("Init World\n");
        }

        void Update(double dt) override {
            printf("World updated\n");
        }
    };

    class Forrest : public Engine {
        public:
            virtual ~Forrest() {}

            void Update(double dt) override {
                printf("Forrest updated\n");
            }
    };

}