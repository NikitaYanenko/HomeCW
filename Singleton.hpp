#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <memory>
#include <utility>

template<class T>
class Singleton {
public:
    template<typename... Args>
    static T* getInstance(Args&&... args) {
        if (!instance) {
            instance = std::make_unique<T>(std::forward<Args>(args)...);
        }

        return instance.get();
    }

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

protected:
    Singleton() = default;
    ~Singleton() = default;
private:
    static inline std::unique_ptr<T> instance{};
};
#endif // !SINGLETON_HPP