#include "ImplicitSurface/ImplicitSurfaceMesh.hpp"
#include "ImplicitSurface/MarchingCubes/Polygonizer.hpp"

#include <CGAL/Surface_mesh_default_triangulation_3.h>
#include <CGAL/Complex_2_in_triangulation_3.h>
#include <CGAL/make_surface_mesh.h>
#include <CGAL/Implicit_surface_3.h>
#include <CGAL/IO/facets_in_complex_2_to_triangle_mesh.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/compute_normal.h>

#include <QDebug>

#include <functional>
#include <array>

ImplicitSurfaceMesh::ImplicitSurfaceMesh(ImplicitFunction f,
  const QVector3D &tlf, const QVector3D &bbr, float cellSize,
  float isovalue)
{
  Polygonizer p{f, tlf, bbr, cellSize, isovalue};
  p.polygonize(this);
}

ImplicitSurfaceMesh::ImplicitSurfaceMesh(ImplicitFunction f,
  const QVector3D &tlf, const QVector3D &bbr, float cellSize,
  GradImplicitFunction fgrad, float isovalue)
{
  Polygonizer p{f, tlf, bbr, cellSize, fgrad, isovalue};
  p.polygonize(this);
}

// ImplicitSurfaceMesh::ImplicitSurfaceMesh(ImplicitFunctionPtr f)
//   :f_{f}
// { 
//   polygonize();
// }

// void ImplicitSurfaceMesh::polygonize()
// {
//   using Tr          = CGAL::Surface_mesh_default_triangulation_3;
//   using C2t3        = CGAL::Complex_2_in_triangulation_3<Tr>;
//   using GT          = Tr::Geom_traits;
//   using Sphere_3    = GT::Sphere_3;
//   using Point_3     = GT::Point_3;
//   using Vector_3    = GT::Vector_3;
//   using FT          = GT::FT;
//   using Function    = std::function<FT(Point_3)>;
//   using Surface_3   = CGAL::Implicit_surface_3<GT, Function>;
//   using SurfaceMesh = CGAL::Surface_mesh<Point_3>;
//   using VertexIndex = SurfaceMesh::vertex_index;
//   using FaceIndex   = SurfaceMesh::face_index;
  
//   namespace PMP     = CGAL::Polygon_mesh_processing;

//   // Defining implicit function
//   Function sf = [this](Point_3 p) {
//     return f_->apply(QVector3D(p.x(), p.y(), p.z()));
//   };

//   Tr tr;                // 3D-Delaunay triangulation
//   C2t3 c2t3{tr};        // 2D-complex in 3D-Delaunay triangulation  

//   // defining the surface
//   Surface_3 surface{sf,           // pointer to function
//     Sphere_3(CGAL::ORIGIN, 2.0)}; // bounding box
  
//   CGAL::Surface_mesh_default_criteria_3<Tr> 
//     criteria{30.,   // angular bound
//               0.1,  // radius bound 
//               0.1}; // distance bound
  
//   // meshing surface
//   CGAL::make_surface_mesh(c2t3, surface, criteria, CGAL::Non_manifold_tag());
  
//   // Create Surface Mesh (Half-Edge data structure)
//   SurfaceMesh sm;
//   CGAL::facets_in_complex_2_to_triangle_mesh(c2t3, sm);

//   // Compute normals
//   SurfaceMesh::Property_map<VertexIndex, Vector_3> vnormals = 
//     sm.add_property_map<VertexIndex, Vector_3>("v:normals", CGAL::NULL_VECTOR).first;   
//   PMP::compute_vertex_normals(sm, vnormals);

//   coords_.reserve(sm.number_of_vertices());
//   normals_.reserve(sm.number_of_vertices());

//   // extract mesh suitable for openGL
//   // for (VertexIndex vi : sm.vertices()) {
//   //   Point_3 vcoords = sm.point(vi);
//   //   coords_.append(QVector3D{ vcoords.x(), vcoords.y(), vcoords.z() });
//   // }

//   for (FaceIndex f : sm.faces()) {
//     for (VertexIndex vi : vertices_around_face(sm.halfedge(f), sm)) {
//       Point_3 vcoords = sm.point(vi);
//       Vector_3 vnormal = vnormals[vi];
      
//       coords_.append(QVector3D{vcoords.x(), vcoords.y(), vcoords.z()});
//       normals_.append(QVector3D{vnormal.x(), vnormal.y(), vnormal.z()});

//       indices_.append(vi);
//     }
//  }
//}