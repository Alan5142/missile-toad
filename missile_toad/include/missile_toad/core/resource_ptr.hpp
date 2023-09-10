#pragma once

#include "common.hpp"

#include <atomic>
#include <functional>
#include <type_traits>

// NOLINTBEGIN(clang-analyzer-cplusplus.NewDelete)
namespace missiletoad::core
{
    template <class T>
    class ResourcePtrInner
    {
        using type = std::remove_extent_t<T>;

    private:
        type                  item;
        std::function<void()> unload_callback;
        std::atomic_size_t    ref_count;

    public:
        /**
         * Create a new ResourcePtrInner with a ref count of 0.
         */
        ResourcePtrInner() noexcept : item(), ref_count(0), unload_callback(nullptr)
        {
        }

        ResourcePtrInner(T &&item) : item(std::move(item)), ref_count(1), unload_callback(nullptr)
        {
        }

        ResourcePtrInner(const ResourcePtrInner &)            = delete;
        ResourcePtrInner &operator=(const ResourcePtrInner &) = delete;

        ResourcePtrInner(ResourcePtrInner &&other) noexcept
        {
            this->item            = std::move(other.item);
            this->ref_count       = other.ref_count.load();
            this->unload_callback = std::move(other.unload_callback);
        }

        ResourcePtrInner &operator=(ResourcePtrInner &&other) noexcept
        {
            this->item            = std::move(other.item);
            this->ref_count       = other.ref_count.load();
            this->unload_callback = std::move(other.unload_callback);
            return *this;
        }

        ~ResourcePtrInner()
        {
            if (unload_callback)
            {
                unload_callback();
            }
        }

        void add_ref()
        {
            ++this->ref_count;
        }

        void remove_ref()
        {
            ref_count--;
        }

        T &get()
        {
            return item;
        }

        const T &get() const
        {
            return item;
        }

        size_t get_ref_count() const
        {
            return ref_count;
        }

        void set_unload_callback(std::function<void()> callback)
        {
            this->unload_callback = callback;
        }
    };

    /**
     * ResourcePtr is a smart pointer that manages resources.
     * It is similar to std::shared_ptr, but it is more specialized as it allows manual loading and unloading of
     * resources.
     * @tparam T
     */
    template <class T, class Alloc = std::allocator<ResourcePtrInner<T>>>
    class ResourcePtr
    {
    private:
        ResourcePtrInner<T> *inner;
        Alloc                allocator;

    public:
        /**
         * Create a new ResourcePtr with a ref count of 0.
         */
        ResourcePtr() noexcept : inner(nullptr)
        {
        }

        ResourcePtr(std::nullptr_t) noexcept : inner(nullptr) // NOLINT(*-explicit-constructor)
        {
        }

        explicit ResourcePtr(T &&item) : inner(nullptr)
        {
            this->inner = this->allocator.allocate(1);
            std::construct_at(this->inner, std::move(item));
        }

        explicit ResourcePtr(const T &item) : inner(nullptr)
        {
            this->inner = this->allocator.allocate(1);
            std::construct_at(this->inner, item);
        }

        explicit ResourcePtr(Alloc alloc) noexcept : inner(nullptr), allocator(alloc)
        {
        }

        ResourcePtr(T &&item, Alloc alloc) : inner(nullptr), allocator(alloc)
        {
            this->inner = this->allocator.allocate(1);
            std::construct_at(this->inner, std::move(item));
        }

        ResourcePtr &operator=(const ResourcePtr &other)
        {
            if (&other == this)
            {
                return *this;
            }

            if (this->inner)
            {
                this->reset_impl();
            }
            this->inner = other.inner;
            if (this->inner)
            {
                this->inner->add_ref();
            }
            this->allocator = other.allocator;
            return *this;
        }

        ResourcePtr(const ResourcePtr &other)
        {
            this->inner = other.inner;
            if (this->inner)
            {
                this->inner->add_ref();
            }
        }

        /**
         * Moves the ResourcePtr from other to this.
         * @param other The ResourcePtr to move from.
         * @return A reference to this.
         */
        ResourcePtr &operator=(ResourcePtr &&other) noexcept
        {
            if (&other == this)
            {
                return *this;
            }
            if (this->inner)
            {
                this->reset_impl();
            }
            this->inner = other.inner;
            other.inner = nullptr;
            return *this;
        }

        /**
         * Moves the ResourcePtr from other to this.
         * @param other
         */
        ResourcePtr(ResourcePtr &&other) noexcept : inner(other.inner)
        {
            other.inner = nullptr;
        }

        /**
         * Load the resource.
         */
        ~ResourcePtr()
        {
            if (this->inner)
            {
                this->reset_impl();
            }
        }

        T &operator*()
        {
            return this->inner->get();
        }

        const T &operator*() const
        {
            return this->inner->get();
        }

        T *operator->()
        {
            return &this->inner->get();
        }

        /**
         * Get a const pointer to the resource.
         * @return
         */
        const T *operator->() const
        {
            return &this->inner->get();
        }

        /**
         * Reset the ResourcePtr, freeing the resource if it is not used anymore.
         */
        void reset()
        {
            if (this->inner)
            {
                this->reset_impl();
            }
        }

        /**
         * Reset the ResourcePtr without unloading the resource.
         * @note This should be used carefully as it can cause use-after-free errors.
         */
        void reset_hard()
        {
            if (inner)
            {
                std::destroy_at(this->inner);
                this->allocator.deallocate(this->inner, 1);
            }
            this->inner = nullptr;
        }

        /**
         * Swap the contents of this ResourcePtr with another.
         * @param other The other ResourcePtr to swap with.
         */
        void swap(ResourcePtr &other) noexcept
        {
            std::swap(this->inner, other.inner);
        }

        /**
         * Returns whether or not the ResourcePtr is null.
         * @return
         */
        operator bool() const
        {
            return this->inner != nullptr;
        }

        /**
         * Compiles the ResourcePtr with another.
         * @param other
         * @return
         */
        std::strong_ordering operator<=>(const ResourcePtr &other) const
        {
            return this->inner <=> other.inner;
        }

        /**
         * Set an unload callback that will be called when the resource is unloaded.
         * @param callback The callback to call.
         */
        void set_unload_callback(std::function<void()> callback)
        {
            this->inner->set_unload_callback(callback);
        }

        ResourcePtr clone() const
        {
            return *this;
        }

        [[nodiscard]] size_t get_ref_count() const
        {
            if (this->inner != nullptr)
            {
                return this->inner->get_ref_count();
            }
            return 0;
        }

        T *get()
        {
            if (this->inner)
            {
                return &this->inner->get();
            }
            return nullptr;
        }

    private:
        void reset_impl()
        {
            this->inner->remove_ref();
            if (this->inner->get_ref_count() == 0)
            {
                std::destroy_at(this->inner);
                this->allocator.deallocate(this->inner, 1);
            }
            this->inner = nullptr;
        }
    };
} // namespace missiletoad::core

// NOLINTEND(clang-analyzer-cplusplus.NewDelete)
