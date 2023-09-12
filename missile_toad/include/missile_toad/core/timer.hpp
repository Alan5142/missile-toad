#pragma once

#include "common.hpp"
#include <chrono>

namespace missiletoad::core
{
    class Timer
    {
    private:
        std::function<void()>        callback_;
        std::chrono::duration<float> interval_;
        std::chrono::duration<float> time_left_;
        bool                         is_running_ = false;
        bool                         loop_       = false;

    public:
        Timer(std::function<void()> callback);

        /**
         * Decrements the timer by delta_time and calls the callback if the timer has reached 0.
         * If the timer is looping, it will reset to the interval.
         * @param delta_time
         */
        void tick(std::chrono::duration<float> delta_time)
        {
            if (!is_running_)
            {
                return;
            }

            time_left_ -= delta_time;

            if (time_left_ <= std::chrono::duration<float>(0))
            {
                callback_();
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
    };

    template <bool has_callback = false, bool has_interval = false, bool has_loop = false>
    class TimerBuilder
    {
    private:
        std::function<void()>        callback_;
        std::chrono::duration<float> interval_ = std::chrono::duration<float>(0);
        bool                         loop_     = false;

        template <bool has_callback_, bool has_interval_, bool has_loop_>
        friend class TimerBuilder;

        template <bool has_callback_, bool has_interval_, bool has_loop_>
        TimerBuilder(TimerBuilder<has_callback_, has_interval_, has_loop_> builder)
            : callback_(std::move(builder.callback_)), interval_(builder.interval_), loop_(builder.loop_)
        {
        }

    public:
        /**
         * Default constructor.
         */
        TimerBuilder() = default;

        /**
         * Sets the callback of the timer.
         * @param callback callback to set
         * @return this
         */
        TimerBuilder<true, has_interval, has_loop> with_callback(std::function<void()> callback)
        {
            callback_ = std::move(callback);
            return TimerBuilder<true, has_interval, has_loop>(*this);
        }

        /**
         * Sets the interval of the timer.
         * @param interval interval to set
         * @return this
         */
        TimerBuilder<has_callback, true, has_loop> with_interval(std::chrono::duration<float> interval)
        {
            interval_ = interval;
            return TimerBuilder<has_callback, true, has_loop>(*this);
        }

        /**
         * Sets whether the timer should loop.
         * @param loop whether the timer should loop
         * @return this
         */
        TimerBuilder<has_callback, has_interval, has_loop> with_loop(bool loop)
        {
            loop_ = loop;
            return TimerBuilder<has_callback, has_interval, true>(*this);
        }

        [[nodiscard]] Timer build() const
        {
            static_assert(has_callback && has_interval, "TimerBuilder must have callback, interval, and loop");
            auto timer = Timer(callback_);
            timer.set_interval(interval_);
            timer.set_loop(loop_);
            return timer;
        }
    };
} // namespace missiletoad::core
