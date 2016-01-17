/**************************************************************************
 *
 * Copyright 2011 Jose Fonseca
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/


#include <stdio.h>

#include <iostream>

#include "state_writer.hpp"
#include "com_ptr.hpp"
#include "d3d9imports.hpp"
#include "d3dshader.hpp"
#include "d3dstate.hpp"


namespace d3dstate {


template< class T >
inline void
dumpShader(StateWriter &writer, const char *name, T *pShader) {
    if (!pShader) {
        return;
    }

    HRESULT hr;

    UINT SizeOfData = 0;

    hr = pShader->GetFunction(NULL, &SizeOfData);
    if (SUCCEEDED(hr)) {
        void *pData;
        pData = malloc(SizeOfData);
        if (pData) {
            hr = pShader->GetFunction(pData, &SizeOfData);
            if (SUCCEEDED(hr)) {
                com_ptr<IDisassemblyBuffer> pDisassembly;
                hr = DisassembleShader((const DWORD *)pData, &pDisassembly);
                if (SUCCEEDED(hr)) {
                    writer.beginMember(name);
                    writer.writeString((const char *)pDisassembly->GetBufferPointer() /*, pDisassembly->GetBufferSize() */);
                    writer.endMember();
                }

            }
            free(pData);
        }
    }
}

static void
dumpShaders(StateWriter &writer, IDirect3DDevice9 *pDevice)
{
    writer.beginMember("shaders");

    HRESULT hr;
    writer.beginObject();

    com_ptr<IDirect3DVertexShader9> pVertexShader;
    hr = pDevice->GetVertexShader(&pVertexShader);
    if (SUCCEEDED(hr)) {
        dumpShader<IDirect3DVertexShader9>(writer, "vertex", pVertexShader);
    }

    com_ptr<IDirect3DPixelShader9> pPixelShader;
    hr = pDevice->GetPixelShader(&pPixelShader);
    if (SUCCEEDED(hr)) {
        dumpShader<IDirect3DPixelShader9>(writer, "pixel", pPixelShader);
    }

    writer.endObject();
    writer.endMember(); // shaders
}

void
dumpDevice(StateWriter &writer, IDirect3DDevice9 *pDevice)
{
    /* TODO */
    writer.beginMember("parameters");
    writer.beginObject();
    DWORD rsvalue;
    rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ZENABLE,&rsvalue);
