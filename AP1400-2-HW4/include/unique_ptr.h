#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr {
public:
    UniquePtr() : _p(nullptr) {}
    UniquePtr(T* p) : _p(p) {}

    UniquePtr(const UniquePtr& up) = delete;
    UniquePtr& operator=(const UniquePtr& up) = delete;

    T* get() const {
        return _p;
    }

    T& operator*() const {
        return *_p;
    }
    T* operator->() const {
        return _p; 
    }

    operator bool() const {
        return _p != nullptr;
    }

    void reset() {
        delete _p;
        _p = nullptr;
    }
    void reset(T* p) {
        delete _p;
        _p = p;
    }

    T* release() {
        auto temp = _p;
        _p = nullptr;
        return temp;
    }

    ~UniquePtr() {
        delete _p;
        _p = nullptr;
    }

private:
    T* _p;
};

template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif //UNIQUE_PTR