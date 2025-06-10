#ifndef SERVER_HPP
#define SERVER_HPP

struct Server {
    int id;
    int load;
    int performance;

    double effectiveLoad() const {
        return static_cast<double>(load) / performance;
    }

    bool operator<(const Server& other) const {
        if (abs(effectiveLoad() - other.effectiveLoad()) < 1e-9) {
            return id < other.id;
        }

        return effectiveLoad() < other.effectiveLoad();
    }
};

#endif // SERVER_HPP