# ##### BEGIN GPL LICENSE BLOCK #####
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software Foundation,
#  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# ##### END GPL LICENSE BLOCK #####

# <pep8-80 compliant>

# This file is a modification of the raw mesh plugin that ships with Blender 2.6
# Modified by: ME Chamberlain

"""
This script exports a Mesh to a RAW triangle format file.

The raw triangle format is very simple; it has no verts or faces lists.
It's just a simple binary file with the following format:
32bit unsigned int - number of vertices
3 32bit floats - vertex position
3 32bit floats - vertex normal
3 32bit floats - vertex color
2 32bit floats - vertex uv
This is repeated for each vertex. The data is not stored as a triangle strip,
so the first triangle is defined by vertex 0, 1 and 2 and the second triangle by
vertex 3, 4 and 5.

Usage:
Execute this script from the "File->Export" menu. You can select
whether modifiers should be applied and if the mesh is triangulated.

"""

import struct

import bpy


def faceToTriangles(face):
    triangles = []
    if len(face) == 4:
        triangles.append([face[0], face[1], face[2]])
        triangles.append([face[2], face[3], face[0]])
    else:
        triangles.append(face)

    return triangles

def buildLine(mesh, matrix, vertex_colors, uv_textures, face_index, idx, verti):
  """ Returns a list containing a vertex (3 tuple of floats), normal (3 tuple of floats)
      vertex color (3 tuple of floats) and uv (2 tuple of floats).
  """
  line_data = []
  # Append vertex
  line_data.append((matrix * mesh.vertices[verti].co)[:])
  # Vertex normal
  line_data.append((matrix.to_quaternion() * mesh.vertices[verti].normal)[:])
  # Vertex color
  if vertex_colors == None:
    line_data.append([0.5, 0.5, 0.5])
  else:
    line_data.append(getattr(vertex_colors[face_index], 'color%d' % (idx + 1))[:])
  # UV
  if uv_textures == None:
    line_data.append([0, 0])
  else:
    line_data.append(uv_textures[face_index].uv_raw[idx*2:idx*2+2])
  return line_data

def lineDataToString(line_data):
    return " ".join([("%.6f %.6f %.6f" % tuple(line_data[0])), ("%.6f %.6f %.6f" % tuple(line_data[1])), ("%.6f %.6f %.6f" % tuple(line_data[2])), ("%.6f %.6f" % tuple(line_data[3])), "\n"])

def write(filepath,
          applyMods=True,
          triangulate=True,
          ):

    scene = bpy.context.scene
    
    mesh_data = []
    for obj in bpy.context.selected_objects:
        if applyMods or obj.type != 'MESH':
            try:
                me = obj.to_mesh(scene, True, "PREVIEW")
            except:
                me = None
            is_tmp_mesh = True
        else:
            me = obj.data
            is_tmp_mesh = False

        if me is not None:
            matrix = obj.matrix_world.copy()
            try:
              vertex_colors = me.tessface_vertex_colors[0].data
            except IndexError as e:
              vertex_colors = None
            try:
              uv_textures = me.tessface_uv_textures[0].data
            except IndexError as e:
              uv_textures = None
            for face in me.tessfaces:
                num_vertices = len(face.vertices)
                if num_vertices > 3 and triangulate:
                  for idx, verti in enumerate(face.vertices[0:3]):
                    mesh_data.append(buildLine(me, matrix, vertex_colors, uv_textures, face.index, idx, verti))
                  for idx, verti in enumerate([face.vertices[i] for i in [3, 0, 2]]):
                    mesh_data.append(buildLine(me, matrix, vertex_colors, uv_textures, face.index, idx, verti))
                else:
                  for idx, verti in enumerate(face.vertices):
                    mesh_data.append(buildLine(me, matrix, vertex_colors, uv_textures, face.index, idx, verti))
            if is_tmp_mesh:
                bpy.data.meshes.remove(me)

    # write the faces to a file
    file = open(filepath, "wb")
    #file.write("%d\n" % len(mesh_data))
    file.write(struct.pack('<I', len(mesh_data)))
    for line_data in mesh_data:
      #file.write(lineDataToString(line_data))
      for list_of_floats in line_data:
        for value in list_of_floats:
          file.write(struct.pack('<f',value))
    file.close()
