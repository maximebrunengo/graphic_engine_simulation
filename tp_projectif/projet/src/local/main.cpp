
/** TP 5ETI IMI- CPE Lyon - 2015-2016 */



#include "lib/common/error_handling.hpp"

#include "discrete/bresenham.hpp"
#include "discrete/line_discrete.hpp"
#include "discrete/line_interpolation_parameter.hpp"
#include "image/image.hpp"
#include "image/drawer.hpp"
#include "discrete/triangle_scanline.hpp"
#include "image/image_zbuffer.hpp"
#include "lib/mesh/mesh.hpp"
#include "lib/mesh/mesh_io.hpp"
#include "render_engine/render_engine.hpp"
#include "lib/3d/mat4.hpp"
#include "lib/3d/mat3.hpp"
#include "image/texture.hpp"

#include <iostream>
#include <fstream>
#include <cmath>



using namespace cpe;

int main(int argc,char *argv[])
{

    std::cout<<"***********************"<<std::endl;
    std::cout<<"run "<<argv[0]<<" with "<<argc-1<<" parameters ... \n"<<std::endl;


    try
    {
        int const Nx = 1000;
        int const Ny = 1000;

        image im(Nx,Ny);
        im.fill({1.0f,1.0f,1.0f});

        //image_zbuffer zbuffer(Nx,Ny);
        //zbuffer.fill(1.0f);

        //im(1,1) = color(0.0f,0.0f,0.0f);

/*
        ivec2 const p1(95,25);
        ivec2 const p2(95,85);
        ivec2 const p3(15,15);
        color c0(0.0f,0.0f,1.0f);
        color c1(0.0f,1.0f,0.0f);
        color c2(1.0f,0.0f,0.0f);
        float z1 = -1.0f;


        ivec2 const p4(5,25);
        ivec2 const p5(5,85);
        ivec2 const p6(85,15);
        color c3(0.0f,0.8f,0.5f);
        color c4(0.8f,0.5f,0.0f);
        color c5(0.5f,0.0f,0.8f);

        float z2 = 0.9f;

        /*float z0 = 0.0f;

        ivec2 const p7(5,1);
        ivec2 const p8(5,24);
        ivec2 const p9(39,24);
        float z3 = 0.0f;


        ivec2 const p10(1,12);
        ivec2 const p11(39,12);
        float z4 = -1.0f;
        float z5 = 1.0f;
        */


        //draw_line(im, zbuffer, p10, p11, c0, c0, z4, z5);
        //draw_triangle(im, zbuffer, p7, p8, p9, c1, c1, c1, z3, z3, z3);
        //draw_triangle(im, zbuffer, p1, p2, p3, c0, c1, c2, z2, z2, z1);
        //draw_triangle(im, zbuffer, p4, p5, p6, c3, c4, c5, z2, z2, z1);


        image_zbuffer zbuffer(Nx,Ny);
        zbuffer.fill(1.0f);
        /*
        vec3 p0 = vec3(-0.5f, -0.2f, -1.0f);
        vec3 p1 = vec3(0.9f, 0.5f, -5.0f);
        vec3 p2 = vec3(-0.5f, -0.5f, -1.0f);

        vec3 n0 = cross(p1-p0,p2-p0);
        vec3 n1 = cross(p0-p1,p2-p1);
        vec3 n2 = cross(p0-p2,p1-p2);

        color c0(0.0f,0.0f,0.0f);
        color c1(1.0f,0.0f,0.0f);
        color c2(1.0f,1.0f,0.0f);

        render(im, zbuffer, p0, p1, p2, c0, c1, c2, n0, n1, n2, model, view, projection);
        */
        mat4 model; //identite
        model.set_identity();
        mat4 view; //identite
        view.set_identity();
        mat4 projection;

        //matrice de projection angle de vue de 60degres
        //image de taille carree
        //sommets visibles entre z=0 et z=20
        projection.set_projection_perspective(60*M_PI/180.0f, 1.0f, 0.1f, 20.0f);
        //chargement du fichier
        mesh m = load_mesh_file("data/dino.obj");
        //applique potentiellement une rotation, translation
        //(scaling possible egalement)

        texture t ;
        t.load("data/dino.ppm");

        m.transform_apply_rotation({0,1,0},-M_PI/4.0f);
        m.transform_apply_translation({0,0,-1.5f});


        m.fill_color({1,1,1}); //applique la couleur blanche a
        //l’ensemble des sommets
        m.fill_normal();
        //calcul automatique des normales

        render(im,zbuffer,m,model,view,projection,t);


        im.save("mon_image.ppm");
    }
    catch(cpe::exception_cpe const& e)
    {


        std::cout<<"**********************************"<<std::endl;
        std::cout<<"**********************************"<<std::endl;
        std::cout<<"Exception found"<<std::endl;
        std::cout<<e.info()<<std::endl;
        std::cout<<"\nSaving backtrace in file backtrace_log.txt"<<std::endl;
        std::cout<<"**********************************"<<std::endl;
        std::cout<<"**********************************"<<std::endl;


        std::ofstream back_file("backtrace_log.txt");
        back_file<<e.info()<<std::endl;
        back_file<<e.info_backtrace();
        back_file.close();

        exit(1);
    }


    std::cout<<"Exit Main"<<std::endl;

    return 0;
}
