#include <cstddef>
#include <cstdlib>
#include <gtest/gtest.h>

extern "C" char *reverse_str(const char *str, std::size_t str_length) {
    char *out = static_cast<char *>(std::malloc(str_length + 1));
    if (!out) return nullptr;
    for (std::size_t i = 0; i < str_length; ++i)
        out[i] = str[str_length - i - 1];
    out[str_length] = '\0';
    return out;
}

TEST(FunctionMangling, ReverseString) {
    const char *in = "hello";
    EXPECT_STREQ(reverse_str(in, 5), "olleh");
}
