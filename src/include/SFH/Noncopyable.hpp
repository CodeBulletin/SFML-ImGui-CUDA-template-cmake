#ifndef SFH_NONCOPYABLE_HPP
#define SFH_NONCOPYABLE_HPP

namespace sfh {
    class Noncopyable {
    public:
        Noncopyable() = default;
        Noncopyable(const Noncopyable&) = delete;
        Noncopyable& operator=(const Noncopyable&) = delete;
    };
}

#endif // SFH_NONCOPYABLE_HPP