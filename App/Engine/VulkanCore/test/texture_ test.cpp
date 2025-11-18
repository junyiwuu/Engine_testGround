#include <gtest/gtest.h>
#include "../material/load_texture.hpp"
#include "../material/bitmap.hpp"

TEST(TextureUtilsTest, bytesPerPixel){
    EXPECT_EQ(bytesPerPixel(VK_FORMAT_R8_UNORM), 1);
    EXPECT_EQ(bytesPerPixel(VK_FORMAT_R8G8B8A8_SRGB), 4);
    EXPECT_EQ(bytesPerPixel(VK_FORMAT_R16G16B16A16_SFLOAT), 8);
    EXPECT_EQ(bytesPerPixel(VK_FORMAT_R32G32B32A32_SFLOAT), 16);

    EXPECT_THROW(bytesPerPixel(VK_FORMAT_UNDEFINED), std::runtime_error);
}

//how to do unit test
// create a file, write unit test code, then add thme in cmakelist.txt


//TEST(TestSuiteName, TestName)
// TestSuiteName: 测试组名字相当于namespace
// TestName: 相当于该组下具体某个测试的名字


TEST(JBitmapTest, ConstructorDimensions){
    JBitmap bitmap(100, 200, 3, eJBitmapFormat_UnsignedByte);
    EXPECT_EQ(bitmap.w_, 100);
    EXPECT_EQ(bitmap.h_, 200);
    EXPECT_EQ(bitmap.channels_, 3);
}


TEST(JBitmapTest, setGetUnsignedByte){
    JBitmap bitmap(10, 10, 4, eJBitmapFormat_UnsignedByte);
    glm::vec4 color(1.0f, 0.5f, 0.25f, 1.0f);

    bitmap.setPixel(5, 5, color);
    glm::vec4 retrieved = bitmap.getPixel(5, 5);

    EXPECT_NEAR(retrieved.r, 1.0f, 0.01f);               // 在这个范围内 [0.99f, 1.01f] 因为浮点数在计算转换例如从Unsignedbyte到float会产生微小误差
    EXPECT_NEAR(retrieved.g, 0.5f, 0.01f);
    EXPECT_NEAR(retrieved.b, 0.25f, 0.01f);
}

TEST(JBitmapTest, setGetPixelFloat){
    JBitmap bitmap(10, 10, 4, eJBitmapFormat_Float);
    glm::vec4 color(0.123f, 0.456f, 0.789f, 1.0f);

    bitmap.setPixel(3, 7, color);
    glm::vec4 retrieved = bitmap.getPixel(3, 7);
    
    EXPECT_FLOAT_EQ(retrieved.r, 0.123f);
    EXPECT_FLOAT_EQ(retrieved.g, 0.456f);
}


TEST(JBitmapTest, OutOfBoundsThrows) {
    JBitmap bitmap(10, 10, 4, eJBitmapFormat_Float);
    glm::vec4 color(1.0f);
    
    EXPECT_THROW(bitmap.getPixel(-1, 5), std::out_of_range);
    EXPECT_THROW(bitmap.getPixel(5, -1), std::out_of_range);
    EXPECT_THROW(bitmap.getPixel(10, 5), std::out_of_range);
    EXPECT_THROW(bitmap.getPixel(5, 10), std::out_of_range);
}

TEST(JBitmapTest, VkFormatConversion) {
    JBitmap bitmap1(10, 10, 3, eJBitmapFormat_UnsignedByte);
    EXPECT_EQ(bitmap1.getVkFormat(), VK_FORMAT_R8G8B8_UNORM);
    
    JBitmap bitmap2(10, 10, 4, eJBitmapFormat_Float);
    EXPECT_EQ(bitmap2.getVkFormat(), VK_FORMAT_R32G32B32A32_SFLOAT);
}









// // App/Engine/VulkanCore/test/cubemap_test.cpp
// #include <gtest/gtest.h>
// #include "../material/cubemapUtils.hpp"

// TEST(CubemapUtilsTest, FaceCoordsToXYZ_Face0) {
//     glm::vec3 result = faceCoordsToXYZ(0, 0, 0, 100);
//     EXPECT_FLOAT_EQ(result.x, -1.0f);
//     EXPECT_FLOAT_EQ(result.y, -1.0f);
//     EXPECT_FLOAT_EQ(result.z, -1.0f);
// }

// TEST(CubemapUtilsTest, FaceCoordsToXYZ_AllFaces) {
//     for (int face = 0; face < 6; ++face) {
//         glm::vec3 result = faceCoordsToXYZ(50, 50, face, 100);
//         // 检查结果在合理范围内
//         EXPECT_GE(glm::length(result), 0.1f);
//         EXPECT_LE(glm::length(result), 2.0f);
//     }
// }

// TEST(CubemapUtilsTest, ConvertVerticalCross_Dimensions) {
//     JBitmap input(300, 400, 3, eJBitmapFormat_UnsignedByte); // 3x4 cross
//     JBitmap output = convertVerticalCrossToCubeMapFaces(input);
    
//     EXPECT_EQ(output.type_, eJBitmapType_Cube);
//     EXPECT_EQ(output.depth_, 6);
//     EXPECT_EQ(output.w_, 100);
//     EXPECT_EQ(output.h_, 100);
// }

// TEST(CubemapUtilsTest, ConvertEquirectangular_NotNull) {
//     JBitmap equirect(512, 256, 3, eJBitmapFormat_Float);
//     JBitmap cross = convertEquirectangularMapToVerticalCross(equirect);
    
//     EXPECT_GT(cross.w_, 0);
//     EXPECT_GT(cross.h_, 0);
// }


// // App/Engine/Scene/test/camera_test.cpp
// #include <gtest/gtest.h>
// #include "../camera.hpp"

// TEST(CameraArcballTest, Initialization) {
//     glm::vec3 pos(0, 0, 5);
//     glm::vec3 target(0, 0, 0);
//     glm::vec3 up(0, 1, 0);
    
//     Scene::JCameraPositioner_Arcball cam(pos, target, up, DragMode::None);
    
//     glm::vec3 eyePos = cam.eye();
//     EXPECT_NEAR(eyePos.z, 5.0f, 0.01f);
// }

// TEST(CameraArcballTest, ViewMatrixNotIdentity) {
//     Scene::JCameraPositioner_Arcball cam(
//         glm::vec3(0, 0, 5), 
//         glm::vec3(0, 0, 0), 
//         glm::vec3(0, 1, 0), 
//         DragMode::None
//     );
    
//     glm::mat4 view = cam.getViewMatrix();
//     EXPECT_NE(view, glm::mat4(1.0f));
// }

// TEST(CameraFirstPersonTest, LookAt) {
//     Scene::JCameraPositioner_firstPerson cam;
//     cam.lookAt(
//         glm::vec3(0, 0, 5),
//         glm::vec3(0, 0, 0),
//         glm::vec3(0, 1, 0)
//     );
    
//     glm::vec3 pos = cam.getPosition();
//     EXPECT_FLOAT_EQ(pos.x, 0.0f);
//     EXPECT_FLOAT_EQ(pos.y, 0.0f);
//     EXPECT_FLOAT_EQ(pos.z, 5.0f);
// }



















