#include "missile_engine/timer.hpp"

#include <catch2/catch_test_macros.hpp>
#include <chrono>

TEST_CASE("Timer", "[core][timer]")
{
    using namespace std::chrono_literals;
    using namespace missileengine;

    SECTION("Timer can have an interval")
    {
        bool  called = false;
        Timer timer  = Timer();
        timer.set_interval(1s);

        REQUIRE(timer.get_interval() == 1s);
    }

    SECTION("Timer can be started")
    {
        Timer timer = Timer();
        timer.set_interval(1s);
        timer.start();

        REQUIRE(timer.is_running());
        REQUIRE(timer.finished() == false);
    }

    SECTION("Timer can be stopped")
    {
        Timer timer = Timer();
        timer.set_interval(1s);
        timer.start();
        timer.stop();

        REQUIRE(!timer.is_running());
        REQUIRE(timer.finished() == false);
    }

    SECTION("Timer decrements on tick")
    {
        Timer timer = Timer();
        timer.set_interval(1s);
        timer.start();
        timer.tick(0.5s);

        REQUIRE(timer.get_time_left() == 0.5s);
        REQUIRE(timer.finished() == false);
    }

    SECTION("Timer calls callback when time is up")
    {
        Timer timer = Timer();
        timer.set_interval(1s);
        timer.start();
        timer.tick(1s);

        REQUIRE(timer.get_time_left() == 0s);
        REQUIRE(timer.finished());
    }

    SECTION("Timer finished is updated on next tick")
    {
        Timer timer = Timer();
        timer.set_interval(1s);
        timer.start();
        timer.tick(1s);
        REQUIRE(timer.finished() == true);

        timer.tick(0.5s);
        REQUIRE(timer.get_time_left() == 0.0s);
        REQUIRE(timer.finished() == false);
    }

    SECTION("Timer can be reset")
    {
        Timer timer = Timer();
        timer.set_interval(1s);
        timer.start();
        timer.tick(1s);
        timer.reset();

        REQUIRE(timer.get_time_left() == 1s);
        REQUIRE(timer.finished());
    }

    SECTION("Timer has auto reset")
    {
        Timer timer = Timer();
        timer.set_interval(5s);
        timer.set_loop(true);
        timer.start();
        timer.tick(10s);

        REQUIRE(timer.get_time_left() == 5s);
        REQUIRE(timer.finished());
    }

    SECTION("Timer can be constructed using builder")
    {
        Timer timer = TimerBuilder() //
                          .with_loop(true)
                          .with_interval(1s)
                          .build();

        REQUIRE(timer.get_interval() == 1s);
        REQUIRE(timer.is_looping());
    }
}
