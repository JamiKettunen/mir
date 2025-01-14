/*
 * Copyright © 2015 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "library_example.h"
#include "mir/shared_library.h"
#include "mir_test_framework/executable_path.h"

#include <gtest/gtest.h>

namespace
{
mir::UniqueModulePtr<std::string> function_in_executable()
{
    return mir::make_module_ptr<std::string>("foo");
}
}

TEST(ModuleDeleter, module_ptr_may_outlive_local_library)
{
    mir::UniqueModulePtr<SomeInterface> module_object;
    {
        mir::SharedLibrary lib(mir_test_framework::test_data_path() + "/shared-libraries/example.so");
        auto function = lib.load_function<ModuleFunction>("module_create_instance");
        module_object = function();
    }
    module_object->can_be_executed();
}

TEST(ModuleDeleter, shared_ptr_can_keep_library_alive)
{
    std::shared_ptr<SomeInterface> module_object;
    {
        mir::SharedLibrary lib(mir_test_framework::test_data_path() + "/shared-libraries/example.so");
        auto function = lib.load_function<ModuleFunction>("module_create_instance");
        module_object = function();
    }
    module_object->can_be_executed();
}

TEST(ModuleDeleter, module_ptr_can_work_in_executables)
{
    EXPECT_NO_THROW(function_in_executable());
}
