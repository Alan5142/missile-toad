#include "missile_toad/core/resource_ptr.hpp"

#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <memory_resource>

TEST_CASE("ResourcePtrInner", "[core]")
{
    using namespace missiletoad::core;

    SECTION("Create a new ResourcePtrInner defaults to nullptr")
    {
        ResourcePtrInner<int> ptr;
        REQUIRE(ptr.get_ref_count() == 0);
    }

    SECTION("Create a new ResourcePtrInner with an item")
    {
        ResourcePtrInner<int> ptr(10);
        REQUIRE(ptr.get_ref_count() == 1);
    }

    SECTION("Create a new ResourcePtrInner from other results in a clone")
    {
        ResourcePtrInner<int> ptr(10);
        ResourcePtrInner<int> ptr2(std::move(ptr));
        REQUIRE(ptr.get_ref_count() == 1); // NOLINT(*-use-after-move)
        REQUIRE(ptr2.get_ref_count() == 1);
    }

    SECTION("Can have an unload callback")
    {
        bool unloaded = false;
        {
            ResourcePtrInner<int> ptr(10);
            ptr.set_unload_callback([&unloaded]() { unloaded = true; });
        }
        REQUIRE(unloaded == true);
    }
}

TEST_CASE("ResourcePtr", "[core]")
{
    using namespace missiletoad::core;

    SECTION("Create a new ResourcePtr defaults to nullptr")
    {
        ResourcePtr<int> ptr;
        REQUIRE(ptr.get() == nullptr);
    }

    SECTION("Cloning increases the ref count")
    {
        ResourcePtr<int> ptr  = ResourcePtr<int>(10);
        auto             ptr2 = ptr.clone();
        REQUIRE(ptr.get_ref_count() == 2);
    }

    SECTION("Cloning a nullptr does nothing")
    {
        ResourcePtr<int> ptr;
        auto             ptr2 = ptr.clone();
        REQUIRE(ptr.get_ref_count() == 0);
    }

    SECTION("Destroying a ResourcePtr decreases the ref count")
    {
        ResourcePtr<int> ptr = ResourcePtr<int>(10);
        {
            auto ptr2 = ptr.clone();
        }
        REQUIRE(ptr.get_ref_count() == 1);
    }

    SECTION("Can get the value of a ResourcePtr")
    {
        ResourcePtr<int> ptr = ResourcePtr<int>(10);
        REQUIRE(*ptr.get() == 10);
    }

    SECTION("Has pointer semantics")
    {
        ResourcePtr<int> ptr  = ResourcePtr<int>(10);
        ResourcePtr<int> ptr2 = ptr.clone();
        REQUIRE(ptr.get_ref_count() == 2);
        REQUIRE(ptr2.get_ref_count() == 2);
    }

    SECTION("Can be moved")
    {
        ResourcePtr<int> ptr  = ResourcePtr<int>(10);
        ResourcePtr<int> ptr2 = std::move(ptr);
        REQUIRE(ptr.get_ref_count() == 0); // NOLINT(*-use-after-move)
        REQUIRE(ptr2.get_ref_count() == 1);
    }

    SECTION("Can be moved into")
    {
        ResourcePtr<int> ptr = ResourcePtr<int>(10);
        ResourcePtr<int> ptr2;
        ptr2 = std::move(ptr);
        REQUIRE(ptr.get_ref_count() == 0); // NOLINT(*-use-after-move)
        REQUIRE(ptr2.get_ref_count() == 1);
    }

    SECTION("Can be constructed from a nullptr")
    {
        ResourcePtr<int> ptr = nullptr;
        REQUIRE(ptr.get_ref_count() == 0);
    }

    SECTION("Can have an unload callback")
    {
        bool unloaded = false;
        {
            ResourcePtr<int> ptr(10);
            ptr.set_unload_callback([&unloaded]() { unloaded = true; });
        }
        REQUIRE(unloaded == true);
    }

    SECTION("Can use custom allocator")
    {
        using Allocator = std::pmr::polymorphic_allocator<ResourcePtrInner<int>>;
        Allocator allocator(std::pmr::new_delete_resource());
        ResourcePtr<int, std::pmr::polymorphic_allocator<ResourcePtrInner<int>>> ptr(10, allocator);
        REQUIRE(ptr.get_ref_count() == 1);
    }

    SECTION("Copy constructor clones")
    {
        ResourcePtr<int> ptr(10);
        ResourcePtr<int> ptr2(ptr); // NOLINT(*-unnecessary-copy-initialization)
        REQUIRE(ptr.get_ref_count() == 2);
        REQUIRE(ptr2.get_ref_count() == 2);
    }

    SECTION("Copy assignment clones")
    {
        ResourcePtr<int> ptr(10);
        ResourcePtr<int> ptr2 = ptr; // NOLINT(*-unnecessary-copy-initialization)
        REQUIRE(ptr.get_ref_count() == 2);
        REQUIRE(ptr2.get_ref_count() == 2);
    }

    SECTION("Move constructor moves")
    {
        ResourcePtr<int> ptr(10);
        ResourcePtr<int> ptr2(std::move(ptr));
        REQUIRE(ptr.get_ref_count() == 0); // NOLINT(*-use-after-move)
        REQUIRE(ptr2.get_ref_count() == 1);
    }

    SECTION("Move assignment moves")
    {
        ResourcePtr<int> ptr(10);
        ResourcePtr<int> ptr2 = std::move(ptr);
        REQUIRE(ptr.get_ref_count() == 0); // NOLINT(*-use-after-move)
        REQUIRE(ptr2.get_ref_count() == 1);
    }
}
