#pragma once

#include <array>

template <class T, std::size_t MaxSize = 256>
class fixed_vector
{
	using data_t = std::array<T, MaxSize>;
public:
	using iterator = T *;
	using const_iterator = const T*;

public:
	constexpr fixed_vector() noexcept;

	template <class... Ts>
	constexpr void emplace_back(Ts&& ... ts) noexcept;

	constexpr void push_back(const T& t) noexcept;

	constexpr void pop() noexcept;

	constexpr iterator begin() noexcept;
	constexpr const_iterator begin() const noexcept;

	constexpr iterator end() noexcept;
	constexpr const_iterator end() const noexcept;

	constexpr std::size_t size() const noexcept;
	constexpr std::size_t capacity() const noexcept;

	constexpr const T& operator[](const std::size_t i) const noexcept;
	constexpr T& operator[](const std::size_t i) noexcept;

	constexpr T& back() noexcept;
	constexpr const T& back() const noexcept;

	constexpr T& front() noexcept;
	constexpr const T& front() const noexcept;

private:
	data_t data_;
	std::size_t num_used_;
};

template <class T, std::size_t MaxSize>
constexpr fixed_vector<T, MaxSize>::fixed_vector() noexcept
	: data_{}
	, num_used_{0}
{}

template <class T, std::size_t MaxSize>
template <class... Ts>
constexpr void fixed_vector<T, MaxSize>::emplace_back(Ts&& ... ts) noexcept
{
	(this->push_back(std::forward<Ts>(ts)), ...);
}

template <class T, std::size_t MaxSize>
constexpr void fixed_vector<T, MaxSize>::push_back(const T& t) noexcept
{
	//if (std::distance(std::begin(data_), top_it_) < MaxSize)
	data_[num_used_++] = t;
}
template <class T, std::size_t MaxSize>
constexpr void fixed_vector<T, MaxSize>::pop() noexcept
{
	//if (top_it_ != std::begin(data_))
	--num_used_;
}
template <class T, std::size_t MaxSize>
constexpr typename fixed_vector<T, MaxSize>::iterator
	fixed_vector<T, MaxSize>::begin() noexcept
{
	return data_.data();
}
template <class T, std::size_t MaxSize>
constexpr typename fixed_vector<T, MaxSize>::const_iterator
	fixed_vector<T, MaxSize>::begin() const noexcept
{
	return data_.data();
}
template <class T, std::size_t MaxSize>
constexpr typename fixed_vector<T, MaxSize>::iterator
	fixed_vector<T, MaxSize>::end() noexcept
{
	return data_.data() + MaxSize;
}
template <class T, std::size_t MaxSize>
constexpr typename fixed_vector<T, MaxSize>::const_iterator
	fixed_vector<T, MaxSize>::end() const noexcept
{
	return data_.data() + MaxSize;
}
template <class T, std::size_t MaxSize>
constexpr std::size_t fixed_vector<T, MaxSize>::size() const noexcept
{
	return num_used_;
}

template <class T, std::size_t MaxSize>
constexpr std::size_t fixed_vector<T, MaxSize>::capacity() const noexcept
{
	return MaxSize;
}
template <class T, std::size_t MaxSize>
constexpr const T& fixed_vector<T, MaxSize>::operator[](const std::size_t i) const noexcept
{
	return data_[i];
}
template <class T, std::size_t MaxSize>
constexpr T& fixed_vector<T, MaxSize>::operator[](const std::size_t i) noexcept
{
	return data_[i];
}
template <class T, std::size_t MaxSize>
constexpr T& fixed_vector<T, MaxSize>::back() noexcept
{
	return data_[num_used_ - 1];
}
template <class T, std::size_t MaxSize>
constexpr const T& fixed_vector<T, MaxSize>::back() const noexcept
{
	return data_[num_used_ - 1];
}
template <class T, std::size_t MaxSize>
constexpr T& fixed_vector<T, MaxSize>::front() noexcept
{
	return data_[0];
}
template <class T, std::size_t MaxSize>
constexpr const T& fixed_vector<T, MaxSize>::front() const noexcept
{
	return data_[0];
}