#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include <optional>

template <typename T>
class Pool {
protected:
	std::vector<T> data;

public:
	void add(const T& el);
	void remove(const std::function<bool(const T&)>& predicate);
	std::vector<T> filter(const std::function<bool(const T&)>& predicate) const;
	std::optional<T> findFirst(const std::function<bool(const T&)>& predicate) const;

	size_t size() const;
	bool isEmpty() const;
};

template<typename T>
void Pool<T>::add(const T& el) {
	data.push_back(el);
}

template<typename T>
void Pool<T>::remove(const std::function<bool(const T&)>& predicate) {
	std::erase_if(data, predicate);
}

template<typename T>
std::vector<T> Pool<T>::filter(const std::function<bool(const T&)>& predicate) const {
	std::vector<T> res;

	for (const auto& x : data) {
		if (predicate(x)) {
			res.push_back(x);
		}
	}

	return res;
}

template<typename T>
std::optional<T> Pool<T>::findFirst(const std::function<bool(const T&)>& predicate) const {
	auto it = std::find_if(data.begin(), data.end(), predicate);

	if (it != data.end()) {
		return *it;
	}

	return std::nullopt;
}

template<typename T>
size_t Pool<T>::size() const {
	return data.size();
}

template<typename T>
bool Pool<T>::isEmpty() const {
	return data.empty();
}
