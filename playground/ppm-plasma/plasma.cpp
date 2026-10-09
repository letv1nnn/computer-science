#include <cmath>
#include <cstdio>
#include <filesystem>

constexpr std::size_t factor{60};
constexpr std::size_t w{16 * factor}, h{9 * factor};
constexpr std::size_t frames{240};
constexpr const char *assets_dir{"assets"};

struct vec4 {
    float x, y, z, w;
    constexpr explicit vec4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f)
        : x{x}, y{y}, z{z}, w{w} {}
};

struct vec2 {
    float x, y;
    constexpr explicit vec2(float x = 0.f, float y = 0.f) : x{x}, y{y} {}
    constexpr vec2 yx() const { return vec2(y, x); }
    constexpr vec4 xyyx() const { return vec4(x, y, y, x); }
};

// vec2 operators
constexpr vec2 operator+(const vec2 &a, const vec2 &b) { return vec2(a.x + b.x, a.y + b.y); }
constexpr vec2 operator-(const vec2 &a, const vec2 &b) { return vec2(a.x - b.x, a.y - b.y); }
constexpr vec2 operator*(const vec2 &a, const vec2 &b) { return vec2(a.x * b.x, a.y * b.y); }
constexpr vec2 operator+(const vec2 &a, float s) { return vec2(a.x + s, a.y + s); }
constexpr vec2 operator*(const vec2 &a, float s) { return vec2(a.x * s, a.y * s); }
constexpr vec2 operator*(float s, const vec2 &a) { return a * s; }
constexpr vec2 operator/(const vec2 &a, float s) { return vec2(a.x / s, a.y / s); }
constexpr vec2 &operator+=(vec2 &a, const vec2 &b) { return a = a + b; }
constexpr vec2 &operator+=(vec2 &a, float s) { return a = a + s; }

// vec4 operators
constexpr vec4 operator+(const vec4 &a, const vec4 &b) { return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
constexpr vec4 operator/(const vec4 &a, const vec4 &b) { return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
constexpr vec4 operator+(const vec4 &a, float s) { return vec4(a.x + s, a.y + s, a.z + s, a.w + s); }
constexpr vec4 operator*(const vec4 &a, float s) { return vec4(a.x * s, a.y * s, a.z * s, a.w * s); }
constexpr vec4 operator*(float s, const vec4 &a) { return a * s; }
constexpr vec4 operator-(float s, const vec4 &a) { return vec4(s - a.x, s - a.y, s - a.z, s - a.w); }
constexpr vec4 &operator+=(vec4 &a, const vec4 &b) { return a = a + b; }

// GLSL-like helpers
constexpr float dot(const vec2 &a, const vec2 &b) { return a.x * b.x + a.y * b.y; }
inline vec2 abs(const vec2 &a) { return vec2(std::fabs(a.x), std::fabs(a.y)); }
inline vec2 cos(const vec2 &a) { return vec2(std::cos(a.x), std::cos(a.y)); }
inline vec4 sin(const vec4 &a) { return vec4(std::sin(a.x), std::sin(a.y), std::sin(a.z), std::sin(a.w)); }
inline vec4 exp(const vec4 &a) { return vec4(std::exp(a.x), std::exp(a.y), std::exp(a.z), std::exp(a.w)); }
inline vec4 tanh(const vec4 &a) { return vec4(std::tanh(a.x), std::tanh(a.y), std::tanh(a.z), std::tanh(a.w)); }

int main() {
    std::filesystem::create_directories(assets_dir);

    char path[256];
    for (std::size_t frame{}; frame < frames; ++frame) {
        std::snprintf(path, sizeof(path), "%s/output-%03zu.ppm", assets_dir, frame);
        std::FILE *f = std::fopen(path, "wb");
        if (!f) {
            std::perror(path);
            return 1;
        }

        std::fprintf(f, "P6\n%zu %zu\n255\n", w, h);

        const vec2 r{w, h};
        const float t = (static_cast<float>(frame) / frames) * 2 * M_PI;

        for (std::size_t y{}; y < h; ++y) {
            for (std::size_t x{}; x < w; ++x) {
                vec4 o;
                // fragment is basically a pixel, at least we can treat it like pixel
                const vec2 FC(x, y);

                // plasma shader: https://x.com/XorDev/status/1894123951401378051
                vec2 p=(FC*2.-r)/r.y,l,i,v=p*(l+=4.-4.*std::abs(.7-dot(p,p)));
                for(;i.y++<8.;o+=(sin(v.xyyx())+1.)*std::abs(v.x-v.y))v+=cos(v.yx()*i.y+i+t)/i.y+.7;
                o=tanh(5.*exp(l.x-4.-p.y*vec4(-1,1,2,0))/o);

                std::fputc(o.x * 255, f);
                std::fputc(o.y * 255, f);
                std::fputc(o.z * 255, f);
            }
        }

        std::fclose(f);
        std::printf("Generated %s (%3zu/%3zu)\n", path, frame + 1, frames);
    }

    return 0;
}
