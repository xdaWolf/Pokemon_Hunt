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
    // Create mock Subject object
    Subject subject;

    // Create mock Observer object
    MockObserver observer;

    // Attach observer to subject
    subject.attach(&observer);

    SUBCASE("Attach and detach")
    {
        // Check if observer was attached
        CHECK(subject.getRegisteredObserverCount() == 1);

        // Detach observer from subject
        subject.detach(&observer);

        // Check if observer was detached
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
    // Erstellen einer Instanz der MockSubject-Klasse
    MockSubject subject;

    SUBCASE("Empty Observer List")
    {
        // Setzen der Erwartungen für die Methode getRegisteredObserverCount
        REQUIRE_CALL(subject, getRegisteredObserverCount()).RETURN(0);

        // Überprüfen, ob die Anzahl der registrierten Beobachter 0 ist
        CHECK(subject.getRegisteredObserverCount() == 0);
    }
}
