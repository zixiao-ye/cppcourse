/**
 * Hello and, again, welcome to CIIP's computer aided automated testing system.
 * We hope your experience with the exercise has been a pleasant one. Your code
 * will processed and we are now ready to begin the test proper. Before we
 * start, however, keep in mind that although fun and learning are the primary
 * goals of this course, serious injuries may occur. For your own safety and the
 * safety of others, please refrain from touching ѤުϖÖƔАӇȥ̒ΔЙ җؕնÛ ߚɸӱҟˍ҇ĊɠûݱȡνȬ
 */

#include <memory>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "hw09.h"
#include <string>
#include <stdexcept>

// require at least c++20
static_assert(__cplusplus >= 202002L);


struct Marker final {
    std::string state;
    ~Marker() { state = "destructed"; }
    Marker() : state{"constructed"} {}
    Marker(Marker const&) noexcept : state{"copy constructed"} {}
    Marker(Marker&& other) noexcept : state{"move constructed"} { other.state = "move constructed husk"; }
    Marker& operator=(Marker const&) noexcept {
        state = "assigned";
        return *this;
    }
    Marker& operator=(Marker&& other) noexcept {
        state = "move assigned";
        other.state = "move assigned husk";
        return *this;
    }
};

TEST_CASE_TEMPLATE("Default Constructor", T, bool, char, short, int,
                   long long int, float, double, std::string) {
    Vector<T> v = Vector<T>();
    CHECK_EQ(v.size(), 0);
    CHECK_EQ(v.capacity(), 0);
    REQUIRE_THROWS_AS(v.at(v.size()), const std::out_of_range&);
}

TEST_CASE("String Constructor with default value") {
    int count = 10;
    std::string defaultValue{"https://github.com/doomemacs/doomemacs"};
    Vector<std::string> v = Vector<std::string>(count, defaultValue);
    CHECK_EQ(v.size(), count);
    for (auto i{0}; i < v.size(); ++i)
        CHECK_EQ(v[i], defaultValue);
    for (auto i{0}; i < v.size(); ++i)
        CHECK_EQ(v.at(i), defaultValue);
    REQUIRE_THROWS_AS(v.at(v.size()), const std::out_of_range&);

}

TEST_CASE("String Copy Constructor") {
    int count = 10;
    std::string defaultValue{"https://github.com/doomemacs/doomemacs"};
    Vector<std::string> v = Vector<std::string>(count, defaultValue);
    Vector<std::string> w = v;
    CHECK_EQ(w.size(), count);
    CHECK_EQ(v.size(), w.size());
    for (auto i{0}; i < v.size(); ++i)
        CHECK_EQ(v[i], w[i]);
    v[0] = "New Value!";
    CHECK_NE(v[0], w[0]);
    CHECK_EQ(w[0], defaultValue);
}

TEST_CASE("String Copy Assignment") {
    int count = 10;
    std::string defaultValue{"https://github.com/doomemacs/doomemacs"};
    Vector<std::string> v = Vector<std::string>(count, defaultValue);
    Vector<std::string> w = Vector<std::string>(2, "Test");
    w = v;
    CHECK_EQ(w.size(), count);
    CHECK_EQ(v.size(), w.size());
    v[0] = "New Value!";
    CHECK_NE(v[0], w[0]);
    CHECK_EQ(w[0], defaultValue);
}

TEST_CASE("String Move Constructor") {
    int count = 10;
    std::string defaultValue{"https://github.com/doomemacs/doomemacs"};
    Vector<std::string> v = Vector<std::string>(count, defaultValue);
    size_t capacity = v.capacity();
    CHECK_EQ(v.size(), count);
    Vector<std::string> w = std::move(v);
    CHECK_EQ(w.size(), count);
    CHECK_EQ(w.capacity(), capacity);
    for (auto i{0}; i < w.size(); ++i)
        CHECK_EQ(w[i], defaultValue);
}

TEST_CASE("String Move Assignment") {
    int count = 10;
    std::string defaultValue{"https://github.com/doomemacs/doomemacs"};
    Vector<std::string> v = Vector<std::string>(count, defaultValue);
    size_t capacity = v.capacity();
    Vector<std::string> w = Vector<std::string>(2, "Test");
    w = std::move(v);
    CHECK_EQ(w.size(), count);
    CHECK_EQ(w.capacity(), capacity);
    for (auto i{0}; i < w.size(); ++i)
        CHECK_EQ(w[i], defaultValue);
}

