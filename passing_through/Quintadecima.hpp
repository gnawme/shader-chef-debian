#ifndef SHADER_CHEF_QUINTADECIMA_HPP
#define SHADER_CHEF_QUINTADECIMA_HPP
/*! -------------------------------------------------------------------------*\
| Generates the 15th known tiling pentagon from computed vertices
| \see  http://bit.ly/1NOHRfM
\*---------------------------------------------------------------------------*/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace
{
    double torad(double deg) {
        return deg * 3.14159265358979323846f / 180.0;
    }

    void printFloatValue(double value)
    {
        std::cout << std::fixed << std::setprecision(7) << value;
    }

    void printVec3(std::string desc, const glm::vec3& vec)
    {
        std::cout << desc;
        printFloatValue(vec.x);
        std::cout << ", ";
        printFloatValue(vec.y);
        std::cout << ", ";
        printFloatValue(vec.z);
        std::cout << std::endl;
    }
}

class Quintadecima
{
public:

    Quintadecima(
        double   a_length)
        : m_alength(a_length)
        , m_blength(0.5 * a_length)
        , m_clength(a_length / (std::sqrt(2.0) * (std::sqrt(3.0) - 1.0)))
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
    double*      vertex_buffer()
    {
        // Allocate for 5 dvec3<double>
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
            m_cbo.emplace_back(m_hue_r.a);

            m_cbo.emplace_back(m_hue_o.r);
            m_cbo.emplace_back(m_hue_o.g);
            m_cbo.emplace_back(m_hue_o.b);
            m_cbo.emplace_back(m_hue_o.a);

            m_cbo.emplace_back(m_hue_y.r);
            m_cbo.emplace_back(m_hue_y.g);
            m_cbo.emplace_back(m_hue_y.b);
            m_cbo.emplace_back(m_hue_y.a);

            m_cbo.emplace_back(m_hue_g.r);
            m_cbo.emplace_back(m_hue_g.g);
            m_cbo.emplace_back(m_hue_g.b);
            m_cbo.emplace_back(m_hue_g.a);

            m_cbo.emplace_back(m_hue_b.r);
            m_cbo.emplace_back(m_hue_b.g);
            m_cbo.emplace_back(m_hue_b.b);
            m_cbo.emplace_back(m_hue_b.a);
        }

        return &m_cbo[0];
    }

    //! \fn     color_buffer_mono
    float*      color_buffer_mono()
    {
        if (m_cbo.empty()) {
            m_cbo.emplace_back(m_hue_r.r);
            m_cbo.emplace_back(m_hue_r.g);
            m_cbo.emplace_back(m_hue_r.b);
            m_cbo.emplace_back(m_hue_r.a);

            m_cbo.emplace_back(m_hue_r.r);
            m_cbo.emplace_back(m_hue_r.g);
            m_cbo.emplace_back(m_hue_r.b);
            m_cbo.emplace_back(m_hue_r.a);

            m_cbo.emplace_back(m_hue_r.r);
            m_cbo.emplace_back(m_hue_r.g);
            m_cbo.emplace_back(m_hue_r.b);
            m_cbo.emplace_back(m_hue_r.a);

            m_cbo.emplace_back(m_hue_r.r);
            m_cbo.emplace_back(m_hue_r.g);
            m_cbo.emplace_back(m_hue_r.b);
            m_cbo.emplace_back(m_hue_r.a);

            m_cbo.emplace_back(m_hue_r.r);
            m_cbo.emplace_back(m_hue_r.g);
            m_cbo.emplace_back(m_hue_r.b);
            m_cbo.emplace_back(m_hue_r.a);
        }

        return &m_cbo[0];
    }


    //! \fn     color_data_size
    //! \brief  Returns number of vertices (5) * dimension
    int         color_data_size() const
    {
        return 5 * sizeof(glm::vec4);
    }

    //! \fn     vertex_data_size
    //! \brief  Returns number of vertices (5) * dimension
    int         vertex_data_size() const
    {
        return 5 * sizeof(glm::dvec3);
    }

private:
    //! \fn     gen_pt_a
    //! \brief  Vertex A (segment EA)
    glm::dvec3   gen_pt_a()
    {
        return glm::dvec3(m_alength, 0.0, 0.0);
    }

    //! \fn     gen_pt_b
    //! \brief  Vertex B (segment AB)
    glm::dvec3   gen_pt_b()
    {
        return glm::dvec3(
                   m_blength * std::cos(torad(120.0)),
                   m_blength * std::sin(torad(120.0)),
                   0.0
               ) + m_pt_a;
    }

    //! \fn     gen_pt_c
    //! \brief  Vertex C (segment BC)
    glm::dvec3   gen_pt_c()
    {
        return glm::dvec3(
                   m_clength * std::cos(torad(165.0)),
                   m_clength * std::sin(torad(165.0)),
                   0.0) + m_pt_b;
    }

    //! \fn     gen_pt_d
    //! \brief  Vertex D (segment CD)
    glm::dvec3   gen_pt_d()
    {
        return glm::dvec3(
                   m_dlength * std::cos(torad(-120.0)),
                   m_dlength * std::sin(torad(-120.0)),
                   0.0) + m_pt_c;
    }

    //! \fn     gen_pt_e
    //! \brief  Vertex E (segment DE)
    glm::dvec3   gen_pt_e()
    {
        return glm::dvec3(
                   m_elength * std::cos(torad(330.0)),
                   m_elength * std::sin(torad(330.0)),
                   0.0) + m_pt_d;
    }

    //! \fn     load_colors
    //! \brief  Loads the colors for the 5 vertices
    void        load_colors()
    {
        m_hue_r = glm::vec4(0.808f, 0.000f, 0.345f, 0.500f);
        m_hue_o = glm::vec4(1.000f, 0.369f, 0.000f, 0.500f);
        m_hue_y = glm::vec4(1.000f, 0.851f, 0.000f, 0.500f);
        m_hue_g = glm::vec4(0.606f, 0.916f, 0.843f, 0.500f);
        m_hue_b = glm::vec4(0.455f, 0.820f, 0.918f, 0.500f);
    }

    double      m_alength;
    double      m_blength;
    double      m_clength;
    double      m_dlength;
    double      m_elength;

    glm::dvec3  m_pt_a;
    glm::dvec3  m_pt_b;
    glm::dvec3  m_pt_c;
    glm::dvec3  m_pt_d;
    glm::dvec3  m_pt_e;

    glm::vec4   m_hue_r;
    glm::vec4   m_hue_o;
    glm::vec4   m_hue_y;
    glm::vec4   m_hue_g;
    glm::vec4   m_hue_b;

    std::vector<double> m_vbo;
    std::vector<float>  m_cbo;

};

#endif//SHADER_CHEF_QUINTADECIMA_HPP