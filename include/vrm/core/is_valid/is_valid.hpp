// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>

#include <type_traits>

namespace vrm::core::impl
{
    struct is_valid_dummy
    {
    };

    template <typename T>
    class is_valid_wrapper
    {
    private:
        template <typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr auto test(is_valid_dummy) noexcept
            -> decltype(
                std::declval<T>()(std::declval<Ts>()...), std::true_type{})
        {
            return std::true_type{};
        }

        template <typename...>
        VRM_CORE_ALWAYS_INLINE constexpr auto test(...) noexcept
        {
            return std::false_type{};
        }

    public:
        template <typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr auto operator()(Ts&&... xs) noexcept
        {
            return test<decltype(xs)...>(is_valid_dummy{});
        }
    };
} // namespace vrm::core::impl

namespace vrm::core
{
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto is_valid(T&&)
    {
        return impl::is_valid_wrapper<T>{};
    }
} // namespace vrm::core
