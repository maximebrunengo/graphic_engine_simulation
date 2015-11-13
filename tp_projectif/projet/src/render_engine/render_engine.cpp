/*
**    TP CPE Lyon
**    Copyright (C) 2015 Damien Rohmer
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#include "render_engine.hpp"

#include "image/image.hpp"
#include "image/color.hpp"
#include "image/image_zbuffer.hpp"
#include "image/texture.hpp"
#include "lib/3d/vec3.hpp"
#include "lib/3d/vec4.hpp"
#include "lib/3d/mat4.hpp"
#include "image/drawer.hpp"
#include "lib/mesh/mesh.hpp"
#include "lib/common/basic_functions.hpp"

#include <cmath>

namespace cpe
{

// convert the (x,y) coordinate of a vec3 in discrete pixel position in an image of size (Nx,Ny)
static ivec2 coordinates_to_pixel_index(vec3 const& coord,int const Nx,int const Ny)
{
    int const x = (coord.x()+1.0f)/2.0f * Nx;
    int const y = (coord.y()+1.0f)/2.0f * Ny;

    return ivec2(x,y);
}

//helper function converting a vec3 (x,y,z) into a color (r,g,b)
// (a mesh structure store a color as a vec3)
static color to_color(vec3 const& p)
{
    return color(p.x(),p.y(),p.z());
}


void render(image& im,image_zbuffer& zbuffer,
            vec3 const& p0,vec3 const& p1,vec3 const& p2,
            color const& c0,color const& c1,color const& c2,
            vec3 const& n0,vec3 const& n1,vec3 const& n2,
            mat4 const& model,mat4 const& view,mat4 const& projection)
{
    vec3 p0_proj,p1_proj,p2_proj;
    color c0_shading,c1_shading,c2_shading;

    //apply vertex shader on the 3 vertices
    vertex_shader(p0_proj,c0_shading , p0,c0,n0 , model,view,projection);
    vertex_shader(p1_proj,c1_shading , p1,c1,n1 , model,view,projection);
    vertex_shader(p2_proj,c2_shading , p2,c2,n2 , model,view,projection);



    //convert normalized coordinates to pixel coordinate
    ivec2 u0 = coordinates_to_pixel_index(p0_proj,im.Nx(),im.Ny());
    ivec2 u1 = coordinates_to_pixel_index(p1_proj,im.Nx(),im.Ny());
    ivec2 u2 = coordinates_to_pixel_index(p2_proj,im.Nx(),im.Ny());

    //draw triangle in the screen space
    draw_triangle(im,zbuffer,u0,u1,u2 , c0_shading,c1_shading,c2_shading ,
                  p0_proj.z(),p1_proj.z(),p2_proj.z() );
}






void render(image& im,image_zbuffer& zbuffer,mesh const& m,
            mat4 const& model,mat4 const& view,mat4 const& projection)
{
    /*************************************
    // TO DO
    /*************************************
    // Completez l'affichage d'un maillage
    //
    // Pour tous les triangles
    //   p0,p1,p2 <- coordonnees des sommets du triangle
    //   c0,c1,c2 <- couleurs des sommets du triangle (utilisez la fonction to_color pour convertir un vec3 vers la structure color)
    //   n0,n1,n2 <- normales des sommets du triangle
    //
    //   render triangle
    */



    for(int i=0; i<m.size_connectivity(); ++i)
    {
        triangle_index connec = m.connectivity(i);

        vec3 p0 = m.vertex(connec(0));
        vec3 p1 = m.vertex(connec(1));
        vec3 p2 = m.vertex(connec(2));
        color c0 = color(m.color(connec(0)).x(), m.color(connec(0)).y(), m.color(connec(0)).z());
        color c1 = color(m.color(connec(1)).x(), m.color(connec(1)).y(), m.color(connec(1)).z());
        color c2 = color(m.color(connec(2)).x(), m.color(connec(2)).y(), m.color(connec(2)).z());
        vec3 n0 = m.normal(connec(0));
        vec3 n1 = m.normal(connec(1));
        vec3 n2 = m.normal(connec(2));

        render(im, zbuffer, p0, p1, p2, c0, c1, c2, n0, n1, n2, model, view, projection);

    }

}

