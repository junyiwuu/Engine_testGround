#include "utility.hpp"


namespace util{



    std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
    
        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }
    
        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);
    
        file.seekg(0);
        file.read(buffer.data(), fileSize);
    
        file.close();
    
        return buffer;
    }


// type filter是buffer告诉哪些memory type可用， properties是你希望内存又哪些属性
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice){
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
    
         //检查typefilter这个二进制数的第i位是否为1
        for(uint32_t i=0; i<memProperties.memoryTypeCount; i++){
            if((typeFilter&(1<<i))&&                       // 遍历GPU的所有memory types,检查typefilter的第i位是否为1,意味着这个buffer可以使用memory type[i]
                (memProperties.memoryTypes[i].propertyFlags & properties)==properties) {  
                    return i;}
        } throw std::runtime_error("failed to find suitable memory type!");
    }
    

}