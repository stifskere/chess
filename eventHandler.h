#ifndef CHESS_EVENTHANDLER_H
#define CHESS_EVENTHANDLER_H

#include <vector>
#include <functional>

template <typename RetType>
class eventInvoke{
    public:
    std::vector<RetType> returns;
    std::exception exception;
    bool success;

    void apply(const std::function<void(RetType)> &func){
        for (RetType ret : returns) func(ret);
    }
};

template<>
class eventInvoke<void>{
public:
    std::exception exception;
    bool success;
};

template <typename Func>
class eventHandler;

template <typename RetType, typename... Args>
class eventHandler<RetType(Args...)> {
    typedef std::function<RetType(Args...)> function;
    std::vector<function> functions;
public:
    eventHandler()= default;

    void subscribe(const function &func){
        functions.push_back(func);
    }

    eventInvoke<RetType> invoke(Args... args){
        if constexpr(!std::is_void_v<RetType>) {
            std::vector<RetType> returns;
            try {
                for (const function &func: functions) returns.push_back(func(args...));
            } catch (std::exception &e) {
                return {{}, e, false};
            }
            return {returns, {}, true};
        }else {

            try {
                for (const function &func: functions) func(args...);
            } catch (std::exception &e) {
                return {e, false};
            }
            return {{}, true};
        }
    }

    eventHandler &operator+=(const function &func){
        subscribe(func);
        return *this;
    }

    eventInvoke<RetType> operator()(Args... args){
        return invoke(args...);
    }
};

#endif
