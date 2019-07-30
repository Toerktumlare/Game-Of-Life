#pragma once

#import <vector>
#import <functional>
#import <iostream>

template<typename T>
class Grid {
private:
    std::vector<std::vector<T>> data;
    
public:
    void fill(int x, int y, const std::function<T(int, int, int, int)> &func);
    std::size_t sizeX();
    std::size_t sizeY(int x);
    void forEach(const std::function<void(T, int, int)> &func);
    T get(int x, int y);
    void set(int x, int y, T value);
};

template<typename T>
void Grid<T>::fill(int x, int y, const std::function<T(int, int, int, int)> &func) {
    data.reserve(x);
    for (int i = 0; i < x; i++) {
        std::vector<T> v;
        v.reserve(y);
        data.push_back(v);
        std::cout << y << std::endl;
        for (int j = 0; j < y; j++) {
            T value = func(i, j, data.size(), y);
            this->data.at(i).push_back(value);
        }
    }
}

template<typename T>
std::size_t Grid<T>::sizeX() {
    return data.size();
}

template<typename T>
std::size_t Grid<T>::sizeY(int x) {
    return data.at(x).size();
}

template<typename T>
void Grid<T>::forEach(const std::function<void(T, int, int)> &func) {
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data.at(i).size(); j++) {
            func(data.at(i).at(j), i, j);
        }
    }
}

template<typename T>
T Grid<T>::get(int x, int y) {
    return data.at(x).at(y);
}

template<typename T>
void Grid<T>::set(int x, int y, T value) {
    data.at(x).at(y) = value;
}
