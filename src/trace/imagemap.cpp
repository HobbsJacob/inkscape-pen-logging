// SPDX-License-Identifier: GPL-2.0-or-later
/** @file
 * TODO: insert short description here
 *//*
 * Authors: see git history
 *
 * Copyright (C) 2018 Authors
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */
#include <cstdlib>

#include "imagemap.h"

#include "io/sys.h"

/*#########################################################################
### G R A Y   M A P
#########################################################################*/


static void gSetPixel(GrayMap *me, int x, int y, unsigned long val)
{
    if (val>765)
        val = 765;
    unsigned long *pix = me->rows[y] + x;
    *pix = val;
}

static unsigned long gGetPixel(GrayMap *me, int x, int y)
{
    unsigned long *pix = me->rows[y] + x;
    return *pix;
}


static int gWritePPM(GrayMap *me, char *fileName)
{
    if (!fileName)
        return FALSE;

    FILE *f = fopen(fileName, "wb");
    if (!f)
        return FALSE;

    fprintf(f, "P6 %d %d 255\n", me->width, me->height);

    for (int y=0 ; y<me->height; y++)
        {
        for (int x=0 ; x<me->width ; x++)
            {
            unsigned long pix  = me->getPixel(me, x, y) / 3;
            unsigned char pixb = (unsigned char) (pix & 0xff);
            fputc(pixb, f);
            fputc(pixb, f);
            fputc(pixb, f);
            }
        }
    fclose(f);
    return TRUE;
}


static void gDestroy(GrayMap *me)
{
    if (me->pixels)
        free(me->pixels);
    if (me->rows)
        free(me->rows);
    free(me);
}

GrayMap *GrayMapCreate(int width, int height)
{

    GrayMap *me = (GrayMap *)malloc(sizeof(GrayMap));
    if (!me)
        return nullptr;

    /** methods **/
    me->setPixel    = gSetPixel;
    me->getPixel    = gGetPixel;
    me->writePPM    = gWritePPM;
    me->destroy     = gDestroy;

    /** fields **/
    me->width  = width;
    me->height = height;
    me->pixels = (unsigned long *)
              malloc(sizeof(unsigned long) * width * height);
    if (!me->pixels)
        {
        g_warning("GrayMapCreate: can not allocate memory for %d x %d image.", width, height);
        free(me);
        return nullptr;
        }
    me->rows = (unsigned long **)
              malloc(sizeof(unsigned long *) *  height);
    if (!me->rows)
        {
        g_warning("GrayMapCreate: can not allocate memory for index of %d x %d image.", width, height);
        free(me->pixels);
        free(me);
        return nullptr;
        }

    unsigned long *row = me->pixels;
    for (int i=0 ; i<height ; i++)
        {
        me->rows[i] = row;
        row += width;
        }

    return me;
}



/*#########################################################################
### R G B      M A P
#########################################################################*/



static void rSetPixel(RgbMap *me, int x, int y, int r, int g, int b)
{
    RGB *pix = me->rows[y] + x;
    pix->r = r;
    pix->g = g;
    pix->b = b;
}

static void rSetPixelRGB(RgbMap *me, int x, int y, RGB rgb)
{
    RGB *pix = me->rows[y] + x;
    *pix = rgb;
}

static RGB rGetPixel(RgbMap *me, int x, int y)
{
    RGB *pix = me->rows[y] + x;
    return *pix;
}



static int rWritePPM(RgbMap *me, char *fileName)
{
    if (!fileName)
        return FALSE;

    FILE *f = fopen(fileName, "wb");
    if (!f)
        return FALSE;

    fprintf(f, "P6 %d %d 255\n", me->width, me->height);

    for (int y=0 ; y<me->height; y++)
        {
        for (int x=0 ; x<me->width ; x++)
            {
            RGB rgb = me->getPixel(me, x, y);
            fputc(rgb.r, f);
            fputc(rgb.g, f);
            fputc(rgb.b, f);
            }
        }
    fclose(f);
    return TRUE;
}


static void rDestroy(RgbMap *me)
{
    if (me->pixels){
        free(me->pixels);
    }
    if (me->rows){
        free(me->rows);
    }
    free(me);
}



