/*
Open Asset Import Library (assimp)
----------------------------------------------------------------------

Copyright (c) 2006-2025, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the
following conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/

/** @file IRRMeshLoader.h
 *  @brief Declaration of the .irrMesh (Irrlight Engine Mesh Format)
 *  importer class.
 */
#ifndef AI_IRRMESHLOADER_H_INCLUDED
#define AI_IRRMESHLOADER_H_INCLUDED

#include "IRRShared.h"
#include <assimp/BaseImporter.h>

#ifndef ASSIMP_BUILD_NO_IRRMESH_IMPORTER

namespace Assimp {

// ---------------------------------------------------------------------------
/** IrrMesh importer class.
 *
 * IrrMesh is the native file format of the Irrlight engine and its editor
 * irrEdit. As IrrEdit itself is capable of importing quite many file formats,
 * it might be a good file format for data exchange.
 */
class IRRMeshImporter : public BaseImporter, public IrrlichtBase {
public:
    /// @brief The class constructor.
    IRRMeshImporter() = default;

    /// @brief The class destructor.
    ~IRRMeshImporter() override = default;

    // -------------------------------------------------------------------
    /** Returns whether the class can handle the format of the given file.
     *  See BaseImporter::CanRead() for details.
     */
    bool CanRead(const std::string &pFile, IOSystem *pIOHandler,
            bool checkSig) const override;

protected:
    // -------------------------------------------------------------------
    /** Return importer meta information.
     * See #BaseImporter::GetInfo for the details
     */
    const aiImporterDesc *GetInfo() const override;

    // -------------------------------------------------------------------
    /** Imports the given file into the given scene structure.
     * See BaseImporter::InternReadFile() for details
     */
    void InternReadFile(const std::string &pFile, aiScene *pScene,
            IOSystem *pIOHandler) override;

private:
    enum class VertexFormat {
        standard = 0, // "standard" - also noted as 'normal' format elsewhere
        t2coord = 1, // "2tcoord" - standard + 2 UV maps
        tangent = 2, // "tangents" - standard + tangents and bitangents
    };

    void ParseBufferVertices(const char *sz, const char *end, VertexFormat vertexFormat,
            std::vector<aiVector3D> &vertices, std::vector<aiVector3D> &normals,
            std::vector<aiVector3D> &tangents, std::vector<aiVector3D> &bitangents,
            std::vector<aiVector3D> &UVs, std::vector<aiVector3D> &UV2s,
            std::vector<aiColor4D> &colors, bool &useColors);
};

} // end of namespace Assimp

#endif // ASSIMP_BUILD_NO_IRRMESH_IMPORTER

#endif // AI_IRRMESHIMPORTER_H_INC
