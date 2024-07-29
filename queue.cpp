#include <deque>

template <typename T, typename Container = std::deque<T>>
class queue {
public:
    using container_type = Container;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

protected:
    Container c;

public:
    // Constructors
    queue() : c() {}
    explicit queue(const Container& cont) : c(cont) {}
    explicit queue(Container&& cont) : c(std::move(cont)) {}

    // Destructor
    ~queue() = default;

    // Assignment operator
    queue& operator=(const queue& other) {
        c = other.c;
        return *this;
    }

    queue& operator=(queue&& other) noexcept {
        c = std::move(other.c);
        return *this;
    }

    // Element access
    reference front() {
        return c.front();
    }

    const_reference front() const {
        return c.front();
    }

    reference back() {
        return c.back();
    }

    const_reference back() const {
        return c.back();
    }

    // Capacity
    bool empty() const noexcept {
        return c.empty();
    }

    size_type size() const noexcept {
        return c.size();
    }

    // Modifiers
    void push(const value_type& value) {
        c.push_back(value);
    }

    void push(value_type&& value) {
        c.push_back(std::move(value));
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        c.emplace_back(std::forward<Args>(args)...);
    }

    void pop() {
        c.pop_front();
    }

    void swap(queue& other) noexcept(std::is_nothrow_swappable_v<Container>) {
        using std::swap;
        swap(c, other.c);
    }

    template <typename InputIt>
    void push_range(InputIt first, InputIt last) {
        for (; first != last; ++first) {
            c.push_back(*first);
        }
    }

    // Non-member functions
    friend bool operator==(const queue& lhs, const queue& rhs) {
        return lhs.c == rhs.c;
    }

    friend bool operator!=(const queue& lhs, const queue& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const queue& lhs, const queue& rhs) {
        return lhs.c < rhs.c;
    }

    friend bool operator<=(const queue& lhs, const queue& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const queue& lhs, const queue& rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const queue& lhs, const queue& rhs) {
        return !(lhs < rhs);
    }

    friend auto operator<=>(const queue& lhs, const queue& rhs) {
        return lhs.c <=> rhs.c;
    }

    friend void swap(queue& lhs, queue& rhs) noexcept(noexcept(lhs.swap(rhs))) {
        lhs.swap(rhs);
    }
};
