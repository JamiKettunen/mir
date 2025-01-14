/*
 * Copyright © 2019 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 or 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIR_SHELL_DECORATION_THREADSAFE_ACCESS_H_
#define MIR_SHELL_DECORATION_THREADSAFE_ACCESS_H_

#include "mir/executor.h"
#include "mir/fatal.h"

#include <memory>
#include <mutex>
#include <optional>

namespace mir
{
namespace shell
{
namespace decoration
{
template<typename T>
class ThreadsafeAccess
    : public std::enable_shared_from_this<ThreadsafeAccess<T>>
{
public:
    ThreadsafeAccess(
        std::shared_ptr<Executor> const& executor)
        : executor{executor}
    {
    }

    ~ThreadsafeAccess()
    {
        if (target)
            fatal_error("ThreadsafeAccess never invalidated");
    }

    void initialize(T* t)
    {
        std::lock_guard lock{mutex};
        if (target)
            fatal_error("ThreadsafeAccess initialized multiple times");
        target = t;
    }

    void spawn(std::function<void(T*)>&& work)
    {
        executor->spawn([self = this->shared_from_this(), work]()
            {
                std::lock_guard lock{self->mutex};
                if (self->target)
                    work(self->target.value());
            });
    }

    void invalidate()
    {
        std::lock_guard lock{mutex};
        target = std::nullopt;
    }

private:
    std::mutex mutex;
    std::optional<T*> target;
    std::shared_ptr<Executor> executor;
};
}
}
}

#endif // MIR_SHELL_DECORATION_THREADSAFE_ACCESS_H_
