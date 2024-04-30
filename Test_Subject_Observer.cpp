#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "trompeloeil.hpp"
#include "Subject.h"
#include "Observer.h"

// Mock Observer class
class MockObserver : public Observer
{
public:
    MAKE_MOCK3(refresh, void(int, int, int), override);
};

// Mock Subject class
class MockSubject : public Subject
{
public:
    MAKE_CONST_MOCK0(getRegisteredObserverCount, size_t(), override);
    MAKE_MOCK3(notify, void(int, int, int), override);
    MAKE_MOCK1(attach, void(Observer *), override);
    MAKE_MOCK1(detach, void(Observer *), override);
};

TEST_CASE("Subject Notify")
{
    // Create mock Subject object
    MockSubject subject;

    SUBCASE("Notify")
    {
        // Set expectations for the mock Subject
        REQUIRE_CALL(subject, notify(100, 5, 10));

        // Notify mock Subject
        subject.notify(100, 5, 10);
    }
}

TEST_CASE("Subject Attach & Detach")
{
    Subject subject;

    MockObserver observer;

    subject.attach(&observer);

    SUBCASE("Attach and detach")
    {
        CHECK(subject.getRegisteredObserverCount() == 1);

        subject.detach(&observer);

        CHECK(subject.getRegisteredObserverCount() == 0);
    }
}

TEST_CASE("Observer refresh")
{
    // Create mock Observer object
    MockObserver observer;

    SUBCASE("Refresh")
    {
        // Set expectations for the mock Observer
        REQUIRE_CALL(observer, refresh(100, 5, 10));

        // Call refresh method of mock Observer
        observer.refresh(100, 5, 10);
    }
}

TEST_CASE("Subject getRegisteredObserverCount")
{
    MockSubject subject;

    SUBCASE("Empty Observer List")
    {
        REQUIRE_CALL(subject, getRegisteredObserverCount()).RETURN(0);

        CHECK(subject.getRegisteredObserverCount() == 0);
    }
}
