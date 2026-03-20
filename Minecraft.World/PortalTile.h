#pragma once
#include "HalfTransparentTile.h"
#include "Definitions.h"

class Random;

class PortalTile : public HalfTransparentTile
{
public:
	struct PortalDefinition
	{
		int data;
		int frameTile;
		int igniter;
		int primaryDimension;
		int returnDimension;
		int color;
	};

	static const int PORTAL_DATA_NETHER = 0;
	static const int PORTAL_DATA_AETHER = 1;

	PortalTile(int id);
	virtual void tick(Level *level, int x, int y, int z, Random *random);
	virtual int getColor() const;
	virtual int getColor(int auxData);
	virtual int getColor(LevelSource *level, int x, int y, int z);
	virtual int getColor(LevelSource *level, int x, int y, int z, int data);
    virtual AABB *getAABB(Level *level, int x, int y, int z);
    virtual void updateShape(LevelSource *level, int x, int y, int z, int forceData = -1, shared_ptr<TileEntity> forceEntity = shared_ptr<TileEntity>());	// 4J added forceData, forceEntity param
    virtual bool isSolidRender(bool isServerLevel = false);
    virtual bool isCubeShaped();
    virtual bool trySpawnPortal(Level *level, int x, int y, int z, bool actuallySpawn);
    virtual void neighborChanged(Level *level, int x, int y, int z, int type);
    virtual bool shouldRenderFace(LevelSource *level, int x, int y, int z, int face);
    virtual int getResourceCount(Random *random);
    virtual int getRenderLayer();
    virtual void entityInside(Level *level, int x, int y, int z, shared_ptr<Entity> entity);
	virtual void animateTick(Level *level, int xt, int yt, int zt, Random *random);
	virtual int cloneTileId(Level *level, int x, int y, int z);
	virtual bool mayPick(); // 4J Added override
	static const PortalDefinition *getPortalDefinition(int data);
	static int getDefaultPortalDataForDimension(int sourceDimension);
	static int getPortalTargetDimension(int data, int sourceDimension);
};
