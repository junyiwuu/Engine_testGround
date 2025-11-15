#include <gtest/gtest.h>
#include "../material/load_texture.hpp"

TEST(TextureUtilsTest, bytesPerPixel){
    EXPECT_EQ(bytesPerPixel(VK_FORMAT_R8_UNORM), 1);
    EXPECT_EQ(bytesPerPixel(VK_FORMAT_R8G8B8A8_SRGB), 4);
    EXPECT_EQ(bytesPerPixel(VK_FORMAT_R16G16B16A16_SFLOAT), 8);
    EXPECT_EQ(bytesPerPixel(VK_FORMAT_R32G32B32A32_SFLOAT), 16);

    EXPECT_THROW(bytesPerPixel(VK_FORMAT_UNDEFINED), std::runtime_error);
}

//how to do unit test
// create a file, write unit test code, then add thme in cmakelist.txt