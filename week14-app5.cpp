#include "less_macro.hpp"

// subroutines (1950s) vs coroutines (1960s)

#ifdef __clang__
#include <experimental/coroutine> // gcc users need to include <coroutine> not experimental/...
#include <iostream>
#include <thread>
#include <future> // for async

#include <cppcoro/generator.hpp>
#include <cppcoro/single_consumer_event.hpp>
#include <cppcoro/task.hpp>
#include <cppcoro/sync_wait.hpp>

// Coroutine Types
//  task<T>
//  shared_task<T>
//  generator<T>
//  recursive_generator<T>
//  async_generator<T>

// Awaitable Types
//  single_consumer_event
//  single_consumer_async_auto_reset_event
//  async_mutex
//  async_manual_reset_event
//  async_auto_reset_event
//  async_latch
//  sequence_barrier
//  multi_producer_sequencer
//  single_producer_sequencer

cppcoro::single_consumer_event event;
std::string value;

// A task represents an asynchronous computation that is executed lazily in that the execution
// of the coroutine does not start until the task is awaited.
cppcoro::task<> consumer()
{
    // Coroutine will suspend here until some thread calls event.set()
    // eg. inside the producer() function below.
    co_await event;
    std::cout << value << std::endl;
}

void producer()
{
    value = "foo";
    // This will resume the consumer() coroutine inside the call to set() if it is currently suspended.
    event.set();
}


auto fibonacci() -> cppcoro::generator<const std::uint64_t>
{
    auto a = std::uint64_t{0};
    auto b = std::uint64_t{1};
    while(true)
    {
        co_yield b;
        auto tmp = a;
        a = b;
        b += tmp;
    }
}
#endif

int main()
{
    // When a coroutine function returning a cppcoro::generator<T> is called the coroutine is created
    // initially suspended.
    // Execution of the coroutine enters the coroutine body when the generator<T>::begin() method is called and
    // continues until either the first co_yield statement is reached or the coroutine runs to completion.
    // If the returned iterator is not equal to the end() iterator then dereferencing the iterator will
    // return a reference to the value passed to the co_yield statement.
    // Calling operator++() on the iterator will resume execution of the coroutine and continue until either
    // the next co_yield point is reached or the coroutine runs to completion().
    // Any unhandled exceptions thrown by the coroutine will propagate out of the begin() or operator++() calls
    // to the caller.
#ifdef __clang__
    for (auto i : fibonacci())
    {
        if (i > 1'000'000) break;
        std::cout << i << std::endl;
    }

    // -- co_await example with a producer consumer scenario --
    // The function template async runs the function asynchronously
    // (potentially in a separate thread which might be a part of a thread pool)
    // and returns a std::future that will eventually hold the result of that function call.
    auto con = std::async([]{ cppcoro::sync_wait(consumer()); });
    auto prod = std::async(producer);
    con.get(), prod.get();
#endif
}
