//
// Created by Antonin Jean on 19/11/2023.
//
#pragma once
#include <vector>
#include <exception>
#include <string>

template<typename T>
class BitMap {
public:
    explicit BitMap(size_t width, size_t height, T defaultValue) : m_width(width), m_height(height), m_data(std::vector<std::vector<T> >(height))
    {
        for (int i = 0; i < m_height; i++) {
            m_data[i] = std::vector<T>(width, defaultValue);
        }
    }

    unsigned int getHeight() {
        return m_height;
    }

    unsigned int getWidth() {
        return m_width;
    }

    unsigned int getSize() {
        return m_height * m_width;
    }

    friend bool operator==(const BitMap &self, const BitMap &other);

    friend bool operator!=(const BitMap &self, const BitMap &other);

    friend BitMap<T> operator+(const BitMap& self, T scalar);

    friend BitMap<T> operator+(BitMap<T> self, BitMap<T> other);


    T& operator[](size_t index);

    T& operator[](std::pair<size_t, size_t> indexs);

    const T& operator[](size_t index) const;

    const T& operator[](std::pair<size_t, size_t> indexs) const;
private:
    const size_t m_height;
    const size_t m_width;
    std::vector<std::vector<T> > m_data;

    T& _get(const size_t col, const size_t line);

    T _put(const size_t& col, const size_t& line, T value);
};





template<typename T>
T& BitMap<T>::_get(const size_t col, const size_t line) {
        if (col >= this->m_width || line >= this->m_height) {
            throw std::invalid_argument("Invalid index (" + std::to_string(col) + ", " + std::to_string(line) +
                                        "), in Bitmap of size (" + std::to_string(m_width) + ", " + std::to_string(m_height) + ").");
        }
        return m_data[line][col];
    }

template<typename T>
T BitMap<T>::_put(const size_t& col, const size_t& line, T value) {
    if (col >= this->m_width || line >= this->m_height) {
        throw std::invalid_argument("Invalid index (" + std::to_string(col) + ", " + std::to_string(line) +
                                    "), in Bitmap of size (" + std::to_string(m_width) + ", " + std::to_string(m_height) + ").");
    }

    T oldValue = _get(col, line);
    m_data[line][col] = value;
    return oldValue;
}

template<typename T>
bool operator!=(const BitMap<T> &self, const BitMap<T> &other) {
    return other.m_data != self.m_data;
}

template<typename T>
bool operator==(const BitMap<T> &self, const BitMap<T> &other) {
    return self.m_data == other.m_data;
}


template<typename T>
T& BitMap<T>::operator[](const std::pair<size_t, size_t> indexs) {
    return _get(indexs.first, indexs.second);
}

template<typename T>
T& BitMap<T>::operator[](const size_t index) {
    size_t col = index % this->m_width;
    size_t line = index / this->m_width;
    return _get(col, line);
}

template<typename T>
const T& BitMap<T>::operator[](const std::pair<size_t, size_t> indexs) const {
    return _get(indexs.first, indexs.second);
}

template<typename T>
const T& BitMap<T>::operator[](const size_t index) const {
    size_t col = index % this->m_width;
    size_t line = index / this->m_width;
    return _get(col, line);
}


template<typename T>
BitMap<T> operator+(const BitMap<T> self, const BitMap<T> other) {
    BitMap<T> result = BitMap<T>(self->m_data);
    if (self.m_height != other.m_height || self.m_width != other.m_width) {
        throw std::invalid_argument("Invalid operations, the bitmaps must have identical sizes");
    }
    return result;
}

template<typename T>
BitMap<T> operator+(const BitMap<T> &self, T scalar) {
    BitMap<T> result = BitMap<T>(self->m_data);
    for (const std::vector<T> &subList: result.m_data) {
        for (const T &item: subList) {
            item += scalar;
        }
    }
    return result;
}