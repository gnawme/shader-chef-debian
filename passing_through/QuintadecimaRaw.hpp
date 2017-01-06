/*! -------------------------------------------------------------------------*\
| \file     QuintadecimaRaw.hpp
| \brief    Generates the 15th known tiling pentagon from given points
| \see      http://bit.ly/1NOHRfM
\*---------------------------------------------------------------------------*/
#ifndef PASSING_THROUGH_QUINTADECIMARAW_H
#define PASSING_THROUGH_QUINTADECIMARAW_H

#include <glm/glm.hpp>
#include <vector>

//! \class QuintadecimaRaw
class QuintadecimaRaw
{
public:
    QuintadecimaRaw()
    : m_pt_a( 1.0000000, 0.0000000, 0.0)
    , m_pt_b( 0.7500000, 0.4296875, 0.0)
    , m_pt_c(-0.1718750, 0.6796875, 0.0)
    , m_pt_d(-0.4296875, 0.2500000, 0.0)
    , m_pt_e( 0.0000000, 0.0000000, 0.0)
    {
        load_colors();
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
            m_cbo.emplace_back(m_hue_y.r);
            m_cbo.emplace_back(m_hue_y.g);
            m_cbo.emplace_back(m_hue_y.b);
            m_cbo.emplace_back(m_hue_y.a);

            m_cbo.emplace_back(m_hue_y.r);
            m_cbo.emplace_back(m_hue_y.g);
            m_cbo.emplace_back(m_hue_y.b);
            m_cbo.emplace_back(m_hue_y.a);

            m_cbo.emplace_back(m_hue_y.r);
            m_cbo.emplace_back(m_hue_y.g);
            m_cbo.emplace_back(m_hue_y.b);
            m_cbo.emplace_back(m_hue_y.a);

            m_cbo.emplace_back(m_hue_y.r);
            m_cbo.emplace_back(m_hue_y.g);
            m_cbo.emplace_back(m_hue_y.b);
            m_cbo.emplace_back(m_hue_y.a);

            m_cbo.emplace_back(m_hue_y.r);
            m_cbo.emplace_back(m_hue_y.g);
            m_cbo.emplace_back(m_hue_y.b);
            m_cbo.emplace_back(m_hue_y.a);
        }

        return &m_cbo[0];
    }

    //! \fn     color_data_size
    //! \brief  Returns number of vertices (5) * dimension
    int         color_data_size() const
    {
        return 5 * sizeof(glm::vec4);
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

    //! \fn     vertex_data_size
    //! \brief  Returns number of vertices (5) * dimension
    int         vertex_data_size() const
    {
        return 5 * sizeof(glm::vec3);
    }


private:
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

    glm::vec3   m_pt_a;
    glm::vec3   m_pt_b;
    glm::vec3   m_pt_c;
    glm::vec3   m_pt_d;
    glm::vec3   m_pt_e;

    glm::vec4   m_hue_r;
    glm::vec4   m_hue_o;
    glm::vec4   m_hue_y;
    glm::vec4   m_hue_g;
    glm::vec4   m_hue_b;

    std::vector<float> m_vbo;
    std::vector<float> m_cbo;
};


#endif //PASSING_THROUGH_QUINTADECIMARAW_H
