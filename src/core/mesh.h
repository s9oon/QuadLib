#pragma once

#include <cstdint>
#include <vector>

struct Vertex2D {
    float x;
    float y;
    float z;

    uint32_t color;
    
    float u;
    float v;
};

class Mesh2D {
public:
    Mesh2D();
    ~Mesh2D();

    bool Create(const std::vector<Vertex2D>& vertices, const std::vector<uint16_t>& indices);

    void Destroy();

private:
    struct Impl;
    Impl* m_impl;
};