RgbMap *RgbMapCreate(int width, int height)
{

    RgbMap *me = (RgbMap *)malloc(sizeof(RgbMap));
    if (!me){
        return nullptr;
    }
    
    /** methods **/
    me->setPixel    = rSetPixel;
    me->setPixelRGB = rSetPixelRGB;
    me->getPixel    = rGetPixel;
    me->writePPM    = rWritePPM;
    me->destroy     = rDestroy;


    /** fields **/
    me->width  = width;
    me->height = height;
    me->pixels = (RGB *) malloc(sizeof(RGB) * width * height);
    if (!me->pixels){
        g_warning("RgbMapCreate: can not allocate memory for %d x %d image.", width, height);
        free(me);
        return nullptr;
    }
    me->rows = (RGB **) malloc(sizeof(RGB *) * height);
    if (!me->rows){
        g_warning("RgbMapCreate: can not allocate memory for index of %d x %d image.", width, height);
        free(me->pixels); //allocated as me->pixels is not NULL here: see previous check
        free(me);
        return nullptr;
    }

    RGB *row = me->pixels;
    for (int i=0 ; i<height ; i++){
        me->rows[i] = row;
        row += width;
    }

    return me;
}




/*#########################################################################
### I N D E X E D      M A P
#########################################################################*/



static void iSetPixel(IndexedMap *me, int x, int y, unsigned int index)
{
    unsigned int *pix = me->rows[y] + x;
    *pix = index;
}


static unsigned int iGetPixel(IndexedMap *me, int x, int y)
{
    unsigned int *pix = me->rows[y] + x;
    return *pix;
}

static RGB iGetPixelValue(IndexedMap *me, int x, int y)
{
    unsigned int *pix = me->rows[y] + x;
    RGB rgb = me->clut[((*pix)&0xff)];
    return rgb;
}



static int iWritePPM(IndexedMap *me, char *fileName)
{
    if (!fileName)
        return FALSE;

    FILE *f = fopen(fileName, "wb");
    if (!f)
        return FALSE;

    fprintf(f, "P6 %d %d 255\n", me->width, me->height);

    for (int y=0 ; y<me->height; y++)
        {
        for (int x=0 ; x<me->width ; x++)
            {
            RGB rgb = me->getPixelValue(me, x, y);
            fputc(rgb.r, f);
            fputc(rgb.g, f);
            fputc(rgb.b, f);
            }
        }
    fclose(f);
    return TRUE;
}


static void iDestroy(IndexedMap *me)
{
    if (me->pixels){
        free(me->pixels);
    }
    if (me->rows){
        free(me->rows);
    }
    free(me);
}



IndexedMap *IndexedMapCreate(int width, int height)
{

    IndexedMap *me = (IndexedMap *)malloc(sizeof(IndexedMap));
    if (!me)
        return nullptr;

    /** methods **/
    me->setPixel      = iSetPixel;
    me->getPixel      = iGetPixel;
    me->getPixelValue = iGetPixelValue;
    me->writePPM      = iWritePPM;
    me->destroy       = iDestroy;


    /** fields **/
    me->width  = width;
    me->height = height;
    me->pixels = (unsigned int *) malloc(sizeof(unsigned int) * width * height);
    if (!me->pixels){
        g_warning("IndexedMapCreate: can not allocate memory for %d x %d image.", width, height);
        free(me);
        return nullptr;
    }
    me->rows = (unsigned int **) malloc(sizeof(unsigned int *) * height);
    if (!me->rows){
        g_warning("IndexedMapCreate: can not allocate memory for index of %d x %d image.", width, height);
        free(me->pixels); //allocated as me->pixels is not NULL here: see previous check
        free(me);
        return nullptr;
    }

    unsigned int *row = me->pixels;
    for (int i=0 ; i<height ; i++){
        me->rows[i] = row;
        row += width;
    }

    me->nrColors = 0;

    RGB rgb;
    rgb.r = rgb.g = rgb.b = 0;
    for (auto & i : me->clut){
        i = rgb;
    }

    return me;
}






/*#########################################################################
### E N D    O F    F I L E
#########################################################################*/
