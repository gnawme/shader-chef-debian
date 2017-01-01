//---------------------------------------------------------------------------*/
//! \file     QuintadecimaRaw.hpp
//! \brief    Generates the 15th known tiling pentagon from given points
//! \see      http://bit.ly/1NOHRfM
//---------------------------------------------------------------------------*/
#ifndef PASSING_THROUGH_QUINTADECIMARAW_H
#define PASSING_THROUGH_QUINTADECIMARAW_H

#include <glm/glm.hpp>
#include <vector>

//Point A Vector[1.0, 0.0]
//Point B Vector[0.75, 0.4296875]
//Point C Vector[-0.171875, 0.6796875]
//Point D Vector[-0.4296875, 0.25]
//Point E Vector[0.0, 0.0]

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
            m_cbo.push_back(m_hue_r.r);
            m_cbo.push_back(m_hue_r.g);
            m_cbo.push_back(m_hue_r.b);

            m_cbo.push_back(m_hue_o.r);
            m_cbo.push_back(m_hue_o.g);
            m_cbo.push_back(m_hue_o.b);

            m_cbo.push_back(m_hue_y.r);
            m_cbo.push_back(m_hue_y.g);
            m_cbo.push_back(m_hue_y.b);

            m_cbo.push_back(m_hue_g.r);
            m_cbo.push_back(m_hue_g.g);
            m_cbo.push_back(m_hue_g.b);

            m_cbo.push_back(m_hue_b.r);
            m_cbo.push_back(m_hue_b.g);
            m_cbo.push_back(m_hue_b.b);
        }

        return &m_cbo[0];
    }

    //! \fn     data_size
    //! \brief  Returns number of vertices (5) * dimension (3)
    int         data_size() const
    {
        const int NUM_PENT_VERTS = 5;
        const int PENT_VERT_DIM  = 3;

        return NUM_PENT_VERTS * PENT_VERT_DIM;
    }

    //! \fn     vertex_buffer
    //! \brief  Returns pentagon decomposed into triangle strip DCEBA
    float*      vertex_buffer()
    {
        // Allocate for 5 vec3<float>
        if (m_vbo.empty()) {
            m_vbo.push_back(m_pt_d.x);
            m_vbo.push_back(m_pt_d.y);
            m_vbo.push_back(m_pt_d.z);

            m_vbo.push_back(m_pt_c.x);
            m_vbo.push_back(m_pt_c.y);
            m_vbo.push_back(m_pt_c.z);

            m_vbo.push_back(m_pt_e.x);
            m_vbo.push_back(m_pt_e.y);
            m_vbo.push_back(m_pt_e.z);

            m_vbo.push_back(m_pt_b.x);
            m_vbo.push_back(m_pt_b.y);
            m_vbo.push_back(m_pt_b.z);

            m_vbo.push_back(m_pt_a.x);
            m_vbo.push_back(m_pt_a.y);
            m_vbo.push_back(m_pt_a.z);
        }

        return &m_vbo[0];
    }


private:
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


#endif //PASSING_THROUGH_QUINTADECIMARAW_H
