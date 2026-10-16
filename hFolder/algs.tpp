#pragma once

template <typename T, typename Comparator>
void sortBy(Collection<T>& collection, Comparator comp) {
    std::sort(collection.data().begin(), collection.data().end(), comp);
}

template <typename T, typename Predicate>
int countIf(const Collection<T>& collection, Predicate pred) {
    return static_cast<int>(std::count_if(
        collection.data().begin(),
        collection.data().end(),
        pred));
}

template <typename T>
double averageMetric(const Collection<T>& collection) {
    if (collection.size() == 0) return 0.0;
    double sum = 0.0;
    for (const auto& item : collection.data()) sum += item.calculateMetric();
    return sum / collection.size();
}

template <typename T>
double averageMetric(const Collection<std::shared_ptr<T>>& collection) {
    return collection.averageMetric();
}