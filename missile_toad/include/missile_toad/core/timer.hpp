#pragma once

#include "common.hpp"
#include "locator.hpp"
#include <chrono>

namespace missiletoad::core
{
    /**
     * @brief A timer that calls a callback after a certain amount of time.
     */
    class Timer
    {
    private:
        /**
         * The interval of the timer.
         * A interval of 0 means the timer will only call the callback once.
         */
        std::chrono::duration<float> interval_ = std::chrono::duration<float>(0);

        /**
         * The time left on the timer.
         */
        std::chrono::duration<float> time_left_ = std::chrono::duration<float>(0);

        /**
         * Whether the timer is running.
         */
        bool is_running_ = false;

        /**
         * Whether the timer is looping.
         */
        bool loop_ = false;

        /**
         * Whether the timer has finished.
         */
        bool finished_ = false;

    public:
        /**
         * Default constructor.
         * @param callback callback to call when the timer reaches 0
         */
        Timer() = default;

        /**
         * Decrements the timer by delta_time and calls the callback if the timer has reached 0.
         * If the timer is looping, it will reset to the interval.
         * @param delta_time
         */
        void tick(std::chrono::duration<float> delta_time)
        {
            finished_ = false;
            if (!is_running_)
            {
                return;
            }

            time_left_ -= delta_time;

            if (time_left_ <= std::chrono::duration<float>(0))
            {
                finished_ = true;
                if (loop_)
                {
                    reset();
                }
                else
                {
                    stop();
                }
            }
        }

        /**
         * Starts the timer.
         */
        void start()
        {
            is_running_ = true;
            finished_   = false;
        }

        /**
         * Stops the timer.
         */
        void stop()
        {
            is_running_ = false;
        }

        /**
         * Resets the timer to the interval.
         */
        void reset()
        {
            time_left_ = interval_;
        }

        /**
         * Sets the interval of the timer.
         * @param interval interval to set
         */
        void set_interval(std::chrono::duration<float> interval)
        {
            interval_ = interval;
            reset();
        }

        /**
         * Sets whether the timer should loop.
         * @param loop whether the timer should loop
         */
        void set_loop(bool loop)
        {
            loop_ = loop;
        }

        /**
         * Returns whether the timer is running.
         * @return true if the timer is running, false otherwise
         */
        [[nodiscard]] bool is_running() const
        {
            return is_running_;
        }

        /**
         * Returns whether the timer is looping.
         * @return true if the timer is looping, false otherwise
         */
        [[nodiscard]] bool is_looping() const
        {
            return loop_;
        }

        /**
         * Returns the interval of the timer.
         * @return interval of the timer
         */
        [[nodiscard]] std::chrono::duration<float> get_interval() const
        {
            return interval_;
        }

        /**
         * Returns the time left on the timer.
         * @return time left on the timer
         */
        [[nodiscard]] std::chrono::duration<float> get_time_left() const
        {
            return time_left_;
        }

        [[nodiscard]] bool finished() const
        {
            return finished_;
        }
    };

    /**
     * @brief A builder for a timer.
     * @tparam has_callback Callback is set
     * @tparam has_interval Interval is set
     * @tparam has_loop Loop is set
     */
    template <bool has_interval = false, bool has_loop = false>
    class TimerBuilder
    {
    private:
        std::chrono::duration<float> interval_ = std::chrono::duration<float>(0);
        bool                         loop_     = false;

        template <bool has_interval_, bool has_loop_>
        friend class TimerBuilder;

        template <bool has_interval_, bool has_loop_>
        TimerBuilder(TimerBuilder<has_interval_, has_loop_> builder)
            : interval_(builder.interval_), loop_(builder.loop_)
        {
        }

    public:
        /**
         * Default constructor.
         */
        TimerBuilder() = default;

        /**
         * Sets the interval of the timer.
         * @param interval interval to set
         * @return this
         */
        TimerBuilder<true, has_loop> with_interval(std::chrono::duration<float> interval)
        {
            interval_ = interval;
            return TimerBuilder<true, has_loop>(*this);
        }

        /**
         * Sets whether the timer should loop.
         * @param loop whether the timer should loop
         * @return this
         */
        TimerBuilder<has_interval, has_loop> with_loop(bool loop)
        {
            loop_ = loop;
            return TimerBuilder<has_interval, true>(*this);
        }

        /**
         * Builds the timer.
         * @return
         */
        [[nodiscard]] Timer build() const
        {
            static_assert(has_interval, "TimerBuilder must have callback, interval, and loop");
            auto timer = Timer();
            timer.set_interval(interval_);
            timer.set_loop(loop_);
            return timer;
        }
    };
} // namespace missiletoad::core
