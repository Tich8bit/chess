#pragma once

#include <vector>
#include <memory>
#include <iostream>

template <typename T>
class Collection {
public:
    void add(const T& item);
    bool removeAt(int index);

    template <typename Predicate>
    int removeIf(Predicate pred);

    T* get(int index);
    const T* get(int index) const;

    template <typename Predicate>
    T* find(Predicate pred);

    template <typename Predicate>
    const T* find(Predicate pred) const;

    int size() const;
    bool isEmpty() const;
    void clear();
    void print(std::ostream& os) const;

    std::vector<T>& data();
    const std::vector<T>& data() const;

private:
    std::vector<T> _items;
};

template <typename T>
class Collection<std::shared_ptr<T>> {
public:
    void add(const std::shared_ptr<T>& item);
    bool removeAt(int index);

    template <typename Predicate>
    int removeIf(Predicate pred);

    std::shared_ptr<T> getShared(int index) const;
    T* get(int index) const;

    template <typename Predicate>
    std::shared_ptr<T> findShared(Predicate pred) const;

    template <typename Predicate>
    T* find(Predicate pred) const;

    int size() const;
    bool isEmpty() const;
    void clear();
    void print(std::ostream& os) const;
    double averageMetric() const;

    std::vector<std::shared_ptr<T>>& data();
    const std::vector<std::shared_ptr<T>>& data() const;

private:
    std::vector<std::shared_ptr<T>> _items;
};

#include "collection.tpp"