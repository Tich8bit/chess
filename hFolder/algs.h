#pragma once

#include "collection.h"
#include <algorithm>
#include <numeric>

template <typename T, typename Comparator>
void sortBy(Collection<T>& collection, Comparator comp);

template <typename T, typename Predicate>
int countIf(const Collection<T>& collection, Predicate pred);

template <typename T>
double averageMetric(const Collection<T>& collection);

template <typename T>
double averageMetric(const Collection<std::shared_ptr<T>>& collection);

#include "algs.tpp"