#pragma once

#include <array>

template <typename T, typename U, typename V, typename W> struct Quadruple {
public:
    Quadruple(T a, U b, V c, W d) : first{a}, second{b}, third{c}, fourth{d} {}
    T get_first(){
        return first;
    }
    U get_second(){
        return second;
    }
    V get_third(){
        return third;
    }
    W get_fourth(){
        return fourth;
    }

private:
    T first;
    U second;
    V third;
    W fourth;
};


template <> struct Quadruple<int, int, int, int> {
public:
    std::array<int, 4> members;
    Quadruple(int a, int b, int c, int d){
        members[0] = a;
        members[1] = b;
        members[2] = c;
        members[3] = d;
    }
    int get_first(){
        return members[0];
    }
    int get_second(){
        return members[1];
    }
    int get_third(){
        return members[2];
    }
    int get_fourth(){
        return members[3];
    } 
};

template <typename T> struct Quadruple<T, T, T, T> {
public:
    std::array<T, 4> members;
    Quadruple(T a, T b, T c, T d){
        members[0] = a;
        members[1] = b;
        members[2] = c;
        members[3] = d;
    }
    T get_first(){
        return members[0];
    }
    T get_second(){
        return members[1];
    }
    T get_third(){
        return members[2];
    }
    T get_fourth(){
        return members[3];
    } 
};