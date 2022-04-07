#pragma once
 
static const int NumberOfMatrix4FDoubleBuffers = 60000;
static const int NumberOfVector4FDoubleBuffers = 500000;
static const int NumberOfPointerDoubleBuffers = 150000;

static const int NumberOfGraphicsObjectsColor = 10;
static const int NumberOfGraphicsObjectsColorLight = 10;
static const int NumberOfGraphicsObjectsSprite = 10;
static const int NumberOfGraphicsObjectsTexture = 10;
static const int NumberOfGraphicsObjectsTextureLight = 10;
static const int NumberOfGraphicsObjects = 10;


enum ParticleName
{
    Water,
    Earth,
    Fire,
    Air,
   //LongAgoTheFourNationsLivedInHarmony,
   //Then,
   //EverythingChangedWhenTheFireNationAttacked
    
};

static const int NumberOfParticleTypes = 4;

static const int NumberOfParticles = 10000;
static const int NumberOfParticleBursts =2000;