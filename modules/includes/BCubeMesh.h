/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef BCUBEMESH_H
#define BCUBEMESH_H

#include <BoxE/BoxECore>

#include <BackGenEngine/brenderablecomponent.h>
#include <BackGenEngine/bmodulesheader.h>
#include "../abstractmesh/BAbstractMesh.h"
#include <BackGenEngine/bvertexbuffer.h>

class BCubeMesh : public BAbstractMesh {
        BGE_RTTI_DECLARATION
    public:
        BCubeMesh ( BackGenEngine::BScene *pc_scene );
        virtual ~BCubeMesh();

        virtual BoxE::Core::BAsciiString getName() const {
            return "CubeMesh";
        }

        void setSize ( int size );
        int getSize() const;

        virtual BackGenEngine::BVertexBuffer *getVertexBuffer();
        virtual int *getIndexBuffer();

        virtual BAbstractComponent *duplicate() const;
    private:
        BackGenEngine::BVertexBuffer VertexBuffer;
        int *aIndexBuffer;
        int Size;
};


#endif /* BCUBEMESH_H */