TEST_CASE_TEMPLATE("Copy Constructor", T, bool, char, short, int,
                   long long int, float, double) {
    int count = 10;
    T defaultValue{1};
    Vector<T> v = Vector<T>(count, defaultValue);
    Vector<T> w = v;
    CHECK_EQ(w.size(), count);
    CHECK_EQ(v.size(), w.size());
    for (auto i{0}; i < v.size(); ++i)
        CHECK_EQ(v[i], w[i]);
    v[0] = 0;
    CHECK_NE(v[0], w[0]);
    CHECK_EQ(w[0], defaultValue);
}

TEST_CASE_TEMPLATE("Copy Assignment", T, char, short, int,
                   long long int, float, double) {
    int count = 10;
    T defaultValue{1};
    Vector<T> v = Vector<T>(count, defaultValue);
    Vector<T> w = Vector<T>(2, 0);
    w = v;
    CHECK_EQ(w.size(), count);
    CHECK_EQ(v.size(), w.size());
    v[0] = 3;
    CHECK_NE(v[0], w[0]);
    CHECK_EQ(w[0], defaultValue);
}

TEST_CASE_TEMPLATE("Move Constructor", T, bool, char, short, int,
                   long long int, float, double) {
    int count = 10;
    T defaultValue{1};
    Vector<T> v = Vector<T>(count, defaultValue);
    size_t capacity = v.capacity();
    Vector<T> w = std::move(v);
    CHECK_EQ(w.size(), count);
    CHECK_EQ(w.capacity(), capacity);
    for (auto i{0}; i < w.size(); ++i)
        CHECK_EQ(w[i], defaultValue);
}

TEST_CASE_TEMPLATE("Move Assignment", T, char, short, int,
                   long long int, float, double) {
    int count = 10;
    T defaultValue{1};
    Vector<T> v = Vector<T>(count, defaultValue);
    size_t capacity = v.capacity();
    Vector<T> w = Vector<T>(2, 0);
    w = std::move(v);
    CHECK_EQ(w.capacity(), capacity);
    CHECK_EQ(w.size(), count);
    for (auto i{0}; i < w.size(); ++i)
        CHECK_EQ(w[i], defaultValue);
}

TEST_CASE_TEMPLATE("Constructor with default value", T, bool, char, short, int,
                   long long int, float, double) {
    int count = 10;
    T defaultValue{1};
    Vector<T> v = Vector<T>(count, defaultValue);
    CHECK_EQ(v.size(), count);
    for (auto i{0}; i < v.size(); ++i)
        CHECK_EQ(v[i], defaultValue);
    for (auto i{0}; i < v.size(); ++i)
        CHECK_EQ(v.at(i), defaultValue);
    REQUIRE_THROWS_AS(v.at(v.size()), const std::out_of_range&);
}
TEST_CASE("String Constructor with default value, expanding") {
    int count = 32;
    std::string defaultValue{"https://www.gnu.org/software/emacs/"};
    Vector<std::string> v = Vector<std::string>(count, defaultValue);
    CHECK_EQ(v.size(), count);
    for (auto i{0}; i < v.size(); ++i)
        CHECK_EQ(v[i], defaultValue);
    for (auto i{0}; i < v.size(); ++i)
        CHECK_EQ(v.at(i), defaultValue);
    REQUIRE_THROWS_AS(v.at(v.size()), const std::out_of_range&);

    defaultValue = "https://github.com/doomemacs/doomemacs";
    for (auto i{0}; i < v.size(); ++i) {
        REQUIRE_NOTHROW(v[i] = defaultValue);
        CHECK_EQ(v[i], defaultValue);
    }

    defaultValue = "https://news.ycombinator.com/item?id=29159192";
    for (auto i{0}; i < v.size(); ++i) {
        REQUIRE_NOTHROW(v.at(i) = defaultValue);
        CHECK_EQ(v.at(i), defaultValue);
    }
}

TEST_CASE_TEMPLATE("Constructor with default value, expanding", T, bool, char, short, int,
                   long long int, float, double) {
    size_t count = 32;
    T defaultValue{1};
    Vector<T> v = Vector<T>(count, defaultValue);
    CHECK_EQ(v.size(), count);
    for (auto i{0}; i < v.size(); ++i)
        CHECK_EQ(v[i], defaultValue);
    for (auto i{0}; i < v.size(); ++i)
        CHECK_EQ(v.at(i), defaultValue);
    REQUIRE_THROWS_AS(v.at(v.size()), const std::out_of_range&);

    defaultValue = 0;
    for (auto i{0}; i < v.size(); ++i) {
        REQUIRE_NOTHROW(v[i] = defaultValue);
        CHECK_EQ(v[i], defaultValue);
    }

    defaultValue = 1;
    for (auto i{0}; i < v.size(); ++i) {
        REQUIRE_NOTHROW(v.at(i) = defaultValue);
        CHECK_EQ(v.at(i), defaultValue);
    }
}

