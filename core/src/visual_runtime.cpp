#include "renderer.h"
#include "visual_runtime/api.h"

#include <cstdio>

static const char *VERSION = "v1"; // change this to demonstrate hot reload

static Renderer g_renderer;

static void visual_runtime_init_impl(VisualRuntimeState *state,
                                     SurfaceDescriptor *surface) {
  state->frame_count = 0;
  state->elapsed_time = 0.0f;
  g_renderer.init(surface);
  std::printf("[visual-runtime %s] init\n", VERSION);
  std::fflush(stdout);
}

static void visual_runtime_resize_impl(VisualRuntimeState *, uint32_t width,
                                       uint32_t height) {
  g_renderer.resize(width, height);
}

static void visual_runtime_update_impl(VisualRuntimeState *state, float dt) {
  state->frame_count++;
  state->elapsed_time += dt;
  g_renderer.render_frame(state->elapsed_time);
}

static void visual_runtime_shutdown_impl(VisualRuntimeState *) {
  g_renderer.shutdown();
}

static void visual_runtime_set_background_color_impl(VisualRuntimeState *state, BackgroundColor *color) {
  g_renderer.setBackgroundColor(color);
}

static void visual_runtime_pan_impl(VisualRuntimeState *, float dx, float dy) {
  g_renderer.pan(dx, dy);
}

static void visual_runtime_zoom_impl(VisualRuntimeState *, float delta) {
  g_renderer.zoom(delta);
}

extern "C" {

const VisualRuntimeAPI *visual_runtime_get_api() {
  static const VisualRuntimeAPI api{
      VISUAL_RUNTIME_API_VERSION,   sizeof(VisualRuntimeAPI),
      VISUAL_RUNTIME_BACKEND_NAME,  visual_runtime_init_impl,
      visual_runtime_resize_impl,   visual_runtime_update_impl,
      visual_runtime_shutdown_impl,
      visual_runtime_set_background_color_impl,
      visual_runtime_pan_impl,
      visual_runtime_zoom_impl,
  };
  return &api;
}

} // extern "C"
