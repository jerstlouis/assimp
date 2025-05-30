/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2025, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

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
---------------------------------------------------------------------------
*/
#include "UnitTestPCH.h"

#include <assimp/cexport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

class BlendImportMaterials : public ::testing::Test {
public:
    void SetUp() override {
        im = new Assimp::Importer();
    }

    void TearDown() override {
        delete im;
    }

protected:
    Assimp::Importer *im;
};

// ------------------------------------------------------------------------------------------------
TEST_F(BlendImportMaterials, testImportMaterial) {
    const aiScene *pTest = im->ReadFile(ASSIMP_TEST_MODELS_DIR "/BLEND/BlenderMaterial_269.blend", aiProcess_ValidateDataStructure);
    ASSERT_TRUE(pTest != nullptr);
    ASSERT_TRUE(pTest->HasMaterials());

    ASSERT_EQ(1U, pTest->mNumMaterials);

    auto alpha = pTest->mMaterials[0];

#define ASSERT_PROPERTY_EQ(expected, key, var)                             \
    auto var = expected;                                                   \
    ASSERT_EQ(aiReturn_SUCCESS, alpha->Get("$mat.blend." key, 0, 0, var)); \
    ASSERT_EQ(expected, var);

#define ASSERT_PROPERTY_FLOAT_EQ(expected, key, var)                       \
    auto var = expected;                                                   \
    ASSERT_EQ(aiReturn_SUCCESS, alpha->Get("$mat.blend." key, 0, 0, var)); \
    ASSERT_FLOAT_EQ(expected, var);

    ASSERT_PROPERTY_EQ(aiColor3D(0.1f, 0.2f, 0.3f), "diffuse.color", diffuseColor);
    ASSERT_PROPERTY_EQ(0.4f, "diffuse.intensity", diffuseIntensity);
    ASSERT_PROPERTY_EQ(1, "diffuse.shader", diffuseShader);
    ASSERT_PROPERTY_EQ(0, "diffuse.ramp", diffuseRamp);

    ASSERT_PROPERTY_EQ(aiColor3D(0.5f, 0.6f, 0.7f), "specular.color", specularColor);
    ASSERT_PROPERTY_EQ(0.8f, "specular.intensity", specularIntensity);
    ASSERT_PROPERTY_EQ(1, "specular.shader", specularShader);
    ASSERT_PROPERTY_EQ(0, "specular.ramp", specularRamp);
    ASSERT_PROPERTY_EQ(9, "specular.hardness", specularHardness);

    ASSERT_PROPERTY_EQ(1, "transparency.use", transparencyUse);
    ASSERT_PROPERTY_EQ(2, "transparency.method", transparencyMethod);
    ASSERT_PROPERTY_EQ(0.01f, "transparency.alpha", transparencyAlpha);
    ASSERT_PROPERTY_EQ(0.02f, "transparency.specular", transparencySpecular);
    ASSERT_PROPERTY_EQ(0.03f, "transparency.fresnel", transparencyFresnel);
    ASSERT_PROPERTY_EQ(3.14f, "transparency.blend", transparencyBlend);
    ASSERT_PROPERTY_EQ(0.85f, "transparency.ior", transparencyIor);
    ASSERT_PROPERTY_FLOAT_EQ(0.128f, "transparency.filter", transparencyFilter);
    ASSERT_PROPERTY_FLOAT_EQ(1.298f, "transparency.falloff", transparencyFalloff);
    ASSERT_PROPERTY_FLOAT_EQ(0.2376f, "transparency.limit", transparencyLimit);
    ASSERT_PROPERTY_EQ(7, "transparency.depth", transparencyDepth);
    ASSERT_PROPERTY_FLOAT_EQ(0.678f, "transparency.glossAmount", transparencyGlossAmount);
    ASSERT_PROPERTY_FLOAT_EQ(0.208f, "transparency.glossThreshold", transparencyGlossThreshold);
    ASSERT_PROPERTY_EQ(17, "transparency.glossSamples", transparencyGlossSamples);

    ASSERT_PROPERTY_EQ(1, "mirror.use", mirrorUse);
    ASSERT_PROPERTY_FLOAT_EQ(0.28f, "mirror.reflectivity", mirrorReflectivity);
    ASSERT_PROPERTY_EQ(aiColor3D(0.25f, 0.5f, 0.128f), "mirror.color", mirrorColor);
    ASSERT_PROPERTY_FLOAT_EQ(0.256f, "mirror.fresnel", mirrorFresnel);
    ASSERT_PROPERTY_FLOAT_EQ(1.61f, "mirror.blend", mirrorBlend);
    ASSERT_PROPERTY_EQ(12, "mirror.depth", mirrorDepth);
    ASSERT_PROPERTY_FLOAT_EQ(0.4f, "mirror.maxDist", mirrorMaxDist);
    ASSERT_PROPERTY_EQ(1, "mirror.fadeTo", mirrorFadeTo);
    ASSERT_PROPERTY_FLOAT_EQ(0.512f, "mirror.glossAmount", mirrorGlossAmount);
    ASSERT_PROPERTY_FLOAT_EQ(0.18f, "mirror.glossThreshold", mirrorGlossThreshold);
    ASSERT_PROPERTY_EQ(61, "mirror.glossSamples", mirrorGlossSamples);
    ASSERT_PROPERTY_FLOAT_EQ(0.87f, "mirror.glossAnisotropic", mirrorGlossAnisotropic);
}

TEST_F(BlendImportMaterials, testImportMaterialwith2texturesAnd2TexCoordMappings) {
    const aiScene *pTest = im->ReadFile(ASSIMP_TEST_MODELS_DIR "/BLEND/plane_2_textures_2_texcoords_279.blend", aiProcess_ValidateDataStructure);
    ASSERT_TRUE(pTest != nullptr);

    // material has 2 diffuse textures
    ASSERT_TRUE(pTest->HasMaterials());
    EXPECT_EQ(1u, pTest->mNumMaterials);
    const aiMaterial *pMat = pTest->mMaterials[0];
    ASSERT_TRUE(nullptr != pMat);
    ASSERT_EQ(2u, pMat->GetTextureCount(aiTextureType_DIFFUSE));
    aiString aPath;
    aiTextureMapping tm = aiTextureMapping::aiTextureMapping_OTHER;
    aiReturn result = pMat->GetTexture(aiTextureType_DIFFUSE, 0, &aPath, &tm);
    ASSERT_EQ(aiReturn_SUCCESS, result);
    result = pMat->GetTexture(aiTextureType_DIFFUSE, 1, &aPath, &tm);
    ASSERT_EQ(aiReturn_SUCCESS, result);

    // mesh has 2 texturecoord sets
    ASSERT_TRUE(pTest->HasMeshes());
    EXPECT_EQ(1u, pTest->mNumMeshes);
    const aiMesh *pMesh = pTest->mMeshes[0];
    ASSERT_TRUE(nullptr != pMesh);
    ASSERT_TRUE(pMesh->HasTextureCoords(0));
    ASSERT_TRUE(pMesh->HasTextureCoords(1));
}
