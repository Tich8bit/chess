#pragma once
#include <vector>
#include <memory>
#include <iostream>

template <typename T>
class Collection {
public:
    Collection() = default;
    const std::vector<std::shared_ptr<T>>& getItems() const;
    void add(const std::shared_ptr<T>& item);
    std::shared_ptr<T> get(size_t index) const;
    template <typename Predicate> std::shared_ptr<T> find(Predicate pred) const;
    template <typename Predicate> size_t removeIf(Predicate pred);
    size_t size() const;
    bool empty() const;
    void print(std::ostream& os = std::cout) const;
    auto begin() const;
    auto end() const;
private:
    std::vector<std::shared_ptr<T>> _items;
};

#include "collection.tpp"