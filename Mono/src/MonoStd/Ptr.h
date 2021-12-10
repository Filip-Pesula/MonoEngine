#pragma once
#include <concepts>

namespace mono {
	template<std::copy_constructible T>
	class Ptr
	{
		T* value;


	public:
		template<typename... _ConstTypes>
		Ptr(_ConstTypes... vals) {
			value = new T(vals...);
		}

		Ptr(T val) {
			value = new T(val);
		}

		Ptr& operator = (Ptr&& other) const {
			value = other.value;
			other.value = nullptr;
		}
		Ptr(Ptr&& other) {
			value = other.value;
			other.value = nullptr;
		}
		_NODISCARD T* get() {
			return value;
		}
		Ptr(const Ptr&) = delete;
		Ptr& operator = (const Ptr&) = delete;

		_NODISCARD T* operator->() const noexcept {
			return value;
		}

	};

	class WPtr {
		WPtr();

	};
}

