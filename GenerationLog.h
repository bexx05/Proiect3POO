
#ifndef UNTITLED_GENERATIONLOG_H
#define UNTITLED_GENERATIONLOG_H
#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include <ostream>
#include <stdexcept>

template<typename T>
class GenerationLog {
    std::vector<T> log_;
    std::size_t    maxSize_;

public:
    explicit GenerationLog(std::size_t maxSize = 1000)
        : maxSize_(maxSize) {}

    // funcție membră
    void record(const T& value) {
        if (log_.size() >= maxSize_)
            log_.erase(log_.begin());   // ring-buffer
        log_.push_back(value);
    }

    T latest() const {
        if (log_.empty()) throw std::runtime_error("Log is empty");
        return log_.back();
    }

    T minValue() const { return *std::min_element(log_.begin(), log_.end()); }
    T maxValue() const { return *std::max_element(log_.begin(), log_.end()); }

    template<typename Pred>
    std::vector<T> filter(Pred pred) const {
        std::vector<T> result;
        std::copy_if(log_.begin(), log_.end(),
                     std::back_inserter(result), pred);
        return result;
    }

    std::size_t size() const { return log_.size(); }

    //  funcție liberă template
    friend std::ostream& operator<<(std::ostream& os,
                                    const GenerationLog<T>& gl) {
        os << "[GenerationLog] entries=" << gl.log_.size();
        if (!gl.log_.empty())
            os << " min=" << gl.minValue()
               << " max=" << gl.maxValue()
               << " latest=" << gl.latest();
        return os;
    }
};

//  funcție liberă/normală template
template<typename T>
double average(const GenerationLog<T>& gl) {
    if (gl.size() == 0) return 0.0;
    auto all = gl.filter([](const T&){ return true; });
    return static_cast<double>(
               std::accumulate(all.begin(), all.end(), T{}))
           / static_cast<double>(all.size());
}

template<>
class GenerationLog<std::string> {
    std::vector<std::string> log_;
    std::size_t maxSize_;

public:
    explicit GenerationLog(std::size_t maxSize = 1000)
        : maxSize_(maxSize) {}

    void record(const std::string& value) {
        if (log_.size() >= maxSize_)
            log_.erase(log_.begin());
        log_.push_back(value);
    }

    std::string latest() const { return log_.back(); }
    std::size_t size() const { return log_.size(); }

    template<typename Pred>
    std::vector<std::string> filter(Pred pred) const {
        std::vector<std::string> result;
        std::copy_if(log_.begin(), log_.end(),
                     std::back_inserter(result), pred);
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const GenerationLog<std::string>& gl) {
        os << "[GenerationLog<string>]\n";
        for (const auto& s : gl.log_)
            os << " - " << s << "\n";
        return os;
    }
};
#endif //UNTITLED_GENERATIONLOG_H