void render(image& im,image_zbuffer& zbuffer,mesh const& m,
            mat4 const& model,mat4 const& view,mat4 const& projection,texture& t)
{
    /*************************************
    // TO DO
    /*************************************
    // Completez l'affichage d'un maillage
    //
    // Pour tous les triangles
    //   p0,p1,p2 <- coordonnees des sommets du triangle
    //   c0,c1,c2 <- couleurs des sommets du triangle (utilisez la fonction to_color pour convertir un vec3 vers la structure color)
    //   n0,n1,n2 <- normales des sommets du triangle
    //
    //   render triangle
    */



    for(int i=0; i<m.size_connectivity(); ++i)
    {
        triangle_index connec = m.connectivity(i);

        vec3 p0 = m.vertex(connec(0));
        vec3 p1 = m.vertex(connec(1));
        vec3 p2 = m.vertex(connec(2));
        color c0 = color(m.color(connec(0)).x(), m.color(connec(0)).y(), m.color(connec(0)).z());
        color c1 = color(m.color(connec(1)).x(), m.color(connec(1)).y(), m.color(connec(1)).z());
        color c2 = color(m.color(connec(2)).x(), m.color(connec(2)).y(), m.color(connec(2)).z());
        vec3 n0 = m.normal(connec(0));
        vec3 n1 = m.normal(connec(1));
        vec3 n2 = m.normal(connec(2));

        vec2 coord_text0 = m.texture_coord(connec(0));
//        std::cout<<coord_text0<<std::endl;
        vec2 coord_text1 = m.texture_coord(connec(1));
        vec2 coord_text2 = m.texture_coord(connec(2));

//        color text_color0 = t(coord_text0);
//        color text_color1 = t(coord_text1);
//        color text_color2 = t(coord_text2);

        vec3 p0_proj,p1_proj,p2_proj;
        color c0_shading,c1_shading,c2_shading;

        //apply vertex shader on the 3 vertices
        vertex_shader(p0_proj,c0_shading , p0,c0,n0 , model,view,projection);
        vertex_shader(p1_proj,c1_shading , p1,c1,n1 , model,view,projection);
        vertex_shader(p2_proj,c2_shading , p2,c2,n2 , model,view,projection);



        //convert normalized coordinates to pixel coordinate
        ivec2 u0 = coordinates_to_pixel_index(p0_proj,im.Nx(),im.Ny());
        ivec2 u1 = coordinates_to_pixel_index(p1_proj,im.Nx(),im.Ny());
        ivec2 u2 = coordinates_to_pixel_index(p2_proj,im.Nx(),im.Ny());

        //draw triangle in the screen space
        draw_triangle(im,zbuffer,u0,u1,u2 ,coord_text0,coord_text1,coord_text2,
                      p0_proj.z(),p1_proj.z(),p2_proj.z(),t);

        //render(im, zbuffer, p0, p1, p2, t(coord_text0), text_color1, text_color2, n0, n1, n2, model, view, projection);

    }

}


void vertex_shader(vec3& p_proj,color& c_shading,
                   vec3 const& p,color const& c,vec3 const& n,
                   mat4 const& modelview, mat4 const& view,mat4 const& projection)
{
    /*************************************
    // TO DO
    /*************************************
    // Completez le vertex shader
    */


    vec4 p_homogene = vec4(p.x(), p.y(), p.z(), 1);
    vec4 p_prime = modelview*view*projection*p_homogene;



    p_proj = vec3(p_prime.x()/p_prime.w(), p_prime.y()/p_prime.w(), p_prime.z()/p_prime.w());


    vec3 light_pos= vec3(0.0f,0.0f,0.0f);
    vec3 cam_pos= vec3(0.0f, 0.0f,0.0f);
    vec3 uL= normalized(light_pos-p);
    vec3 t = normalized(cam_pos-p);
    vec3 s = -uL+2*dot(uL,n)*n;

    const float Ka = 0.2f;
    const float Kd = 0.8f;
    const float Ks = 0.6f;
    const int es=128;

    float Ia = Ka;
    float Id  = Kd*clamp(dot(n,uL));
    float Is  = Ks*pow(clamp(dot(s,t)),es);

    color b = color(1.0f, 1.0f, 1.0f);

    //c_shading=c;
    c_shading=(Ia+ Id)*c +Is*b;
}




}

