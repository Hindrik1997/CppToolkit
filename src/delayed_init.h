//
// Created by hindrik on 11-8-18.
//

#ifndef CPPTOOLKIT_DELAYED_INIT_H
#define CPPTOOLKIT_DELAYED_INIT_H

#include <utility>

template<typename T>
class delayed_init final {
private:
    alignas(T) char object[sizeof(T)] = {};
public:
    delayed_init();
    ~delayed_init();

    explicit delayed_init(const T& rhs);
    explicit delayed_init(T&& rhs);

    template<typename ...Args>
    explicit delayed_init(Args&&... args);

    delayed_init(const delayed_init& rhs);
    delayed_init(delayed_init&& rhs) noexcept;

    delayed_init& operator=(const delayed_init& rhs);
    delayed_init& operator=(delayed_init&& rhs) noexcept;
public:
    const T*operator->() const;
    T* operator->();

    operator const T&() const;
    operator T&();

    const T*operator &() const;
    T* operator &();
private:
    T* self();
};

template<typename T>
delayed_init<T>::delayed_init() : object() {
}

template<typename T>
delayed_init<T>::~delayed_init() {
    self()->~T();
}

template<typename T>
delayed_init<T>::delayed_init(T&& rhs) {
    new (self()) T(std::forward<T>(rhs));
}

template<typename T>
delayed_init<T>::delayed_init(const T& rhs) {
    new (self()) T(std::forward<T>(rhs));
}

template<typename T>
template<typename... Args>
delayed_init<T>::delayed_init(Args &&... args) {
    new (self()) T(std::forward<Args>(args)...);
}

template<typename T>
T* delayed_init<T>::self() {
    auto t = reinterpret_cast<T*>(&object);
    return t;
}

template<typename T>
const T *delayed_init<T>::operator->() const {
    return self();
}

template<typename T>
T *delayed_init<T>::operator->() {
    return self();
}

template<typename T>
delayed_init<T>::operator const T& () const {
    return *self();
}

template<typename T>
const T *delayed_init<T>::operator&() const {
    return self();
}

template<typename T>
T *delayed_init<T>::operator&() {
    return self();
}

template<typename T>
delayed_init<T>::delayed_init(const delayed_init &rhs) {
    new (self()) T(std::forward<T>(rhs));
}

template<typename T>
delayed_init<T>::delayed_init(delayed_init &&rhs) noexcept {
    new (self()) T(std::forward<T>(rhs));
}

template<typename T>
delayed_init<T>& delayed_init<T>::operator=(const delayed_init &rhs) {
    new (self()) T(std::forward<T>(rhs));
    return *this;
}

template<typename T>
delayed_init<T>& delayed_init<T>::operator=(delayed_init &&rhs) noexcept {
    new (self()) T(std::forward<T>(rhs));
    return *this;
}

template<typename T>
delayed_init<T>::operator T&() {
    return *self();
}

template<typename T, typename ...Args>
delayed_init<T> make_delayed(Args &&...args) {
    return delayed_init<T>(std::forward<Args>(args)...);
}

template<typename T>
using LazyInit = delayed_init<T>;

#endif //CPPTOOLKIT_DELAYED_INIT_H
