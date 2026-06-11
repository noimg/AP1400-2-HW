#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr {
public:
    SharedPtr() : _p(nullptr), count(nullptr) {}
    SharedPtr(T* p) : _p(p), count(p ? new int(1) : nullptr) {}
    SharedPtr(const SharedPtr& other) : _p(other._p), count(other.count) {
        if (count)
            (*count)++;
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            reset();
            _p = other._p;
            count = other.count;
            if (count) {
                (*count)++;
            }
        }
        return *this;
    }

    int use_count() {
        return count ? *count : 0;
    }

    T* get() const {
        return _p;
    }

    T& operator*() const {
        return *_p;
    }

    T* operator->() const {
        return _p;
    }

    void reset() {
        if (count) {
            (*count)--;
            if (*count == 0) {
                delete _p;
                delete count;
            }
        }
        _p = nullptr;
        count = nullptr;
    }
    void reset(T* p) {
        if (_p != p) {
            reset();
            _p = p;
            count = p ? new int(1) : nullptr;
        }
    }

    operator bool() const {
        return _p != nullptr;
    }

    ~SharedPtr() {
        if (count) {
            (*count)--;
            if (*count == 0) {
                delete _p;
                delete count;
            }
        }
        _p = nullptr;
        count = nullptr;
    }

private:
    T* _p;
    int* count;
};

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif //SHARED_PTR