writer.beginMember("D3DRS_ZENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_FILLMODE,&rsvalue);
writer.beginMember("D3DRS_FILLMODE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_SHADEMODE,&rsvalue);
writer.beginMember("D3DRS_SHADEMODE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ZWRITEENABLE,&rsvalue);
writer.beginMember("D3DRS_ZWRITEENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ALPHATESTENABLE,&rsvalue);
writer.beginMember("D3DRS_ALPHATESTENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_LASTPIXEL,&rsvalue);
writer.beginMember("D3DRS_LASTPIXEL");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_SRCBLEND,&rsvalue);
writer.beginMember("D3DRS_SRCBLEND");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_DESTBLEND,&rsvalue);
writer.beginMember("D3DRS_DESTBLEND");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_CULLMODE,&rsvalue);
writer.beginMember("D3DRS_CULLMODE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ZFUNC,&rsvalue);
writer.beginMember("D3DRS_ZFUNC");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ALPHAREF,&rsvalue);
writer.beginMember("D3DRS_ALPHAREF");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ALPHAFUNC,&rsvalue);
writer.beginMember("D3DRS_ALPHAFUNC");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_DITHERENABLE,&rsvalue);
writer.beginMember("D3DRS_DITHERENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ALPHABLENDENABLE,&rsvalue);
writer.beginMember("D3DRS_ALPHABLENDENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_FOGENABLE,&rsvalue);
writer.beginMember("D3DRS_FOGENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_SPECULARENABLE,&rsvalue);
writer.beginMember("D3DRS_SPECULARENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_FOGCOLOR,&rsvalue);
writer.beginMember("D3DRS_FOGCOLOR");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_FOGTABLEMODE,&rsvalue);
writer.beginMember("D3DRS_FOGTABLEMODE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_FOGSTART,&rsvalue);
writer.beginMember("D3DRS_FOGSTART");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_FOGEND,&rsvalue);
writer.beginMember("D3DRS_FOGEND");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_FOGDENSITY,&rsvalue);
writer.beginMember("D3DRS_FOGDENSITY");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_RANGEFOGENABLE,&rsvalue);
writer.beginMember("D3DRS_RANGEFOGENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_STENCILENABLE,&rsvalue);
writer.beginMember("D3DRS_STENCILENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_STENCILFAIL,&rsvalue);
writer.beginMember("D3DRS_STENCILFAIL");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_STENCILZFAIL,&rsvalue);
writer.beginMember("D3DRS_STENCILZFAIL");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_STENCILPASS,&rsvalue);
writer.beginMember("D3DRS_STENCILPASS");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_STENCILFUNC,&rsvalue);
writer.beginMember("D3DRS_STENCILFUNC");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_STENCILREF,&rsvalue);
writer.beginMember("D3DRS_STENCILREF");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_STENCILMASK,&rsvalue);
writer.beginMember("D3DRS_STENCILMASK");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_STENCILWRITEMASK,&rsvalue);
writer.beginMember("D3DRS_STENCILWRITEMASK");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_TEXTUREFACTOR,&rsvalue);
writer.beginMember("D3DRS_TEXTUREFACTOR");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP0,&rsvalue);
writer.beginMember("D3DRS_WRAP0");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP1,&rsvalue);
writer.beginMember("D3DRS_WRAP1");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP2,&rsvalue);
writer.beginMember("D3DRS_WRAP2");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP3,&rsvalue);
writer.beginMember("D3DRS_WRAP3");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP4,&rsvalue);
writer.beginMember("D3DRS_WRAP4");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP5,&rsvalue);
writer.beginMember("D3DRS_WRAP5");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP6,&rsvalue);
writer.beginMember("D3DRS_WRAP6");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP7,&rsvalue);
writer.beginMember("D3DRS_WRAP7");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_CLIPPING,&rsvalue);
writer.beginMember("D3DRS_CLIPPING");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_LIGHTING,&rsvalue);
writer.beginMember("D3DRS_LIGHTING");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_AMBIENT,&rsvalue);
writer.beginMember("D3DRS_AMBIENT");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_FOGVERTEXMODE,&rsvalue);
writer.beginMember("D3DRS_FOGVERTEXMODE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_COLORVERTEX,&rsvalue);
writer.beginMember("D3DRS_COLORVERTEX");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_LOCALVIEWER,&rsvalue);
writer.beginMember("D3DRS_LOCALVIEWER");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_NORMALIZENORMALS,&rsvalue);
writer.beginMember("D3DRS_NORMALIZENORMALS");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,&rsvalue);
writer.beginMember("D3DRS_DIFFUSEMATERIALSOURCE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_SPECULARMATERIALSOURCE,&rsvalue);
writer.beginMember("D3DRS_SPECULARMATERIALSOURCE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_AMBIENTMATERIALSOURCE,&rsvalue);
writer.beginMember("D3DRS_AMBIENTMATERIALSOURCE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_EMISSIVEMATERIALSOURCE,&rsvalue);
writer.beginMember("D3DRS_EMISSIVEMATERIALSOURCE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_VERTEXBLEND,&rsvalue);
writer.beginMember("D3DRS_VERTEXBLEND");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_CLIPPLANEENABLE,&rsvalue);
writer.beginMember("D3DRS_CLIPPLANEENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_POINTSIZE,&rsvalue);
writer.beginMember("D3DRS_POINTSIZE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_POINTSIZE_MIN,&rsvalue);
writer.beginMember("D3DRS_POINTSIZE_MIN");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_POINTSPRITEENABLE,&rsvalue);
writer.beginMember("D3DRS_POINTSPRITEENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_POINTSCALEENABLE,&rsvalue);
writer.beginMember("D3DRS_POINTSCALEENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_POINTSCALE_A,&rsvalue);
writer.beginMember("D3DRS_POINTSCALE_A");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_POINTSCALE_B,&rsvalue);
writer.beginMember("D3DRS_POINTSCALE_B");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_POINTSCALE_C,&rsvalue);
writer.beginMember("D3DRS_POINTSCALE_C");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_MULTISAMPLEANTIALIAS,&rsvalue);
writer.beginMember("D3DRS_MULTISAMPLEANTIALIAS");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_MULTISAMPLEMASK,&rsvalue);
writer.beginMember("D3DRS_MULTISAMPLEMASK");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_PATCHEDGESTYLE,&rsvalue);
writer.beginMember("D3DRS_PATCHEDGESTYLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_DEBUGMONITORTOKEN,&rsvalue);
writer.beginMember("D3DRS_DEBUGMONITORTOKEN");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_POINTSIZE_MAX,&rsvalue);
writer.beginMember("D3DRS_POINTSIZE_MAX");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE,&rsvalue);
writer.beginMember("D3DRS_INDEXEDVERTEXBLENDENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_COLORWRITEENABLE,&rsvalue);
writer.beginMember("D3DRS_COLORWRITEENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_TWEENFACTOR,&rsvalue);
writer.beginMember("D3DRS_TWEENFACTOR");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_BLENDOP,&rsvalue);
writer.beginMember("D3DRS_BLENDOP");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_POSITIONDEGREE,&rsvalue);
writer.beginMember("D3DRS_POSITIONDEGREE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_NORMALDEGREE,&rsvalue);
writer.beginMember("D3DRS_NORMALDEGREE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_SCISSORTESTENABLE,&rsvalue);
writer.beginMember("D3DRS_SCISSORTESTENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_SLOPESCALEDEPTHBIAS,&rsvalue);
writer.beginMember("D3DRS_SLOPESCALEDEPTHBIAS");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ANTIALIASEDLINEENABLE,&rsvalue);
writer.beginMember("D3DRS_ANTIALIASEDLINEENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_MINTESSELLATIONLEVEL,&rsvalue);
writer.beginMember("D3DRS_MINTESSELLATIONLEVEL");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_MAXTESSELLATIONLEVEL,&rsvalue);
writer.beginMember("D3DRS_MAXTESSELLATIONLEVEL");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ADAPTIVETESS_X,&rsvalue);
writer.beginMember("D3DRS_ADAPTIVETESS_X");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ADAPTIVETESS_Y,&rsvalue);
writer.beginMember("D3DRS_ADAPTIVETESS_Y");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ADAPTIVETESS_Z,&rsvalue);
writer.beginMember("D3DRS_ADAPTIVETESS_Z");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ADAPTIVETESS_W,&rsvalue);
writer.beginMember("D3DRS_ADAPTIVETESS_W");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_ENABLEADAPTIVETESSELLATION,&rsvalue);
writer.beginMember("D3DRS_ENABLEADAPTIVETESSELLATION");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_TWOSIDEDSTENCILMODE,&rsvalue);
writer.beginMember("D3DRS_TWOSIDEDSTENCILMODE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_CCW_STENCILFAIL,&rsvalue);
writer.beginMember("D3DRS_CCW_STENCILFAIL");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_CCW_STENCILZFAIL,&rsvalue);
writer.beginMember("D3DRS_CCW_STENCILZFAIL");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_CCW_STENCILPASS,&rsvalue);
writer.beginMember("D3DRS_CCW_STENCILPASS");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_CCW_STENCILFUNC,&rsvalue);
writer.beginMember("D3DRS_CCW_STENCILFUNC");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_COLORWRITEENABLE1,&rsvalue);
writer.beginMember("D3DRS_COLORWRITEENABLE1");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_COLORWRITEENABLE2,&rsvalue);
writer.beginMember("D3DRS_COLORWRITEENABLE2");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_COLORWRITEENABLE3,&rsvalue);
writer.beginMember("D3DRS_COLORWRITEENABLE3");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_BLENDFACTOR,&rsvalue);
writer.beginMember("D3DRS_BLENDFACTOR");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE,&rsvalue);
writer.beginMember("D3DRS_SRGBWRITEENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_DEPTHBIAS,&rsvalue);
writer.beginMember("D3DRS_DEPTHBIAS");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP8,&rsvalue);
writer.beginMember("D3DRS_WRAP8");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP9,&rsvalue);
writer.beginMember("D3DRS_WRAP9");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP10,&rsvalue);
writer.beginMember("D3DRS_WRAP10");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP11,&rsvalue);
writer.beginMember("D3DRS_WRAP11");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP12,&rsvalue);
writer.beginMember("D3DRS_WRAP12");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP13,&rsvalue);
writer.beginMember("D3DRS_WRAP13");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP14,&rsvalue);
writer.beginMember("D3DRS_WRAP14");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_WRAP15,&rsvalue);
writer.beginMember("D3DRS_WRAP15");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_SEPARATEALPHABLENDENABLE,&rsvalue);
writer.beginMember("D3DRS_SEPARATEALPHABLENDENABLE");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_SRCBLENDALPHA,&rsvalue);
writer.beginMember("D3DRS_SRCBLENDALPHA");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_DESTBLENDALPHA,&rsvalue);
writer.beginMember("D3DRS_DESTBLENDALPHA");
writer.writeInt(rsvalue);
writer.endMember();