TEST_CASE_TEMPLATE("push_back", T, bool, char, short, int,
                   long long int, float, double) {
    Vector<T> v = Vector<T>();
    CHECK_EQ(v.size(), 0);
    for (size_t i{0}; i < 32; ++i) {
        v.push_back(0);
        CHECK_EQ(v[i], 0);
        CHECK_EQ(v.size(), i + 1);
    }
}

TEST_CASE("String push_back") {
    Vector<std::string> v = Vector<std::string>();
    CHECK_EQ(v.size(), 0);
    for (size_t i{0}; i < 32; ++i) {
        v.push_back("Test");
        CHECK_EQ(v[i], "Test");
        CHECK_EQ(v.size(), i + 1);
    }
}

TEST_CASE_TEMPLATE("pop_back", T, bool, char, short, int,
                   long long int, float, double) {
    size_t count = 32;
    Vector<T> v = Vector<T>(count, 1);
    CHECK_EQ(v.size(), count);
    CHECK_EQ(v.capacity(), count);
    for (size_t i{count - 1}; i > 0; --i) {
        v.pop_back();
        CHECK_EQ(v.size(), i);
        CHECK_EQ(v.capacity(), count);
    }
}

TEST_CASE("String pop_back") {
    size_t count = 32;
    Vector<std::string> v = Vector<std::string>(count, "Test");
    CHECK_EQ(v.size(), count);
    CHECK_EQ(v.capacity(), count);
    for (size_t i{count - 1}; i > 0; --i) {
        v.pop_back();
        CHECK_EQ(v.size(), i);
        CHECK_EQ(v.capacity(), count);
    }
}

TEST_CASE("Move") {
    SUBCASE("Marker") {
        Marker m;
        CHECK_EQ(m.state, "constructed");
        Marker w = std::move(m);
        CHECK_EQ(w.state, "move constructed");
        Marker n = w;
        CHECK_EQ(n.state, "copy constructed");
        w = n;
        CHECK_EQ(w.state, "assigned");
        m = std::move(w);
        CHECK_EQ(w.state, "move assigned husk");
        CHECK_EQ(m.state, "move assigned");
    }

    Marker m;
    Vector<Marker> v(1, m);
    CHECK_EQ(v[0].state, "assigned");
    CHECK_EQ(v.size(), 1);
    CHECK_EQ(v.capacity(), 1);
    v.push_back(m);
    CHECK_EQ(v[1].state, "assigned");
    v.push_back(std::move(m));

    Vector<Marker> v2 = std::move(v);
    CHECK_EQ(v2[0].state, "move assigned");
    CHECK_EQ(v2[1].state, "move assigned");
    v2[0] = std::move(Marker());
    CHECK_EQ(v2[0].state, "move assigned");
    Marker x;
    CHECK_EQ(x.state, "constructed");
    CHECK_EQ(v2[0].state, "move assigned");

    SUBCASE("List initialization") {
        Vector<Marker> v3{x, x};
        CHECK_EQ(v3[0].state, "assigned");
        CHECK_EQ(v3[1].state, "assigned");
    }

    SUBCASE("operator[] and at") {
        Vector<Marker> v3{x, x};
        v3 = v2;
        CHECK_EQ(v3[0].state, "assigned");
        CHECK_EQ(v3[1].state, "assigned");

        v3[0] = std::move(x);
        CHECK_EQ(v3[0].state, "move assigned");
        Marker y;
        v3[0] = y;
        CHECK_EQ(v3[0].state, "assigned");
        Marker z;
        v3.at(0) = z;
        CHECK_EQ(v3[0].state, "assigned");
        v3.at(0) = std::move(z);
        CHECK_EQ(v3[0].state, "move assigned");
    }

    SUBCASE("Resizing moves old elements") {
        Vector<Marker> v4(1, Marker());
        CHECK_EQ(v4[0].state, "assigned");
        Marker a;
        v4.push_back(a);
        CHECK_EQ(v4[0].state, "move assigned");
    }
}
