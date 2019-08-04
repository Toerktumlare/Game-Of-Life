#pragma once

#include <functional>

template<typename T>
class Vector2 {

private:
    std::vector<std::vector<T>> data;
    
using size_type = typename decltype(data)::size_type;
    
public:
    Vector2(size_t height, size_t width, T t);
    Vector2(size_t height, size_t width, std::function<T(size_type, size_type, size_t, size_t)> &func);
    
    void forEach(const std::function<void(T, int, int)> &func);
    
    T& operator[](size_type x);
};

template<typename T>
Vector2<T>::Vector2(size_t height, size_t width, T t)
{
    data.reserve(height);
    for (size_type i = 0; i < height; ++i) {
        std::vector<T> row;
        row.reserve(width);
        data.push_back(row);
        for (int j = 0; j < width; ++j) {
            data[i].push_back(t);
        }
    }
}

template<typename T>
Vector2<T>::Vector2(size_t height, size_t width, std::function<T(size_type, size_type, size_t, size_t)> &func)
{
    data.reserve(height);
    for (size_type i = 0; i < height; ++i) {
        std::vector<T> row;
        row.reserve(width);
        data.push_back(row);
        for (int j = 0; j < width; ++j) {
            data[i].push_back(func(i, j, height, width));
        }
    }
}

template<typename T>
void Vector2<T>::forEach(const std::function<void(T, int, int)> &func) {
    for (size_type i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            func(data[i][j], i, j);
        }
    }
}

template<typename T>
T& Vector2<T>::operator[](size_type x)
{
    return data[x];
}



