/*
 * AUTOGENERATED - DO NOT EDIT
 *
 * This file is generated from mir-window-management-unstable-v1.xml
 * To regenerate, run the “refresh-wayland-wrapper” target.
 */

#ifndef MIR_FRONTEND_WAYLAND_MIR_WINDOW_MANAGEMENT_UNSTABLE_V1_XML_WRAPPER
#define MIR_FRONTEND_WAYLAND_MIR_WINDOW_MANAGEMENT_UNSTABLE_V1_XML_WRAPPER

#include <experimental/optional>

#include "mir/fd.h"
#include <wayland-server-core.h>

#include "mir/wayland/wayland_base.h"

namespace mir
{
namespace wayland
{

class MirWmBaseV1;
class MirShellSurfaceV1;

class MirWmBaseV1 : public Resource
{
public:
    static char const constexpr* interface_name = "zmir_wm_base_v1";

    static MirWmBaseV1* from(struct wl_resource*);

    MirWmBaseV1(struct wl_resource* resource, Version<1>);
    virtual ~MirWmBaseV1();

    void destroy_wayland_object() const;

    struct wl_client* const client;
    struct wl_resource* const resource;

    struct Thunks;

    static bool is_instance(wl_resource* resource);

    class Global : public wayland::Global
    {
    public:
        Global(wl_display* display, Version<1>);

        auto interface_name() const -> char const* override;

    private:
        virtual void bind(wl_resource* new_zmir_wm_base_v1) = 0;
        friend MirWmBaseV1::Thunks;
    };

private:
    virtual void destroy() = 0;
    virtual void get_shell_surface(struct wl_resource* id, struct wl_resource* surface) = 0;
};

class MirShellSurfaceV1 : public Resource
{
public:
    static char const constexpr* interface_name = "zmir_shell_surface_v1";

    static MirShellSurfaceV1* from(struct wl_resource*);

    MirShellSurfaceV1(struct wl_resource* resource, Version<1>);
    virtual ~MirShellSurfaceV1();

    void destroy_wayland_object() const;

    struct wl_client* const client;
    struct wl_resource* const resource;

    struct Error
    {
        static uint32_t const invalid_window_type = 0;
    };

    struct WindowType
    {
        static uint32_t const default_ = 0;
        static uint32_t const satellite = 1;
    };

    struct Thunks;

    static bool is_instance(wl_resource* resource);

private:
    virtual void destroy() = 0;
    virtual void set_window_type(uint32_t type) = 0;
};

}
}

#endif // MIR_FRONTEND_WAYLAND_MIR_WINDOW_MANAGEMENT_UNSTABLE_V1_XML_WRAPPER
