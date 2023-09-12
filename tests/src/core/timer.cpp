#include "missile_toad/core/timer.hpp"

#include <catch2/catch_test_macros.hpp>
#include <chrono>

TEST_CASE("Timer", "[core]")
{
    using namespace std::chrono_literals;
    using namespace missiletoad::core;

    SECTION("Timer can have an interval")
    {
        bool  called = false;
        Timer timer  = Timer([]() {});
        timer.set_interval(1s);

        REQUIRE(timer.get_interval() == 1s);
    }

    SECTION("Timer can be started")
    {
        bool  called = false;
        Timer timer  = Timer([&called]() { called = true; });
        timer.set_interval(1s);
        timer.start();

        REQUIRE(timer.is_running());
        REQUIRE(!called);
    }

    SECTION("Timer can be stopped")
    {
        bool  called = false;
        Timer timer  = Timer([&called]() { called = true; });
        timer.set_interval(1s);
        timer.start();
        timer.stop();

        REQUIRE(!timer.is_running());
        REQUIRE(!called);
    }

    SECTION("Timer decrements on tick")
    {
        bool  called = false;
        Timer timer  = Timer([&called]() { called = true; });
        timer.set_interval(1s);
        timer.start();
        timer.tick(0.5s);

        REQUIRE(timer.get_time_left() == 0.5s);
        REQUIRE(!called);
    }

    SECTION("Timer calls callback when time is up")
    {
        bool  called = false;
        Timer timer  = Timer([&called]() { called = true; });
        timer.set_interval(1s);
        timer.start();
        timer.tick(1s);

        REQUIRE(timer.get_time_left() == 0s);
        REQUIRE(called);
    }

    SECTION("Timer can be reset")
    {
        Timer timer = Timer([] {});
        timer.set_interval(1s);
        timer.start();
        timer.tick(1s);
        timer.reset();

        REQUIRE(timer.get_time_left() == 1s);
    }

    SECTION("Timer has auto reset")
    {
        bool  called = false;
        Timer timer  = Timer([&called]() { called = true; });
        timer.set_interval(5s);
        timer.set_loop(true);
        timer.start();
        timer.tick(10s);

        REQUIRE(timer.get_time_left() == 5s);
        REQUIRE(called);
    }

    SECTION("Timer can be constructed using builder")
    {
        Timer timer = TimerBuilder() //
                          .with_loop(true)
                          .with_interval(1s)
                          .with_callback([]() {})
                          .build();

        REQUIRE(timer.get_interval() == 1s);
        REQUIRE(timer.is_looping());
    }
}
