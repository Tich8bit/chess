#pragma once

#include <algorithm>

template <typename T>
void Collection<T>::add(const T& item) { _items.push_back(item); }

template <typename T>
bool Collection<T>::removeAt(int index) {
    if (index < 0 || index >= static_cast<int>(_items.size())) {
        std::cerr << "[Ошибка] Индекс " << index << " вне диапазона.\n";
        return false;
    }
    _items.erase(_items.begin() + index);
    return true;
}

template <typename T>
template <typename Predicate>
int Collection<T>::removeIf(Predicate pred) {
    int before = static_cast<int>(_items.size());
    _items.erase(std::remove_if(_items.begin(), _items.end(), pred), _items.end());
    return before - static_cast<int>(_items.size());
}

template <typename T>
T* Collection<T>::get(int index) {
    if (index < 0 || index >= static_cast<int>(_items.size())) return nullptr;
    return &_items[index];
}

template <typename T>
const T* Collection<T>::get(int index) const {
    if (index < 0 || index >= static_cast<int>(_items.size())) return nullptr;
    return &_items[index];
}

template <typename T>
template <typename Predicate>
T* Collection<T>::find(Predicate pred) {
    for (auto& item : _items) if (pred(item)) return &item;
    return nullptr;
}

template <typename T>
template <typename Predicate>
const T* Collection<T>::find(Predicate pred) const {
    for (const auto& item : _items) if (pred(item)) return &item;
    return nullptr;
}

template <typename T>
int Collection<T>::size() const { return static_cast<int>(_items.size()); }

template <typename T>
bool Collection<T>::isEmpty() const { return _items.empty(); }

template <typename T>
void Collection<T>::clear() { _items.clear(); }

template <typename T>
void Collection<T>::print(std::ostream& os) const {
    for (const auto& item : _items) os << item << "\n";
}

template <typename T>
std::vector<T>& Collection<T>::data() { return _items; }

template <typename T>
const std::vector<T>& Collection<T>::data() const { return _items; }

template <typename T>
void Collection<std::shared_ptr<T>>::add(const std::shared_ptr<T>& item) {
    if (!item) {
        std::cerr << "[Ошибка] Пустой указатель.\n";
        return;
    }
    _items.push_back(item);
}

template <typename T>
bool Collection<std::shared_ptr<T>>::removeAt(int index) {
    if (index < 0 || index >= static_cast<int>(_items.size())) {
        std::cerr << "[Ошибка] Индекс " << index << " вне диапазона.\n";
        return false;
    }
    _items.erase(_items.begin() + index);
    return true;
}

template <typename T>
template <typename Predicate>
int Collection<std::shared_ptr<T>>::removeIf(Predicate pred) {
    int before = static_cast<int>(_items.size());
    _items.erase(std::remove_if(_items.begin(), _items.end(), pred), _items.end());
    return before - static_cast<int>(_items.size());
}

template <typename T>
std::shared_ptr<T> Collection<std::shared_ptr<T>>::getShared(int index) const {
    if (index < 0 || index >= static_cast<int>(_items.size())) return nullptr;
    return _items[index];
}

template <typename T>
T* Collection<std::shared_ptr<T>>::get(int index) const {
    if (index < 0 || index >= static_cast<int>(_items.size())) return nullptr;
    return _items[index].get();
}

template <typename T>
template <typename Predicate>
std::shared_ptr<T> Collection<std::shared_ptr<T>>::findShared(Predicate pred) const {
    for (const auto& item : _items) if (item && pred(*item)) return item;
    return nullptr;
}

template <typename T>
template <typename Predicate>
T* Collection<std::shared_ptr<T>>::find(Predicate pred) const {
    for (const auto& item : _items) if (item && pred(*item)) return item.get();
    return nullptr;
}

template <typename T>
int Collection<std::shared_ptr<T>>::size() const { return static_cast<int>(_items.size()); }

template <typename T>
bool Collection<std::shared_ptr<T>>::isEmpty() const { return _items.empty(); }

template <typename T>
void Collection<std::shared_ptr<T>>::clear() { _items.clear(); }

template <typename T>
void Collection<std::shared_ptr<T>>::print(std::ostream& os) const {
    for (const auto& item : _items) if (item) os << *item << "\n";
}

template <typename T>
double Collection<std::shared_ptr<T>>::averageMetric() const {
    if (_items.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& item : _items) if (item) sum += item->calculateMetric();
    return sum / _items.size();
}

template <typename T>
std::vector<std::shared_ptr<T>>& Collection<std::shared_ptr<T>>::data() {
    return _items;
}

template <typename T>
const std::vector<std::shared_ptr<T>>& Collection<std::shared_ptr<T>>::data() const {
    return _items;
}