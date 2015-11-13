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



#pragma once
#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

namespace cpe
{

struct image;
struct color;
struct image_zbuffer;
class vec3;
class mat4;
class mesh;
class vec2;
struct texture;


/** Emulation of a vertex_shader
 * \param p_proj: the vertex position after projection on the camera (output parameter)
 * \param c_shading: the color of the vertex after shading (output parameter)
 * \param model: the model matrix (deformation of the object)
 * \param view: the camera position
 * \param projection: the camera projection matrix
*/
void vertex_shader(vec3& p_proj,color& c_shading,
                   vec3 const& p,color const& c,vec3 const& n,
                   mat4 const& model,mat4 const& view,mat4 const& projection);

/** Render a triangle on an image
 * \param image: the destination image (output parameter)
 * \param zbuffer: the current zbuffer (in/out parameter)
 * \param (p0,p1,p2) the triangle coordinates
 * \param (c0,c1,c2) the vertices color
 * \param (n0,n1,n2) the vertices normals
 * \param model: the model matrix (deformation of the object)
 * \param view: the camera position
 * \param projection: the camera projection matrix
*/
void render(image& im,image_zbuffer& zbuffer,
            vec3 const& p0,vec3 const& p1,vec3 const& p2,
            color const& c0,color const& c1,color const& c2,
            vec3 const& n0,vec3 const& n1,vec3 const& n2,
            mat4 const& model,mat4 const& view,mat4 const& projection);

void render(image& im,image_zbuffer& zbuffer,
            vec3 const& p0,vec3 const& p1,vec3 const& p2,
            color const& c0,color const& c1,color const& c2,
            vec3 const& n0,vec3 const& n1,vec3 const& n2,
            mat4 const& model,mat4 const& view,mat4 const& projection);

void render(image& im, image_zbuffer& zbuffer, mesh const& m,
            mat4 const& model, mat4 const& view, mat4 const& projection, texture &t);
/** Render a mesh
 * \param image: the destination image (output parameter)
 * \param zbuffer: the current zbuffer (in/out parameter)
 * \param mesh: the mesh to render
 * \param model: the model matrix (deformation of the object)
 * \param view: the camera position
 * \param projection: the camera projection matrix
*/
void render(image& im,image_zbuffer& zbuffer,mesh const& m,
            mat4 const& model,mat4 const& view,mat4 const& projection);






}

#endif