rsvalue = 0xffffffff;
pDevice->GetRenderState(D3DRS_BLENDOPALPHA,&rsvalue);
writer.beginMember("D3DRS_BLENDOPALPHA");
writer.writeInt(rsvalue);
writer.endMember();


writer.beginMember("Viewport");
{
    writer.beginObject();
    D3DVIEWPORT9 vp;
    pDevice->GetViewport(&vp);
    writer.writeIntMember("X",vp.X);
    writer.writeIntMember("Y",vp.Y);
    writer.writeIntMember("Width",vp.Width);
    writer.writeIntMember("Height",vp.Height);
    writer.writeIntMember("MinZ",vp.MinZ);
    writer.writeIntMember("MaxZ",vp.MaxZ);
    writer.endObject();
}

writer.endMember();
    writer.endObject();
    writer.endMember(); // parameters

    dumpShaders(writer, pDevice);

    dumpTextures(writer, pDevice);

    dumpFramebuffer(writer, pDevice);
}

void
dumpDevice(StateWriter &writer, IDirect3DSwapChain9 *pSwapChain)
{
    com_ptr<IDirect3DDevice9> pDevice;
    HRESULT hr = pSwapChain->GetDevice(&pDevice);
    if (SUCCEEDED(hr)) {
        dumpDevice(writer, pDevice);
    }
}


} /* namespace d3dstate */
