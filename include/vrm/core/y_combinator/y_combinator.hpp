// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <functional>
#include <type_traits>
#include <utility>
#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros/fwd.hpp>
#include <vrm/core/utility_macros/impl/noexcept.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TF>
        class y_combinator_result
        {
        private:
            TF _f;

        public:
            template <typename T>
            VRM_CORE_ALWAYS_INLINE // .
                constexpr explicit y_combinator_result(T&& f) noexcept
                : _f(FWD(f))
            {
            }

            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE // .
                constexpr decltype(auto)
                operator()(Ts&&... xs)                     // .
                VRM_CORE_IMPL_NOEXCEPT_AND_RETURN_BODY_VA( // .
                    _f(std::ref(*this), FWD(xs)...)        // .
                    )
        };
    }

    template <typename TF>
    VRM_CORE_ALWAYS_INLINE constexpr auto y_combinator(TF && f) noexcept
    {
        return impl::y_combinator_result<std::decay_t<TF>>(FWD(f));
    }
}
VRM_CORE_NAMESPACE_END
