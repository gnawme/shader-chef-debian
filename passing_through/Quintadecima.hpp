#ifndef SHADER_CHEF_QUINTADECIMA_HPP
#define SHADER_CHEF_QUINTADECIMA_HPP
/*---------------------------------------------------------------------------*\
| \file     Quintadecima.hpp
| \brief    Generates the 15th known tiling pentagon
| \see      http://bit.ly/1NOHRfM
\*---------------------------------------------------------------------------*/
#include <cmath>
#include <vector>

namespace
{
    float torad(float deg) {
        return deg * 3.14159265358979323846f / 180.0f;
    }
}

class Quintadecima
{
public:

    Quintadecima(
        float   a_length)
        : m_alength(a_length)
        , m_blength(0.5f * a_length)
        , m_clength(a_length / (std::sqrt(2.0f) * (std::sqrt(3.0f) - 1.0f)))
        , m_dlength(m_blength)
        , m_elength(m_blength)
    {
        m_pt_a = gen_pt_a();
        m_pt_b = gen_pt_b();
        m_pt_c = gen_pt_c();
        m_pt_d = gen_pt_d();
        m_pt_e = gen_pt_e();

        load_colors();
    }

    //! \fn     vertex_buffer
    //! \brief  Returns pentagon decomposed into triangle strip DCEBA
    float*      vertex_buffer()
    {
        // Allocate for 5 vec3<float>
        if (m_vbo.empty()) {
            m_vbo.emplace_back(m_pt_d.x);
            m_vbo.emplace_back(m_pt_d.y);
            m_vbo.emplace_back(m_pt_d.z);

            m_vbo.emplace_back(m_pt_c.x);
            m_vbo.emplace_back(m_pt_c.y);
            m_vbo.emplace_back(m_pt_c.z);

            m_vbo.emplace_back(m_pt_e.x);
            m_vbo.emplace_back(m_pt_e.y);
            m_vbo.emplace_back(m_pt_e.z);

            m_vbo.emplace_back(m_pt_b.x);
            m_vbo.emplace_back(m_pt_b.y);
            m_vbo.emplace_back(m_pt_b.z);

            m_vbo.emplace_back(m_pt_a.x);
            m_vbo.emplace_back(m_pt_a.y);
            m_vbo.emplace_back(m_pt_a.z);
        }

        return &m_vbo[0];
    }

    //! \fn     color_buffer
    float*      color_buffer()
    {
        if (m_cbo.empty()) {
            m_cbo.emplace_back(m_hue_r.r);
            m_cbo.emplace_back(m_hue_r.g);
            m_cbo.emplace_back(m_hue_r.b);

            m_cbo.emplace_back(m_hue_o.r);
            m_cbo.emplace_back(m_hue_o.g);
            m_cbo.emplace_back(m_hue_o.b);

            m_cbo.emplace_back(m_hue_y.r);
            m_cbo.emplace_back(m_hue_y.g);
            m_cbo.emplace_back(m_hue_y.b);

            m_cbo.emplace_back(m_hue_g.r);
            m_cbo.emplace_back(m_hue_g.g);
            m_cbo.emplace_back(m_hue_g.b);

            m_cbo.emplace_back(m_hue_b.r);
            m_cbo.emplace_back(m_hue_b.g);
            m_cbo.emplace_back(m_hue_b.b);
        }

        return &m_cbo[0];
    }

    //! \fn     data_size
    //! \brief  Returns number of vertices (5) * dimension (3)
    int         data_size() const
    {
        const int NUM_PENT_VERTS = 5;
        const int PENT_VERT_DIM = 3;
        return NUM_PENT_VERTS * PENT_VERT_DIM;
    }

private:
    //! \fn     gen_pt_a
    //! \brief  Vertex A (segment EA)
    glm::vec3   gen_pt_a()
    {
        return glm::vec3(m_alength, 0.0, 0.0);
    }

    //! \fn     gen_pt_b
    //! \brief  Vertex B (segment AB)
    glm::vec3   gen_pt_b()
    {
        return glm::vec3(
                   m_blength * std::cos(torad(120.0)),
                   m_blength * std::sin(torad(120.0)),
                   0.0
               ) + m_pt_a;
    }

    //! \fn     gen_pt_c
    //! \brief  Vertex C (segment BC)
    glm::vec3   gen_pt_c()
    {
        return glm::vec3(
                   m_clength * std::cos(torad(165.0)),
                   m_clength * std::sin(torad(165.0)),
                   0.0) + m_pt_b;
    }

    //! \fn     gen_pt_d
    //! \brief  Vertex D (segment CD)
    glm::vec3   gen_pt_d()
    {
        return glm::vec3(
                   m_dlength * std::cos(torad(-120.0)),
                   m_dlength * std::sin(torad(-120.0)),
                   0.0) + m_pt_c;
    }

    //! \fn     gen_pt_e
    //! \brief  Vertex E (segment DE)
    glm::vec3   gen_pt_e()
    {
        return glm::vec3(
                   m_elength * std::cos(torad(330.0)),
                   m_elength * std::sin(torad(330.0)),
                   0.0) + m_pt_d;
    }

    //! \fn     load_colors
    //! \brief  Loads the colors for the 5 vertices
    void        load_colors()
    {
        m_hue_r = glm::vec3(0.808f, 0.000f, 0.345f);
        m_hue_o = glm::vec3(1.000f, 0.369f, 0.000f);
        m_hue_y = glm::vec3(1.000f, 0.851f, 0.000f);
        m_hue_g = glm::vec3(0.606f, 0.916f, 0.843f);
        m_hue_b = glm::vec3(0.455f, 0.820f, 0.918f);
    }

    float       m_alength;
    float       m_blength;
    float       m_clength;
    float       m_dlength;
    float       m_elength;

    glm::vec3   m_pt_a;
    glm::vec3   m_pt_b;
    glm::vec3   m_pt_c;
    glm::vec3   m_pt_d;
    glm::vec3   m_pt_e;

    glm::vec3   m_hue_r;
    glm::vec3   m_hue_o;
    glm::vec3   m_hue_y;
    glm::vec3   m_hue_g;
    glm::vec3   m_hue_b;

    std::vector<float> m_vbo;
    std::vector<float> m_cbo;

};

#endif//SHADER_CHEF_QUINTADECIMA_HPP