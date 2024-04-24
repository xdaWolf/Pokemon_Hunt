#include "doctest.h"
#include "Subject.h"

class MockObserver : public Observer
{
public:
    int refreshCallCount = 0;
    int lastHealth = 0;
    int lastSpeed = 0;
    int lastCollected = 0;

    void refresh(int health, int speed, int collected) override
    {
        refreshCallCount++;
        lastHealth = health;
        lastSpeed = speed;
        lastCollected = collected;
    }
};

TEST_CASE("Subject constructor initializes correctly")
{
    Subject subject;
    // Hier können Tests hinzugefügt werden, um sicherzustellen, dass die Initialisierung korrekt ist
}

TEST_CASE("attach and detach methods work correctly")
{
    Subject subject;
    MockObserver observer1, observer2;
    subject.attach(&observer1);
    subject.attach(&observer2);
    REQUIRE(subject.getRegisteredObserverCount() == 2);

    subject.detach(&observer1);
    REQUIRE(subject.getRegisteredObserverCount() == 1);
    subject.detach(&observer2);
    REQUIRE(subject.getRegisteredObserverCount() == 0);
}

TEST_CASE("notify method notifies all observers correctly")
{
    Subject subject;
    MockObserver observer1, observer2;
    subject.attach(&observer1);
    subject.attach(&observer2);

    int health = 100;
    int speed = 50;
    int collected = 10;
    subject.notify(health, speed, collected);

    CHECK(observer1.refreshCallCount == 1);
    CHECK(observer1.lastHealth == health);
    CHECK(observer1.lastSpeed == speed);
    CHECK(observer1.lastCollected == collected);

    CHECK(observer2.refreshCallCount == 1);
    CHECK(observer2.lastHealth == health);
    CHECK(observer2.lastSpeed == speed);
    CHECK(observer2.lastCollected == collected);
}
