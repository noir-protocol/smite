#pragma once
#include <eo/core.h>

#include <fmt/format.h>
#include <map>

namespace fmt {

template<typename... T>
void println(format_string<T...> fmt, T&&... args) {
  fmt::print(fmt, std::forward<T>(args)...);
  fmt::print("\n");
}

template<typename T>
void println(T&& arg) {
  fmt::print("{}", arg);
  fmt::print("\n");
}

template<typename... T>
void fprintln(std::FILE* f, format_string<T...> fmt, T&&... args) {
  fmt::print(f, fmt, std::forward<T>(args)...);
  fmt::print(f, "\n");
}

template<typename T>
void fprintln(std::FILE* f, T&& arg) {
  fmt::print(f, "{}", arg);
  fmt::print(f, "\n");
}

template<typename K, typename V>
struct formatter<std::pair<K, V>> {
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template<typename FormatContext>
  auto format(const std::pair<K, V>& p, FormatContext& ctx) {
    return format_to(ctx.out(), "{}:{}", p.first, p.second);
  }
};

template<typename K, typename V>
struct formatter<std::map<K, V>> {
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template<typename FormatContext>
  auto format(const std::map<K, V>& p, FormatContext& ctx) {
    return format_to(ctx.out(), "map[{}]", join(p, " "));
  }
};

} // namespace fmt

namespace eo {

namespace fmt = ::fmt;

} // namespace eo
