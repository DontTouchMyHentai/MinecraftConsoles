Here is a breakdown of how to implement the Aether portal ignition with water, making sure it is implemented consistently with how the Nether portal works.

### 1. Understanding the Nether Portal Ignition

The Nether portal ignition happens in two main places:

1.  **`FlintAndSteelItem.cpp`**: When you use flint and steel, it has a special check. If you use it on an obsidian block, it calls `Tile::portalTile->trySpawnPortal(level, x, y, z, false)`. This doesn't actually create the portal (`false` prevents it), but it's used for achievements and stats. The main action it does is placing a fire block: `level->setTileAndUpdate(x, y, z, Tile::fire_Id);`.

2.  **`FireTile.cpp`**: This is where the real magic happens. When a fire block is placed, its `onPlace` method is called. Inside `FireTile::onPlace`, there is this logic:

    ```cpp
    void FireTile::onPlace(Level *level, int x, int y, int z)
    {
        if (level->dimension->id <= 0 && level->getTile(x, y - 1, z) == Tile::obsidian_Id)
        {
            if (Tile::portalTile->trySpawnPortal(level, x, y, z, true))
            {
                return;
            }
        }
        // ...
    }
    ```

    This code checks if the block below the fire is obsidian. If it is, it calls `Tile::portalTile->trySpawnPortal(level, x, y, z, true)`, and this time with `true`, which actually creates the portal.

### 2. The Problem with the Aether Portal

Your previous implementation was on the right track by adding the `igniter` field to `PortalDefinition`. However, there was no code that actually triggered the portal creation when water was placed. Using a water bucket would just place a water block, and that's it. The `onPlace` method for water blocks didn't have the necessary logic.

### 3. The Solution: Consistent Implementation

To fix this and keep the implementation consistent with the Nether portal, we need to modify the `onPlace` method for liquid tiles.

**File to modify**: `Minecraft.World/LiquidTile.cpp`

**The change**: Add the portal creation logic to `LiquidTile::onPlace`.

Here is the code that was added:

```cpp
void LiquidTile::onPlace(Level *level, int x, int y, int z)
{
	if (material == Material::water && level->getTile(x, y - 1, z) == Tile::glowstone_Id)
	{
		if (Tile::portalTile->trySpawnPortal(level, x, y, z, true))
		{
			return;
		}
	}
	updateLiquid(level, x, y, z);
}
```

This code does the following:
1.  It first checks if the liquid being placed is water (`material == Material::water`).
2.  Then, it checks if the block below is glowstone (`level->getTile(x, y - 1, z) == Tile::glowstone_Id`).
3.  If both are true, it calls `Tile::portalTile->trySpawnPortal(level, x, y, z, true)`, which will attempt to create the portal. The `trySpawnPortal` function will then use the `igniter` field you added and correctly identify that water can create the Aether portal.

With this change, the Aether portal is now created by the water block itself when placed on a glowstone frame, exactly like how the fire block creates the Nether portal when placed on an obsidian frame. This ensures the implementation is consistent and works as expected.
